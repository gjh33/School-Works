type 'a church = ('a->'a) * 'a -> 'a;
val test:'a church = fn (f:('a -> 'a), x:'a) => f(f(f(x)));

fun create (n:int):'a church =
    let
	fun applyntimes (k:int, h:('a -> 'a), x: 'a):'a =
	    case k of
		0 =>  x
	       |p => h(applyntimes(k-1, h, x));
    in
	fn (f:('a -> 'a), x:'a) => applyntimes(n, f, x)
    end;

fun churchToInt (c:int church):int = c ((fn x:int => x+1), 0:int);

fun succ (c:'a church):'a church = (fn (f, x) => f(c(f,x)));
