(*used to build a list for foldl, an input of 4 gives 0,1,2,3 and input of 0 gives []*)
fun upToNExclusive(n:int):int list =
    case n of
	0 => []
      | n => upToNExclusive(n-1)@(n-1::[]);

(*Catalan function*)
fun Catalan(n:int):int =
    case n of
	0 => 1
      | n:int => foldl (fn (x,y) => round((real(4*x + 2)/real(x + 2)) * real(y))) 1 (upToNExclusive(n));

(*PART 2*)
datatype realSeq = Cons of real * (unit -> realSeq);

(*this is pretty much right out of the lecture slides*)
fun helperStream(n:int):realSeq =
    let
	val num = real(2*(2*n + 1))/real(n+2)
    in
	Cons(num, fn()=> helperStream(n+1))
    end;

(*woah this one is a bit trick. Ok so i start by defining a helperStream at 0. Now the first value of the catalan is the base case of 0*)
(*so i use that. a is the previous catalan number, and s is the current helperstream*)
(*in the normal case, we first split up the helper stream to get the coefficient AND the next stream. We then evaluate s to get that next stream*)
(*from here it's what you expect, (catalan(n), nextstream)*)
val CatStream =
    let
	val helpStream = helperStream(0);
	fun cat (a:real, n:int, s:realSeq):realSeq =
	    case (a, n, s) of
		(a, 0, s) => Cons(1.0, (fn () => cat (1.0, 1, s)))
	      | (a, n, s) => (let
				      val Cons(x, p) = s
				      val s2 = p()
				  in
				      Cons(x*a, (fn () => cat (x*a, n+1, s2)))
				  end);
    in
	cat (0.0, 0, helpStream)
    end;
