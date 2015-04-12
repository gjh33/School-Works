datatype 'a tree = Empty | Node of (int * 'a) * 'a tree * 'a tree;

val testTree:string tree = Node((5,"h"),Node((3,"c"),Node((1,"p"),Empty,Empty),Node((4,"k"),Empty,Empty)),Node((8,"k"),Empty,Node((9,"h"),Empty,Empty)));


exception Found of (int * string) list;

fun collect (p:(int -> bool), t:string tree):(int * string) list =
    (case t of
	Empty => []
      | Node(a,l,r) => (if (p(#1 a) = true) then raise Found (a::[]) else raise Found []) handle Found x => collect(p, l) @ x @ collect(p, r));

fun gather (p:(int -> bool), T:string tree, cont:((int * string) list -> (int * string) list)):(int * string) list =
    case T of
	Empty => cont([])
      | Node(d, L, R) => if (p(#1 d) = true)
			 then gather (p, L, (fn x => x @ (d::[]) @ gather(p, R, cont)))
			 else gather (p, L, (fn x => x @ gather(p, R, cont)));
