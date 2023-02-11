# main() gets the user's input from the fn get_input. Depending on what the user had typed,
# either $0, $20 or $100 is printed to the terminal.
def main():
    user_input = get_input()
    user_input = user_input.lower()

    if "hello" in user_input:
        print("$0")

    elif (user_input[0] == "h"):
        print("$20")

    else:
        print("$100")

# get_input() gets the user's input & returns it to main.
def get_input():
    user_input = str(input("Greeting: "))
    return user_input

# calls the main() fn to begin the program.
main()