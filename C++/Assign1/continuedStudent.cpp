#include "continued.h"
#include <iostream>

ContinuedFraction *copyCF(ContinuedFraction*);//Used in getCF for periodic CF. Recursively creates a duplicate of a continued fraction so it can be modified without the original being changed

unsigned int gcd(unsigned int a, unsigned int b) {
	if (b%a == 0) {
		return a;//base case just returns a, we are done.
	}
	else {
		return gcd((b%a),a);//b%a is the same as remainder of b/a so this follows euclid's alg
	}
}
unsigned int gcdFaster(unsigned int a, unsigned int b){
    if(a == 1 || b == 1){//base case 1, you will always reach 1 at the least, as 1 is the smallest divisor
        return 1;//you will never reach 0 because the only subtraction requires a>b or b<a therefore it cannnot be 0
    }
    else if(a==b){//this base case avoids the subtration below creating a 0. If a == b then obviously they are their own common divisor
        return a;
    }
    else if(a%2==0 && b%2==0){// case a and b are even (2m)
        return 2*(gcdFaster((a/2),(b/2)));// follow formula for evens gcd(2m,2m)
    }
    else if(a%2==1 && b%2 == 0){//a is odd, (2m+1)
        return gcdFaster((b/2),a);// follow formula for gcd(2m+1,2n)
    }
    else if (a%2==0 && b%2==1){//b is odd
        return gcdFaster((a/2),b);// reverse of previous formula via concept of gcd(a,b) = gcd(b,a)
    }
    // remaining case is both are odd
    //when subtracting we have to make sure the smaller is subtracted from the larger, so there are two cases to reflect this depending on a>b or b>a
    else if (a > b){
        return gcdFaster((((a-1)/2)-((b-1)/2)),b);//case for 2 odd gcd(2a+1,2b+1)
    }
    else if (a < b){
        return gcdFaster((((b-1)/2)-((a-1)/2)), a);//same as above except b and a are reveres because b is larger
    }// this concludes all possible cases
}

ContinuedFraction *getCFlargerThanOne(unsigned int b, unsigned int a) {// returns a pointer to a CF, receives int b for numerator and a for denominator
    ContinuedFraction *toRet = new ContinuedFraction;//create a new continued fraction in memory and assign it's pointer value to a return variable
    if(b%a == 0){//base case: if they divide fine, then you've reached the end of the CF
        toRet->head = b/a;//therefore the head will be the nicely divided whole number of b/a
        toRet->tail = nullptr;//tail is a null pointer to signal the end of the CF
    }
    else{//any other case
        toRet->head = (b/a);//head is the integer of b/a (how many times you can fit a into b before going over)
        toRet->tail = getCFlargerThanOne(a, b%a);//the tail is a continued fraction, with the numerator as a, and the denominator as the remainder of b/a. recurse until base case
    }
    return toRet;//self explanatory...
}

ContinuedFraction *getCF(unsigned int b, unsigned int a) {// same as previous function
    if (b>a){//case of numerator bigger than denominator
        return getCFlargerThanOne(b,a);//use previously defined function
    }
    else{// new case of less than 1
        ContinuedFraction *toRet = new ContinuedFraction;//create new CF in memory and add it's pointer to return variable
        toRet->head = 0;//set the head to 0 because fractions less than 1 b/a = 0 + 1/a/b
        toRet->tail = getCF(a,b);//get the cf for a/b and recurse until base case
        return toRet;//also very self explanatory, this will now be the joke comments line
    }
}

ContinuedFraction *getCF(unsigned int head, ContinuedFraction *fixed, ContinuedFraction *period) {//returns CF, takes in as head, pointer to the fixed portion as a CF, pointer to repeating as CF
    ContinuedFraction *newFixed = copyCF(fixed);//a duplicate of fixed to be modified for return - see top of file to read copyCF
    ContinuedFraction *newPeriod = copyCF(period);// duplicate of period, you can see the actual code at the bottom of the file
    //
    ContinuedFraction *tailOf = newPeriod;//a value starting at the first CF that will become the last CF
    while (tailOf->tail != nullptr){//tail becomes it's current tail until you reach the last CF with a nullptr
        tailOf = tailOf->tail;
    }
    tailOf->tail = newPeriod;//the pointer of the last CF in period now points to the first
    //
    tailOf = newFixed;//reseting tailOf for use with fixed
    while (tailOf->tail != nullptr){//same as above
        tailOf = tailOf->tail;
    }
    tailOf->tail = newPeriod;//attaches the last CF in fixed to the start of period
    ContinuedFraction *toRet = new ContinuedFraction;//the CF to be returned
    toRet->head = head;//head is the same int as the head argument
    toRet->tail = newFixed;//tail links to your fixed duplicate which is now linked to the period duplicate which repeats
    return toRet;//return your new CF that is independent from the original
}


Fraction getApproximation(ContinuedFraction *fr, unsigned int n) {//returns a fraction, receives pointer to CF and int as a limit
    Fraction toRet = *(new Fraction);//creates a new fraction to return, toRet is the value not a pointer
    Fraction recursedRet = *(new Fraction);//'x in head+1/'x -- it is found by recursion, thus the name
    Fraction toAdd1 = *(new Fraction); // used for toAdd1 + toAdd2 where toAdd2 is 1/'x and toadd1 is the current head of fr over 1
    Fraction toAdd2 = *(new Fraction);
    if (n==1){//if we are simply at a single number, then return that number in fraction form head/1
        toRet.numerator = fr->head;
        toRet.denominator = 1;
    }
    else{
        recursedRet = getApproximation(fr->tail, n-1);//recurse to find 'x in x=head+1/'x
        toAdd2.numerator = recursedRet.denominator;//since it's head+1/'x we reverse num and denom so it's in the form head+''x
        toAdd2.denominator = recursedRet.numerator;//assigning the denom of toAdd2, toAdd2= 1/'x
        toAdd1.numerator = ((fr->head)*(toAdd2.denominator));//change of numerator for addition of fractions. Since denom is always 1, just multiply the top and bottom by denominator of toAdd2
        toAdd1.denominator = toAdd2.denominator;//setting the denominator for addition
        toRet.numerator = toAdd1.numerator + toAdd2.numerator;//add the numerators with the same denominator we have now added head+1/'x
        toRet.denominator = toAdd2.denominator;//they have the same denominator so just set manually
    }
    return toRet;//Chuck norris kills two stones with one bird
}
//===================USED IN GET CF FOR PERIODIC CF====================================
ContinuedFraction *copyCF(ContinuedFraction *cf){
    ContinuedFraction *tmp = new ContinuedFraction;//create a brand new fraction to copy
    tmp->head = cf->head;//head has the same value as current CF
    if((cf->tail) == nullptr){//if the tail is nullptr it should bloody well stay nullptr
        tmp->tail = nullptr;
    }
    else{
        tmp->tail = copyCF(cf->tail);//otherwise the tail is the copy of the tail fraction of cf, this recursion will duplicate the whole thing through
    }
    return tmp;//what's red and green and goes 100mph? A frog in a blender.
}
