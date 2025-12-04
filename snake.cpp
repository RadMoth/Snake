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
                cout << "\033[31mF\033[0m";
            }else{
                if (isSnake)
                    cout << "\033[32mS\033[0m";
                else
                    cout << "*";
            }
            
            
        } 
    }
    cout << "\n\n";
}

void move(vector<pair<int,int>>& currentPositions){
    char movement;
    rep:
    cin >> movement;

    int heady= currentPositions[0].first;
    int headx= currentPositions[0].second;
    
    switch (movement)
    {
    case 'w':
        if (heady!=0)
        {
            heady--;
        }else{
            goto rep;
        }
        break;
    case 'a':
        if (headx!=0)
        {
            headx--;
        }else{
            goto rep;
        }
        break;
    case 's':
        if (heady!=8)
        {
            heady++;
        }else{
            goto rep;
        }
        break;
    case 'd':
        if (headx!=8)
        {
            headx++;
        }else{
            goto rep;
        }
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

pair<int,int> foodCheck(vector<pair<int,int>>& currentPositions, pair<int,int> food, pair<int,int> tail){
    bool isFood = false;
    for (auto& p : currentPositions) {
            if (p.first == food.first && p.second == food.second) {
                isFood = true;
                break;
            }
        }
    if (isFood)
    {
        currentPositions.push_back(tail);
        again:
        food = Food();
        bool isBadSpawn = false;
        for (auto& p : currentPositions) {
            if (p.first == food.first && p.second == food.second) {
                isBadSpawn = true;
                break;
            }
        }
        if (isBadSpawn)
        {
            goto again;
        }
        
        return food;
    }else{
        return food;
    }

}

int main(){
    vector<pair<int,int>> currentPositions = {{1,0},{0,0}};
    pair<int, int> food = Food();
    pair<int, int> tail = currentPositions.back();
    bool isDead = false;
    int counter = 0;
    while(!isDead){ 
        counter = 0;
        food = foodCheck(currentPositions,food,tail);
        tail = currentPositions.back();
        drawBoard(currentPositions,food);
        move(currentPositions);
        for (auto& p : currentPositions) {
            if (p == currentPositions[0]) {
                counter++;
                if (counter==2)
                {
                    isDead = true;
                    break;
                }
                
                
                
            }
        }
        
    }
    
    return 0;
}