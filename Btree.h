#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
//algorithms implentation is based on Cormen Itruduction to Algorithms Third Edition
int order;
#define MIN_DEGREE 2
#define MIN_ORDER MIN_DEGREE

#define MIN_NUM_OF_KEYS_IN_ROOT 1
#define MIN_NUM_OF_CHILDS_IN_ROOT 2

#define MIN_NUM_OF_KEYS (order-1)
#define MIN_NUM_OF_CHILDS order

#define MAX_NUM_OF_KEYS (2 * order - 1)
#define MAX_NUM_OF_CHILDS (2*order)

#define MAX_INPUT_LENGTH 50
#define COM_COUNT 13
#define COM_LENGTH 20

enum Commands {
    CONSTRUCT,
    ADD,
    SEARCH,
    PRINT,
    LOAD,
    SAVE,
    REMOVE,
    IGNORE,
    END,
    CACHE
};

struct node {
    int n = 0;
    bool leaf = true;
    int* key = new int[MAX_NUM_OF_KEYS];
    node** child = new node * [MAX_NUM_OF_CHILDS];

};


class Btree {
private:
    node* root;
    int height = 0;

public:
    void remove(int value) {
    }
    void load() {

    }
    void save() {

    }
    void cache(){}

    node* getRoot() { return root; }
    Btree() {   }
    void constr() {
        root = new node;
    }

    bool search(node* curr, int value) {
        int i = 1;

        while (i <= curr->n && value > curr->key[i])
            i++;

        if (i <= curr->n && value == curr->key[i]) {
            cout << "\nSuccess: " << value << " was found!";
            return true;
        }

        else if (curr->leaf == true) {
            cout << "\nFailure: " << value << " was NOT found!";
            return false;
        }

        else
            return search(curr->child[i], value);
    }

    void splitChild(node* parent, int i) {
        node* z = new node;
        node* y = parent->child[i];
        z->leaf = y->leaf;
        z->n = order - 1;

        for (int j = 1; j <= z->n; j++) //najwieksze klucze ida do Z
            z->key[j] = y->key[j + order];

        if (y->leaf == false)
            for (int j = 1; j <= order; j++) //jesli Y ma dzieci, przepisz je do Z
                z->child[j] = y->child[j + order];

        y->n = order - 1; //polowa maksymalnej ilosci kluczy

        for (int j = parent->n + 1; j >= i + 1; j--) //robienie miejsce dla srodkowego klucza z Y
            parent->child[j + 1] = parent->child[j];

        parent->child[i + 1] = z;//prawym dzieckiem srodkowego klucza z Y jest Z

        for (int j = parent->n; j >= i; j--) //robienie miejsce dla srodkowego klucza z Y
            parent->key[j + 1] = parent->key[j];

        parent->key[i] = y->key[order]; // srodkowy klucz z Y idzie do Parent
        parent->n += 1; //ilosc kluczy w Parent sie zwiekszyla

       /* cout << endl;
        for (int k = 1; k <= y->n; k++)
            cout << "Y " << y->key[k] << " ";
        cout << endl;

        for (int k = 1; k <= parent->n; k++)
            cout << "parent " << parent->key[k] << " ";
        cout << endl;

        for (int k = 1; k <= z->n; k++)
            cout << "Z " << z->key[k] << " ";
        cout << endl;

        cout << parent->leaf << endl;*/

    }

    void insert(int value) {
        if (root->n == MAX_NUM_OF_KEYS) {
            //cout << root->leaf;
            node* s = new node;

            s->leaf = false;
            s->child[1] = root;
            //cout << root->leaf;
            splitChild(s, 1);
            insertNonFull(s, value);
            root = s;
        }
        else
            insertNonFull(root, value);

        this->InOrderPrint(root);
       
    }

    void insertNonFull(node* curr, int value) {
        int i = curr->n;
        if (curr->leaf == true) {
            while (i >= 1 && value < curr->key[i]) {
                curr->key[i + 1] = curr->key[i];
                i--;
            }
            curr->key[i + 1] = value;
            curr->n++;

            /* cout << "node: ";
             for (int i = 1; i <= curr->n; i++)
                cout << curr->key[i] << " ";
             cout << endl;
             */
        }
        else {
            while (i >= 1 && value < curr->key[i])
                i--;
            i++;
            if (curr->child[i]->n == MAX_NUM_OF_KEYS) {
                splitChild(curr, i);
                if (value > curr->key[i])
                    i++;
            }
            insertNonFull(curr->child[i], value);
        }
    }
    void insertNonFullRec(node* curr, int value) //not sure if it works
    {
        int i = curr->n;
        while (curr->leaf == false) {
            while (i >= 1 && value < curr->key[i])
                i--;
            i++;
            if (curr->child[i]->n == MAX_NUM_OF_KEYS) {
                splitChild(curr, i);
                if (value > curr->key[i])
                    i++;
            }
            insertNonFull(curr->child[i], value);
        }

        while (i >= 1 && value < curr->key[i]) {
            curr->key[i + 1] = curr->key[i];
            i--;
        }
        curr->key[i + 1] = value;
        curr->n += 1;

    }

    void InOrderPrint(node* curr) {
        cout << "( ";
        int i;
        for (i = 1; i <= curr->n; i++)
        {
            // If this is not leaf, then before printing key[i],
            // traverse the subtree rooted with child C[i].
            if (curr->leaf == false) {
                InOrderPrint(curr->child[i]);
            }
            cout << curr->key[i] << " ";
        }


        if (curr->leaf == false) {
            InOrderPrint(curr->child[i]);
        }
        cout << ") ";

    }

}tree;




void insertandprint(int value, Btree* b) {
    b->insert(value);
    b->InOrderPrint(b->getRoot());
    cout << endl;
}

int get_value(int com_index);
bool get_command(int* com_index);
void do_command(int com_index, int value);



