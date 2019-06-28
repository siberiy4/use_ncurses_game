//#include "menu/menu.hpp"
#include "game/main_game.hpp"

int main(int argc, char const *argv[])
{
    int max_x, max_y;

    setlocale(LC_ALL, "");

    initscr();
    // start_color();
    crmode();
    noecho();
    curs_set(0);

    main_game();

    /*
    while (1)
    {
        menu();
        main_game();
    }
*/
    endwin();

    return 0;
}
