fun classSum (f:(real -> real), a:real, b:real, inc:(real -> real)):real = (*as seen in class, general sum*)
    if (a > b) then 0.0
    else (f a) + classSum (f, inc(a), b, inc);
fun integrateFormula (f:(real -> real), g:(real -> real), dy:real) = fn x:real => (dy * classSum (fn y:real => (f(y)*g(x+y)), dy/2.0, x, (fn k:real => (k+dy))));
(*similar to integral seen in class, it takes the functions f, g, dy and returns a function that when given x will aproximate the equation build from f and g, and aproximate with dy*)
