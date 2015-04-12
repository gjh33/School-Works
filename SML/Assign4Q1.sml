Control.Print.printDepth := 12;

datatype 'a rlist = Empty | RCons of 'a * (('a rlist) ref);

val myList:int rlist ref = ref(RCons(2, ref(RCons(5,ref(Empty)))));

(* made assuming for an ascending order list you'd use fn (x,y) => if x<=y then true else false *)

fun insert (f:('a * 'a -> bool), value:'a, lst:('a rlist) ref):unit =
    case !lst of
	Empty => lst := (RCons(value, ref(Empty)))
      | RCons(h, t) => if (f(value, h)) then lst:= RCons(value, ref(RCons(h,t))) else insert (f,value,t);
