//
// Created by Jakub on 14.10.2018.
//

#include "BackpackProblem.h"

BackpackProblem::BackpackProblem(int id, int n, int M, int *Weights, int *Prices, int Rest) {

    this->id = id;
    this->n = n;
    this->M = 0;
    this->Price = 0;

    this->initM = M;
    this->Weights = Weights;
    this->Prices = Prices;
    this->itemNum = new int[n]();

    this->Rest = Rest;

}

int BackpackProblem::getM() const {
    return M;
}

int BackpackProblem::getinitM() const {
    return initM;
}

int BackpackProblem::getPrice() {
    return Price;
}

int BackpackProblem::getRest() {
    return Rest;
}

int BackpackProblem::getN() {
    return this->n;
}

int BackpackProblem::getW(int i) {
    return this->Weights[i];
}

int BackpackProblem::getP(int i) {
    return this->Prices[i];
}

BackpackProblem *BackpackProblem::flipValue(int flip) {
    BackpackProblem *tmp = new BackpackProblem(id, n, M, Weights, Prices, Rest - Prices[flip]);

    //copy(itemNum[0], itemNum[n], tmp->itemNum[0]);

    //cout<< " n" << n<<" flip "<<flip<<endl;
     memcpy( tmp->itemNum, itemNum, sizeof(&tmp->itemNum) );
/*
    for (int i = 0; i < n; ++i) {
        tmp->itemNum[i]= itemNum[i];
    }
*/
    tmp->itemNum[flip] = 1;
    tmp->M = M + Weights[flip];
    tmp->Price = Price + Prices[flip];
    return tmp;
}


void BackpackProblem::addItem(int Weight, int Price) {


}

ostream &operator<<(ostream &os, const BackpackProblem *obj) {

    os << "id: " << obj->id << "  ";
    os << "n: " << obj->n << "  ";
    os << "M: " << obj->getM() << "  ";
    os << "\n------------------------------- : " << obj->M << "\n";

    for (int i = 0; i < obj->n; ++i) {

        os << obj->itemNum[i];
        os << "  (";
        os << obj->Weights[i];
        os << ", ";
        os << obj->Prices[i];
        os << ") ";
        os << " ; ";
    }
    os << "\n" << endl;
    return os;
}


void BackpackProblem::format() {

    cout << id << " " << n << " " << getPrice() << " ";

    for (int i = 0; i < n; ++i) {
        cout << itemNum[i] << " ";
    }
    cout << " " << Rest;
    int celkem = 0;
    for (int j = 0; j < n; ++j) {
        celkem += Prices[j];
    }
    cout << "  celkem " << celkem;
    cout << endl;
}

void BackpackProblem::solve() {


}

BackpackProblem::~BackpackProblem() {

    delete[] this->itemNum;

}
