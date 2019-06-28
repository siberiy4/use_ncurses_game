#include <utility>
#include <deque>
#include <ncurses.h>
#include <locale.h>

namespace own_machine
{
namespace bullet
{
std::deque<std::pair<long, long>> machine_gun;
std::deque<std::pair<long, long>> missile;

} // namespace bullet

std::deque<int> input_char;
bool living_player = true;

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
    /*
    OWN_MACHINE(long x, long y) : life(1), machine_gun(1), missile(1)
    {
        position.first = x;
        position.second = y;
    }
*/
    void sweeping() //機銃を撃つ
    {
        bullet::machine_gun.push_back({position.first, position.second});
    }
    void firering() //ミサイル発射
    {
        bullet::missile.push_back({position.first, position.second});
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
            else if (position.first > screen.first)
            {
                position.first = screen.first - 1;
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
OWN_MACHINE own;

void players_move()
{
    initscr();
    // start_color();
    crmode();
    noecho();
    curs_set(0);
    int ch;

    long ox, oy;

    getmaxyx(stdscr, oy, ox);
    own.position = {ox / 2, oy * 3 / 4};
    mvprintw(own.position.second, own.position.first, "A");
    refresh();

    while (1)
    {
        ch = input_char.front();
        if (ch == 'w')
        {
            own.move_machine(1);
            input_char.pop_front();
        }
        else if (ch == 'd')
        {
            own.move_machine(2);
            input_char.pop_front();
        }
        else if (ch == 's')
        {
            own.move_machine(3);
            input_char.pop_front();
        }
        else if (ch == 'a')
        {
            own.move_machine(0);
            input_char.pop_front();
        }
        clear();
        mvaddch(own.position.second, own.position.first, 'A');
        refresh();
    }

    endwin();
}

void players_attack()
{

    initscr();
    crmode();
    noecho();
    curs_set(0);
    int ch;

    while (living_player)
    {
        ch = input_char.front();
        if (ch == 'm')
        {
            own.sweeping();
            input_char.pop_front();
        }
        else if (ch == 'l')
        {
            own.firering();
            input_char.pop_front();
        }
        clear();
        for (auto &x : bullet::machine_gun)
        {
            mvaddch(x.second, x.first, '|');
        }
        for (auto &x : bullet::missile)
        {
            mvaddch(x.second, x.first, '!');
        }
        refresh();
    }

    endwin();
}

void input(){
    while (living_player)
    {
        int ch = getch();
        input_char.push_back(ch);
    }
}

} // namespace own_machine
