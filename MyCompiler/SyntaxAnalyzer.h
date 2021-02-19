#pragma once
#include "LinkedList.h"
class SyntaxAnalyzer
{
	LinkedList* t;
	SyntaxAnalyzer(LinkedList* tokens)
	{
		this->t = tokens;
	}

	bool dec(){
		if (t->getClassPart == "DT") {
			t->next();
			if (dec_choice()) {
				return true;
			}
		}
		return false;
	}

	bool dec_choice(){
		if (t->getClassPart == "[") {
			t->next();
			if (t->getClassPart == "]") {
				t->next();
				if (t->getClassPart == "ID") {
					t->next();
					if (init_arr()) {
						if (list_arr()) {
							return true;
						}
					}
				}
			}

		}
		else if (t->getClassPart == "ID") {
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

	}
	bool list() {

	}
	bool init_arr() {

	}
	bool list_arr() {

	}

	bool this_st() {
		if (t->getClassPart == "this") {
			t->next();
			if (t->getClassPart == ".") {
				return true;
			}
		}
		else if(t->getClassPart == "ID"){
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
		if (t->getClassPart == "||") {
			t->next();
			if (AE()) {
				if (OE_()) {
					return true;
				}
			}
		}
		else if (t->getClassPart == ")" || t->getClassPart == "]" || t->getClassPart == ";" || t->getClassPart == "," || t->getClassPart == "}") {
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
		if (t->getClassPart == "&&") {
			t->next();
			if (RE()) {
				if (AE_()) {
					return true;
				}
			}
		}
		else if ( t->getClassPart == "||" ||
			t->getClassPart == ")" || t->getClassPart == "]" || t->getClassPart == ";" || t->getClassPart == "," || t->getClassPart == "}") {
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
		if (t->getClassPart == "rop") {
			t->next();
			if (PE()) {
				if (RE_()) {
					return true;
				}
			}
		}
		else if ( t->getClassPart == "&&" || t->getClassPart == "||" ||
			t->getClassPart == ")" || t->getClassPart == "]" || t->getClassPart == ";" || t->getClassPart == "," || t->getClassPart == "}") {
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
		if (t->getClassPart == "pm") {
			t->next();
			if (ME()) {
				if (PE_()) {
					return true;
				}
			}
		}
		else if (t->getClassPart == "rop" || t->getClassPart == "&&" || t->getClassPart == "||" ||
			t->getClassPart == ")" || t->getClassPart == "]" || t->getClassPart == ";" || t->getClassPart == "," || t->getClassPart == "}") {
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
		if (t->getClassPart == "mdm") {
			t->next();
			if (F()) {
				if (ME_()) {
					return true;
				}
			}
		}
		else if (t->getClassPart == "pm" || t->getClassPart == "rop" || t->getClassPart == "&&" || t->getClassPart == "||" ||
			t->getClassPart == ")" || t->getClassPart == "]" || t->getClassPart == ";" || t->getClassPart == "," || t->getClassPart == "}") {
			return true;
		}
		return false;
	}
	
	bool F() {
		if (constant()) {
			return true;
		}
		else if (t->getClassPart == "(") {
			t->next();
			if (OE()) {
				if (t->getClassPart == ")") {
					t->next();
					return true;
				}
			}
		}
		else if (t->getClassPart == "!") {
			t->next();
			if (F()) {
				return true;
			}
		}
		else if (this_st()) {
			if (t->getClassPart == "ID") {
				t->next();
				if (XY()) {
					return true;
				}
			}
		}
		else if (t->getClassPart == "inc_dec") {
			t->next();
			if (this_st()) {
				if (t->getClassPart == "ID") {
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
		if (t->getClassPart == "[") {
			t->next();
			if (OE()) {
				if (t->getClassPart == "]") {
					t->next();
					if (XY1()) {
						return true;
					}
				}
			}
		}
		else if (t->getClassPart == "(") {
			t->next();
			if (PL()) {
				if (t->getClassPart == ")") {
					t->next();
					if (XY2()) {
						return true;
					}
				}
			}
		}
		else if (t->getClassPart == ".") {
			t->next();
			if (t->getClassPart == "ID") {
				t->next();
				if (XY()) {
					return true;
				}
			}
		}
		else if (t->getClassPart == "inc_dec") {

		}
		else if (t->getClassPart == "mdm" || t->getClassPart == "pm" || t->getClassPart == "rop" || t->getClassPart == "&&" || t->getClassPart == "||" ||
			t->getClassPart == ")" || t->getClassPart == "]" || t->getClassPart == ";" || t->getClassPart == "," || t->getClassPart == "}") {
			return true;
		}
		return false;
	}
	
	bool XY2() {
		if (t->getClassPart == ".") {
			t->next();
			if (t->getClassPart == "ID") {
				t->next();
				if (XY()) {
					return true;
				}
			}
		}
		else if (t->getClassPart == "mdm" || t->getClassPart == "pm" || t->getClassPart == "rop" || t->getClassPart == "&&" || t->getClassPart == "||" ||
			t->getClassPart == ")" || t->getClassPart == "]" || t->getClassPart == ";" || t->getClassPart == "," || t->getClassPart == "}") {
			return true;
		}
		return false;
	}
	
	bool XY1() {
		if (t->getClassPart == ".") {
			t->next();
			if (t->getClassPart == "ID") {
				t->next();
				if (XY()) {
					return true;
				}
			}
		}
		else if (t->getClassPart == "inc_dec") {
			t->next();
			return true;
		}
		else if (t->getClassPart == "mdm" || t->getClassPart == "pm" || t->getClassPart == "rop" || t->getClassPart == "&&" || t->getClassPart == "||" ||
			t->getClassPart == ")" || t->getClassPart == "]" || t->getClassPart == ";" || t->getClassPart == "," || t->getClassPart == "}") {
			return true;
		}
		return false;
	}
	
	bool constant() {
		if (t->getClassPart == "int" || t->getClassPart == "float" || t->getClassPart == "char" || t->getClassPart == "string"
			|| t->getClassPart == "true" || t->getClassPart == "false" || t->getClassPart == "bool" || t->getClassPart == "var") {
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
		return false;
	}

	bool PL1() {
		if (t->getClassPart == ",") {
			t->next();
			if (OE()) {
				if (PL1()) {
					return true;
				}
			}
		}
		else if (t->getClassPart == ")") {
			return true;
		}
		return false;
	}

	/*<X> --> [<OE>] <X1> | (<PL>).ID<X> | .ID<X> | ~
	<X1> --> .ID<X> | ~*/
	bool X() {

	}

};

