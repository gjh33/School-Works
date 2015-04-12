#include "flowers.h"
#include <math.h>
#define M_PI 3.14159265358979323846	//aperantly M_PI doesn't work with math.h

ContinuedFraction fractionalPart(ContinuedFraction &f) {
    ContinuedFraction tmp;// return variable
    if(f.fixedPart.empty() && f.periodicPart.empty()){//edge case: both parts empty
        return tmp;//prematurely return the empty CF
    }
    else if (!f.fixedPart.empty()){//if there's a fixed part it's as simple as setting first element to 0
        tmp.fixedPart = f.fixedPart;
        tmp.fixedPart[0] = 0;
        tmp.periodicPart = f.periodicPart;
    }
    else {//since the repeating part is... well repeating and we only want the first element to be 0, I create a fixed part using pop_back and then i rotate the periodic part to match
        tmp.fixedPart = f.fixedPart;
        tmp.fixedPart.push_back(0);
        tmp.periodicPart = f.periodicPart;
        int tmpStore = tmp.periodicPart[0];//used to store the first element so i can rotate. I.e. abc -> bca -> cab -> abc.
        tmp.periodicPart.erase(tmp.periodicPart.begin());//I rotate because adding the fixed part, periodic will print after. I.e. abc -> 0abc where 0 is the added fixed part
        tmp.periodicPart.push_back(tmpStore);//continin above explanation, i dont wasn 0abc i want 0bc because 0 should replace a. So i rotate the fixed part to get 0bcabcabcabc...
    }
    return tmp;
}

unsigned int spitEulerSquare(unsigned int index) {
    if(index == 0) return 7;//first index is 7
	if(index % 5 == 1) return (index / 5 * 3) + 2;//if it's mod 1
	if(index % 5 == 4) return (index / 5 + 1) * 3;//mod 4
	if(index % 5 == 0 && index != 0) return ((index / 5 - 1)* 12) + 18;//mod 0 but NOT first index
	return 1;//anything else
}

Fraction getApproximation(ContinuedFraction &fr, unsigned int n){//this algorithm starts from the end and loops back, almost mimicking recursion.
    Fraction toRet;//in this solution toRet keeps track of our current x value for our subCF until we get back to the head of fr, in which time it will be x for fr
    int loop = n;
    int myMod = fr.periodicPart.size();
    for(loop=n; loop>0; loop--){
        if(loop==n){//if there is no x' to the right, just return head of our smallest sub CF
            if(loop > fr.fixedPart.size() && !fr.periodicPart.empty()){//if it's in the periodic partn and it's not empty
                toRet.numerator = fr.periodicPart[(loop - fr.fixedPart.size() - 1)%myMod];//-1 because it's an index. Then mod it by the size of periodic size
            }
            else if(loop > fr.fixedPart.size() && fr.periodicPart.empty()){//if periodic part is empty, just reduce n down to fixed size.
                loop = fr.fixedPart.size();
                toRet.numerator = fr.fixedPart[loop-1];
            }
            else{//fixed part
                toRet.numerator = fr.fixedPart[loop-1];//if n is within the fixed portion simply return n-1 index
            }
            toRet.denominator=1;//set denom to 1 because returning whole number
        }
        else{
            //toRet is currently x'
            Fraction xPrime;
            xPrime.numerator = toRet.denominator;//toRet is x' and we want head+1/x' to be in the form head + ''x so ''x  = 1/'x. thus we flip num and denom
            xPrime.denominator = toRet.numerator;
            if(xPrime.denominator < 0){//if denominator is negative, i want my numerator to be instead because i add the numerator.
                xPrime.denominator = 0 - xPrime.denominator;
                xPrime.numerator = 0 - xPrime.numerator;
            }
            //set the numerator of toRet to be head of our sub CF. The head is the index we are currently at.
            //we are now going to make toRet = x, that's why we stored 'x earlier.
            //by setting the numerator we will multiply it later for fraction addition
            if(loop > fr.fixedPart.size()){//if we are in the periodic part
                toRet.numerator = fr.periodicPart[(loop - fr.fixedPart.size() - 1)%myMod];//-1 because it's an index. Then mod it by the size of periodic size
            }
            else{//fixed part
                toRet.numerator = fr.fixedPart[loop-1];//if n is within the fixed portion simply return n-1 index
            }
            toRet.denominator = xPrime.denominator; //to add fractions denom must be the same, since head will always be head/1, we can just set 1 to be 'x denom and then multiply head later.
            toRet.numerator = toRet.numerator * xPrime.denominator;//setting the numerator to match our change of denominator above.
            toRet.numerator = toRet.numerator + xPrime.numerator;//add the two numerators.
        }
    }
    return toRet;
}


double getAngle(ContinuedFraction &theta, int k) {
    double toRet;//double to return
    ContinuedFraction fTheta = fractionalPart(theta);//fraction part of theta
    Fraction aproxFTheta = getApproximation(fTheta, 7);//aproximation
    aproxFTheta.numerator = (aproxFTheta.numerator * k);//multiplying
    //now we have to find the fractional component. Simply use mod right? well...
    if (aproxFTheta.numerator%aproxFTheta.denominator == 0){//special case of 3/3 or 6/3 we dont want it going to 0/3 when i use module later.
        aproxFTheta.numerator = aproxFTheta.denominator;
    }
    else{
        aproxFTheta.numerator = aproxFTheta.numerator%aproxFTheta.denominator;//but this works. 5/3 -> 2/3 8/7 -> 1/7 etc...
    }
    toRet = ((double)aproxFTheta.numerator/(double)aproxFTheta.denominator) * 2 * M_PI;//and finishing it off by getting our double and multiplying by 2 pi
    return toRet;
}

Seed getSeed(ContinuedFraction &theta, int k) {//this function is pretty self explanatory
    double angle = getAngle(theta, k);
    Seed toRet;
    toRet.x = sqrt((double)k/M_PI) * cos(angle);
    toRet.y = sqrt((double)k/M_PI) * sin(angle);
    return toRet;
}

void pushSeed(std::list<Seed> &flower, ContinuedFraction &theta) {
    flower.push_back(getSeed(theta, flower.size()));
}

int spitNextMagicBox(MagicBox &box) {//I apolagize for the control flow of this question, i was having trouble understanding what to do mathematically, so the code reflects that confusion...
    int toRet;
    int i,j,k,l;//temporary values for reassigning of box.i/j/k/l
    //integer division test is in the body, to make sure any divide by 0s dont happen.
    if (box.k == 0 && box.l == 0){//initial tests to avoid all the code below in a simple scenario
        return -1;//the error code so to speak
    }
    if ((box.k != 0) && (box.l != 0))//if both are non zero
            {
                 if (box.i/box.k == box.j/box.l){//if we have a q to return, break and return below.
                    i = box.i;
                    j = box.j;
                    k = box.k;
                    l = box.l;
                    //do math
                    toRet = i/k;
                    box.i = k;
                    box.k = i - (k*toRet);
                    box.j = l;
                    box.l = j - (l*toRet);
                    box.indexInBoxedFraction++;//here we have to increase the index
                    return toRet;
                }
            }
    while(box.k != 0 || box.l != 0){//while both aren't 0
            //the following are nestive because idk if c++ does exaustive conditions. I want to avoid it getting hung on #/0 operation
            if ((box.k != 0) && (box.l != 0))//if both are non zero
            {
                 if (box.i/box.k == box.j/box.l){//if we have a q to return, break and return below.
                    break;
                }
            }//otherwise we continue
            //store temp values
            i = box.i;
            j = box.j;
            k = box.k;
            l = box.l;
            int p;
            if (box.indexInBoxedFraction < box.boxedFraction.fixedPart.size()){//if we're in the fixed portion
                p = box.boxedFraction.fixedPart[box.indexInBoxedFraction];//extract p
            }
            else if ((box.indexInBoxedFraction >= box.boxedFraction.fixedPart.size())&&(box.boxedFraction.periodicPart.empty())){//if we hit the end of x
                box.i = j;
                box.k = l;
                break;
            }
            else{//otherwise we have a periodic fraction and we need to see what index of periodic part, p will be
                int ind;
                ind = (box.indexInBoxedFraction - box.boxedFraction.fixedPart.size())%box.boxedFraction.periodicPart.size();//do that using modulus
                p = box.boxedFraction.periodicPart[ind];//extract p
            }
            //do our modification
            box.i = j;
            box.k = l;
            box.j = i + (j*p);
            box.l = k + (l*p);
            //increase index
            box.indexInBoxedFraction++;
    }
    if (box.k == 0 && box.l == 0){//check for EOF (end of fraction)
        return -1;//the error code so to speak
    }
    i = box.i;
    j = box.j;
    k = box.k;
    l = box.l;
    //do math
    toRet = i/k;
    box.i = k;
    box.k = i - (k*toRet);
    box.j = l;
    box.l = j - (l*toRet);
    //we dont have to increase the index here because it was increased in the loop above
    //box.indexInBoxedFraction++;
    return toRet;
}

ContinuedFraction getCFUsingMB(ContinuedFraction &f, int a, int b, int length) {
    //initialize values
    MagicBox tmp;
    ContinuedFraction toRet;
    tmp.i = a;
    tmp.j = b;
    tmp.k = 1;
    tmp.l = 0;
    tmp.boxedFraction = f;
    tmp.indexInBoxedFraction = 0;
    while(toRet.fixedPart.size() <= length){//while we are less than length requested
        int tmpRes = spitNextMagicBox(tmp);//find out the next int
        if (tmpRes == -1){//if it's the error code -1, we done here fool
            break;
        }
        else{//otherwise slap that bitch onto the end XD
            toRet.fixedPart.push_back(tmpRes);
        }
    }
    return toRet;//we done boys and girls, it's over. WOOT!
}
