#pragma once
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include "Token.h"
#include "LinkedList.h"
using namespace std;



class WordBreak
{
	private:
		char words[1000];
		int count;
		string temp;
		Token token;
		int lineNo = 1;
	public:
	WordBreak(string inputFile)
	{
		count = 0;
		ifstream myInputFile(inputFile);
		while (myInputFile.get(words[count])) {
			count++;
		}
		mySplit();
	}

	void mySplit() 
	{
		string temp = "";
		for (int i = 0; i < count; i++)
		{
			bool not_any = false;

			if (words[i] == '{' || words[i] == '(' || words[i] == '[' || words[i] == '}' || words[i] == ')' || words[i] == ']' || words[i] == ' ' || words[i] == ';' || words[i] == '\n' || words[i] == ',')
			{
				not_any = true;
				if (words[i] == ' ' || words[i] == ';')
				{
					token.generateToken(temp, lineNo);
					temp = "";
				}
				else if(words[i] == '\n')
				{
					token.generateToken(temp, lineNo);
					lineNo++;
					temp = "";
				}
				else
				{
					token.generateToken(temp, lineNo);
					token.generateToken(string(1, words[i]), lineNo);
					temp = "";
				}
			}



			if (words[i] == '+' || words[i] == '-' || words[i] == '*' || words[i] == '/' || words[i] == '%')
			{
				not_any = true;
				if (words[i] == '+' && words[i + 1] == '+')
				{
					token.generateToken(temp, lineNo);
					token.generateToken("Inc/Dec", string(1, words[i]) + words[i + 1], lineNo);
					temp = "";
					i++;
				}
				else if (words[i] == '-' && words[i + 1] == '-')
				{
					token.generateToken(temp, lineNo);
					token.generateToken("Inc/Dec", string(1, words[i]) + words[i + 1], lineNo);
					temp = "";
					i++;
				}
				else if(words[i] == '+' || words[i] == '-')
				{
					token.generateToken(temp, lineNo);
					token.generateToken("PM", string(1,words[i]), lineNo);
					temp = "";
				}
				else 
				{
					token.generateToken(temp, lineNo);
					token.generateToken("MDM", string(1,words[i]), lineNo);
					temp = "";
				}
			}



			if (words[i] == '=' || words[i] == '!' || words[i] == '<' || words[i] == '>')
			{
				not_any = true;
				if (words[i + 1] == '=') 
				{
					token.generateToken(temp, lineNo);
					temp = "";
					token.generateToken("ROP", string(1, words[i]) + words[i + 1], lineNo);
					i++;
				}
				else if(words[i] == '!')
				{
					token.generateToken(temp, lineNo);
					token.generateToken("Not", string(1,words[i]), lineNo);
					temp = "";
				}
				else if (words[i] == '=')
				{
					token.generateToken(temp, lineNo);
					token.generateToken("EqlTo", string(1, words[i]), lineNo);
					temp = "";
				}
				else if (words[i] == '>' || words[i] == '<') 
				{
					token.generateToken(temp, lineNo);
					token.generateToken("ROP", string(1, words[i]), lineNo);
					temp = "";
				}
			}



			if (words[i] == '&' || words[i] == '|')
			{
				not_any = true;
				if (words[i] == '&' && words[i+1] == '&') 
				{
					token.generateToken(temp, lineNo);
					temp = "";
					token.generateToken("And", string(1, words[i]) + words[i + 1], lineNo);
					i++;
				}
				else if (words[i] == '|' && words[i+1] == '|')
				{
					token.generateToken(temp, lineNo);
					temp = "";
					token.generateToken("Or", string(1, words[i]) + words[i + 1], lineNo);
					i++;
				}
				else 
				{
					token.generateToken(temp, lineNo);
					temp = "";
					token.generateToken("InvalidLexene", string(1, words[i]), lineNo);
				}
			}



			if (words[i] == '\"')
			{
				i++;
				not_any = true;
				token.generateToken(temp, lineNo);
				temp = "";
				while (words[i] != '\"' && i < count)
				{
					if (words[i] == '\\')
					{
						temp += words[i];
						if (words[i + 1] == '\n')
						{
							cout << lineNo << endl;
							lineNo++;
						}
						else 
						{
						temp += words[i + 1];
						}
						i += 2;
					}
					else if (words[i] == '\n')
					{
						break;
					}
					else
					{
						temp += words[i];
						i++;
					}
				}

				if (i < count)
				{
					token.generateToken(temp, lineNo);
					temp = "";
				}
				else
				{
					token.generateToken("InvalidLexene", "\"" + temp, lineNo);
					temp = "";
				}
			}



			if(!not_any)
			{
				temp += words[i];
			}
		}
		token.generateToken(temp, lineNo);
	}
};


