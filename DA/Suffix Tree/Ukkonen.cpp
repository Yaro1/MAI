// yar.cpp : Defines the entry point for the console application.
//


#if 1
//
// Created by yar on 26.08.2019.
//


#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <vector>
#include <set>
#include <list>
#include <iostream>
#include <cstdlib>
#include <string>
#include <map>
#include <fstream>
#include <ctime>   

using std::cin;
using std::cout;
using std::map;
using std::string;

class TNode
{
public:
    std::map<char, TNode *> child;
    std::string::iterator begin, end;
    TNode *link;
    std::set <int> number_string;
    TNode(std::string::iterator begin, std::string::iterator end);
    ~TNode() {};
};

struct LCS{ // longest common substring
    int length;
    std::vector <TNode *> path_to_subs;
    TNode * ending;
    TNode * begining;
};


class TSTree {
public:
    std::string str;
    std::string str2;
    TNode * root, * activeNode, * link;
    int numStr;
    int remaining, activeLen;

    int num_max_substring;
    std::vector <LCS> answer;
    LCS ans; // prev version (with only one substring)

    std::string::iterator activeEdge;
    TSTree(std::string n_str, std::string n_str2);
    ~TSTree() {};
    void Destroy(TNode *node);
    void Sufflink(TNode *node);
    void Add(std::string::iterator it);
    void NodePrint(TNode *node, int dpth);
    void TreePrint();
    int Markup(TNode * node);
    void FindNumMax(TNode * node, int walk);
    void FindLongestSubstrings(TNode * node, int walk, TNode * begin, std::vector <TNode *> path_to_sub);
};

TNode::TNode(std::string::iterator begin, std::string::iterator end) {
    this->begin = begin;
    this->end = end;
    this->link = nullptr;
}
// SAW


void TSTree::FindNumMax(TNode * node, int walk) {
    if (node->number_string.size() == 2) {
        if (node != root) {
            walk += distance(node->begin, node->end) + 1;
            if (walk > num_max_substring) {
                num_max_substring = walk;
            }
        }
        for (std::map<char, TNode *>::iterator it = node->child.begin(); it != node->child.end(); it++) {
            TNode *next_child = it->second;
            FindNumMax(next_child, walk);
        }
    }
}


void TSTree::FindLongestSubstrings(TNode *node, int walk, TNode *begin, std::vector <TNode *> path_to_sub) {
    if (node->number_string.size() == 2) {
        if(node != root) {

            if(walk == 0) {
                path_to_sub.clear();
            }
            path_to_sub.push_back(node);

            walk += distance(node->begin, node->end) + 1;
            if (walk == num_max_substring) {
                ans.path_to_subs = path_to_sub;
                ans.length = walk;
                answer.push_back(ans);
                path_to_sub.clear();
            }
        }
        for (std::map<char, TNode *>::iterator it = node->child.begin(); it != node->child.end(); it++) {
            TNode *next_child = it->second;
            FindLongestSubstrings(next_child, walk, begin, path_to_sub);
        }
    }
}


int TSTree::Markup(TNode * node) {
	if(node->begin != str.end()) {
		if(*node->begin == '#')
			node->number_string.insert(1);
		else if(*node->begin == '$')
			node->number_string.insert(2);
	}
    if(distance(node->begin, node->end) > 0) {
        int size_str = str2.size();
        if(distance(node->begin, node->end) > size_str)
            node->number_string.insert(1);
        else if(node->end == str.end())
				node->number_string.insert(2);
    }


    for (std::map<char, TNode *>::iterator it2 = node->child.begin(); it2 != node->child.end(); it2++) {
        TNode *next_child = it2->second;
        int ans = Markup(next_child);
        if (node->number_string.size() < 2) {
            if (ans == 3) {
                node->number_string.insert(1);
                node->number_string.insert(2);
            }
            if (ans == 1) {
                node->number_string.insert(1);
            }
            if (ans == 2) {
                node->number_string.insert(2);
            }
        }
    }
    if(node->number_string.size() == 2) {
        return 3;
    }
	if(node->number_string.size() == 1) {
		if(*node->number_string.begin() == 1) {
			return 1;
		}
	    if(*node->number_string.begin() == 2) {
		    return 2;
		}
	}
    return 0;

}
// SAW
TSTree::TSTree(std::string n_str, std::string n_str2) {
    this->str2 = n_str2;
    this->ans.begining = nullptr;
    this->ans.ending = nullptr;
    this->numStr = 1;
    this->str = n_str;
    this->activeEdge = str.begin();
    this->root = new TNode(str.end(), str.end());
    this->root->link = this->root;
    this->activeNode = this->root;
    this->link = this->root;
    this->remaining = 0;
    this->activeLen = 0;
    this->ans.length = 0;
    this->num_max_substring = 0;

    for(std::string::iterator it = str.begin(); it != str.end(); it++) {
        Add(it);
        if(*it == '#') {
            numStr++;
        }
    }
    Markup(root);
    FindNumMax(root, 0);
    std::vector <TNode *> path_to_sub;
    FindLongestSubstrings(root, 0, root, path_to_sub);
    std::list <std::string> answer_string;

    int size_answer = answer.size();
    for(int i = 0; i < size_answer;i++) {
        std::string a_string;
        int size_answer_path_to_subs = answer[i].path_to_subs.size();
        for(int j = 0; j < size_answer_path_to_subs;j++) {
            std::string next_string(answer[i].path_to_subs[j]->begin,answer[i].path_to_subs[j]->end + 1);
            a_string += next_string;
        }
        answer_string.push_back(a_string);
    }

    answer_string.sort();
    std::cout << num_max_substring << std::endl;
    for(auto i = answer_string.begin(); i != answer_string.end();i++){
        std::cout << *i << std::endl;
    }
	

}

void TSTree::Add(std::string::iterator it) {
    link = root;
    remaining++;
    while(remaining) {
        if (!activeLen) {
            // if activeLen is zero, we check is есть ли путь с такими данными
            activeEdge = it;
        }
        std::map<char, TNode *>::iterator it1 = activeNode->child.find(*activeEdge);


        if(it1 == activeNode->child.end()) {
            // Если из текущего activeNode нет пути по заданному символу создаем новую вершину
            TNode *n_node = new TNode(it, str.end());
            activeNode->child[*activeEdge] = n_node;
            Sufflink(activeNode);
        }
        else {
            TNode * after = it1->second;
// Jump
            int length = after->end - after->begin + 1;
            if (activeLen >= length) {
                activeEdge += length;

                if(activeEdge == str.end()) {  // TEST
                    cout << "ERROR" << std::endl;
                    int err;
                    cin >> err;
                }

                activeLen -= length;

                if(activeLen < 0) { // TEST
                    cout << "ERROR" << std::endl;
                    int err;
                    cin >> err;
                }

                activeNode = after;
                continue;
            }
// Rule 3 extention
            if( ( (after->begin + activeLen) == str.end() ) && it == str.end() ) { // TEST
                cout << "ERROR" << std::endl;
                int err;
                cin >> err;

                activeLen++;
                Sufflink(activeNode);
                //showstopper
                break;
            }
            else {
                if (*(after->begin + activeLen) == *it) {
                    activeLen++;
                    Sufflink(activeNode);
                    //showstopper
                    break;
                }
            }

// Rule 2 extention
            TNode *split = new TNode(after->begin, after->begin + activeLen - 1);
            TNode *leaf = new TNode(it, str.end());
            activeNode->child[*activeEdge] = split;
            split->child[*it] = leaf;
            after->begin += activeLen;
            split->child[*after->begin] = after;


            Sufflink(split);

        }
        remaining--;
        if(activeNode == root && activeLen != 0){
            activeLen--;

            if(activeLen < 0) { // TEST
                cout << "ERROR" << std::endl;
                int err;
                cin >> err;
            }

            activeEdge++;

            if(activeEdge == str.end()) { // TEST
                cout << "ERROR" << std::endl;
                int err;
                cin >> err;
            }

        }
        else {
            if(activeNode->link)
                activeNode = activeNode->link;
            else
                activeNode = root;
        }

    }
}

void TSTree::NodePrint(TNode *node, int dpth)
{
    for (int i = 0; i < dpth; ++i) {
        putchar('\t');
    }

    std::cout << "node represents: ";
    for (std::string::iterator str = node->begin; str <= node->end; ++str) {
        std::cout << *str;
    }
    std::cout << std::endl;

    for (std::map<char, TNode *>::iterator it = node->child.begin(); it != node->child.end(); ++it) {
        NodePrint(it->second, dpth + 1);
    }
}



void TSTree::TreePrint()
{
    NodePrint(root, 0);
}

void TSTree::Sufflink(TNode *node)
{
    if (link != root)
        link->link = node;
    link = node;
}

void TSTree::Destroy(TNode *node)
{
    for (std::map<char, TNode *>::iterator it = node->child.begin(); it != node->child.end(); ++it) {
        Destroy(it->second);
    }
    delete node;
}

int main(){
    std::string str1, str2;
    while(cin >> str1 >> str2) {
	srand(time(0))
        str1 += "#";
        str2 += "$";
        str1 += str2;
        TSTree tree(str1, str2);
        tree.Destroy(tree.root);
	cout << "runtime = " << clock()/1000.0 << endl; // время работы программы  
    }

    return 0;
}
#endif

