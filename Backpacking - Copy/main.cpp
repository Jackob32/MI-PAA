#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <array>


#include "./BackpackProblem.h"

int BestPrice=0;

BackpackProblem * bruteForceCalculate(BackpackProblem *problem, int M, int i) {

    //pokud jsem dosel na konec plneni knapsacku
    if (i >= problem->getN() || problem->getM() == M) return problem;

    if(problem->getM() + problem->getW(i) > M) {
        return bruteForceCalculate(problem, M, i + 1);
    }

    BackpackProblem *tmp1 = bruteForceCalculate(problem->flipValue(i), M, i + 1);
    BackpackProblem *tmp2 = bruteForceCalculate(problem, M, i + 1);

    if (tmp1->getPrice() > tmp2->getPrice()) {
        delete tmp2;
        return tmp1;
    } else {
        delete tmp1;
        return tmp2;
    }

}

BackpackProblem * branchAndBoundCalculate(BackpackProblem *problem, int M, int i) {

    //pokud jsem dosel na konec plneni knapsacku
    if (i >= problem->getN() || problem->getM() == M) return problem;

    if(problem->getM() + problem->getW(i) > M) {
        return branchAndBoundCalculate(problem, M, i + 1);
    }

    BackpackProblem *tmp1 = branchAndBoundCalculate(problem->flipValue(i), M, i + 1);
    if(problem->getPrice()+problem->getRest()<BestPrice)
        return  branchAndBoundCalculate(tmp1, M, i + 1);
    BackpackProblem *tmp2 = branchAndBoundCalculate(problem, M, i + 1);

    if (tmp1->getPrice() > tmp2->getPrice()) {
        delete tmp2;
        if(tmp1->getPrice()>BestPrice)BestPrice=tmp1->getPrice();
        return tmp1;
    } else {
        delete tmp1;
        if(tmp2->getPrice()>BestPrice)BestPrice=tmp1->getPrice();
        return tmp2;
    }
}

BackpackProblem * heuristicsCalculate(BackpackProblem *problem, int M, int i) {

    double *ratio = new double[problem->getN()];

    array<int, 2> a[5] = { { 20, 11 },
                           { 10, 20 },
                           { 39, 14 },
                           { 29, 15 },
                           { 22, 23 } };

    sort( a, a + 5 );

    for (int j = 0; j < problem->getN(); ++j) {

        ratio[j]=(double)problem->getW(j)/((double)problem->getP(j));
        cout<<"m "<<ratio[j]<<endl;
    }
    sort(ratio, ratio + problem->getN());
    for (int j = 0; j < problem->getN(); ++j) {

        cout<<" "<<ratio[j]<<endl;
    }
    return problem;

}

BackpackProblem * bruteForceCalculate(int * Weights,int * Prices, int n, int M, int actM, int i) {

    //pokud jsem dosel na konec plneni knapsacku
    if (i >= problem->getN() || problem->getM() == M) return problem;

    if (n == 0 || M == actM) return 0;

    if (Weights[i-1] > M)
        return bruteForceCalculate(Weights, Prices, n, M, actM, i-1);

    if(problem->getM() + problem->getW(i) > M) {
        return bruteForceCalculate(problem, M, i + 1);
    }

    BackpackProblem *tmp1 = bruteForceCalculate(problem->flipValue(i), M, i + 1);
    BackpackProblem *tmp2 = bruteForceCalculate(problem, M, i + 1);

    if (tmp1->getPrice() > tmp2->getPrice()) {
        delete tmp2;
        return tmp1;
    } else {
        delete tmp1;
        return tmp2;
    }

}

// Driver program to test above function
int main()
{
    int val[] = {60, 100, 120};
    int wt[] = {10, 20, 30};
    int  W = 50;
    int n = sizeof(val)/sizeof(val[0]);
    printf("%d", knapSack(W, wt, val, n));
    return 0;
}


int main(int argc, char **argv) {
    cout << "The Backpack Problem" << endl;

    string inst = argv[1];
    //string inst = "../inst/knap_4.inst.dat";

    cout << "Jmeno souboru " << inst << endl;

    ifstream infile;

    infile.open(inst);

    if (!infile) {
        cout << "Unable to open file";
        return 1; // terminate with error
    }
    string line;

    const clock_t begin_time = clock();
    cout<<"begin time"<<endl;
// do something

    while (getline(infile, line)) {
        istringstream iss(line);

        int id, n, M = 0;

        if (!(iss >> id >> n >> M)) {
            cout << "Chyba formatu " << inst << endl;
            break;
        } // error

        int V, C, itemnum = 0;

        auto *Weights = new int[n];
        auto *Prices = new int[n];
        int rest=0;

        while (iss >> V >> C) {

            Weights[itemnum] = V;
            Prices[itemnum] = C;

            itemnum++;
            if (itemnum > n) {
                cout << "Chyba formatu, vice itemu nez deklarovano " << inst << endl;
                break;
            }
        }

        for (int i = 0; i < n; ++i) {
            rest+=Prices[i];
        }

        BackpackProblem *tmp = new BackpackProblem(id, n, M, Weights, Prices, rest);
        //       cout << "============================" << endl;

        tmp = branchAndBoundCalculate(tmp, tmp->getinitM(), 0);

      //  heuristicsCalculate(tmp, tmp->getinitM(), 0);


        //cout<<tmp<<endl;
        tmp->format();

        delete tmp;
        delete[] Weights;
        delete[] Prices;

        // cout << "============================" << endl;
        // process pair (a,b)

        BestPrice=0;
    }
    cout << float( clock () - begin_time ) /  CLOCKS_PER_SEC<<endl;

    return 0;
}





