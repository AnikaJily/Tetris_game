
#include "tetris.h"
#include "backend.h"
#include "frontend.h"

int main() {
    
    int c;
    WinBlocks winGame;
    SetUp(&winGame);
    
    GameInfo_t gameInfo;
    Constructor(&gameInfo);
    srand((unsigned)time(NULL));
    createNextFigure(&gameInfo);


 do
    {
    clear_field(&gameInfo);

        if (c == KEY_UP ) printw("%d", isRotatable(&gameInfo));
        else if (c == KEY_DOWN ) {
            int MoveResult = Move(&gameInfo, 0, 1);
            if (MoveResult == 300 || MoveResult == 200) {
                printw("%d",MoveResult);
                gameInfo.next_figure.id = 8;

                createNextFigure(&gameInfo);
            }
        }
        else if (c == KEY_LEFT ) Move(&gameInfo, -1, 0);
        else if (c == KEY_RIGHT ) Move(&gameInfo, 1, 0);

        FigureOnBoard(&gameInfo);

        werase(winGame.winBoard);
        draw_game(gameInfo, winGame);
        box(winGame.winBoard, 0, 0);
        
        wrefresh(winGame.winBoard);
    } while ((c = getch()) != 27); //27 - ASCII code for ESC
    
    getch();

    endwin();

    return 0;
}