#include <ncurses.h>
#include"../game/main_game.hpp"
#include"./how_to_play.hpp"
#include<cstring>

void start_menu();

void put_start_guide();

void menu()
{
    int ch ;
	
   	 put_start_guide();
    while(ch=getch()){
        if (ch == 's')
        {
		main_game();
        }
        else if (ch == 'h')
        {
            how_to_play();
        }else if(ch=='q'){
		break;
	}
   	 put_start_guide();
    }
}



void put_start_guide()
{
    //スタートメニューで表示する文
    int x, y;
    getmaxyx(stdscr, y, x);
	clear();
	std::string start_msg = "GAME_START(PRESS_s)";
    mvprintw(y / 2, x / 2 - (start_msg.size() / 2),  start_msg.c_str() );

    std::string use_msg = "HOW_TO_PLAY(PRESS_h)";
    mvprintw(y / 2 + 2, x / 2 - (start_msg.size() / 2),  use_msg.c_str());

    std::string  quit_msg = "EXIT_GAME(PRESS_q)";
    mvprintw(y / 2 + 6, x / 2 - (quit_msg.size() / 2),  quit_msg.c_str());
    
    std::string game_name = "XEBIOUS";
    mvprintw(y /4, x/2- (game_name.size()/2),  game_name.c_str());

	refresh();
}
