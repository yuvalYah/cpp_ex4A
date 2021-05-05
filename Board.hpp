#pragma once
#include "City.hpp"
#include "Color.hpp"

#include <iostream>
namespace pandemic{
    class Board{
        private:
        public:
            // const int operator[](uint index) const;
            void operator=(int value);
            // const Board operator[](pandemic::City s) const;
            int& operator[](pandemic::City index);

            friend std::ostream& operator<< (std::ostream& os, const Board& c);
            bool is_clean();
            void remove_cures();



    };
}