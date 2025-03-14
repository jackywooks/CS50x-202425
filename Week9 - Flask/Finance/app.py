import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, get_flashed_messages
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)
# For flash
app.secret_key = b'_5#y2L"F4Q8z\n\xec]/'

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
    user_id = session["user_id"]
    portfolio = db.execute("SELECT * FROM portfolio WHERE user_id = (?)", user_id)
    cash = db.execute("SELECT cash FROM users WHERE id = (?) LIMIT 1", user_id)
    cash = cash[0]["cash"]
    for stock in portfolio:
        result = lookup(stock.get("symbol"))
        current_price = result.get("price")
        stock.update({"current_price": current_price})
    print(portfolio)
    return render_template("index.html", portfolio=portfolio, cash=cash)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        # Ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide stock symbol", 400)
        # Ensure shares was submitted
        elif not request.form.get("shares"):
            return apology("must provide shares to buy", 400)

        if not request.form.get("shares").isdigit():
            return apology("Pleaes input postive integer of shares", 400)

        # Try to buy the stock
        result = lookup(request.form.get("symbol"))
        if result:
            symbol = result.get("symbol")
            price = float(result.get("price"))
            shares = float(request.form.get("shares"))
            user_id = session["user_id"]

            if symbol:
                try:
                    cash = db.execute("SELECT cash FROM users WHERE id = (?) LIMIT 1", user_id)
                    cash = cash[0]["cash"]

                    # calculate the total cost required to buy the shares
                    total_price = shares * price

                    if cash > total_price:
                        # insert successful transaction to db
                        db.execute("INSERT INTO transactions (user_id, symbol, shares, unit_price, total_price) VALUES (?, ?, ?, ?, ?)",
                                   user_id, symbol, shares, price, total_price)

                        # insert or update in porfolio
                        # check if the stock is in my portfo first
                        myStock = db.execute(
                            "SELECT shares, average_price FROM portfolio WHERE user_id = (?) AND symbol = (?)", user_id, symbol)
                        print(myStock)
                        if myStock:
                            myStock = myStock[0]
                            current_price = myStock["average_price"]
                            current_share = myStock["shares"]
                            # calculate the new average price
                            new_total_share = current_share + shares
                            print(new_total_share)
                            new_average_price = ((current_price * current_share) +
                                                 (total_price))/(new_total_share)
                            print(f"New Average: {new_average_price}")
                            db.execute("UPDATE portfolio SET shares = (?), average_price = (?) WHERE user_id = (?) AND symbol = (?)",
                                       new_total_share, new_average_price, user_id, symbol)
                        else:
                            db.execute("INSERT INTO portfolio (user_id, symbol, shares, average_price) VALUES (?, ?, ?, ?)",
                                       user_id, symbol, shares, price)
                        # Update user cash
                        db.execute("UPDATE users SET cash = cash - ? WHERE id = ?",
                                   total_price, user_id)
                    else:
                        return apology("Not Enough Cash in your Account", 400)
                except RuntimeError as e:
                    print(e)
                    return apology("Failed Operation", 500)
            else:
                return apology("Invalid Stock Symbol", 400)
        elif result is None:
            return apology("Invalid Stock Symbol", 400)
        return redirect("/")
    return render_template("buy.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_id = session["user_id"]
    on_hand_stocks = db.execute("SELECT symbol FROM portfolio WHERE user_id = (?)", user_id)
    print(type(on_hand_stocks))
    on_hand_stocks = list(map(lambda item: item["symbol"], on_hand_stocks))
    if request.method == "POST":
        # Ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide stock symbol", 400)
        # Ensure shares was submitted
        elif not request.form.get("shares"):
            return apology("must provide shares to buy", 400)
        if request.form.get("shares").isdigit():
            shares = int(request.form.get("shares"))
        else:
            return apology("Pleaes input postive integer of shares", 400)
        # Try to Sell the stock
        result = lookup(request.form.get("symbol"))
        if result:
            symbol = result.get("symbol")
            price = float(result.get("price"))
            user_id = session["user_id"]

            if symbol:
                owned_shares = db.execute(
                    "SELECT shares FROM portfolio WHERE user_id = (?) AND symbol = (?) LIMIT 1", user_id, symbol)
                owned_shares = owned_shares[0]["shares"]

                # calculate the total revenue when selling the stock
                total_revenue = shares * price

                if owned_shares >= shares:
                    db.execute("INSERT INTO transactions (user_id, symbol, shares, unit_price, total_price) VALUES (?, ?, ?, ?, ?)",
                               user_id, symbol, shares * -1, price, total_revenue)
                    if (owned_shares-shares) == 0:
                        db.execute(
                            "DELETE FROM portfolio WHERE user_id = (?) AND symbol = (?)", user_id, symbol)
                    db.execute("UPDATE portfolio SET shares = (?) WHERE user_id = (?) AND symbol = (?)",
                               owned_shares - shares, user_id, symbol)

                # add cash back to the account
                cash = db.execute("SELECT cash FROM users WHERE id = (?) LIMIT 1", user_id)
                cash = cash[0]["cash"]
                db.execute("UPDATE users SET cash = (?) WHERE id = (?) LIMIT 1",
                           total_revenue + cash, user_id)

        else:
            return apology("Invalid Stock Symbol", 400)
        return redirect("/")
    return render_template("sell.html", on_hand_stocks=on_hand_stocks)


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    user_id = session["user_id"]
    transactions = db.execute("SELECT * FROM transactions WHERE user_id = (?)", user_id)
    return render_template("transaction.html", transactions= transactions)


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
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
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
    if "quoteResult" not in session:
        session["quoteResult"] = []

    """Get stock quote."""
    if request.method == "POST":
        action = request.form.get("action")
        if action == "quote":
            if not request.form.get("symbol"):
                return apology("must provide stock symbol", 400)
            result = lookup(request.form.get("symbol"))
            if result:
                symbol = result.get("symbol")
                if symbol:
                    # Check if the symbol is already in the list
                    for i, item in enumerate(session["quoteResult"]):
                        if item.get("symbol") == symbol:
                            # Replace the existing dictionary
                            session["quoteResult"][i] = result
                            break  # Stop searching after replacement
                    else:
                        # Symbol not found, append the new result
                        session["quoteResult"].append(result)
            elif result is None:
                return apology("Invalid stock symbol", 400)
            return render_template("quote.html", result=session["quoteResult"])
        elif action == "clear":
            session["quoteResult"] = []  # Clear the session list
            print(session["quoteResult"])
            flash("Quote history cleared.", "success")
            return redirect("/quote")
        elif action == "refresh":
            for stock in session["quoteResult"]:
                stock["price"] = lookup(stock["symbol"])["price"]
            flash("Price Refreshed.", "success")
            return redirect("/quote")
    return render_template("quote.html", result=session["quoteResult"])


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        name = request.form.get("username")
        password = request.form.get("password")
        # Ensure username was submitted
        if not name:
            return apology("must provide username", 400)
        # Ensure password was submitted
        elif not password:
            return apology("must provide password", 400)
        elif not password == request.form.get("confirmation"):
            return apology("passwords do not match", 400)
        # Insert new user in db
        try:
            db.execute("INSERT INTO users(username, hash) VALUES(?, ?)",
                       name, generate_password_hash(password))
            # Redirect user to home page
            flash(f"{name} is registered successfully.")
            return render_template("login.html")
        except ValueError:
            return apology(f"Duplicate User ID \"{name}\"", 400)
        except:
            return apology("Database Error, Please try again", 500)
    return render_template("register.html")
