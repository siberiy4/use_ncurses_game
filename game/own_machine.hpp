#pragma once

#include <deque>
#include <ncurses.h>
#include <locale.h>
#include <mutex>
#include <vector>
#include "playerliving.hpp"
namespace own_machine
{
namespace bullet
{
std::deque<std::pair<long, long>> machine_gun;
std::deque<std::pair<long, long>> missile;

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
        bullet::machine_gun.push_back({position.first, position.second - 1});
    }
    void firering() //ミサイル発射
    {
        bullet::missile.push_back({position.first, position.second - 1});
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

void input()
{
    while (players_live::living_player)
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
        else if (ch == 'l')
        {
            own.firering();
        }
    }
}

} // namespace own_machine
