import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":

        # TODO: Add the user's entry into the database
        form_data_name = request.form.get('name')
        form_data_month = request.form.get('month')
        form_data_day = request.form.get('day')
        if form_data_name and form_data_month and form_data_day:
            db.execute(
                "INSERT INTO birthdays (name, month, day) VALUES (?, ?, ?)",
                form_data_name,
                form_data_month,
                form_data_day,
            )

        return redirect("/")

    else:
        # TODO: Display the entries in the database on index.html
        list_of_birthdays_from_db = db.execute("SELECT * FROM birthdays;")

        # print(list_of_birthdays_from_db)
        # [
        #     {'id': 1, 'name': 'Harry', 'month': 7, 'day': 31},
        #     {'id': 2, 'name': 'Ron', 'month': 3, 'day': 1},
        #     {'id': 3, 'name': 'Hermione', 'month': 9, 'day': 19}
        # ]
        return render_template("index.html", birthdays_list=list_of_birthdays_from_db)

@app.route("/delete", methods=["GET", "POST"])
def delete_entry():
    if request.method == "POST":
        birthday_id = request.form.get('id')
        if birthday_id:
            db.execute(
                "DELETE FROM birthdays WHERE id=?",
                birthday_id,
            )
            # print("I found the data", birthday_id)
            # print("I'm going to sleep now...")
            # sleep(5)
            # print("I've woken up now...")
            return redirect("/")
        else:
            print("No id field found in form data")
            return redirect("/")
    else:
        return redirect("/")
