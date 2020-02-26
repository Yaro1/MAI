// RB_REAL_MY.cpp: определяет точку входа для консольного приложения.
//
//#define _CRT_SECURE_NO_WARNINGS

//#include "stdafx.h"
#include <iostream>
#include <cctype>
#include <cstring>
#include <iostream>
#include <fstream>

//#pragma warning(disable : 4996)

const short END = -1;

class TNode {
public:
    TNode() {};
    TNode(bool ecolor, unsigned long long int eval, char *ekey) {
        leftson = nullptr;
        rightson = nullptr;
        parent = nullptr;
        color = ecolor;
        value = eval;
        key = ekey;
    }
    ~TNode() {
        delete[] key;
        key = nullptr;
        parent = nullptr;
        leftson = nullptr;
        rightson = nullptr;
    }
    TNode * leftson;
    TNode * rightson;
    TNode * parent;
    bool color; // 0 == RED, 1 == BLACK
    char * key;
    unsigned long long int value;
};

class TRbTree {
public:
    TNode * root;
    TNode * nil;
    TRbTree() {
        nil = new TNode(1,0,nullptr);
        nil->color = 1;
        nil->key = 0;
        nil->leftson = nullptr;
        nil->rightson = nullptr;
        nil->value = 0;
        nil->parent = nullptr;
        root = nil;
    }

    void LeftRotate(TNode * x);
    void RightRotate(TNode * x);
    void Push(TNode * elem_new);
    void FixPush(TNode * current);
    void Print_Tree(TNode * p, int level);
    TNode * FindMin(TNode * current);
    TNode * Find(char * s);
    int Delete(TNode * z);
    void FixDelete(TNode * x);
    void Translplant(TNode *u, TNode * v);

    void Save(char * name);
    void Save(std::ofstream& output, TNode* root);
    void Reborn();
    void Load(char * name);
    void Load(std::ifstream& input, TNode *& root);

};

void TRbTree::Reborn() {
    root = nil;
    nil->parent = nullptr;
    nil->leftson = nullptr;
    nil->rightson = nullptr;
    nil->value = 0;
    nil->color = 1;
    nil->key = nullptr;
}

int TRbTree::Delete(TNode * z) {
    TNode * x = nullptr;
    TNode * y = z;
    bool cool_color = y->color;
    if (z->leftson == nil) {
        x = z->rightson;
        Translplant(z, z->rightson);
    }
    else if (z->rightson == nil) {
        x = z->leftson;
        Translplant(z, z->leftson);
    }
    else {
        y = FindMin(z->rightson);
        cool_color = y->color;
        x = y->rightson;
        if (y->parent == z) {
            x->parent = y;
        }
        else {
            Translplant(y,y->rightson);
            y->rightson = z->rightson;
            y->rightson->parent = y;
        }
        Translplant(z,y);
        y->leftson = z->leftson;
        y->leftson->parent = y;
        y->color = z->color;
    }
    if (cool_color == 1)
        FixDelete(x);
    delete z;
    return 0;
}


void TRbTree::FixDelete(TNode * x) {
    while (x != root && x->color == 1) {
        if (x == x->parent->leftson) {
            TNode * w = x->parent->rightson;
            if (w->color == 0) {
                w->color = 1;
                x->parent->color = 0;
                LeftRotate(x->parent);
                w = x->parent->rightson;
            }
            if (w->leftson->color == 1 && w->rightson->color == 1) {
                w->color = 0;
                x = x->parent;

            }
            else {
                if (w->rightson->color == 1) {
                    w->leftson->color = 1;
                    w->color = 0;
                    RightRotate(w);
                    w = x->parent->rightson;
                }
                w->color = x->parent->color;
                x->parent->color = 1;
                w->rightson->color = 1;
                LeftRotate(x->parent);
                x = root;
            }
        }
        else {
            TNode * w = x->parent->leftson;
            if (w->color == 0) {
                w->color = 1;
                x->parent->color = 0;
                RightRotate(x->parent);
                w = x->parent->leftson;
            }
            if (w->rightson->color == 1 && w->leftson->color == 1) {
                w->color = 0;
                x = x->parent;
            }
            else {
                if (w->leftson->color == 1) {
                    w->rightson->color = 1;
                    w->color = 0;
                    LeftRotate(w);
                    w = x->parent->leftson;
                }
                w->color = x->parent->color;
                x->parent->color = 1;
                w->leftson->color = 1;
                RightRotate(x->parent);
                x = root;
            }
        }
    }
    x->color = 1;
}

void TRbTree::Translplant(TNode *current, TNode * change) {
    if (current->parent == nil)
        root = change;
    else if (current == current->parent->leftson) {
        current->parent->leftson = change;
    }
    else {
        current->parent->rightson = change;
    }
    change->parent = current->parent;
}

TNode * TRbTree::Find(char *s) {
    TNode * current = root;
    while (current != nil) {
        if (strcmp(s, current->key) > 0) {
            current = current->rightson;
        }
        else if (strcmp(s, current->key) < 0){
            current = current->leftson;
        }
        else {
            return current;
        }
    }
    return nullptr;
}

TNode * TRbTree::FindMin(TNode * current) {

    while(current->leftson != nil) {
        current = current->leftson;
    }
    return current;
}


void TRbTree::Print_Tree(TNode * p, int level)
{
    if (p != nil)
    {
        std::cout << "P IS : " << p->key << "\n\n";
        //Print_Tree(p->leftson, level + 1);
        //for (int i = 0; i< level; i++) std::cout << "   ";

        //std::cout << p->key << " Color is : " << p->color << "   " << "NumSim is : " << strlen(p->key) << std::endl;
        //std::cout << " Color is : " << p->color << std::endl;

        //Print_Tree(p->rightson, level + 1);
    }
}

void TRbTree::LeftRotate(TNode * x) {
    TNode * y = x->rightson;
    x->rightson = y->leftson;
    if (y->leftson != nil) {
        y->leftson->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nil) {
        root = y;
    }
    else if (x == x->parent->leftson)
        x->parent->leftson = y;
    else
        x->parent->rightson = y;

    y->leftson = x;
    x->parent = y;
}

void TRbTree::RightRotate(TNode * x) {
    TNode * y = x->leftson;
    x->leftson = y->rightson;
    if (y->rightson != nil) {
        y->rightson->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nil) {
        root = y;
    }
    else if (x == x->parent->rightson)
        x->parent->rightson = y;
    else
        x->parent->leftson = y;

    y->rightson = x;
    x->parent = y;
}

void TRbTree::Push(TNode * elem_new) {
    TNode * prev = nil;
    TNode * current = root;
    while (current != nil) {
        prev = current;
        if (strcmp(elem_new->key, current->key) < 0) {
            current = current->leftson;
        }
        else {
            current = current->rightson;
        }
    }
    elem_new->parent = prev;
    if (prev == nil) {
        root = elem_new;
    }
    else if (strcmp(elem_new->key, prev->key) < 0) {
        prev->leftson = elem_new;
    }
    else {
        prev->rightson = elem_new;
    }
    elem_new->rightson = nil;
    elem_new->leftson = nil;
    elem_new->color = 0;
    FixPush(elem_new);
}

void TRbTree::FixPush(TNode * z) {
    while (z->parent->color == 0) {
        if (z->parent == z->parent->parent->leftson) {
            TNode * y = z->parent->parent->rightson;
            if (y->color == 0)
            {
                z->parent->color = 1;
                y->color = 1;
                z->parent->parent->color = 0;
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->rightson) {
                    z = z->parent;
                    LeftRotate(z);
                }
                z->parent->color = 1;
                z->parent->parent->color = 0;
                RightRotate(z->parent->parent);
            }
        }
        else {
            TNode * y = z->parent->parent->leftson;
            if (y->color == 0)
            {
                z->parent->color = 1;
                y->color = 1;
                z->parent->parent->color = 0;
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->leftson) {
                    z = z->parent;
                    RightRotate(z);
                }
                z->parent->color = 1;
                z->parent->parent->color = 0;
                LeftRotate(z->parent->parent);
            }
        }
    }
    root->color = 1;
}




void TRbTree::Save(char * name) {
std::ofstream output(name);
if (output.is_open()) {
    Save(output, this->root);
    std::cout << "OK\n";
}
else {
    std::cout << "ERROR: Couldn't create file\n";
}
output.close();
return;
}

void TRbTree::Save(std::ofstream &output, TNode* current) {
    if (current == nil) {
        output << END << " ";
        return;
    }
    output << current->key << " " << current->value << " " << current->color << " ";
    Save(output, current->leftson);
    Save(output, current->rightson);
    return;
}

void TRbTree::Load(char * name) {
    std::ifstream input(name);
    if (input.is_open()) {
        Reborn();
        Load(input, root);
        std::cout << "OK\n";
    }
    else {
        std::cout << "ERROR: Couldn't load file\n";
    }
    root->parent = nil;
    input.close(); //закрывает файлы функцией клоуз
    return;
}

void TRbTree::Load(std::ifstream& input, TNode *& current) {
    char buffer[257];
    unsigned long long int value = 0;
    bool color = 0;
    if (input.peek() == EOF || (input >> buffer && !strcmp(buffer, "-1"))) { //peek смотрит на следующий символ потока, но не берет его
        return;
    }

    input >> value >> color;
    char* tmpKey = new char[strlen(buffer) + 1];
    strcpy(tmpKey, buffer);

    current = new TNode(color, value, tmpKey);
    current->leftson = nil;
    current->rightson = nil;
    Load(input, current->leftson);
    Load(input, current->rightson);

    current->leftson->parent = current;
    current->rightson->parent = current;
    return;
}


int Test(TRbTree * tree) {
    char work;
    char simbol;
    char buff[257];
    std::ifstream fin("Test3.txt");
    for (int u = 0; fin >> work;u++) {
        if (u == 15) {
            std::cout << "\n\n\n";
        }
        if (work == '+' || work == '-' || work == '!') {

            if (work == '+' || work == '-') {
                if (work == '+') {
                    unsigned long long int value = 0;
                    int i = 0;
                    for (; 1; ) {
                        simbol = tolower(fin.get());
                        if (!isalpha(simbol) && simbol != ' ') {
                            break;
                        }
                        if (simbol != '\n' && simbol != ' ') {
                            buff[i] = simbol;
                            i++;
                        }
                    }
                    buff[i] = 0;


                    if (tree->Find(buff) != nullptr) {
                        std::cout << "Exist\n";

                        value = simbol - '0';
                        while (((simbol = fin.get()) != '\n') && simbol != -1) {
                            value = value * 10 + (simbol - '0');
                        }

                        continue;
                    }

                    char * key = new char[strlen(buff) + 1];
                    strcpy(key, buff);

                    value = simbol - '0';
                    while (((simbol = fin.get()) != '\n') && simbol != -1) {
                        value = value * 10 + (simbol - '0');
                    }

                    TNode * elem_new = new TNode(0, value, key);
                    tree->Push(elem_new);
                    std::cout << "OK\n";
                    //tree->Print_Tree(tree->root, 0);
                    //std::cout << "\n\n";
                }
                else {
                    int i = 0;
                    for (; 1; ) {
                        simbol = tolower(fin.get());
                        if (simbol == '\n' || simbol == EOF) {
                            break;
                        }
                        if (simbol != '\n' && simbol != ' ') {
                            buff[i] = simbol;
                            i++;
                        }
                    }
                    buff[i] = 0;

                    TNode * z = tree->Find(buff);
                    if (z == nullptr) {
                        std::cout << "NoSuchWord\n";
                        continue;
                    }
                    tree->Delete(z);

                    std::cout << "OK\n";
                    //tree->Print_Tree(tree->root, 0);
                    //std::cout << "\n\n";
                    continue;
                }
            }
            else { // if work == '!'
                char save_load[5];
                fin >> save_load;
                save_load[4] = 0;
                char path[256];
                int i = 0;
                for (; 1; ) {
                    simbol = fin.get();
                    if (simbol == '\n' || simbol == EOF) {
                        break;
                    }
                    if (simbol != '\n' && simbol != ' ') {
                        path[i] = simbol;
                        i++;
                    }
                }
                path[i] = 0;
                if (save_load[0] == 'S') {
                    tree->Save(path);
                }
                else {
                    tree->Load(path);
                }
            }
        }
        else {
            buff[0] = tolower(work);
            int i = 1;
            for (; 1; ) {
                simbol = tolower(fin.get());
                if (simbol == '\n' || simbol == EOF) {
                    break;
                }
                else {
                    buff[i] = simbol;
                    i++;
                }
            }
            buff[i] = 0;
            TNode * search = tree->Find(buff);
            if (search == nullptr) {
                std::cout << "NoSuchWord\n";
            }
            else {
                std::cout << "OK: " << search->value << "\n";
            }
        }
    }
    return 0;
}


int Work(TRbTree * tree) {
    char work;
    char simbol;
    char buff[257];
    while (std::cin >> work) {
        if (work == '+' || work == '-' || work == '!') {

            if (work == '+' || work == '-') {
                if (work == '+') {
                    unsigned long long int value = 0;
                    int i = 0;
                    for (; 1; ) {
                        simbol = tolower(std::cin.get());
                        if (!isalpha(simbol) && simbol != ' ') {
                            break;
                        }
                        if (simbol != '\n' && simbol != ' ') {
                            buff[i] = simbol;
                            i++;
                        }
                    }
                    buff[i] = 0;


                    if (tree->Find(buff) != nullptr) {
                        std::cout << "Exist\n";
                        value = simbol - '0';
                        while (((simbol = std::cin.get()) != '\n') && simbol != -1) {
                            value = value * 10 + (simbol - '0');
                        }
                        continue;
                    }

                    char * key = new char[strlen(buff) + 1];
                    strcpy(key, buff);

                    value = simbol - '0';
                    while (((simbol = std::cin.get()) != '\n') && simbol != -1) {
                        value = value * 10 + (simbol - '0');
                    }

                    TNode * elem_new = new TNode(0, value, key);
                    tree->Push(elem_new);
                    std::cout << "OK\n";
                }
                else {
                    int i = 0;
                    for (; 1; ) {
                        simbol = tolower(std::cin.get());
                        if (simbol == '\n' || simbol == EOF) {
                            break;
                        }
                        if (simbol != '\n' && simbol != ' ') {
                            buff[i] = simbol;
                            i++;
                        }
                    }
                    buff[i] = 0;

                    TNode * z = tree->Find(buff);
                    if (z == nullptr) {
                        std::cout << "NoSuchWord\n";
                        continue;
                    }
                    tree->Delete(z);

                    std::cout << "OK\n";
                    continue;
                }
            }
            else { // if work == '!'
                char save_load[5];
                std::cin >> save_load;
                save_load[4] = 0;
                char path[256];
                int i = 0;
                for (; 1; ) {
                    simbol = std::cin.get();
                    if (simbol == '\n' || simbol == EOF) {
                        break;
                    }
                    if (simbol != '\n' && simbol != ' ') {
                        path[i] = simbol;
                        i++;
                    }
                }
                path[i] = 0;
                if (save_load[0] == 'S') {
                    tree->Save(path);
                }
                else {
                    tree->Load(path);
                }
            }
        }
        else {
            buff[0] = tolower(work);
            int i = 1;
            for (; 1; ) {
                simbol = tolower(std::cin.get());
                if (simbol == '\n' || simbol == EOF) {
                    break;
                }
                else {
                    buff[i] = simbol;
                    i++;
                }
            }
            buff[i] = 0;
            TNode * search = tree->Find(buff);
            if (search == nullptr) {
                std::cout << "NoSuchWord\n";
            }
            else {
                std::cout << "OK: " << search->value << "\n";
            }
        }
    }
    return 0;
}

int main()
{
    TRbTree *tree = new TRbTree;
    //Test(tree);
    Work(tree);
    //tree->Print_Tree(tree->root, 0);
    delete tree;
    return 0;
}


