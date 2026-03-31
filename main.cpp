#include <iostream>
#include <vector>
#include <conio.h>   // for _kbhit(), _getch()
#include <windows.h> // for Sleep()

int nrows = 15;
int ncols = 60;

int x, y; // snake head position

bool gameOver = false;

enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
Direction dir;

void Setup() {
    x = ncols / 2;
    y = nrows / 2;
    dir = STOP;
}

void Draw() {
    system("cls");

    // Top wall
    for (int i = 0; i < ncols + 2; i++)
        std::cout << "#";
    std::cout << std::endl;

    // Map
    for (int i = 0; i < nrows; i++) {
        for (int j = 0; j < ncols; j++) {

            if (j == 0) std::cout << "#";

            if (i == y && j == x)
                std::cout << "O"; // Snake head
            else
                std::cout << " ";

            if (j == ncols - 1) std::cout << "#";
        }
        std::cout << std::endl;
    }

    // Bottom wall
    for (int i = 0; i < ncols + 2; i++)
        std::cout << "#";
    std::cout << std::endl;
}

// ===== INPUT (PHYSICS LEAD) =====
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

void Logic() {
    switch (dir) {
        case LEFT:  x--; break;
        case RIGHT: x++; break;
        case UP:    y--; break;
        case DOWN:  y++; break;
        default: break;
    }

    // Wall collision
    if (x < 0 || x >= ncols || y < 0 || y >= nrows) {
        gameOver = true;
    }
}

int main() {
    Setup();

    while (!gameOver) {
        Draw();   // UI
        Input();  // Physics Lead
        Logic();  // Physics Lead
        Sleep(100);
    }

    std::cout << "Game Over!" << std::endl;
    return 0;
}
