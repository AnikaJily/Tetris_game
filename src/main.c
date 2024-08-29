#include <stdio.h>
#include "defines.h"
#include "ncurses.h"
#include <string.h>

#define HEIGHT 20

#define WIDTH 20


#define ACS_ULCORNER	NCURSES_ACS('l') /* upper left corner */
#define ACS_LLCORNER	NCURSES_ACS('m') /* lower left corner */
#define ACS_URCORNER	NCURSES_ACS('k') /* upper right corner */
#define ACS_LRCORNER	NCURSES_ACS('j') /* lower right corner */

void print_rectangle(int top_y, int bottom_y, int left_x, int right_x)
{
    MVADDCH(top_y, left_x, ACS_ULCORNER);

    int i = left_x + 1;

    for (;i < right_x; i++)
        MVADDCH(top_y, i, ACS_HLINE);
    MVADDCH(top_y, i, ACS_URCORNER);

    for (int i = top_y + 1; i < bottom_y; i++)
    {
        MVADDCH(i, left_x, ACS_VLINE);
        MVADDCH(i, right_x, ACS_VLINE);
    }

    MVADDCH(bottom_y, left_x, ACS_LLCORNER);
    i = left_x + 1;
    for (;i < right_x; i++)
        MVADDCH(bottom_y, i, ACS_HLINE);
    MVADDCH(bottom_y, i, ACS_LRCORNER);
}

int main(){
    initscr();
    curs_set(0);
    print_rectangle(0, HEIGHT, 0, WIDTH);
     getch();  
    endwin();

    return SUCCESS;

}




// int main()
// {
//     initscr();
//     //Выводим сообщение в центре окна stdscr
//     print_rectangle(0, HEIGHT, 0, WIDTH);


//     getch();    
//     endwin();
//     return 0;
// }