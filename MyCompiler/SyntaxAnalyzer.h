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
		if (MST()) {
			cout << "Okay All correct !" << endl;
		}
		else
		{
			cout << "Something's wrong here" << endl;
		}
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
							return true;
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
					if (OE()) {
						if (t->getClassPart() == ")") {
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
							return true;
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
		/*if (if_else()) {
			return true;
		}
		else if (while_st()) {
			return true;
		}
		else if (for_st()) {
			return true;
		}
		else*/ if (t->getClassPart() == "inc_dec") {
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
		/* if (try_st()) {
			return true;
		}*/
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
};

