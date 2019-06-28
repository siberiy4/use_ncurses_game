#include <ncurses.h>
#include "own_machine.hpp"
#include <locale.h>

void main_game()
{
    int ch;
    long ox, oy;
    own_machine::OWN_MACHINE own;

    /*
    getmaxyx(stdscr, oy, ox);
    // own.position = {ox * 3 / 4, oy * 3 / 4};
    // own.position = {ox * 3 / 4, oy * 3 / 4};
*/
    mvprintw(own.position.second, own.position.first, "A");

    refresh();

    while (1)
    {
        ch = getch();
        if (ch == 'w')
        {
            own.move_machine(1);
        }
        else if (ch == 'd')
        {
            own.move_machine(2);
        }
        else if (ch == 's')
        {
            own.move_machine(3);
        }
        else if (ch == 'a')
        {
            own.move_machine(0);
        }

        mvaddch(own.position.second, own.position.first, 'A');
        refresh();
    }

    endwin();
}