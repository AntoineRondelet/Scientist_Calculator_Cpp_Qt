#ifndef ADD_H
#define ADD_H

#include "binaryoperator.h"


class Add: public BinaryOperator {
public:
    Add(): BinaryOperator(){}
    Litterale* execute(Litterale** litterals) const override;
};


#endif // ADD_H
