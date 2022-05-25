#ifndef COMBINERS_H
#define COMBINERS_H

#include "searcheng.h"

/*** Define Derived WebPageSetCombiners (for AND, OR, DIFF) classes below ***/
class AndWebPageSetCombiner: public WebPageSetCombiner{
public:
    
    ~AndWebPageSetCombiner(); //destructor
    
    /**
     * Combines two sets of webpages into a resulting set based on some strategy
     *
     * @param[in] setA
     *   first set of webpages
     * @param[in] setB
     *   second set of webpages
     * @return set of webpages that results from the combination strategy
     */
    WebPageSet combine(const WebPageSet& setA, const WebPageSet& setB);
};


class OrWebPageSetCombiner: public WebPageSetCombiner{
public:
    
    ~OrWebPageSetCombiner(); //destructor

    WebPageSet combine(const WebPageSet& setA, const WebPageSet& setB);
};

//DIFFCombiner class to find whats not in evething in setA not in setB
class DiffWebPageSetCombiner: public WebPageSetCombiner{

public:
    
    ~DiffWebPageSetCombiner(); //destructor

    WebPageSet combine(const WebPageSet& setA, const WebPageSet& setB);
};



#endif
