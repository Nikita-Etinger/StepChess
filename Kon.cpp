#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
#define random(a,b) a + rand() % (b - a + 1)
const int SIZE = 8;

// Проверка, находится ли данная позиция на поле
bool isValidPosition(int x, int y) {
    return (x >= 0 && x < SIZE&& y >= 0 && y < SIZE);
}

// Проверка, был ли данной клетке конь
bool isVisited(bool visited[SIZE][SIZE], int x, int y) {
    return visited[x][y];
}

// Вывод поля с закрашенными клетками после каждого хода
void displayBoard(bool visited[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (visited[i][j])
                 cout << "X ";
            else
                 cout << ". ";
        }
         cout <<  endl;
    }
     cout <<  endl;
}

// Поиск оптимального пути для коня
void findOptimalPath() {
    bool visited[SIZE][SIZE] = { false };
    int dx[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };
    int dy[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };



    // Стартовая позиция коня
    int x = random(0, SIZE);
    int y = random(0, SIZE);
    visited[x][y] = true;
    displayBoard(visited);

    int moveCount = 1;

    // Проход коня по всем клеткам поля
    while (moveCount < SIZE * SIZE) {
        int minDegree = SIZE + 1;
        int newX = -1, newY = -1;

        // Поиск доступных следующих ходов
        for (int i = 0; i < 8; ++i) {
            int nextX = x + dx[i];
            int nextY = y + dy[i];
            if (isValidPosition(nextX, nextY) && !isVisited(visited, nextX, nextY)) {
                int degree = 0;
                for (int j = 0; j < 8; ++j) {
                    int x2 = nextX + dx[j];
                    int y2 = nextY + dy[j];
                    if (isValidPosition(x2, y2) && !isVisited(visited, x2, y2))
                        degree++;
                }
                if (degree < minDegree) {
                    minDegree = degree;
                    newX = nextX;
                    newY = nextY;
                }
            }
        }

        // Если не найдены доступные ходы, а конь еще не прошел все клетки поля
        if (minDegree == SIZE + 1) {
             cout << "Путь невозможен" <<  endl;
            return;
        }

        // Перемещение коня на следующую позицию
        x = newX;
        y = newY;
        visited[x][y] = true;
        displayBoard(visited);

        moveCount++;
    }

     cout << "Путь найден" <<  endl;
}

int main() {
    findOptimalPath();
    return 0;
}