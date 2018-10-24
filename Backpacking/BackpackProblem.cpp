//
// Created by Jakub on 14.10.2018.
//

#include "BackpackProblem.h"

BackpackProblem::BackpackProblem(int id, int n, int M, int * Weights, int * Prices){

    this->id=id;
    this->n=n;
    this->M=0;
    this->initM=M;
    this->Weights=Weights;
    this->Prices=Prices;
    this->itemNum=new int[n];
    for(int i=0;i<n;i++){
        itemNum[i]=0;
    }

}
int BackpackProblem::getM() const{
    int M=0;
    for(int i=0;i<this->n;i++){
        M+=this->Weights[i]*this->itemNum[i];
    }
    return M;
}
int BackpackProblem::getinitM() const{

    return initM;
}
int BackpackProblem::getPrice(){
    int Price=0;
    for(int i=0;i<this->n;i++){
        Price+=this->Prices[i]*this->itemNum[i];
    }

    return Price;
}


int BackpackProblem::getN(){
    return this->n;
}

int BackpackProblem::getWeight(int i){
    return this->Weights[i];
}

BackpackProblem * BackpackProblem::flipValue(int flip){

    auto *newWeights = new int[n];
    for (int i = 0; i < n; ++i) {
        newWeights[i]=Weights[i];
    }
    auto *newPrices = new int[n];
    for (int i = 0; i < n; ++i) {
        newPrices[i]=Prices[i];
    }

    BackpackProblem  *tmp = new BackpackProblem(id,n,M,newWeights,newPrices);

    for(int i=0;i<n;i++){
        tmp->itemNum[i]=itemNum[i];
    }
    //cout<< " n" << n<<" flip "<<flip<<endl;

    tmp->itemNum[flip]=1;

    return tmp;
}

void BackpackProblem::addItem(int Weight, int Price){


}

ostream& operator<<(ostream& os, const BackpackProblem* obj){

    os << "id: "<<obj->id<<"  ";
    os << "n: "<<obj->n<<"  ";
    os << "M: "<<obj->getM()<<"  ";
    os << "\n------------------------------- : "<<obj->M<<"\n";

    for (int i = 0; i < obj->n; ++i) {

        os << obj->itemNum[i];
        os << "  (";
            os << obj->Weights[i];
        os << ", ";
        os << obj->Prices[i];
        os << ") ";
        os << " ; ";
    }
    os <<"\n"<< endl;
    return os;
}


void BackpackProblem::format(){

    cout<< id<<" "<<n<<" "<<getPrice()<<" ";

    for (int i = 0; i < n; ++i) {

        cout << itemNum[i]<<" ";

    }
    cout<< endl;
}

void BackpackProblem::solve(){


}
BackpackProblem::~BackpackProblem(){

    delete[] this->Prices;
    delete[] this->Weights;
    delete[] this->itemNum;

}
