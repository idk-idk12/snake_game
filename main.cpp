#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>

using namespace std;

bool gameOver;
const int width = 20;
const int height = 20;
int x, y, headX, headY, fruitX, fruitY, score;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

vector<int> tailX, tailY;
int nTail;

bool find_(int currX, int currY) {
    for (int i = 0; i < tailX.size(); i++) {
        if (tailX.at(i) == currX && tailY.at(i) == currY) {
            return true;
        }
    }
    return false;
}

bool check_if_snake_ate_itself() {
    for (int i = 1; i < tailX.size(); i++) {
        if (tailX.at(0) == tailX.at(i) && tailY.at(0) == tailY.at(i)) {
            return true;
        }
    }
    return false;
}

void Setup() {
    std::srand(std::time(0));

    gameOver = false;
    dir = STOP;

    headX = width / 2;
    headY = height / 2;

    fruitX = rand() % width;
    fruitY = rand() % height;

    score = 0;

    tailX.push_back(headX);
    tailY.push_back(headY);
}

void Draw() {
    system("cls");

    std::cout << "#";
    for (x = 0; x < width; x++) {
        std::cout << "#";
    }
    std::cout << "#" << std::endl;
    for (y = 0; y < height; y++) {
        std::cout << "#";
        for (x = 0; x < width; x++) {
            if (x == fruitX && y == fruitY) {
                std::cout << "F";
            }
            else if (find_(x, y)) {
                std::cout << "O";
            }
            else {
                std::cout << " ";
            }
        }
        std::cout << "#" << std::endl;
    }
    std::cout << "#";
    for (x = 0; x < width; x++) {
        std::cout << "#";
    }
    std::cout << "#" << std::endl;

    cout << "Score: " << score << endl;
}

void Input() {
    // Physics Lead: Handle key presses (W, A, S, D)
    if (_kbhit()) {
        switch (_getch()) {
        case 'a': dir = LEFT; break;
        case 'd': dir = RIGHT; break;
        case 'w': dir = UP; break;
        case 's': dir = DOWN; break;
        case 'x': gameOver = true; break;
        }
    }
}

void Logic() {
    if (tailX.at(0) == fruitX && tailY.at(0) == fruitY) {
        score += 1;
        // Adds to snake's tail
        tailX.push_back(tailX.back());
        tailY.push_back(tailY.back());
        int final_idx = tailX.size()-1;
        switch (dir) {
            case UP:
                tailY.at(final_idx) -= 1;
                break;
            case DOWN:
                tailY.at(final_idx) += 1;
                break;
            case LEFT:
                tailX.at(final_idx) -= 1;
                break;
            case RIGHT:
                tailX.at(final_idx) += 1;
                break;
        }
        // Resets fruit location
        fruitX = rand() % width;
        fruitY = rand() % height;
    }

    // Updates all other positions
    if (tailX.size() > 1) {
        for (int i = tailX.size()-1; i > 0; i--) {
            tailX.at(i) = tailX.at(i-1);
            tailY.at(i) = tailY.at(i-1);
        }
    }

    // Updates head direction
    switch (dir) {
        case UP:
            tailY.at(0) -= 1;
            break;
        case DOWN:
            tailY.at(0) += 1;
            break;
        case LEFT:
            tailX.at(0) -= 1;
            break;
        case RIGHT:
            tailX.at(0) += 1;
            break;
    }

    if (tailX.at(0) < 0 || tailX.at(0) > width-1 || tailY.at(0) < 0 || tailY.at(0) > height-1 || check_if_snake_ate_itself()) {
        gameOver = true;
    }
}

int main() {
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(100); // Controls game speed
    }
    system("cls");
    std::cout << "GAME OVER!\nFinal Score: " << score << std::endl;
    return 0;
}
