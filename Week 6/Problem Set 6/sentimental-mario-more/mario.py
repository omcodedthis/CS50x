
# main() prompts the user for the desired height & prints the pyramid of said height.
def main():
    height = get_input()
    draw_pyramid(height)


# get_input() gets the height from the user, only returning the value to main() when the
# Height inputted is between 1 & 8 inclusive.
def get_input():
    while True:
        try:
            user_input = int(input("Height:"))

            if (1 <= user_input <= 8):
                return user_input

        except ValueError:
            print("Not an integer!")



# draw_pyramid draws the pyramid of the Height the user inputted. i is increased by 1 each
# iteration of the loop after finding the spaces_req as the for-loop starts from 0, meaning
# that the very top of the pyramid will not be printed as i would be 0 (fencepost problem).
def draw_pyramid(height):
    for i in range(height):

        hashes_req = i + 1
        spaces_req = height - hashes_req

        print(" " * spaces_req, end="")

        print("#" * hashes_req, end="")

        print("  ", end="")

        print("#" * hashes_req)


main()