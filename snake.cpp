#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

void drawBoard(vector<pair<int,int>> currentPositions, pair<int,int> food){
    cout << "\n";
    for (int i = 0; i < 9; i++)
    {
        cout << "\n";
        for (int j = 0; j < 9; j++)
        { 
            bool isSnake = false;

            for (auto& p : currentPositions) {
                if (p.first == i && p.second == j) {
                    isSnake = true;
                    break;
                }
            }
            if (i == food.first && j == food.second)
            {
                cout << "F";
            }else{
                if (isSnake)
                    cout << "S";
                else
                    cout << "X";
            }
            
            
        } 
    }
    cout << "\n\n";
}

void move(vector<pair<int,int>>& currentPositions){
    char movement;
    cin >> movement;

    int heady= currentPositions[0].first;
    int headx= currentPositions[0].second;
    
    switch (movement)
    {
    case 'w':
        heady--;
        break;
    case 'a':
        headx--;
        break;
    case 's':
        heady++;
        break;
    case 'd':
        headx++;
        break;
    default: return;
        break;
    }

    for (int i = currentPositions.size() - 1; i > 0; i--) {
        currentPositions[i] = currentPositions[i - 1];
    }

    currentPositions[0]= {heady, headx};
}

pair<int,int> Food(){
    srand((unsigned)time(0));
    int i;
    i = (rand()%8)+1;
    int j;
    j = (rand()%8)+1;
    pair<int,int> food = {i,j};
    return(food);
}

pair<int,int> foodCheck(vector<pair<int,int>> currentPositions, pair<int,int> food){
    bool isFood = false;
    for (auto& p : currentPositions) {
            if (p.first == food.first && p.second == food.second) {
                isFood = true;
                break;
            }
        }
    if (isFood)
    {
        food = Food();
        return food;
    }else{
        return food;
    }

}

int main(){
    vector<pair<int,int>> currentPositions = {{1,0},{0,0}};
    pair<int, int> food = Food();
    while(true){
        food = foodCheck(currentPositions,food);
        drawBoard(currentPositions,food);
        move(currentPositions);
    }
    
    return 0;
}