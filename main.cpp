#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>

// ===== GLOBALS =====
int nrows = 15;
int ncols = 60;

int x, y; // head

int fruitX, fruitY;
int score;

bool gameOver = false;

// Tail system
int tailX[100], tailY[100];
int tailLength = 0;

enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
Direction dir;

// ===== SETUP =====
void Setup() {
    x = ncols / 2;
    y = nrows / 2;

    srand(time(0));
    fruitX = rand() % ncols;
    fruitY = rand() % nrows;

    score = 0;
    dir = STOP;
}

// ===== DRAW =====
void Draw() {
    system("cls");

    for (int i = 0; i < ncols + 2; i++)
        std::cout << "#";
    std::cout << std::endl;

    for (int i = 0; i < nrows; i++) {
        for (int j = 0; j < ncols; j++) {

            if (j == 0) std::cout << "#";

            if (i == y && j == x)
                std::cout << "O"; // head
            else if (i == fruitY && j == fruitX)
                std::cout << "F"; // fruit
            else {
                bool printTail = false;

                for (int k = 0; k < tailLength; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        std::cout << "o"; // tail
                        printTail = true;
                    }
                }

                if (!printTail)
                    std::cout << " ";
            }

            if (j == ncols - 1) std::cout << "#";
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < ncols + 2; i++)
        std::cout << "#";
    std::cout << std::endl;

    std::cout << "Score: " << score << std::endl;
}

// ===== INPUT =====
void Input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a':
                if (dir != RIGHT) dir = LEFT;
                break;
            case 'd':
                if (dir != LEFT) dir = RIGHT;
                break;
            case 'w':
                if (dir != DOWN) dir = UP;
                break;
            case 's':
                if (dir != UP) dir = DOWN;
                break;
            case 'x':
                gameOver = true;
                break;
        }
    }
}

// ===== LOGIC =====
void Logic() {

    // 🐍 MOVE TAIL (SHIFT SYSTEM)
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;

    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < tailLength; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];

        tailX[i] = prevX;
        tailY[i] = prevY;

        prevX = prev2X;
        prevY = prev2Y;
    }

    // MOVE HEAD
    switch (dir) {
        case LEFT:  x--; break;
        case RIGHT: x++; break;
        case UP:    y--; break;
        case DOWN:  y++; break;
        default: break;
    }

    // WALL COLLISION
    if (x < 0 || x >= ncols || y < 0 || y >= nrows)
        gameOver = true;

    // SELF COLLISION
    for (int i = 0; i < tailLength; i++) {
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;
    }

    // FRUIT EATEN
    if (x == fruitX && y == fruitY) {
        score += 10;

        fruitX = rand() % ncols;
        fruitY = rand() % nrows;

        tailLength++; // 🔥 GROW
    }
}

// ===== MAIN =====
int main() {
    Setup();

    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(100);
    }

    std::cout << "Game Over!" << std::endl;
    return 0;
}
