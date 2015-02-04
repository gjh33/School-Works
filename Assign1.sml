fun last_day(y:int, m:int, d:int):int =
    let
	(*isLeapYear recursively checks if the year is a multiple of 4 by hitting the base case of 0*)
	fun isLeapYear(year:int):bool =
	    if year=0 then true else if year<0 then false else isLeapYear(year-4);
	exception MonthOutOfRange;(*exception declared for if the month isn't 1-12*)
    in
	case m of (*i'm so sorry about this part, i wish i knew a better way of doing it...*)
	    1 => 31
	  | 2 => (case isLeapYear(y) of true => 29 
				      | false => 28)(*here's where i have a nested case for if it's a leap year*)
	  | 3 => 31
	  | 4 => 30
	  | 5 => 31
	  | 6 => 30
	  | 7 => 31
	  | 8 => 31
	  | 9 => 30
	  | 10 => 31
	  | 11 => 30
	  | 12 => 31
	  | _ => raise MonthOutOfRange (*here i call my exception for anything other than 1-12*)
    end;
fun valid_date(y:int, m:int, d:int):bool =
    (*I will consider a valid year to be positive, a valid month to is 1-12, and a valid day to be above 0 and no more than last_day*)
    if ((y>0) andalso (m>0) andalso (m<13) andalso (d>0) andalso (d<=last_day(y,m,d))) then true else false;
fun next_day(y:int, m:int, d:int):int*int*int = (*the flow of this function checks for if the day needs to carry over to the next month, then if the month has to carry over to next year, then returns the apropriate date*)
    if d>=last_day(y,m,d)(*here i opted to use >= incase someone enters an invalid date, it will return a valid date*)
    then
	if m=12(*there is no need for >= because last_day will trigger MonthOutOfRange error*)
	then (y+1,1,1)
	else (y, m+1, 1)
    else (y,m,d+1);
fun precedes((y1:int, m1:int, d1:int),(y2:int, m2:int, d2:int)):bool =
    if y1<y2
    then true
    else if y1>y2
    then false
    else
	if m1<m2
	then true
	else if m1>m2
	then false
	else
	    if d1<d2
	    then true
	    else false;
fun earliest(lst:(int*int*int) list):int*int*int=
    case lst of
	x::[] => x
      | x::xs => (if precedes(x,earliest(xs)) then x else earliest(xs))
      | _ =>  let exception EmptyListError in raise EmptyListError end;
