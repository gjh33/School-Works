fun zip(lst1:string list, lst2:int list):(string*int) list =
    case (lst1,lst2) of
	(x::xs,y::ys) => (x,y)::(zip(xs,ys)) (*splits the first elements from each list into a pair, and then adds that to the front of the zipped list created from the remaining to lists xs and ys*)
      | _ => [];(*base cases are all encompased by the default: (x::xs,[]) and ([],y::ys) and ([],[])*)
fun unzip(lst:(string*int) list):string list * int list =
    case lst of
	(x,y)::xs => (x::(#1 (unzip xs)), y::(#2 (unzip xs)))(* in essence this splits the pair at the head of the list then adds them to the head of the corresponding list resulted from unzipped the remaining xs*)
      | [] => ([],[]) (*base case*)
