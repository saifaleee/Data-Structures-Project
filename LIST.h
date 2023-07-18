#pragma once
#pragma once
#include <iostream>
#include<fstream>
#include <sstream>
using namespace std;

template<typename T>
struct Lnode
{
	T data;
	Lnode* next;
	Lnode() 
	{
		next = nullptr;
	//	data = 0;
	}
};
template<typename T>
class List {
public:
	Lnode<T>* head;
	Lnode<T>* tail;
	int ssize;

	List() 
	{
		head = nullptr;
		tail = nullptr;
		//data = nullptr;
		ssize = 0;
	}

	bool isEmpty()
	{
		return (head == NULL);
	}

	void Insert(T data)
	{
		if (isEmpty()) 
		{
			Lnode<T>* newLnode = new Lnode<T>();
			newLnode->data = data;
			head = newLnode;
			head->next = head;
			tail = newLnode;
			ssize++;
			return;
		}

		Lnode<T>* newLnode = new Lnode<T>();
		newLnode->data = data;
		tail->next = newLnode;
		tail = newLnode;
		tail->next = head;
		ssize++;
		return;
	}

	void Delete(int index) {
		Lnode<T>* temp = head;
		if (index == 0)
		{
			head = temp->next;
			delete temp;
		}
		else
		{
			for (int i = 0; i < index; i++)
				temp = temp->next;

			Lnode<T>* del = temp->next;
			temp->next = temp->next->next;
			delete del;
		}
		ssize--;
	}

	int getSize() {
		return ssize;
	}

	string getData(int index) {
		Lnode<T>* temp = head;
		if (temp != NULL)
		{
			for (int i = 0; i < index && temp != nullptr; i++)
				temp = temp->next;

			return temp->data;
		}
	}
	int getIndex(T data) {
		Lnode<T>* temp = head;
		if (temp != NULL)
		{
			for (int i = 0; i < ssize && temp != nullptr; i++)
			{
				if (temp->data == data)
					return i;

				temp = temp->next;
			}
		}
	}
	void displayall()
	{
		Lnode<T>* temp = head;
		if (temp != NULL)
		{
			for (int i = 0; i < ssize && temp != nullptr; i++)
			{
				cout << temp->data << " ";
				temp = temp->next;
			}
		}
	}

	//~List() 
	//{
	//	/*Lnode* temp = head;
	//	for (int i = 0; i < ssize; i++) {
	//		head = head->next;
	//		delete[] temp;
	//		temp = head;
	//	}*/
	//}
};


int** ReadFromFile()
{
	List<int> City;
	int** data;
	data = new int* [25]{};
	for (int i = 0; i < 25; i++)
	{
		data[i] = new int[25]{};
	}


	int count = 0;
	int city_count = 0;
	ifstream file("GraphData.csv");
	for (int row = 0; row < 26; ++row)
	{
		string line;
		getline(file, line);


		if (row == 0)
			continue;
		else
		{
			stringstream iss(line);

			for (int col = 0, bigcount = 0; col < 26; ++col)
			{
				string val;
				getline(iss, val, ',');


				if (col == 0)
				{
					City.Insert(1);
					city_count++;
				}
				else
				{
					stringstream convertor(val);
					convertor >> data[count][bigcount];
					bigcount++;
				}
				if (!iss.good())
					break;
			}
			// if (row != 0)
			count++;
		}
	}
	return data;
}
