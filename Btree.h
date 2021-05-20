#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
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
int get_value_from_char(char znak[MAX_INPUT_LENGTH], int poczatek)
{
    int result = 0, i = 0;
    while (znak[poczatek + i] >= 48 && znak[poczatek + i] <= 57)
    {
        result = result * 10 + (znak[poczatek + i] - 48);
        i++;
    }
    return result;
}

class Btree {
private:
    node* root;
    int height = 0;

public:
    Btree() {}
    node* getRoot() { return root; }
    void constr() { this->root = new node; }
    void remove(int value) {
    }
    void cache(){}
    void load(FILE* fptr) {
        this->root = new node;

        bool leaf;

        char chunk[128];
        fgets(chunk, sizeof(chunk), fptr);

        int h = 0;
        node *curr = this->root;


        int nh = 0;
        int z = 0;
        int maxh = 0;
        while (chunk[z] != '\0'){

            if (chunk[z] == '(') {
                nh++;
            }
            if (chunk[z] == ')') {
                nh--;
            }
            if (nh > maxh) maxh = nh;
            z++;
        }
        cout << " fh:" << maxh << endl;


            node** nodes = new node * [h]; //kazdy node  to inny level --> bedzie mozna wracac do poprzenich

            int b = 0;
            for (int i = 0; i < h; i++) {
               // nodes[i] = 
            }

            int j = 0;
            while (chunk[j] != '\0') {
                int t = 0;
                char act =' ';
                int temph = 0;
                int tempc = 0;
                while (t < j) {
                    act = chunk[t];

                    if (act == '(') {
                        nodes[temph] = curr;
                        
                        temph++;

                        
                    }
                    if (act == ')') {
                        temph--;
 
                    }
                    t++;
                }
                if (act != ' ') {
                    cout << " c:" << act << " ";
                    if (temph == h) leaf = true;
                    else leaf = false;

                    if (act >= 48 && act <= 57) {
                        
                        int val = get_value_from_char(chunk, t-1);
                        cout << "v:" << val << endl;
                        



                        while (val > 0) {
                            val /= 10;
                            j++;
                        }
                    }
                }

                j++;
            }


            //for (int a = 1; a <= height; a++) {
            //    //wpisz liczby
            //    while (chunk[k - 1] > 48 || chunk[k - 1] < 57 || chunk[k - 1] == ' ') {
            //        cout << chunk[k - 1];
            //        curr->key[k] = chunk[k] - 48;
            //        k++;
            //    }
            //    //cofnij sie do rodzica
            //    while (chunk[k - 1] < 48 || chunk[k - 1] > 57) {
            //        cout << chunk[k - 1];
            //        if (k > 1) curr->leaf = false;
            //        curr = root->child[k];
            //        k++;
            //    }

            //}
           





    }
    void save(node* curr) {
        cout << "( ";

        int i;
        for (i = 1; i <= curr->n; i++)
        {
            if (curr->leaf == false) 
                print(curr->child[i]);

            cout << curr->key[i] << " ";
        }

        if (curr->leaf == false) {
            print(curr->child[i]);
        }

        cout << ") ";
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

        this->print(root);
       
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

    void print(node* curr) {

        int i;
        for (i = 1; i <= curr->n; i++)
        {
            // If this is not leaf, then before printing key[i],
            // traverse the subtree rooted with child C[i].
            if (curr->leaf == false) {
                print(curr->child[i]);
            }
            cout << curr->key[i] << " ";
        }

        if (curr->leaf == false) {
            print(curr->child[i]);
        }

    }

}tree;




void insertandprint(int value, Btree* b) {
    b->insert(value);
    b->print(b->getRoot());
    cout << endl;
}

int get_value(int com_index);
bool get_command(int* com_index);
void do_command(int com_index, int value);



