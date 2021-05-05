#pragma once

#include "Player.hpp"

#include <iostream>
namespace pandemic{

class Medic : public Player{
    private:
            Board board ;
            City city;
    public:
        Medic(pandemic::Board board , pandemic::City city);


};
}