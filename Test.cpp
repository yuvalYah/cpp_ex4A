#include "doctest.h"
#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"
#include "Player.hpp"

#include "Researcher.hpp"
#include "Scientist.hpp"
#include "FieldDoctor.hpp"
#include "GeneSplicer.hpp"
#include "OperationsExpert.hpp"
#include "Dispatcher.hpp"
#include "Medic.hpp"
#include "Virologist.hpp"
using namespace pandemic;

// #include "Direction.hpp"
// using ariel::Direction;

#include <string>
#include <algorithm>
using namespace std;


TEST_CASE("check board class: operator []"){
    Board board;  
	board[City::Kinshasa] = 3;
    CHECK(board[City::Kinshasa] == 3);     
	board[City::Kinshasa] = 2;
    CHECK(board[City::Kinshasa] == 2);     
	board[City::MexicoCity] = 3;  
    CHECK(board[City::MexicoCity] == 3);     
	board[City::HoChiMinhCity] = 1; 
    CHECK(board[City::MexicoCity] == 1);     
    board[City::SaoPaulo] = 4;
    CHECK(board[City::SaoPaulo] == 4);     


}
TEST_CASE("check board class : is_clean"){
    Board board;  
    Player player{board ,City::Kinshasa };
    CHECK(board.is_clean() == true);
    board[City::Kinshasa] = 3;
    CHECK(board[City::Kinshasa] == 3);  
    CHECK_FALSE(board.is_clean());
    player.treat(City::Kinshasa).treat(City::Kinshasa).treat(City::Kinshasa);
    CHECK(board.is_clean()==true);
}
TEST_CASE("player test - drive"){
    Board board;
    Player player{board , City::Algiers };
    CHECK_THROWS(player.drive(City::Atlanta)); 
    CHECK_THROWS(player.drive(City::Baghdad));
    CHECK_THROWS(player.drive(City::Bangkok));
    CHECK_THROWS(player.drive(City::Beijing));
    CHECK_THROWS(player.drive(City::Bogota));
    CHECK_THROWS(player.drive(City::BuenosAires));

    CHECK_NOTHROW(player.drive(City::Madrid ));
    CHECK_NOTHROW(player.drive(City::Algiers ));//return to algiers

    CHECK_NOTHROW(player.drive(City::Paris ));
    CHECK_NOTHROW(player.drive(City::Algiers ));//return to algiers

    CHECK_NOTHROW(player.drive(City::Istanbul ));
    CHECK_NOTHROW(player.drive(City::Algiers ));//return to algiers

    CHECK_NOTHROW(player.drive(City::Cairo));

}
TEST_CASE("player test - fly_direct"){
    Board board;
    Player player{board , City::Atlanta};
    player.take_card(City::Baghdad )
	      .take_card(City::Bangkok )
	      .take_card(City::Beijing )
	      .take_card(City::Bogota );
    CHECK_THROWS(player.fly_direct(City::BuenosAires )) ;
    CHECK_THROWS(player.fly_direct(City::Cairo  )) ;
    CHECK_THROWS(player.fly_direct(City::Chennai  )) ;
    CHECK_THROWS(player.fly_direct(City::Delhi  )) ;

    CHECK_NOTHROW(player.fly_direct(City::Chicago));
    CHECK_THROWS(player.fly_direct(City::Chicago));

    CHECK_NOTHROW(player.fly_direct(City::Miami));
    CHECK_THROWS(player.fly_direct(City::Miami));

    CHECK_NOTHROW(player.fly_direct(City::Washington ));
    CHECK_THROWS(player.fly_direct(City::Washington ));
}
TEST_CASE("player test - fly_charter"){
    Board board;
    Player player{board , City::Essen };
    player.take_card(City::HoChiMinhCity  )
	      .take_card(City::HongKong  )
	      .take_card(City::Istanbul  )
	      .take_card(City::Jakarta  );
    CHECK_THROWS(player.fly_charter(City::Johannesburg)) ;
    CHECK_THROWS(player.fly_charter(City::Karachi)) ;
    CHECK_THROWS(player.fly_charter(City::Khartoum)) ;
    CHECK_THROWS(player.fly_charter(City::Kinshasa) );

    CHECK_THROWS(player.fly_charter(City::HoChiMinhCity)) ;
    CHECK_THROWS(player.fly_charter(City::HongKong)) ;
    CHECK_THROWS(player.fly_charter(City::Istanbul)) ;
    CHECK_THROWS(player.fly_charter(City::Jakarta)) ;
    player.take_card(City::Essen);
    CHECK_NOTHROW(player.fly_charter(City::HoChiMinhCity));
}
TEST_CASE("player test - fly_shuttle"){
    Board board;
    Player player{board , City::Kolkata  };
    player.take_card(City::Kolkata) //v
	      .take_card(City::Lagos)
	      .take_card(City::Manila)//v
	      .take_card(City::Chennai);//v
    CHECK_THROWS(player.fly_shuttle(City::Chennai));
    CHECK_THROWS(player.fly_shuttle(City::Manila));
    CHECK_THROWS(player.fly_shuttle(City::Lagos));

    CHECK_NOTHROW(player.build());
    player.drive(City::Delhi)
        .drive(City::Mumbai )
        .drive(City::Chennai );
    CHECK_NOTHROW(player.build());
    player.drive(City::Jakarta)
        .drive(City::HoChiMinhCity )
        .drive(City::Manila );
    CHECK_NOTHROW(player.build());
    
    CHECK_NOTHROW(player.fly_shuttle(City::Chennai));
    CHECK_NOTHROW(player.fly_shuttle(City::Manila));
    CHECK_NOTHROW(player.fly_shuttle(City::Kolkata));
    CHECK_NOTHROW(player.fly_shuttle(City::Chennai));

    CHECK_THROWS(player.fly_shuttle(City::Lagos));

}
TEST_CASE("player test - build"){
    Board board;
    Player player{board , City::Lima   };
    player.take_card(City::MexicoCity) //v
	      .take_card(City::LosAngeles )
	      .take_card(City::Sydney)//v
	      .take_card(City::Lima);//v
    
    CHECK_NOTHROW(player.build());
    CHECK_THROWS(player.build()); //cant build twise
    player.drive(City::MexicoCity );
    CHECK_NOTHROW(player.build());
    CHECK_THROWS(player.build()); //cant build twise
    player.drive(City::LosAngeles );
    CHECK_NOTHROW(player.build());
    CHECK_THROWS(player.build());
    player.drive(City::Sydney );
    CHECK_NOTHROW(player.build());
    CHECK_THROWS(player.build());

    player.drive(City::Jakarta );
    CHECK_THROWS(player.build());
    player.drive(City::Chennai );
    CHECK_THROWS(player.build());
    player.drive(City::Mumbai );
    CHECK_THROWS(player.build());

}
TEST_CASE("test player - discover_cure"){
    Board board;
    board[City::Paris] = 1;
    board[City::Santiago] = 1;
    board[City::SaoPaulo] = 2;
    board[City::Seoul] = 2;
    board[City::Sydney] = 3;
    board[City::Taipei] = 3;
    board[City::Karachi] = 1;
    board[City::Moscow] = 2;
    board[City::Tehran] = 3;
    Player player{board , City::London };
    player.take_card(City::LosAngeles )
	      .take_card(City::Manila )
	      .take_card(City::MexicoCity )
	      .take_card(City::Miami)
	      .take_card(City::Paris);
    player.drive(City::Paris);
    CHECK_THROWS(player.discover_cure(Color::Blue));
    player.build();
    CHECK_THROWS(player.discover_cure(Color::Blue));//dosent have 5 cards in blue color
    CHECK_THROWS(player.discover_cure(Color::Red));
    CHECK_THROWS(player.discover_cure(Color::Yellow));
    CHECK_THROWS(player.discover_cure(Color::Black));

    player.take_card(City::Santiago )
	      .take_card(City::SaoPaulo  );
    CHECK_NOTHROW(player.discover_cure(Color::Blue));
    CHECK_NOTHROW(player.discover_cure(Color::Yellow));
    CHECK_THROWS(player.discover_cure(Color::Red));
    CHECK_THROWS(player.discover_cure(Color::Black));

    player.take_card(City::Seoul)
	      .take_card(City::Shanghai)
	      .take_card(City::Sydney)
	      .take_card(City::Taipei)
          .take_card(City::Tokyo);
    CHECK_NOTHROW(player.discover_cure(Color::Blue));
    CHECK_NOTHROW(player.discover_cure(Color::Yellow));
    CHECK_NOTHROW(player.discover_cure(Color::Red));
    CHECK_THROWS(player.discover_cure(Color::Black));
     player.take_card(City::Karachi)
	      .take_card(City::Moscow )
	      .take_card(City::Mumbai)
	      .take_card(City::Riyadh)
          .take_card(City::Tehran);
    CHECK_NOTHROW(player.discover_cure(Color::Blue));
    CHECK_NOTHROW(player.discover_cure(Color::Yellow));
    CHECK_NOTHROW(player.discover_cure(Color::Red));
    CHECK_NOTHROW(player.discover_cure(Color::Black));
}
TEST_CASE("player test - treat"){
    Board board;
    board[City::Madrid] = 3;
    board[City::London ] = 1;
    board[City::Essen ] = 2;
    board[City::StPetersburg] = 2;
    Player player{board , City::Madrid };
    CHECK(board[City::Madrid] == 3);
    player.treat(City::Madrid);
    CHECK(board[City::Madrid] == 2);
    player.treat(City::Madrid);
    CHECK(board[City::Madrid] == 1);
    player.treat(City::Madrid);
    CHECK(board[City::Madrid] == 0);
    CHECK_THROWS(player.treat(City::Madrid));

    player.drive(City::London);
    CHECK(board[City::London] == 1);
    player.treat(City::London);
    CHECK(board[City::London] == 0);
    CHECK_THROWS(player.treat(City::London));

    player.drive(City::Essen);
    CHECK(board[City::Essen] == 2);
    player.treat(City::Essen);
    CHECK(board[City::Essen] == 1);
    player.treat(City::Essen);
    CHECK(board[City::Essen] == 0);
    CHECK_THROWS(player.treat(City::Essen));

    player.drive(City::StPetersburg);
    CHECK(board[City::StPetersburg] == 2);
    player.treat(City::StPetersburg);
    CHECK(board[City::StPetersburg] == 1);
    player.treat(City::StPetersburg);
    CHECK(board[City::StPetersburg] == 0);
    CHECK_THROWS(player.treat(City::StPetersburg));

    board[City::Montreal] = 3;
    board[City::Paris ] = 1;
    board[City::Essen ] = 2;
    board[City::Chicago] = 2;
    player.drive(City::Essen);
    player.take_card(City::Essen )
        .take_card(City::Montreal )
        .take_card(City::NewYork  )
        .take_card(City::Paris  )
        .take_card(City::Chicago )
	    .take_card(City::London);
    player.build();
    player.discover_cure(Color::Blue);
    CHECK_THROWS(player.treat(City::Essen));//discover_cure to the blue 

}
///check the diffrent job in players
TEST_CASE("OperationsExpert test - build"){
    Board board;
    OperationsExpert player{board , City::Manila};
    player.take_card(City::Manila);
    CHECK_NOTHROW(player.build());
    CHECK_THROWS(player.build());
    CHECK_NOTHROW(player.fly_charter(City::MexicoCity )); // that mean the OperationExpert build withot throw a city card

    Board board2;
    OperationsExpert player2{board2 , City::Miami};
    player2.take_card(City::Miami);
    CHECK_NOTHROW(player2.build());
    CHECK_THROWS(player2.build());
    CHECK_NOTHROW(player2.fly_charter(City::Milan)); 

    Board board3;
    OperationsExpert player3{board3 , City::Montreal };
    player3.take_card(City::Montreal);
    CHECK_NOTHROW(player3.build());
    CHECK_THROWS(player3.build());
    CHECK_NOTHROW(player3.fly_charter(City::Moscow  )); 

    Board board4;
    OperationsExpert player4{board4 , City::Mumbai };
    player4.take_card(City::Mumbai );
    CHECK_NOTHROW(player4.build());
    CHECK_THROWS(player4.build());
    CHECK_NOTHROW(player4.fly_charter(City::NewYork)); 

}
TEST_CASE("OperationsExpert test - role"){
    Board board;
    OperationsExpert player{board , City::Osaka};
    CHECK_EQ(player.role() , "OperationsExpert");
}

TEST_CASE("Dispatcher test - build"){
    Board board;
    Dispatcher player{board , City::Paris};
    player.take_card(City::Riyadh ).take_card(City::Paris);
    player.build();
    CHECK_NOTHROW(player.fly_direct(City::Riyadh));
    player.build();
    CHECK_NOTHROW(player.fly_direct(City::SanFrancisco));
    CHECK_THROWS(player.fly_direct(City::Santiago));

    Board board2;
    Dispatcher player2{board2 , City::SaoPaulo};
    player.take_card(City::Seoul  ).take_card(City::SaoPaulo );
    player.build();
    CHECK_NOTHROW(player.fly_direct(City::Seoul ));
    player.build();
    CHECK_NOTHROW(player.fly_direct(City::Shanghai ));
    CHECK_THROWS(player.fly_direct(City::StPetersburg ));

    Board board3;
    Dispatcher player3{board3 , City::Sydney };
    player.take_card(City::Taipei).take_card(City::Sydney  );
    player.build();
    CHECK_NOTHROW(player.fly_direct(City::Taipei));
    player.build();
    CHECK_NOTHROW(player.fly_direct(City::Tehran));
    CHECK_THROWS(player.fly_direct(City::Tokyo));


}
TEST_CASE("Dispatcher test - role"){
    Board board;
    OperationsExpert player{board , City::Osaka};
    CHECK_EQ(player.role() , "Dispatcher");
}

TEST_CASE("scientist test - discover_cure"){
    Board board;
    board[City::Cairo] = 3;
    board[City::Karachi] = 1;
    board[City::Mumbai] = 2;
    board[City::Tehran] = 2;
    int n_card = rand()%12;
    Scientist player{board , City::Paris,n_card};
    player.take_card(City::Algiers).take_card(City::Baghdad )
        .take_card(City::Cairo)
        .take_card(City::Chennai)
        .take_card(City::Istanbul)
        .take_card(City::Karachi)
        .take_card(City::Kolkata)
        .take_card(City::Moscow)
        .take_card(City::Mumbai)
        .take_card(City::Riyadh)
        .take_card(City::Tehran)
        .take_card(City::Paris);
    CHECK_THROWS(player.discover_cure(Color::Black));//WE IN CITY THAT DONT HAVE BUILD
    player.build();
    CHECK_NOTHROW(player.discover_cure(Color::Black));//after we build we in city that have reasrch station


    Board board2;
    board2[City::London] = 3;
    board2[City::Paris] = 1;
    board2[City::StPetersburg] = 2;
    board2[City::Santiago] = 2;
    int n_card2 = rand()%12;
    Scientist player2{board2 , City::Santiago ,n_card2};
    player2.take_card(City::Atlanta ).take_card(City::Chicago )
        .take_card(City::Essen )
        .take_card(City::London )
        .take_card(City::Madrid )
        .take_card(City::Milan )
        .take_card(City::Montreal )
        .take_card(City::NewYork )
        .take_card(City::Paris )
        .take_card(City::SanFrancisco )
        .take_card(City::StPetersburg )
        .take_card(City::Washington )
        .take_card(City::Santiago );
    CHECK_THROWS(player2.discover_cure(Color::Blue));//WE IN CITY THAT DONT HAVE BUILD
    player2.build();
    CHECK_NOTHROW(player2.discover_cure(Color::Blue));//after we build we in city that have reasrch station




    Board board3;
    board3[City::Johannesburg] = 3;
    board3[City::MexicoCity] = 1;
    board3[City::SaoPaulo] = 2;
    board3[City::BuenosAires] = 2;
    int n_card3 = rand()%12;
    Scientist player3{board3 , City::Taipei  ,n_card3};
    player3.take_card(City::Bogota  ).take_card(City::BuenosAires  )
        .take_card(City::Johannesburg)
        .take_card(City::Khartoum)
        .take_card(City::Kinshasa)
        .take_card(City::Lima)
        .take_card(City::LosAngeles)
        .take_card(City::MexicoCity)
        .take_card(City::Miami)
        .take_card(City::Santiago)
        .take_card(City::SaoPaulo)
        .take_card(City::Lagos)
        .take_card(City::Taipei);
    CHECK_THROWS(player3.discover_cure(Color::Yellow));//WE IN CITY THAT DONT HAVE BUILD
    player3.build();
    CHECK_NOTHROW(player3.discover_cure(Color::Yellow));//after we build we in city that have reasrch station

    Board board4;
    board4[City::Johannesburg] = 3;
    board4[City::MexicoCity] = 1;
    board4[City::SaoPaulo] = 2;
    board4[City::BuenosAires] = 2;
    int n_card4 = rand()%12;
    Scientist player4{board4 , City::NewYork   ,n_card4};
    player4.take_card(City::Bangkok   ).take_card(City::Beijing   )
        .take_card(City::HoChiMinhCity )
        .take_card(City::HongKong )
        .take_card(City::Jakarta )
        .take_card(City::Manila )
        .take_card(City::Osaka )
        .take_card(City::Seoul )
        .take_card(City::Shanghai )
        .take_card(City::Sydney )
        .take_card(City::Taipei )
        .take_card(City::Tokyo )
        .take_card(City::NewYork );
    CHECK_THROWS(player4.discover_cure(Color::Red));//WE IN CITY THAT DONT HAVE BUILD
    player4.build();
    CHECK_NOTHROW(player4.discover_cure(Color::Red));//after we build we in city that have reasrch station



}
TEST_CASE("Scientist test - role"){
    Board board;
    OperationsExpert player{board , City::Osaka};
    CHECK_EQ(player.role() , "Scientist");
}


TEST_CASE("Dispatcher test - role"){
    Board board;
    OperationsExpert player{board , City::Osaka};
    CHECK_EQ(player.role() , "Dispatcher");
}

TEST_CASE("Researcher test - discover_cure"){
    Board board;
    board[City::Cairo] = 3;
    board[City::Karachi] = 1;
    board[City::Mumbai] = 2;
    board[City::Tehran] = 2;
    Researcher player{board , City::Paris};
    player.take_card(City::Algiers).take_card(City::Baghdad )
        .take_card(City::Cairo)
        .take_card(City::Chennai)
        .take_card(City::Istanbul);
    CHECK_NOTHROW(player.discover_cure(Color::Black));//WE IN CITY THAT DONT HAVE BUILD

    Board board2;
    board2[City::London] = 3;
    board2[City::Paris] = 1;
    board2[City::StPetersburg] = 2;
    board2[City::Santiago] = 2;
    Researcher player2{board2 , City::Santiago};
    player2.take_card(City::Atlanta ).take_card(City::Chicago )
        .take_card(City::Essen )
        .take_card(City::London )
        .take_card(City::Madrid );
    CHECK_NOTHROW(player2.discover_cure(Color::Blue));//Researcher can discover cure at any place he whant

    Board board3;
    board3[City::Johannesburg] = 3;
    board3[City::MexicoCity] = 1;
    board3[City::SaoPaulo] = 2;
    board3[City::BuenosAires] = 2;
    Researcher player3{board3 , City::Taipei};
    player3.take_card(City::Bogota  ).take_card(City::BuenosAires  )
        .take_card(City::Johannesburg)
        .take_card(City::Khartoum)
        .take_card(City::Kinshasa);
    CHECK_NOTHROW(player3.discover_cure(Color::Yellow));

    Board board4;
    board4[City::Johannesburg] = 3;
    board4[City::MexicoCity] = 1;
    board4[City::SaoPaulo] = 2;
    board4[City::BuenosAires] = 2;
    Researcher player4{board4 , City::NewYork   };
    player4.take_card(City::Bangkok   ).take_card(City::Beijing   )
        .take_card(City::HoChiMinhCity )
        .take_card(City::HongKong )
        .take_card(City::Jakarta );
    
    CHECK_NOTHROW(player4.discover_cure(Color::Red));



}
TEST_CASE("Researcher test - role"){
    Board board;
    OperationsExpert player{board , City::Osaka};
    CHECK_EQ(player.role() , "Researcher");
}

//// do medic 

TEST_CASE("Virologist test - treat"){
    Board board;
    board[City::Cairo] = 3;
    board[City::Karachi] = 1;
    board[City::Mumbai] = 2;
    board[City::Tehran] = 2;
    Virologist player{board , City::Santiago};
    player.take_card(City::Karachi).take_card(City::Mumbai )
        .take_card(City::Cairo)
        .take_card(City::Chennai)
        .take_card(City::Tehran);
    CHECK_NOTHROW(player.treat(City::Cairo));
    CHECK_EQ(board[City::Cairo] , 2);
    CHECK_NOTHROW(player.treat(City::Karachi));
    CHECK_EQ(board[City::Karachi] , 0);
    CHECK_NOTHROW(player.treat(City::Mumbai));
    CHECK_EQ(board[City::Mumbai] , 1);
    CHECK_NOTHROW(player.treat(City::Tehran));
    CHECK_EQ(board[City::Tehran] , 1);

}
TEST_CASE("Virologist test - role"){
    Board board;
    OperationsExpert player{board , City::Osaka};
    CHECK_EQ(player.role() , "Virologist");
}
TEST_CASE("GeneSplicer test - discover_cure"){
    Board board;
    board[City::Cairo] = 3;
    board[City::Karachi] = 1;
    board[City::Mumbai] = 2;
    board[City::Tehran] = 2;
    GeneSplicer player{board , City::Paris};
    player.take_card(City::Algiers).take_card(City::Baghdad )
        .take_card(City::Cairo)
        .take_card(City::Chennai)
        .take_card(City::Istanbul)
        .take_card(City::Paris);
    CHECK_THROWS(player.discover_cure(Color::Blue));//we dont have build
    player.build();
    CHECK_NOTHROW(player.discover_cure(Color::Blue));//hava build and we can find cure blue with black cards

    Board board2;
    board2[City::London] = 3;
    board2[City::Paris] = 1;
    board2[City::StPetersburg] = 2;
    board2[City::Santiago] = 2;
    GeneSplicer player2{board2 , City::Santiago};
    player2.take_card(City::Atlanta ).take_card(City::Chicago )
        .take_card(City::Essen )
        .take_card(City::London )
        .take_card(City::Madrid )
        .take_card(City::Santiago);
    CHECK_THROWS(player2.discover_cure(Color::Black));// try to find cure to black with 5 blue cards - but ther isnt build
    player2.build();
    CHECK_NOTHROW(player.discover_cure(Color::Black));//hava build and we can find cure bleck with blue cards

    Board board3;
    board3[City::Johannesburg] = 3;
    board3[City::MexicoCity] = 1;
    board3[City::SaoPaulo] = 2;
    board3[City::BuenosAires] = 2;
    GeneSplicer player3{board3 , City::Taipei};
    player3.take_card(City::Bogota  ).take_card(City::BuenosAires  )
        .take_card(City::Johannesburg)
        .take_card(City::Khartoum)
        .take_card(City::Kinshasa)
        .take_card(City::Taipei);
    CHECK_THROWS(player3.discover_cure(Color::Red));// try to find cure to red with 5 yellow cards - but ther isnt build
    player3.build();
    CHECK_NOTHROW(player3.discover_cure(Color::Red));//hava build and we can find cure red with yellow cards

    Board board4;
    board4[City::Johannesburg] = 3;
    board4[City::MexicoCity] = 1;
    board4[City::SaoPaulo] = 2;
    board4[City::BuenosAires] = 2;
    GeneSplicer player4{board4 , City::NewYork};
    player4.take_card(City::Bangkok   ).take_card(City::Beijing   )
        .take_card(City::HoChiMinhCity )
        .take_card(City::HongKong )
        .take_card(City::Jakarta )
        .take_card(City::NewYork );
    
    CHECK_THROWS(player4.discover_cure(Color::Yellow)); // try to find cure to yellow with 5 red cards - but ther isnt build
    player4.build();
    CHECK_NOTHROW(player4.discover_cure(Color::Yellow));//hava build and we can find cure yellow with red cards
}
TEST_CASE("GeneSplicer test - role"){
    Board board;
    OperationsExpert player{board , City::Osaka};
    CHECK_EQ(player.role() , "GeneSplicer");
}



TEST_CASE("FieldDoctor test - treat"){
    Board board;
    board[City::Tehran ] = 3;
    board[City::Istanbul ] = 3;
    board[City::Cairo ] = 3;
    board[City::Karachi] = 3;
    board[City::Baghdad] = 3;
    int sum = 3;
    FieldDoctor player{board , City::Baghdad };
    for(int i = 0 ; i < 3 ;i++){
        player.treat(City::Tehran );
        CHECK_EQ(board[City::Tehran] , sum);
        player.treat(City::Istanbul );
        CHECK_EQ(board[City::Istanbul] , sum);
        player.treat(City::Cairo );
        CHECK_EQ(board[City::Cairo] , sum);
        player.treat(City::Karachi );
        CHECK_EQ(board[City::Karachi] , sum);
        player.treat(City::Baghdad );
        CHECK_EQ(board[City::Baghdad] , sum);
        sum--;
    }

    Board board2;
    board2[City::Madrid ] = 3;
    board2[City::London  ] = 3;
    board2[City::Washington  ] = 3;
    board2[City::Montreal ] = 3;
    board2[City::NewYork] = 3;
    sum = 3;
    FieldDoctor player2{board2 , City::NewYork  };
    for(int i = 0 ; i < 3 ;i++){
        player2.treat(City::Montreal);
        CHECK_EQ(board2[City::Montreal] , sum);
        player2.treat(City::Washington);
        CHECK_EQ(board2[City::Washington ] , sum);
        player2.treat(City::London);
        CHECK_EQ(board2[City::London ] , sum);
        player2.treat(City::Madrid );
        CHECK_EQ(board2[City::Madrid] , sum);
        player2.treat(City::NewYork );
        CHECK_EQ(board2[City::NewYork] , sum);
        sum--;
    }
}
TEST_CASE("FieldDoctor test - role"){
    Board board;
    OperationsExpert player{board , City::Osaka};
    CHECK_EQ(player.role() , "FieldDoctor");
}
