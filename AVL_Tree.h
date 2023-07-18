#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <filesystem>
#include <direct.h>
#include <limits.h>
#include <cstring>
#include <string>

using namespace std;

int askfilename();
template <typename T>
struct node;
template <typename T>
class AVL;
template <typename T>
void AVL_NODE_STORE(string filename,AVL<T>& tree, node<T>* root, int type, string folder);

template <typename T>
void ReadFromFile_int(string filename, AVL<T>& tree, int type) {
	// File pointer
	fstream fin;
	cout << filename << endl;
	//node<T>* root = NULL; // will be used for in insertion, deletion

	// Open an existing file
	fin.open(filename, ios::in); // input mode

	// Read the Data from the file
	// as String Vector
	vector<string> row;

	string line, word, temp;

	int count = 0; // will help in keeping track of whether first row was read or not

	while (!fin.eof()) { // read till end of file

		row.clear();

		// read an entire row and
		// store it in a string variable 'line'
		getline(fin, line);
		if (line == "") {
			break;
		}
		// used for breaking words
		stringstream s(line);

		// read every column data of a row and
		// store it in a string variable, 'word'
		while (getline(s, word, ',')) {

			// add all the column data
			// of a row to a vector
			row.push_back(word);
		}

		if (count == 0) { // ignore 1st row of csv
			//continue;
		}
		// reading from 2nd row in .csv
		else {
			// type -1 = specifies index on which tree is to be made
			 // start i from 1 ignoring first column
			if  (type < 3) {
				int i = type - 1;
				tree.root = tree.insert(tree.root, stoi(row[i]), count + 1); // row of 0 will always contain, ID

			}
			else if (type > 3) {
				int i = type;
				if (type == 6) { // float 
					tree.root = tree.insert(tree.root, stof(row[i]), count + 1); // row of 0 will always contain, ID
				}
				else {
					tree.root = tree.insert(tree.root, stoi(row[i]), count + 1); // row of 0 will always contain, ID
				}
			
			}
			// count == line number	
		}


		count++;
		//}
	}

	tree.PreOrderTraversal(tree.root);
}


template <typename T>
void ReadFromFile_string(string filename, AVL<T>& tree, int type) {
	// File pointer
	fstream fin;

	node<T>* root = NULL; // will be used for in insertion, deletion

	// Open an existing file
	fin.open(filename, ios::in); // input mode

	// Read the Data from the file
	// as String Vector
	vector<string> row;

	string line, word, temp;

	int count = 0; // will help in keeping track of whether first row was read or not

	while (!fin.eof()) { // read till end of file

		row.clear();

		// read an entire row and
		// store it in a string variable 'line'
		getline(fin, line);
		if (line == "") {
			break;
		}
		// used for breaking words
		stringstream s(line);

		// read every column data of a row and
		// store it in a string variable, 'word'
		while (getline(s, word, ',')) {

			// add all the column data
			// of a row to a vector
			row.push_back(word);
		}

		if (count == 0) { // ignore 1st row of csv

		}
		// reading from 2nd row in .csv
		else {
			// type -1 = specifies index on which tree is to be made
			 // start i from 1 ignoring first column
			
			if (type >= 3) {
				// add conditons
				int i = type;
				//string string_key = row[i];
				tree.root = tree.insert(tree.root, row[i], count + 1); // row of 0 will always contain, ID

			}
			// count == line number	
		}


		count++;
		//}
	}
	tree.PreOrderTraversal(tree.root);
}



fstream& GotoLine(fstream& file, unsigned int num) {
	file.seekg(ios::beg);
	for (int i = 0; i < num - 1; ++i) {
		file.ignore(numeric_limits < streamsize>::max(), '\n'); // ignore the max characters in line and loop will continue till user specified line number
	}
	return file;
}

template <typename T> string tostr(const T& t) {
	ostringstream os;
	os << t;
	return os.str();
}

template <typename T>
void AVL_NODE_STORE(string filename,AVL<T>& tree, node<T>* root, int type , string folder) {

	node<T>* temp = root;
	string key_fname="";
	string thefilename = "";

	if (temp != nullptr)
	{

		thefilename.clear();
		//cout << "-->" << "ID: " << temp->key << endl;
		// 
		// make a txt file here with key name
		// 
		// Create and open a text file
		key_fname.clear();
	
			key_fname = tostr(temp->key) ; // / / / 1.txt

		thefilename = folder + key_fname + ".txt";

		ofstream MyFile(thefilename);

		//////////////////////////////////////// Write to the file
		// File pointer
		fstream file(filename);

		node<T>* root = NULL; // will be used for in insertion, deletion

		// Open an existing file
		//fin.open(filename, ios::in); // input mode

		GotoLine(file, temp->line);

		string line;

		getline(file, line);
		
		//////////////
		MyFile << line; // write to newly createdd file
		// Read the Data from the file
		// as String Vector
		
		file.close();
		///////////////////////////////////////
		
		// Close the file
		MyFile.close();
		thefilename.clear();
		AVL_NODE_STORE(filename, tree, temp->left, type, folder);
		AVL_NODE_STORE(filename, tree, temp->right, type, folder);
	}

}

template <typename T>
void STORE_AVL(string filename, AVL<T>&tree, int type) {
	_mkdir("AVL_TREE"); // create folder

	string path="";

	if (type == 1) {
		_mkdir("AVL_TREE/AVL_ID"); // create sub_folder
		path = "AVL_TREE/AVL_ID/";
	}
	else if (type == 2) {
		_mkdir("AVL_TREE/AVL_YEAR"); // create sub_folder
		path = "AVL_TREE/AVL_YEAR/";
	}
	else if(type == 3) {
		_mkdir("AVL_TREE/AVL_CAUSE_NAME"); // create sub_folder
		path = "AVL_TREE/AVL_CAUSE_NAME/";
	}
	else if(type == 4) {
		_mkdir("AVL_TREE/AVL_STATE"); // create sub_folder
		path = "AVL_TREE/AVL_STATE/";
	}
	else if(type == 5) {
		_mkdir("AVL_TREE/AVL_DEATHS"); // create sub_folder
		path = "AVL_TREE/AVL_DEATHS/";
	}
	else if(type == 6) {
		_mkdir("AVL_TREE/AVL_DEATH_RATE"); // create sub_folder
		path = "AVL_TREE/AVL_DEATH_RATE/";
	}


	AVL_NODE_STORE(filename,tree,tree.root, type, path);

}

//#####################################################################
//----------------------------------------------------------------------

template <typename T>
struct node {

	T key; // key, 2016
	int line;
	//----------------------------------------------
	int height; // keeps track of a node height at particular level
	node* left; // left child
	node* right; // right child

};

template <typename T>
class AVL {

public:
	node<T>* root;
	
public:

	AVL(); // Default Constructor
	int height(node<T>* N); // getter for a node's height
	int max(int a, int b); // compares 2 height values, and returns the greater one
	bool isEmpty(); // Checks whether the AVL tree is empty or not
	node<T>* thenewnode(T data ,int); // makes and returns a node that has default values, height =0, data =0, left right are null
	node<T>* insert(node<T>* node1, T data, int); // insert a node into the AVL tree, will automatically add to left or right sub tree and balance it
	bool retrieve(T d); // d == data, searches for the value inside AVL tree and returns 1 if it is found
	void PreOrderTraversal(node<T>* r); // r == root node, Prints The AVL tree in Pre-Order Traversal 

	int GetBalanceFactor(node<T>* N); // subtracts the height of left and right child , and returns its value as balance factor
	//of the node passed in the argument

	void update_height(node<T>* node, int height); // Setter to update a node's Height

	node<T>* RotRight(node<T>* y); // Perform Single Right Rotation
	node<T>* RotLeft(node<T>* x); //Perform Single Left Rotation
	node<T>* nodeWithMimumValue(node<T>* node1); // Return a node from the left-most sub tree that will basically have the minimum in the whole AVL Tree
	node<T>* DoubleRotateWithLeft(node<T>* K3); // Perform L-R Rotatiom
	node<T>* DoubleRotateWithRight(node<T>* K3); // Perform R-L Rotation

	node<T>* deleteNode(node<T>* root, T key); // Searches for the Key in AVL tree, if founf , that Node is Deleted and the Tree is AutoBalanced, by checking
	// Balance Factors when going up through the Recursion

	void StoreAVLTree(); // reads from file and stores Tree on HDD
	void AVL_POINT_SEARCH();
	void AVL_RANGE_SEARCH();
	void AVL_UPDATE();
	void AVL_DELETE();
	void AVL_WHERE();
};

template <class T>
AVL<T>::AVL() {
	root = NULL;
}

template <class T>
int AVL<T>::height(node<T>* N) {
	if (N == NULL)
		return 0;
	return N->height;
}
template <class T>
int AVL<T>::max(int a, int b) {
	if (a > b) {
		return a;
	}
	else {
		return b;
	}
	
}
template <class T>
bool AVL<T>::isEmpty() {
	if (root == NULL) {
		return true;
	}
	else
		return false;
}
template <class T>
node<T>* AVL<T>::thenewnode(T datalol, int line_number ) {
	node<T>* newnode = new node<T>;
	newnode->key = datalol;
	
	newnode->height = 0;
	newnode->left = NULL;
	newnode->right = NULL;
	newnode->line = line_number;
	return newnode;
}
template <class T>
node<T>* AVL<T>::insert(node<T>* node1, T data, int line_number) {


	// Find the correct postion and insert the node
	if (node1 == NULL)
		return (thenewnode(data,line_number));
	if (data < node1-> key )
		node1->left = insert(node1->left, data, line_number);
	else if (data > node1->key)
		node1->right = insert(node1->right, data , line_number);
	else
		return node1;


	// Update the balance factor of each node and
	// balance the tree
	node1->height = 1 + max(height(node1->left),
		height(node1->right));
	int balanceFactor = GetBalanceFactor(node1); 
	if (balanceFactor > 1) {
		if (data < node1->left->key) {
			return RotRight(node1);
		}
		else if (data > node1->left->key) {
			node1->left = RotLeft(node1->left);
			return RotRight(node1);
		}
	}
	if (balanceFactor < -1) {
		if (data > node1->right->key) {
			return RotLeft(node1);
		}
		else if (data < node1->right->key) {
			node1->right = RotRight(node1->right);
			return RotLeft(node1);
		}
	}
	return node1;
}
template <class T>
bool AVL<T>::retrieve(T d) {
	node* temp = new node;
	if (isEmpty()) {
		root = temp;
	}
	temp = root;
	while (temp != NULL) {
		if (d > temp->key) {
			if (temp->right) {
				temp = temp->right;
			}

		}
		else if (d < temp->key) {
			if (temp->left) {
				temp = temp->left;
			}
		}
		if (d == temp->key) {
			return 1; // value found
		}
	}
	return false; // value not found in tree
}
template <class T>

void AVL<T>::PreOrderTraversal(node<T>* root)
{
	node<T>* temp = root;
	if (temp != nullptr)
	{
		
		PreOrderTraversal(temp->left);
		cout << "-->" << "ID: " << temp->key << endl;
		PreOrderTraversal(temp->right);
	}
}

template <class T>
int AVL<T>::GetBalanceFactor(node<T>* N) {
	if (N == NULL)
		return 0;
	return (height(N->left) - height(N->right));

}
template <class T>
void AVL<T>::update_height(node<T>* node, int height) {
	node->height = height;
	return;
}
template <class T>
node<T>* AVL<T>::RotRight(node<T>* y) {
	node<T>* x = y->left;
	node<T>* T2 = x->right;
	x->right = y;
	y->left = T2;
	y->height = max(height(y->left),
		height(y->right)) +
		1;
	x->height = max(height(x->left),
		height(x->right)) +
		1;
	return x;

}
template <class T>
node<T>* AVL<T>::RotLeft(node<T>* x) {

	node<T>* y = x->right;
	node<T>* T2 = y->left;
	y->left = x;
	x->right = T2;
	x->height = max(height(x->left),
		height(x->right)) +
		1;
	y->height = max(height(y->left),
		height(y->right)) +
		1;
	return y;
}
template <class T>
node<T>* AVL<T>::nodeWithMimumValue(node<T>* node1) {
	node<T> current = node1;
	while (current->left != NULL)
		current = current->left;
	return current;
}
template <class T>
node<T>* AVL<T>::DoubleRotateWithLeft(node<T>* K3)
{

	/* LL rotation between K1 and K2 */
	K3->left = RotRight(K3->left);
	/* RR rotation between K3 and K2 */
	return RotLeft(K3);

}
template <class T>
node<T>* AVL<T>::DoubleRotateWithRight(node<T>* K3)
{

	/* LL rotation between K1 and K2 */
	K3->left = RotLeft(K3->left);
	/* RR rotation between K3 and K2 */
	return RotRight(K3);

}
template <class T>
node<T>* AVL<T>::deleteNode(node<T>* root, T key) {
	// Find the node and delete it
	if (root == NULL)
		return root;
	if (key < root->key)
		root->left = deleteNode(root->left, key);
	else if (key > root->key)
		root->right = deleteNode(root->right, key);
	else {
		if ((root->left == NULL) ||
			(root->right == NULL)) {
			node<T> temp = root->left ? root->left : root->right;
			if (temp == NULL) {
				temp = root;
				root = NULL;
			}
			else
				*root = *temp;
			free(temp);
		}
		else {
			node<T> temp = nodeWithMimumValue(root->right);
			root->key = temp->key;
			root->right = deleteNode(root->right,
				temp->key);
		}
	}

	if (root == NULL)
		return root;

	// Update the balance factor of each node and
	// balance the tree
	root->height = 1 + max(height(root->left),
		height(root->right));
	int balanceFactor = GetBalanceFactor(root);
	if (balanceFactor > 1) {
		if (GetBalanceFactor(root->left) >= 0) {
			return RotRight(root);
		}
		else {
			root->left = RotLeft(root->left);
			return RotRight(root);
		}
	}
	if (balanceFactor < -1) {
		if (GetBalanceFactor(root->right) <= 0) {
			return RotLeft(root);
		}
		else {
			root->right = RotRight(root->right);
			return RotLeft(root);
		}
	}
	return root;
}


void StoreAVLTree() {
	cout << "Please Select An Indexing Method" << endl;
	cout << "1. ID" << endl;
	cout << "2. Year" << endl;
	cout << "3. Cause Name" << endl;
	cout << "4. State" << endl;
	cout << "5. Deaths" << endl;
	cout << "6. Age-Adjusted Death Rate" << endl;
	int option;
	cin >> option;
	if (option == 1) { // ID based indexing
		AVL<int> tree;
		option = askfilename();
		///////////////////////////
		if (option == 1) {
			ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_1.csv", tree, 1);	
			STORE_AVL("NCHS_-_Leading_Causes_of_Death__United_States_1.csv", tree, 1);
		}
		else if (option == 2) {
			ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_2.csv", tree, 1);
			STORE_AVL("NCHS_-_Leading_Causes_of_Death__United_States_2.csv", tree, 1);
		}
		else if (option == 3) {
			ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_3.csv", tree, 1);
			STORE_AVL("NCHS_-_Leading_Causes_of_Death__United_States_3.csv", tree, 1);
		}
		else if (option == 4) {
			ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_4.csv", tree, 1);
			STORE_AVL("NCHS_-_Leading_Causes_of_Death__United_States_4.csv", tree, 1);
		}
		else if (option == 5) {
			ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_5.csv", tree, 1);
			STORE_AVL("NCHS_-_Leading_Causes_of_Death__United_States_5.csv", tree, 1);
		}
		else if (option == 6) {
			ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_6.csv", tree, 1);
			STORE_AVL("NCHS_-_Leading_Causes_of_Death__United_States_6.csv", tree, 1);
		}
		else if (option == 7) {
			ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_7.csv", tree, 1);
			STORE_AVL("NCHS_-_Leading_Causes_of_Death__United_States_7.csv", tree, 1);
		}
		else if (option == 8) {
			ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_8.csv", tree, 1);
			STORE_AVL("NCHS_-_Leading_Causes_of_Death__United_States_8.csv", tree, 1);
		}
		else if (option == 9) {
			ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_9.csv", tree, 1);
			STORE_AVL("NCHS_-_Leading_Causes_of_Death__United_States_9.csv", tree, 1);
		}
		else if (option == 10) {
			ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_10.csv", tree, 1);
			STORE_AVL("NCHS_-_Leading_Causes_of_Death__United_States_10.csv", tree, 1);
		}
		//////////////////////////
	}
	else if (option == 2) { // Year Based based indexing
		AVL<int> tree;
		option = askfilename();
		///////////////////////////
		if (option == 1) {
			ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_1.csv", tree, 2);
			STORE_AVL("NCHS_-_Leading_Causes_of_Death__United_States_1.csv", tree, 2);
		}
		else if (option == 2) {
			ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_2.csv", tree, 2);
			STORE_AVL("NCHS_-_Leading_Causes_of_Death__United_States_2.csv", tree, 2);
		}
		else if (option == 3) {
			ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_3.csv", tree, 2);
			STORE_AVL("NCHS_-_Leading_Causes_of_Death__United_States_3.csv", tree, 2);
		}
		else if (option == 4) {
			ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_4.csv", tree, 2);
			STORE_AVL("NCHS_-_Leading_Causes_of_Death__United_States_4.csv", tree, 2);
		}
		else if (option == 5) {
			ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_5.csv", tree, 2);
			STORE_AVL("NCHS_-_Leading_Causes_of_Death__United_States_5.csv", tree, 2);
		}
		else if (option == 6) {
			ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_6.csv", tree, 2);
			STORE_AVL("NCHS_-_Leading_Causes_of_Death__United_States_6.csv", tree, 2);
		}
		else if (option == 7) {
			ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_7.csv", tree, 2);
			STORE_AVL("NCHS_-_Leading_Causes_of_Death__United_States_7.csv", tree, 2);
		}
		else if (option == 8) {
			ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_8.csv", tree, 2);
			STORE_AVL("NCHS_-_Leading_Causes_of_Death__United_States_8.csv", tree, 2);
		}
		else if (option == 9) {
			ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_9.csv", tree, 2);
			STORE_AVL("NCHS_-_Leading_Causes_of_Death__United_States_9.csv", tree, 2);
		}
		else if (option == 10) {
			ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_10.csv", tree, 2);
			STORE_AVL("NCHS_-_Leading_Causes_of_Death__United_States_10.csv", tree, 2);
		}
		//////////////////////////
	}
	else if (option == 3) { // Cause Name based indexing
		AVL<string> tree;
		option = askfilename();
		///////////////////////////
		if (option == 1) {
			ReadFromFile_string("NCHS_-_Leading_Causes_of_Death__United_States_1.csv", tree, 3);
			STORE_AVL("NCHS_-_Leading_Causes_of_Death__United_States_1.csv", tree, 3);
		}
		else if (option == 2) {
			ReadFromFile_string("NCHS_-_Leading_Causes_of_Death__United_States_2.csv", tree, 3);
			STORE_AVL("NCHS_-_Leading_Causes_of_Death__United_States_2.csv", tree, 3);
		}
		else if (option == 3) {
			ReadFromFile_string("NCHS_-_Leading_Causes_of_Death__United_States_3.csv", tree, 3);
			STORE_AVL("NCHS_-_Leading_Causes_of_Death__United_States_3.csv", tree, 3);
		}
		else if (option == 4) {
			ReadFromFile_string("NCHS_-_Leading_Causes_of_Death__United_States_4.csv", tree, 3);
			STORE_AVL("NCHS_-_Leading_Causes_of_Death__United_States_4.csv", tree, 3);
		}
		else if (option == 5) {
			ReadFromFile_string("NCHS_-_Leading_Causes_of_Death__United_States_5.csv", tree, 3);
			STORE_AVL("NCHS_-_Leading_Causes_of_Death__United_States_5.csv", tree, 3);
		}
		else if (option == 6) {
			ReadFromFile_string("NCHS_-_Leading_Causes_of_Death__United_States_6.csv", tree, 3);
			STORE_AVL("NCHS_-_Leading_Causes_of_Death__United_States_6.csv", tree, 3);
		}
		else if (option == 7) {
			ReadFromFile_string("NCHS_-_Leading_Causes_of_Death__United_States_7.csv", tree, 3);
			STORE_AVL("NCHS_-_Leading_Causes_of_Death__United_States_7.csv", tree, 3);
		}
		else if (option == 8) {
			ReadFromFile_string("NCHS_-_Leading_Causes_of_Death__United_States_8.csv", tree, 3);
			STORE_AVL("NCHS_-_Leading_Causes_of_Death__United_States_8.csv", tree, 3);
		}
		else if (option == 9) {
			ReadFromFile_string("NCHS_-_Leading_Causes_of_Death__United_States_9.csv", tree, 3);
			STORE_AVL("NCHS_-_Leading_Causes_of_Death__United_States_9.csv", tree, 3);
		}
		else if (option == 10) {
			ReadFromFile_string("NCHS_-_Leading_Causes_of_Death__United_States_10.csv", tree, 3);
			STORE_AVL("NCHS_-_Leading_Causes_of_Death__United_States_10.csv", tree, 3);
		}
		//////////////////////////
	}

	else if (option == 4) { // State Name based indexing
	AVL<string> tree;
	option = askfilename();
	///////////////////////////
	if (option == 1) {
		ReadFromFile_string("NCHS_-_Leading_Causes_of_Death__United_States_1.csv", tree, 4);
		STORE_AVL("NCHS_-_Leading_Causes_of_Death__United_States_1.csv", tree, 4);
	}
	else if (option == 2) {
		ReadFromFile_string("NCHS_-_Leading_Causes_of_Death__United_States_2.csv", tree, 4);
		STORE_AVL("NCHS_-_Leading_Causes_of_Death__United_States_2.csv", tree, 4);
	}
	else if (option == 3) {
		ReadFromFile_string("NCHS_-_Leading_Causes_of_Death__United_States_3.csv", tree, 4);
		STORE_AVL("NCHS_-_Leading_Causes_of_Death__United_States_3.csv", tree, 4);
	}
	else if (option == 4) {
		ReadFromFile_string("NCHS_-_Leading_Causes_of_Death__United_States_4.csv", tree, 4);
		STORE_AVL("NCHS_-_Leading_Causes_of_Death__United_States_4.csv", tree, 4);
	}
	else if (option == 5) {
		ReadFromFile_string("NCHS_-_Leading_Causes_of_Death__United_States_5.csv", tree, 4);
		STORE_AVL("NCHS_-_Leading_Causes_of_Death__United_States_5.csv", tree, 4);
	}
	else if (option == 6) {
		ReadFromFile_string("NCHS_-_Leading_Causes_of_Death__United_States_6.csv", tree, 4);
		STORE_AVL("NCHS_-_Leading_Causes_of_Death__United_States_6.csv", tree, 4);
	}
	else if (option == 7) {
		ReadFromFile_string("NCHS_-_Leading_Causes_of_Death__United_States_7.csv", tree, 4);
		STORE_AVL("NCHS_-_Leading_Causes_of_Death__United_States_7.csv", tree, 4);
	}
	else if (option == 8) {
		ReadFromFile_string("NCHS_-_Leading_Causes_of_Death__United_States_8.csv", tree, 4);
		STORE_AVL("NCHS_-_Leading_Causes_of_Death__United_States_8.csv", tree, 4);
	}
	else if (option == 9) {
		ReadFromFile_string("NCHS_-_Leading_Causes_of_Death__United_States_9.csv", tree, 4);
		STORE_AVL("NCHS_-_Leading_Causes_of_Death__United_States_9.csv", tree, 4);
	}
	else if (option == 10) {
		ReadFromFile_string("NCHS_-_Leading_Causes_of_Death__United_States_10.csv", tree, 4);
		STORE_AVL("NCHS_-_Leading_Causes_of_Death__United_States_10.csv", tree, 4);
	}
	//////////////////////////
	}

	else if (option == 5) { // Deaths based indexing
	AVL<int> tree;
	option = askfilename();
	///////////////////////////
	if (option == 1) {
		ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_1.csv", tree, 5);
		STORE_AVL("NCHS_-_Leading_Causes_of_Death__United_States_1.csv", tree, 5);
	}
	else if (option == 2) {
		ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_2.csv", tree, 5);
		STORE_AVL("NCHS_-_Leading_Causes_of_Death__United_States_2.csv", tree, 5);
	}
	else if (option == 3) {
		ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_3.csv", tree, 5);
		STORE_AVL("NCHS_-_Leading_Causes_of_Death__United_States_3.csv", tree, 5);
	}
	else if (option == 4) {
		ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_4.csv", tree, 5);
		STORE_AVL("NCHS_-_Leading_Causes_of_Death__United_States_4.csv", tree, 5);
	}
	else if (option == 5) {
		ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_5.csv", tree, 5);
		STORE_AVL("NCHS_-_Leading_Causes_of_Death__United_States_5.csv", tree, 5);
	}
	else if (option == 6) {
		ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_6.csv", tree, 5);
		STORE_AVL("NCHS_-_Leading_Causes_of_Death__United_States_6.csv", tree, 5);
	}
	else if (option == 7) {
		ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_7.csv", tree, 5);
		STORE_AVL("NCHS_-_Leading_Causes_of_Death__United_States_7.csv", tree, 5);
	}
	else if (option == 8) {
		ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_8.csv", tree, 5);
		STORE_AVL("NCHS_-_Leading_Causes_of_Death__United_States_8.csv", tree, 5);
	}
	else if (option == 9) {
		ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_9.csv", tree, 5);
		STORE_AVL("NCHS_-_Leading_Causes_of_Death__United_States_9.csv", tree, 5);
	}
	else if (option == 10) {
		ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_10.csv", tree, 5);
		STORE_AVL("NCHS_-_Leading_Causes_of_Death__United_States_10.csv", tree, 5);
	}
	//////////////////////////
	}

	else if (option == 6) { // Death Rate based indexing
	AVL<float> tree;
	option = askfilename();
	///////////////////////////
	if (option == 1) {
		ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_1.csv", tree, 6);
		STORE_AVL("NCHS_-_Leading_Causes_of_Death__United_States_1.csv", tree, 6);
	}
	else if (option == 2) {
		ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_2.csv", tree, 6);
		STORE_AVL("NCHS_-_Leading_Causes_of_Death__United_States_2.csv", tree, 6);
	}
	else if (option == 3) {
		ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_3.csv", tree, 6);
		STORE_AVL("NCHS_-_Leading_Causes_of_Death__United_States_3.csv", tree, 6);
	}
	else if (option == 4) {
		ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_4.csv", tree, 6);
		STORE_AVL("NCHS_-_Leading_Causes_of_Death__United_States_4.csv", tree, 6);
	}
	else if (option == 5) {
		ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_5.csv", tree, 6);
		STORE_AVL("NCHS_-_Leading_Causes_of_Death__United_States_5.csv", tree, 6);
	}
	else if (option == 6) {
		ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_6.csv", tree, 6);
		STORE_AVL("NCHS_-_Leading_Causes_of_Death__United_States_6.csv", tree, 6);
	}
	else if (option == 7) {
		ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_7.csv", tree, 6);
		STORE_AVL("NCHS_-_Leading_Causes_of_Death__United_States_7.csv", tree, 6);
	}
	else if (option == 8) {
		ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_8.csv", tree, 6);
		STORE_AVL("NCHS_-_Leading_Causes_of_Death__United_States_8.csv", tree, 6);
	}
	else if (option == 9) {
		ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_9.csv", tree, 6);
		STORE_AVL("NCHS_-_Leading_Causes_of_Death__United_States_9.csv", tree, 6);
	}
	else if (option == 10) {
		ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_10.csv", tree, 6);
		STORE_AVL("NCHS_-_Leading_Causes_of_Death__United_States_10.csv", tree, 6);
	}
	//////////////////////////
	}
	else {
	cout << "invalid option" << endl;
	}

}

int askfilename() {
	int temp;
	cout << "Enter the file you want to read" << endl;
	cout << "1. NCHS_-_Leading_Causes_of_Death__United_States_1.csv" << endl;
	cout << "2. NCHS_-_Leading_Causes_of_Death__United_States_2.csv" << endl;
	cout << "3. NCHS_-_Leading_Causes_of_Death__United_States_3.csv" << endl;
	cout << "4. NCHS_-_Leading_Causes_of_Death__United_States_4.csv" << endl;
	cout << "5. NCHS_-_Leading_Causes_of_Death__United_States_5.csv" << endl;
	cout << "6. NCHS_-_Leading_Causes_of_Death__United_States_6.csv" << endl;
	cout << "7. NCHS_-_Leading_Causes_of_Death__United_States_7.csv" << endl;
	cout << "8. NCHS_-_Leading_Causes_of_Death__United_States_8.csv" << endl;
	cout << "9. NCHS_-_Leading_Causes_of_Death__United_States_9.csv" << endl;
	cout << "10. NCHS_-_Leading_Causes_of_Death__United_States_10.csv" << endl;
	cin >> temp;
	return temp;
}

void AVL_POINT_SEARCH() {
	cout << "Enter The Point Key" << endl;
	cout << "1. ID" << endl;
	cout << "2. Year" << endl;
	cout << "3. Cause Name" << endl;
	cout << "4. State" << endl;
	cout << "5. Deaths" << endl;
	cout << "6. Age-Adjusted Death Rate" << endl;
	int option;
	cin >> option;
	if (option == 1) {
		cout << "Enter ID" << endl;
		int id;
		cin >> id;

		string filename;
		filename = "AVL_TREE/AVL_ID/" + to_string(id) + ".txt";
			// Open an existing file
		fstream fin;
		fin.open(filename, ios::in); // input mode

		string output;
		getline(fin, output);
		cout << "Required Data is : " << endl;
		cout << output << endl;

		fin.close();

	}
	else if (option == 2) {
		cout << "Enter Year" << endl;
		int id;
		cin >> id;

		string filename;
		filename = "AVL_TREE/AVL_YEAR/" + to_string(id) + ".txt";
		// Open an existing file
		fstream fin;
		fin.open(filename, ios::in); // input mode

		string output;
		getline(fin, output);
		cout << "Required Data is : " << endl;
		cout << output << endl;

		fin.close();
	}
	else if (option == 3) {
		cout << "Enter Cause Name" << endl;
		string id;
		getline(cin, id);


		string filename;
		filename = "AVL_TREE/AVL_CAUSE_NAME/" + (id) + ".txt";
		// Open an existing file
		fstream fin;
		fin.open(filename, ios::in); // input mode

		string output;
		getline(fin, output);
		cout << "Required Data is : " << endl;
		cout << output << endl;

		fin.close();
	}
	else if (option == 4) {
		cout << "Enter State" << endl;
		string id;
		getline(cin, id);

		string filename;
		filename = "AVL_TREE/AVL_STATE/" + (id)+".txt";
		// Open an existing file
		fstream fin;
		fin.open(filename, ios::in); // input mode

		string output;
		getline(fin, output);
		cout << "Required Data is : " << endl;
		cout << output << endl;

		fin.close();
	}
	else if (option == 5) {
		cout << "Enter Deaths" << endl;
		int id;
		cin >> id;

		string filename;
		filename = "AVL_TREE/AVL_DEATHS/" + to_string(id)+ ".txt";
		// Open an existing file
		fstream fin;
		fin.open(filename, ios::in); // input mode

		string output;
		getline(fin, output);
		cout << "Required Data is : " << endl;
		cout << output << endl;

		fin.close();
	}
	else if (option == 6) {
		cout << "Enter Death Rate" << endl;
		float id;
		cin >> id;

		string filename;
		filename = "AVL_TREE/AVL_DEATH_RATE/" + to_string(id) + ".txt";
		// Open an existing file
		fstream fin;
		fin.open(filename, ios::in); // input mode

		string output;
		getline(fin, output);
		cout << "Required Data is : " << endl;
		cout << output << endl;

		fin.close();
	}
}


void AVL_RANGE_SEARCH() {

}


void AVL_UPDATE() {

}

void AVL_DELETE() {

}


void AVL_WHERE(){

}

