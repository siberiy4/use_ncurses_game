#include <ncurses.h>
#include "own_machine.hpp"
#include <locale.h>
#include <thread>
#include <iostream>

void draw_all()
{
    long ox, oy;

    getmaxyx(stdscr, oy, ox);
    own_machine::own.position = {ox / 2, oy * 3 / 4};
    while (own_machine::living_player)
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

        refresh();
    }
}

void main_game()
{
    try
    {
        std::thread th_a(own_machine::players_move);
        std::thread th_b(own_machine::players_attack);
        std::thread th_c(own_machine::input);
        std::thread th_d(draw_all);
        th_a.join();
        th_b.join();
        th_c.join();
        th_d.join();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    //endwin();
}
