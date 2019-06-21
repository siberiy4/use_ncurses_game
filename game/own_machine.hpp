#include <utility>
#include <deque>
#include <ncurses.h>
namespace own_machine
{
namespace bullet
{
std::deque<std::pair<long, long>> machine_gun;
std::deque<std::pair<long, long>> missile;

} // namespace bullet

class OWN_MACHINE
{
    int life = 1;        //残機
    int machine_gun = 1; //機銃の威力
    int missile = 1;     //ミサイルの威力

    std::pair<long, long> position;

    OWN_MACHINE(long x, long y)
    {
        position.first = x;
        position.second = y;
    }

    void sweeping() //機銃を撃つ
    {
        bullet::machine_gun.push_back({position.first, position.second});
    }
    void firering() //ミサイル発射
    {
        bullet::missile.push_back({position.first, position.second});
    }
    
    void move_machine(int direct,T solved)
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
        else if (direct == 3)//3なら下へ
        {
            if (position.second < screen.second - 1)
            {
                position.second++;
            }
        }
        else//0なら左へ
        {
            if (position.first > 0)
            {
                position.first--;
            }
        }
    }
};

OWN_MACHINE mine;

} // namespace own_machine
