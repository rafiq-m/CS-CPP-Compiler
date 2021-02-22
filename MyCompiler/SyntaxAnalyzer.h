#pragma once
#include "LinkedList.h"
class SyntaxAnalyzer
{
	LinkedList* t;
public:
	SyntaxAnalyzer(LinkedList* tokens)
	{
		this->t = tokens;
		checkSyntactically();
	}
	void checkSyntactically() {
		if (S()) {
			if(t->getClassPart() == "$")
				cout << "Okay All correct !" << endl;
		}
		else
		{
			cout << "Error at Line No: " << t->getLineno() << "   " << t->getClassPart() << endl;
		}
	}

	bool practice() {
		if (t->getClassPart() == "ID") {
			t->next();
			if (t->getClassPart() == "{") {
				t->next();
				if (MST1()) {
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

	bool dec(){
		if (t->getClassPart() == "DT") {
			t->next();
			if (dec_choice()) {
				return true;
			}
		}
		return false;
	}

	bool dec_choice(){
		if (t->getClassPart() == "[") {
			t->next();
			if (t->getClassPart() == "]") {
				t->next();
				if (t->getClassPart() == "ID") {
					t->next();
					if (init_arr()) {
						if (list_arr()) {
							return true;
						}
					}
				}
			}
		}
		else if (t->getClassPart() == "ID") {
			t->next();
			if (init()) {
				if (list()) {
					return true;
				}
			}
		}
		return false;
	}

	bool init() {
		if (t->getClassPart() == "=") {
			t->next();
			if (OE()) {
				return true;
			}
		}
		else if (t->getClassPart() == ";" || t->getClassPart() == ",") {
			return true;
		}
		return false;
	}

	bool list() {
		if (t->getClassPart() == ";") {
			t->next();
			return true;
		}
		else if (t->getClassPart() == ",") {
			t->next();
			if (t->getClassPart() == "ID") {
				t->next();
				if (init()) {
					if (list()) {
						return true;
					}
				}
			}
		}
		return false;
	}

	bool init_arr() {
		if (t->getClassPart() == "=") {
			t->next();
			if (init_arr_choice()) {
				return true;
			}
		}
		else if (t->getClassPart() == ";" || t->getClassPart() == ",") {
			return true;
		}
		return false;
	}

	bool list_arr() {
		if (t->getClassPart() == ";") {
			t->next();
			return true;
		}
		else if (t->getClassPart() == ",") {
			t->next();
			if (t->getClassPart() == "ID") {
				t->next();
				if (init_arr()) {
					if (list_arr()) {
						return true;
					}
				}
			}
		}
		return false;
	}

	bool init_arr_choice() {
		if (t->getClassPart() == "new") {
			t->next();
			if (t->getClassPart() == "DT") {
				t->next();
				if (t->getClassPart() == "[") {
					t->next();
					if (OE()) {
						if (t->getClassPart() == "]") {
							t->next();
							if (return_choice()) {
								return true;
							}
						}
					}
				}
			}
		}
		else if (t->getClassPart() == "{") {
			t->next();
			if (PL()) {
				if (t->getClassPart() == "}") {
					t->next();
					return true;
				}
			}
		}
		else if (t->getClassPart() == ";" || t->getClassPart() == ",") {
			return true;
		}
		return false;
	}

	bool this_st() {
		if (t->getClassPart() == "this") {
			t->next();
			if (t->getClassPart() == ".") {
				t->next();
				return true;
			}
		}
		else if(t->getClassPart() == "ID"){
			return true;
		}
		return false;
	}

	bool OE() {
		if (AE()) {
			if (OE_()) {
				return true;
			}
		}
		return false;
	}

	bool OE_() {
		if (t->getClassPart() == "||") {
			t->next();
			if (AE()) {
				if (OE_()) {
					return true;
				}
			}
		}
		else if (t->getClassPart() == ")" || t->getClassPart() == "]" || t->getClassPart() == ";" || t->getClassPart() == "," || t->getClassPart() == "}") {
			return true;
		}
		return false;
	}
	
	bool AE() {
		if (RE()) {
			if (AE_()) {
				return true;
			}
		}
		return false;
	}

	bool AE_() {
		if (t->getClassPart() == "&&") {
			t->next();
			if (RE()) {
				if (AE_()) {
					return true;
				}
			}
		}
		else if ( t->getClassPart() == "||" ||
			t->getClassPart() == ")" || t->getClassPart() == "]" || t->getClassPart() == ";" || t->getClassPart() == "," || t->getClassPart() == "}") {
			return true;
		}
		return false;
	}

	bool RE() {
		if (PE()) {
			if (RE_()) {
				return true;
			}
		}
		return false;
	}
	
	bool RE_() {
		if (t->getClassPart() == "rop") {
			t->next();
			if (PE()) {
				if (RE_()) {
					return true;
				}
			}
		}
		else if ( t->getClassPart() == "&&" || t->getClassPart() == "||" ||
			t->getClassPart() == ")" || t->getClassPart() == "]" || t->getClassPart() == ";" || t->getClassPart() == "," || t->getClassPart() == "}") {
			return true;
		}
		return false;
	}

	bool PE() {
		if (ME()) {
			if (PE_()) {
				return true;
			}
		}
		return false;
	}
	
	bool PE_() {
		if (t->getClassPart() == "pm") {
			t->next();
			if (ME()) {
				if (PE_()) {
					return true;
				}
			}
		}
		else if (t->getClassPart() == "rop" || t->getClassPart() == "&&" || t->getClassPart() == "||" ||
			t->getClassPart() == ")" || t->getClassPart() == "]" || t->getClassPart() == ";" || t->getClassPart() == "," || t->getClassPart() == "}") {
			return true;
		}
		return false;
	}
	
	bool ME() {
		if (F()) {
			if (ME_()) {
				return true;
			}
		}
		return false;
	}
	
	bool ME_(){
		if (t->getClassPart() == "mdm") {
			t->next();
			if (F()) {
				if (ME_()) {
					return true;
				}
			}
		}
		else if (t->getClassPart() == "pm" || t->getClassPart() == "rop" || t->getClassPart() == "&&" || t->getClassPart() == "||" ||
			t->getClassPart() == ")" || t->getClassPart() == "]" || t->getClassPart() == ";" || t->getClassPart() == "," || t->getClassPart() == "}") {
			return true;
		}
		return false;
	}
	
	bool F() {
		if (constant()) {
			return true;
		}
		else if (t->getClassPart() == "(") {
			t->next();
			if (OE()) {
				if (t->getClassPart() == ")") {
					t->next();
					return true;
				}
			}
		}
		else if (t->getClassPart() == "!") {
			t->next();
			if (F()) {
				return true;
			}
		}
		else if (this_st()) {
			if (t->getClassPart() == "ID") {
				t->next();
				if (XY()) {
					return true;
				}
			}
		}
		else if (t->getClassPart() == "inc_dec") {
			t->next();
			if (this_st()) {
				if (t->getClassPart() == "ID") {
					t->next();
					if (X()) {
						return true;
					}
				}
			}
		}
		return false;
	}
	
	bool XY() {
		if (t->getClassPart() == "[") {
			t->next();
			if (OE()) {
				if (t->getClassPart() == "]") {
					t->next();
					if (XY1()) {
						return true;
					}
				}
			}
		}
		else if (t->getClassPart() == "(") {
			t->next();
			if (PL()) {
				if (t->getClassPart() == ")") {
					t->next();
					if (XY2()) {
						return true;
					}
				}
			}
		}
		else if (t->getClassPart() == ".") {
			t->next();
			if (t->getClassPart() == "ID") {
				t->next();
				if (XY()) {
					return true;
				}
			}
		}
		else if (t->getClassPart() == "inc_dec") {
			t->next();
			return true;
		}
		else if (t->getClassPart() == "mdm" || t->getClassPart() == "pm" || t->getClassPart() == "rop" || t->getClassPart() == "&&" || t->getClassPart() == "||" ||
			t->getClassPart() == ")" || t->getClassPart() == "]" || t->getClassPart() == ";" || t->getClassPart() == "," || t->getClassPart() == "}") {
			return true;
		}
		return false;
	}
	
	bool XY2() {
		if (t->getClassPart() == ".") {
			t->next();
			if (t->getClassPart() == "ID") {
				t->next();
				if (XY()) {
					return true;
				}
			}
		}
		else if (t->getClassPart() == "[") {
			t->next();
			if (OE()) {
				if (t->getClassPart() == "]") {
					t->next();
					if (XY1()) {
						return true;
					}
				}
			}
		}
		else if (t->getClassPart() == "mdm" || t->getClassPart() == "pm" || t->getClassPart() == "rop" || t->getClassPart() == "&&" || t->getClassPart() == "||" ||
			t->getClassPart() == ")" || t->getClassPart() == "]" || t->getClassPart() == ";" || t->getClassPart() == "," || t->getClassPart() == "}") {
			return true;
		}
		return false;
	}
	
	bool XY1() {
		if (t->getClassPart() == ".") {
			t->next();
			if (t->getClassPart() == "ID") {
				t->next();
				if (XY()) {
					return true;
				}
			}
		}
		else if (t->getClassPart() == "inc_dec") {
			t->next();
			return true;
		}
		else if (t->getClassPart() == "mdm" || t->getClassPart() == "pm" || t->getClassPart() == "rop" || t->getClassPart() == "&&" || t->getClassPart() == "||" ||
			t->getClassPart() == ")" || t->getClassPart() == "]" || t->getClassPart() == ";" || t->getClassPart() == "," || t->getClassPart() == "}") {
			return true;
		}
		return false;
	}
	
	bool constant() {
		if (t->getClassPart() == "int_const" || t->getClassPart() == "float_const" || t->getClassPart() == "char_const" || t->getClassPart() == "string_const"
			|| t->getClassPart() == "true" || t->getClassPart() == "false" || t->getClassPart() == "bool" || t->getClassPart() == "var") {
			t->next();
			return true;
		}
		return false;
	}

	bool PL() {
		if (OE()) {
			if (PL1()) {
				return true;
			}
		}
		else if (t->getClassPart() == ")" || t->getClassPart() == "}") {
			return true;
		}
		return false;
	}

	bool PL1() {
		if (t->getClassPart() == ",") {
			t->next();
			if (OE()) {
				if (PL1()) {
					return true;
				}
			}
		}
		else if (t->getClassPart() == ")" || t->getClassPart() == "}") {
			return true;
		}
		return false;
	}
	//some questions regarding first and follow set of X 
	bool X() {
		if (t->getClassPart() == "[") {
			t->next();
			if (OE()) {
				if (t->getClassPart() == "]") {
					t->next();
					if (X1()) {
						return true;
					}
				}
			}
		}
		else if (t->getClassPart() == "(") {
			t->next();
			if (PL()) {
				if (t->getClassPart() == ")") {
					t->next();
					if (X2()) {
						return true;
					}
				}
			}
		}
		else if (t->getClassPart() == ".") {
			t->next();
			if (t->getClassPart() == "ID") {
				t->next();
				if (X()) {
					return true;
				}
			}
		}
		//Follow Of X // kuch masley hain isme miss se discuss karna he
		else if (t->getClassPart() == ";" || t->getClassPart() == "pm" || t->getClassPart() == "mdm" || t->getClassPart() == "rop" || t->getClassPart() == "&&" || t->getClassPart() == "||"
			|| t->getClassPart() == ")" || t->getClassPart() == "]" || t->getClassPart() == "," || t->getClassPart() == "}" || t->getClassPart() == "if" 
			|| t->getClassPart() == "while" || t->getClassPart() == "for" || t->getClassPart() == "try" || t->getClassPart() == "this" || t->getClassPart() == "inc_dec"
			|| t->getClassPart() == "ID" || t->getClassPart() == "DT" || t->getClassPart() == "continue" || t->getClassPart() == "break" || t->getClassPart() == "return"
			|| t->getClassPart() == "=") {
			return true;
		}
		return false;
	}

	bool X1() {
		if (t->getClassPart() == ".") {
			t->next();
			if (t->getClassPart() == "ID") {
				t->next();
				if (X()) {
					return true;
				}
			}
		}
		else if (t->getClassPart() == ";" || t->getClassPart() == "mdm" || t->getClassPart() == "rop" || t->getClassPart() == "&&" || t->getClassPart() == "||"
			|| t->getClassPart() == ")" || t->getClassPart() == "]" || t->getClassPart() == "," || t->getClassPart() == "}" || t->getClassPart() == "if"
			|| t->getClassPart() == "while" || t->getClassPart() == "for" || t->getClassPart() == "try" || t->getClassPart() == "this" || t->getClassPart() == "inc_dec"
			|| t->getClassPart() == "ID" || t->getClassPart() == "DT" || t->getClassPart() == "continue" || t->getClassPart() == "break" || t->getClassPart() == "return"
			|| t->getClassPart() == "=") {
			return true;
		}
		return false;
	}

	bool X2() {
		if (t->getClassPart() == ".") {
			t->next();
			if (t->getClassPart() == "ID") {
				t->next();
				if (X()) {
					return true;
				}
			}
		}
		else if (t->getClassPart() == "[") {
			t->next();
			if (OE()) {
				if (t->getClassPart() == "]") {
					t->next();
					if (t->getClassPart() == ".") {
						t->next();
						if (t->getClassPart() == "ID") {
							t->next();
							if (X()) {
								return true;
							}
						}
					}
				}
			}
		}
		return false;
	}

	bool obj_dec() {
		if (t->getClassPart() == "ID") {
			t->next();
			if (obj_dec_choice()) {
				return true;
			}
		}
		return false;
	}

	bool obj_dec_choice() {
		if (t->getClassPart() == "[") {
			t->next();
			if (t->getClassPart() == "]") {
				t->next();
				if (t->getClassPart() == "ID") {
					t->next();
					if (obj_init_arr()) {
						if (obj_list_arr()) {
							return true;
						}
					}
				}
			}
		}
		else if (t->getClassPart() == "ID") {
			t->next();
			if (obj_init()) {
				if (obj_list()) {
					return true;
				}
			}
		}
		return false;
	}

	bool obj_init() {
		if (t->getClassPart() == "=") {
			t->next();
			if (obj_init_choice()) {
				return true;
			}
		}
		else if (t->getClassPart() == ";" || t->getClassPart() == ",") {
			return true;
		}
		return false;
	}

	bool obj_init_choice() {
		if (t->getClassPart() == "new") {
			t->next();
			if (t->getClassPart() == "ID") {
				t->next();
				if (t->getClassPart() == "(") {
					t->next();
					if (PL()) {
						if (t->getClassPart() == ")") {
							t->next();
							return true;
						}
					}
				}
			}
		}
		else if (OE()) {
			return true;
		}
		else if (t->getClassPart() == "," || t->getClassPart() == ";") {
			return true;
		}
		return false;
	}

	bool obj_list() {
		if (t->getClassPart() == ";") {
			t->next();
			return true;
		}
		else if (t->getClassPart() == ",") {
			t->next();
			if (t->getClassPart() == "ID") {
				t->next();
				if (obj_init()) {
					if (obj_list()) {
						return true;
					}
				}
			}
		}
		return false;
	}

	bool obj_init_arr() {
		if (t->getClassPart() == "=") {
			t->next();
			if (obj_init_arr_choice()) {
				return true;
			}
		}
		else if (t->getClassPart() == ";" || t->getClassPart() == ",") {
			return true;
		}
		return false;
	}

	bool obj_list_arr() {
		if (t->getClassPart() == ";") {
			t->next();
			return true;
		}
		else if (t->getClassPart() == ",") {
			t->next();
			if (t->getClassPart() == "ID") {
				t->next();
				if (obj_init_arr()) {
					if (obj_list_arr()) {
						return true;
					}
				}
			}
		}
		return false;
	}

	bool obj_init_arr_choice() {
		if (t->getClassPart() == "new") {
			t->next();
			if (t->getClassPart() == "ID") {
				t->next();
				if (t->getClassPart() == "[") {
					t->next();
					if (OE()) {
						if (t->getClassPart() == "]") {
							t->next();
							if (return_obj_choice()) {
								return true;
							}
						}
					}
				}
			}
		}
		else if (t->getClassPart() == "{") {
			t->next();
			if (PL_dec()) {
				if (t->getClassPart() == "}") {
					t->next();
					return true;
				}
			}
		}
		else if (t->getClassPart() == ";" || t->getClassPart() == ",") {
			return true;
		}
		return false;
	}

	bool PL_dec() {
		if (t->getClassPart() == "new") {
			t->next();
			if (t->getClassPart() == "ID") {
				t->next();
				if (t->getClassPart() == "(") {
					t->next();
					if (PL()) {
						if (t->getClassPart() == ")") {
							t->next();
							if (PL1_dec()) {
								return true;
							}
						}
					}
				}
			}
		}
		else if (OE()) {
			if (PL1_dec()) {
				return true;
			}
		}
		return false;
	}

	bool PL1_dec() {
		if (t->getClassPart() == ",") {
			t->next();
			if (PL1_choice()) {
				if (PL1_dec()) {
					return true;
				}
			}
		}
		else if (t->getClassPart() == "}") {
			return true;
		}
		return false;
	}

	bool PL1_choice() {
		if (t->getClassPart() == "new") {
			t->next();
			if (t->getClassPart() == "ID") {
				t->next();
				if (t->getClassPart() == "(") {
					t->next();
					if (PL()) {
						if (t->getClassPart() == ")") {
							t->next();
							return true;
						}
					}
				}
			}
		}
		else if (OE()) {
			return true;
		}
		return false;
	}

	bool SST() {
		if (if_else()) {
			return true;
		}
		else if (while_st()) {
			return true;
		}
		else if (for_st()) {
			return true;
		}
		else if (t->getClassPart() == "inc_dec") {
			t->next();
			if (this_st()) {
				if (t->getClassPart() == "ID") {
					t->next();
					if (X()) {
						if (t->getClassPart() == ";") {
							t->next();
							return true;
						}
					}
				}
			}
		}
		else if (t->getClassPart() == "this") {
			t->next();
			if (t->getClassPart() == ".") {
				t->next();
				if (t->getClassPart() == "ID") {
					t->next();
					if (XY_SST()) {
						return true;
					}
				}
			}
		}
		else if (t->getClassPart() == "ID") {
			t->next();
			if (ZZZ()) {
				return true;
			}
		}
		else if (try_st()) {
			return true;
		}
		else if (t->getClassPart() == "DT") {
			t->next();
			if (dec_choice()) {
				return true;
			}
		}
		else if (t->getClassPart() == "continue") {
			t->next();
			if (t->getClassPart() == ";") {
				t->next();
				return true;
			}
		}
		else if (t->getClassPart() == "break") {
			t->next();
			if (t->getClassPart() == ";") {
				t->next();
				return true;
			}
		}
		else if (t->getClassPart() == ";") {
			t->next();
			return true;
		}
		return false;
	}

	bool ZZZ() {
		if (t->getClassPart() == "ID") {
			t->next();
			if (obj_init()) {
				if (obj_list()) {
					return true;
				}
			}
		}		
		else if (t->getClassPart() == "[") {
			t->next();
			if (XY_dec()) {
				return true;
			}
		}
		else if (XY1_SST()) {
			return true;
		}
		else if (t->getClassPart() == "(") {
			t->next();
			if (PL()) {
				if (t->getClassPart() == ")") {
					t->next();
					if (XY2_SST()) {
						return true;
					}
				}
			}
		}
		return false;
	}

	bool XY_dec() {
		if (OE()) {
			if (t->getClassPart() == "]") {
				t->next();
				if (XY1_SST()) {
					return true;
				}
			}
		}
		else if (t->getClassPart() == "]") {
			t->next();
			if (t->getClassPart() == "ID") {
				t->next();
				if (obj_init_arr()) {
					if (obj_list_arr()) {
						return true;
					}
				}
			}
		}
		return false;
	}

	bool XY_SST() {
		if (t->getClassPart() == "(") {
			t->next();
			if (PL()) {
				if (t->getClassPart() == ")") {
					t->next();
					if (XY2_SST()) {
						return true;
					}
				}
			}
		}
		else if (t->getClassPart() == ".") {
			t->next();
			if (t->getClassPart() == "ID") {
				t->next();
				if (XY_SST()) {
					return true;
				}
			}
		}
		else if (t->getClassPart() == "inc_dec") {
			t->next();
			if (t->getClassPart() == ";") {
				t->next();
				return true;
			}
		}
		else if (t->getClassPart() == "=") {
			t->next();
			if (OE()) {
				if (t->getClassPart() == ";") {
					t->next();
					return true;
				}
			}
		}
		else if (t->getClassPart() == "[") {
			t->next();
			if (OE()) {
				if (t->getClassPart() == "]") {
					t->next();
					if (XY1_SST()) {
						return true;
					}
				}
			}
		}
		else if (t->getClassPart() == ";") {
			t->next();
			return true;
		}
		return false;
	}

	bool XY1_SST() {
		if (t->getClassPart() == ".") {
			t->next();
			if (t->getClassPart() == "ID") {
				t->next();
				if (XY_SST()) {
					return true;
				}
			}
		}
		else if (t->getClassPart() == "inc_dec") {
			t->next();
			if (t->getClassPart() == ";") {
				t->next();
				return true;
			}
		}
		else if (t->getClassPart() == "=") {
			t->next();
			if (OE()) {
				if (t->getClassPart() == ";") {
					t->next();
					return true;
				}
			}
		}
		return false;
	}

	bool XY2_SST() {
		if (t->getClassPart() == ".") {
			t->next();
			if (t->getClassPart() == "ID") {
				t->next();
				if (XY_SST()) {
					return true;
				}
			}
		}
		else if (t->getClassPart() == "[") {
			t->next();
			if (OE()) {
				if (t->getClassPart() == "]") {
					t->next();
					if (XY1_SST()) {
						return true;
					}
				}
			}
		}
		else if (t->getClassPart() == ";") {
			t->next();
			return true;
		}
		return false;
	}
	//MST ka issue
	bool MST() {
		if (SST()) {
			if (MST()) {
				return true;
			}
		}
		else if (t->getClassPart() == "}") {
			return true;
		}
		return false;
	}
	
	bool for_st() {
		if (t->getClassPart() == "for") {
			t->next();
			if (t->getClassPart() == "(") {
				t->next();
				if (c1()) {
					if (c2()) {
						if (t->getClassPart() == ";") {
							t->next();
							if (c3()) {
								if (t->getClassPart() == ")") {
									t->next();
									if (t->getClassPart() == "{") {
										t->next();
										if (MST()) {
											if (t->getClassPart() == "}") {
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

	bool c1() {
		if (t->getClassPart() == "inc_dec") {
			t->next();
			if (this_st()) {
				if (t->getClassPart() == "ID") {
					t->next();
					if (X()) {
						if (t->getClassPart() == ";") {
							t->next();
							return true;
						}
					}
				}
			}
		}
		else if (t->getClassPart() == "DT") {
			t->next();
			if (dec_choice()) {
				return true;
			}
		}
		else if (t->getClassPart() == "this") {
			t->next();
			if (t->getClassPart() == ".") {
				t->next();
				if (t->getClassPart() == "ID") {
					t->next();
					if (X()) {
						if (c1_choice2()) {
							return true;
						}
					}
				}
			}
		}
		else if (t->getClassPart() == "ID") {
			t->next();
			if (ZZZ()) {
				return true;
			}
		}
		else if (t->getClassPart() == ";") {
			t->next();
			return true;
		}
		return false;
	}

	bool c1_choice() {
		if (obj_dec_choice()) {
			return true;
		}
		else if (X()) {
			if (c1_choice2()) {
				return true;
			}
		}
		return false;
	}

	bool c1_choice2() {
		if (t->getClassPart() == "=") {
			t->next();
			if (OE()) {
				if (t->getClassPart() == ";") {
					t->next();
					return true;
				}
			}
		}
		else if (t->getClassPart() == "inc_dec") {
			t->next();
			if (t->getClassPart() == ";") {
				t->next();
				return true;
			}
		}
		return false;
	}

	bool c2() {
		if (OE()) {
			return true;
		}
		else if (t->getClassPart() == ";") {
			return true;
		}
		return false;
	}

	bool c3() {
		if (this_st()) {
			if (t->getClassPart() == "ID") {
				t->next();
				if (X()) {
					if (c3_choice()) {
						return true;
					}
				}
			}
		}
		else if (t->getClassPart() == "inc_dec") {
			t->next();
			if (this_st()) {
				if (t->getClassPart() == "ID") {
					t->next();
					if (X()) {
						return true;
					}
				}
			}
		}
		else if (t->getClassPart() == "new") {
			t->next();
			if (t->getClassPart() == "ID") {
				t->next();
				if (t->getClassPart() == "(") {
					t->next();
					if (PL()) {
						if (t->getClassPart() == ")") {
							t->next();
							return true;
						}
					}
				}
			}
		}
		else if (t->getClassPart() == ")") {
			return true;
		}
		return false;
	}

	bool c3_choice() {
		if (t->getClassPart() == "inc_dec") {
			t->next();
			return true;
		}
		else if (t->getClassPart() == "=") {
			t->next();
			if (OE()) {
				return true;
			}
		}
		return false;
	}

	bool if_else() {
		if (t->getClassPart() == "if") {
			t->next();
			if (t->getClassPart() == "(") {
				t->next();
				if (OE()) {
					if (t->getClassPart() == ")") {
						t->next();
						if (t->getClassPart() == "{") {
							t->next();
							if (MST()) {
								if (t->getClassPart() == "}") {
									t->next();
									if (o_else()) {
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

	bool o_else() {
		if (t->getClassPart() == "else") {
			t->next();
			if (t->getClassPart() == "{") {
				t->next();
				if (MST()) {
					if (t->getClassPart() == "}") {
						t->next();
						return true;
					}
				}
			}
		}
		else if (t->getClassPart() == "if" || t->getClassPart() == "while" || t->getClassPart() == "for" || t->getClassPart() == "try"
			|| t->getClassPart() == "this" || t->getClassPart() == "inc_dec" || t->getClassPart() == "ID" || t->getClassPart() == "DT"
			|| t->getClassPart() == "continue" || t->getClassPart() == "break" || t->getClassPart() == "return" || t->getClassPart() == "}") {
			return true;
		}
		return false;
	}

	bool while_st() {
		if (t->getClassPart() == "while") {
			t->next();
			if (t->getClassPart() == "(") {
				t->next();
				if (OE()) {
					if (t->getClassPart() == ")") {
						t->next();
						if (t->getClassPart() == "{") {
							t->next();
							if (MST()) {
								if (t->getClassPart() == "}") {
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

	bool try_st() {
		if (t->getClassPart() == "try") {
			t->next();
			if (t->getClassPart() == "{") {
				t->next();
				if (MST()) {
					if (t->getClassPart() == "}") {
						t->next();
						if (catch_st()) {
							if (finally_st()) {
								return true;
							}
						}
					}
				}
			}
		}
		return false;
	}

	bool catch_st() {
		if (t->getClassPart() == "catch") {
			t->next();
			if (t->getClassPart() == "(") {
				t->next();
				if (t->getClassPart() == "ID") {
					t->next();
					if (t->getClassPart() == "ID") {
						t->next();
						if (t->getClassPart() == ")") {
							t->next();
							if (t->getClassPart() == "{") {
								t->next();
								if (MST()) {
									if (t->getClassPart() == "}") {
										t->next();
										if (catch_st1()) {
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

	bool catch_st1() {
		if (catch_st()) {
			if (catch_st1()) {
				return true;
			}
		}
		else if (t->getClassPart() == "if" || t->getClassPart() == "while" || t->getClassPart() == "for" || t->getClassPart() == "try"
			|| t->getClassPart() == "this" || t->getClassPart() == "inc_dec" || t->getClassPart() == "ID" || t->getClassPart() == "DT"
			|| t->getClassPart() == "continue" || t->getClassPart() == "break" || t->getClassPart() == "return" || t->getClassPart() == "}"
			|| t->getClassPart() == "finally") {
			return true;
		}
		return false;
	}

	bool finally_st() {
		if (t->getClassPart() == "finally") {
			t->next();
			if (t->getClassPart() == "{") {
				t->next();
				if (MST()) {
					if (t->getClassPart() == "}") {
						t->next();
						return true;
					}
				}
			}
		}
		else if (t->getClassPart() == "if" || t->getClassPart() == "while" || t->getClassPart() == "for" || t->getClassPart() == "try"
			|| t->getClassPart() == "this" || t->getClassPart() == "inc_dec" || t->getClassPart() == "ID" || t->getClassPart() == "DT"
			|| t->getClassPart() == "continue" || t->getClassPart() == "break" || t->getClassPart() == "return" || t->getClassPart() == "}") {
			return true;
		}
		return false;
	}

	bool func_dec() {
		if (ret_type_choice()) {
			if (t->getClassPart() == "ID") {
				t->next();
				if (t->getClassPart() == "(") {
					t->next();
					if (def()) {
						if (t->getClassPart() == ")") {
							t->next();
							if (t->getClassPart() == "{") {
								t->next();
								if (MST1()) {
									if (t->getClassPart() == "}") {
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

	bool ret_type_choice() {
		if (ret_type()) {
			return true;
		}
		else if (t->getClassPart() == "void") {
			t->next();
			return true;
		}
		else if (t->getClassPart() == "ID") {
			return true;
		}
		return false;
	}

	bool ret_type() {
		if (t->getClassPart() == "DT") {
			t->next();
			if (ret_choice()) {
				return true;
			}
		}
		else if (t->getClassPart() == "ID") {
			t->next();
			if (ret_choice()) {
				return true;
			}
		}
		return false;
	}

	bool ret_choice() {
		if (t->getClassPart() == "[") {
			t->next();
			if (t->getClassPart() == "]") {
				t->next();
				return true;
			}
		}
		else if (t->getClassPart() == ")" || t->getClassPart() == "," || t->getClassPart() == "ID") {
			return true;
		}
		return false;
	}

	bool def() {
		if (ret_type()) {
			if (t->getClassPart() == "ID") {
				t->next();
				if (more_def()) {
					return true;
				}
			}
		}
		else if (t->getClassPart() == ")") {
			return true;
		}
		return false;
	}

	bool more_def() {
		if (t->getClassPart() == ",") {
			t->next();
			if (ret_type()) {
				if (t->getClassPart() == "ID") {
					t->next();
					if (more_def()) {
						return true;
					}
				}
			}
		}
		else if (t->getClassPart() == ")") {
			return true;
		}
		return false;
	}

	bool SST1() {
		if (if_else()) {
			return true;
		}
		else if (while_st()) {
			return true;
		}
		else if (for_st()) {
			return true;
		}
		else if (t->getClassPart() == "inc_dec") {
			t->next();
			if (this_st()) {
				if (t->getClassPart() == "ID") {
					t->next();
					if (X()) {
						if (t->getClassPart() == ";") {
							t->next();
							return true;
						}
					}
				}
			}
		}
		else if (t->getClassPart() == "this") {
			t->next();
			if (t->getClassPart() == ".") {
				t->next();
				if (t->getClassPart() == "ID") {
					t->next();
					if (XY_SST()) {
						return true;
					}
				}
			}
		}
		else if (t->getClassPart() == "ID") {
			t->next();
			if (ZZZ()) {
				return true;
			}
		}
		else if (try_st()) {
			return true;
		}
		else if (t->getClassPart() == "DT") {
			t->next();
			if (dec_choice()) {
				return true;
			}
		}
		else if (return_st()) {
			return true;
		}
		else if (t->getClassPart() == ";") {
			t->next();
			return true;
		}
		return false;
	}

	bool MST1() {
		if (SST1()) {
			if (MST1()) {
				return true;
			}
		}
		else if (t->getClassPart() == "}") {
			return true;
		}
		return false;
	}
		
	bool func() {
		if (t->getClassPart() == "ID") {
			t->next();
			if (t->getClassPart() == "(") {
				t->next();
				if (def()) {
					if (t->getClassPart() == ")") {
						t->next();
						if (t->getClassPart() == "{") {
							t->next();
							if (MST1()) {
								if (t->getClassPart() == "}") {
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

	bool return_st() {
		if (t->getClassPart() == "return") {
			t->next();
			if (either_return()) {
				if (t->getClassPart() == ";") {
					t->next();
					return true;
				}
			}
		}
		return false;
	}

	bool either_return() {
		if (OE()) {
			return true;
		}
		else if (t->getClassPart() == "new") {
			t->next();
			if (return1()) {
				return true;
			}
		}
		else if (t->getClassPart() == ";") {
			return true;
		}
		return false;
	}

	bool return1() {
		if (t->getClassPart() == "ID") {
			t->next();
			if (return2()) {
				return true;
			}
		}
		else if (t->getClassPart() == "DT") {
			t->next();
			if (t->getClassPart() == "[") {
				t->next();
				if (OE()) {
					if (t->getClassPart() == "]") {
						t->next();
						if (return_choice()) {
							return true;
						}
					}
				}
			}
		}
		return false;
	}

	bool return2() {
		if (t->getClassPart() == "(") {
			t->next();
			if (PL()) {
				if (t->getClassPart() == ")") {
					t->next();
					return true;
				}
			}
		}
		else if (t->getClassPart() == "[") {
			t->next();
			if (OE()) {
				if (t->getClassPart() == "]") {
					t->next();
					if (return_obj_choice()) {
						return true;
					}
				}
			}
		}
		return false;
	}

	bool return_choice() {
		if (t->getClassPart() == "{") {
			t->next();
			if (PL()) {
				if (t->getClassPart() == "}") {
					t->next();
					return true;
				}
			}
		}
		else if (t->getClassPart() == ";" || t->getClassPart() == ",") {
			return true;
		}
		return false;
	}

	bool return_obj_choice() {
		if (t->getClassPart() == "{") {
			t->next();
			if (PL_dec()) {
				if (t->getClassPart() == "}") {
					t->next();
					return true;
				}
			}
		}
		else if (t->getClassPart() == ";" || t->getClassPart() == ",") {
			return true;
		}
		return false;
	}

	bool class_st() {
		if (class_choice()) {
			if (t->getClassPart() == "class") {
				t->next();
				if (t->getClassPart() == "ID") {
					t->next();
					if (inhrt()) {
						if (t->getClassPart() == "{") {
							t->next();
							if (CB_MST()) {
								if (t->getClassPart() == "}") {
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

	bool CB_MST() {
		if (CB()) {
			if (CB_MST()) {
				return true;
			}
		}
		else if (t->getClassPart() == "}") {
			return true;
		}
		return false;
	}

	bool class_choice() {
		if (t->getClassPart() == "static" || t->getClassPart() == "abstract" || t->getClassPart() == "final") {
			t->next();
			return true;
		}
		else if (t->getClassPart() == "class") {
			return true;
		}
		return false;
	}

	bool inhrt() {
		if (t->getClassPart() == "extends") {
			t->next();
			if (t->getClassPart() == "ID") {
				t->next();
				if (inhrt_choice()) {
					return true;
				}
			}
		}
		else if (t->getClassPart() == "{") {
			return true;
		}
		return false;
	}

	bool inhrt_choice() {
		if (t->getClassPart() == ",") {
			t->next();
			if (t->getClassPart() == "ID") {
				t->next();
				if (inhrt_choice()) {
					return true;
				}
			}
		}
		else if (t->getClassPart() == "{") {
			return true;
		}
		return false;
	}

	bool CB() {
		if (t->getClassPart() == "static") {
			t->next();
			if (acc_choice()) {
				if (CB1()) {
					return true;
				}
			}
		}
		else if (access_modifiers()) {
			if (static_choice()) {
				if (CB1()) {
					return true;
				}
			}
		}
		else if (CB1()) {
			return true;
		}
		return false;
	}

	bool acc_choice() {
		if (access_modifiers()) {
			return true;
		}
		else if (t->getClassPart() == "DT" || t->getClassPart() == "ID" || t->getClassPart() == "void") {
			return true;
		}
		return false;
	}

	bool access_modifiers() {
		if (t->getClassPart() == "public" || t->getClassPart() == "private" || t->getClassPart() == "protected") {
			t->next();
			return true;
		}
		return false;
	}

	bool static_choice() {
		if (t->getClassPart() == "static") {
			t->next();
			return true;
		}
		else if (t->getClassPart() == "DT" || t->getClassPart() == "ID" || t->getClassPart() == "void") {
			return true;
		}
		return false;
	}

	bool CB1() {
		if (t->getClassPart() == "DT") {
			t->next();
			if (fn1()) {
				if (CB()) {
					return true;
				}
			}
		}
		else if (t->getClassPart() == "void") {
			t->next();
			if (func()) {
				if (CB()) {
					return true;
				}
			}
		}
		else if (t->getClassPart() == "ID") {
			t->next();
			if (fn2()) {
				if (CB()) {
					return true;
				}
			}
		}
		return false;
	}

	bool fn1() {
		if (t->getClassPart() == "ID") {
			t->next();
			if (fn_simple()) {
				return true;
			}
		}
		else if (t->getClassPart() == "[") {
			t->next();
			if (t->getClassPart() == "]") {
				t->next();
				if (fn_arr()) {
					return true;
				}
			}
		}
		return false;
	}

	bool fn2() {
		if (t->getClassPart() == "ID") {
			t->next();
			if (fn2_simple()) {
				return true;
			}
		}
		else if (t->getClassPart() == "[") {
			t->next();
			if (t->getClassPart() == "]") {
				t->next();
				if (fn2_arr()) {
					return true;
				}
			}
		}
		else if (t->getClassPart() == "(") {
			t->next();
			if (def()) {
				if (t->getClassPart() == ")") {
					t->next();
					if (t->getClassPart() == "{") {
						t->next();
						if (MST1()) {
							if (t->getClassPart() == "}") {
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

	bool fn_simple() {
		if (t->getClassPart() == "(") {
			t->next();
			if (def()) {
				if (t->getClassPart() == ")") {
					t->next();
					if (t->getClassPart() == "{") {
						t->next();
						if (MST1()) {
							if (t->getClassPart() == "}") {
								t->next();
								return true;
							}
						}
					}
				}
			}
		}
		else if (init()) {
			if (list()) {
				return true;
			}
		}
		return false;
	}

	bool fn2_simple() {
		if (t->getClassPart() == "(") {
			t->next();
			if (def()) {
				if (t->getClassPart() == ")") {
					t->next();
					if (t->getClassPart() == "{") {
						t->next();
						if (MST1()) {
							if (t->getClassPart() == "}") {
								t->next();
								return true;
							}
						}
					}
				}
			}
		}
		else if (obj_init()) {
			if (obj_list()) {
				return true;
			}
		}
		return false;
	}

	bool fn_arr() {
		if (func()) {
			return true;
		}
		else if (init_arr()) {
			if (list_arr()) {
				return true;
			}
		}
		return false;
	}

	bool fn2_arr() {
		if (func()) {
			return true;
		}
		else if (obj_init_arr()) {
			if (obj_list_arr()) {
				return true;
			}
		}
		return false;
	}

	bool class_rep() {
		if (class_st()) {
			if (class_rep()) {
				return true;
			}
		}
		else if (t->getClassPart() == "}") {
			return true;
		}
		return false;
	}

	/*<S>  namespace ID { <class_rep> } */
	bool S() {
		if (t->getClassPart() == "namespace") {
			t->next();
			if (t->getClassPart() == "ID") {
				t->next();
				if (t->getClassPart() == "{") {
					t->next();
					if (class_rep()) {
						if (t->getClassPart() == "}") {
							t->next();
							return true;
						}
					}
				}
			}
		}
		return false;
	}
};

