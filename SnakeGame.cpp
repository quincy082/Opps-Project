#include <bits/stdc++.h>
#include <conio.h>
#include <windows.h>

using namespace std;

#define MAX_LENGTH 1000

// Directions
const char DIR_UP = 'U';
const char DIR_DOWN = 'D';
const char DIR_LEFT = 'L';
const char DIR_RIGHT = 'R';

int consoleWidth = 40, consoleHeight = 20; // Fixed dimensions for stable gameplay
int highScore = 0; // Store the highest score

void hideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.bVisible = FALSE;
    info.dwSize = 100;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void gotoxy(int x, int y) {
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void drawCenteredText(string text, int y) {
    int x = (consoleWidth - text.length()) / 2;
    gotoxy(x, y);
    cout << text;
}

void drawBorder() {
    system("cls");
    for (int i = 0; i < consoleWidth; i++) {
        gotoxy(i, 0); cout << "#";
        gotoxy(i, consoleHeight - 1); cout << "#";
    }
    for (int i = 0; i < consoleHeight; i++) {
        gotoxy(0, i); cout << "#";
        gotoxy(consoleWidth - 1, i); cout << "#";
    }
}

void showStartScreen() {
    system("cls");
    drawBorder();

    drawCenteredText("==== SNAKE GAME ====", consoleHeight / 2 - 3);
    drawCenteredText("Use W, A, S, D to move", consoleHeight / 2 - 1);
    drawCenteredText("Press any key to start...", consoleHeight / 2 + 1);
    
    getch();
}

bool showGameOverScreen(int score) {
    system("cls");
    drawBorder();

    drawCenteredText("===== GAME OVER! =====", consoleHeight / 2 - 4);
    drawCenteredText("Final Score: " + to_string(score), consoleHeight / 2 - 2);
    drawCenteredText("High Score: " + to_string(highScore), consoleHeight / 2);
    drawCenteredText("Press 'R' to Restart", consoleHeight / 2 + 2);
    drawCenteredText("Press any other key to Exit", consoleHeight / 2 + 4);

    char choice = getch();
    return (choice == 'r' || choice == 'R');
}

struct Point {
    int xCoord, yCoord;
    Point() {}
    Point(int x, int y) : xCoord(x), yCoord(y) {}
};

class Snake {
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

        // Collision with itself
        for (int i = 1; i < length; i++) {
            if (body[0].xCoord == body[i].xCoord && body[0].yCoord == body[i].yCoord) {
                return false;
            }
        }

        // Collision with borders
        if (body[0].xCoord <= 0 || body[0].xCoord >= consoleWidth - 1 ||
            body[0].yCoord <= 0 || body[0].yCoord >= consoleHeight - 1) {
            return false;
        }

        // Eating food
        if (food.xCoord == body[0].xCoord && food.yCoord == body[0].yCoord) {
            body[length++] = Point(body[length - 1].xCoord, body[length - 1].yCoord);
        }

        return true;
    }
};

class Board {
    Snake* snake;
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

    void draw() {
        system("cls");
        drawBorder();
        gotoxy(2, consoleHeight);
        cout << "Score: " << score << "  High Score: " << highScore;

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
            if (score > highScore) highScore = score;
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
    hideCursor();

    while (true) {
        showStartScreen();
        Board* board = new Board();
        while (board->update()) {
            board->getInput();
            board->draw();
            Sleep(100);
        }
        delete board;

        if (!showGameOverScreen(board->getScore())) {
            break;
        }
    }

    return 0;
} 
