#include <iostream>
#include<stdio.h>
#include<fstream>
#include "WordBreak.h"
#include <string>

using namespace std;

int main()
{
	//starts here
	/*regex sttring("\"([a-zA-Z0-9]([\\\\][torbn]){0,1}|[^a-zA-Z0-9\\\\])*\"");
	string s = "\"s\\ba9132ja\\ndlk\"";
	cout << s << endl;
	if (regex_match(s, sttring)) 
	{
		cout << "Hello" << endl;
	}*/
	WordBreak *word = new WordBreak("input.txt");
}

