#include <stdlib.h>
#include <algorithm>
#include <string>
#include <vector>
#include <iostream>

class ToyBot
{
    private:
        // members
        struct State
        {
            int x;
            int y;
            std::string direction;
        }state_;

        constexpr static std::pair<int, int> grid_dimension_ = {5, 5};

        //methods
        bool isValidPosition(const int& a, const int& b);
        void ShiftPosition(const int& a, const int& b);
        bool isValidDirection(const std::string& dir);
        void ShiftDirection(const int& increment);
    
        public:
            // constructor
            ToyBot();
            // destructor
            ~ToyBot() = default;

            // methods
            bool Place(const int& a = 0, const int& b = 0, const std::string& dir = "N");
            void Report();
            void Left();
            void Right();
            void Move();
};