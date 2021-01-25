#include <iostream>
#include<stdio.h>
#include<fstream>
#include "WordBreak.h"
#include <string>
#include "Token.h"
#include "LinkedList.h"

using namespace std;

int main()
{
	WordBreak *word = new WordBreak("input.txt");
	LinkedList *tokens = word->getTokens();
	tokens->append("$", "_", -1); 
	tokens->print();
}

