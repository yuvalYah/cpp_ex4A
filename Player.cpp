#include "Player.hpp"
#include <iostream>
namespace pandemic{

            Player::Player(Board board , City city){

            }

            // Player(Board board , City city);
    Player& Player::drive(City c) 
    {return *this;}
    Player& Player::fly_direct(City c) 
    {return *this;}
    Player& Player::fly_charter(City c)
    {return *this;}
    Player& Player::fly_shuttle(City c)
    {return *this;}
    Player& Player::build()
    {return *this;}
    Player& Player::discover_cure(Color color)
    {return *this;}
    Player& Player::treat( City c)
    {return *this;}

    std::string Player::role()
    {return "f";
    }//return the part of the plyer in the game , not implaments here
    Player& Player::take_card(City c)
    {return *this;}

   
}