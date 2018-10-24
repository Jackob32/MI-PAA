#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <array>


#include "./BackpackProblem.h"

int BestPrice = 0;

BackpackProblem *bruteForceCalculate(BackpackProblem *problem, int M, int i) {


    //pokud jsem dosel na konec plneni knapsacku
    if (i >= problem->getN() || problem->getM() == M) return problem;

    if (problem->getM() + problem->getW(i) > M) {
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

BackpackProblem *heuristicsCalculate(BackpackProblem *problem, int M, int i) {

    double *ratio = new double[problem->getN()];

    array<double, 2> a[problem->getN()];
    /*= {{20, 11},
                          {10, 20},
                          {39, 14},
                          {29, 15},
                          {22, 23}};
                          */



    for (int j = 0; j < problem->getN(); ++j) {

        a[j] = {(double) problem->getW(j) / ((double) problem->getP(j)),(double)j};

    }

    sort(a, a + problem->getN());

    int k=0;

    while(k<problem->getN()) {

        if (problem->getM() + problem->getW((int) a[k][1]) <= problem->getinitM()) {

        problem->itemNum[(int) a[k][1]] = 1;
        problem->M += problem->getW((int) a[k][1]);
        problem->Price += problem->getP((int) a[k][1]);
    }
        k++;

    }

    /*
    cout <<"\n\n\n";


    for (int j = 0; j < problem->getN(); ++j) {

        cout << a[j][0] <<"  " << a[j][1] << " "<<  problem->getW((int)a[j][1]) << " " <<problem->getP((int)a[j][1]) << endl;
    }
*/


    return problem;

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
    cout << "begin time" << endl;
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

        while (iss >> V >> C) {

            Weights[itemnum] = V;
            Prices[itemnum] = C;

            itemnum++;
            if (itemnum > n) {
                cout << "Chyba formatu, vice itemu nez deklarovano " << inst << endl;
                break;
            }
        }
        int SumWeights = 0;

        for (int i = 0; i < n; ++i) {
            SumWeights += Prices[i];
        }

        BackpackProblem *heur = new BackpackProblem(id, n, M, Weights, Prices, SumWeights);
        //       cout << "============================" << endl;

        heur=heuristicsCalculate(heur, heur->getinitM(), 0);


        BackpackProblem *optim = new BackpackProblem(id, n, M, Weights, Prices, SumWeights);
        //       cout << "============================" << endl;

        optim=bruteForceCalculate(optim, optim->getinitM(), 0);

        //  heuristicsCalculate(tmp, tmp->getinitM(), 0);


        //cout<<tmp<<endl;
        heur->format();

        optim->format();




        cout<<optim->id<<"  "<<(double)(optim->getPrice()-heur->getPrice())/optim->getPrice()*100<<endl;


        delete heur;
        delete optim;
        delete[] Weights;
        delete[] Prices;

        // cout << "============================" << endl;
        // process pair (a,b)

        BestPrice = 0;
    }
    cout <<"\n"<< float(clock() - begin_time) / CLOCKS_PER_SEC << "  s "<<endl;

    return 0;
}





