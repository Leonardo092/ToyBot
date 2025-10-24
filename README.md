# ToyBot
This folder contains two versions (C++ and Python) of a terminal simulation of a virtual AGV roaming onto a 5x5 grid table.

C++ version:
-   make sure cmake tools and g++ compiler are installed in your system (if on Linux, run `sudo apt install build-essential`)
-   compile the executable by navigating into PlanarToyBot_cpp and running `make`
-   launch the executable named "run"

Python version:
-   make sure python3 is installed in your system (if on Linux, run `sudo apt-get install python3.x`)
-   run the main script via the command "python3 main_py"

How to test:
I tried to create a highly interactive application, where the user can insert commands via terminal.
For this reason, no pre-defined inputs or tests are loaded into the application; as user, feel free to explore the functionalities yourself and try stress the application to the limits you find satisfactory.

Here is a list of commands to interact with the robot:
	- PLACE X Y DIRECTION: it spawns the robot at position [X, Y] facing DIRECTION
	- MOVE: it makes the robot advance by one position in its current direction
	- LEFT: it makes the robot turn leftward by 90 degrees"
	- RIGHT: it makes the robot turn rightward by 90 degrees"
        - REPORT: it displays the current robot position and bearing"
        - HELP: it lists all the available commands"
        - EXIT or QUIT: type this only in case you are tired"
        
As developer, I hope you can have fun!
