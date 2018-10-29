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

    double max_relative = 0, avg_relative = 0;

    double lines = 0, totalerr = 0;

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
            if (modheur == 2)
                heur->format();
        }
        BackpackProblem *optim = NULL;
        if (modoptim) {
            optim = new BackpackProblem(id, n, M, Weights, Prices, SumWeights);
            optim = bruteForceCalculate(optim, optim->getinitM(), 0);
            //  heuristicsCalculate(tmp, tmp->getinitM(), 0);
            if (modoptim == 2)
                optim->format();
        }

        if (modoptim && modheur && modcompare) {

            double chyba = (double) (optim->getPrice() - heur->getPrice()) / optim->getPrice() * 100;

            if (chyba > max_relative) max_relative = chyba;

            totalerr += chyba;

            // cout<<optim->id<<"  "<<(double)(optim->getPrice()-heur->getPrice())/optim->getPrice()*100<<endl;
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
        lines++;
    }

    //cout << file << "  "  <<float(clock() - begin_time) / CLOCKS_PER_SEC << " s " << endl;

    avg_relative = totalerr / lines;
    if (modoptim && modheur && modcompare) {
        cout << "  Max Relative " << max_relative << ", Avg relative  " << avg_relative << endl;
    }

    return 0;
}


void multipleruns(string file, int runs) {


    const clock_t begin_time = clock();

    for (int i = 0; i < runs; ++i) {
        knap(file, 0, 1, 0);
    }

    cout << file << " " << runs << "  " << ((float(clock() - begin_time) / CLOCKS_PER_SEC)) / runs << " s " << endl;

}

int main(int argc, char **argv) {

    cout << "The Backpack Problem" << endl;
/*
    multipleruns("./inst/knap_4.inst.dat",1000);
    multipleruns("./inst/knap_10.inst.dat",100);
    multipleruns("./inst/knap_15.inst.dat",10);
    multipleruns("./inst/knap_20.inst.dat",1);
    multipleruns("./inst/knap_22.inst.dat",1);
*/
    /*multipleruns("./inst/knap_25.inst.dat",1000);
    multipleruns("./inst/knap_27.inst.dat",1000);
    multipleruns("./inst/knap_30.inst.dat",1000);
    multipleruns("./inst/knap_32.inst.dat",1000);
    multipleruns("./inst/knap_35.inst.dat",1000);
    multipleruns("./inst/knap_37.inst.dat",1000);
    multipleruns("./inst/knap_40.inst.dat",1000);

*/

//    multipleruns("./inst/knap_20.inst.dat",10);


    knap("./inst/knap_4.inst.dat", 1, 1, 1);
    knap("./inst/knap_10.inst.dat", 1, 1, 1);
    knap("./inst/knap_15.inst.dat", 1, 1, 1);
    knap("./inst/knap_20.inst.dat", 1, 1, 1);
    knap("./inst/knap_22.inst.dat", 1, 1, 1);
    knap("./inst/knap_25.inst.dat", 1, 1, 1);
    knap("./inst/knap_27.inst.dat", 1, 1, 1);
    // knap("./inst/knap_30.inst.dat",1,1,1);

/*

    knap("./inst/knap_4.inst.dat",1,1,1);
    knap("./inst/knap_10.inst.dat",1,1,1);
    knap("./inst/knap_15.inst.dat",1,1,1);
    knap("./inst/knap_20.inst.dat",1,1,1);
    knap("./inst/knap_22.inst.dat",1,1,1);
    knap("./inst/knap_25.inst.dat",1,1,1);
    knap("./inst/knap_27.inst.dat",1,1,1);
    knap("./inst/knap_30.inst.dat",1,1,1);

*/


    return 0;
}


/*
heuristics only

./inst/knap_4.inst.dat 1000  0.000234375 s
./inst/knap_10.inst.dat 1000  0.0003125 s
./inst/knap_15.inst.dat 1000  0.000296875 s
./inst/knap_20.inst.dat 1000  0.000359375 s
./inst/knap_22.inst.dat 1000  0.000390625 s
./inst/knap_25.inst.dat 1000  0.0004375 s
./inst/knap_27.inst.dat 1000  0.000453125 s
./inst/knap_30.inst.dat 1000  0.000484375 s
./inst/knap_32.inst.dat 1000  0.000515625 s
./inst/knap_35.inst.dat 1000  0.000546875 s
./inst/knap_37.inst.dat 1000  0.0005625 s
./inst/knap_40.inst.dat 1000  0.000578125 s

4   0.000234375 s
10   0.0003125 s
15   0.000326875 s
20   0.000359375 s
22   0.000390625 s
25   0.0004375 s
27   0.000453125 s
30   0.000484375 s
32   0.000515625 s
35   0.000546875 s
37   0.0005625 s
40   0.000578125 s

bruteforce


# Problem size    Hrubá síla       Heuristika
4  0.00021875   0.000234375
10  0.00234375   0.0003125
15  0.107813    0.000326875
20			2.8125		0.000359375
22			10.7344		0.000390625
25			90.5938		0.0004375
27			401.484		0.000453125



 prum relativni chybovost

 4	2.17451
10	1.2862
15	0.475892
20	0.600086
22	0.686694
25	0.498356
 27	0.50165

 max relativni chybovost

 4	36.3636
10	11.4801
15	8.54271
20	8.43373
22	7.22892
25	3.67893
 27	10.6017

./inst/knap_4.inst.dat  0 s Max Relative 36.3636, Avg relative  2.17451

./inst/knap_10.inst.dat  0.015625 s Max Relative 11.4801, Avg relative  1.2862

./inst/knap_15.inst.dat  0.078125 s Max Relative 8.54271, Avg relative  0.475892

./inst/knap_20.inst.dat  2.85938 s Max Relative 8.43373, Avg relative  0.600086

./inst/knap_22.inst.dat  10.4219 s Max Relative 7.22892, Avg relative  0.686694

./inst/knap_25.inst.dat  89.9531 s Max Relative 3.67893, Avg relative  0.498356

./inst/knap_27.inst.dat  365.766 s   Max Relative 10.6017, Avg relative  0.50165



4 5 5


 ./inst/knap_27.inst.dat  401.484 s
./inst/knap_4.inst.dat  0 s
  Max Relative 36.3636, Avg relative  2.17451
./inst/knap_10.inst.dat  0 s
  Max Relative 11.4801, Avg relative  1.2862
./inst/knap_20.inst.dat  2.75 s
  Max Relative 8.43373, Avg relative  0.600086
./inst/knap_22.inst.dat  10.2031 s
  Max Relative 7.22892, Avg relative  0.686694
./inst/knap_25.inst.dat  90.1719 s
  Max Relative 3.67893, Avg relative  0.498356



 # This file is called   force.dat
# Force-Deflection data for a beam and a bar
# Problem size    Hrubá síla       Heuristika
0			0		0
4			0.00059375		0
10			0		0
15			0.09375		0
20			2.8125		0
22			10.7344		0
25			90.5938		0
27			401.484		0


# Scale font and line width (dpi) by changing the size! It will always display stretched.
set terminal svg size 400,300 enhanced fname 'arial'  fsize 10 butt solid
set output 'out.svg'

# Key means label...
set key inside bottom right
set xlabel 'Problem size (n)'
set ylabel 'Time (s)'
set title 'Hrubá síla vs Heuristika'
plot  "data.txt" using 1:2 title 'Hrubá síla' with lines, "data.txt" using 1:3 title 'Heuristika' with linespoints







 # This file is called   force.dat
# Force-Deflection data for a beam and a bar
# Deflection    Průměrná chybovost
4              2.17451
10				1.2862
15				0.475892
20             0.600086
22             0.686694
25           0.4


# Scale font and line width (dpi) by changing the size! It will always display stretched.
set terminal svg size 400,300 enhanced fname 'arial'  fsize 10 butt solid
set output 'out.svg'

set title "Query 1 - BSBM"
set style data histogram
set boxwidth 0.3 absolute
set style histogram rowstacked
set style fill solid 1.0 border lt -1
set ylabel "%"
set auto x

plot "data.txt" using 2 t "Průměrná relativní chybovost %"


 * */


