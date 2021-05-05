#pragma once

#include "Player.hpp"

#include <iostream>
namespace pandemic{

class Researcher : public Player{
    private:
            Board board ;
            City city;
    public:
        Researcher(pandemic::Board board , pandemic::City city);


};
}