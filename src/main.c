
#include "tetris.h"
#include "backend.h"
#include "frontend.h"

int main() {
    int c;
    WinBlocks winGame;
    SetUp(&winGame);
    GameInfo_t gameInfo;
    Constructor(&gameInfo);
    createNextFigure(&gameInfo);

    MoveFigure(&gameInfo);
    // printf("%d ", gameInfo.next_figure.center_x[0]);
    FigureOnBoard(&gameInfo);
    
    // for (int i = 0; i < BOARD_HEIGHT; i++) {
    //     for (int j = 0; j < BOARD_WIDTH; j++) {
    //         printw("%d ", gameInfo.field[i][j]); // Печатаем значение элемента матрицы
    //     }
    //     printw("\n"); // Переход на новую строку после печати строки матрицы
    // }
   


 do
    {
        werase(winGame.winBoard);
        draw_game(gameInfo, winGame);
        box(winGame.winBoard, 0, 0);
        // if (c == KEY_UP ) y--;
        // else if (c == KEY_DOWN ) y++;
        // else if (c == KEY_LEFT ) x--;
        // else if (c == KEY_RIGHT ) x++;
        // mvwprintw(winGame.winBoard, y, x, "@");
        wrefresh(winGame.winBoard);
    } while ((c = getch()) != 27); //27 - ASCII code for ESC
    
    getch();

    endwin();

    

    /*
    setup();
    GameInfo_t gameInfo = [];
    game_loop(gameInfo);{

        draw(gameInfo); {
            draw_field(gameInfo);
            draw_score(gameInfo);
            draw_record(gameInfo);
            draw_level(gameInfo);
        }
        logic(gameInfo);{
            

            move(gameInfo);
            rotate(gameInfo);

        }

    }

    
    */





    // Figure_t *figure = get_figure();
    // print_figure(figure, winGame.winNext);
    //map[][]
    //score
   


    
    //очистка памяти

    return 0;
}