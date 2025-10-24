#include "../include/toybot.hpp"
#include <thread>
#include <atomic>
#include <memory>
#include <sstream>

std::atomic<bool> running(true);

// loop allowing the user to insert commands at execution time
void inputLoop(std::shared_ptr<ToyBot> bot) 
{
    std::string cmd;
    bool place_initialized = false;

    std::cout << "Welcome to our robot simulator! Please place your robot on the grid table using the command:" << std::endl;
    std::cout << "PLACE X Y DIRECTION" << std::endl;
    std::cout<<std::endl;

    while (running) 
    {
        std::cout << "> " << std::flush;

        if (!(std::cin >> cmd)) 
            break; // handle EOF or error

        if ((cmd == "QUIT" || cmd == "Quit" || cmd == "quit") || (cmd == "EXIT" || cmd == "Exit" || cmd == "exit")) 
        {
            running = false;
        } 
        else if (cmd == "MOVE" || cmd == "Move" || cmd == "move") 
        {
            if (!place_initialized) 
            {
                std::cout<<std::endl;
                std::cout<<"Impossible to move as the robot is not on the table."<<std::endl;
                std::cout<<"Please initialize the robot position first using the PLACE command."<<std::endl;
                std::cout<<std::endl;
            }
            else
            {
                bot->Move();
            }
        } 
        else if (cmd == "LEFT" || cmd == "Left" || cmd == "left") 
        {
            if (!place_initialized) 
            {
                std::cout<<std::endl;
                std::cout<<"Impossible to turn left as the robot is not on the table."<<std::endl;
                std::cout<<"Please initialize the robot position first using the PLACE command."<<std::endl;
                std::cout<<std::endl;
            }
            else
            {
                bot->Left();
            }
        } 
        else if (cmd == "RIGHT" || cmd == "Right" || cmd == "right") 
        {
            if (!place_initialized) 
            {
                std::cout<<std::endl;
                std::cout<<"Impossible to turn right as the robot is not on the table."<<std::endl;
                std::cout<<"Please initialize the robot position first using the PLACE command."<<std::endl;
                std::cout<<std::endl;
            }
            else
            {
                bot->Right();
            }
        } 
        else if (cmd == "REPORT" || cmd == "Report" || cmd == "report") 
        {
            if (!place_initialized) 
            {
                std::cout<<std::endl;
                std::cout<<"Nothing to report as the robot is not on the table."<<std::endl;
                std::cout<<"Please initialize the robot position first using the PLACE command."<<std::endl;
                std::cout<<std::endl;
            }
            else
            {
                bot->Report();
            }
        } 
        else if (cmd == "PLACE" || cmd == "Place" || cmd == "place")
        {
            int x, y;
            std::string dir;

            // Peek if there's more on the same line after "PLACE"
            std::string rest_of_line;
            std::getline(std::cin, rest_of_line);

            // Trim leading spaces
            rest_of_line.erase(0, rest_of_line.find_first_not_of(" \t\r\n"));

            if (!rest_of_line.empty()) 
            {
                // User typed everything in one go, e.g. "PLACE 1 2 NORTH"
                std::istringstream iss(rest_of_line);
                if (iss >> x >> y >> dir)
                {
                    auto valid_placement = bot->Place(x, y, dir);

                    if (!place_initialized && valid_placement)
                    {
                        place_initialized = true;
                        std::cout << std::endl;
                        std::cout << "Well done! Feel free to interact with the robot via the following commands:" << std::endl;
                        std::cout << "1) PLACE X Y DIRECTION: you are already familiar with this :) " << std::endl;
                        std::cout << "2) MOVE: it makes the robot advance by one position in its current direction" << std::endl;
                        std::cout << "3) LEFT: it makes the robot turn leftward by 90 degrees" << std::endl;
                        std::cout << "4) RIGHT: it makes the robot turn rightward by 90 degrees" << std::endl;
                        std::cout << "5) REPORT: it displays the current robot position and bearing" << std::endl;
                        std::cout << "6) HELP: it lists all the available commands" << std::endl;
                        std::cout << "7) EXIT or QUIT: type this only in case you are tired" << std::endl;
                        std::cout << std::endl;
                    }
                }
                else
                {
                    std::cout << "\nInvalid PLACE command. Usage: PLACE X Y DIRECTION\n\n";
                }
            }
            else 
            {
                // User typed "PLACE" only, let the user insert coordinates and direction right away
                std::cout << "Now enter X, Y, and DIRECTION separated by spaces or newlines";

                if (std::cin >> x >> y >> dir)
                {
                    auto valid_placement = bot->Place(x, y, dir);

                    if (!place_initialized && valid_placement)
                    {
                        place_initialized = true;
                        std::cout << std::endl;
                        std::cout << "Well done! Feel free to interact with the robot via the following commands:" << std::endl;
                        std::cout << "1) PLACE X Y DIRECTION: you are already familiar with this :) " << std::endl;
                        std::cout << "2) MOVE: it makes the robot advance by one position in its current direction" << std::endl;
                        std::cout << "3) LEFT: it makes the robot turn leftward by 90 degrees" << std::endl;
                        std::cout << "4) RIGHT: it makes the robot turn rightward by 90 degrees" << std::endl;
                        std::cout << "5) REPORT: it displays the current robot position and bearing" << std::endl;
                        std::cout << "6) HELP: it lists all the available commands" << std::endl;
                        std::cout << "7) EXIT or QUIT: type this only in case you are tired" << std::endl;
                        std::cout << std::endl;
                    }
                }
                else
                {
                    std::cout << "\nInvalid PLACE command. Usage: PLACE X Y DIRECTION\n\n";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            }
        }
        else if (cmd == "HELP" || cmd == "Help" || cmd == "help")
        {
            std::cout<<std::endl;
            std::cout << "Do not panic! Here is the list of the available commands:" << std::endl;
            std::cout << "1) PLACE X Y DIRECTION: it spawns the robot at position [X, Y] facing DIRECTION " << std::endl;
            std::cout << "2) MOVE: it makes the robot advance by one position in its current direction" << std::endl;
            std::cout << "3) LEFT: it makes the robot turn leftward by 90 degress" << std::endl;
            std::cout << "4) RIGHT: it makes the robot turn rightward by 90 degress" << std::endl;
            std::cout << "5) REPORT: it displays the current robot position and bearing" << std::endl;
            std::cout << "6) HELP: it lists all the available commands" << std::endl;
            std::cout << "7) EXIT or QUIT: type this only in case you are tired" << std::endl;
            std::cout<<std::endl;
        }
        else 
        {
            std::cout<<std::endl;
            std::cout << "Mmm not quite! Command: " << cmd << " not in the list, pick one of the following: " << std::endl;
            std::cout << "1) PLACE X Y DIRECTION: it spawns the robot at position [X, Y] facing DIRECTION " << std::endl;
            std::cout << "2) MOVE: it makes the robot advance by one position in its current direction" << std::endl;
            std::cout << "3) LEFT: it makes the robot turn leftward by 90 degress" << std::endl;
            std::cout << "4) RIGHT: it makes the robot turn rightward by 90 degress" << std::endl;
            std::cout << "5) REPORT: it displays the current robot position and bearing" << std::endl;
            std::cout << "6) HELP: it lists all the available commands" << std::endl;
            std::cout << "7) EXIT or QUIT: type this only in case you are tired" << std::endl;
            std::cout<<std::endl;
        }
    }
}

int main() 
{
    // create class object
    std::shared_ptr<ToyBot> mybot = std::make_shared<ToyBot>();

    // start the input thread
    std::thread listener(inputLoop, mybot);

    // meanwhile, main keeps doing its work (in this case, just staying up and running)
    while (running) 
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    // join the listener thread
    if (listener.joinable()) 
        listener.join();

    std::cout<<std::endl;
    std::cout << "Exiting program. Hope you had fun!" << std::endl;
    return 0;
}