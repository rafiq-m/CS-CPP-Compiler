#pragma once
#include <string>
#include<iostream>
#include "ClassTable.h"
#include "FunctionTable.h"
#include<stack>

using namespace std;


static int stackSize = 1;
class MNode
{
public:
	string name;
	string type;
	string access_modifier;
	string category;
	string parent;
	ClassTable* class_link;
	FunctionTable* function_link;
	MNode* next;

public:
	MNode(string name, string type, string access_modifier, string category, string parent)
	{
		class_link = new ClassTable();
		function_link = new FunctionTable();
		this->name = name;
		this->type = type;
		this->access_modifier = access_modifier;
		this->category = category;
		this->parent = parent;
		this->next = NULL;
	}
};
class MainTable
{
public:
	stack<int> stack_scope;
	MNode* head;
	MainTable()
	{
		head = NULL;
	}

	bool insertMainTable(string name, string type, string access_modifier, string category,string parent, ClassTable *class_link, FunctionTable *function_link)
	{
		MNode* node = new MNode(name, type, access_modifier, category, parent);
		if (head == NULL)
		{
			node->class_link = class_link;
			node->function_link = function_link;
			head = node;
		}
		else
		{
			MNode* thead = head;
			while (thead->next != NULL)
			{
				if (thead->name == name)
				{
					return false;
				}
				thead = thead->next;
			}
			if (thead->name == name)
			{
				return false;
			}
			node->class_link = class_link;
			node->function_link = function_link;
			thead->next = node;
		}
		//printMainTable();
		return true;
	}
	string lookupMT(string name, string *category)
	{

		MNode* thead = head;
		while (thead->next != NULL)
		{
			if (thead->name == name)
			{
				return thead->type;
			}
			thead = thead->next;
		}
		if (thead->name == name)
		{
			return thead->type;
		}
		return "NULL";
	}

	ClassTable* findClassTable(string name)
	{
		MNode* thead = head;
		while (thead != NULL)
		{
			if (thead->name == name)
			{
				break;
			}
			thead = thead->next;
		}
		return thead->class_link;
	}

	FunctionTable* findFunctionTable(string name)
	{
		MNode* thead = head;
		while (thead != NULL)
		{
			if (thead->name == name)
			{
				break;
			}
			thead = thead->next;
		}
		return thead->function_link;
	}

	int createScope()
	{
		stack_scope.push(stackSize);
		stackSize++;
		return stackSize-1;
	}

	int deleteScope()
	{
		stack_scope.pop();
		if (!stack_scope.empty())
		{
			return (stack_scope.top());
		}
		else
		{
			return -1;
		}
	}

	void printMainTable()
	{
		MNode* troot = head;
		while (troot != NULL)
		{
			cout << "[ " << troot->name << ", " << troot->type << ", " << troot->access_modifier << ", " << troot->category << ", " << troot->parent << ", " << &troot->class_link << ", " << &troot->function_link << " ]" << endl;
			troot = troot->next;
		}
		troot = NULL;
		delete troot;
	}	
};

