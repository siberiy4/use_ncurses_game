#include "menu/menu.hpp"

int main(int argc, char const *argv[])
{

    //setlocale(LC_ALL, "");

    initscr();
    crmode();
    noecho();
    curs_set(0);

    menu();

    endwin();

    return 0;
}
