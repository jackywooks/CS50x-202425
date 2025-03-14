# Says hello to world
from cs50 import SQL
from flask import Flask, render_template, request


db = SQL("sqlite:///froshims.db")
app = Flask(__name__)

SPORTS = ["Basketball", "Football", "Frisbee",]


@app.route("/")
def index():
    return render_template("index.html", sports=SPORTS)


@app.route("/register", methods=["POST"])
def register():
    name = request.form.get("name")
    if not name:
        return render_template("error.html", message="Missing Name")

    sport = request.form.get("sport")
    if not sport:
        return render_template("error.html", message="Missing sport")

    sport = request.form.get("sport")
    if sport not in SPORTS:
        return render_template("error.html", message="Invalid sport")

    db.execute("INSERT INTO registrants(name, sport) VALUES(?, ?)", name, sport)
    regRecord = db.execute("SELECT name, sport FROM registrants")
    return render_template("success.html", regRecord=regRecord)
