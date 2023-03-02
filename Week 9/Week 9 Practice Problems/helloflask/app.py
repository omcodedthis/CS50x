from flask import Flask, render_template, request

app = Flask(__name__)

# this is a list of all the valid colors the form has.
colors = ["red", "blue"]


# this route asks the user to enter the form if it was requested by GET. The form then
# states all valid colors as the options. Once the user submits the form, this route is
# now requested by POST. The color submitted is checked for its validity and if it is
# not valid, an invalid page, using invalid.html is shown to the user.
@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "GET":
        return render_template("index.html", colors=colors)
    else:
        color = request.form.get("color")

        if color in colors:
            return render_template("color.html", color=color)
        else:
            return render_template("invalid.html")
