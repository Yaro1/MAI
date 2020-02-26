#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
using std::endl;


struct element{
    int data;
    int num;
};

class Heh_Bag{
public:
    Heh_Bag(int weight, int number) {
        this->max_number = number;
        this->max_weight = weight;

        vector <element> next_vector;
        element next_element;
        next_element.data = 0;
        next_element.num = 0;

        next_vector.resize(weight, next_element);
        for(int i = 0; i < number;i++) {
            this->answer.push_back(next_vector);
        }
    }

    ~Heh_Bag(){}

    void PutData();
    void GenerateMatric();
    void FindPath(int k, int s);
    void PrintResult();
    void PrintMatric();
private:
    vector <int> data_weight;
    vector <int> data_cost;

    int max_weight;
    int max_number;

    vector <vector <element> > answer;
    vector <int> answer_path;

};

void Heh_Bag::PutData() {
    int one_weight, one_cost;
    for(int i = 0; i < this->max_number - 1;i++) {
        cin >> one_weight >> one_cost;
        data_weight.push_back(one_weight);
        data_cost.push_back(one_cost);
    }
}

void Heh_Bag::GenerateMatric() {
    for(int k = 1;k < this->max_number;k++) {

        for(int s = 1; s < this->max_weight;s++) {
            if(s >= this->data_weight[k - 1]) {
                if(this->answer[k - 1][s].data * this->answer[k - 1][s].num <= (this->answer[k - 1][s - data_weight[k - 1]].data + data_cost[k - 1]) * (this->answer[k - 1][s - data_weight[k - 1]].num + 1)) {
                    this->answer[k][s].data = (this->answer[k - 1][s - data_weight[k - 1]].data + data_cost[k - 1]);
                    this->answer[k][s].num = this->answer[k - 1][s - data_weight[k - 1]].num + 1;
                }
                else {
                    this->answer[k][s].data = this->answer[k - 1][s].data;
                    this->answer[k][s].num = this->answer[k - 1][s].num;
                }
            }
            else {
                this->answer[k][s].data = this->answer[k - 1][s].data;
                this->answer[k][s].num = this->answer[k - 1][s].num;
            }
        }
        PrintMatric();
        cout << endl << endl;
    }
}

void Heh_Bag::PrintMatric() {
    for(int i =0; i < this->answer.size();i++) {
        for(int j = 0; j < this->answer[i].size();j++) {
            cout << this->answer[i][j].data << " ";
        }
        cout << endl;
    }
}


void Heh_Bag::FindPath(int k, int s) {
    if (this->answer[k][s].data == 0)
        return;
    if (this->answer[k - 1][s].data == this->answer[k][s].data)
        FindPath(k - 1, s);
    else {
        FindPath(k - 1, s - this->data_weight[k - 1]);
        this->answer_path.push_back(k);
    }
}
/*
 7 9
4 11
8 25
15 30
7 40
6 50
3 100
1 1000
*/

void Heh_Bag::PrintResult() {
    cout << this->answer[this->answer.size() - 1][this->answer[this->answer.size() - 1].size() - 1].data * this->answer[this->answer.size() - 1][this->answer[this->answer.size() - 1].size() - 1].num << endl;
    if(this->answer_path.size() > 0) {
        for (int i = 0; i < this->answer_path.size() - 1; i++) {
            cout << this->answer_path[i] << " ";
        }
        cout << this->answer_path[this->answer_path.size() - 1] << endl;
    }
}
int main() {
    int W, N;
    cin >> N >> W;
    Heh_Bag bag(W + 1, N + 1);
    bag.PutData();
    bag.GenerateMatric();
    //  bag.PrintMatric();
    bag.FindPath(N, W);
    bag.PrintResult();
    return 0;
}
