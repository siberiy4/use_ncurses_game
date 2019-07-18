#pragma once

#include <deque>
#include <ncurses.h>
#include <unistd.h>
#include <random>
#include "playerliving.hpp"
#include <unistd.h>
#include<mutex>
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

struct TEKI{
std::deque<ENEMY> sky_enemyes;
//std::deque<ENEMY> land_enemyes;
std::mutex mtx;
};

TEKI E;
std::random_device rnd;

void make_enemy(int count)
{

    getmaxyx(stdscr, window_size.second, window_size.first);


	std::lock_guard<std::mutex> lock(E.mtx);
    for (int m = 0; m < count; m++)
    {
        for (long i = 0; i < 2; i++)
        {
            if (rnd() % 10 < 8)
            { //空
                ENEMY tmp((window_size.first * (i + 1) / 3), 0, bool(1), bool(i));
                E.sky_enemyes.push_back(tmp);
            }
	}
    }
}
void move_enemy()
{

	std::lock_guard<std::mutex> lock(E.mtx);
   	for (long i = 0; i < E.sky_enemyes.size(); i++)
    {
        int m = rnd() % 3;
        if (m == 0)
        {
            E.sky_enemyes[i].position.first--;
        }
        else if (m == 1)
        {
            E.sky_enemyes[i].position.first++;
        }
        else
        {
            E.sky_enemyes[i].position.second++;
        }
        if (E.sky_enemyes[i].position.second >= window_size.second - 1)
        {
            E.sky_enemyes.erase(E.sky_enemyes.begin() + i);
        }
        else if (E.sky_enemyes[i].position.first >= window_size.first - 1)
        {
            E.sky_enemyes.erase(E.sky_enemyes.begin() + i);
        }
        else if (E.sky_enemyes[i].position.first <= 1)
        {
            E.sky_enemyes.erase(E.sky_enemyes.begin() + i);
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
