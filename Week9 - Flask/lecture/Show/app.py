# Says hello to world
from cs50 import SQL
from flask import Flask, render_template, request

app = Flask(__name__)

db = SQL("sqlite:///shows.db")

@app.route("/", methods=["GET","POST"])
def index():
    return render_template("index.html")


@app.route("/search", methods=["GET","POST"])
def search():
    query = "%" + request.args.get("q") + "%"
    shows = db.execute("SELECT * FROM shows WHERE title LIKE ?", query)
    return render_template("search.html", shows=shows)

