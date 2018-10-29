#include <iostream>
#include <fstream>

#include <sstream>


#include "./BackpackProblem.h"

BackpackProblem *calculate(BackpackProblem *problem, int M, int i) {

    //pokud jsem dosel na konec plneni knapsacku
    if (i >= problem->getN() || problem->getM() == M) return problem;

    BackpackProblem *tmp=problem->flipValue(i);
    if(tmp->getM()>M) {
        delete tmp;
        return calculate(problem, M, i + 1);
    }

    BackpackProblem *tmp1 = calculate(tmp, M, i + 1);
    // cout<<tmp1<<endl;
    //optimize
    BackpackProblem *tmp2 = calculate(problem, M, i + 1);

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
    //copy(res[0], res[n], resAdded[0]);


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


int main(int argc, char **argv) {
    cout << "The Backpack Problem" << endl;

    string inst = argv[1];
    // string inst = "./inst/knap_4.inst.dat";

    cout << "Jmeno souboru " << inst << endl;

    ifstream infile;

    infile.open(inst);

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

        BackpackProblem *tmp = new BackpackProblem(id, n, M, Weights, Prices);
        //       cout << "============================" << endl;

        tmp = calculate(tmp, tmp->getinitM(), 0);

        tmp->format();

        delete tmp;

        // cout << "============================" << endl;
        // process pair (a,b)
    }
    cout << float( clock () - begin_time ) /  CLOCKS_PER_SEC;

    return 0;
}
