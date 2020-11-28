#pragma once
#include<iostream>
#include<stdio.h>
#include"LinkedList.h"


using namespace std;

class Token
{
private:
	LinkedList* list = new LinkedList();
	string keyword[24] = { "if","else","for","while","void","return",
		"break","continue","true","false","NULL","class","extends","private",
		"public","protected","this","static","new","abstract","final","try","catch","finally" };
	string DT[6] = { "int","float","char","string","bool","var" };
	
public:
	void generateToken(string class_part, string value_part, int line_no) 
	{
		if (value_part != "")
			list->append(class_part, value_part, line_no);
	}
	void generateToken(string value_part, int line_no)
	{
		regex isalphabet("[_A-Za-z]");
		regex floatrgx("[+-]{0,1}[0-9]*.[0-9]+");
		regex digit("[+-]{0,1}[0-9]+");
		regex isID("([_a-zA-Z][_A-Za-z0-9]*[A-Za-z0-9])|[A-Za-z]");

		if (value_part != "")
		{
			if (regex_match(string(1, value_part[0]), isalphabet))		//if alphabet or ID
			{
				if (regex_match(value_part, isID))
				{
					string CP = isKeyWord(value_part);
					if (CP == "")
					{
						list->append("ID", value_part, line_no);
					}
					else
					{
						list->append(CP, " _ ", line_no);
					}
				}
				else
				{
					list->append("InvalidLexene", value_part, line_no);
				}
			}
			else if (value_part[0] == '\"')			//String constant?
			{
				if (value_part[value_part.size() - 1] == '\"')
				{
					list->append("string_const", value_part.substr(1,value_part.size()-2), line_no);
				}
				else
				{
					list->append("InvalidLexene", value_part, line_no);
				}
			}
			else if (value_part[0] == '\'')			//char constant
			{
				if (value_part[value_part.size() - 1] == '\'' && value_part.size() >= 3 && value_part.size() <= 4)
				{
					list->append("char_const", value_part.substr(1,value_part.size()-2), line_no);
				}
				else
				{
					list->append("InvalidLexene", value_part, line_no);
				}
			}
			else if (regex_match(value_part, digit))	//if digit
			{
				list->append("Int_const", value_part, line_no);
			}
			else if (regex_match(value_part, floatrgx))		//if float
			{
				list->append("Float_const", value_part, line_no);
			}
			else if (value_part == ".")					//if dot
			{
				list->append(value_part," _ ", line_no);
			}
			else
			{
				list->append("InvalidLexene", value_part, line_no);
			}	
		}
	}

	string isKeyWord(string word) 
	{
		for (int i = 0; i < sizeof(keyword)/sizeof(keyword[0]); i++)
		{
			if (word == keyword[i]) 
			{
				return keyword[i];
			}
		}
		return "";
	}

	bool isDT(string word)
	{
		for (int i = 0; i < sizeof(DT) / sizeof(DT[0]); i++)
		{
			if (word == DT[i])
			{
				return true;
			}
		}
		return false;
	}

	void printList()
	{
		list->print();
	}
};

