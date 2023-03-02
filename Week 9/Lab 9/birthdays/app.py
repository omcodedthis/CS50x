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

# for this route, if requested by post, the name, month & day are added to an SQL table, birthdays.db
# & redirected back to the page, thus, reloading the page with updated values from the database. If
# the route was requested by get, the user is shown index.html where they can either submit a new
# birthday or view the previously added birthdays in the table using the SELECT * SQL statement.
@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        name = request.form.get("name")
        month = request.form.get("month")
        day = request.form.get("day")

        db.execute("INSERT INTO birthdays (name, month, day) VALUES (?, ?, ?);", name, month, day)

        return redirect("/")

    else:

        birthdays = db.execute("SELECT * FROM birthdays;")

        return render_template("index.html", birthdays=birthdays)


