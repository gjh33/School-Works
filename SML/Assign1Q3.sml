fun incr (lst: int list, amt: int) :int list = (*increment function as seen in class*)
    case lst of
	[] => []
      | x :: xs => (x+amt) :: incr(xs, amt);
fun prefixSum(lst:int list):int list = (*slow function O(n^2)*)
    case lst of
	[] => []
      | x::xs => x::(incr(prefixSum(xs),x));(*adds x to all other numbers, after the other numbers have been computed for prefixSum*)
fun prefixSumFast(lst:int list):int list =
    let
	fun prefixSum2(lst1:int list, amount:int):int list =(*Increments the first element by a certain amount, then recurses*)
	    case lst1 of
		[] => []
	      | x::xs => (x+amount)::(prefixSum2(xs, (x+amount)))(*increments the first element by amount, and then recurses to increment the next element by the one before it which is x+amount*)
    in
	prefixSum2(lst, 0)(*by starting at 0 it computes as follows: #1+0; #2+#1; #3+#2 etc... This will give a prefix sum*)
    end;
