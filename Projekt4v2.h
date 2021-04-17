#pragma once
#include "Projekt4v2functions.h"




class BTree {
public:
	int height = 0;
	node* root;


	void construct(int order) {
		cout << "CNS " << order << endl;
		treeOrder = order;
	}

	void add(int value) {
		cout << "ADD " << value << endl;

		if (root == NULL) {
			root = new node;
			root->keys[0] = value;
			root->amount = 1;
		}
		else {
			searchNodeToInsert(value, root, root);


		}

	}

	void search(int value) {
		cout << "SEA " << value << " ";
		if (searching(value, root))
			cout << "+";
		else
			cout << "-";
		cout << endl;

	}
	void print() {
		cout << "PRT" << endl;

	}
	void load(int value) {
		cout << "LAD " << value << endl;
	}
	void save() {
		cout << "SAV" << endl;
	}
	void remove(int value) {
		cout << "RMV " << value << endl;
	}
	void cache() {
		cout << "CCH" << endl;

		for (int i = 0; i < root->amount; i++)
			cout << root->keys[i] << " ";

		cout << endl << "children:\n";

		for (int i = 0; i < root->amount+1; i++) {
			for (int j = 0; j < root->children[i]->amount; j++)
				cout << root->children[i]->keys[j] << " ";
			cout << "  ";
		}
	}

}tree;

