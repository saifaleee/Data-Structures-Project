#pragma once
#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <filesystem>
#include <direct.h>
#include <limits.h>
#include "LIST.h"
#include <cstring>
using namespace std;


fstream& RB_GotoLine(fstream& file, int num);
int RBaskfilename() {
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

template <typename T> 
string RBtostr(const T& t) 
{
    ostringstream os;
    os << t;
    return os.str();
}
//######################## REDBLACK TREES
template <typename T>
struct RBnode
{
    T key;
    int id;
    int years;
    int line_no;
    string Cause;
    string name;
    string state;                        
    int deaths;
    double ADR;
    List<T> duplicate;

    
    RBnode<T>* left = nullptr;
    RBnode<T>* right = nullptr;
    RBnode<T>* parent = nullptr;
    bool red = 0;
    bool black = 1;
    int height;
    RBnode(T key=0,int id = 0, int yrs = 0, string cuz="\0", string name="\0", string state="\0", int dths=0, double ADR=0,int line=0)
    {
            this->key = key;
            this->id = id;
            years = yrs;
            Cause = cuz;
            this->name = name;
            this->state = state;
            deaths = dths;
            this->ADR = ADR;
            this->line_no = line;
        height = 1;
    }
};
template <typename T>
class REDBLACK
{
    
public:
    RBnode<T>* root;
    //List<T> duplicate;
    REDBLACK()
    {
        root = nullptr;
    }

    RBnode<T>* getroot()
    {
        return root;
    }

    void insert(T Key=0,int id=0, int yrs = 0, string cuz = "", string name = "", string state = "", int dths = 0, double ADR = 0, int line=0)
    {
       
        RBnode<T>* temproot = getroot();
        RBnode<T>* temp = search(temproot,Key);
        //if (temp != nullptr) // if value not found insert in tree 
        //{
            if (root == NULL)
            {
                root = new RBnode<T>(Key, id, yrs, cuz, name, state, dths, ADR, line);
                root->black = 1;
                root->red = 0;
                root->parent = NULL;
            }
            else
            {
                RBnode<T>* temp = getroot();
                RBnode<T>* newnode = new RBnode<T>(Key, id, yrs, cuz, name, state, dths, ADR, line);

                while (temp != nullptr)
                {
                    if (Key < temp->key) // if insertion id is less than present id then insert at left
                    {
                        if (temp->left != nullptr)
                        {
                            temp = temp->left;
                        }
                        else
                        {
                            temp->left = newnode;
                            newnode->black = 0;
                            newnode->red = 1; // new node made are always red so bool red =1
                            newnode->parent = temp;
                            //  newnode->height = calheight(newnode);
                            break;
                        }
                    }
                    else         // if insertion id is more than present id then insert at right
                    {
                        if (temp->right != nullptr)
                        {
                            temp = temp->right;
                        }
                        else
                        {
                            temp->right = newnode;
                            newnode->black = 0;
                            newnode->red = 1;       // new node made are always red so bool red =1
                            newnode->parent = temp;
                            //  newnode->height = calheight(newnode);
                            break;
                        }
                    }
                }
                fixcolor(newnode);
            }
/*/ }
        else
        {
            temp->duplicate.Insert(line);
        }*/
       
    }

   
    void fixcolor(RBnode<T>* newnode)
    {
        while (newnode->parent->red == 1)
        {
            RBnode<T>* dada = newnode->parent->parent;
            RBnode<T>* chachu = getroot();
            //case 1
            if (newnode->parent == dada->left)
            {
                if (dada->right)
                    chachu = dada->right;

                if (chachu->red == 1)      //IF CHACHU RED RECOLOR ONLY
                {
                    newnode->parent->black = 1;
                    newnode->parent->red = 0;
                    chachu->black = 1;
                    chachu->red = 0;
                    dada->red = 1;
                    dada->black = 0;

                    if (dada->key != root->key)
                    {
                        newnode = dada;
                    }
                    else
                        break;
                }
                //ELSE IF CHACHU NODE IS BLACK OR DOESNOT EXIST ROTATE AND RECOLOR  ACCORDINGLY
                else if (newnode == dada->left->right)  //IF PATH IS LEFT TO RIGHT ROTATE LEFT
                {
                    leftRotate(newnode->parent);
                }
                else   // ELSE ROTATE LEFT
                {
                    //recoloring
                    newnode->parent->black = 1;
                    newnode->parent->red = 0;
                    dada->red = 1;
                    dada->black = 0;

                    rightRotate(dada);

                    if (dada->key != root->key)
                        newnode = dada;

                    else
                        break;
                }
            }
            //case 2
            else
            {   //if chachu exist make node chachu
                if (dada->left)
                    chachu = dada->left;

                // if chachu red recolor
                if (chachu->red == 1)
                {
                    newnode->parent->black = 1;
                    newnode->parent->red = 0;
                    chachu->black = 1;
                    chachu->red = 0;
                    dada->red = 1;
                    dada->black = 0;

                    if (dada->key != root->key)
                        newnode = dada;
                    else
                        break;
                }
                //if right left roation rotate
                else if (newnode == dada->right->left)
                {
                    rightRotate(newnode->parent);
                }
                //if  left right roation rotate and recolor
                else
                {
                    newnode->parent->black = 1;
                    newnode->parent->red = 0;
                    dada->red = 1;
                    dada->black = 0;

                    leftRotate(dada);

                    if (dada->key != root->key)
                        newnode = dada;

                    else
                        break;
                }
            }
        }
        //setting root black cuz root always black
        root->black = 1;
        root->red = 0;
    }



    void leftRotate(RBnode<T>* node1)
    {
        RBnode<T>* rotation_node = new RBnode<T>(node1->key);

        if (node1->right->left)
            rotation_node->right = node1->right->left;

        rotation_node->left = node1->left;

        rotation_node->id = node1->id;
        rotation_node->key = node1->key;/////-----------------------------------------------------
        rotation_node->years = node1->years;
        rotation_node->line_no = node1->line_no;//---------------------------------
        rotation_node->Cause = node1->Cause;
        rotation_node->name = node1->name;
        rotation_node->state = node1->state;
        rotation_node->ADR = node1->ADR;
        rotation_node->black = node1->black;
        rotation_node->red = node1->red;

        rotation_node->black = node1->black;
        rotation_node->red = node1->red;

        node1->id = node1->right->id;
        node1->years = node1->right->years;
        node1->key = node1->right->key;/////-----------------------------------------------------
        node1->Cause = node1->right->Cause;
        node1->name = node1->right->name;
        node1->line_no = node1->right->line_no; ///------------------------------
        node1->state = node1->right->state;
        node1->deaths = node1->right->deaths;
        node1->ADR = node1->right->ADR;
        node1->red = node1->right->red;
        node1->black = node1->right->black;


        node1->left = rotation_node;

        if (rotation_node->left)
            rotation_node->left->parent = rotation_node;

        if (rotation_node->right)
            rotation_node->right->parent = rotation_node;

        //else
        rotation_node->parent = node1;

        if (node1->right->right)
            node1->right = node1->right->right;

        else
            node1->right = nullptr;

        if (node1->right)
            node1->right->parent = node1;
    }

    void rightRotate(RBnode<T>* node1)
    {
        RBnode<T>* rotation_node = new RBnode<T>(node1->key);

        if (node1->left->right)
            rotation_node->left = node1->left->right;
        rotation_node->right = node1->right;


        rotation_node->id = node1->id;
        rotation_node->key = node1->key; //-----------------------------------------------
        rotation_node->years = node1->years;
        rotation_node->Cause = node1->Cause;
        rotation_node->name = node1->name;
        rotation_node->state = node1->state;
        rotation_node->ADR = node1->ADR;
        rotation_node->line_no = node1->line_no;
        rotation_node->black = node1->black;
        rotation_node->red = node1->red;

        
        node1->id = node1->left->id;
        node1->key = node1->left->key; ///--------------------------------------
        node1->years = node1->left->years;
        node1->Cause = node1->left->Cause;
        node1->name = node1->left->name;
        node1->state = node1->left->state;
        node1->line_no = node1->left->line_no;//------------------------
        node1->deaths = node1->left->deaths;
        node1->ADR = node1->left->ADR;
        node1->red = node1->left->red;
        node1->black = node1->left->black;

        node1->right = rotation_node;
        if (rotation_node->left)
            rotation_node->left->parent = rotation_node;

        if (rotation_node->right)
            rotation_node->right->parent = rotation_node;

        //else
        rotation_node->parent = node1;

        if (node1->left->left)
            node1->left = node1->left->left;

        else
            node1->left = nullptr;

        if (node1->left)
            node1->left->parent = node1;
    }

    void RemoveNode(RBnode<T>* parent, RBnode<T>* ongoing, T key) 
    {
        if (ongoing == nullptr)
        return;
        
        int i = 0;
        while (i < 2) 
        { 
            i++; 
        }
        if (ongoing->key == key) 
        {
            
            if (ongoing->left == nullptr && ongoing->right == nullptr)  //first case 
            {
                if (parent->key == ongoing->key) 
                {
                    root = nullptr;
                }
                else if (parent->right == ongoing) 
                {
                    delete_colorFix(ongoing);
                    parent->right = nullptr;
                }
                else 
                {
                    delete_colorFix(ongoing);
                    parent->left = nullptr;
                }
            }
            
            else if (ongoing->left != nullptr && ongoing->right == nullptr) //Second case  swap node data
            {
                T sort = ongoing->key;
                int d= ongoing->id;
                int yrs=ongoing->years;
                string state = ongoing->state;
                string name = ongoing->name;
                string cuz = ongoing->Cause;
                int deaths = ongoing->deaths;
                double adr=ongoing->ADR;
                int l=ongoing->line_no;

                ongoing->key = ongoing->left->key;
                //debugger cmnt remove if pangay swapping 
                //------------------------------------------------------------------------------------------------|
                /**/ongoing->id = ongoing->left->id;                                                        //    |
                /**/ongoing->name = ongoing->left->name;                                                    //    |
                /**/ongoing->years = ongoing->left->years;                                                  //    |
                /**/ongoing->state = ongoing->left->state;                                                  //    |
                /**/ongoing->Cause = ongoing->left->Cause;                                                  //    |
                /**/ongoing->deaths = ongoing->left->deaths;                                                //    |
                /**/ongoing->ADR = ongoing->left->ADR;                                                      //    |
                /**/ongoing->key = ongoing->left->key;                                                      //    |
                /**/ongoing->line_no = ongoing->left->line_no;                                                      //    |
                /**/                                                                                        //    |
                /**/                                                                                       //     |
                /**/                                                                                       //     |
                /**/  ongoing->left->key = sort;                                                           //     |
                /**/  ongoing->left->id = d;                                                               //     |
                /**/  ongoing->left->state = state;                                                        //     |
                /**/  ongoing->left->name = name;                                                          //     |
                /**/  ongoing->left->years = yrs;                                                          //     |
                /**/  ongoing->left->ADR = adr;                                                            //     |
                /**/  ongoing->left->deaths = deaths;                                                      //     |
                /**/   ongoing->left->Cause = cuz;                                                         //     |
                /**/   ongoing->left->line_no = l;                                                         //     |
                //--______________________________________________________________________________________________|
                RemoveNode(ongoing, ongoing->right, key);
            }
            else if (ongoing->left == nullptr && ongoing->right != nullptr)
            {
                if (ongoing->left == nullptr)
                {}

                T sort = ongoing->key;
                int d= ongoing->id;
                int yrs=ongoing->years;
                string state = ongoing->state;
                string name = ongoing->name;
                string cuz = ongoing->Cause;
                int deaths = ongoing->deaths;
                double adr=ongoing->ADR;
                int l=ongoing->line_no;

                ongoing->key = ongoing->right->key;
                //debugger cmnt remove if pangay
                //------------------------------------------------------------------------------------------------|
                /**/ongoing->id = ongoing->right->id;                                                        //    |
                /**/ongoing->name = ongoing->right->name;                                                    //    |
                /**/ongoing->years = ongoing->right->years;                                                  //    |
                /**/ongoing->state = ongoing->right->state;                                                 //    |
                /**/ongoing->Cause = ongoing->right->Cause;                                                  //    |
                /**/ongoing->deaths = ongoing->right->deaths;                                                //    |
                /**/ongoing->ADR = ongoing->right->ADR;                                                      //    |
                /**/ongoing->key = ongoing->right->key;                                                      //    |
                /**/ongoing->line_no = ongoing->right->line_no;                                                      //    |
                /**/                                                                                        //    |
                /**/                                                                                       //     |
                //--______________________________________________________________________________________________|
                ongoing->right->key = sort;
                ongoing->right->id = d;
                ongoing->right->state = state;
                ongoing->right->name = name;
                ongoing->right->years = yrs;
                ongoing->right->ADR = adr;
                ongoing->right->deaths = deaths;
                ongoing->right->Cause = cuz;
                ongoing->right->line_no = l;
                RemoveNode(ongoing, ongoing->right, key);
                
            }
            
            else //Third case
            {
                bool flag = false;
                RBnode<T>* temp = ongoing->right;
                while (temp->left!=nullptr) 
                { 
                  flag = true; 
                  parent = temp; 
                  temp = temp->left; 
                }
                if (flag==false) 
                    parent = ongoing; 
                
                T SORT = ongoing->key;
                int id_temo = ongoing->id;
                int yrs = ongoing->years;
                string tCause = ongoing->Cause;
                string name = ongoing->name;
                string state = ongoing->state;
                int dths = ongoing->deaths;
                double ADR = ongoing->ADR;
                int l = ongoing->line_no;

                ongoing->key = temp->key;
               
                //debugger cmnt remove if pangay
               // ------------------------------------------------------------------------------------------------|
                /**/ongoing->id = temp->id;                                                        //    |
                /**/ongoing->name = temp->name;                                                    //    |
                /**/ongoing->years = temp->years;                                                  //    |
                /**/ ongoing->state = temp->state;                                                 //    |
                /**/ongoing->Cause = temp->Cause;                                                  //    |
                /**/ongoing->deaths = temp->deaths;                                                //    |
                /**/ongoing->ADR = temp->ADR;                                                      //    |
                /**/ongoing->key = temp->key;                                                      //    |
                /**/ongoing->line_no = temp->line_no;                                                      //    |
                ///**/                                                                                        //    |
                ///**/ this->key = key;                  
                ///  
                ///                                                                    //     |
                //--______________________________________________________________________________________________|
                temp->key = SORT;
                temp->id = id_temo;                                               
                temp->name =name;                                                 
                temp->years=yrs;                                                  
                temp->state=state;                                                
                temp->Cause=tCause;                                               
                temp->deaths=dths;                                                
                temp->ADR=ADR;
                temp->line_no = l;
                
                RemoveNode(parent, temp, SORT);
            }
            
        }
    }

    void DELETE(T key) 
    {
        RBnode<T>* temp = root;
        RBnode<T>* parent = temp;
        RBnode<T>* temp1 = nullptr;
        if (temp==nullptr)  
            RemoveNode(nullptr, nullptr, key);
    

        while (temp!=nullptr) 
        {

            if (key == temp->key) 
            { 
                RemoveNode(parent, temp, key);
                break; 
            }
            else if (temp->key > key)
            { 
                parent = temp;
                temp = temp->left;
            }
            else 
            { 
                parent = temp; 
                temp = temp->right;
            }
        }    
    }

    void delete_colorFix(RBnode<T>* node1) 
    {
        while ((node1->key != root->key) && (node1->black== 1))
        {
            RBnode<T>* bhai = getroot();
            if (node1->parent->left == node1) 
            {
                if (node1->parent->right) 
                 bhai = node1->parent->right; 

                if (bhai)//if bhai exist no tension 
                {
                    if (bhai->red== 1) //CASE -- 1 if sibling red roatate and recolor chnage bhai
                    {
                        bhai->black = 1;
                        bhai->red = 0;
                        node1->parent->red = 1;
                        node1->parent->black = 0;
                        leftRotate(node1->parent);
                        bhai = node1->parent->right;
                    }                 
                    if (bhai->left == nullptr && bhai->right == nullptr) //CASE -- 2 if no child of sibling ||  black  make parent chnage bhai 
                    {
                        bhai->red= 1;
                        bhai->black= 0;
                        node1 = node1->parent;
                    }
                    else if (bhai->left->black == 1 && bhai->right->black == 1) 
                    {
                        bhai->red= 1;
                        bhai->black= 0;
                        node1 = node1->parent;
                    }
                    else if (bhai->right->black == 1) //CASE -- 3 if brothers child == black chnage bhai
                    {
                        bhai->left->black = 1;
                        bhai->left->red = 0;
                        bhai->red = 1;
                        bhai->black = 0;
                        rightRotate(bhai);
                        bhai = node1->parent->right;
                    }
                    else //else rotate and recolor chnage bhai
                    {
                        bhai->red = node1->parent->red;
                        bhai->black = node1->parent->black;
                        node1->parent->black= 1;
                        node1->parent->red= 0;
                        if (bhai->right) 
                        { 
                            bhai->right->black = 1; 
                            bhai->right->red = 0; 
                        }
                        leftRotate(node1->parent);
                        node1 = root;
                    }
                }
            }
            else //if bhai no exist make bhai first then do operation
            {
                if (node1->parent->right == node1) 
                {
                    // make bhai
                    if (node1->parent->left) 
                     bhai = node1->parent->left; 
                    
                    if (bhai) 
                    {
                        if (bhai->red== 1)  //CASE -- 1 if sibling red roatate and recolor change bhai
                        {
                            bhai->black = 1;
                            bhai->red = 0;
                            node1->parent->red= 1;
                            node1->parent->black= 0;
                            rightRotate(node1->parent);
                            bhai = node1->parent->left;
                        }
                        if (bhai->left == nullptr && bhai->right == nullptr) //CASE -- 2 if no child of sibling ||  black  make parent 
                        {
                            bhai->red = 1;
                            bhai->black = 0;
                            node1 = node1->parent;
                        }
                        else if (bhai->left->black == 1 && bhai->right->black == 1) 
                        {
                            bhai->red = 1;
                            bhai->black = 0;
                            node1 = node1->parent;
                        }
                        
                        else if (bhai->left->black == 1) //CASE -- 3  if brothers child == black chnage bhai
                        {
                            bhai->right->black = 1;
                            bhai->right->red = 0;
                            bhai->red = 1;
                            bhai->black = 0;
                            rightRotate(bhai);
                            bhai = node1->parent->left;
                        }
                        else //else rotate and recolor chnage bhai
                        {
                            bhai->red = node1->parent->red;
                            bhai->black = node1->parent->black;
                            node1->parent->black = 1;
                            node1->parent->red = 0;
                            if (bhai->left) 
                            { 
                                bhai->left->black = 1; 
                                bhai->left->red = 0; 
                            }
                            leftRotate(node1->parent);
                            node1 = root;
                        }
                    }
                }

            }
        }
        node1->black = 1;
        node1->red = 0;
    }

    RBnode<T>* search(RBnode<T>* root, T key)
    {
        if (root == NULL || root->key == key)
            return root;
        if (root->key < key)
            return search(root->right, key);
        else
        return search(root->left, key);
    }
    void display(RBnode<T>* temp)
    {
        cout <<"-->"<< "ID:" << temp->id << " Name: " << temp->name << " Cause: " << temp->Cause << " AGE: " <<temp->years << " STATE: " << temp->state <<" ADR: " << temp->ADR << " RED<" << temp->red << ">  black<" << temp->black << ">  -> \n";
    }

    void preorderTraversal(RBnode<T>* root)
    {
        RBnode<T>* temp = root;
        if (temp != nullptr)
        {
           
            preorderTraversal(temp->left);
            cout << "-->" << "ID:" << temp->id << " Name: " << temp->name << " Cause: " << temp->Cause << " AGE: " << temp->years << " STATE: " << temp->state << " ADR: " << temp->ADR << " RED<" << temp->red << ">  black<" << temp->black << ">  ->" << temp->line_no << " \n";  
            preorderTraversal(temp->right);
        }
    }
};










//_____________________________FILE HANDLING_______________________________________
//#################################################################################
//#################################################################################
//#################################################################################
//#################################################################################
//#################################################################################
template <typename T>
void RB_ReadFromFile_int(string filename, REDBLACK<T>& tree, int type) 
{
    // File pointer
    fstream fin;
    cout << filename << endl;
    //RBnode<T>* root = NULL; // will be used for in insertion, deletion

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
            if (type < 3) 
            {
                int i = type - 1;
                tree.insert(stoi(row[i]), stoi(row[0]), stoi(row[1]), row[2], row[3], row[4], stoi(row[5]), stof(row[6]), count + 1); // row of 0 will always contain, ID

            }
            else if (type > 3) {
                int i = type;
                if (type == 6) 
                { // float 
                    tree.insert(stof(row[i]), stoi(row[0]), stoi(row[1]), row[2], row[3], row[4], stoi(row[5]), stof(row[6]), count + 1); // row of 0 will always contain, ID
                }
                else 
                {
                    tree.insert(stoi(row[i]), stoi(row[0]), stoi(row[1]), row[2], row[3], row[4], stoi(row[5]), stof(row[6]), count + 1); // row of 0 will always contain, ID
                }

            }
            // count == line number	
        }


        count++;
        //}
    }

    tree.preorderTraversal(tree.getroot());
}
template <typename T>
void RB_ReadFromFile_string(string filename, REDBLACK<T>& tree, int type) {
    // File pointer
    fstream fin;

    RBnode<T>* root = NULL; // will be used for in insertion, deletion

    // Open an existing file
    fin.open(filename, ios::in); // input mode

    // Read the Data from the file
    // as String Vector
    vector<string> row;

    string line, word, temp;

    int count = 0; // will help in keeping track of whether first row was read or not

    while (!fin.eof()) 
    { // read till end of file

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
            if (type < 3) {
                int i = type - 1;

                //root = tree.insert(root, stoi(row[i]), count + 1); // row of 0 will always contain, ID

            }
            else if (type >= 3) {
                // add conditons
                int i = type;
                string string_key = row[i];
               tree.insert(string_key, stoi(row[0]), stoi(row[1]), row[2], row[3], row[4], stoi(row[5]), stof(row[6]), count + 1); // row of 0 will always contain, ID

            }
            // count == line number	
        }


        count++;
        //}
    }
    tree.preorderTraversal(tree.getroot());
}/*
template <typename T>*/




//############################## HEAP STORE #####################################
fstream& RB_GotoLine(fstream& file,  int num) {
    file.seekg(ios::beg);
    for (int i = 0; i < num - 1; ++i) {
        file.ignore(numeric_limits < streamsize>::max(), '\n'); // ignore the max characters in line and loop will continue till user specified line number
    }
    return file;
}

template <typename T>
void RB_NODE_STORE(string filename, REDBLACK<T>& tree, RBnode<T>* root, int type, string folder) {

    RBnode<T>* temp = root;
    string key_fname = "";
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

        key_fname = RBtostr(temp->key); // / / / 1.txt

        thefilename = folder + key_fname + ".txt";

        ofstream MyFile(thefilename);

        //////////////////////////////////////// Write to the file
        // File pointer
        fstream file(filename);

        RBnode<T>* root = NULL; // will be used for in insertion, deletion

        // Open an existing file
        //fin.open(filename, ios::in); // input mode

        RB_GotoLine(file, temp->line_no);

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
        RB_NODE_STORE(filename, tree, temp->left, type, folder);
        RB_NODE_STORE(filename, tree, temp->right, type, folder);
    }

}


//################### heap storage#################################
template <typename T>
void STORE_RB(string filename, REDBLACK<T>& tree, int type)
{
    _mkdir("RB_TREE"); // create folder

    string path = "";

    if (type == 1) {
        _mkdir("RB_TREE/RB_ID"); // create sub_folder
        path = "RB_TREE/RB_ID/";
    }
    else if (type == 2) {
        _mkdir("RB_TREE/RB_YEAR"); // create sub_folder
        path = "RB_TREE/RB_YEAR/";
    }
    else if (type == 3) {
        _mkdir("RB_TREE/RB_CAUSE_NAME"); // create sub_folder
        path = "RB_TREE/RB_CAUSE_NAME/";
    }
    else if (type == 4) {
        _mkdir("RB_TREE/RB_STATE"); // create sub_folder
        path = "RB_TREE/RB_STATE/";
    }
    else if (type == 5) {
        _mkdir("RB_TREE/RB_DEATHS"); // create sub_folder
        path = "RB_TREE/RB_DEATHS/";
    }
    else if (type == 6) {
        _mkdir("RB_TREE/RB_DEATH_RATE"); // create sub_folder
        path = "RB_TREE/RB_DEATH_RATE/";
    }


    RB_NODE_STORE(filename, tree, tree.getroot(), type, path);

}



void StoreRBTree() {
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
        REDBLACK<int> tree;
        option = askfilename();
        ///////////////////////////
        if (option == 1) {
            RB_ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_1.csv", tree, 1);
            STORE_RB("NCHS_-_Leading_Causes_of_Death__United_States_1.csv", tree, 1);
        }
        else if (option == 2) {
            RB_ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_2.csv", tree, 1);
            STORE_RB("NCHS_-_Leading_Causes_of_Death__United_States_2.csv", tree, 1);
        }
        else if (option == 3) {
            RB_ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_3.csv", tree, 1);
            STORE_RB("NCHS_-_Leading_Causes_of_Death__United_States_3.csv", tree, 1);
        }
        else if (option == 4) {
            RB_ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_4.csv", tree, 1);
            STORE_RB("NCHS_-_Leading_Causes_of_Death__United_States_4.csv", tree, 1);
        }
        else if (option == 5) {
            RB_ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_5.csv", tree, 1);
            STORE_RB("NCHS_-_Leading_Causes_of_Death__United_States_5.csv", tree, 1);
        }
        else if (option == 6) {
            RB_ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_6.csv", tree, 1);
            STORE_RB("NCHS_-_Leading_Causes_of_Death__United_States_6.csv", tree, 1);
        }
        else if (option == 7) {
            RB_ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_7.csv", tree, 1);
            STORE_RB("NCHS_-_Leading_Causes_of_Death__United_States_7.csv", tree, 1);
        }
        else if (option == 8) {
            RB_ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_8.csv", tree, 1);
            STORE_RB("NCHS_-_Leading_Causes_of_Death__United_States_8.csv", tree, 1);
        }
        else if (option == 9) {
            RB_ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_9.csv", tree, 1);
            STORE_RB("NCHS_-_Leading_Causes_of_Death__United_States_9.csv", tree, 1);
        }
        else if (option == 10) {
            RB_ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_10.csv", tree, 1);
            STORE_RB("NCHS_-_Leading_Causes_of_Death__United_States_10.csv", tree, 1);
        }
        //////////////////////////
    }
    else if (option == 2) { // Year Based based indexing
        REDBLACK<int> tree;
        option = askfilename();
        ///////////////////////////
        if (option == 1) {
            RB_ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_1.csv", tree, 2);
            STORE_RB("NCHS_-_Leading_Causes_of_Death__United_States_1.csv", tree, 2);
        }
        else if (option == 2) {
            RB_ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_2.csv", tree, 2);
            STORE_RB("NCHS_-_Leading_Causes_of_Death__United_States_2.csv", tree, 2);
        }
        else if (option == 3) {
            RB_ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_3.csv", tree, 2);
            STORE_RB("NCHS_-_Leading_Causes_of_Death__United_States_3.csv", tree, 2);
        }
        else if (option == 4) {
            RB_ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_4.csv", tree, 2);
            STORE_RB("NCHS_-_Leading_Causes_of_Death__United_States_4.csv", tree, 2);
        }
        else if (option == 5) {
            RB_ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_5.csv", tree, 2);
            STORE_RB("NCHS_-_Leading_Causes_of_Death__United_States_5.csv", tree, 2);
        }
        else if (option == 6) {
            RB_ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_6.csv", tree, 2);
            STORE_RB("NCHS_-_Leading_Causes_of_Death__United_States_6.csv", tree, 2);
        }
        else if (option == 7) {
            RB_ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_7.csv", tree, 2);
            STORE_RB("NCHS_-_Leading_Causes_of_Death__United_States_7.csv", tree, 2);
        }
        else if (option == 8) {
            RB_ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_8.csv", tree, 2);
            STORE_RB("NCHS_-_Leading_Causes_of_Death__United_States_8.csv", tree, 2);
        }
        else if (option == 9) {
            RB_ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_9.csv", tree, 2);
            STORE_RB("NCHS_-_Leading_Causes_of_Death__United_States_9.csv", tree, 2);
        }
        else if (option == 10) {
            RB_ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_10.csv", tree, 2);
            STORE_RB("NCHS_-_Leading_Causes_of_Death__United_States_10.csv", tree, 2);
        }
        //////////////////////////
    }
    else if (option == 3) { // Cause Name based indexing
        REDBLACK<string> tree;
        option = askfilename();
        ///////////////////////////
        if (option == 1) {
            RB_ReadFromFile_string("NCHS_-_Leading_Causes_of_Death__United_States_1.csv", tree, 3);
            STORE_RB("NCHS_-_Leading_Causes_of_Death__United_States_1.csv", tree, 3);
        }
        else if (option == 2) {
            RB_ReadFromFile_string("NCHS_-_Leading_Causes_of_Death__United_States_2.csv", tree, 3);
            STORE_RB("NCHS_-_Leading_Causes_of_Death__United_States_2.csv", tree, 3);
        }
        else if (option == 3) {
            RB_ReadFromFile_string("NCHS_-_Leading_Causes_of_Death__United_States_3.csv", tree, 3);
            STORE_RB("NCHS_-_Leading_Causes_of_Death__United_States_3.csv", tree, 3);
        }
        else if (option == 4) {
            RB_ReadFromFile_string("NCHS_-_Leading_Causes_of_Death__United_States_4.csv", tree, 3);
            STORE_RB("NCHS_-_Leading_Causes_of_Death__United_States_4.csv", tree, 3);
        }
        else if (option == 5) {
            RB_ReadFromFile_string("NCHS_-_Leading_Causes_of_Death__United_States_5.csv", tree, 3);
            STORE_RB("NCHS_-_Leading_Causes_of_Death__United_States_5.csv", tree, 3);
        }
        else if (option == 6) {
            RB_ReadFromFile_string("NCHS_-_Leading_Causes_of_Death__United_States_6.csv", tree, 3);
            STORE_RB("NCHS_-_Leading_Causes_of_Death__United_States_6.csv", tree, 3);
        }
        else if (option == 7) {
            RB_ReadFromFile_string("NCHS_-_Leading_Causes_of_Death__United_States_7.csv", tree, 3);
            STORE_RB("NCHS_-_Leading_Causes_of_Death__United_States_7.csv", tree, 3);
        }
        else if (option == 8) {
            RB_ReadFromFile_string("NCHS_-_Leading_Causes_of_Death__United_States_8.csv", tree, 3);
            STORE_RB("NCHS_-_Leading_Causes_of_Death__United_States_8.csv", tree, 3);
        }
        else if (option == 9) {
            RB_ReadFromFile_string("NCHS_-_Leading_Causes_of_Death__United_States_9.csv", tree, 3);
            STORE_RB("NCHS_-_Leading_Causes_of_Death__United_States_9.csv", tree, 3);
        }
        else if (option == 10) {
            RB_ReadFromFile_string("NCHS_-_Leading_Causes_of_Death__United_States_10.csv", tree, 3);
            STORE_RB("NCHS_-_Leading_Causes_of_Death__United_States_10.csv", tree, 3);
        }
        //////////////////////////
    }

    else if (option == 4) { // State Name based indexing
        REDBLACK<string> tree;
        option = askfilename();
        ///////////////////////////
        if (option == 1) {
            RB_ReadFromFile_string("NCHS_-_Leading_Causes_of_Death__United_States_1.csv", tree, 4);
            STORE_RB("NCHS_-_Leading_Causes_of_Death__United_States_1.csv", tree, 4);
        }
        else if (option == 2) {
            RB_ReadFromFile_string("NCHS_-_Leading_Causes_of_Death__United_States_2.csv", tree, 4);
            STORE_RB("NCHS_-_Leading_Causes_of_Death__United_States_2.csv", tree, 4);
        }
        else if (option == 3) {
            RB_ReadFromFile_string("NCHS_-_Leading_Causes_of_Death__United_States_3.csv", tree, 4);
            STORE_RB("NCHS_-_Leading_Causes_of_Death__United_States_3.csv", tree, 4);
        }
        else if (option == 4) {
            RB_ReadFromFile_string("NCHS_-_Leading_Causes_of_Death__United_States_4.csv", tree, 4);
            STORE_RB("NCHS_-_Leading_Causes_of_Death__United_States_4.csv", tree, 4);
        }
        else if (option == 5) {
            RB_ReadFromFile_string("NCHS_-_Leading_Causes_of_Death__United_States_5.csv", tree, 4);
            STORE_RB("NCHS_-_Leading_Causes_of_Death__United_States_5.csv", tree, 4);
        }
        else if (option == 6) {
            RB_ReadFromFile_string("NCHS_-_Leading_Causes_of_Death__United_States_6.csv", tree, 4);
            STORE_RB("NCHS_-_Leading_Causes_of_Death__United_States_6.csv", tree, 4);
        }
        else if (option == 7) {
            RB_ReadFromFile_string("NCHS_-_Leading_Causes_of_Death__United_States_7.csv", tree, 4);
            STORE_RB("NCHS_-_Leading_Causes_of_Death__United_States_7.csv", tree, 4);
        }
        else if (option == 8) {
            RB_ReadFromFile_string("NCHS_-_Leading_Causes_of_Death__United_States_8.csv", tree, 4);
            STORE_RB("NCHS_-_Leading_Causes_of_Death__United_States_8.csv", tree, 4);
        }
        else if (option == 9) {
            RB_ReadFromFile_string("NCHS_-_Leading_Causes_of_Death__United_States_9.csv", tree, 4);
            STORE_RB("NCHS_-_Leading_Causes_of_Death__United_States_9.csv", tree, 4);
        }
        else if (option == 10) {
            RB_ReadFromFile_string("NCHS_-_Leading_Causes_of_Death__United_States_10.csv", tree, 4);
            STORE_RB("NCHS_-_Leading_Causes_of_Death__United_States_10.csv", tree, 4);
        }
        //////////////////////////
    }

    else if (option == 5) { // Deaths based indexing
        REDBLACK<int> tree;
        option = askfilename();
        ///////////////////////////
        if (option == 1) {
            RB_ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_1.csv", tree, 5);
            STORE_RB("NCHS_-_Leading_Causes_of_Death__United_States_1.csv", tree, 5);
        }
        else if (option == 2) {
            RB_ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_2.csv", tree, 5);
            STORE_RB("NCHS_-_Leading_Causes_of_Death__United_States_2.csv", tree, 5);
        }
        else if (option == 3) {
            RB_ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_3.csv", tree, 5);
            STORE_RB("NCHS_-_Leading_Causes_of_Death__United_States_3.csv", tree, 5);
        }
        else if (option == 4) {
            RB_ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_4.csv", tree, 5);
            STORE_RB("NCHS_-_Leading_Causes_of_Death__United_States_4.csv", tree, 5);
        }
        else if (option == 5) {
            RB_ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_5.csv", tree, 5);
            STORE_RB("NCHS_-_Leading_Causes_of_Death__United_States_5.csv", tree, 5);
        }
        else if (option == 6) {
            RB_ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_6.csv", tree, 5);
            STORE_RB("NCHS_-_Leading_Causes_of_Death__United_States_6.csv", tree, 5);
        }
        else if (option == 7) {
            RB_ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_7.csv", tree, 5);
            STORE_RB("NCHS_-_Leading_Causes_of_Death__United_States_7.csv", tree, 5);
        }
        else if (option == 8) {
            RB_ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_8.csv", tree, 5);
            STORE_RB("NCHS_-_Leading_Causes_of_Death__United_States_8.csv", tree, 5);
        }
        else if (option == 9) {
            RB_ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_9.csv", tree, 5);
            STORE_RB("NCHS_-_Leading_Causes_of_Death__United_States_9.csv", tree, 5);
        }
        else if (option == 10) {
            RB_ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_10.csv", tree, 5);
            STORE_RB("NCHS_-_Leading_Causes_of_Death__United_States_10.csv", tree, 5);
        }
        //////////////////////////
    }

    else if (option == 6) { // Death Rate based indexing
        REDBLACK<double> tree;
        option = RBaskfilename();
        ///////////////////////////
        if (option == 1) {
            RB_ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_1.csv", tree, 6);
            STORE_RB("NCHS_-_Leading_Causes_of_Death__United_States_1.csv", tree, 6);
        }
        else if (option == 2) {
            RB_ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_2.csv", tree, 6);
            STORE_RB("NCHS_-_Leading_Causes_of_Death__United_States_2.csv", tree, 6);
        }
        else if (option == 3) {
            RB_ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_3.csv", tree, 6);
            STORE_RB("NCHS_-_Leading_Causes_of_Death__United_States_3.csv", tree, 6);
        }
        else if (option == 4) {
            RB_ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_4.csv", tree, 6);
            STORE_RB("NCHS_-_Leading_Causes_of_Death__United_States_4.csv", tree, 6);
        }
        else if (option == 5) {
            RB_ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_5.csv", tree, 6);
            STORE_RB("NCHS_-_Leading_Causes_of_Death__United_States_5.csv", tree, 6);
        }
        else if (option == 6) {
            RB_ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_6.csv", tree, 6);
            STORE_RB("NCHS_-_Leading_Causes_of_Death__United_States_6.csv", tree, 6);
        }
        else if (option == 7) {
            RB_ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_7.csv", tree, 6);
            STORE_RB("NCHS_-_Leading_Causes_of_Death__United_States_7.csv", tree, 6);
        }
        else if (option == 8) {
            RB_ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_8.csv", tree, 6);
            STORE_RB("NCHS_-_Leading_Causes_of_Death__United_States_8.csv", tree, 6);
        }
        else if (option == 9) {
            RB_ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_9.csv", tree, 6);
            STORE_RB("NCHS_-_Leading_Causes_of_Death__United_States_9.csv", tree, 6);
        }
        else if (option == 10) {
            RB_ReadFromFile_int("NCHS_-_Leading_Causes_of_Death__United_States_10.csv", tree, 6);
            STORE_RB("NCHS_-_Leading_Causes_of_Death__United_States_10.csv", tree, 6);
        }
        //////////////////////////
    }
    else 
    {
        cout << "invalid option" << endl;
    }
    
}

void  REDBLACK_POINT_SEARCH()
{
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
        filename = "RB_TREE/RB_ID/" + to_string(id) + ".txt";
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
        filename = "RB_TREE/RB_YEAR/" + to_string(id) + ".txt";
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
        filename = "RB_TREE/RB_CAUSE_NAME/" + (id)+".txt";
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
        filename = "RB_TREE/RB_STATE/" + (id)+".txt";
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
        filename = "RB_TREE/RB_DEATHS/" + to_string(id) + ".txt";
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
        filename = "RB_TREE/RB_DEATH_RATE/" + to_string(id) + ".txt";
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


void REDBLACK_RANGE_SEARCH()
{

}


void  REDBLACK_UPDATE()
{

}

void REDBLACK_DELETE()
{

}


void REDBLACK_WHERE()
{

}
