#include <ncurses.h>
#include <fstream>
#include <string>
#include <vector>

void how_to_play()
{
    clear();
    int x, y;
    getmaxyx(stdscr, y, x);
    std::ifstream ifs("./menu/key_map");

    if (ifs.fail())
    {
        mvprintw(y / 2, x / 2, "%s", "Failed to open file.");
    }
    else
    {
        int i = 0;
        std::string str;
        std::vector<std::string> vec{"front: ", "back:", "right: ", "left: ", "fire: "};
        while (getline(ifs, str))
        {
            mvprintw(y / 2 - 4 + i * 2, x / 2 - 2, vec[i].c_str());
            mvprintw(y / 2 - 4 + i * 2, x / 2 + 6, str.c_str());
            i++;
        }
    }

    mvprintw(y / 2 + 7, x / 2, "%s", "BACK HOME(PUSH q)");
    refresh;
    int ch;
    while (ch = getch())
    {
        if (ch == 'q')
            break;
    }
}