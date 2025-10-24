import threading
import time
import sys
from toybot import ToyBot

running = True

# loop allowing the user to insert commands at execution time
def inputLoop(bot):
    global running
    place_initialized = False

    print("Welcome to our robot simulator! Please place your robot on the grid table using the command:")
    print("PLACE X Y DIRECTION")
    print()

    while running:

        try:
            cmd = input("> ").strip()
        except EOFError:
            break

        if (cmd == "QUIT" or cmd == "Quit" or cmd == "quit") or (cmd == "EXIT" or cmd == "Exit" or cmd == "exit"):
            running = False

        elif (cmd == "MOVE" or cmd == "move"):
            if not place_initialized:
                print()
                print("Impossible to move as the robot is not on the table.")
                print("Please initialize the robot position first using the PLACE command.")
                print()
            else:
                bot.Move()
        
        elif (cmd == "LEFT" or cmd == "Left" or cmd == "left"):
            if not place_initialized:
                print()
                print("Impossible to turn left as the robot is not on the table.")
                print("Please initialize the robot position first using the PLACE command.")
                print()
            else:
                bot.Left()

        elif (cmd == "RIGHT" or cmd == "Right" or cmd == "right"):
            if not place_initialized:
                print()
                print("Impossible to turn right as the robot is not on the table.")
                print("Please initialize the robot position first using the PLACE command.")
                print()
            else:
                bot.Right()

        elif (cmd == "REPORT" or cmd == "Report" or cmd == "report"):
            if not place_initialized:
                print()
                print("Nothing to report as the robot is not on the table.")
                print("Please initialize the robot position first using the PLACE command.")
                print()
            else:
                bot.Report()

        elif cmd.strip().split()[0].lower() == "place":
            # Split the full command into parts
            parts = cmd.strip().split()

            if len(parts) == 4:
                # Case: user typed everything in one line, e.g. "PLACE/place 1 1 N"
                try:
                    x = int(parts[1])
                    y = int(parts[2])
                    direction = parts[3]

                    valid_placement = bot.Place(x, y, direction)

                    if not place_initialized and valid_placement:
                        place_initialized = True
                        print()
                        print("Well done! Feel free to interact with the robot via the following commands:")
                        print("1) PLACE X Y DIRECTION: you are already familiar with this :)")
                        print("2) MOVE: it makes the robot advance by one position in its current direction")
                        print("3) LEFT: it makes the robot turn leftward by 90 degrees")
                        print("4) RIGHT: it makes the robot turn rightward by 90 degrees")
                        print("5) REPORT: it displays the current robot position and bearing")
                        print("6) HELP: it lists all the available commands")
                        print("7) EXIT or QUIT: type this only in case you are tired")
                        print()
                except ValueError:
                    print("\nInvalid PLACE command. Usage: PLACE X Y DIRECTION\n")

            elif len(parts) == 1:
                # Case: user typed just "PLACE/place", ask for coordinates next
                try:
                    user_input = input("Now enter X, Y, and DIRECTION separated by spaces").strip().split()
                    if len(user_input) != 3:
                        raise ValueError

                    x, y, direction = user_input
                    x = int(x)
                    y = int(y)

                    valid_placement = bot.Place(x, y, direction)

                    if not place_initialized and valid_placement:
                        place_initialized = True
                        print()
                        print("Well done! Feel free to interact with the robot via the following commands:")
                        print("1) PLACE X Y DIRECTION: you are already familiar with this :)")
                        print("2) MOVE: it makes the robot advance by one position in its current direction")
                        print("3) LEFT: it makes the robot turn leftward by 90 degrees")
                        print("4) RIGHT: it makes the robot turn rightward by 90 degrees")
                        print("5) REPORT: it displays the current robot position and bearing")
                        print("6) HELP: it lists all the available commands")
                        print("7) EXIT or QUIT: type this only in case you are tired")
                        print()
                except ValueError:
                    print("\nInvalid PLACE command. Usage: PLACE X Y DIRECTION\n")

            else:
                # Anything else is invalid
                print("\nInvalid PLACE command. Usage: PLACE X Y DIRECTION\n")
        
        elif (cmd == "HELP" or cmd == "Help" or cmd == "help"):
            print()
            print("Do not panic! Here is the list of the available commands:")
            print("1) PLACE X Y DIRECTION: it spawns the robot at position [X, Y] facing DIRECTION ")
            print("2) MOVE: it makes the robot advance by one position in its current direction")
            print("3) LEFT: it makes the robot turn leftward by 90 degress")
            print("4) RIGHT: it makes the robot turn rightward by 90 degress")
            print("5) REPORT: it displays the current robot position and bearing")
            print("6) HELP: it lists all the available commands")
            print("7) EXIT or QUIT: type this only in case you are tired")
            print()

        else:
            print()
            print(f"Mmm not quite! Command: {cmd} not in the list, pick one of the following: ")
            print("1) PLACE X Y DIRECTION: it spawns the robot at position [X, Y] facing DIRECTION ")
            print("2) MOVE: it makes the robot advance by one position in its current direction")
            print("3) LEFT: it makes the robot turn leftward by 90 degress")
            print("4) RIGHT: it makes the robot turn rightward by 90 degress")
            print("5) REPORT: it displays the current robot position and bearing")
            print("6) HELP: it lists all the available commands")
            print("7) EXIT or QUIT: type this only in case you are tired")
            print()


def main():
    global running

    # create class object
    bot = ToyBot()

    # start the input thread
    listener = threading.Thread(target=inputLoop, args=(bot,))
    listener.start()

    # meanwhile, main keeps doing its work (in this case, just staying up and running)
    while running:
        time.sleep(0.01)

    # stop cleanly
    listener.join()

    print("Exiting program. Hope you had fun!")

if __name__ == "__main__":
    main()