#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "BTrees.h"
using namespace std;


string** ReadFromFileB(string fname, int& size) {
    

    vector<vector<string>> content;
    vector<string> row;
    string line, word;

    fstream file(fname, ios::in);
    if (file.is_open())
    {
        while (getline(file, line))
        {
            row.clear();

            stringstream str(line);
            int count = 0;
            bool flag = false;

            while (getline(str, word, ',')) {
                if (word == "," && count == 3) {
                    flag = true;
                }
                if (!flag) {
                    row.push_back(word);
                }
            }
            content.push_back(row);
        }
    }
    string** ans = new string*[content.size()];
    for (int c = 0; c < content.size(); c++) {
        ans[c] = new string[content[c].size()];
    }

    for (int i = 0; i < content.size(); i++)
    {
        for (int j = 0; j < content[i].size(); j++)
        {  
            ans[i][j] = content[i][j];
            //cout << ans[i][j];
        }
        //cout << endl;
    }
    size = content[0].size();

    return ans;
}

int main()
{
    string** ans;
    int degree = 1;
    cout << "Enter degree of B tree: ";
    cin >> degree;
    BTree<float> t(degree); // A B-Tree with minimum degree 3

    int ind;
    cout << "Enter type of Indexing: ";
    cin >> ind;

    switch (ind) {
    case 1:
        int size = 0;
        ans = ReadFromFileB("NCHS_-_Leading_Causes_of_Death__United_States_1.csv", size);
        float temp;
        for (int c = 1; c < 50; c++) {
            temp = stof(ans[c][1]);
            t.insert(temp, temp, stoi(ans[c][1]),ans[c][4], stoi(ans[c][5]), stof(ans[c][6]));
        }
        break;
    }
    t.traverse();
    

    return 0;
} 