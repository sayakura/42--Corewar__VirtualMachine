#include "vm.h"

char     update_screen(t_gui *gui)
{
    usleep(15000);
    clear();
    wrefresh(gui->win);
    return (wgetch(gui->win));
}

void            end_screen(void)
{
    endwin();
}

static void     fill_map(t_gui *gui)
{
    int x;
    int y;

    x = -2;
    y = 1;

    while (y != MAX_Y - 1)
    {
       if (x == MAX_X - 3)
        {
            x = -2;
            y++;
        }
        else { 
        x += 3;
        mvwprintw(gui->win, y, x, "00 ");
        }
    }
}

void            init_screen(t_gui *gui)
{
    initscr();
    start_color();
    cbreak();
    noecho();
    curs_set(0);
    gui->win = newwin(MAX_Y, MAX_X + 1, 1, 1);
    nodelay(gui->win, true);
    box(gui->win, 0, 0);
    keypad(gui->win, true);
  //  fill_map(gui);
}