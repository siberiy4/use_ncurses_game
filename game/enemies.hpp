#include <utility>
#include <deque>
#include <ncurses.h>

namespace enemyes
{
namespace bullet
{
std::deque<std::pair<long, long>> enemy_attack;
}
class ENEMY
{
    int life = 1;         //残機
    int machine_gun = 1;  //攻撃の威力
    bool category = true; //敵種　0:地上　1:空
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

std::deque<ENEMY> enemy;

void spawn_enemy()
{
    long x, y;
    getmaxyx(stdscr, y, x);

    for (int i = 0; i < 2; i++)
    {
        for (int k = 0; k < 2; k++)
        {

            ENEMY tmp(x, y, i, k);
        }
    }
}

} // namespace enemyes