#pragma once

#include "Player.hpp"

#include <iostream>
namespace pandemic{

class Scientist : public Player{
    private:
            Board board ;
            City city;
            int n;
    public:
        Scientist(pandemic::Board board , pandemic::City city, int);


};
}