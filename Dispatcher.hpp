#pragma once

#include "Player.hpp"

#include <iostream>
namespace pandemic{

class Dispatcher : public Player{
    private:
            Board board ;
            City city;
    public:
        Dispatcher(pandemic::Board board , pandemic::City city);


};
}