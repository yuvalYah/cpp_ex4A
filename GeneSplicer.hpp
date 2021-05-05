#pragma once

#include "Player.hpp"

#include <iostream>
namespace pandemic{

class GeneSplicer : public Player{
    private:
            Board board ;
            City city;
    public:
        GeneSplicer(pandemic::Board board , pandemic::City city);


};
}