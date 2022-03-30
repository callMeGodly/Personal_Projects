#include "searcheng.h"
#include "combiners.h"

using namespace std;

AndWebPageSetCombiner::~AndWebPageSetCombiner(){
    
}

WebPageSet AndWebPageSetCombiner::combine(const WebPageSet& setA, const WebPageSet&setB){
    
    //initiates the retval and iterators to go through the arguments.
    WebPageSet retval;
    WebPageSet::iterator it;
    WebPageSet::iterator itr;
    for(it = setA.begin(); it != setA.end(); ++it){
        itr = setB.find(*it);
        
        //if in setB then we can add to our retval
        if(itr != setB.end()) retval.insert(*it);
    }
    
    return retval;
}

OrWebPageSetCombiner::~OrWebPageSetCombiner(){
    
}

WebPageSet OrWebPageSetCombiner::combine(const WebPageSet& setA, const WebPageSet&setB){

    //initiates the retval and iterators to go through the arguments.
    WebPageSet retval;
    WebPageSet::iterator it;
    WebPageSet::iterator itr;

    //the two for loops just combines everything in setA and setB into one WebPageSet
    //Doesn't need to check for duplicates because we are using a set
    for(it = setA.begin(); it != setA.end(); ++it){
        retval.insert(*it);
    }
    for(itr = setB.begin(); itr != setB.end(); ++itr){
        retval.insert(*itr);
    }

    return retval;
}

DiffWebPageSetCombiner::~DiffWebPageSetCombiner(){
    
}

WebPageSet DiffWebPageSetCombiner::combine(const WebPageSet& setA, const WebPageSet&setB){

    //initiates the retval and iterators to go through the arguments.
    WebPageSet retval;
    WebPageSet::iterator it;
    WebPageSet::iterator itr;

    for(it = setA.begin(); it != setA.end(); ++it){
        itr = setB.find(*it);

        //if not in setB then we can add to our retval
        if(itr == setB.end()) retval.insert(*it);
    }

    return retval;
}




