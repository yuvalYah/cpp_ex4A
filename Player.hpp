#pragma once
#include "Board.hpp"
#include <iostream>
namespace pandemic{

    class Player{
        private:
            Board board ;
            City city;
        public:
            Player(Board board , City city);
            Player& drive(City c);
            Player& fly_direct(City c);
            Player& fly_charter(City c);
            Player& fly_shuttle(City c);
            Player& build();
            Player& discover_cure(Color color);
            Player& treat( City c);

            std::string role();//return the part of the plyer in the game , not implaments here
            Player& take_card(City c);

    };
}