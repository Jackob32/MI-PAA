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




int *bruteForceCalculate2(int * m, int * c, int * res, int M, int W, int n, int i) {

    //pokud jsem dosel na konec plneni knapsacku
    if (i >= n || W == M) return res;



    if (W + m[i] > M) {
        return bruteForceCalculate2(m,c,res, M,W,n, i + 1);
    }

    int * resAdded;
    copy(res[0], res[n], resAdded[0]);


    resAdded[i]=1;

    int  *tmp1 = bruteForceCalculate2(m,c,resAdded, M,W,n, i + 1);
    int  *tmp2 = bruteForceCalculate2(m,c,res, M,W,n, i + 1);

    if (1) {
        delete tmp2;
        return tmp1;
    } else {
        delete tmp1;
        return tmp2;
    }
}


BackpackProblem *heuristicsCalculate(BackpackProblem *problem, int M, int i) {

    array<double, 2> a[problem->getN()];

    for (int j = 0; j < problem->getN(); ++j) {

        a[j] = {(double) problem->getW(j) / ((double) problem->getP(j)), (double) j};

    }

    sort(a, a + problem->getN());

    int k = 0;

    while (k < problem->getN()) {

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


int knap(string file, int modheur, int modoptim, int modcompare) {

   // cout << "Jmeno souboru " << file << endl;

    ifstream infile;

    infile.open(file);

    if (!infile) {
        cout << "Unable to open file";
        return 1; // terminate with error
    }
    string line;

    const clock_t begin_time = clock();

// do something

    while (getline(infile, line)) {
        istringstream iss(line);

        int id, n, M = 0;

        if (!(iss >> id >> n >> M)) {
            cout << "Chyba formatu " << file << endl;
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
                cout << "Chyba formatu, vice itemu nez deklarovano " << file << endl;
                break;
            }
        }

        int SumWeights = 0;

        for (int i = 0; i < n; ++i) {
            SumWeights += Prices[i];
        }
        BackpackProblem *heur = NULL;
        if (modheur) {
            heur = new BackpackProblem(id, n, M, Weights, Prices, SumWeights);
            heur = heuristicsCalculate(heur, heur->getinitM(), 0);
            if(modheur==2)
            heur->format();
        }
        BackpackProblem *optim = NULL;
        if (modoptim) {
            optim = new BackpackProblem(id, n, M, Weights, Prices, SumWeights);
            optim = bruteForceCalculate(optim, optim->getinitM(), 0);
            //  heuristicsCalculate(tmp, tmp->getinitM(), 0);
            if(modoptim==2)
            optim->format();
        }

        if (modoptim && modheur && modcompare) {
            cout<<optim->id<<"  "<<(double)(optim->getPrice()-heur->getPrice())/optim->getPrice()*100<<endl;
        }

        if (modheur)
            delete heur;
        if (modoptim)
            delete optim;
        delete[] Weights;
        delete[] Prices;

        // cout << "============================" << endl;
        // process pair (a,b)

        BestPrice = 0;
    }
    cout << file << "  "  <<float(clock() - begin_time) / CLOCKS_PER_SEC << " s " << endl;

    return 0;
}


int main(int argc, char **argv) {

    cout << "The Backpack Problem" << endl;


    knap("./inst/knap_4.inst.dat",1,1,1);
    knap("./inst/knap_10.inst.dat",1,1,1);
    knap("./inst/knap_20.inst.dat",1,1,1);
    knap("./inst/knap_22.inst.dat",1,1,1);
    knap("./inst/knap_25.inst.dat",1,1,1);




    return 0;
}


/*
heuristics only

./inst/knap_4.inst.dat  0.000209  s
./inst/knap_10.inst.dat  0.000421  s
./inst/knap_20.inst.dat  0.000898  s
./inst/knap_22.inst.dat  0.001005  s
./inst/knap_25.inst.dat  0.00121  s
./inst/knap_27.inst.dat  0.001313  s
./inst/knap_30.inst.dat  0.00149  s
./inst/knap_32.inst.dat  0.001455  s
./inst/knap_35.inst.dat  0.001709  s
./inst/knap_37.inst.dat  0.0018  s
./inst/knap_40.inst.dat  0.001883  s


./inst/knap_4.inst.dat  0.000172 s
./inst/knap_10.inst.dat  0.006379 s
./inst/knap_20.inst.dat  10.5503 s
./inst/knap_22.inst.dat  39.0728 s
./inst/knap_25.inst.dat  345.054 s


 * */


