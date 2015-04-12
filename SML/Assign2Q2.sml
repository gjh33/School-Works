fun newton(f:(real -> real), guess:real, eps:real):real =
    let
	fun converge (h:(real -> real), gue:real, ep:real, loop:int) =(*helper function that just has an added arguement to count the number of recursions and raise diverge*)
	    let
		fun derivAprox(f:(real->real), x:real, dx:real):real = ((f (x+dx))-(f (x-dx)))/(2.0*dx);(*derivative aproximation using 0.05 in actual code for dx*)
		val newGuess:real = gue - ((h gue)/(derivAprox(h, gue, 0.05)));(*the new guess being the equation given in the assignment*)
		exception Diverge;(*declaring exception*)
	    in
		if(loop > 0) then(*if it's been less than 1000 loops*)
		    if ((abs(h gue)) < ep) then gue else converge(h, newGuess, ep, loop-1)(*if it's close enough return it, else recurse*)
		else
		    raise Diverge(*my exception if it's gone more than 1000 loops*)
	    end;
    in
	converge(f,guess,eps,1000)(*putting it all together*)
    end;
