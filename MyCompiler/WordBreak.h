#pragma once
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <regex>
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
		bool is_another_dot = false;
		int lineNo = 1;
	public:
	WordBreak(string inputFile)
	{
		count = 0;
		ifstream myInputFile(inputFile);
		while (myInputFile.get(words[count]))
		{
			count++;
		}
		mySplit();		//breaks whole sentence into pieces
		show();
	}

	void mySplit() 
	{
		regex isdigit("[0-9]+");
		regex isAlphaDigit("[A-Za-z0-9_]+");
		string temp = "";
		for (int i = 0; i < count; i++)
		{
			bool not_any = false;

			if (words[i] == '\/' && words[i + 1] == '*')
			{
				not_any = true;
				//not_any true nhi kiya kiyonke agla character hamein identifier me daalna he
				i += 2;
				while (true && i <= count)
				{
					if (words[i + 1] == '\*' && words[i + 2] == '\/')
					{
						break;
					}
					if (words[i] == '\n')
					{
						lineNo++;
					}
					i++;
				}
				i += 3;
			}

			if (words[i] == '\/' && words[i + 1] == '\/')
			{
				not_any = true;
				while (words[i] != '\n')
				{
					i++;
				}
			}

			if (words[i] == '.') 
			{
				not_any = true;
				if (!regex_match(temp, isdigit)) 
				{
					token.generateToken(temp, lineNo);
					temp = "";
				}
				if(regex_match(string(1,words[i+1]),isdigit))
				{
					//Dot add karaya he
					temp += words[i];		
					i++;	
					//Dot ke baad wala digit check horaha 
					while (regex_match(string(1,words[i]), isAlphaDigit))
					{
						temp += words[i];
						i++;
					}
					token.generateToken(temp, lineNo);
					temp = "";
				}
				else
				{
					token.generateToken(temp, lineNo);
					temp = "";
					token.generateToken(".", lineNo);
					i++;
					while (regex_match(string(1, words[i]), isAlphaDigit))
					{
						temp += words[i];
						i++;
					}
					token.generateToken(temp, lineNo);
					temp = "";
					i--;
				}
			}
			
			if (words[i] == '{' || words[i] == '(' || words[i] == '[' || words[i] == '}' || words[i] == ')' || words[i] == ']' || words[i] == ' ' || words[i] == ';' || words[i] == '\n' || words[i] == ',' )
			{
				not_any = true;
				if (words[i] == ' ')
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
					token.generateToken(string(1, words[i])," _ ", lineNo);
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
					token.generateToken(string(1, words[i]) + words[i + 1], " _ ", lineNo);
					i++;
				}
				else if (words[i] == '|' && words[i+1] == '|')
				{
					token.generateToken(temp, lineNo);
					temp = "";
					token.generateToken(string(1, words[i]) + words[i + 1], " _ ", lineNo);
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
				not_any = true;
				token.generateToken(temp, lineNo);
				temp = "";
				temp += words[i];
				i++;
				while (words[i] != '\"' && i < count)
				{
					if (words[i] == '\\')
					{
						if (words[i + 1] == '\n')
						{
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
				if (words[i] == '\"')temp += words[i];
				token.generateToken(temp, lineNo);
				temp = "";
				if (words[i] == '\n')
				{
					lineNo++;
				}
			}

			if (words[i] == '\'')
			{
				token.generateToken(temp, lineNo);
				temp = "";
				not_any = true;
				temp += words[i];
				i++;
				if (words[i] == '\n')
				{
					token.generateToken(temp, lineNo);
					temp = "";
					lineNo++;
				}
				else if (words[i] == '\'')
				{
					i--;
				}
				else
				{
					if (words[i] == '\\')
					{
						temp += words[i];
						i++;
						temp += words[i];
						i++;
						if (words[i] == '\'') 
							temp += words[i];
						else if (words[i] == '\n')
						{
							token.generateToken(temp, lineNo);
							temp = "";
							lineNo++;
						}
					}
					else
					{
						temp += words[i];
						i++;
						if (words[i] == '\'')
							temp += words[i];
						else
							i--;
					}
				}
				token.generateToken(temp, lineNo);
				temp = "";
			}

			if(!not_any)
			{
				if(words[i] != '\t' && words[i] != ' ')
					temp += words[i];	
			}
		}
		token.generateToken(temp, lineNo);
	}

	void show()
	{
		token.printList();
	}
};


