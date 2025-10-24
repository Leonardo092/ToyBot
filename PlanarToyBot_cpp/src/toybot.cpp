#include "../include/toybot.hpp"

ToyBot::ToyBot()
{
    Place();
}

bool ToyBot::Place(const int& a, const int& b, const std::string& dir)
{
    if (!isValidPosition(a, b))
    {
        std::cout<<std::endl;
        std::cerr << "Careful! The target position is out of the table." << std::endl;
        std::cout<<std::endl;
        return false;
    }
    else if (!isValidDirection(dir))
    {
        std::cout<<std::endl;
        std::cerr << "Invalid direction! Use one of the following: N, E, S, W." << std::endl;
        std::cout<<std::endl;
        return false;
    }
    else
    {
        state_.x = a;
        state_.y = b;
        state_.direction = dir;
        return true;
    }
}

void ToyBot::Report()
{
    std::cout<<std::endl;
    std::cout << "Robot is at position [" << state_.x << "," << state_.y << "] facing " << state_.direction << std::endl;
    std::cout<<std::endl;
}

bool ToyBot::isValidPosition(const int& a, const int& b)
{
    return (((a >= 0) && (a < grid_dimension_.first)) && ((b >= 0) && (b < grid_dimension_.second)));
}

void ToyBot::ShiftPosition(const int& a, const int& b)
{
    auto target_x = state_.x + a;
    auto target_y = state_.y + b;

    if (!isValidPosition(target_x, target_y))
    {
        std::cout<<std::endl;
        std::cerr << "Invalid move! Please do not push the robot down the table :(" << std::endl;
        std::cout<<std::endl;
        return;
    }
    else
    {
        state_.x = target_x;
        state_.y = target_y;
    }
}

bool ToyBot::isValidDirection(const std::string& dir)
{
    return (dir == "N" || dir == "E" || dir == "S" || dir == "W");
}

void ToyBot::ShiftDirection(const int& increment)
{
    std::vector<std::string> dir {"N", "E", "S", "W"};
    int target_idx = 0;

    auto it = std::find(dir.begin(), dir.end(), state_.direction);

    if (it != dir.end()) 
    {
        auto curr_idx = std::distance(dir.begin(), it);
        target_idx = curr_idx + increment;

        if (target_idx < 0)
            target_idx = dir.size() - 1;
        else if (static_cast<size_t>(target_idx) >= dir.size())
            target_idx = 0;

        state_.direction = dir[target_idx];      
    }
    else
    {
        std::cout<<std::endl;
        std::cerr << "Invalid direction! Maintaining previous direction" << std::endl;
        std::cout<<std::endl;
    }
}

void ToyBot::Left()
{
    ShiftDirection(-1);
}

void ToyBot::Right()
{
    ShiftDirection(1);
}

void ToyBot::Move()
{
    if (state_.direction == "N")
    {
        ShiftPosition(1, 0);
    }
    else if (state_.direction == "S")
    {
        ShiftPosition(-1, 0);
    }
    else if (state_.direction == "E")
    {
        ShiftPosition(0, 1); 
    }
    else if (state_.direction == "W")
    {
        ShiftPosition(0, -1);
    }
    else
    {
        std::cerr << "Invalid direction!" << std::endl;
    }
}