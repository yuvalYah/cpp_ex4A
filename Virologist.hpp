#pragma once

#include "Player.hpp"

#include <iostream>
namespace pandemic{

class Virologist : public Player{
    private:
            Board board ;
            City city;
    public:
        Virologist(pandemic::Board board , pandemic::City city);


};
}