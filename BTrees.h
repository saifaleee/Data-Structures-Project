#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;
int one = 1;
int zero = 0;


template <typename T>
struct BTreeNode {
    BTreeNode<T>** nexts;
    T* keys;
    string* directories;
    int current_keys;
    bool leaf;
    int range;

    //Data
    int* ID;
    int* year;
    //string* //cause;
    string* state;
    int* deaths;
    float* death_rate;


    BTreeNode(bool l, int r): range(r), leaf(l), current_keys(zero) {
        keys = new T[2 * range - one];
        nexts = new BTreeNode<T> * [2 * range];
        directories = new string[range];

        ID = new int[2 * range - one];
        year = new int[2 * range - one];
        //cause = new string[2 * range - one];
        state = new string[2 * range - one];
        deaths = new int[2 * range - one];
        death_rate = new float[2 * range - one];
    }
    int findKey(int k) {
        int ind = zero;
        for (; ind < current_keys && keys[ind] < k; ind++);
        return ind;
    }

    void splitChild(int i, BTreeNode<T>* kid) {

        BTreeNode<T>* temp = new BTreeNode<T>(kid->leaf, kid->range);
        temp->current_keys = range - one;

        for (int j = zero; j < range - one; j++) {
            temp->keys[j] = kid->keys[j + range];
            temp->ID[j] = kid->ID[j + range];
            temp->year[j] = kid->year[j + range];
            //temp->//cause[j] = kid->//cause[j + range];
            temp->state[j] = kid->state[j + range];
            temp->deaths[j] = kid->deaths[j + range];
            temp->death_rate[j] = kid->death_rate[j + range];
        }

        if (kid->leaf == false) {
            for (int j = zero; j < range; j++) {
                temp->nexts[j] = kid->nexts[j + range];
            }
        }

        kid->current_keys = range - one;
        for (int j = current_keys; j >= i + one; j--) {
            nexts[j + one] = nexts[j];
        }

        nexts[i + one] = temp;
        for (int j = current_keys - one; j >= i; j--) {
            keys[j + one] = keys[j];

            ID[j + one] = ID[j];
            year[j + one] = year[j];
            //cause[j + one] = //cause[j];
            state[j + one] = state[j];
            deaths[j + one] = deaths[j];
            death_rate[j + one] = death_rate[j];
        }

        keys[i] = kid->keys[range - one];
        ID[i] = kid->ID[range - one];
        year[i] = kid->year[range - one];
        //cause[i] = kid->//cause[range - one];
        state[i] = kid->state[range - one];
        deaths[i] = kid->deaths[range - one];
        death_rate[i] = kid->death_rate[range - one];

        current_keys = current_keys + one;
    }


    void traverse() {
        int i;
        for (i = zero; i < current_keys; i++) {
            if (leaf == false) {
                nexts[i]->traverse();
            }
            cout << " " << keys[i];
        }
        if (leaf == false) {
            nexts[i]->traverse();
        }
    }


    void insertNonFull(T k, int id, int Year, string State, int Deaths, float Death_rate) {
        int i = current_keys - one;
        if (leaf == true) {
            for (; i >= zero && keys[i] > k; i--) {
                keys[i + one] = keys[i];
            }
            keys[i + one] = k;
            ID[i + one] = id;
            year[i + one] = Year;
            //cause[static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(i) + one] = Cause;
            state[static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(i) + one] = State;
            deaths[i + one] = Deaths;
            death_rate[i + one] = Death_rate;
            current_keys = current_keys + one;
        }
        else {
            for (; i >= zero && keys[i] > k; i--);
            if (nexts[i + one]->current_keys == 2 * range - one) {
                splitChild(i + one, nexts[i + one]);
                if (keys[i + one] < k) {
                    i++;
                }
            }
            nexts[i + one]->insertNonFull(k, id, Year, State, Deaths, Death_rate);
        }
    }



    BTreeNode<T>* search(int k) {

        int i = zero;
        for (; i < current_keys && k > keys[i]; i++);

        if (keys[i] == k) {
            return this;
        }

        if (leaf == true) {
            return NULL;
        }
        return nexts[i]->search(k);
    }

    void removeFromLeaf(int idx) {
        for (int i = idx + one; i < current_keys; i++) {
            keys[i - one] = keys[i];
            ID[i - one] = ID[i];
            year[i - one] = year[i];
            //cause[i - one] = //cause[i];
            state[i - one] = state[i];
            deaths[i - one] = deaths[i];
            death_rate[i - one] = death_rate[i];

        }

        current_keys = current_keys - one;

        return;
    }
    void removeFromNonLeaf(int idx) {

        int k = keys[idx];

        if (nexts[idx]->current_keys >= range)
        {
            int pred = getPred(idx);
            keys[idx] = pred;
            nexts[idx]->remove(pred);
        }

        else if (nexts[idx + one]->current_keys >= range)
        {
            int succ = getSucc(idx);
            keys[idx] = succ;
            nexts[idx + one]->remove(succ);
        }

        else
        {
            merge(idx);
            nexts[idx]->remove(k);
        }
        return;
    }

    int getPred(int idx) {
        BTreeNode<T>* cur = nexts[idx];
        while (!cur->leaf)
            cur = cur->nexts[cur->current_keys];

        return cur->keys[cur->current_keys - one];
    }

    int getSucc(int idx) {


        BTreeNode<T>* cur = nexts[idx + one];
        while (!cur->leaf)
            cur = cur->nexts[zero];


        return cur->keys[zero];
    }
    void fill(int idx) {


        if (idx != zero && nexts[idx - one]->current_keys >= range)
            borrowFromPrev(idx);

        else if (idx != current_keys && nexts[idx + one]->current_keys >= range)
            borrowFromNext(idx);


        else
        {
            if (idx != current_keys)
                merge(idx);
            else
                merge(idx - one);
        }
        return;
    }
    void borrowFromPrev(int idx) {

        BTreeNode<T>* child = nexts[idx];
        BTreeNode<T>* sibling = nexts[idx - one];

        for (int i = child->current_keys - one; i >= zero; --i) {
            child->keys[(child->current_keys)] = child->keys[i];
            child->ID[(child->current_keys)] = child->ID[i];
            child->year[(child->current_keys)] = child->year[i];
            //child->//cause[(child->current_keys)] = child->//cause[i];
            child->state[(child->current_keys)] = child->state[i];
            child->deaths[(child->current_keys)] = child->deaths[i];
            child->death_rate[(child->current_keys)] = child->death_rate[i];
        }

        if (!child->leaf)
        {
            for (int i = child->current_keys; i >= zero; --i)
                child->nexts[(child->current_keys)] = child->nexts[i];
        }

        child->keys[zero] = keys[idx - one];
        child->ID[zero] = child->ID[idx - one];
        child->year[zero] = child->year[idx - one];
        //child->//cause[zero] = child->//cause[idx - one];
        child->state[zero] = child->state[idx - one];
        child->deaths[zero] = child->deaths[idx - one];
        child->death_rate[zero] = child->death_rate[idx - one];

        if (!child->leaf)
            child->nexts[zero] = sibling->nexts[sibling->current_keys];

        keys[idx - one] = sibling->keys[sibling->current_keys - one];
        ID[(child->current_keys)] = sibling->ID[sibling->current_keys - one];
        year[(child->current_keys)] = sibling->year[sibling->current_keys - one];
        //cause[(child->current_keys)] = sibling->//cause[sibling->current_keys - one];
        state[(child->current_keys)] = sibling->state[sibling->current_keys - one];
        deaths[(child->current_keys)] = sibling->deaths[sibling->current_keys - one];
        death_rate[(child->current_keys)] = sibling->death_rate[sibling->current_keys - one];

        child->current_keys += one;
        sibling->current_keys -= one;

        return;
    }
    void borrowFromNext(int idx) {

        BTreeNode<T>* child = nexts[idx];
        BTreeNode<T>* sibling = nexts[idx + one];

        child->keys[(child->current_keys)] = keys[idx];
        child->ID[(child->current_keys)] = ID[idx];
        child->year[(child->current_keys)] = year[idx];
        child->//cause[(child->current_keys)] = //cause[idx];
        child->state[(child->current_keys)] = state[idx];
        child->deaths[(child->current_keys)] = deaths[idx];
        child->death_rate[(child->current_keys)] = death_rate[idx];

        if (!(child->leaf))
            child->nexts[(child->current_keys) + one] = sibling->nexts[zero];
            
        keys[idx] = sibling->keys[zero];

        for (int i = one; i < sibling->current_keys; ++i) {
            sibling->keys[i - one] = sibling->keys[i];
            sibling->ID[i - one] = sibling->ID[i];
            sibling->year[i - one] = sibling->year[i];
            //sibling->//cause[i - one] = sibling->//cause[i];
            sibling->state[i - one] = sibling->state[i];
            sibling->deaths[i - one] = sibling->deaths[i];
            sibling->death_rate[i - one] = sibling->death_rate[i];
        }

        if (!sibling->leaf)
        {
            for (int i = one; i <= sibling->current_keys; ++i)
                sibling->nexts[i - one] = sibling->nexts[i];
        }

        child->current_keys += one;
        sibling->current_keys -= one;

        return;
    }
    void merge(int idx) {
        BTreeNode<T>* child = nexts[idx];
        BTreeNode<T>* sibling = nexts[idx + one];

        child->keys[range - one] = keys[idx];
        child->ID[range - one] = ID[idx];
        child->year[range - one] = year[idx];
        //child->//cause[range - one] = //cause[idx];
        child->state[range - one] = state[idx];
        child->deaths[range - one] = deaths[idx];
        child->death_rate[range - one] = death_rate[idx];

        for (int i = zero; i < sibling->current_keys; ++i) {
            child->keys[i + range] = sibling->keys[i];
            child->ID[i + range] = sibling->ID[i];
            child->year[i + range] = sibling->year[i];
            //child->//cause[i + range] = sibling->//cause[i];
            child->state[i + range] = sibling->state[i];
            child->deaths[i + range] = sibling->deaths[i];
            child->death_rate[i + range] = sibling->death_rate[i];
        }

        if (!child->leaf)
        {
            for (int i = zero; i <= sibling->current_keys; ++i)
                child->nexts[i + range] = sibling->nexts[i];
        }

        for (int i = idx + one; i < current_keys; ++i) {
            keys[i - one] = keys[i];
            ID[i - one] = ID[i];
            year[i - one] = year[i];
            //cause[i - one] = //cause[i];
            state[i - one] = state[i];
            deaths[i - one] = deaths[i];
            death_rate[i - one] = death_rate[i];
        }


        for (int i = idx + 2; i <= current_keys; ++i)
            nexts[i - one] = nexts[i];

        child->current_keys += sibling->current_keys + one;
        current_keys--;

        delete(sibling);
        return;
    }
    void remove(int k) {
        int idx = findKey(k);

        if (idx < current_keys && keys[idx] == k) {
            if (leaf) {
                removeFromLeaf(idx);
            }
            else {
                removeFromNonLeaf(idx);
            }
        }
        else {
            if (leaf) {
                cout << "The key " << k << " is does not exist in the tree\n";
                return;
            }
            bool flag;
            if (idx == current_keys) {
                flag = one;
            }
            else {
                flag = zero;
            }

            if (nexts[idx]->current_keys < range) {
                fill(idx);
            }

            if (flag && idx > current_keys) {
                nexts[idx - one]->remove(k);
            }
            else {
                nexts[idx]->remove(k);
            }
        }
        return;
    }

};

template <typename T>
class BTree {
    BTreeNode<T>* root;
    int range;
public:
    BTree(int r) : range(r), root(NULL) {}
    void traverse()
    {
        if (root != NULL)
            root->traverse();
    }

    BTreeNode<T>* search(int k)
    {
        if (root == NULL) {
            return NULL;
        }
        else {
            return root->search(k);
        }
    }
    void insert(int k, int id, int Year, string State, int Deaths, float Death_rate) {
        BTreeNode<T>* temp = root;

        if (temp == NULL) {
            temp = new BTreeNode<T>(true, range);
            temp->keys[zero] = k;
            temp->ID[zero] = id;
            temp->year[zero] = Year;
            //temp->//cause[zero] = Cause;
            temp->state[zero] = State;
            temp->deaths[zero] = Deaths;
            temp->death_rate[zero] = Death_rate;
            temp->current_keys = one;
        }
        else {
            if (temp->current_keys == 2 * range - one) {
                BTreeNode<T>* s = new BTreeNode<T>(false, range);
                s->nexts[zero] = temp;
                s->splitChild(zero, temp);
                int i = zero;
                if (s->keys[zero] < k) {
                    i++;
                }
                s->nexts[i]->insertNonFull(k, id, Year, State, Deaths, Death_rate);
                temp = s;
            }

            else {
                temp->insertNonFull(k, id, Year, State, Deaths, Death_rate);
            }
        }
        root = temp;
    }
    void remove(int k) {
        if (!root)
        {
            cout << "The tree is empty\current_keys";
            return;
        }

        root->remove(k);

        if (root->current_keys == zero)
        {
            BTreeNode<T>* tmp = root;
            if (root->leaf)
                root = NULL;
            else
                root = root->nexts[zero];

            delete tmp;
        }
        return;
    }


};








