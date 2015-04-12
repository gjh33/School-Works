datatype 'a instr = Put of 'a | Get | Restore;

fun makeCell (v:'a) =
    let
	val stack = ref (v::[]);
	exception Error;
    in
	fn (instruction:'a instr) =>
	   case instruction of
	       Put(i) => ((stack := i::(!stack)); i)
	     | Get => (let
			  val x::xs = !stack;
		      in
			  x
		      end)
	     | Restore => (case !stack of
			       [] => raise Error
			     | x::[] => raise Error
			     | x::y::xs => ((stack := y::xs); y))
    end;
