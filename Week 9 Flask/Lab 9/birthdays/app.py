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
        list_of_birthdays_from_db = db.execute("SELECT * FROM birthdays;")
        return render_template("index.html", birthdays_list=list_of_birthdays_from_db)

@app.route("/delete", methods=["POST"])
def delete_entry():
    birthday_id = request.form.get('id')
    if birthday_id:
        db.execute(
            "DELETE FROM birthdays WHERE id=?",
            birthday_id,
        )
        return ("Item deleted")
    else:
        return ("No id field found in form data")

@app.route("/edit", methods=["POST"])
def edit_entry():
    form_data_name = request.form.get('name')
    form_data_month = request.form.get('month')
    form_data_day = request.form.get('day')
    form_data_id = request.form.get('id')
    print("Here are the details", form_data_name, form_data_month, form_data_day, form_data_id)
    if form_data_id: # A better way to do this would be to construct a dynamic query, but that could be liable to SQL injection...
        if form_data_name:
            print("got here #1")
            db.execute(
                "UPDATE birthdays SET name=? WHERE id=?",
                form_data_name,
                form_data_id,
            )
        if form_data_month:
            print("got here #2")
            db.execute(
                "UPDATE birthdays SET month=? WHERE id=?",
                form_data_month,
                form_data_id,
            )
        if form_data_day:
            print("got here #3")
            db.execute(
                "UPDATE birthdays SET day=? WHERE id=?",
                form_data_day,
                form_data_id,
            )
        return redirect("/")
    else:
        return ("No id found to update birthday")
