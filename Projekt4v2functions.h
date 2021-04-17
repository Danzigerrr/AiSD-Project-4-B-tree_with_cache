#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

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

int treeOrder;

struct node {
	bool leaf = true;
	int *keys = new int[treeOrder];
	int amount = 0;
	node** children = new node*[treeOrder];
};


int get_value_from_char(char znak[MAX_INPUT_LENGTH], int poczatek);
int get_value(int value);
void get_command();
node* findParentOfNodeWithValue(int value, node* curr);
void insertValue(node* curr, int value, node* root);


bool searching(int value, node* curr) {

	for (int i = 0; i < curr->amount; i++) { //search in the current
		if (value == curr->keys[i])
			return true;
	}
	if (curr->leaf == true)
		return false;



	if (value < curr->keys[0]) {	//search left side
		cout << "lef ";
		searching(value, curr->children[0]);
	}

	else if (value > curr->keys[curr->amount - 1]) { //search right side
		cout << "rig ";
		searching(value, curr->children[curr->amount]);
	}

	else { //search in next node
		for (int i = 0; i < curr->amount; i++) {
			if (i != curr->amount - 1) {
				if (value > curr->keys[i] && value < curr->keys[i + 1]) {
					cout << "mid ";
					searching(value, curr->children[i + 1]);
				}
			}
		}
	}
}


bool searchInsideChildren(int value, node* curr) {
	for (int i = 0; i <= curr->amount; i++) {
		for (int j = 0; j < curr->amount-1; j++)
			if (value == curr->children[i]->keys[j])
				return true;
	}
	return false;
}


void searchNodeToInsert(int value, node* curr, node* root) {
	if (curr->leaf == false) {
		if (value < curr->keys[0]) {	//search left side
			cout << "lef ";
			searchNodeToInsert(value, curr->children[0], root);
		}

		else if (value > curr->keys[curr->amount - 1]) { //search right side
			cout << "rig ";
			searchNodeToInsert(value, curr->children[curr->amount], root);
		}

		else { //search in next node
			for (int i = 0; i < curr->amount; i++) {
				if (i != curr->amount - 1) {
					if (value > curr->keys[i] && value < curr->keys[i + 1]) {
						cout << "mid ";
						searchNodeToInsert(value, curr->children[i + 1], root);
					}
				}
			}
		}
	}
	else {
		insertValue(curr, value, root);
	}
}

void insertValue(node* curr, int value,node* root) {
	if (curr->amount < treeOrder && curr->leaf == true) { //dodawanie do aktualnego wezla, jeszcze jest wolne miejsce
		int i = curr->amount - 1;
		while (curr->keys[i] > value){
			curr->keys[i + 1] = curr->keys[i];
			i--;
			if (i < 0) break;
		}
		curr->keys[i + 1] = value;
		curr->amount++;
	}
	if (curr->amount == treeOrder) { // overflow, node is full
		if (true) {
			cout << "rozszerzenie: ";
			for (int i = 0; i < curr->amount; i++)
				cout << curr->keys[i] << " ";
			cout << endl;
		}

		int partitionIndex = curr->amount / 2;
		node* left = new node;
		node* right = new node;
		cout << "\nL= ";
		for (int i = 0; i < partitionIndex; i++) { //przepisywanie lewej czesci
			left->keys[i] = curr->keys[i];
			cout << curr->keys[i] << " ";
			left->amount++;
		}
		cout << "\nR= ";
		int j = 0;
		for (int i = 1 + partitionIndex; i < curr->amount; i++) { //przepisywanie prawej czesci
			right->keys[j] = curr->keys[i];
			cout << curr->keys[i] << " " ;
			right->amount++;
		}
		cout << endl;

		node* parent = findParentOfNodeWithValue(value, root);
		
		int i = parent->amount - 1;
		while (parent->keys[i] > curr->keys[partitionIndex]) {
			parent->keys[i + 1] = parent->keys[i];
			i--;
			if (i < 0) break;
		}
		parent->keys[i + 1] = curr->keys[partitionIndex];

		parent->children[parent->amount] = left;
		parent->amount++;
		parent->children[parent->amount] = right;

	}
}


node* findParentOfNodeWithValue(int value, node* curr) {
	
		if(curr->leaf == false)
		if (searchInsideChildren(value,curr))
			return curr;

		if (value < curr->keys[0]) {	//search left side
			cout << "lef ";
			findParentOfNodeWithValue(value, curr->children[0]);
		}

		else if (value > curr->keys[curr->amount - 1]) { //search right side
			cout << "rig ";
			findParentOfNodeWithValue(value, curr->children[curr->amount]);
		}

		else { //search in next node
			for (int i = 0; i < curr->amount; i++) {
				if (i != curr->amount - 1) {
					if (value > curr->keys[i] && value < curr->keys[i + 1]) {
						cout << "mid ";
						findParentOfNodeWithValue(value, curr->children[i + 1]);
					}
				}
			}
		}
}
