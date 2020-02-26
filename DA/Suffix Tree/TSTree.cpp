//
// Created by yar on 27.06.19.
//
#include "TSTree.h"
#include <list>

TNode::TNode(std::string::iterator begin, std::string::iterator end, int num) {
    this->begin = begin;
    this->end = end;
    this->link = nullptr;
    number_string.insert(num);
}

/*
 find maximum length
 longest common substring
 */
void TSTree::FindNumMax(TNode * node, int walk) {
    if (node->number_string.size() == 2) {
        if(node != root) {
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

/*
 Find all longest
 substring
 */
void TSTree::FindLongestSubstrings(TNode *node, int walk, TNode *begin, std::vector <TNode *> path_to_sub) {
    if (node->number_string.size() == 2) {
        if(node != root) {

            if(walk == 0) {
                path_to_sub.clear();
            }
            path_to_sub.push_back(node);

            walk += distance(node->begin, node->end) + 1;
            if (walk == num_max_substring) {
                //ans.begining = begin;
                //ans.ending = node;
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

void TSTree::Find(TNode * node, int walk, TNode * begin) {
    if (node->number_string.size() == 2) {
        if(node != root) {

            if(walk == 0) {
                begin = node;
            }
            walk += distance(node->begin, node->end) + 1;
            if (walk > ans.length) { // may be >= !!!!
                ans.begining = begin;
                ans.length = walk;
                ans.ending = node;
            }
        }
        for (std::map<char, TNode *>::iterator it = node->child.begin(); it != node->child.end(); it++) {
            TNode *next_child = it->second;
            Find(next_child, walk, begin);
        }
    }
}

TSTree::TSTree(std::string n_str) {
    this->numStr = 1;
    this->str = n_str;
    this->activeEdge = str.begin();
    this->root = new TNode(str.end(), str.end(), numStr);
    this->root->link = root;
    this->activeNode = root;
    this->link = root;
    this->remaining = 0;
    this->activeLen = 0;

    for(std::string::iterator it = str.begin(); it != str.end(); it++) {
        Add(it);
        if(*it == '#') {
            numStr++;
        }
    }
    /*
    TreePrint();
    std::cout << "Complete\n";
     */
    ans.length = 0;
    num_max_substring = 0;
    //Find(root, 0, root);
    FindNumMax(root, 0);
    std::vector <TNode *> path_to_sub;
    FindLongestSubstrings(root, 0, root, path_to_sub);
    std::list <std::string> answer_string;
    for(int i = 0; i < answer.size();i++) {
        std::string a_string;
        for(int j = 0; j < answer[i].path_to_subs.size();j++) {
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
    /*
     if(ans.length != 0) {
        std::cout << "Answer is : \n";
        for(std::string::iterator it = ans.begining->begin; it != ans.ending->end + 1; it++) {
            std::cout << *it;
        }
        std::cout << std::endl;
    }
     */

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

        if(numStr == 2 && activeNode->number_string.size() == 1) {
            activeNode->number_string.insert(numStr);
        }

        if(it1 == activeNode->child.end()) {
            // Если из текущего activeNode нет пути по заданному символу создаем новую вершину
            TNode *n_node = new TNode(it, str.end(), numStr);
            activeNode->child[*activeEdge] = n_node;

            activeNode->number_string.insert(numStr);

            Sufflink(activeNode);
        }
        else {
            TNode * after = it1->second;
// Jump
            //int lenght = min(after->end, it + 1) - after->begin; // Вычисляет сколько надо прыгнуть символов на ребре
            int length = after->end - after->begin + 1;
            if (activeLen >= length) {
                activeEdge += length;
                activeLen -= length;
                activeNode = after;
                continue;
            }
            /*if(activeLen > after->end - after->begin) {
                std::map<char, TNode *>::iterator it2 = after->child.find(*activeEdge);
                if(it2 != after->child.end()) {
                    activeNode = after;
                    activeEdge = it2->second->begin;
                    activeLen -= (after->end - after->begin + 1);
                    break;
                }
                else {
                    std::cout << "ERROR" << std::endl;
                    // sozdat Vershinu
                }
                //Sufflink(activeNode);
                //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            }
            */
// Rule 3 extention
            if (*(after->begin + activeLen) == *it) {
                activeLen++;
                Sufflink(activeNode);
                //showstopper
                break;
            }

// Rule 2 extention
            TNode *split = new TNode(after->begin, after->begin + activeLen - 1, numStr); // ?????????
            TNode *leaf = new TNode(it, str.end(), numStr);
            activeNode->child[*activeEdge] = split;
            split->child[*it] = leaf;
            after->begin += activeLen;
            split->child[*after->begin] = after;

            activeNode->number_string.insert(numStr);

            split->number_string.insert(numStr);
            split->number_string.insert(*(after->number_string.begin()));

            Sufflink(split);

        }
        remaining--;
        if(activeNode == root && activeLen != 0){
            activeLen--;
            activeEdge++;
            //activeEdge = it - remaining + 1;
            /*
            std::string::iterator activeTest = activeEdge;
            activeTest++;
            if( activeTest != activeEdge)
                std::cout << "LOOOOOOSSSEEEEER" << std::endl;
            */
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
    //std:: cout << " node is " << node << " sufflink is " << node->suffixLink << std::endl;

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