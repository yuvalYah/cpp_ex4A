#pragma once

#include "Player.hpp"

#include <iostream>
namespace pandemic{

class FieldDoctor : public Player{
    private:
            Board board ;
            City city;
    public:
        FieldDoctor(pandemic::Board board , pandemic::City city);


};
}