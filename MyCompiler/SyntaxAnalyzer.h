#pragma once
#include "LinkedList.h"
#include "MainTable.h"
#include "FunctionTable.h"
#include <stack>
#include "ClassTable.h"
class SyntaxAnalyzer
{
	stack<string> my_stack;
	string class_name = "empty";
	string class_type;
	string class_access_modifier;
	string class_parent;
	string class_category;
	MainTable* maintable = new MainTable();

	string global_type;

	int current_scope;
	ClassTable* classtable = new ClassTable();
	FunctionTable* functiontable = new FunctionTable();
	string name;
	string type;
	string type_def;
	string ret_def;
	LinkedList* t;
public:
	SyntaxAnalyzer(LinkedList* tokens)
	{
		this->t = tokens;
		checkSyntactically();
	}
	void checkSyntactically()
	{
		if (S())
		{
			if (t->getClassPart() == "$")
				cout << "Okay All correct !" << endl;
			else
				cout << "Error at Line No: " << t->getLineno() << "   " << t->getClassPart() << endl;
		}
		else
			cout << "Error at Line No: " << t->getLineno() << "   " << t->getClassPart() << endl;
		maintable->printMainTable();
	}

	bool practice()
	{
		if (t->getClassPart() == "ID")
		{
			t->next();
			if (t->getClassPart() == "{")
			{
				t->next();
				if (MST1())
				{
					if (t->getClassPart() == "}")
					{
						t->next();
						return true;
					}
				}
			}
		}
		return false;
	}

	bool dec()
	{
		if (t->getClassPart() == "DT")
		{
			t->next();
			if (dec_choice())
			{
				return true;
			}
		}
		return false;
	}

	bool dec_choice()
	{
		if (t->getClassPart() == "[")
		{
			t->next();
			if (t->getClassPart() == "]")
			{
				t->next();
				if (t->getClassPart() == "ID")
				{
					name = t->getValuePart();
					type += "[]";
					functiontable = maintable->findFunctionTable(my_stack.top());
					if (functiontable->insertFT(name, type, current_scope))
					{
					}
					else
					{
						cout << "Variable Redeclration Error at Line no: " << t->getLineno() << endl;
					}
					t->next();
					if (init_arr())
					{
						if (list_arr())
						{
							return true;
						}
					}
				}
			}
		}
		else if (t->getClassPart() == "ID")
		{
			name = t->getValuePart();
			functiontable = maintable->findFunctionTable(my_stack.top());
			if (functiontable->insertFT(name, type, current_scope))
			{
			}
			else
			{
				cout << "Variable Redeclration Error at Line no: " << t->getLineno() << endl;
			}
			t->next();
			if (init())
			{
				if (list())
				{
					return true;
				}
			}
		}
		return false;
	}

	bool init()
	{
		if (t->getClassPart() == "=")
		{
			t->next();
			string T4 = "";
			if (OE(T4))
			{
				string TR = compatibilityCheck(T4, type, "=");
				if (TR == "Incompatible")
				{
					cout << "Type is incompatible at Line No: " << t->getLineno() << endl;
				}
				return true;
			}			
		}
		else if (t->getClassPart() == ";" || t->getClassPart() == ",")
		{
			return true;
		}
		return false;
	}

	bool list()
	{
		if (t->getClassPart() == ";")
		{
			t->next();
			return true;
		}
		else if (t->getClassPart() == ",")
		{
			t->next();
			if (t->getClassPart() == "ID")
			{
				t->next();
				if (init())
				{
					if (list())
					{
						return true;
					}
				}
			}
		}
		return false;
	}

	bool init_arr()
	{
		if (t->getClassPart() == "=")
		{
			t->next();
			if (init_arr_choice())
			{
				return true;
			}
		}
		else if (t->getClassPart() == ";" || t->getClassPart() == ",")
		{
			return true;
		}
		return false;
	}

	bool list_arr()
	{
		if (t->getClassPart() == ";")
		{
			t->next();
			return true;
		}
		else if (t->getClassPart() == ",")
		{
			t->next();
			if (t->getClassPart() == "ID")
			{
				t->next();
				if (init_arr())
				{
					if (list_arr())
					{
						return true;
					}
				}
			}
		}
		return false;
	}

	bool init_arr_choice()
	{
		if (t->getClassPart() == "new")
		{
			t->next();
			if (t->getClassPart() == "DT")
			{
				t->next();
				if (t->getClassPart() == "[")
				{
					t->next();
					string T4 = "";
					if (OE(T4))
					{
						if (t->getClassPart() == "]")
						{
							t->next();
							if (return_choice())
							{
								return true;
							}
						}
					}
				}
			}
		}
		else if (t->getClassPart() == "{")
		{
			t->next();
			if (PL())
			{
				if (t->getClassPart() == "}")
				{
					t->next();
					return true;
				}
			}
		}
		else if (t->getClassPart() == "ID")
		{
			t->next();
			return true;
		}
		else if (t->getClassPart() == ";" || t->getClassPart() == ",")
		{
			return true;
		}
		return false;
	}

	bool this_st()
	{
		if (t->getClassPart() == "this")
		{
			t->next();
			if (t->getClassPart() == ".")
			{
				t->next();
				return true;
			}
		}
		else if (t->getClassPart() == "ID")
		{
			return true;
		}
		return false;
	}

	bool OE(string &T)
	{	
		if (t->getClassPart() == "int_const" || t->getClassPart() == "float_const" || t->getClassPart() == "char_const" || t->getClassPart() == "string_const"
			|| t->getClassPart() == "true" || t->getClassPart() == "false" || t->getClassPart() == "("
			|| t->getClassPart() == "!" || t->getClassPart() == "this" || t->getClassPart() == "ID" || t->getClassPart() == "inc_dec")
		{
			string T1 = "";
			if (AE(T1))
			{
				if (OE_(T1, T))
				{
					if (T == "") T = T1;
					return true;
				}
			}
		}
		return false;
	}

	bool OE_(string T1, string &T)
	{
		if (t->getClassPart() == "||")
		{
			string opr = t->getClassPart();
			t->next();
			string T2 = "";
			if (AE(T2))
			{
				string T3 = compatibilityCheck(T1, T2, opr);
				if (T3 == "Incompatible")
				{
					cout << "Type is incompatible at Line No: " << t->getLineno() << endl;
				}
				if (OE_(T3, T))
				{
					return true;
				}
			}
		}
		else if (t->getClassPart() == ")" || t->getClassPart() == "]" || t->getClassPart() == ";" || t->getClassPart() == "," || t->getClassPart() == "}")
		{
			T = T1;
			return true;
		}
		return false;
	}

	bool AE(string &T)
	{
		if (t->getClassPart() == "int_const" || t->getClassPart() == "float_const" || t->getClassPart() == "char_const" || t->getClassPart() == "string_const"
			|| t->getClassPart() == "true" || t->getClassPart() == "false" || t->getClassPart() == "("
			|| t->getClassPart() == "!" || t->getClassPart() == "this" || t->getClassPart() == "ID" || t->getClassPart() == "inc_dec")
		{
			string T1 = "";
			if (RE(T1))
			{
				if (AE_(T1, T))
				{
					if (T == "") T = T1;
					return true;
				}
			}
		}
		return false;
	}

	bool AE_(string T1, string& T)
	{
		if (t->getClassPart() == "&&")
		{
			string opr = t->getClassPart();
			t->next();
			string T2 = "";
			if (RE(T2))
			{
				string T3 = compatibilityCheck(T1, T2, opr);
				if (T3 == "Incompatible")
				{
					cout << "Type is incompatible at Line No: " << t->getLineno() << endl;
				}
				if (AE_(T3, T))
				{
					if (T == "") T = T1;
					return true;
				}
			}
		}
		else if (t->getClassPart() == "||" ||
			t->getClassPart() == ")" || t->getClassPart() == "]" || t->getClassPart() == ";" || t->getClassPart() == "," || t->getClassPart() == "}")
		{
			T = T1;
			return true;
		}
		return false;
	}

	bool RE(string &T)
	{
		if (t->getClassPart() == "int_const" || t->getClassPart() == "float_const" || t->getClassPart() == "char_const" || t->getClassPart() == "string_const"
			|| t->getClassPart() == "true" || t->getClassPart() == "false" || t->getClassPart() == "("
			|| t->getClassPart() == "!" || t->getClassPart() == "this" || t->getClassPart() == "ID" || t->getClassPart() == "inc_dec")
		{
			string T1 = "";
			if (PE(T1))
			{
				if (RE_(T1 , T))
				{
					return true;
				}
			}
		}
		return false;
	}

	bool RE_(string T1, string& T)
	{
		if (t->getClassPart() == "rop")
		{
			string opr = t->getValuePart();
			t->next();
			string T2 = "";
			if (PE(T2))
			{
				string T3 = compatibilityCheck(T1, T2, opr);
				if (T3 == "Incompatible")
				{
					cout << "Type is incompatible at Line No: " << t->getLineno() << endl;
				}
				if (RE_(T3,T))
				{
					if (T == "") T = T1;
					return true;
				}
			}
		}
		else if (t->getClassPart() == "&&" || t->getClassPart() == "||" ||
			t->getClassPart() == ")" || t->getClassPart() == "]" || t->getClassPart() == ";" || t->getClassPart() == "," || t->getClassPart() == "}")
		{
			T = T1;
			return true;
		}
		return false;
	}

	bool PE(string &T)
	{
		if (t->getClassPart() == "int_const" || t->getClassPart() == "float_const" || t->getClassPart() == "char_const" || t->getClassPart() == "string_const"
			|| t->getClassPart() == "true" || t->getClassPart() == "false" || t->getClassPart() == "("
			|| t->getClassPart() == "!" || t->getClassPart() == "this" || t->getClassPart() == "ID" || t->getClassPart() == "inc_dec")
		{
			string T1 = "";
			if (ME(T1))
			{
				if (PE_(T1, T))
				{
					return true;
				}
			}
		}
		return false;
	}

	bool PE_(string T1, string& T)
	{
		if (t->getClassPart() == "pm")
		{
			string opr = t->getValuePart();
			t->next();
			string T2 = "";
			if (ME(T2))
			{
				string T3 = compatibilityCheck(T1, T2, opr);
				if (T3 == "Incompatible")
				{
					cout << "Type is incompatible at Line No: " << t->getLineno() << endl;
				}
				if (PE_(T3 ,T))
				{
					return true;
				}
			}
		}
		else if (t->getClassPart() == "rop" || t->getClassPart() == "&&" || t->getClassPart() == "||" ||
			t->getClassPart() == ")" || t->getClassPart() == "]" || t->getClassPart() == ";" || t->getClassPart() == "," || t->getClassPart() == "}")
		{
			T = T1;
			return true;
		}
		return false;
	}

	bool ME(string &T)
	{
		if (t->getClassPart() == "int_const" || t->getClassPart() == "float_const" || t->getClassPart() == "char_const" || t->getClassPart() == "string_const"
			|| t->getClassPart() == "true" || t->getClassPart() == "false" || t->getClassPart() == "("
			|| t->getClassPart() == "!" || t->getClassPart() == "this" || t->getClassPart() == "ID" || t->getClassPart() == "inc_dec")
		{
			string T1 = "";
			if (F(T1))
			{
				if (ME_(T1,T))
				{
					return true;
				}
			}
		}
		return false;
	}

	bool ME_(string T1, string& T)
	{
		if (t->getClassPart() == "mdm")
		{
			string opr = t->getValuePart();
			t->next();
			string T2 = "";
			if (F(T2))
			{
				string T3 = compatibilityCheck(T1, T2, opr);
				if (T3 == "Incompatible")
				{
					cout << "Type is incompatible at Line No: " << t->getLineno() << endl;
				}
				if (ME_(T3, T))
				{
					if (T == "") T = T1;
					return true;
				}
			}
		}
		else if (t->getClassPart() == "pm" || t->getClassPart() == "rop" || t->getClassPart() == "&&" || t->getClassPart() == "||" ||
			t->getClassPart() == ")" || t->getClassPart() == "]" || t->getClassPart() == ";" || t->getClassPart() == "," || t->getClassPart() == "}")
		{
			T = T1;
			return true;
		}
		return false;
	}

	bool F(string &T)
	{
		if (t->getClassPart() == "int_const" || t->getClassPart() == "float_const" || t->getClassPart() == "char_const" || t->getClassPart() == "string_const"
			|| t->getClassPart() == "true" || t->getClassPart() == "false")
		{
			string T1 = "";
			if (constant(T1))
			{
				T = T1;
				return true;
			}
		}
		else if (t->getClassPart() == "(")
		{
			t->next();
			string T4 = "";
			if (OE(T4))
			{
				if (t->getClassPart() == ")")
				{
					t->next();
					return true;
				}
			}
		}
		else if (t->getClassPart() == "!")
		{
			t->next();
			string T4 = "";
			if (F(T4))
			{
				T = compatibilityCheck(T4, "!");
				if (T == "NULL")
				{
					cout << "Type is incompatible at Line No: " << t->getLineno() << endl;
				}
				return true;
			}	
		}
		else if (t->getClassPart() == "this" || t->getClassPart() == "ID")
		{
			if (this_st())
			{
				if (t->getClassPart() == "ID")
				{
					name = t->getValuePart();
					functiontable = maintable->findFunctionTable(my_stack.top());
					stack<int> scope = maintable->stack_scope;
					T = functiontable->lookUpFT(name, current_scope, scope);
					if (T == "NULL")
					{
						classtable = maintable->findClassTable(my_stack.top());
						T = classtable->lookUpCT(name);
						if (T == "NULL")
						{
							cout << "Variable named: "<< name <<  " is Undeclared ! at line number: " << t->getLineno() << endl;
						}
					}
					global_type = T;
					t->next();
					if (XY())
					{
						return true;
					}
				}
			}
		}
		else if (t->getClassPart() == "inc_dec")
		{
			t->next();
			if (this_st())
			{
				if (t->getClassPart() == "ID")
				{
					name = t->getValuePart();
					functiontable = maintable->findFunctionTable(my_stack.top());
					stack<int> scope = maintable->stack_scope;
					T = functiontable->lookUpFT(name, current_scope, scope);
					if (T == "NULL")
					{
						classtable = maintable->findClassTable(my_stack.top());
						T = classtable->lookUpCT(name);
						if (T == "NULL")
						{
							cout << "Variable named: " << name << " is Undeclared ! at line number: " << t->getLineno() << endl;
						}
					}
					T = compatibilityCheck(T, "inc_dec");
					if (T == "Incompatible")
					{
						cout << "Type is incompatible at Line No: " << t->getLineno() << endl;
					}
					t->next();
					if (X())
					{
						return true;
					}
				}
			}
		}
		return false;
	}

	bool XY()
	{
		if (t->getClassPart() == "[")
		{
			t->next();
			string T4 = "";
			if (OE(T4))
			{
				if (t->getClassPart() == "]")
				{
					t->next();
					if (XY1())
					{
						return true;
					}
				}
			}
		}
		else if (t->getClassPart() == "(")
		{
			t->next();
			if (PL())
			{
				if (t->getClassPart() == ")")
				{
					t->next();
					if (XY2())
					{
						return true;
					}
				}
			}
		}
		else if (t->getClassPart() == ".")
		{
			t->next();
			if (t->getClassPart() == "ID")
			{
				t->next();
				if (XY())
				{
					return true;
				}
			}
		}
		else if (t->getClassPart() == "inc_dec")
		{
			string T1 = compatibilityCheck(global_type, "inc_dec");
			if (T1 == "Incompatible")
			{
				cout << "Type is incompatible at Line No: " << t->getLineno() << endl;
			}
			t->next();
			return true;
		}
		else if (t->getClassPart() == "mdm" || t->getClassPart() == "pm" || t->getClassPart() == "rop" || t->getClassPart() == "&&" || t->getClassPart() == "||" ||
			t->getClassPart() == ")" || t->getClassPart() == "]" || t->getClassPart() == ";" || t->getClassPart() == "," || t->getClassPart() == "}")
		{
			return true;
		}
		return false;
	}

	bool XY2()
	{
		if (t->getClassPart() == ".")
		{
			t->next();
			if (t->getClassPart() == "ID")
			{
				t->next();
				if (XY())
				{
					return true;
				}
			}
		}
		else if (t->getClassPart() == "[")
		{
			t->next();
			string T4 = "";
			if (OE(T4))
			{
				if (t->getClassPart() == "]")
				{
					t->next();
					if (XY1())
					{
						return true;
					}
				}
			}
		}
		else if (t->getClassPart() == "mdm" || t->getClassPart() == "pm" || t->getClassPart() == "rop" || t->getClassPart() == "&&" || t->getClassPart() == "||" ||
			t->getClassPart() == ")" || t->getClassPart() == "]" || t->getClassPart() == ";" || t->getClassPart() == "," || t->getClassPart() == "}")
		{
			return true;
		}
		return false;
	}

	bool XY1()
	{
		if (t->getClassPart() == ".")
		{
			t->next();
			if (t->getClassPart() == "ID")
			{
				t->next();
				if (XY())
				{
					return true;
				}
			}
		}
		else if (t->getClassPart() == "inc_dec")
		{
			t->next();
			return true;
		}
		else if (t->getClassPart() == "mdm" || t->getClassPart() == "pm" || t->getClassPart() == "rop" || t->getClassPart() == "&&" || t->getClassPart() == "||" ||
			t->getClassPart() == ")" || t->getClassPart() == "]" || t->getClassPart() == ";" || t->getClassPart() == "," || t->getClassPart() == "}")
		{
			return true;
		}
		return false;
	}

	bool constant(string &T)
	{
		if (t->getClassPart() == "int_const" || t->getClassPart() == "float_const" || t->getClassPart() == "char_const" || t->getClassPart() == "string_const"
			|| t->getClassPart() == "true" || t->getClassPart() == "false")
		{
			T = ConstType(t->getClassPart());
			t->next();
			return true;
		}
		return false;
	}

	bool PL()
	{
		string T4 = "";
		if (OE(T4))
		{
			if (PL1())
			{
				return true;
			}
		}
		else if (t->getClassPart() == ")" || t->getClassPart() == "}")
		{
			return true;
		}
		return false;
	}

	bool PL1()
	{
		if (t->getClassPart() == ",")
		{
			t->next();
			string T4 = "";
			if (OE(T4))
			{
				if (PL1())
				{
					return true;
				}
			}
		}
		else if (t->getClassPart() == ")" || t->getClassPart() == "}")
		{
			return true;
		}
		return false;
	}
	//some questions regarding first and follow set of X 
	bool X()
	{
		if (t->getClassPart() == "[")
		{
			t->next();
			string T4 = "";
			if (OE(T4))
			{
				if (t->getClassPart() == "]")
				{
					t->next();
					if (X1())
					{
						return true;
					}
				}
			}
		}
		else if (t->getClassPart() == "(")
		{
			t->next();
			if (PL())
			{
				if (t->getClassPart() == ")")
				{
					t->next();
					if (X2())
					{
						return true;
					}
				}
			}
		}
		else if (t->getClassPart() == ".")
		{
			t->next();
			if (t->getClassPart() == "ID")
			{
				t->next();
				if (X())
				{
					return true;
				}
			}
		}
		//Follow Of X // kuch masley hain isme miss se discuss karna he
		else if (t->getClassPart() == ";" || t->getClassPart() == "pm" || t->getClassPart() == "mdm" || t->getClassPart() == "rop" || t->getClassPart() == "&&" || t->getClassPart() == "||"
			|| t->getClassPart() == ")" || t->getClassPart() == "]" || t->getClassPart() == "," || t->getClassPart() == "}"
			|| t->getClassPart() == "=" || t->getClassPart() == "inc_dec")
		{
			return true;
		}
		return false;
	}

	bool X1()
	{
		if (t->getClassPart() == ".")
		{
			t->next();
			if (t->getClassPart() == "ID")
			{
				t->next();
				if (X())
				{
					return true;
				}
			}
		}
		else if (t->getClassPart() == ";" || t->getClassPart() == "mdm" || t->getClassPart() == "rop" || t->getClassPart() == "&&" || t->getClassPart() == "||"
			|| t->getClassPart() == ")" || t->getClassPart() == "]" || t->getClassPart() == "," || t->getClassPart() == "}"
			|| t->getClassPart() == "=" || t->getClassPart() == "inc_dec")
		{
			return true;
		}
		return false;
	}

	bool X2()
	{
		if (t->getClassPart() == ".")
		{
			t->next();
			if (t->getClassPart() == "ID")
			{
				t->next();
				if (X())
				{
					return true;
				}
			}
		}
		else if (t->getClassPart() == "[")
		{
			t->next();
			string T4 = "";
			if (OE(T4))
			{
				if (t->getClassPart() == "]")
				{
					t->next();
					if (t->getClassPart() == ".")
					{
						t->next();
						if (t->getClassPart() == "ID")
						{
							t->next();
							if (X())
							{
								return true;
							}
						}
					}
				}
			}
		}
		return false;
	}

	bool obj_dec()
	{
		if (t->getClassPart() == "ID")
		{
			t->next();
			if (obj_dec_choice())
			{
				return true;
			}
		}
		return false;
	}

	bool obj_dec_choice()
	{
		if (t->getClassPart() == "[")
		{
			t->next();
			if (t->getClassPart() == "]")
			{
				t->next();
				if (t->getClassPart() == "ID")
				{
					t->next();
					if (obj_init_arr())
					{
						if (obj_list_arr())
						{
							return true;
						}
					}
				}
			}
		}
		else if (t->getClassPart() == "ID")
		{
			t->next();
			if (obj_init())
			{
				if (obj_list())
				{
					return true;
				}
			}
		}
		return false;
	}

	bool obj_init()
	{
		if (t->getClassPart() == "=")
		{
			t->next();
			if (obj_init_choice())
			{
				return true;
			}
		}
		else if (t->getClassPart() == ";" || t->getClassPart() == ",")
		{
			return true;
		}
		return false;
	}

	bool obj_init_choice()
	{
		if (t->getClassPart() == "new")
		{
			t->next();
			if (t->getClassPart() == "ID")
			{
				t->next();
				if (t->getClassPart() == "(")
				{
					t->next();
					if (PL())
					{
						if (t->getClassPart() == ")")
						{
							t->next();
							return true;
						}
					}
				}
			}
		}
		if (t->getClassPart() == "int_const" || t->getClassPart() == "float_const" || t->getClassPart() == "char_const" || t->getClassPart() == "string_const"
			|| t->getClassPart() == "true" || t->getClassPart() == "false" || t->getClassPart() == "("
			|| t->getClassPart() == "!" || t->getClassPart() == "this" || t->getClassPart() == "ID" || t->getClassPart() == "inc_dec")
		{
			string T4 = "";
			if (OE(T4))
			{

				string TR = compatibilityCheck(T4, type, "=");
				if (TR == "Incompatible")
				{
					cout << "Type is incompatible at Line No: " << t->getLineno() << endl;
				}
				return true;
			}
		}
		return false;
	}

	bool obj_list()
	{
		if (t->getClassPart() == ";")
		{
			t->next();
			return true;
		}
		else if (t->getClassPart() == ",")
		{
			t->next();
			if (t->getClassPart() == "ID")
			{
				t->next();
				if (obj_init())
				{
					if (obj_list())
					{
						return true;
					}
				}
			}
		}
		return false;
	}

	bool obj_init_arr()
	{
		if (t->getClassPart() == "=")
		{
			t->next();
			if (obj_init_arr_choice())
			{
				return true;
			}
		}
		else if (t->getClassPart() == ";" || t->getClassPart() == ",")
		{
			return true;
		}
		return false;
	}

	bool obj_list_arr()
	{
		if (t->getClassPart() == ";")
		{
			t->next();
			return true;
		}
		else if (t->getClassPart() == ",")
		{
			t->next();
			if (t->getClassPart() == "ID")
			{
				t->next();
				if (obj_init_arr())
				{
					if (obj_list_arr())
					{
						return true;
					}
				}
			}
		}
		return false;
	}

	bool obj_init_arr_choice()
	{
		if (t->getClassPart() == "new")
		{
			t->next();
			if (t->getClassPart() == "ID")
			{
				t->next();
				if (t->getClassPart() == "[")
				{
					t->next();
					string T4 = "";
					if (OE(T4))
					{
						if (t->getClassPart() == "]")
						{
							t->next();
							if (return_obj_choice())
							{
								return true;
							}
						}
					}
				}
			}
		}
		else if (t->getClassPart() == "{")
		{
			t->next();
			if (PL_dec())
			{
				if (t->getClassPart() == "}")
				{
					t->next();
					return true;
				}
			}
		}
		else if (t->getClassPart() == "ID")
		{
			t->next();
			return true;
		}
		else if (t->getClassPart() == ";" || t->getClassPart() == ",")
		{
			return true;
		}
		return false;
	}

	bool PL_dec()
	{
		if (t->getClassPart() == "new")
		{
			t->next();
			if (t->getClassPart() == "ID")
			{
				t->next();
				if (t->getClassPart() == "(")
				{
					t->next();
					if (PL())
					{
						if (t->getClassPart() == ")")
						{
							t->next();
							if (PL1_dec())
							{
								return true;
							}
						}
					}
				}
			}
		}
		else if (t->getClassPart() == "int_const" || t->getClassPart() == "float_const" || t->getClassPart() == "char_const" || t->getClassPart() == "string_const"
			|| t->getClassPart() == "true" || t->getClassPart() == "false" || t->getClassPart() == "("
			|| t->getClassPart() == "!" || t->getClassPart() == "this" || t->getClassPart() == "ID" || t->getClassPart() == "inc_dec")
		{
			string T4 = "";
			if (OE(T4))
			{
				if (PL1_dec())
				{
					return true;
				}
			}
		}
		return false;
	}

	bool PL1_dec()
	{
		if (t->getClassPart() == ",")
		{
			t->next();
			if (PL1_choice())
			{
				if (PL1_dec())
				{
					return true;
				}
			}
		}
		else if (t->getClassPart() == "}")
		{
			return true;
		}
		return false;
	}

	bool PL1_choice()
	{
		if (t->getClassPart() == "new")
		{
			t->next();
			if (t->getClassPart() == "ID")
			{
				t->next();
				if (t->getClassPart() == "(")
				{
					t->next();
					if (PL())
					{
						if (t->getClassPart() == ")")
						{
							t->next();
							return true;
						}
					}
				}
			}
		}
		else if (t->getClassPart() == "int_const" || t->getClassPart() == "float_const" || t->getClassPart() == "char_const" || t->getClassPart() == "string_const"
			|| t->getClassPart() == "true" || t->getClassPart() == "false" || t->getClassPart() == "("
			|| t->getClassPart() == "!" || t->getClassPart() == "this" || t->getClassPart() == "ID" || t->getClassPart() == "inc_dec")
		{
			string T4 = "";
			if (OE(T4))
			{
				return true;
			}
		}
		return false;
	}

	bool SST()
	{
		name = "";
		type = "";
		if (t->getClassPart() == "if")
		{
			if (if_else())
			{
				return true;
			}
		}
		if (t->getClassPart() == "while")
		{
			if (while_st())
			{
				return true;
			}
		}
		else if (t->getClassPart() == "for")
		{
			if (for_st())
			{
				return true;
			}
		}
		else if (t->getClassPart() == "inc_dec")
		{
			t->next();
			if (this_st())
			{
				if (t->getClassPart() == "ID")
				{
					name = t->getValuePart();
					functiontable = maintable->findFunctionTable(my_stack.top());
					stack<int> scope = maintable->stack_scope;
					global_type = functiontable->lookUpFT(name, current_scope, scope);
					if (global_type == "NULL")
					{
						classtable = maintable->findClassTable(my_stack.top());
						global_type = classtable->lookUpCT(name);
						if (global_type == "NULL")
						{
							cout << "Variable named: " << name << " is Undeclared ! at line number: " << t->getLineno() << endl;
						}
					}
					else
					{
						string T1 = compatibilityCheck(global_type, "inc_dec");
						if (T1 == "Incompatible")
						{
							cout << "Type is incompatible at Line No: " << t->getLineno() << endl;
						}
					}
					t->next();
					if (X())
					{
						if (t->getClassPart() == ";")
						{
							t->next();
							return true;
						}
					}
				}
			}
		}
		else if (t->getClassPart() == "this")
		{
			t->next();
			if (t->getClassPart() == ".")
			{
				t->next();
				if (t->getClassPart() == "ID")
				{
					name = t->getValuePart();
					functiontable = maintable->findFunctionTable(my_stack.top());
					stack<int> scope = maintable->stack_scope;
					global_type = functiontable->lookUpFT(name, current_scope, scope);
					if (global_type == "NULL")
					{
						classtable = maintable->findClassTable(my_stack.top());
						global_type = classtable->lookUpCT(name);
						if (global_type == "NULL")
						{
							cout << "Variable named: " << name << " is Undeclared ! at line number: " << t->getLineno() << endl;
						}
					}
					t->next();
					if (XY_SST())
					{
						return true;
					}
				}
			}
		}
		else if (t->getClassPart() == "ID")
		{
			type = t->getValuePart();
			name = t->getValuePart();
			t->next();
			if (ZZZ())
			{
				return true;
			}
		}
		else if (try_st())
		{
			return true;
		}
		else if (t->getClassPart() == "DT")
		{
			type = t->getValuePart();
			t->next();
			if (dec_choice())
			{
				return true;
			}
		}
		else if (t->getClassPart() == "continue")
		{
			t->next();
			if (t->getClassPart() == ";")
			{
				t->next();
				return true;
			}
		}
		else if (t->getClassPart() == "break")
		{
			t->next();
			if (t->getClassPart() == ";")
			{
				t->next();
				return true;
			}
		}
		else if (t->getClassPart() == ";")
		{
			t->next();
			return true;
		}
		return false;
	}

	bool ZZZ()
	{
		if (t->getClassPart() == "ID")
		{
			name = t->getValuePart();
			functiontable = maintable->findFunctionTable(my_stack.top());
			stack<int> scope = maintable->stack_scope;
			global_type = functiontable->lookUpFT(name, current_scope, scope);
			if (global_type == "NULL")
			{
				classtable = maintable->findClassTable(my_stack.top());
				global_type = classtable->lookUpCT(name);
				if (global_type == "NULL")
				{
					cout << "Variable named: " << name << " is Undeclared ! at line number: " << t->getLineno() << endl;
				}
			}
			t->next();
			if (obj_init())
			{
				if (obj_list())
				{
					return true;
				}
			}
		}
		else if (t->getClassPart() == "[")
		{
			t->next();
			if (XY_dec())
			{
				return true;
			}
		}
		else if (t->getClassPart() == "." || t->getClassPart() == "inc_dec" || t->getClassPart() == "=")
		{
			functiontable = maintable->findFunctionTable(my_stack.top());
			stack<int> scope = maintable->stack_scope;
			global_type = functiontable->lookUpFT(type, current_scope, scope);
			if (global_type == "NULL")
			{
				classtable = maintable->findClassTable(my_stack.top());
				global_type = classtable->lookUpCT(type);
				if (global_type == "NULL")
				{
					cout << "Variable named: " << type << " is Undeclared ! at line number: " << t->getLineno() << endl;
				}
			}
			if (t->getClassPart() == "inc_dec")
			{
				string t1 = compatibilityCheck(global_type, "inc_dec");
				if(t1 == "Incompatible")
				{
					cout << "Type is incompatible at Line No: " << t->getLineno() << endl;
				}
			}
			if (XY1_SST())
			{
				return true;
			}
		}
		else if (t->getClassPart() == "(")
		{
			t->next();
			if (PL())
			{
				if (t->getClassPart() == ")")
				{
					t->next();
					if (XY2_SST())
					{
						return true;
					}
				}
			}
		}
		return false;
	}

	bool XY_dec()
	{
		if (t->getClassPart() == "int_const" || t->getClassPart() == "float_const" || t->getClassPart() == "char_const" || t->getClassPart() == "string_const"
			|| t->getClassPart() == "true" || t->getClassPart() == "false" || t->getClassPart() == "("
			|| t->getClassPart() == "!" || t->getClassPart() == "this" || t->getClassPart() == "ID" || t->getClassPart() == "inc_dec")
		{
			string T4 = "";
			if (OE(T4))
			{
				if (t->getClassPart() == "]")
				{
					t->next();
					if (XY1_SST())
					{
						return true;
					}
				}
			}
		}
		else if (t->getClassPart() == "]")
		{
			t->next();
			if (t->getClassPart() == "ID")
			{
				name = t->getValuePart();
				type += "[]";
				functiontable = maintable->findFunctionTable(my_stack.top());
				if (functiontable->insertFT(name, type, current_scope))
				{
				}
				else
				{
					cout << "Variable Redeclration Error at Line no: " << t->getLineno() << endl;
				}
				t->next();
				if (obj_init_arr())
				{
					if (obj_list_arr())
					{
						return true;
					}
				}
			}
		}
		return false;
	}

	bool XY_SST()
	{
		if (t->getClassPart() == "(")
		{
			t->next();
			if (PL())
			{
				if (t->getClassPart() == ")")
				{
					t->next();
					if (XY2_SST())
					{
						return true;
					}
				}
			}
		}
		else if (t->getClassPart() == ".")
		{
			t->next();
			if (t->getClassPart() == "ID")
			{
				t->next();
				if (XY_SST())
				{
					return true;
				}
			}
		}
		else if (t->getClassPart() == "inc_dec")
		{
			string t1 = compatibilityCheck(name, "inc_dec");
			if (t1 == "Incompatible")
			{
				cout << "Type is incompatible at Line No: " << t->getLineno() << endl;
			}
			t->next();
			if (t->getClassPart() == ";")
			{
				t->next();
				return true;
			}
		}
		else if (t->getClassPart() == "=")
		{
			t->next();
			string T4 = "";
			if (OE(T4))
			{
				string TR = compatibilityCheck(T4, global_type, "=");
				if (TR == "Incompatible")
				{
					cout << "Type is incompatible at Line No: " << t->getLineno() << endl;
				}
				if (t->getClassPart() == ";")
				{
					t->next();
					return true;
				}
			}
		}
		else if (t->getClassPart() == "[")
		{
			t->next();
			string T4 = "";
			if (OE(T4))
			{
				if (t->getClassPart() == "]")
				{
					t->next();
					if (XY1_SST())
					{
						return true;
					}
				}
			}
		}
		else if (t->getClassPart() == ";")
		{
			t->next();
			return true;
		}
		return false;
	}

	bool XY1_SST()
	{
		if (t->getClassPart() == ".")
		{
			t->next();
			if (t->getClassPart() == "ID")
			{
				t->next();
				if (XY_SST())
				{
					return true;
				}
			}
		}
		else if (t->getClassPart() == "inc_dec")
		{
			t->next();
			if (t->getClassPart() == ";")
			{
				t->next();
				return true;
			}
		}
		else if (t->getClassPart() == "=")
		{
			t->next();
			string T4 = "";
			if (OE(T4))
			{
				string TR = compatibilityCheck(T4, global_type, "=");
				if (TR == "Incompatible")
				{
					cout << "Type is incompatible at Line No: " << t->getLineno() << endl;
				}
				if (t->getClassPart() == ";")
				{
					t->next();
					return true;
				}
			}
		}
		return false;
	}

	bool XY2_SST()
	{
		if (t->getClassPart() == ".")
		{
			t->next();
			if (t->getClassPart() == "ID")
			{
				t->next();
				if (XY_SST())
				{
					return true;
				}
			}
		}
		else if (t->getClassPart() == "[")
		{
			t->next();
			string T4 = "";
			if (OE(T4))
			{
				if (t->getClassPart() == "]")
				{
					t->next();
					if (XY1_SST())
					{
						return true;
					}
				}
			}
		}
		else if (t->getClassPart() == ";")
		{
			t->next();
			return true;
		}
		return false;
	}

	bool MST()
	{
		if (t->getClassPart() == "if" || t->getClassPart() == "while" || t->getClassPart() == "for" || t->getClassPart() == "try" || t->getClassPart() == "this" ||
			t->getClassPart() == "inc_dec" || t->getClassPart() == "ID" || t->getClassPart() == "DT" || t->getClassPart() == "continue" || t->getClassPart() == "break")
		{
			if (SST())
			{
				if (MST())
				{
					return true;
				}
			}
		}
		else if (t->getClassPart() == "}")
		{
			return true;
		}
		return false;
	}

	bool for_st()
	{
		if (t->getClassPart() == "for")
		{
			t->next();
			if (t->getClassPart() == "(")
			{
				current_scope = maintable->createScope();
				t->next();
				if (c1())
				{
					if (c2())
					{
						if (t->getClassPart() == ";")
						{
							t->next();
							if (c3())
							{
								if (t->getClassPart() == ")")
								{
									t->next();
									if (t->getClassPart() == "{")
									{
										t->next();
										if (MST())
										{
											if (t->getClassPart() == "}")
											{
												current_scope = maintable->deleteScope();
												t->next();
												return true;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		return false;
	}

	bool c1()
	{
		if (t->getClassPart() == "inc_dec")
		{
			t->next();
			if (this_st())
			{
				if (t->getClassPart() == "ID")
				{
					name = t->getValuePart();
					functiontable = maintable->findFunctionTable(my_stack.top());
					stack<int> scope = maintable->stack_scope;
					global_type = functiontable->lookUpFT(name, current_scope, scope);
					if (global_type == "NULL")
					{
						classtable = maintable->findClassTable(my_stack.top());
						global_type = classtable->lookUpCT(name);
						if (global_type == "NULL")
						{
							cout << "Variable named: " << name << " is Undeclared ! at line number: " << t->getLineno() << endl;
						}
					}
					else
					{
						string T1 = compatibilityCheck(global_type, "inc_dec");
						if (T1 == "Incompatible")
						{
							cout << "Type is incompatible at Line No: " << t->getLineno() << endl;
						}
					}
					t->next();
					if (X())
					{
						if (t->getClassPart() == ";")
						{
							t->next();
							return true;
						}
					}
				}
			}
		}
		else if (t->getClassPart() == "DT")
		{
			type = t->getValuePart();
			t->next();
			if (dec_choice())
			{
				return true;
			}
		}
		else if (t->getClassPart() == "this")
		{
			t->next();
			if (t->getClassPart() == ".")
			{
				t->next();
				if (t->getClassPart() == "ID")
				{
					name = t->getValuePart();
					functiontable = maintable->findFunctionTable(my_stack.top());
					stack<int> scope = maintable->stack_scope;
					global_type = functiontable->lookUpFT(name, current_scope, scope);
					if (global_type == "NULL")
					{
						classtable = maintable->findClassTable(my_stack.top());
						global_type = classtable->lookUpCT(name);
						if (global_type == "NULL")
						{
							cout << "Variable named: " << name << " is Undeclared ! at line number: " << t->getLineno() << endl;
						}
					}
					t->next();
					if (X())
					{
						if (c1_choice2())
						{
							return true;
						}
					}
				}
			}
		}
		else if (t->getClassPart() == "ID")
		{
			type = t->getValuePart();
			t->next();
			if (for_ZZZ())
			{
				return true;
			}
		}
		else if (t->getClassPart() == ";")
		{
			t->next();
			return true;
		}
		return false;
	}


	bool for_ZZZ()
	{
		if (t->getClassPart() == "ID")
		{
			name = t->getValuePart();
			functiontable = maintable->findFunctionTable(my_stack.top());
			if (functiontable->insertFT(name, type, current_scope))
			{
			}
			else
			{
				cout << "Variable Redeclration Error at Line no: " << t->getLineno() << endl;
			}
			t->next();
			if (obj_init())
			{
				if (obj_list())
				{
					return true;
				}
			}
		}
		else if (t->getClassPart() == "[")
		{
			t->next();
			if (for_XY_dec())
			{
				return true;
			}
		}
		else if (for_XY1_SST())
		{
			return true;
		}
		else if (t->getClassPart() == "(")
		{
			t->next();
			if (PL())
			{
				if (t->getClassPart() == ")")
				{
					t->next();
					if (for_XY2_SST())
					{
						return true;
					}
				}
			}
		}
		return false;
	}

	bool for_XY_dec()
	{
		if (t->getClassPart() == "int_const" || t->getClassPart() == "float_const" || t->getClassPart() == "char_const" || t->getClassPart() == "string_const"
			|| t->getClassPart() == "true" || t->getClassPart() == "false" || t->getClassPart() == "("
			|| t->getClassPart() == "!" || t->getClassPart() == "this" || t->getClassPart() == "ID" || t->getClassPart() == "inc_dec")
		{
			string T4 = "";
			if (OE(T4))
			{
				if (t->getClassPart() == "]")
				{
					t->next();
					if (for_XY1_SST())
					{
						return true;
					}
				}
			}
		}
		else if (t->getClassPart() == "]")
		{
			t->next();
			if (t->getClassPart() == "ID")
			{
				name = t->getValuePart();
				type += "[]";
				functiontable = maintable->findFunctionTable(my_stack.top());
				if (functiontable->insertFT(name, type, current_scope))
				{
				}
				else
				{
					cout << "Variable Redeclration Error at Line no: " << t->getLineno() << endl;
				}
				t->next();
				if (obj_init_arr())
				{
					if (obj_list_arr())
					{
						return true;
					}
				}
			}
		}
		return false;
	}

	bool for_XY_SST()
	{
		if (t->getClassPart() == "(")
		{
			t->next();
			if (PL())
			{
				if (t->getClassPart() == ")")
				{
					t->next();
					if (for_XY2_SST())
					{
						return true;
					}
				}
			}
		}
		else if (t->getClassPart() == ".")
		{
			t->next();
			if (t->getClassPart() == "ID")
			{
				t->next();
				if (for_XY_SST())
				{
					return true;
				}
			}
		}
		else if (t->getClassPart() == "inc_dec")
		{
			t->next();
			if (t->getClassPart() == ";")
			{
				t->next();
				return true;
			}
		}
		else if (t->getClassPart() == "=")
		{
			t->next();
			string T4 = "";
			if (OE(T4))
			{
				string TR = compatibilityCheck(T4, global_type, "=");
				if (TR == "Incompatible")
				{
					cout << "Type is incompatible at Line No: " << t->getLineno() << endl;
				}
				if (t->getClassPart() == ";")
				{
					t->next();
					return true;
				}
			}
		}
		else if (t->getClassPart() == "[")
		{
			t->next();
			string T4 = "";
			if (OE(T4))
			{
				if (t->getClassPart() == "]")
				{
					t->next();
					if (for_XY1_SST())
					{
						return true;
					}
				}
			}
		}
		else if (t->getClassPart() == ";")
		{
			t->next();
			return true;
		}
		return false;
	}

	bool for_XY1_SST()
	{
		if (t->getClassPart() == ".")
		{
			t->next();
			if (t->getClassPart() == "ID")
			{
				t->next();
				if (for_XY_SST())
				{
					return true;
				}
			}
		}
		else if (t->getClassPart() == "inc_dec")
		{
			t->next();
			if (t->getClassPart() == ";")
			{
				t->next();
				return true;
			}
		}
		else if (t->getClassPart() == "=")
		{
			t->next();
			string T4 = "";
			if (OE(T4))
			{
				string TR = compatibilityCheck(T4, global_type, "=");
				if (TR == "Incompatible")
				{
					cout << "Type is incompatible at Line No: " << t->getLineno() << endl;
				}
				if (t->getClassPart() == ";")
				{
					t->next();
					return true;
				}
			}
		}
		return false;
	}

	bool for_XY2_SST()
	{
		if (t->getClassPart() == ".")
		{
			t->next();
			if (t->getClassPart() == "ID")
			{
				t->next();
				if (for_XY_SST())
				{
					return true;
				}
			}
		}
		else if (t->getClassPart() == "[")
		{
			t->next();
			string T4 = "";
			if (OE(T4))
			{
				if (t->getClassPart() == "]")
				{
					t->next();
					if (for_XY1_SST())
					{
						return true;
					}
				}
			}
		}
		return false;
	}

	bool c1_choice2()
	{
		if (t->getClassPart() == "=")
		{
			t->next();
			string T4 = "";
			if (OE(T4))
			{
				string TR = compatibilityCheck(T4, global_type, "=");
				if (TR == "Incompatible")
				{
					cout << "Type is incompatible at Line No: " << t->getLineno() << endl;
				}
				if (t->getClassPart() == ";")
				{
					t->next();
					return true;
				}
			}
		}
		else if (t->getClassPart() == "inc_dec")
		{
			string T1 = compatibilityCheck(name, "inc_dec");
			if (T1 == "Incompatible")
			{
				cout << "Type is incompatible at Line No: " << t->getLineno() << endl;
			}
			t->next();
			if (t->getClassPart() == ";")
			{
				t->next();
				return true;
			}
		}
		return false;
	}

	bool c2()
	{

		if (t->getClassPart() == "int_const" || t->getClassPart() == "float_const" || t->getClassPart() == "char_const" || t->getClassPart() == "string_const"
			|| t->getClassPart() == "true" || t->getClassPart() == "false" || t->getClassPart() == "("
			|| t->getClassPart() == "!" || t->getClassPart() == "this" || t->getClassPart() == "ID" || t->getClassPart() == "inc_dec")
		{
			string T4 = "";
			if (OE(T4))
			{
				return true;
			}
		}
		else if (t->getClassPart() == ";")
		{
			return true;
		}
		return false;
	}

	bool c3()
	{
		if (t->getClassPart() == "this" || t->getClassPart() == "ID")
		{
			if (this_st())
			{
				if (t->getClassPart() == "ID")
				{
					name = t->getValuePart();
					functiontable = maintable->findFunctionTable(my_stack.top());
					stack<int> scope = maintable->stack_scope;
					global_type = functiontable->lookUpFT(name, current_scope, scope);
					if (global_type == "NULL")
					{
						classtable = maintable->findClassTable(my_stack.top());
						global_type = classtable->lookUpCT(name);
						if (global_type == "NULL")
						{
							cout << "Variable named: " << name << " is Undeclared ! at line number: " << t->getLineno() << endl;
						}
					}
					t->next();
					if (X())
					{
						if (c3_choice())
						{
							if (c3_more_choice())
							{
								return true;
							}
						}
					}
				}
			}
		}
		else if (t->getClassPart() == "inc_dec")
		{
			t->next();
			if (this_st())
			{
				if (t->getClassPart() == "ID")
				{
					name = t->getValuePart();
					functiontable = maintable->findFunctionTable(my_stack.top());
					stack<int> scope = maintable->stack_scope;
					global_type = functiontable->lookUpFT(name, current_scope, scope);
					if (global_type == "NULL")
					{
						classtable = maintable->findClassTable(my_stack.top());
						global_type = classtable->lookUpCT(name);
						if (global_type == "NULL")
						{
							cout << "Variable named: " << name << " is Undeclared ! at line number: " << t->getLineno() << endl;
						}
					}
					else
					{
						string T1 = compatibilityCheck(global_type, "inc_dec");
						if (T1 == "Incompatible")
						{
							cout << "Type is incompatible at Line No: " << t->getLineno() << endl;
						}
					}
					t->next();
					if (X())
					{
						if (c3_more_choice())
						{
							return true;
						}
					}
				}
			}
		}
		else if (t->getClassPart() == "new")
		{
			t->next();
			if (t->getClassPart() == "ID")
			{
				t->next();
				if (t->getClassPart() == "(")
				{
					t->next();
					if (PL())
					{
						if (t->getClassPart() == ")")
						{
							t->next();
							if (c3_more_choice())
							{
								return true;
							}
						}
					}
				}
			}
		}
		else if (t->getClassPart() == ")")
		{
			return true;
		}
		return false;
	}

	bool c3_choice()
	{
		if (t->getClassPart() == "inc_dec")
		{
			string T1 = compatibilityCheck(name, "inc_dec");
			if (T1 == "Incompatible")
			{
				cout << "Type is incompatible at Line No: " << t->getLineno() << endl;
			}
			t->next();
			return true;
		}
		else if (t->getClassPart() == "=")
		{
			t->next();
			string T4 = "";
			if (OE(T4))
			{
				string TR = compatibilityCheck(T4, global_type, "=");
				if (TR == "Incompatible")
				{
					cout << "Type is incompatible at Line No: " << t->getLineno() << endl;
				}
				return true;
			}
		}
		return false;
	}

	bool c3_more_choice()
	{
		if (t->getClassPart() == ",")
		{
			t->next();
			if (c3_must())
			{
				if (c3_more_choice())
				{
					return true;
				}
			}
		}
		else if (t->getClassPart() == ")")
		{
			return true;
		}
		return false;
	}

	bool c3_must()
	{
		if (t->getClassPart() == "this" || t->getClassPart() == "ID")
		{
			if (this_st())
			{
				if (t->getClassPart() == "ID")
				{
					name = t->getValuePart();
					functiontable = maintable->findFunctionTable(my_stack.top());
					stack<int> scope = maintable->stack_scope;
					global_type = functiontable->lookUpFT(name, current_scope, scope);
					if (global_type == "NULL")
					{
						classtable = maintable->findClassTable(my_stack.top());
						global_type = classtable->lookUpCT(name);
						if (global_type == "NULL")
						{
							cout << "Variable named: " << name << " is Undeclared ! at line number: " << t->getLineno() << endl;
						}
					}
					t->next();
					if (X())
					{
						if (c3_choice())
						{
							if (c3_more_choice())
							{
								return true;
							}
						}
					}
				}
			}
		}
		else if (t->getClassPart() == "inc_dec")
		{
			t->next();
			if (this_st())
			{
				if (t->getClassPart() == "ID")
				{
					name = t->getValuePart();
					functiontable = maintable->findFunctionTable(my_stack.top());
					stack<int> scope = maintable->stack_scope;
					global_type = functiontable->lookUpFT(name, current_scope, scope);
					if (global_type == "NULL")
					{
						classtable = maintable->findClassTable(my_stack.top());
						global_type = classtable->lookUpCT(name);
						if (global_type == "NULL")
						{
							cout << "Variable named: " << name << " is Undeclared ! at line number: " << t->getLineno() << endl;
						}
					}
					else
					{
						string T1 = compatibilityCheck(global_type, "inc_dec");
						if (T1 == "Incompatible")
						{
							cout << "Type is incompatible at Line No: " << t->getLineno() << endl;
						}
					}
					t->next();
					if (X())
					{
						if (c3_more_choice())
						{
							return true;
						}
					}
				}
			}
		}
		else if (t->getClassPart() == "new")
		{
			t->next();
			if (t->getClassPart() == "ID")
			{
				t->next();
				if (t->getClassPart() == "(")
				{
					t->next();
					if (PL())
					{
						if (t->getClassPart() == ")")
						{
							t->next();
							if (c3_more_choice())
							{
								return true;
							}
						}
					}
				}
			}
		}
		return false;
	}

	bool if_else()
	{
		if (t->getClassPart() == "if")
		{
			t->next();
			if (t->getClassPart() == "(")
			{
				current_scope = maintable->createScope();
				t->next();
				string T4 = "";
				if (OE(T4))
				{
					if (t->getClassPart() == ")")
					{
						t->next();
						if (t->getClassPart() == "{")
						{
							t->next();
							if (MST())
							{
								if (t->getClassPart() == "}")
								{
									current_scope = maintable->deleteScope();
									t->next();
									if (o_else())
									{
										return true;
									}
								}
							}
						}
					}
				}
			}
		}
		return false;
	}

	bool o_else()
	{
		if (t->getClassPart() == "else")
		{
			t->next();
			if (if_choice())
			{
				return true;
			}
		}
		else if (t->getClassPart() == "if" || t->getClassPart() == "while" || t->getClassPart() == "for" || t->getClassPart() == "try"
			|| t->getClassPart() == "this" || t->getClassPart() == "inc_dec" || t->getClassPart() == "ID" || t->getClassPart() == "DT"
			|| t->getClassPart() == "continue" || t->getClassPart() == "break" || t->getClassPart() == "return" || t->getClassPart() == "}")
		{
			return true;
		}
		return false;
	}

	bool if_choice()
	{
		if (t->getClassPart() == "if")
		{
			if (if_else())
			{
				return true;
			}
		}
		else if (t->getClassPart() == "{")
		{
			t->next();
			if (MST())
			{
				if (t->getClassPart() == "}")
				{
					t->next();
					return true;
				}
			}
		}
		return false;
	}

	bool while_st()
	{
		if (t->getClassPart() == "while")
		{
			t->next();
			if (t->getClassPart() == "(")
			{
				current_scope = maintable->createScope();
				t->next();
				string T4 = "";
				if (OE(T4))
				{
					if (t->getClassPart() == ")")
					{
						t->next();
						if (t->getClassPart() == "{")
						{
							t->next();
							if (MST())
							{
								if (t->getClassPart() == "}")
								{
									current_scope = maintable->deleteScope();
									t->next();
									return true;
								}
							}
						}
					}
				}
			}
		}
		return false;
	}

	bool try_st()
	{
		if (t->getClassPart() == "try")
		{
			t->next();
			if (t->getClassPart() == "{")
			{
				current_scope = maintable->createScope();
				t->next();
				if (MST())
				{
					if (t->getClassPart() == "}")
					{
						current_scope = maintable->deleteScope();
						t->next();
						if (catch_st())
						{
							if (finally_st())
							{
								return true;
							}
						}
					}
				}
			}
		}
		return false;
	}

	bool catch_st()
	{
		if (t->getClassPart() == "catch")
		{
			t->next();
			if (t->getClassPart() == "(")
			{
				current_scope = maintable->createScope();
				t->next();
				if (t->getClassPart() == "ID")
				{
					t->next();
					if (t->getClassPart() == "ID")
					{
						t->next();
						if (t->getClassPart() == ")")
						{
							t->next();
							if (t->getClassPart() == "{")
							{
								t->next();
								if (MST())
								{
									if (t->getClassPart() == "}")
									{
										current_scope = maintable->deleteScope();
										t->next();
										if (catch_st1())
										{
											return true;
										}
									}
								}
							}
						}
					}
				}
			}
		}
		return false;
	}

	bool catch_st1()
	{
		if (catch_st())
		{
			if (catch_st1())
			{
				return true;
			}
		}
		else if (t->getClassPart() == "if" || t->getClassPart() == "while" || t->getClassPart() == "for" || t->getClassPart() == "try"
			|| t->getClassPart() == "this" || t->getClassPart() == "inc_dec" || t->getClassPart() == "ID" || t->getClassPart() == "DT"
			|| t->getClassPart() == "continue" || t->getClassPart() == "break" || t->getClassPart() == "return" || t->getClassPart() == "}"
			|| t->getClassPart() == "finally")
		{
			return true;
		}
		return false;
	}

	bool finally_st()
	{
		if (t->getClassPart() == "finally")
		{
			t->next();
			if (t->getClassPart() == "{")
			{
				current_scope = maintable->createScope();
				t->next();
				if (MST())
				{
					if (t->getClassPart() == "}")
					{
						current_scope = maintable->deleteScope();
						t->next();
						return true;
					}
				}
			}
		}
		else if (t->getClassPart() == "if" || t->getClassPart() == "while" || t->getClassPart() == "for" || t->getClassPart() == "try"
			|| t->getClassPart() == "this" || t->getClassPart() == "inc_dec" || t->getClassPart() == "ID" || t->getClassPart() == "DT"
			|| t->getClassPart() == "continue" || t->getClassPart() == "break" || t->getClassPart() == "return" || t->getClassPart() == "}")
		{
			return true;
		}
		return false;
	}

	bool func_dec()
	{
		if (ret_type_choice())
		{
			if (t->getClassPart() == "ID")
			{
				t->next();
				if (t->getClassPart() == "(")
				{
					t->next();
					if (def())
					{
						if (t->getClassPart() == ")")
						{
							t->next();
							if (t->getClassPart() == "{")
							{
								t->next();
								if (MST1())
								{
									if (t->getClassPart() == "}")
									{
										t->next();
										return true;
									}
								}
							}
						}
					}
				}
			}
		}
		return false;
	}

	bool ret_type_choice()
	{
		if (t->getClassPart() == "DT" || t->getClassPart() == "ID")
		{
			if (ret_type())
			{
				return true;
			}
		}
		else if (t->getClassPart() == "void")
		{
			t->next();
			return true;
		}
		else if (t->getClassPart() == "ID")
		{
			return true;
		}
		return false;
	}

	bool ret_type()
	{
		if (t->getClassPart() == "DT")
		{
			type_def += t->getValuePart() + " ";
			type = t->getValuePart();
			t->next();
			if (ret_choice())
			{
				return true;
			}
		}
		else if (t->getClassPart() == "ID")
		{
			type_def += t->getValuePart() + " ";
			type = t->getValuePart();
			t->next();
			if (ret_choice())
			{
				return true;
			}
		}
		return false;
	}

	bool ret_choice()
	{
		if (t->getClassPart() == "[")
		{
			t->next();
			if (t->getClassPart() == "]")
			{
				type += "[]";
				t->next();
				return true;
			}
		}
		else if (t->getClassPart() == ")" || t->getClassPart() == "," || t->getClassPart() == "ID")
		{
			return true;
		}
		return false;
	}

	bool def()
	{
		name = "";
		type_def = "";
		if (t->getClassPart() == "DT" || t->getClassPart() == "ID")
		{
			if (ret_type())
			{
				if (t->getClassPart() == "ID")
				{
					name = t->getValuePart();
					functiontable = maintable->findFunctionTable(my_stack.top());
					if (functiontable->insertFT(name, type, current_scope))
					{
					}
					else
					{
						cout << "Variable Redeclaration Error at Line no: " << t->getLineno() << endl;
					}
					t->next();
					if (more_def())
					{
						return true;
					}
				}
			}
		}
		else if (t->getClassPart() == ")")
		{
			return true;
		}
		return false;
	}

	bool more_def()
	{
		type = "";
		name = "";
		if (t->getClassPart() == ",")
		{
			t->next();
			if (ret_type())
			{
				if (t->getClassPart() == "ID")
				{
					name = t->getValuePart();
					functiontable = maintable->findFunctionTable(my_stack.top());
					if (functiontable->insertFT(name, type, current_scope))
					{
					}
					else
					{
						cout << "Variable Redeclaration Error at Line no: " << t->getLineno() << endl;
					}
					t->next();
					if (more_def())
					{
						return true;
					}
				}
			}
		}
		else if (t->getClassPart() == ")")
		{
			return true;
		}
		return false;
	}

	bool SST1()
	{
		name = "";
		type = "";
		if (t->getClassPart() == "if")
		{
			if (if_else())
			{
				return true;
			}
		}
		if (t->getClassPart() == "while")
		{
			if (while_st())
			{
				return true;
			}
		}
		else if (t->getClassPart() == "for")
		{
			if (for_st())
			{
				return true;
			}
		}
		else if (t->getClassPart() == "inc_dec")
		{
			t->next();
			if (this_st())
			{
				if (t->getClassPart() == "ID")
				{
					name = t->getValuePart();
					functiontable = maintable->findFunctionTable(my_stack.top());
					stack<int> scope = maintable->stack_scope;
					global_type = functiontable->lookUpFT(name, current_scope, scope);
					if (global_type == "NULL")
					{
						classtable = maintable->findClassTable(my_stack.top());
						global_type = classtable->lookUpCT(name);
						if (global_type == "NULL")
						{
							cout << "Variable named: " << name << " is Undeclared ! at line number: " << t->getLineno() << endl;
						}
					}
					else
					{
						string T1 = compatibilityCheck(global_type, "inc_dec");
						if (T1 == "Incompatible")
						{
							cout << "Type is incompatible at Line No: " << t->getLineno() << endl;
						}
					}
					t->next();
					if (X())
					{
						if (t->getClassPart() == ";")
						{
							t->next();
							return true;
						}
					}
				}
			}
		}
		else if (t->getClassPart() == "this")
		{
			t->next();
			if (t->getClassPart() == ".")
			{
				t->next();
				if (t->getClassPart() == "ID")
				{
					name = t->getValuePart();
					functiontable = maintable->findFunctionTable(my_stack.top());
					stack<int> scope = maintable->stack_scope;
					global_type = functiontable->lookUpFT(name, current_scope, scope);
					if (global_type == "NULL")
					{
						classtable = maintable->findClassTable(my_stack.top());
						global_type = classtable->lookUpCT(name);
						if (global_type == "NULL")
						{
							cout << "Variable named: " << name << " is Undeclared ! at line number: " << t->getLineno() << endl;
						}
					}
					t->next();
					if (XY_SST())
					{
						return true;
					}
				}
			}
		}
		else if (t->getClassPart() == "ID")
		{
			type = t->getValuePart();
			name = t->getValuePart();
			t->next();
			if (ZZZ())
			{
				return true;
			}
		}
		else if (try_st())
		{
			return true;
		}
		else if (t->getClassPart() == "DT")
		{
			type = t->getValuePart();
			t->next();
			if (dec_choice())
			{
				return true;
			}
		}
		else if (return_st())
		{
			return true;
		}
		else if (t->getClassPart() == ";")
		{
			t->next();
			return true;
		}
		return false;
	}

	bool MST1()
	{
		if (t->getClassPart() == "if" || t->getClassPart() == "while" || t->getClassPart() == "for" || t->getClassPart() == "try" || t->getClassPart() == "this" ||
			t->getClassPart() == "inc_dec" || t->getClassPart() == "ID" || t->getClassPart() == "DT" || t->getClassPart() == "return")
		{
			if (SST1())
			{
				if (MST1())
				{
					return true;
				}
			}
		}
		else if (t->getClassPart() == "}")
		{
			return true;
		}
		return false;
	}

	bool func()
	{
		if (t->getClassPart() == "ID")
		{
			string func_name = t->getValuePart();
			t->next();
			if (t->getClassPart() == "(")
			{
				current_scope = maintable->createScope();
				t->next();
				if (def())
				{
					classtable = maintable->findClassTable(my_stack.top());
					if (classtable->insertCT(func_name, type_def + "->" + ret_def, class_access_modifier, class_category))
					{
					}
					else
					{
						cout << "Redeclaration Error at Line No: " << t->getLineno() << endl;
					}
					if (t->getClassPart() == ")")
					{
						t->next();
						if (t->getClassPart() == "{")
						{
							t->next();
							if (MST1())
							{
								if (t->getClassPart() == "}")
								{
									current_scope = maintable->deleteScope();
									t->next();
									return true;
								}
							}
						}
					}
				}
			}
		}
		return false;
	}

	bool return_st()
	{
		if (t->getClassPart() == "return")
		{
			t->next();
			if (either_return())
			{
				if (t->getClassPart() == ";")
				{
					t->next();
					return true;
				}
			}
		}
		return false;
	}

	bool either_return()
	{
		if (t->getClassPart() == "int_const" || t->getClassPart() == "float_const" || t->getClassPart() == "char_const" || t->getClassPart() == "string_const"
			|| t->getClassPart() == "true" || t->getClassPart() == "false" || t->getClassPart() == "("
			|| t->getClassPart() == "!" || t->getClassPart() == "this" || t->getClassPart() == "ID" || t->getClassPart() == "inc_dec")
		{
			string T4 = "";
			if (OE(T4))
			{
				string t1 = compatibilityCheck(ret_def, T4, "=");
				if (t1 == "Incompatible")
				{
					cout << "Method Return type: " << ret_def << " is incompatible at Line No: " << t->getLineno() << " of return Expression type: " << T4 << endl;
				}
				return true;
			}
		}
		else if (t->getClassPart() == "new")
		{
			t->next();
			if (return1())
			{
				return true;
			}
		}
		else if (t->getClassPart() == ";")
		{
			return true;
		}
		return false;
	}

	bool return1()
	{
		if (t->getClassPart() == "ID")
		{
			t->next();
			if (return2())
			{
				return true;
			}
		}
		else if (t->getClassPart() == "DT")
		{
			t->next();
			if (t->getClassPart() == "[")
			{
				t->next();
				string T4 = "";
				if (OE(T4))
				{
					if (t->getClassPart() == "]")
					{
						t->next();
						if (return_choice())
						{
							return true;
						}
					}
				}
			}
		}
		return false;
	}

	bool return2()
	{
		if (t->getClassPart() == "(")
		{
			t->next();
			if (PL())
			{
				if (t->getClassPart() == ")")
				{
					t->next();
					return true;
				}
			}
		}
		else if (t->getClassPart() == "[")
		{
			t->next();
			string T4 = "";
			if (OE(T4))
			{
				if (t->getClassPart() == "]")
				{
					t->next();
					if (return_obj_choice())
					{
						return true;
					}
				}
			}
		}
		return false;
	}

	bool return_choice()
	{
		if (t->getClassPart() == "{")
		{
			t->next();
			if (PL())
			{
				if (t->getClassPart() == "}")
				{
					t->next();
					return true;
				}
			}
		}
		else if (t->getClassPart() == ";" || t->getClassPart() == ",")
		{
			return true;
		}
		return false;
	}

	bool return_obj_choice()
	{
		if (t->getClassPart() == "{")
		{
			t->next();
			if (PL_dec())
			{
				if (t->getClassPart() == "}")
				{
					t->next();
					return true;
				}
			}
		}
		else if (t->getClassPart() == ";" || t->getClassPart() == ",")
		{
			return true;
		}
		return false;
	}

	bool class_st()
	{
		if (t->getClassPart() == "static" || t->getClassPart() == "abstract" || t->getClassPart() == "final" || t->getClassPart() == "class")
		{
			if (class_choice())
			{
				if (class_def())
				{
					return true;
				}
			}
		}
		return false;
	}

	bool class_def()
	{
		class_access_modifier = "public";
		if (t->getClassPart() == "class")
		{
			class_type = "class";
			t->next();
			if (t->getClassPart() == "ID")
			{
				class_name = t->getValuePart();
				my_stack.push(class_name);
				class_access_modifier = "public";
				t->next();
				if (inhrt())
				{
					if (t->getClassPart() == "{")
					{
						current_scope = maintable->createScope();
						if (!maintable->insertMainTable(class_name, class_type, class_access_modifier, class_category, class_parent, new ClassTable(), new FunctionTable()))
						{
							cout << "Redeclaration Error of Class at Line Number: " << t->getLineno() << endl;
						}
						else
						{
							cout << "entry Successfull !" << endl;
						}
						t->next();
						if (CB())
						{
							if (t->getClassPart() == "}")
							{

								functiontable = maintable->findFunctionTable(my_stack.top());
								functiontable->printFunctionTable(my_stack.top());
								classtable = maintable->findClassTable(my_stack.top());
								classtable->printClassTable(my_stack.top());
								current_scope = maintable->deleteScope();
								class_name = my_stack.top();
								my_stack.pop();
								t->next();
								return true;
							}
						}
					}
				}
			}
		}
		return false;
	}

	bool class_choice()
	{
		if (t->getClassPart() == "static" || t->getClassPart() == "abstract" || t->getClassPart() == "final")
		{
			class_category = t->getClassPart();
			t->next();
			return true;
		}
		else if (t->getClassPart() == "class")
		{
			return true;
		}
		return false;
	}

	bool inhrt()
	{
		class_parent = "NULL";
		if (t->getClassPart() == "extends")
		{
			t->next();
			if (t->getClassPart() == "ID")
			{
				string type, category;
				type = maintable->lookupMT(t->getValuePart(), &category);
				if (type == "NULL")
				{
					cout << "Undeclared Identifier at Line no: " << t->getLineno() << endl;
				}
				else if (category == "final")
				{
					cout << "Class can't be inherited ! Error at line no: " << t->getLineno() << endl;
				}
				else
				{
					class_parent = t->getValuePart();
				}
				t->next();
				if (inhrt_choice())
				{
					return true;
				}
			}
		}
		else if (t->getClassPart() == "{")
		{
			return true;
		}
		return false;
	}

	bool inhrt_choice()
	{
		if (t->getClassPart() == ",")
		{
			t->next();
			if (t->getClassPart() == "ID")
			{
				string type, category;
				type = maintable->lookupMT(t->getValuePart(), &category);
				if (type == "NULL")
				{
					cout << "Undeclared Identifier at Line no: " << t->getLineno() << endl;
					return false;
				}
				else if (category == "final")
				{
					cout << "Class can't be inherited ! at line no: " << t->getLineno() << endl;
					return false;
				}
				else
				{
					class_parent += t->getValuePart();
				}
				t->next();
				if (inhrt_choice())
				{
					return true;
				}
			}
		}
		else if (t->getClassPart() == "{")
		{
			return true;
		}
		return false;
	}

	bool CB()
	{
		class_category = "General";
		class_access_modifier = "default";
		if (t->getClassPart() == "static")
		{
			class_category = "static";
			t->next();
			if (CB_class())
			{
				return true;
			}
		}
		else if (t->getClassPart() == "private" || t->getClassPart() == "public" || t->getClassPart() == "protected")
		{
			class_access_modifier = t->getClassPart();
			if (access_modifiers())
			{
				if (static_choice())
				{
					if (CB1())
					{
						return true;
					}
				}
			}
		}
		else if (t->getClassPart() == "DT" || t->getClassPart() == "ID" || t->getClassPart() == "void")
		{
			if (CB1())
			{
				return true;
			}
		}
		else if (t->getClassPart() == "abstract")
		{
			t->next();
			if (class_def())
			{
				if (CB())
				{
					return true;
				}
			}
		}
		else if (t->getClassPart() == "final")
		{
			t->next();
			if (class_def())
			{
				if (CB())
				{
					return true;
				}
			}
		}
		else if (class_def())
		{
			if (CB())
			{
				return true;
			}
		}
		else if (t->getClassPart() == "}")
		{
			return true;
		}
		return false;
	}

	bool CB_class()
	{
		if (acc_choice())
		{
			if (CB1())
			{
				return true;
			}
		}
		else if (class_def())
		{
			if (CB())
			{
				return true;
			}
		}
		return false;
	}

	bool acc_choice()
	{
		if (access_modifiers())
		{
			return true;
		}
		else if (t->getClassPart() == "DT" || t->getClassPart() == "ID" || t->getClassPart() == "void")
		{
			return true;
		}
		return false;
	}

	bool access_modifiers()
	{
		if (t->getClassPart() == "public" || t->getClassPart() == "private" || t->getClassPart() == "protected")
		{
			class_access_modifier = t->getClassPart();
			t->next();
			return true;
		}
		return false;
	}

	bool static_choice()
	{
		if (t->getClassPart() == "static")
		{
			class_category = "static";
			t->next();
			return true;
		}
		else if (t->getClassPart() == "DT" || t->getClassPart() == "ID" || t->getClassPart() == "void")
		{
			return true;
		}
		return false;
	}

	bool CB1()
	{
		if (t->getClassPart() == "DT")
		{
			ret_def = t->getValuePart();
			type = t->getValuePart();
			t->next();
			if (fn1())
			{
				if (CB())
				{
					return true;
				}
			}
		}
		else if (t->getClassPart() == "void")
		{
			ret_def = t->getClassPart();
			t->next();
			if (func())
			{
				if (CB())
				{
					return true;
				}
			}
		}
		else if (t->getClassPart() == "ID")
		{
			ret_def = t->getValuePart();
			t->next();
			if (fn2())
			{
				if (CB())
				{
					return true;
				}
			}
		}
		return false;
	}

	bool fn1()
	{
		if (t->getClassPart() == "ID")
		{
			class_name = t->getValuePart();
			t->next();
			if (fn_simple())
			{
				return true;
			}
		}
		else if (t->getClassPart() == "[")
		{
			t->next();
			if (t->getClassPart() == "]")
			{
				ret_def += "[]";
				t->next();
				if (t->getClassPart() == "ID")
				{
					class_name = t->getValuePart();
					t->next();
					if (fn_arr())
					{
						return true;
					}
				}
			}
		}
		return false;
	}

	bool fn2()
	{
		if (t->getClassPart() == "ID")
		{
			class_name = t->getValuePart();
			t->next();
			if (fn2_simple())
			{
				return true;
			}
		}
		else if (t->getClassPart() == "[")
		{
			t->next();
			if (t->getClassPart() == "]")
			{
				ret_def += "[]";
				t->next();
				if (t->getClassPart() == "ID")
				{
					class_name = t->getValuePart();
					t->next();
					if (fn2_arr())
					{
						return true;
					}
				}
			}
		}
		else if (t->getClassPart() == "(")
		{
			current_scope = maintable->createScope();
			classtable = maintable->findClassTable(my_stack.top());
			if (classtable->insertCT(class_name, type_def + "->" + ret_def, class_access_modifier, class_category))
			{
			}
			else
			{
				cout << "Redeclaration Error at Line No: " << t->getLineno() << endl;
			}
			t->next();
			if (def())
			{
				if (t->getClassPart() == ")")
				{
					t->next();
					if (t->getClassPart() == "{")
					{
						t->next();
						if (MST1())
						{
							if (t->getClassPart() == "}")
							{
								current_scope = maintable->deleteScope();
								t->next();
								return true;
							}
						}
					}
				}
			}
		}
		return false;
	}

	bool fn_simple()
	{
		if (t->getClassPart() == "(")
		{
			current_scope = maintable->createScope();
			t->next();
			if (def())
			{
				classtable = maintable->findClassTable(my_stack.top());
				if (classtable->insertCT(class_name, type_def + "->" + ret_def, class_access_modifier, class_category))
				{
				}
				else
				{
					cout << "Redeclaration Error at Line No: " << t->getLineno() << endl;
				}
				if (t->getClassPart() == ")")
				{
					t->next();
					if (t->getClassPart() == "{")
					{
						t->next();
						if (MST1())
						{
							if (t->getClassPart() == "}")
							{
								current_scope = maintable->deleteScope();
								t->next();
								return true;
							}
						}
					}
				}
			}
		}
		else if (t->getClassPart() == "=" || t->getClassPart() == "," || t->getClassPart() == ";")
		{
			classtable = maintable->findClassTable(my_stack.top());
			if (classtable->insertCT(class_name, ret_def, class_access_modifier, class_category))
			{
			}
			else
			{
				cout << "Redeclaration Error at Line No: " << t->getLineno() << endl;
			}
		if (init())
		{
			if (list())
			{
				return true;
			}
		}
		}
		return false;
	}

	bool fn2_simple()
	{
		if (t->getClassPart() == "(")
		{
			current_scope = maintable->createScope();
			t->next();
			if (def())
			{

				classtable = maintable->findClassTable(my_stack.top());
				if (classtable->insertCT(class_name, type_def + "->" + ret_def, class_access_modifier, class_category))
				{
				}
				else
				{
					cout << "Redeclaration Error at Line No: " << t->getLineno() << endl;
				}
				if (t->getClassPart() == ")")
				{
					t->next();
					if (t->getClassPart() == "{")
					{
						t->next();
						if (MST1())
						{
							if (t->getClassPart() == "}")
							{
								current_scope = maintable->deleteScope();
								t->next();
								return true;
							}
						}
					}
				}
			}
		}
		else if (t->getClassPart() == "=" || t->getClassPart() == "," || t->getClassPart() == ";")
		{
			classtable = maintable->findClassTable(my_stack.top());
			if (classtable->insertCT(class_name, ret_def, class_access_modifier, class_category))
			{
			}
			else
			{
				cout << "Redeclaration Error at Line No: " << t->getLineno() << endl;
			}
			if (obj_init())
			{
				if (obj_list())
				{
					return true;
				}
			}
		}
		return false;
	}

	bool fn_arr()
	{
		if (t->getClassPart() == "(")
		{
			current_scope = maintable->createScope();
			t->next();
			if (def())
			{
				classtable = maintable->findClassTable(my_stack.top());
				if (classtable->insertCT(class_name, type_def + "->" + ret_def, class_access_modifier, class_category))
				{
				}
				else
				{
					cout << "Redeclaration Error at Line No: " << t->getLineno() << endl;
				}
				if (t->getClassPart() == ")")
				{
					t->next();
					if (t->getClassPart() == "{")
					{
						t->next();
						if (MST1())
						{
							if (t->getClassPart() == "}")
							{
								current_scope = maintable->deleteScope();
								t->next();
								return true;
							}
						}
					}
				}
			}
		}
		else if (t->getClassPart() == "=" || t->getClassPart() == "," || t->getClassPart() == ";")
		{
			classtable = maintable->findClassTable(my_stack.top());
			if (classtable->insertCT(class_name, ret_def, class_access_modifier, class_category))
			{
			}
			else
			{
				cout << "Redeclaration Error at Line No: " << t->getLineno() << endl;
			}
			if (init_arr())
			{
				if (list_arr())
				{
					return true;
				}
			}
		}
		return false;
	}

	bool fn2_arr()
	{
		if (t->getClassPart() == "(")
		{
			current_scope = maintable->createScope();
			t->next();
			if (def())
			{
				classtable = maintable->findClassTable(my_stack.top());
				if (classtable->insertCT(class_name, type_def + "->" + ret_def, class_access_modifier, class_category))
				{
				}
				else
				{
					cout << "Redeclaration Error at Line No: " << t->getLineno() << endl;
				}
				if (t->getClassPart() == ")")
				{
					t->next();
					if (t->getClassPart() == "{")
					{
						t->next();
						if (MST1())
						{
							if (t->getClassPart() == "}")
							{
								current_scope = maintable->deleteScope();
								t->next();
								return true;
							}
						}
					}
				}
			}
		}
		else if (t->getClassPart() == "=" || t->getClassPart() == "," || t->getClassPart() == ";")
		{
			classtable = maintable->findClassTable(my_stack.top());
			if (classtable->insertCT(class_name, ret_def, class_access_modifier, class_category))
			{
			}
			else
			{
				cout << "Redeclaration Error at Line No: " << t->getLineno() << endl;
			}
			if (obj_init_arr())
			{
				if (obj_list_arr())
				{
					return true;
				}
			}
		}
		return false;
	}

	bool class_rep()
	{
		if (t->getClassPart() == "static" || t->getClassPart() == "abstract" || t->getClassPart() == "final" || t->getClassPart() == "class")
		{
			if (class_st())
			{
				if (class_rep())
				{
					return true;
				}
			}
		}
		else if (t->getClassPart() == "}")
		{
			return true;
		}
		return false;
	}

	bool S()
	{
		if (t->getClassPart() == "namespace")
		{
			t->next();
			if (t->getClassPart() == "ID")
			{
				t->next();
				if (t->getClassPart() == "{")
				{
					t->next();
					if (class_rep())
					{
						if (t->getClassPart() == "}")
						{
							t->next();
							return true;
						}
					}
				}
			}
		}
		return false;
	}

	string compatibilityCheck(string type, string Operator)
	{
		if ((type == "int"  || type == "float" || type == "char") && (Operator == "inc_dec"))
		{
			return type;
		}
		else if ((type == "int" || type == "bool" || type == "float" || type == "char") && (Operator == "!"))
		{
			return "bool";
		}
		return "Incompatible";
	}

	string compatibilityCheck(string leftType, string rightType, string Operator)
	{
		if (leftType == "int" && rightType == "int")
		{
			if (Operator == "+" || Operator == "-" || Operator == "*" || Operator == "/" || Operator == "%" || Operator == "=")
				return "int";
			if (Operator == "<" || Operator == ">" || Operator == "<=" || Operator == ">=" || Operator == "!=" || Operator == "==" || Operator == "=")
				return "bool";
		}
		else if ((leftType == "int" && rightType == "float") || (leftType == "float" && rightType == "int") || (leftType == "float" && rightType == "float"))
		{
			if(Operator == "+" || Operator == "-" || Operator == "*" || Operator == "/" || Operator == "%" ||  Operator == "=" )
				return "float";
			if (Operator == "<" || Operator == ">" || Operator == "<=" || Operator == ">=" || Operator == "!=" || Operator == "==")
				return "bool";
		}
		else if ((leftType == "string" && rightType == "string"))
		{
			if(Operator == "+")
				return "string";
			if (Operator == "=" || Operator == "<" || Operator == ">" || Operator == "<=" || Operator == ">=" || Operator == "!=" || Operator == "==")
				return "bool";
		}
		else if (leftType == "bool" && rightType == "bool" && 
			(Operator == "=" || Operator == "<" || Operator == ">" || Operator == "<=" || Operator == ">=" || Operator == "!=" || Operator == "==" || Operator == "&&" || Operator == "||"))
		{
			return "bool";
		}
		else if (leftType == "char" && rightType == "char" && 
			(Operator == "=" || Operator == "<" || Operator == ">" || Operator == "<=" || Operator == ">=" || Operator == "!=" || Operator == "==" || Operator == "&&" || Operator == "||"))
		{
			return "bool";
		}
		return "Incompatible";
	}

	string ConstType(string type)
	{
		if (type == "int_const")
		{
			return "int";
		}

		if (type == "float_const")
		{
			return "float";
		}

		if (type == "string_const")
		{
			return "string";
		}

		if (type == "char_const")
		{
			return "char";
		}

		if (type == "true" || type =="false")
		{
			return "bool";
		}
		return "none";
	}
};

