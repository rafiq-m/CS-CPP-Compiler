#pragma once
#include<iostream>
#include<stdio.h>
#include"LinkedList.h"


using namespace std;

class Token
{
private:
	LinkedList* list = new LinkedList();
	string keyword[25] = { "if","else","for","while","void","return",
		"break","continue","true","false","NULL","class","extends","private",
		"public","protected","this","static","new","abstract","final","try","catch","finally","namespace"};
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
		regex floatrgx("[+-]{0,1}[0-9]*[\\.][0-9]+");
		regex charConst("\\'([\\\\][torbn])\\'");
		regex char1Const("\\'\.?\\'");
		regex digit("[+-]{0,1}[0-9]+");
		regex isID("([_a-zA-Z][_A-Za-z0-9]*[A-Za-z0-9])|[A-Za-z]");
		regex sttring("\"([a-zA-Z0-9]?([\\\\][torbna0\"\'\\\\])?|[^a-zA-Z0-9\\\\])*\"");

		if (value_part != "")
		{
			if (regex_match(string(1, value_part[0]), isalphabet))		//if alphabet or ID
			{
				if (regex_match(value_part, isID))
				{
					string CP = isKeyWord(value_part);
					if (CP == "")
					{
						if (isDT(value_part))
						{
							list->append("DT", value_part, line_no);
						}
						else
						{
							list->append("ID", value_part, line_no);
						}
					}
					else
					{
							list->append(CP, " _ ", line_no);
					}
				}
				else
				{
					list->append("invalid_lexene", value_part, line_no);
				}
			}
			else if (regex_match(value_part, sttring))			//String constant?
			{
					list->append("string_const", value_part.substr(1,value_part.size()-2), line_no);
			}
			else if (regex_match(value_part, charConst) || regex_match(value_part, char1Const))			//char constant
			{
				list->append("char_const", value_part.substr(1,value_part.size()-2), line_no);
			}
			else if (regex_match(value_part, digit))	//if digit
			{
				list->append("int_const", value_part, line_no);
			}
			else if (regex_match(value_part, floatrgx))		//if float
			{
				list->append("float_const", value_part, line_no);
			}
			else if (value_part == ".")					//if dot
			{
				list->append(value_part," _ ", line_no);
			}
			else
			{
				list->append("invalid_lexene", value_part, line_no);
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

	LinkedList* tokenPointer()
	{
		return list;
	}
};

