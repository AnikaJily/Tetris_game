
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

    // MoveFigure(&gameInfo);
    // Move(&gameInfo, 0, 3);
    // printw("x Before: %d", gameInfo.next_figure.center_x);
    // printw("y Before: %d", gameInfo.next_figure.center_y);
    // printw("%d",Move(&gameInfo, 0, 10));
    // printw("x After: %d", gameInfo.next_figure.center_x);
    // printw("y After: %d", gameInfo.next_figure.center_y);
    Move(&gameInfo, 0, 6);
    // Move(&gameInfo, 0, 3);
    // // MoveFigure(&gameInfo);
    // // printf("%d ", gameInfo.next_figure.center_x[0]);
    // FigureOnBoard(&gameInfo);
    
    // for (int i = 0; i < BOARD_HEIGHT; i++) {
    //     for (int j = s0; j < BOARD_WIDTH; j++) {
    //         printw("%d ", gameInfo.field[i][j]); // Печатаем значение элемента матрицы
    //     }
    //     printw("\n"); // Переход на новую строку после печати строки матрицы
    // }
    //    for (int i = 0; i < 20; ++i) {
    //     createNextFigure(&gameInfo);
    //     printf("Figure ID: %d\n", gameInfo.next_figure.id);
    // }



 do
    {
    clear_field(&gameInfo);
    // printw("%d",Move(&gameInfo, -1, 0));
    // MoveFigure(&gameInfo);
    // printf("%d ", gameInfo.next_figure.center_x[0]);
        // if (c == KEY_UP ) Move(&gameInfo, 0, -1);
        if (c == KEY_UP ) isRotatable(&gameInfo);
        else if (c == KEY_DOWN ) Move(&gameInfo, 0, 1);
        else if (c == KEY_LEFT ) Move(&gameInfo, -1, 0);
        else if (c == KEY_RIGHT ) Move(&gameInfo, 1, 0);
    FigureOnBoard(&gameInfo);
        werase(winGame.winBoard);
        // Move(&gameInfo, 0, 1);
        // FigureOnBoard(&gameInfo);
        draw_game(gameInfo, winGame);
        box(winGame.winBoard, 0, 0);
       
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