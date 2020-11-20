#pragma once
#include<iostream>
#include<stdio.h>
#include"LinkedList.h"

using namespace std;

class Token
{
private:
	string CP;
	string VP;
	int lineNo;
	LinkedList* list = new LinkedList();
public:
	/*string getCP() {
		return this->CP;
	}
	void setCP(string CP) {
		this->CP = CP;
	}
	string getVP() {
		return this->CP;
	}
	void setVP(string VP) {
		this->VP = VP;
	}
	int getLineNo() {
		return this->lineNo;
	}
	void setLineNo(int lineNo) {
		this->lineNo = lineNo;
	}*/
	void generateToken(string class_part, string value_part, int line_no) 
	{
		if (value_part != "")
			cout << class_part << " " << value_part << " " << line_no << endl;
	}
	void generateToken(string value_part, int line_no)
	{
		if (value_part != "")
			cout << "KW " << value_part << " " << line_no<< endl;
	}

	string isKeyWord(string word) 
	{
		return "Keyword";
	}


};

