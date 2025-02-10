#include<bits/stdc++.h>
#include<conio.h>
#include<windows.h>

using namespace std;

#define MAX_LENGTH 1000

// Directions
const char DIR_UP = 'U';
const char DIR_DOWN = 'D';
const char DIR_LEFT = 'L';
const char DIR_RIGHT = 'R';

int consoleWidth, consoleHeight;

void initScreen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    consoleHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

void hideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.bVisible = FALSE;
    info.dwSize = 100;
    SetConsoleCursorInfo(consoleHandle, &info);
}

struct Point{
    int xCoord;
    int yCoord;
    Point() {}
    Point(int x, int y) : xCoord(x), yCoord(y) {}
};

class Snake{
    int length;
    char direction;
public:
    Point body[MAX_LENGTH];
    Snake(int x, int y) : length(1), direction(DIR_RIGHT) {
       body[0] = Point(x, y);
    }

    int getLength() { return length; }

    void changeDirection(char newDirection) {
        if ((newDirection == DIR_UP && direction != DIR_DOWN) ||
            (newDirection == DIR_DOWN && direction != DIR_UP) ||
            (newDirection == DIR_LEFT && direction != DIR_RIGHT) ||
            (newDirection == DIR_RIGHT && direction != DIR_LEFT)) {
            direction = newDirection;
        }
    }

    bool move(Point food) {
        for (int i = length - 1; i > 0; i--) {
            body[i] = body[i - 1];
        }

        switch (direction) {
            case DIR_UP: body[0].yCoord--; break;
            case DIR_DOWN: body[0].yCoord++; break;
            case DIR_LEFT: body[0].xCoord--; break;
            case DIR_RIGHT: body[0].xCoord++; break;
        }

        for (int i = 1; i < length; i++) {
            if (body[0].xCoord == body[i].xCoord && body[0].yCoord == body[i].yCoord) {
                return false;
            }
        }

        if (food.xCoord == body[0].xCoord && food.yCoord == body[0].yCoord) {
            body[length++] = Point(body[length - 1].xCoord, body[length - 1].yCoord);
        }

        return true;
    }
};

class Board{
    Snake *snake;
    const char SNAKE_BODY = 'O';
    Point food;
    const char FOOD = 'o';
    int score;
public:
    Board() : score(0) {
        spawnFood();
        snake = new Snake(consoleWidth / 2, consoleHeight / 2);
    }

    ~Board() { delete snake; }

    int getScore() { return score; }

    void spawnFood() {
        food = Point(rand() % (consoleWidth - 2) + 1, rand() % (consoleHeight - 2) + 1);
    }

    void gotoxy(int x, int y) {
        COORD coord = { (SHORT)x, (SHORT)y };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }

    void draw() {
        gotoxy(0, 0);
        cout << "Score: " << score;

        gotoxy(food.xCoord, food.yCoord);
        cout << FOOD;

        for (int i = 0; i < snake->getLength(); i++) {
            gotoxy(snake->body[i].xCoord, snake->body[i].yCoord);
            cout << SNAKE_BODY;
        }
    }

    bool update() {
        gotoxy(snake->body[snake->getLength() - 1].xCoord, snake->body[snake->getLength() - 1].yCoord);
        cout << " ";

        bool isAlive = snake->move(food);
        if (!isAlive) return false;

        if (food.xCoord == snake->body[0].xCoord && food.yCoord == snake->body[0].yCoord) {
            score++;
            spawnFood();
        }
        return true;
    }

    void getInput() {
        if (kbhit()) {
            int key = getch();
            if (key == 'w' || key == 'W') snake->changeDirection(DIR_UP);
            else if (key == 'a' || key == 'A') snake->changeDirection(DIR_LEFT);
            else if (key == 's' || key == 'S') snake->changeDirection(DIR_DOWN);
            else if (key == 'd' || key == 'D') snake->changeDirection(DIR_RIGHT);
        }
    }
};

int main() {
    srand(time(0));
    initScreen();
    hideCursor();
    Board *board = new Board();
    while (board->update()) {
        board->getInput();
        board->draw();
        Sleep(100);
    }

    board -> gotoxy(consoleWidth / 2, consoleHeight / 2);
    cout << "Game Over! Final Score: " << board->getScore() << endl;
    return 0;
}