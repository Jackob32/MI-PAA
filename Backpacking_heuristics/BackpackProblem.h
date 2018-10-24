//
// Created by Jakub on 14.10.2018.
//

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>
#include <deque>

using namespace std;

#ifndef BACKPACKING_BACKPACKPROBLEM_H
#define BACKPACKING_BACKPACKPROBLEM_H


class BackpackProblem {
public:
    BackpackProblem(int id, int n, int M, int * Weights, int * Prices);
    void addItem(int Weight, int Price);
    friend ostream& operator<<(ostream& os, const BackpackProblem* obj);
    void format();
    void solve();
    int getM() const;
    int getinitM() const;
    int getN();
    int getPrice();
    BackpackProblem * flipValue(int nulIndex);

    ~BackpackProblem();
private:
int id,n,M,Price,initM;
int * Weights, * Prices, * itemNum;

};


#endif //BACKPACKING_BACKPACKPROBLEM_H
