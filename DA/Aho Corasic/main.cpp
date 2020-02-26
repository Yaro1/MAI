// TRUE_MY_AHOK.cpp: определяет точку входа для консольного приложения.
//

//#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <queue>
#include <fstream>

using std::string;
using std::vector;
using std::map;
using std::queue;
using std::fstream;
using std::cout;
using std::cin;
using std::endl;

class TNode {
public:
    unsigned long long key_number;
    TNode * parent;
    map <unsigned long long, TNode *> child;
    TNode * link;
    bool is_list;
    int place_under_string;
    int num_mask;
    vector <int> num_in_pattern;
    int depth;
    TNode() {

    }
    TNode(unsigned long long n_number, TNode * n_parent, int n_depth) {
        key_number = n_number;
        parent = n_parent;
        link = nullptr;
        is_list = false;
        place_under_string = -1;
        num_mask = 0;
        depth = n_depth;
    }
    ~TNode() { }
};

class TTrie {
public:
    TNode * root;
    vector <string> patterns;
    vector <int> joker_place;
    int num_pattern_without_Joker;
    int num_Joker;

    const string Joker = "?";
    TTrie() {
        root = new TNode(0, root, 0);
        root->link = root;
        num_Joker = 0;
        num_pattern_without_Joker = 0;
    }
    void Make();
    void Make_Links();
    void Find_Occurrence(vector<std::pair<int, int> > answer, vector <unsigned long long> check);
};

void TTrie::Make() {
    map <unsigned long long, TNode *>::iterator it;
    TNode * now_node = root;
    int now_length = 0;
    int now_depth = 0;
    int index_begin = 0;
    int i = 0;
    for (; i < this->patterns.size(); i++) {

        if (patterns[i] == Joker) {
            num_Joker++;
            now_node->num_in_pattern.push_back(index_begin);
            index_begin = i + 1;
            now_node->is_list = true;
            now_node = root;
            now_depth = 0;
            //num_pattern_without_Joker++;
        }
        else {
            it = now_node->child.find(stoul(patterns[i]));
            now_depth++;
            if (it == now_node->child.end()) {
                TNode * new_node = new TNode(stoul(patterns[i]), now_node, now_depth);
                now_node->child[stoul(patterns[i])] = new_node;
                now_node = new_node;
            }
            else {
                now_node = it->second;
            }
            now_length++;
        }
    }
    //num_pattern_without_Joker++;
    now_node->is_list = true;
    now_node->num_in_pattern.push_back(index_begin);
    Make_Links();
}

void TTrie::Make_Links() {
    TNode *now_link, *node, *now_node;
    unsigned long long number;
    queue <TNode *> node_queue;
    now_node = root;
    node_queue.push(now_node);

    while (!node_queue.empty()) {
        node = node_queue.front();
        node_queue.pop();

        for (auto i : node->child) {

            now_node = i.second;
            if (now_node->is_list) {
                for (int k = 0; k < now_node->num_in_pattern.size(); k++)
                    num_pattern_without_Joker++;
            }
            number = i.first;
            node_queue.push(now_node);
            now_link = now_node->parent->link;
            if (now_node->parent == root) {
                now_node->link = root;
            }
            else {
                while (1) {
                    std::map<unsigned long long, TNode *>::iterator it = now_link->child.find(number);
                    if (it != now_link->child.end()) {
                        now_link = it->second;
                        break;
                    }
                    else {
                        if (now_link == root)
                            break;
                        else
                            now_link = now_link->link;
                    }
                }
                now_node->link = now_link;
            }
        }

    }
}

void TTrie::Find_Occurrence(vector<std::pair<int, int> > answer, vector <unsigned long long> check) {

    map <unsigned  long long, TNode *>::iterator it;
    vector <int> pos_entering;

    int l = 0;
    int c = 0;
    TNode * now_node1 = root;
    TNode * now_node2;

    pos_entering.resize(check.size(), 0);

    do {

        it = now_node1->child.find(check[c]);

        while (it != now_node1->child.end()) {
            now_node2 = it->second;

            if (now_node2->is_list) {
                for (auto i : now_node2->num_in_pattern) {
                    if (l - i < 0)
                        break;
                    pos_entering[l - i]++;
                }
            }

            // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
            if (now_node2->link != root) {
                TNode * now_link = now_node2->link;
                do {
                    if (now_link->is_list) {
                        int new_str = c - now_link->depth + 1;
                        for (auto i : now_link->num_in_pattern) {
                            if (new_str - i < 0)
                                break;
                            pos_entering[new_str - i]++;
                        }
                    }
                    now_link = now_link->link;
                } while (now_link != root);
            }
            // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            c++;
            if (c >= check.size()) {
                break;
            }
            //l++;
            now_node1 = now_node2;
            it = now_node1->child.find(check[c]);
        }
        if (c >= check.size()) {
            break;
        }
        if (now_node1 == root) {
            l++;
            c++;
        }
        else {
            now_node1 = now_node1->link;
            l = c - now_node1->depth;
        }

    } while (c < check.size());

    if (num_pattern_without_Joker != 0) {
        for (int j = 0; j < pos_entering.size(); j++) {
            if (num_pattern_without_Joker == pos_entering[j]) {
                // вывод пары
                cout << answer[j].first << " , " << answer[j].second << endl;
            }
        }
    }
    else {
        for (int j = 0; j < pos_entering.size(); j++) {
            if (num_Joker > pos_entering.size() - j)
                break;
            cout << answer[j].first << " , " << answer[j].second << endl;
        }
    }

}



int main()
{
    vector<std::pair<int, int> > answer;
    TTrie * trie = new TTrie;
    string enter;

    vector <unsigned long long> check;
    string word;
    //ifstream file("t3.txt");
    getline(cin, enter);
    std::stringstream patterns_string(enter);

    for (int i = 0; patterns_string >> enter; i++) {
        trie->patterns.push_back(enter);
    }

    trie->Make();

    int lineCnt = 1;
    int wordCnt = 1;

    for (/*int i = 0; i < 1 */; getline(cin, enter);/* ; i++*/) {
        //getline(cin, enter);
        std::stringstream check_stream(enter);
        for (; check_stream >> word;) {
            check.push_back(stoul(word));
            answer.push_back(std::make_pair(lineCnt, wordCnt));
            ++wordCnt;
        }
        wordCnt = 1;
        lineCnt++;
    }

    trie->Find_Occurrence(answer, check);

    return 0;
}
