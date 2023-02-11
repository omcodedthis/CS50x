import random
from pyfiglet import Figlet
figlet = Figlet()
import sys

# main() takes in CLAs for the font the user wishes to printed a piece of text in. If the
# user does not specify a certain font, a random font is used.
def main():

    font_list = figlet.getFonts()
    total_fonts = len(font_list)

# path for no specific font.
    if (len(sys.argv) == 1):
        user_text = get_input()

        get_font = random.randint(0, total_fonts)

        figlet.setFont(font=font_list[get_font])

        print("Output:")
        print(figlet.renderText(user_text))
        sys.exit(0)

# path for a specific font.
    elif ((len(sys.argv) == 3) and (((sys.argv[1] =="-f") or (sys.argv[1] =="-font")))):

        if (sys.argv[2]) not in font_list:
            print("Invalid Usage")
            sys.exit(1)

        else:
            user_text = get_input()

            figlet.setFont(font=sys.argv[2])

            print("Output:")
            print(figlet.renderText(user_text))
            sys.exit(0)

# path for invalid input.
    else:
        print("Invalid Usage")
        sys.exit(1)


def get_input():
    text = str(input("Input:"))
    return text



main()