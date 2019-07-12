#pragma once

#include <deque>
#include <ncurses.h>
#include <unistd.h>
#include <random>
#include "playerliving.hpp"
#include <unistd.h>
using namespace players_live;
namespace enemy
{
namespace bullet
{
std::deque<std::pair<long, long>> enemy_attack;
}
class ENEMY
{
public:
    int life = 1;         //HP
    int machine_gun = 1;  //攻撃の威力
    bool category = true; //敵種 0:地上1:空
    bool from = true;     //0:左から出現１：右から出現

    std::pair<long, long> position;

    ENEMY(long x, long y, bool cate, bool f)
    {
        position.first = x;
        position.second = y;
        category = cate;
        from = f;
    }

    void firering() //ミサイル発射
    {
        bullet::enemy_attack.push_back({position.first, position.second});
    }

    void move_machine(int direct)
    {

        getmaxyx(stdscr, window_size.second, window_size.first);

        if (direct == 1)
        { //1なら上へ
            if (position.second > 0)
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
            if (position.first > 0)
            {
                position.first--;
            }
        }
    }
};

std::deque<ENEMY> sky_enemyes;
std::deque<ENEMY> land_enemyes;
std::random_device rnd;

void make_enemy(int count)
{

    getmaxyx(stdscr, window_size.second, window_size.first);

    for (int m = 0; m < count; m++)
    {
        for (long i = 0; i < 2; i++)
        {
            if (rnd() % 10 < 8)
            { //空
                ENEMY tmp((window_size.first * (i + 1) / 3), 0, bool(1), bool(i));
                sky_enemyes.push_back(tmp);
            }
            if (rnd() % 10 < 8)
            { //地上
                ENEMY tmp((window_size.first * i), long(window_size.second / 3), bool(0), bool(i));
                land_enemyes.push_back(tmp);
            }
        }
    }
}
void move_enemy()
{
    for (long i = 0; i < sky_enemyes.size(); i++)
    {
        int m = rnd() % 3;
        if (m == 0)
        {
            sky_enemyes[i].position.first--;
        }
        else if (m == 1)
        {
            sky_enemyes[i].position.first++;
        }
        else
        {
            sky_enemyes[i].position.second++;
        }
        if (sky_enemyes[i].position.second >= window_size.second - 1)
        {
            sky_enemyes.erase(sky_enemyes.begin() + i);
        }
        else if (sky_enemyes[i].position.first >= window_size.first - 1)
        {
            sky_enemyes.erase(sky_enemyes.begin() + i);
        }
        else if (sky_enemyes[i].position.first <= 1)
        {
            sky_enemyes.erase(sky_enemyes.begin() + i);
        }
    }

    for (long i = 0; i < land_enemyes.size(); i++)
    {
        int m = rnd() % 3;
        if (m == 0)
        {
            land_enemyes[i].position.first--;
        }
        else if (!land_enemyes[i].from)
        {
            land_enemyes[i].position.first++;
        }
        else
        {
            land_enemyes[i].position.second++;
        }
        if (land_enemyes[i].position.second >= window_size.second - 1)
        {
            land_enemyes.erase(land_enemyes.begin() + i);
        }
        else if (land_enemyes[i].position.first >= window_size.first - 1)
        {
            land_enemyes.erase(land_enemyes.begin() + i);
        }
        else if (land_enemyes[i].position.first <= 1)
        {
            land_enemyes.erase(land_enemyes.begin() + i);
        }
    }
}

void enemys_ecology()
{

    int i = 0;

    while (living_player)
    {
        if (i % 37 == 0)
        {
            make_enemy(8);
        }
        i++;
        move_enemy();

        usleep(100000);
    }
}

} // namespace enemy