#pragma once

#include<iostream>
#include<stdio.h>
#include<vector>

using namespace std;
class ClassNode
{
public:
	string name;
	string type;
	string access_modifier;
	string type_modifier;
public:
	ClassNode(string name, string type, string access_modifier, string type_modifier)
	{
		this->name = name;
		this->type = type;
		this->access_modifier = access_modifier;
		this->type_modifier = type_modifier;
	}

};
class ClassTable
{
	vector<ClassNode> class_table;


public:
	bool insertCT(string name, string type, string access_modifier, string type_modifier)
	{
		ClassNode* node = new ClassNode(name, type, access_modifier, type_modifier);
		if (class_table.empty())
		{
			class_table.push_back(*node);
			return true;
		}
		for (auto i = class_table.begin(); i != class_table.end(); ++i)
		{
			if (contains(type, "-"))
			{
				if (i->name == node->name && i->type.substr(0, i->type.find("-")) == type.substr(0, type.find("-")))
				{
					return false;
				}
			}
			else
			{
				if (i->name == node->name)
				{
					return false;
				}
			}
		}
		class_table.push_back(*node);
		return true;
	}

	string lookUpCT(string name)
	{
		for (auto i = class_table.begin(); i != class_table.end(); ++i)
		{
			if (i->name == name)
			{
				return i->type;
			}
		}
		return "NULL";
	}
	void printClassTable(string className)
	{
		cout << "-------printing Class Table of Class: " << className << "--------" << endl;
		for (auto i = class_table.begin(); i != class_table.end(); ++i)
		{
			cout << i->name << "\t\t\t" << i->type << "\t\t\t" << i->access_modifier << "\t\t\t" << i->type_modifier << endl;
		}
	}

private:
	bool contains(const std::string& str, const std::string substr)
	{
		if (str.size() < substr.size()) return false;

		for (int i = 0; i < str.size(); i++)
		{
			if (str.size() - i < substr.size()) return false;

			bool match = true;
			for (int j = 0; j < substr.size(); j++)
			{
				if (str.at(i + j) != substr.at(j))
				{
					match = false;
					break;
				}
			}
			if (match) return true;
		}
		return false;
	}
};

