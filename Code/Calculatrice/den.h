#ifndef DEN_H
#define DEN_H

#include "unaryoperator.h"

class Den: public UnaryOperator {
public:
    Den(): UnaryOperator(){}
    Litterale* execute(QVector<Litterale*> litterals) const override;
};


#endif // DEN_H
