import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
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

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# This route denotes the homepage for the user. Using SQL statements and for-loops, a dictionary of the shares
# & prices of each respective ticker as well the total value of each holding owned is created. The user balance
# & holding values are determined using an SQL statement and the summation of all the total value for each
# holding using a for-loop respectively, these are then put into a list. These lists & dictionaries are passed
# to the render_template where they are used to populate the table values.
@app.route("/")
@login_required
def index():
    ticker_types = db.execute("SELECT DISTINCT ticker FROM users_index WHERE user_id=?;", session["user_id"])
    ticker_shares = {}

    for i in range(len(ticker_types)):
        current_ticker = ticker_types[i]["ticker"]
        holder1 = db.execute("SELECT SUM(shares_owned) FROM users_index WHERE user_id=? AND ticker=?;",
                             session["user_id"], current_ticker)
        ticker_shares[current_ticker] = holder1[0]["SUM(shares_owned)"]
    ticker_prices = {}

    for i in range(len(ticker_types)):
        current_ticker = ticker_types[i]["ticker"]
        price = lookup(current_ticker)
        ticker_prices[current_ticker] = price["price"]

    total_value = {}
    for i in range(len(ticker_types)):
        current_ticker = ticker_types[i]["ticker"]
        holder2 = db.execute("SELECT SUM(shares_owned) FROM users_index WHERE user_id=? AND ticker=?;",
                             session["user_id"], current_ticker)
        price = lookup(current_ticker)
        total_value[current_ticker] = price["price"] * holder2[0]["SUM(shares_owned)"]

    user_data = db.execute("SELECT cash FROM users WHERE id = ?;", session["user_id"])
    user_cash = user_data[0]["cash"]
    holding_value = 0

    for ticker in total_value:
        holding_value += total_value[ticker]

    user_value = user_cash + holding_value
    user_finances = [user_cash, holding_value, user_value]

    return render_template("index.html", ticker_shares=ticker_shares, ticker_prices=ticker_prices, total_value=total_value, user_finances=user_finances)


# This route denotes the buy page for the user. If the request method is via GET, the user is shown buy.html where they
# can input their details. If the request method is via POST (else), the user details are checked for validity in terms of
# whether the shares is a postive integer, whether ticker is valid, whether the user has sufficent funds. Then, the
# SQL table users_index & users_buy are inserted with the transaction details & the users table is updated with a the
# balance.
@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")

    else:
        ticker = request.form.get("symbol")
        try:
            shares = int(request.form.get("shares"))

        except ValueError:
            return apology("invalid amount of shares", 400)

        ticker_details = lookup(ticker)

        if ticker_details == None:
            return apology("invalid ticker", 400)

        if shares <= 0:
            return apology("invalid amount of shares", 400)

        cost = ticker_details["price"] * shares
        user_cash = db.execute("SELECT cash FROM users WHERE id = ?;", session["user_id"])

        if cost > user_cash[0]["cash"]:
            return apology("Insufficient funds to proceed with transaction", 403)

        db.execute("INSERT INTO users_buy (user_id, ticker, shares_bought) VALUES (?, ?, ?);", session["user_id"], ticker, shares)
        db.execute("UPDATE users SET cash=? WHERE id=?;", user_cash[0]["cash"] - cost, session["user_id"])
        db.execute("INSERT INTO users_index (ticker, shares_owned, user_id) VALUES (?, ?, ?);", ticker, shares, session["user_id"])
        return redirect("/")


# This route denotes the history page for the user. Using SQL statements, the "buys" & "sells" dictionaries of the user are created.
# These dictionaries are passed to render_template to populate the values in the table.
@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_bought = db.execute("SELECT ticker, shares_bought FROM users_buy WHERE user_id=?", session["user_id"])
    user_sold = db.execute("SELECT ticker, shares_sold FROM users_sold WHERE user_id=?", session["user_id"])

    return render_template("history.html", user_bought=user_bought, user_sold=user_sold)


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


# This route denotes the quote page for the user. If the request method is via GET, the user is shown quote.html
# where they can input the details of the stock (ticker) they wish to quote. If the request method is via POST
# (else), the user input is checked for validity. Then, the user is shown quoted.html passing ticker_details,
# a dictionary of all the details of the ticker. This is used to populate the table in quoted.html.
@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html")

    else:
        ticker = request.form.get("symbol")
        ticker_details = lookup(ticker)
        if ticker_details == None:
            return apology("invalid ticker", 400)

        return render_template("quoted.html", ticker_details=ticker_details)


# This route denotes the register page for the user. If the request method is via GET, the user is shown
# register.html where they can input their details. If the request method is via POST, the user input
# is checked, ensuring that the username has not been taken, the password & the confirmation match &
# all the text-boxes have been filled. A hash is generated for this password and the user details are
# added to the users table in finance.db using an SQL statement.
@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "GET":
        return render_template("register.html")

    elif request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        username_validity = db.execute("SELECT * FROM users WHERE username =?", username)

        if len(username_validity) > 0:
            return apology("username exists", 400)

        if not username:
            return apology("must provide username", 400)

        elif not password:
            return apology("must provide password", 400)

        elif not confirmation:
            return apology("must re-type password", 400)

        if password != confirmation:
            return apology("passwords do not match, please try again", 400)

        hash = generate_password_hash(password)

        db.execute("INSERT INTO users (username, hash) VALUES (?, ?);", username, hash)

        return render_template("login.html")


# This route denotes the sell page for the user. If the request method is via GET, the user is shown sell.html where they
# can input their details. If the request method is via POST (else), the user details are checked for validity in terms of
# whether the shares is a postive integer, whether the user owns the ticker, whether the user has sufficent shares. A
# dictionary, ticker_shares, is created to determined the tickers and the respective shares the user own. This is used to
# populate the option select element of the page. Then, the SQL table users_index & users_sell are inserted with the
# transaction details & the users table is updated with a the balance.
@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "GET":
        return render_template("sell.html")

    else:
        user_cash = db.execute("SELECT cash FROM users WHERE id = ?;", session["user_id"])
        ticker = request.form.get("symbol")
        shares = int(request.form.get("shares"))

        ticker_details = lookup(ticker)

        cost = ticker_details["price"] * shares

        if ticker_details == None:
            return apology("invalid ticker", 400)

        elif shares <= 0:
            return apology("invalid amount of shares", 400)

        ticker_types = db.execute("SELECT DISTINCT ticker FROM users_index WHERE user_id=?;", session["user_id"])
        ticker_shares = {}

        for i in range(len(ticker_types)):
            current_ticker = ticker_types[i]["ticker"]
            holder1 = db.execute("SELECT SUM(shares_owned) FROM users_index WHERE user_id=? AND ticker=?;",
                                 session["user_id"], current_ticker)
            ticker_shares[current_ticker] = holder1[0]["SUM(shares_owned)"]

        if ticker in ticker_shares:
            if ticker_shares[ticker] <= shares:
                return apology("insufficent shares to proceed with transaction", 400)

        db.execute("INSERT INTO users_sold (user_id, ticker, shares_sold) VALUES (?, ?, ?);", session["user_id"], ticker, shares)
        db.execute("UPDATE users SET cash=? WHERE id=?;", user_cash[0]["cash"] + cost, session["user_id"])
        db.execute("INSERT INTO users_index (ticker, shares_owned, user_id) VALUES (?, ?, ?);", ticker, -shares, session["user_id"])
        return redirect("/")


# This denotes the edit page for the user. The user can change their password, and has similar functionality to register's
# in terms of checking and updateding the password.
@app.route("/edit", methods=["GET", "POST"])
@login_required
def edit():
    if request.method == "GET":
        return render_template("edit.html")

    else:
        new_password = request.form.get("edit")
        confirmation = request.form.get("confirmation")

        if new_password != confirmation:
            return apology("passwords do not match, please try again", 400)

        if not new_password:
            return apology("must provide password", 400)

        hash = generate_password_hash(new_password)

        db.execute("UPDATE users SET hash=? WHERE id=?;", hash, session["user_id"])
        return redirect("/")