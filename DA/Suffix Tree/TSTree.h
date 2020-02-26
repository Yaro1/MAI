//
// Created by yar on 27.06.19.
//

#ifndef UKKOMEM_MY_TSTREE_H
#define UKKOMEM_MY_TSTREE_H

#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <vector>
#include <set>

class TNode
{
public:
    std::map<char, TNode *> child;
    std::string::iterator begin, end;
    TNode *link;
    std::set <int> number_string;
   // std::vector <int> number_string;
    TNode(std::string::iterator begin, std::string::iterator end, int num);
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
    TNode *root, * activeNode, * link;
    int numStr;
    int remaining, activeLen;

    int num_max_substring;
    std::vector <LCS> answer;
   // std::vector <TNode *> path_to_sub; // path to next substring
    LCS ans; // prev version (with only one substring)

    std::string::iterator activeEdge;
    TSTree(std::string n_str);
    ~TSTree() {};
    void Destroy(TNode *node);
    void Sufflink(TNode *node);
    void Add(std::string::iterator it);
    void NodePrint(TNode *node, int dpth);
    void TreePrint();
    void Find(TNode * node, int walk, TNode * begin);
    void FindNumMax(TNode * node, int walk);
    void FindLongestSubstrings(TNode * node, int walk, TNode * begin, std::vector <TNode *> path_to_sub);
};
#endif //UKKOMEM_MY_TSTREE_H
