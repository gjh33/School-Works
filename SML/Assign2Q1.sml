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
