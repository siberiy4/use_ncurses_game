#pragma once

#include <deque>
#include <ncurses.h>
#include <locale.h>
#include <mutex>
#include <vector>
#include <sys/ioctl.h>
#include <termios.h>

#include "playerliving.hpp"
namespace own_machine
{
	namespace bullet
	{
		struct BULLET{
			std::deque<std::pair<long, long>> machine_gun;
			std::mutex mtx;
		};
		BULLET B;

	} // namespace bullet

class OWN_MACHINE
{
    int life;        //残機
    int machine_gun; //機銃の威力
    int missile;     //ミサイルの威力

public:
    std::pair<long, long> position;
    OWN_MACHINE() : life(1), machine_gun(1), missile(1), position({1, 1})
    {
    }

    void sweeping() //機銃を撃つ
    {
        bullet::B.machine_gun.push_back({position.first, position.second - 1});
    }

void move_machine(int direct)
    {
        using namespace players_live;
        getmaxyx(stdscr, window_size.second, window_size.first);

        if (direct == 1)
        { //1なら上へ
            if (position.second > 1)
            {
                position.second--;
            }
        }
        else if (direct == 2) //２なら右へ
        {
            if (position.first < window_size.first - 1)
            {
                position.first++;
            }
            else if (position.first > window_size.first)
            {
                position.first = window_size.first - 1;
            }
        }
        else if (direct == 3) //3なら下へ
        {
            if (position.second < window_size.second - 1)
            {
                position.second++;
            }
        }
        else //0なら左へ
        {
            if (position.first > 1)
            {
                position.first--;
            }
        }
    }
};
OWN_MACHINE own;

bool kbhit()
{
    termios term;
    tcgetattr(0, &term);

    termios term2 = term;
    term2.c_lflag &= ~ICANON;
    tcsetattr(0, TCSANOW, &term2);

    int byteswaiting;
    ioctl(0, FIONREAD, &byteswaiting);

    tcsetattr(0, TCSANOW, &term);

    return byteswaiting > 0;
}

void input()
{
    while (players_live::living_player)
    {
        if (kbhit())
        {
            int ch = getch();

            bool check = false;
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
            else if (ch == 'm')
            {
                own.sweeping();
            }
        }
    }
}

} // namespace own_machine
