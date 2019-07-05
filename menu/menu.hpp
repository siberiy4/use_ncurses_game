#include "menu.h"
#include <ncurses.h>

int coin = 0;

void start_menu();
void how_to_play();
void put_start_guid();

void menu()
{
    int ch = getch();
    while (1)
    {
        if (ch == 's')
        {
            if (coin > 0)
            {
                coin--;
                break;
            }
        }
        else if (ch == 'r')
        {
            coin++;
        }
        else if (ch == 'u')
        {
            how_to();
        }
    }
}



void put_start_guid()
{
    //スタートメニューで表示する文
    int x, y;
    getmaxyx(stdscr, y, x);

    char *start_msg = "コインを入れてスタート(PRESS　S)";
    mvprintw(y / 2, x / 2 - (strlen(start_msg) / 2), "%s", start_msg);

    char *use_msg = "操作法(PRESS　S)";
    mvprintw(y / 2 + 2, x / 2 - (strlen(start_msg) / 2), "%s", use_msg);

    char *coin_msg = "COIN(PRESS R):";
    mvprintw(y -1, x -5- (strlen(coin_msg), "%s%d",( coin_msg,coin));
}