#pragma once

#include <ncurses.h>
#include "own_machine.hpp"
#include "enemies.hpp"
#include <locale.h>
#include <thread>
#include <iostream>
#include <string>

void draw_all()
{
    getmaxyx(stdscr, players_live::window_size.second, players_live::window_size.first);
    own_machine::own.position = {players_live::window_size.first / 2, players_live::window_size.second * 3 / 4};
    while (players_live::living_player)
    {
        clear();
        mvaddch(own_machine::own.position.second, own_machine::own.position.first, 'A');

        {
            std::lock_guard<std::mutex> lock(own_machine::bullet::B.mtx);
            for (auto &x : own_machine::bullet::B.machine_gun)
            {
                if (x.second >= 1)
                {
                    mvaddch(x.second, x.first, '|');
                }
            }
        }

        {
            std::lock_guard<std::mutex> lock(enemy::E.mtx);
            for (auto &x : enemy::E.sky_enemyes)
            {
                if (x.position.second >= 1)
                {
                    mvaddch(x.position.second, x.position.first, '?');
                }
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

        {
            std::lock_guard<std::mutex> lock(own_machine::bullet::B.mtx);
            for (auto itr = B.machine_gun.begin(); itr != B.machine_gun.end(); ++itr)
            {
                if ((*itr).second > -10)
                {
                    (*itr).second--;
                }
            }
        }
        usleep(100000);
    }
}

void check_live()
{
    while (players_live::living_player)
    {

        {
            std::lock_guard<std::mutex> lock(enemy::E.mtx);

            for (auto &x : enemy::E.sky_enemyes)
            {
                if (x.position == own_machine::own.position)
                {
                    players_live::living_player = false;
                    break;
                }
            }
        }

        for (auto itr = enemy::E.sky_enemyes.begin(); itr != enemy::E.sky_enemyes.end(); ++itr)
        {

            {
                std::lock_guard<std::mutex> lock(own_machine::bullet::B.mtx);
                for (auto &x : own_machine::bullet::B.machine_gun)
                {
                    if ((*itr).position == x)
                    {
                        enemy::E.sky_enemyes.erase(itr);
                        players_live::score++;
                    }
                }
            }
        }
    }
}

void init_game()
{
    players_live::score = 0;
    if (!enemy::E.sky_enemyes.empty())
        enemy::E.sky_enemyes.clear();

    if (!own_machine::bullet::B.machine_gun.empty())
        own_machine::bullet::B.machine_gun.clear();
    players_live::living_player = true;
}

void main_game()
{
    init_game();
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

    clear();
    mvprintw(players_live::window_size.second / 2, players_live::window_size.first / 2 - 2, "%s", "score");
    mvprintw(players_live::window_size.second / 2 + 1, players_live::window_size.first / 2 - 1, "%lld", (players_live::score));
    mvprintw(players_live::window_size.second / 2 + 3, players_live::window_size.first / 2 - 3, "%s", "BACK HOME(PUSH q)");
    refresh();

    int ch;
    while (ch = getch())
    {
        if (ch == 'q')
            break;
    }

}
