#include "operator.h"

#include "add.h"
#include "mult.h"
#include "div.h"
#include "sous.h"
#include "operateurcomplexe.h"
#include "oplogique.h"
#include "ift.h"
#include "sto.h"
#include "swap.h"
#include "and.h"
#include "or.h"
#include "mod.h"
#include "diventiere.h"

#include "neg.h"
#include "num.h"
#include "den.h"
#include "drop.h"
#include "eval.h"
#include "dup.h"
#include "not.h"
#include "forget.h"
#include "re.h"
#include "im.h"

#include "undo.h"
#include "redo.h"
#include "operateurspecial.h"
#include "clear.h"





Operator* getOperateur(const string& str){ //Ici c'est une factory en quelque sorte

    //---------- Operateurs Binaires ----------- //
    if(str == "+") {
        return new Add;
    }
    else if(str == "*") {
        return new Mult;
    }
    else if(str == "/") {
        return new Div;
    }
    else if(str == "-") {
        return new Sous;
    }
    else if(str == "$") {
        return new  OperateurComplexe;
    }
    else if(str == "STO") {
        return new Sto;
    }
    else if(str == "=") {
        return new OpLogiqueEgal;
    }
    else if(str == "<") {
        return new OpLogiqueInf;
    }
    else if(str == "<=") {
        return new OpLogiqueInfEgal;
    }
    else if(str == ">") {
        return new OpLogiqueSup;
    }
    else if(str == ">=") {
        return new OpLogiqueSupEgal;
    }
    else if(str == "!=") {
        return new OpLogiqueDiffEgal;
    }
    else if(str == "IFT") {
        return new Ift;
    }
    else if(str == "SWAP") {
        return new Swap;
    }
    else if(str == "AND") {
        return new And;
    }
    else if(str == "OR") {
        return new Or;
    }
    else if(str == "DIV") {
        return new Diventiere;
    }
    else if(str == "MOD") {
        return new Mod;
    }



    //---------- Operateurs Unaires ----------- //
    else if(str == "NEG") {
        return new Neg;
    }
    else if(str == "NUM") {
        return new Num;
    }
    else if(str == "DEN") {
        return new Den;
    }
    else if(str == "DROP") {
        return new Drop;
    }
    else if(str == "EVAL") {
        return new Eval;
    }
    else if(str == "DUP") {
        return new Dup;
    }
    else if(str == "NOT") {
        return new Not;
    }
    else if(str == "FORGET") {
        return new Forget;
    }
    else if(str == "RE") {
        return new Re;
    }
    else if(str == "IM") {
        return new Im;
    }

    //---------- Operateurs "Speciaux" -----------//
    else if(str == "UNDO") {
        return new Undo;
    }
    else if(str == "REDO") {
        return new Redo;
    }
    else if(str == "CLEAR") {
        return new Clear;
    }

    //---------- Si on a pas reconnu un operateur ----------- //
    cout << "Operateur inconnu ! " << endl;
    return nullptr;
}
