#include "TryIt.h"

TryIt::TryIt(unsigned int v)
{
Setval(v);
    //ctor
}

TryIt::~TryIt()
{
    //dtor
}

TryIt::TryIt(const TryIt& other)
{
    //copy ctor
}

TryIt& TryIt::operator=(const TryIt& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    const TryIt t=rhs;
    //assignment operator
    Setval(t.Getval());
    return *this;
}
