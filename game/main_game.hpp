#include <ncurses.h>
#include "own_machine.hpp"
#include <locale.h>
#include <thread>
#include <iostream>

void main_game()
{
    try
    {
        std::thread th_a(own_machine::players_move);
        //      std::thread th_b(own_machine::players_attack);
        std::thread th_c(own_machine::input);

        th_a.join();
        //     th_b.join();
        th_c.join();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    //endwin();
}