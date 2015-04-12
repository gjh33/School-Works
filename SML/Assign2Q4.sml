Control.Print.printDepth := 100;
datatype Mathexp =(*data type*)
	 Num of int
	 | Var of string
	 | Neg of Mathexp
	 | Add of Mathexp * Mathexp
	 | Mul of Mathexp * Mathexp;
fun diff(ME:Mathexp, v:string):Mathexp =(*all the cases of derivative broken into recursive segments*)
    case ME of
	Num(x) => Num(0)
      | Var(x) => if x = v then Num(1) else Num(0)
      | Neg(x) => Neg(diff(x, v))
      | Add(x, y) => Add(diff(x, v), diff(y, v))
      | Mul(x, y) => Add(Mul(x,diff(y, v)), Mul(diff(x, v), y));
fun simplify(ME:Mathexp):Mathexp =(*this was tricky because simplifying could create another case where you need tosimplify i.e. 3 + (0*3) will return 3+0 because it hadn't evaluated the second part yet*)
    let
	fun isSimplified(MathE:Mathexp):bool =(*my solution was a helper function to test if a ME is simplified*)
	    case MathE of(*i go through all the cases to check if a ME is simplified*)
		Add(e,Num(0)) => false
	      | Add(Num(0),e) => false
	      | Mul(e,Num(1)) => false
	      | Mul(Num(1),e) => false
	      | Mul(e,Num(0)) => false
	      | Mul(Num(0),e) => false
	      | Num(x) => true
	      | Var(x) => true
	      | Add(x,y) => (isSimplified(x) andalso isSimplified(y))
	      | Mul(x,y) => (isSimplified(x) andalso isSimplified(y))
	      | Neg(x) => isSimplified x;
	fun simplifyHELPER(ME:Mathexp):Mathexp =(*this was my original simplify function which i made into a helper so i could use it in the value below*)
	    case ME of
		Add(e,Num(0)) => simplifyHELPER(e)
	      | Add(Num(0),e) => simplifyHELPER(e)
	      | Mul(e,Num(1)) => simplifyHELPER(e)
	      | Mul(Num(1),e) => simplifyHELPER(e)
	      | Mul(e,Num(0)) => Num(0)
	      | Mul(Num(0),e) => Num(0)
	      | Num(x) => Num(x)
	      | Var(x) => Var(x)
	      | Add(x,y) => Add(simplifyHELPER(x),simplifyHELPER(y))
	      | Mul(x,y) => Mul(simplifyHELPER(x),simplifyHELPER(y))
	      | Neg(x) => simplifyHELPER(x);
	val simplified = simplifyHELPER(ME);(*here i use the helper to get the simplified ME for testing in the later statement*)
    in
	if (isSimplified(simplified)) then simplified else simplify(simplified)(*here i test if the result was simplified, if not simply do it again*)
    end;

