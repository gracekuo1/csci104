#include "searcheng.h"
#include "combiners.h"

// Complete the necessary code
AndWebPageSetCombiner::AndWebPageSetCombiner(){
    
}

WebPageSet AndWebPageSetCombiner::combine(const WebPageSet& setA, const WebPageSet& setB)
{
    WebPageSet answer;
    for(WebPageSet::iterator it=setA.begin(); it != setA.end(); ++it){
        if (*setB.find(*it) != *setB.end())
            answer.insert(*it);
    }
    return answer;
}

OrWebPageSetCombiner::OrWebPageSetCombiner(){
    
}

WebPageSet OrWebPageSetCombiner::combine(const WebPageSet& setA, const WebPageSet& setB)
{
    WebPageSet answer;
    for(WebPageSet::iterator it=setA.begin(); it != setA.end(); ++it){
        answer.insert(*it);
    }
    for(WebPageSet::iterator jt=setB.begin(); jt != setB.end(); ++jt){
        if (!(*setA.find(*jt) != *setA.end()))
            answer.insert(*jt);
    }
    return answer;
}

DiffWebPageSetCombiner::DiffWebPageSetCombiner(){
    
}

WebPageSet DiffWebPageSetCombiner::combine(const WebPageSet& setA, const WebPageSet& setB)
{
    WebPageSet answer;
    for(WebPageSet::iterator it=setA.begin(); it != setA.end(); ++it){
        if (*setB.find(*it) == *setB.end())
            answer.insert(*it);
    }
    return answer;
}