#include "gardens.h"
#include <stack>
#include <iostream>
#include <math.h>

 /* 0-credit */
Fraction ContinuedFraction::getApproximation(unsigned int k) const {
    Fraction toRet; // will be returned

    // we go backwards from the end to the beginning to compute the approximation
    // z is the index that keeps track of the position reached - starts at n-1
    int z = k-1;

    //here i simulate a fixed CF based on the iterator. I iterate and store the first k values or until there's no more.
    vector<cf_int> fixedPart;
    int i=0;
    while (!hasNoMore() && i<k){
        fixedPart.push_back(next());
        i++;
    }

    // start with 1/0
    toRet.numerator = 1;
    toRet.denominator = 0;

    auto l = fixedPart.size(); // l is the length of the fixed part

    for (; z >= 0; z--) {
        // change the numerator and denominator
        auto tmp = toRet.numerator;
        toRet.numerator = fixedPart[z] * toRet.numerator + toRet.denominator;
        toRet.denominator = tmp;
    }
    return toRet;
}


RationalCF::RationalCF(Fraction f): PeriodicCF({},{}) {
    //assign a and b like assign 1
  	cf_int a = f.denominator;
	cf_int b = f.numerator;
	//loop through and pop stuff onto the end.
	while (b%a != 0){
        fixedPart.push_back(b/a);
        int tmpa = a, tmpb = b;
        b = tmpa;
        a = tmpb%tmpa;
	}
	fixedPart.push_back(b/a);//this is because the loop quits before assigning the last value
}

RationalCF::~RationalCF() {
    //TODO
}

/* QUESTION 3*/

cf_int PeriodicCF::next() const {
    int toRet;

    auto l = fixedPart.size(); // l is the length of the fixed part
    auto z = periodicPart.size();// z is the length of the periodic part

    //if we're in the periodic part, find it's modular equivalent in periodicPart
    if (*iteratorPosition >= l){
        int tmp = *iteratorPosition - l;
        *iteratorPosition = *iteratorPosition + 1;
        return periodicPart[tmp%z];
    }
    //fixed part
    else{
        unsigned int tmp = *iteratorPosition;
        *iteratorPosition = *iteratorPosition + 1;
        return fixedPart[tmp];
    }
}

bool PeriodicCF::hasNoMore() const {
    // if there's no periodic part and iterator reached the end, then return true
    if (periodicPart.size() == 0){
        if ((*iteratorPosition+1) > fixedPart.size()){
            return true;
        }
        else{
            return false;
        }
    }
    //otherwise if there's a period part, then you can't get off mr.bones's wild ride. (google the reference if you dont get the joke)
    else {
        return false;
    }
}

void PeriodicCF::resetIterator() const {
    //I thought it would be fun to write a very lengthy comment to the simplest part of this entire assignment
    //so i'm going to explain things very slowly and long windedly. First of all the variable iteratorPosition
    //which is an integer pointer is dereferenced using the asterix operator. From here the value that is stored
    //in the variable is retrieved and is set to the number zero by the euqals operator. The entire process completion
    //is indicated by the semi colon
    *iteratorPosition = 0;
}

PeriodicCF::~PeriodicCF() {
    //spoke too soon... this is also a very simple portion of the assignment. Maybe this is the simplest. Damn!
    delete iteratorPosition;
}



/* QUESTION 4*/

MagicBoxCF::MagicBoxCF(const ContinuedFraction *f, cf_int x, cf_int y): a{x}, b{y} {
    boxedFraction = f;//initializing boxed Fraction
    mbnums = new cf_int[4];//{i, j, k, l}
    resetIterator();//this sets i, j, k, l to base values and resets boxedFraction's iterator. See below
}

cf_int MagicBoxCF::next() const {
    //<sarcasm>
    //this code took me a lot of effort. I had to be very careful when copy pasting from last homework's solutions
    //that i didn't miss anything. I hope you apreciate the hard work put into it. OH AND DONT GET ME STARTED on
    //having to cntrl+r all the variables used from the previous homework. I mean really you guys are just asking too much
    //at this point.
    //</sarcasm>
    while( ((mbnums[2] == 0 || mbnums[3] == 0) && !(mbnums[2] == 0 && mbnums[3] == 0)) ||
            (mbnums[2] != 0 && mbnums[3] != 0 && mbnums[0] / mbnums[2] != mbnums[1] / mbnums[3]) ) {
		// while the indeces are not yet ready to spit q
		if(boxedFraction->hasNoMore()) {
            // no more integers to spit from cf
			mbnums[0] = mbnums[1];
			mbnums[2] = mbnums[3];
            continue;
		}
		//read p
        int p = boxedFraction->next();

		//change box accordingly
		int i = mbnums[1],
            j = mbnums[0] + mbnums[1] * p,
			k = mbnums[3],
			l = mbnums[2] + mbnums[3] * p;
		mbnums[0] = i;
		mbnums[1] = j;
		mbnums[2] = k;
		mbnums[3] = l;
    }
    // if we reached the end of the cf - return -1
	if(mbnums[2] == 0 && mbnums[3] == 0) return -1;

    // return q and change box accordingly
	int q = mbnums[0] / mbnums[2];
	int i = mbnums[2],
        j = mbnums[3],
		k = mbnums[0] - mbnums[2] * q,
		l = mbnums[1] - mbnums[3] * q;
	mbnums[0] = i;
	mbnums[1] = j;
	mbnums[2] = k;
	mbnums[3] = l;
	return q;
}

bool MagicBoxCF::hasNoMore() const {
    //by the definition given in previous hw
    if(mbnums[2] == 0 && mbnums[3] == 0){
        return true;
    }
    else{
        return false;
    }
}

void MagicBoxCF::resetIterator() const {
    //i mean... duh!
    boxedFraction->resetIterator();
    mbnums[0] = a;
    mbnums[1] = b;
    mbnums[2] = 1;
    mbnums[3] = 0;
}

MagicBoxCF::~MagicBoxCF() {
    //<sarcasm> oh the labour is too much... kill me now... </sarcasm>
    delete mbnums;
}



/* QUESTION 5*/

ostream &operator<<(ostream& outs, const ContinuedFraction &cf) {
    //first reset iterator
    cf.resetIterator();
    //the first few are special case so they are outside the main loop
    cout << "[" << cf.next() << ";";//special case of needing [ and ;
    cout << cf.next();//special case because it doesn't have a ","
    int i = 0;
    while (!cf.hasNoMore()){
        //10 was the limit hard coded into desiredOutput.txt
        if (i > 10){
            cout << "...";
            break;
        }
        //otherwise we're all good just print shit. This is EASY!!
        cout << "," << cf.next();
        i++;//dont forget to increment this bitc... uhhh i mean... thing (sorry too much breaking bad)
    }
    cout << "]";//oh my god comments are boring. *yawns*
    cf.resetIterator();//i mean... duh.
    return outs;//if this line were any simpler, programmers would be out of a job
}


/* QUESTION 6 */

Flower::Flower(const ContinuedFraction *f, unsigned int apxLengthParam): theta{f}, apx_length{apxLengthParam}{};

float Flower::getAngle(unsigned int k) const {
    //<sarcasm> so much copy paste, my fingers hurt from all the copy pasting... </sarcasm>
    // get approximation
    Fraction fr = theta->getApproximation(apx_length);
    //keep only fractional part
    fr.numerator = fr.numerator%fr.denominator;
    // compute fractional part of the rotations
    double fractpart = ((k*fr.numerator)%fr.denominator/(double)fr.denominator);
    //return
    return (2 * pie * fractpart);
}

Seed Flower::getSeed(unsigned int k) const {
    Seed s;
    // we follow the formulas in the assignment's document
    float angle = getAngle(k);
    s.x = sqrt(k / (pie * 1.0)) * cos(angle);
    s.y = sqrt(k / (pie * 1.0)) * sin(angle);
    return s;
}

vector<Seed> Flower::getSeeds(unsigned int k) const {
    int i;//loop tracker
    vector<Seed> toRet;//return vector
    //for k items push the next seed
    for (i=0; i<k; i++){
        toRet.push_back(getSeed(i));
    }
    return toRet;
}


Flower::~Flower() {
    //TODO: NOTHING BECAUSE I DIDN'T ALOCATE SHIT
}

/* QUESTION 7*/

void Flower::writeMVGPicture(ostream &out, unsigned int k, unsigned int scale_x, unsigned int scale_y) const {
    unsigned int Cx,Cy,Bx,By,curSeed;//curSeed keeps track of the current seed.
    curSeed = 0;
    //for first k seeds
    for (auto& s : getSeeds(k)){
        //apply equations in assign
        Cx = (scale_y/2.0) + (s.x * ((scale_y - 200.0)/2.0) * (sqrt(pie/(double)k)));
        Cy = (scale_x/2.0) + (s.y * ((scale_x - 200.0)/2.0) * (sqrt(pie/(double)k)));
        unsigned int tmp;
        //find min(W,H) - this was easier and more space efficient than including the entire algorithm.h header
        if (scale_x < scale_y){
            tmp = scale_x;
        }
        else{
            tmp = scale_y;
        }
        //apply more equations and use min(W,H)
        Bx = (double)Cx + ((sqrt((double)curSeed/(double)k)) * ((double)tmp/100.0));
        By = Cy;
        //print final statement
        out << "fill blue circle " << Cx << "," << Cy << " " << Bx << "," << By << endl;
        //increment curSeed
        curSeed++;
    }
}




