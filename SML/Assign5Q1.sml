datatype exp = Nat of int | Bool of bool |Plus of exp * exp |
	       Mult of exp * exp | If of exp * exp * exp |
	       And of exp * exp | Not of exp | Eq of exp * exp |
	       Var of string | Let of exp * (string * exp) |
	       Fun of string * string * exp |
	       Apply of exp * exp;

fun remDuplicates(lst:''a list):''a list =
    let
	fun removeInstances(tmplst:''a list, value:''a):''a list =(*a function that removes all instances of "value"*)
	    case tmplst of
		[] => []
	      | x::xs => if x = value then removeInstances(xs, value) else x::(removeInstances (xs, value))(*uses recursion if x = value we get rid of it and then recurse to the rest of list*)
    in
	case lst of
	    [] => []
	  | x::xs => x::(remDuplicates(removeInstances(xs, x)))(*remove the first element x from the rest of the list, then recurse, this removes any duplicates while keeping the original*)
    end;

fun removeInstances(tmplst:''a list, value:''a):''a list =(*a function that removes all instances of "value"*)
    case tmplst of
	[] => []
      | x::xs => if x = value then removeInstances(xs, value) else x::(removeInstances (xs, value))(*uses recursion if x = value we get rid of it and then recurse to the rest of list*);

fun freelist(E:exp):string list =
    let
	fun h(ex:exp):string list =
	    case ex of
		Nat(n) => []
	       |Bool(n) => []
	       | Plus(e1,e2) => h(e1)@h(e2)
	       | Mult(e1,e2) => h(e1)@h(e2)
	       | If(e1,e2,e3) => h(e1)@h(e2)@h(e3)
	       | And(e1,e2) => h(e1)@h(e2)
	       | Not(e) => h(e)
	       | Eq(e1,e2) => h(e1)@h(e2)
	       | Var(s) => s::[]
	       | Let(e1,(s,e2)) => removeInstances(h(e1)@h(e2), s)
	       | Fun(s1,s2,e1) => removeInstances(removeInstances(h(e1), s2), s1)
	       | Apply(e1,e2) => h(e1)@h(e2)
    in
	remDuplicates(h(E))
    end;
