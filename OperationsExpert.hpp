#pragma once

#include "Player.hpp"

#include <iostream>
namespace pandemic{

class OperationsExpert : public Player{
    private:
            Board board ;
            City city;
    public:
        OperationsExpert(pandemic::Board board , pandemic::City city);


};
}