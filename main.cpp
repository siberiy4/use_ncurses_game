#include <ncurses.h>
#include <locale.h>
#include <unistd.h>
#include "menu/menu.hpp"
#include "game/main_game.hpp"

int main(int argc, char const *argv[])
{
    int max_x, max_y;

    setlocale(LC_ALL, "");

    initscr();
    start_color();
    curs_set(0);

    while (1)
    {
        menu();
        main_game();
    }

    endwin();

    return 0;
}
