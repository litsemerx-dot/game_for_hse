#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define MAX 15 // максимальный размер поля

void print_header(int n) // это нумерует наш массив по столбцам
{
    printf("  ");
    for (int c = 0; c < n; c++){
        printf("%2d ", c + 1);
    }
    printf("\n");
}



void init_board(char board[MAX][MAX], int n) // заполняем поля точками 
{ 
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            board[r][c] = '.';
        }
    }
}



void print_board(char board[MAX][MAX], int n) // здесь печатаются поля
{
    print_header(n);
    for (int r = 0; r < n; r++) {
        printf("%2d", r + 1);

        for (int c = 0; c < n; c++) {
            printf ("%2c ", board[r][c]);
        }
        printf ("\n");
    }
}



// чистит экран в терминале от лишнего
void clear_screen(void) {
    printf("\033[2J\033[H");
}



// проверка победы: считаем одинаковые символы в 4 направлениях
bool check_win(char board[MAX][MAX], int size, int line_to_win, int row, int col, char symbol)
{
    int dr[4] = {0, 1, 1, 1};   // шаг по строке
    int dc[4] = {1, 0, 1, -1};  // шаг по столбцу

    for (int d = 0; d < 4; d++) {
        int count = 1; 

        int r = row + dr[d];
        int c = col + dc[d];
        while (r >= 0 && r < size && c >= 0 && c < size && board[r][c] == symbol) {
            count++;
            r += dr[d];
            c += dc[d];
        }

        r = row - dr[d];
        c = col - dc[d];
        while (r >= 0 && r < size && c >= 0 && c < size && board[r][c] == symbol) {
            count++;
            r -= dr[d];
            c -= dc[d];
        }

        if (count >= line_to_win) {
            return true;
        }
    }
    return false;
}


// main


int main(void){
    int row = 0, col = 0;
    int SIZE = 0, line_to_win = 0, mode = 0;
    char board[MAX][MAX];
    char player1 = 'X';
    char player2 = 'O';
    bool side = true;
    bool won = false;
    
    char human = 'X'; // нужно для режима с ботом
    srand((unsigned)time(NULL));

    // меню

    printf("---------КРЕСТИКИ-НОЛИКИ----------\n");
    printf("\n");

    // параметр: размер поля

    while (true) {
    printf("Введите размер поля (3-%d): ", MAX);

    if (scanf("%d", &SIZE) != 1 || getchar() != '\n') {
        while (getchar() != '\n') { }
        printf("Нужно число\n");
        continue;
    }

    if (SIZE < 3 || SIZE > MAX) {
        printf("Размер должен быть от 3 до %d\n", MAX);
        continue;
    }

    break;
    }

    // параметр: длина победной линии

    while (true) {
    printf("Введите длину победной линии (3-%d): ", SIZE);

    if (scanf("%d", &line_to_win) != 1 || getchar() != '\n') {
        while (getchar() != '\n') { }
        printf("Нужно число\n");
        continue;
    }

    if (line_to_win < 3 || line_to_win > SIZE) {
        printf("Размер должен быть от 3 до %d\n", SIZE);
        continue;
    }

    break;
    }

    // параметр: выбрать бота или два игрока

    while (true) {
    printf("Режим 1 — два игрока, Режим 0 — против бота\n");

    if (scanf("%d", &mode) != 1 || getchar() != '\n') {
        while (getchar() != '\n') { }
        printf("Нужно число 1 или 0\n");
        continue;
    }

    if (mode < 0 || mode > 1) {
        printf("Нужно число 1 или 0\n");
        continue;
    }

    break;
    }

    // параметр: за кого играет человек (только против бота)

    if (mode == 0) {
        while (true) {
            printf("За кого играете? X или O: ");

            if (scanf(" %c", &human) != 1 || getchar() != '\n') {
                while (getchar() != '\n') { }
                printf("Нужна одна буква: X или O\n");
                continue;
            }

            if (human != 'X' && human != 'O') {
              printf("Нужна буква X или O\n");
               continue;
            }

            break;
        }
    }
    
    clear_screen();
    init_board(board, SIZE);
    clear_screen();
    print_board(board, SIZE);
    printf("\n");

    
    
    for (int i = 0; i < SIZE * SIZE; i++){
        char symbol = side ? player1 : player2;
        int number = side ? 1 : 2;

        if (mode == 0 && symbol != human) {
            do {
                row = rand() % SIZE + 1;
                col = rand() % SIZE + 1;
            } 
            while (board[row - 1][col - 1] != '.');
            printf("Бот (%c) ходит: %d %d\n", symbol, row, col);
        } 
        else {
        
            while(true) {
                printf("Игрок %d (%c): Введите строку и столбец: ", number, symbol);
                
                if (scanf("%d %d", &row, &col) != 2 || getchar() != '\n') { // здесь пришлось обращаться в инет, т.к.
                    while (getchar() != '\n') { }                           // была проблема при вводе букв вместо цифр
                    printf("Введите два числа\n");                          // это просто проверка на ЧИСЛА, чтобы не 
                    continue;                                               // сломать прогу
                }
                printf("\n");
                
                // проверяем на логичность ввода пользователя
                if (row < 1 || row > SIZE || col < 1 || col > SIZE) {
                    printf("Вышли за поле, попробуйте ещё раз...\n");
                    continue;
                }
                
                if (board[row - 1][col - 1] != '.') {
                    printf("Клетка занята\n");
                    continue;
                }
                break; 
            }
            }
            board[row - 1][col - 1] = symbol;
            clear_screen();
            print_board(board, SIZE);

            if (check_win(board, SIZE, line_to_win, row - 1, col - 1, symbol)) {
                printf("Игрок %d (%c) победил!\n", number, symbol);
                won = true;
                break;
        }
        
        side = !side;
    }

    if (!won) {
    printf("Ничья!\n");
    }   
    
    return 0;
}

