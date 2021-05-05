#include "Board.hpp"
#include <iostream>

namespace pandemic{
    int a=1;
    // class Board{
    //     private:
    //     public:
            // const int operator[](uint index) const;
            void Board::operator=(int value){

            }
            // const Board operator[](pandemic::City s) const;
            int& Board::operator[](pandemic::City index){
                int mnm =1;
                return a;
            }

            std::ostream& operator<< (std::ostream& os, const Board& c){
                return os;
            }
            bool Board::is_clean(){
                return true;
            }
            void Board::remove_cures(){

            }



    // };
}