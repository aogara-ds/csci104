#ifndef COMBINERS_H
#define COMBINERS_H

#include "webpage.h"
#include "searcheng.h"

/*** Define Derived WebPageSetCombiners (for AND, OR, DIFF) classes below ***/

class AndWebPageSetCombiner : public WebPageSetCombiner
{
    public:
        AndWebPageSetCombiner();
        ~AndWebPageSetCombiner();
        WebPageSet combine(const WebPageSet& setA, const WebPageSet& setB);
};

class OrWebPageSetCombiner : public WebPageSetCombiner
{
    public:
        OrWebPageSetCombiner();
        ~OrWebPageSetCombiner();
        WebPageSet combine(const WebPageSet& setA, const WebPageSet& setB);
};

class DiffWebPageSetCombiner : public WebPageSetCombiner
{
    public:
        DiffWebPageSetCombiner();
        ~DiffWebPageSetCombiner();
        WebPageSet combine(const WebPageSet& setA, const WebPageSet& setB);
};

#endif