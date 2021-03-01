#pragma once
#include <string>
#include<iostream>
#include<stack>
#include <vector>

using namespace std;
class FNode
{
public:
	string name;
	string type;
	int scope;
	FNode(string name, string type, int scope)
	{
		this->name = name;
		this->type = type;
		this->scope = scope;
	}
};

class FunctionTable
{
	vector<FNode> functiontable;

public:
	bool insertFT(string name, string type, int scope)
	{
		FNode* node = new FNode(name, type, scope);
		if (functiontable.empty())
		{
			functiontable.push_back(*node);
			return true;
		}
		for (auto i = functiontable.begin(); i != functiontable.end(); ++i)
		{
			if (i->name == name && i->scope == scope)
			{
				return false;
			}
		}
		functiontable.push_back(*node);
		return true;
	}

	string lookUpFT(string name, int scope, stack<int> stack_scope)
	{
		while (!stack_scope.empty())
		{
			for (auto i = functiontable.begin(); i != functiontable.end(); ++i)
			{
				if (i->name == name)
				{
					return i->type;
				}
			}
			scope = stack_scope.top();
			stack_scope.pop();
		}
		return "NULL";
	}
	void printFunctionTable(string className)
	{
		cout << "-------printing Function Table of Class: " << className <<"--------" << endl;
		for (auto i = functiontable.begin(); i != functiontable.end(); ++i)
		{
			cout << i->name << "\t" << i->type << "\t" << "\t" << i->scope << endl;
		}
	}
};

