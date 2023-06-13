#include <iostream>
#include <random>
#include <windows.h>

using std::cout;
using std::cin;
using std::string;

int field[9][9];
int openedCells = 0;
bool GameOver = false;

void generateField();
int generateMines(int x, int y);
bool isOutOfBounds(int i, int j);
bool isMine(int i, int j);
bool isCellOpened(int i, int j);
bool isWin();
bool isZero(int i, int j);
void getInput();
void checkInput(int i, int j);
int cellsAround(int i, int j);
void cellsAroundZero(int i, int j);
void showField();
void showMines();

void generateField(){
    srand((unsigned int)time(NULL));
    int minesCounter = 0;
    int x, y;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            field[i][j] = -2;
        }
    }
    while (minesCounter < 10)
    {
        x = std::rand() % 9;
        y = std::rand() % 9;
        minesCounter += generateMines(x, y);
    }    
}

int generateMines(int x, int y){
    if(!isMine(x, y)){
        field[x][y] = -1;
        return 1;
    }
    return 0;
}

bool isOutOfBounds(int i, int j){
    return i < 0 || j < 0 || i > 8 || j > 8;
}

bool isMine(int i, int j){
    return field[i][j] == -1;
}

bool isCellOpened(int i, int j){
    return field[i][j] != -2;
}

bool isZero(int i, int j){
    return cellsAround(i, j) == 0;
}

bool isWin(){
    openedCells = 0;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if(isCellOpened(i, j))
                openedCells++;
        }
    }
    return openedCells == 81;    
}

void getInput(){
    cout << "Ход игрока: ";
    int x, y;
    cin >> x >> y;
    if(!cin){
        cin.clear();
        cin.ignore();
    }
    x--;
    y--;
    checkInput(x, y);
}

void checkInput(int i, int j){
    if(isOutOfBounds(i, j)){
        return;
    }
    else if(isMine(i, j)){
        GameOver = true;
        showMines();
        cout << "\n\nGAME OVER";
        return;
    }
    else if(isZero(i, j)) cellsAroundZero(i, j);
    else field[i][j] = cellsAround(i, j);
    if(isWin()){
        GameOver = true;
        showField();
        cout << "\n\nВы победили!";
        return;
    }
}

int cellsAround(int i, int j){
    int count = 0;
    for (int x = i-1; x <= i+1; x++)
    {
        for (int y = j-1; y <= j+1; y++)
        {
            if(isMine(x, y) && !isOutOfBounds(x,y))
                count++;
        }
    }
    openedCells++;
    return count;    
}

void cellsAroundZero(int i, int j){
    for (int x = i-1; x < i+2; x++)
    {
        for (int y = j-1; y < j+2; y++)
        {
            if(!isMine(x, y) && !isOutOfBounds(x,y) && !isCellOpened(x, y)){
                field[x][y] = cellsAround(x, y);
                if(field[x][y] == 0)
                    cellsAroundZero(x, y);
            }
        }
    }
}

void showField(){
    cout << '\n';
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (!isCellOpened(i, j) || isMine(i, j))
                cout << "'";
            else
                cout << field[i][j];
        }
        cout << '\n';
    }
}

void showMines(){
    cout << '\n';
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if(isMine(i, j))
                cout << "*";
            else if (!isCellOpened(i, j))
                cout << "'";
            else
                cout << field[i][j];
        }
        cout << '\n';
    }
}

int main(){
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    cout << "начало игры\n\n";
    generateField();
    while(!GameOver){
        showField();
        getInput();
    }
    cout << "\n\nконец игры";
    char await;
    cin >> await;
    return 0;
}