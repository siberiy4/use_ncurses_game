#include <utility>
#include <deque>
#include <ncurses.h>
#include <unistd.h>
#include <random>
#include "playerliving.hpp"
#include <unistd.h>
namespace enemy
{
namespace bullet
{
std::deque<std::pair<long, long>> enemy_attack;
}
class ENEMY
{
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
        std::pair<long, long> screen;
        getmaxyx(stdscr, screen.second, screen.first);

        if (direct == 1)
        { //1なら上へ
            if (position.second > 0)
            {
                position.second--;
            }
        }
        else if (direct == 2) //２なら右へ
        {
            if (position.first < screen.first - 1)
            {
                position.first++;
            }
        }
        else if (direct == 3) //3なら下へ
        {
            if (position.second < screen.second - 1)
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
    long x, y;
    getmaxyx(stdscr, y, x);

    for (int m = 0; m < count; m++)
    {
        for (int i = 0; i < 2; i++)
        {
            if (rnd() % 10 < 8)
            { //空
                ENEMY tmp(long(x * (i + 1) / 3), 0, bool(1), bool(i));
                sky_enemyes.push_back(tmp);
            }
            if (rnd() % 10 < 8)
            { //地上
                ENEMY tmp(long(x * i), long(y / 3), bool(0), bool(i));
                land_enemyes.push_back(tmp);
            }
        }
    }
}
void move_enemy()
{
    for (long i = 0; i < sky_enemyes.size(); i++)
    {
        int m = rnd % 3;
        if (m == 0)
        {
            sky_enemyes[i].posision.first--;
        }
        else if (m == 1)
        {
            sky_enemyes[i].posision.first++;
        }
        else
        {
            sky_enemyes[i].posision.second++;
        }
        if (sky_enemyes[i].posision.second >= players_live::windowsize.second - 1)
        {
            sky_enemyes.erase(sky_enemyes.begin() + i);
        }
        else if (sky_enemyes[i].posision.first >= players_live::windowsize.first - 1)
        {
            sky_enemyes.erase(sky_enemyes.begin() + i);
        }
        else if (sky_enemyes[i].posision.first <= 1)
        {
            sky_enemyes.erase(sky_enemyes.begin() + i);
        }
    }

    for (long i = 0; i < land_enemyes.size(); i++)
    {
        int m = rnd % 3;
        if (m == 0)
        {
            land_enemyes[i].posision.first--;
        }
        else if (!land_enemyes[i].from)
        {
            land_enemyes[i].posision.first++;
        }
        else
        {
            land_enemyes[i].posision.second++;
        }
        if (land_enemyes[i].posision.second >= players_live::windowsize.second - 1)
        {
            land_enemyes.erase(land_enemyes.begin() + i);
        }
        else if (land_enemyes[i].posision.first >= players_live::windowsize.first - 1)
        {
            land_enemyes.erase(land_enemyes.begin() + i);
        }
        else if (land_enemyes[i].posision.first <= 1)
        {
            land_enemyes.erase(land_enemyes.begin() + i);
        }
    }
}

void enemys_ecology()
{
    while (players_live::living_player)
    {
        make_enemy(2);
        move_enemy();

        usleep(1000000);
    }
}

} // namespace enemy