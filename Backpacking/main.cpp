#include <iostream>
#include <fstream>

#include <sstream>


#include "./BackpackProblem.h"

BackpackProblem *calculate(BackpackProblem *problem, int M, int i) {

    //pokud jsem dosel na konec plneni knapsacku
    if (i >= problem->getN() || problem->getM() == M) return problem;

    if(problem->getM() + problem->getWeight(i) > M) {
        return calculate(problem, M, i + 1);
    }

    BackpackProblem *tmp1 = calculate(problem->flipValue(i), M, i + 1);
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
    cout << float( clock () - begin_time ) /  CLOCKS_PER_SEC<<endl;

    return 0;
}





