#pragma once

#include <ncurses.h>
#include "own_machine.hpp"
#include "enemies.hpp"
#include <locale.h>
#include <thread>
#include <iostream>

void draw_all()
{
    getmaxyx(stdscr, players_live::window_size.second, players_live::window_size.first);
    own_machine::own.position = {players_live::window_size.first / 2, players_live::window_size.second * 3 / 4};
    while (players_live::living_player)
    {
        clear();
        mvaddch(own_machine::own.position.second, own_machine::own.position.first, 'A');
        for (auto &x : own_machine::bullet::machine_gun)
        {
            mvaddch(x.second, x.first, '|');
        }
        for (auto &x : own_machine::bullet::missile)
        {
            mvaddch(x.second, x.first, '\\');
        }

	{
	std::lock_guard<std::mutex> lock(enemy::E.mtx);
	for(auto &x:enemy::E.sky_enemyes)
		          { 
	mvaddch(x.position.second, x.position.first, '?');
        }
	}
        refresh();

    }
}

void move_all_bullet()
{
    using namespace own_machine::bullet;

    while (players_live::living_player)
    {

        for (auto itr = machine_gun.begin(); itr != machine_gun.end(); ++itr)
        {

            (*itr).second--;
            /*if ((*itr).second == 0)
            {
                machine_gun.erase(itr);
            }*/
        }
        for (auto itr = missile.begin(); itr != missile.end(); ++itr)
        {
            (*itr).second--;
            /*if ((*itr).second == 0)
            {
                missile.erase(itr);
            }*/
        }
        usleep(150000);
    }
}

void check_live()
{
    while (players_live::living_player)
    {
        for (auto &x : enemy::E.sky_enemyes)
        {
            if (x.position == own_machine::own.position)
            {
                players_live::living_player = false;
                break;
            }
        }


	std::lock_guard<std::mutex> lock(enemy::E.mtx);
	for(auto itr=enemy::E.sky_enemyes.begin();itr!=enemy::E.sky_enemyes.end();++itr  ){
		for(auto &x : own_machine::bullet::machine_gun){
			if((*itr).position==x){
				enemy::E.sky_enemyes.erase(itr);
		}
	}
    }
}
}

void main_game()
{
    try
    {
        std::thread th_d(draw_all);
        std::thread th_a(move_all_bullet);
        std::thread th_e(check_live);
        std::thread th_b(enemy::enemys_ecology);
        std::thread th_c(own_machine::input);

        th_d.join();
        th_e.join();
        th_a.join();
        th_b.join();
        th_c.join();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    //endwin();
}
