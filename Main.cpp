#include "AVL_Tree.h"
#include"REDBLACK.h"
#include"LIST.h"
#include "BTrees.h"

#include <iostream>
#include <Windows.h>
#include <stdlib.h>

using namespace std;

bool Ask_tree_on_hardisk();
int Show_Operations();
bool Goodbye();


int main() {
	HANDLE cout_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(cout_handle, FOREGROUND_GREEN); // set color text to green
	int tree = 0; // AVL == 1, B-Tree == 2, RB-Tree == 3
START:
	cout << "#############################################" << endl;
	cout << "---------------WELCOME TO DSDB---------------" << endl;
	cout << "#############################################" << endl;
	cout << endl;

TreeInput:
	cout << "Please Select A tree from Below" << endl;
	cout << "1. AVL TREE" << endl;
	cout << "2. B-TREE" << endl;
	cout << "3. RB-TREE" << endl; // red black
	cout << endl;

	cin >> tree; // option input

	bool Tree_on_HDD; // check wether tree is stored on hardisk or not
	int operation;
	//################## AVL TREES ################################################
	if (tree == 1) { //AVL
		Tree_on_HDD = Ask_tree_on_hardisk();

		if (!Tree_on_HDD)
		{ // if tree not stored, then read and store it in HDD, 
			StoreAVLTree(); // here user will also ask about the indexing method, for the tree to be stored, i.e year,id etc
		}

		cout << endl;
	operation_input:
		operation = Show_Operations(); // get user operation input

		if (operation == 1) {
			AVL_POINT_SEARCH();
		}
		else if (operation == 2) {
			AVL_RANGE_SEARCH();
		}
		else if (operation == 3) {
			AVL_UPDATE();
		}
		else if (operation == 4) {
			AVL_DELETE();
		}
		else if (operation == 5) {
			AVL_WHERE();
		}

		else { // invalid operation
			system("CLS"); // clear terminal Screen
			cout << "INVALID INPUT, Please Try Again" << endl << endl;
			goto operation_input;
		}
	}
	//################## B TREES ################################################
	else if (tree == 2) { // B TREE
		Tree_on_HDD = Ask_tree_on_hardisk();

		if (!Tree_on_HDD) { // if tree not stored, then read and store it in HDD, 
			//StoreBTree();
		}

		operation = Show_Operations(); // get user operation input
	}
	//################## REDBLACK TREES ################################################
	else if (tree == 3)
	{ // RED BLACK


		Tree_on_HDD = Ask_tree_on_hardisk();

		if (!Tree_on_HDD)
		{ // if tree not stored, then read and store it in HDD, 
			StoreRBTree();
		}

		operation = Show_Operations(); // get user operation input
		if (operation == 1) {
			REDBLACK_POINT_SEARCH();
		}
		else if (operation == 2) {
			REDBLACK_RANGE_SEARCH();
		}
		else if (operation == 3) {
			REDBLACK_UPDATE();
		}
		else if (operation == 4) {
			REDBLACK_DELETE();
		}
		else if (operation == 5) {
			REDBLACK_WHERE();
		}
		else
		{ // invalid operation
			system("CLS"); // clear terminal Screen
			cout << "INVALID INPUT, Please Try Again" << endl << endl;
			goto operation_input;
		}
		operation = Show_Operations(); // get user operation input

		// add your functions here
	}
	else {
		system("CLS"); // clear terminal Screen
		cout << "INVALID INPUT, Please Try Again" << endl << endl;
		goto TreeInput;
	}


END:
	if (Goodbye()) {
		return 0; // Terminate Program
	}
	else {
		goto START;
	}
}

bool Ask_tree_on_hardisk() { // ask user if store is stored or not
	bool option = false;
	cout << "Is This Tree Stored On HDD ?" << endl;
	cout << "1. Yes" << endl;
	cout << "0. No" << endl;
	cin >> option;
	return option;
}

int Show_Operations() { // prints all available options to users
	cout << "Please Specify an option Below" << endl;
	cout << "1. Point Search" << endl;
	cout << "2. Range Search" << endl;
	cout << "3. Update Field" << endl; // update the whole row of key searched
	cout << "4. Delete Key" << endl; // will Delete all the rows having the key user wants to delete
	cout << "5. Where field=value..." << endl; // Bonus Part
	int option;
	cin >> option;
	return option;
}

bool Goodbye() {
	cout << "Do You Wish to Exit ?" << endl;
	cout << "1. Yes" << endl;
	cout << "0. No" << endl;
	bool option;
	cin >> option;
	return option;
}
