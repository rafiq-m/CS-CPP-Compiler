#pragma once
#include<iostream>
#include<stdio.h>

using namespace std;

class Node {
public:
	string class_part;
	string value_part;
	int line_no;
	Node* next;
	Node(string class_part, string value_part, int line_no) {
		this->class_part = class_part;
		this->value_part = value_part;
		this->line_no = line_no;
		next = nullptr;
	}
};
class LinkedList
{
private:
	Node* root = nullptr;
	Node* tail = nullptr;

public:
	void append(string class_part, string value_part, int line_no) {
		Node* temp = new Node(class_part, value_part, line_no);
		if (this->root == nullptr) {
			this->root = temp;
			this->tail = temp;
		}
		else {
			tail->next = temp;
			tail = temp;
		}
	}


	void print()
	{
		Node* troot = root;
		while (troot != NULL) {
			cout << troot->class_part <<", "<< troot->value_part <<", "<< troot->line_no << endl;
			troot = troot->next;
		}
	}



};

