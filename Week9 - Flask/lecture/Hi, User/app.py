# Says hello to world

from flask import Flask, render_template, request

app = Flask(__name__)

@app.route("/", methods=["GET","POST"])
def index():
    # if method
    # if("name" in request.args):
    #     name = request.args["name"]
    # else:
    #     name = "world"
    # show name by get method
    # name = request.args.get("name","world")
    # return render_template("index.html", name=name)
    if request.method == "POST":
        return render_template("greet.html", name=request.form.get("name"))
    else:
        return render_template("index.html")
