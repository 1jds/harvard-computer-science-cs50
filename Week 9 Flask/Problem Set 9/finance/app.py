import os
import time
import datetime

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_curr_cash = db.execute(
        "SELECT cash FROM users WHERE id = ?",
        session["user_id"],
    )
    totals = db.execute(
        "SELECT * FROM totals WHERE user_id = ?",
        session["user_id"],
    )
    updated_totals = []
    overall_portfolio_value = user_curr_cash[0]["cash"]
    for item in totals:
        new_item = {}
        company_info = db.execute(
            "SELECT * FROM companies WHERE company_id = ?",
            item["company_id"],
        )
        # print("DOING SOME DIAGNOSTICS HERE...", type(lookup(company_info[0]["ticker"])), lookup(company_info[0]["ticker"]), type(item["total"]), item["total"])
        new_item["symbol"] = company_info[0]["ticker"]
        new_item["company"] = company_info[0]["company_name"]
        new_item["shares"] = item["total"]
        new_item["curr_price"] = lookup(company_info[0]["ticker"])["price"] # TypeError: 'NoneType' object is not subscriptable...
        new_item["total_price"] = new_item["curr_price"] * item["total"]
        overall_portfolio_value += new_item["total_price"]
        new_item["total_price"] = usd(new_item["total_price"])
        updated_totals.append(new_item)
    return render_template("portfolio.html", totals = updated_totals, user_cash = usd(user_curr_cash[0]["cash"]), portfolio_value = usd(overall_portfolio_value))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        is_int = False
        try:
            int(request.form.get("shares"))
            is_int = True
        except ValueError as ex:
            print('"%s" cannot be converted to an int: %s' % (request.form.get("shares"), ex))
        if not is_int:
            return apology("non-numeric shares", 400)
        elif not (int(request.form.get("shares"))).is_integer():
            return apology("fractional values not allowed", 400)
        elif not request.form.get("symbol") or not lookup(request.form.get("symbol")):
            return apology("invalid symbol", 400)
        elif int(request.form.get("shares")) < 1:
            return apology("number of shares to buy must be a positive integer", 400)
        else:
            number_to_buy = int(request.form.get("shares"))
            current_price = lookup(request.form.get("symbol"))
            current_user_cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
            if current_user_cash[0]["cash"] - number_to_buy * current_price["price"] < 0:
                return apology("can't afford", 400)
            else:
                company_id = db.execute("SELECT company_id FROM companies WHERE ticker = ?", current_price["symbol"])
                if not company_id:
                    db.execute(
                        "INSERT INTO companies (ticker, company_name) VALUES (?, ?)",
                        current_price["symbol"],
                        current_price["name"],
                    )
                    company_id = db.execute("SELECT company_id FROM companies WHERE ticker = ?", current_price["symbol"])
                print("\n\n AM LOOKING AT THIS RIGHT NOW... \n\n", company_id, current_user_cash, current_price)
                    #  AM LOOKING AT THIS RIGHT NOW...
                    #  [] [{'cash': 5711.099999999999}] {'name': 'B', 'price': 32.85, 'symbol': 'B'}
                # 1. execute an update on the users table to change 'cash' to be the new reduced amount
                db.execute(
                    "UPDATE users SET cash = ?",
                    current_user_cash[0]["cash"] - number_to_buy * current_price["price"],
                )
                # 2. execute an insert into the transactions table to add the details of the present purchase of stocks
                unixepoch = int(time.time())
                print("HERE IS THE UNIX EPOCH.........", unixepoch)
                db.execute(
                    "INSERT INTO transactions (user_id, company_id, number_transacted, transaction_price, date_transacted) VALUES (?, ?, ?, ?, ?)",
                    session["user_id"],
                    company_id[0]["company_id"],
                    number_to_buy,
                    current_price["price"],
                    unixepoch,
                )
                # 3. execute an insert/update on the totals table to add/update the total number of stocks owned by the present user of the type/symbol in the current transaction
                curr_totals_for_session_user = db.execute(
                    "SELECT * FROM totals WHERE user_id = ? AND company_id = ?",
                    session["user_id"],
                    company_id[0]["company_id"]
                )
                if curr_totals_for_session_user:
                    db.execute(
                        "UPDATE totals SET total = ? WHERE user_id = ? AND company_id = ?",
                        curr_totals_for_session_user[0]["total"] + number_to_buy,
                        session["user_id"],
                        company_id[0]["company_id"],
                    )
                else:
                    db.execute(
                        "INSERT INTO totals (user_id, company_id, total) VALUES(?, ?, ?)",
                        session["user_id"],
                        company_id[0]["company_id"],
                        number_to_buy,
                    )
            return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transactions_history = db.execute(
        "SELECT * FROM transactions WHERE user_id = ?",
        session["user_id"]
    )
    updated_transactions_history = []
    for item in transactions_history:
        new_item = {}
        company_info = db.execute(
            "SELECT * FROM companies WHERE company_id = ?",
            item["company_id"],
        )
        new_item["symbol"] = company_info[0]["ticker"]
        new_item["company"] = company_info[0]["company_name"]
        new_item["shares"] = item["number_transacted"]
        new_item["price"] = item["transaction_price"]
        new_item["date"] = datetime.datetime.utcfromtimestamp(item["date_transacted"]).strftime('%Y-%m-%d %H:%M:%S')
        updated_transactions_history.append(new_item)
    return render_template("history.html", transactions_history = updated_transactions_history)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("must provide a symbol for lookup", 400)
        else:
            quote_info = lookup(request.form.get("symbol"))
            print(quote_info)
            # print(quote_info) // expected return value e.g. {'name': 'NFLX', 'price': 489.95, 'symbol': 'NFLX'}
            if quote_info:
                name = db.execute("SELECT company_name FROM companies WHERE ticker = ?", quote_info["symbol"])
                if name:
                    return render_template("quoted.html", company_name=name[0]["company_name"], company_symbol=quote_info["symbol"], current_price=usd(quote_info["price"]))
                else:
                    return render_template("quoted.html", company_name=quote_info["symbol"], company_symbol=quote_info["symbol"], current_price=usd(quote_info["price"]))
            else:
                return apology("invalid symbol", 400)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure that username contains alphanumeric characters (e.g. it's not just whitespace of some sort)
        username_has_no_alnum = True
        for character in request.form.get("username"):
            if character.isalnum():
                username_has_no_alnum = False
                break
        if username_has_no_alnum:
            return apology("username must contain at least one alphanumeric character", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Ensure password confirmation was submitted
        elif not request.form.get("confirmation"):
            return apology("must provide confirmation of password", 400)

        # Check that password and confirmation match
        elif not request.form.get("password") == request.form.get("confirmation"):
            return apology("the password did not match the confirmation", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username does not exist already
        if len(rows) >= 1:
            return apology("Sorry, that username has already been taken", 400)
        else:
            db.execute(
                "INSERT INTO users (username, hash) VALUES(?, ?)",
                request.form.get("username"),
                generate_password_hash(request.form.get("password")),
            )

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_stocks = db.execute(
        "SELECT total, ticker FROM totals JOIN companies ON companies.company_id = totals.company_id WHERE user_id = ?",
        session["user_id"]
    )
    dict_of_stocks = {}
    for stock in user_stocks:
        dict_of_stocks[stock["ticker"]] = stock["total"]

    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("missing symbol", 400)
        elif not dict_of_stocks[request.form.get("symbol")] > 0:
            return apology("no shares matching symbol", 400)
        elif not int(request.form.get("shares")) > 0:
            return apology("enter a positive integer", 400)
        elif not dict_of_stocks[request.form.get("symbol")] >= int(request.form.get("shares")):
            return apology("insufficient shares to sell", 400)
        else:
            # THIS IS ALL COPIED AND NEEDS EDITING
            curr_stock_and_user_info = db.execute(
                "SELECT total_id, user_id, companies.company_id, total, ticker, company_name, username, cash FROM totals JOIN companies ON companies.company_id = totals.company_id JOIN users ON users.id = totals.user_id WHERE user_id = ? AND ticker = ?",
                session["user_id"],
                request.form.get("symbol"),
            )
            number_to_sell = int(request.form.get("shares"))
            print("\n\n THE NUMBER TO SELL FOLLOWS HEREAFTER... \n\n", number_to_sell)
            current_price = lookup(request.form.get("symbol"))
            # 1. execute an update on the users table to change 'cash' to be the new increased amount
            db.execute(
                "UPDATE users SET cash = ?",
                curr_stock_and_user_info[0]["cash"] + number_to_sell * current_price["price"],
            )
            # 2. execute an insert into the transactions table to add the details of the present sale of stocks
            unixepoch = int(time.time())
            db.execute(
                "INSERT INTO transactions (user_id, company_id, number_transacted, transaction_price, date_transacted) VALUES (?, ?, ?, ?, ?)",
                session["user_id"],
                curr_stock_and_user_info[0]["company_id"],
                 0 - number_to_sell,
                current_price["price"],
                unixepoch,
            )

            # 3. execute an update/delete on the totals table to add/update the total number of stocks owned by the present user of the type/symbol in the current transaction
            if number_to_sell == curr_stock_and_user_info[0]["total"]:
                db.execute(
                    "DELETE FROM totals WHERE total_id = ?",
                    curr_stock_and_user_info[0]["total_id"],
                )
            else:
                db.execute(
                    "UPDATE totals SET total = ? WHERE total_id = ?",
                    curr_stock_and_user_info[0]["total"] - number_to_sell,
                    curr_stock_and_user_info[0]["total_id"],
                )
            return redirect("/")
            # THIS IS ALL COPIED AND NEEDS EDITING
    else:
        return render_template("sell.html", options=user_stocks)
# symbol shares
# [
#  {'total': 1, 'ticker': 'A'},
#  {'total': 5, 'ticker': 'AA'},
#  {'total': 150, 'ticker': 'F'}
# ]

# I NEED TO DELETE ITEMS FROM THE TOTALS TABLE IF THEY ARE ALL SOLD....
