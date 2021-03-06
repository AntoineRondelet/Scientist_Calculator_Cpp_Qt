#include "complexe.h"

#include "entier.h"
#include "calculatriceexception.h"
#include "reel.h"
#include "rationnel.h"
#include "litteralenum.h"



Complexe::Complexe(const LitteraleNombre& re, const LitteraleNombre& im) {
    const LitteraleNum* tmpRe = dynamic_cast<const LitteraleNum*>(&re);
    const LitteraleNum* tmpIm = dynamic_cast<const LitteraleNum*>(&im);
    if (tmpRe == 0 || tmpIm == 0) {
        CALCULATRICE_EXCEPTION("Construction du complexe impossible");
    } else {
        partEnt = tmpRe;
        partIm = tmpIm;
    }
}

QString Complexe::toString() const {
    return partEnt->toString() + "$" + partIm->toString();
}

Complexe* Complexe::clone() const {
    Litterale* tmpEnt = partEnt->clone();
    Litterale* tmpIm = partIm->clone();

    LitteraleNum* pEnt = dynamic_cast<LitteraleNum*>(tmpEnt);
    LitteraleNum* pIm = dynamic_cast<LitteraleNum*>(tmpIm);

    return new Complexe(*pEnt, *pIm);
}


LitteraleNombre& Complexe::addition(const LitteraleNombre& lit) const {
    //Complexe + Complexe = complexe
    const Complexe* ptComplexe = dynamic_cast<const Complexe*>(&lit);
    if (ptComplexe == nullptr) {
        const Entier* ptEntier = dynamic_cast<const Entier*>(&lit);
        // Complexe + int = complexe
        if (ptEntier == 0) {
            //Complexe + rationnel = complexe
            const Rationnel* ptRationnel = dynamic_cast<const Rationnel*>(&lit);
                if (ptRationnel == 0) {
                    //Complexe + reel = complexe
                    const Reel* ptReel = dynamic_cast<const Reel*>(&lit);
                        if (ptReel ==  0) {
                            CALCULATRICE_EXCEPTION("ERREUR: Dynamic_cast");
                        }
                        else {/*
                            Complexe* res= new Complexe((*partEnt) + (*ptReel), *partIm);
                            LitteraleNombre& ref = *res;
                            return ref;*/
                            Complexe* refC = ptReel->toComplexe();
                            Complexe* res = new Complexe((partEnt)->addition(*refC->getPartEnt()), (partIm)->addition(*refC->getPartIm()));
                            LitteraleNombre& ref = *res;
                            return(ref);
                        }
                }
                else {
                    Complexe* res= new Complexe(partEnt->addition(*ptRationnel), *partIm);
                    LitteraleNombre& ref = *res;
                    return ref;
                }
        }
        else {
            Complexe* res= new Complexe(partEnt->addition(*ptEntier), *partIm);
            LitteraleNombre& ref = *res;
            return ref;
        }
    }
    else {
        Complexe* res= new Complexe(partEnt->addition(*ptComplexe->getPartEnt()), partIm->addition(*ptComplexe->getPartIm()));
        LitteraleNombre& ref = *res;
        return ref;
    }
}


LitteraleNombre& Complexe::soustraction(const LitteraleNombre& lit) const {
    //Complexe + Complexe = complexe
    const Complexe* ptComplexe = dynamic_cast<const Complexe*>(&lit);
    if (ptComplexe == nullptr) {
        const Entier* ptEntier = dynamic_cast<const Entier*>(&lit);
        // Complexe + int = complexe
        if (ptEntier == 0) {
            //Complexe + rationnel = complexe
            const Rationnel* ptRationnel = dynamic_cast<const Rationnel*>(&lit);
                if (ptRationnel == 0) {
                    //Complexe + reel = complexe
                    const Reel* ptReel = dynamic_cast<const Reel*>(&lit);
                        if (ptReel ==  0) {
                            CALCULATRICE_EXCEPTION("ERREUR: Dynamic_cast");
                        }
                        else {
                            Complexe* res= new Complexe(partEnt->soustraction(*ptReel), *partIm);
                            LitteraleNombre& ref = *res;
                            return ref;
                        }
                }
                else {
                    Complexe* res= new Complexe(partEnt->soustraction(*ptRationnel), *partIm);
                    LitteraleNombre& ref = *res;
                    return ref;
                }
        }
        else {
            Complexe* res= new Complexe(partEnt->soustraction(*ptEntier), *partIm);
            LitteraleNombre& ref = *res;
            return ref;
        }
    }
    else {
        Complexe* res= new Complexe(partEnt->soustraction(*ptComplexe->getPartEnt()), partIm->soustraction(*ptComplexe->getPartIm()));
        LitteraleNombre& ref = *res;
        return ref;
    }
}



LitteraleNombre& Complexe::multiplication(const LitteraleNombre& lit) const {
    //Complexe + Complexe = complexe
    const Complexe* ptComplexe = dynamic_cast<const Complexe*>(&lit);
    if (ptComplexe == nullptr) {
        const Entier* ptEntier = dynamic_cast<const Entier*>(&lit);
        // Complexe + int = complexe
        if (ptEntier == 0) {
            //Complexe + rationnel = complexe
            const Rationnel* ptRationnel = dynamic_cast<const Rationnel*>(&lit);
                if (ptRationnel == 0) {
                    //Complexe + reel = complexe
                    const Reel* ptReel = dynamic_cast<const Reel*>(&lit);
                        if (ptReel ==  0) {
                            CALCULATRICE_EXCEPTION("ERREUR: Dynamic_cast");
                        }
                        else {
                            Complexe* res= new Complexe(partEnt->multiplication(*ptReel), partIm->multiplication(*ptReel));
                            LitteraleNombre& ref = *res;
                            return ref;
                        }
                }
                else {
                    Complexe* res= new Complexe(partEnt->multiplication(*ptRationnel), partIm->multiplication(*ptRationnel));
                    LitteraleNombre& ref = *res;
                    return ref;
                }
        }
        else {
            Complexe* res= new Complexe(partEnt->multiplication(*ptEntier), partIm->multiplication(*ptEntier));
            LitteraleNombre& ref = *res;
            return ref;
        }
    }
    else {
        Complexe* res= new Complexe(((partEnt->multiplication(*ptComplexe->getPartEnt()))-(partIm->multiplication(*ptComplexe->getPartIm()))), ((partEnt->multiplication(*ptComplexe->getPartIm()))+(partIm->multiplication(*ptComplexe->getPartEnt()))));
        LitteraleNombre& ref = *res;
        return ref;
    }
}



LitteraleNombre& Complexe::division(const LitteraleNombre& lit) const {
    //Complexe + Complexe = complexe
    const Complexe* ptComplexe = dynamic_cast<const Complexe*>(&lit);
    if (ptComplexe == nullptr) {
        const Entier* ptEntier = dynamic_cast<const Entier*>(&lit);
        // Complexe + int = complexe
        if (ptEntier == 0) {
            //Complexe + rationnel = complexe
            const Rationnel* ptRationnel = dynamic_cast<const Rationnel*>(&lit);
                if (ptRationnel == 0) {
                    //Complexe + reel = complexe
                    const Reel* ptReel = dynamic_cast<const Reel*>(&lit);
                        if (ptReel ==  0) {
                            CALCULATRICE_EXCEPTION("ERREUR: Dynamic_cast");
                        }
                        else {
                            if (ptReel->getValue() == 0){
                               CALCULATRICE_EXCEPTION("ERREUR: Division par 0");
                            }
                            else {
                                Complexe* res= new Complexe(partEnt->division(*ptReel), partIm->division(*ptReel));
                                LitteraleNombre& ref = *res;
                                return ref;
                            }
                        }
                }
                else {
                    if (ptRationnel->getNumerateur() == 0){
                        CALCULATRICE_EXCEPTION("ERREUR: Division par 0");
                    }
                    else {
                        Complexe* res= new Complexe(partEnt->division(*ptRationnel), partIm->division(*ptRationnel));
                        LitteraleNombre& ref = *res;
                        return ref;
                    }
                }
        }
        else {
            if(ptEntier->getValeur() == 0){
                CALCULATRICE_EXCEPTION("ERREUR: Division par 0");
            }
            else {
                Complexe* res= new Complexe(partEnt->division(*ptEntier), partIm->division(*ptEntier));
                LitteraleNombre& ref = *res;
                return ref;
            }
        }
    }
    else {
        if (ptComplexe->getPartEnt() == 0 && ptComplexe->getPartIm() == 0){
            CALCULATRICE_EXCEPTION("ERREUR: Division par 0");
        }
        else {
            LitteraleNombre& tmpRe = ((partEnt->multiplication(*ptComplexe->getPartEnt())).addition(partIm->multiplication(*ptComplexe->getPartIm()))).division(((*ptComplexe->getPartEnt()).multiplication(*ptComplexe->getPartEnt())).addition(((*ptComplexe->getPartIm()).multiplication(*ptComplexe->getPartIm()))));
            LitteraleNombre& tmpIm = ((partIm->multiplication(*ptComplexe->getPartEnt())).soustraction(partEnt->multiplication(*ptComplexe->getPartIm()))).division(((*ptComplexe->getPartEnt()).multiplication(*ptComplexe->getPartEnt())).addition(((*ptComplexe->getPartIm()).multiplication(*ptComplexe->getPartIm()))));

            Complexe* res= new Complexe(tmpRe, tmpIm);
            LitteraleNombre& ref = *res;
            return ref;
        }
    }
}




// -- HYPOTHESE POUR LA COMPARAISON DES COMPLEXES -- //
// -- Attention: Hypothese ! Pour comparer les nombres complexes, comme on est dans R^2 c'est assez delicat -- //
// -- On applique l'ordre lexicographique c'est (x,y) > (a,b) ssi x>a ou (x=a et y>b) dans ce cas la -- //


bool Complexe::superieur(const LitteraleNombre& lit) const {
    const Complexe* ptComplexe = dynamic_cast<const Complexe*>(&lit);
    if (ptComplexe == nullptr) {
        const Entier* ptEntier = dynamic_cast<const Entier*>(&lit);
        // int + int = int
        if (ptEntier == 0) {
            //int + rationnel = rationnel
            const Rationnel* ptRationnel = dynamic_cast<const Rationnel*>(&lit);
                if (ptRationnel == 0) {
                    //int + reel = reel
                    const Reel* ptReel = dynamic_cast<const Reel*>(&lit);
                        if (ptReel ==  0) {
                            CALCULATRICE_EXCEPTION("ERREUR: Dynamic_cast");
                        }
                        else {
                            Complexe* cplx = ptReel->toComplexe();
                            if (this->getPartEnt()->superieur(*cplx->getPartEnt()) || (this->getPartEnt()->egal(*cplx->getPartEnt()) && this->getPartIm()->superieur(*cplx->getPartIm()))){
                                return true;
                             }
                            else {
                                return false;
                            }
                        }
                }
                else {
                    Complexe* cplx = ptRationnel->toComplexe();
                    if (this->getPartEnt()->superieur(*cplx->getPartEnt()) || (this->getPartEnt()->egal(*cplx->getPartEnt()) && this->getPartIm()->superieur(*cplx->getPartIm()))){
                        return true;
                     }
                    else {
                        return false;
                    }
                }
        }
        else {
            Complexe* cplx = ptEntier->toComplexe();
            if (this->getPartEnt()->superieur(*cplx->getPartEnt()) || (this->getPartEnt()->egal(*cplx->getPartEnt()) && this->getPartIm()->superieur(*cplx->getPartIm()))){
                return true;
             }
            else {
                return false;
            }
        }
    }
    else {
        if (this->getPartEnt()->superieur(*ptComplexe->getPartEnt()) || (this->getPartEnt()->egal(*ptComplexe->getPartEnt()) && this->getPartIm()->superieur(*ptComplexe->getPartIm()))){
            return true;
         }
        else {
            return false;
        }
    }
}


//PAS FAIT
bool Complexe::inferieur(const LitteraleNombre& lit) const {
    const Complexe* ptComplexe = dynamic_cast<const Complexe*>(&lit);
    if (ptComplexe == nullptr) {
        const Entier* ptEntier = dynamic_cast<const Entier*>(&lit);
        // int + int = int
        if (ptEntier == 0) {
            //int + rationnel = rationnel
            const Rationnel* ptRationnel = dynamic_cast<const Rationnel*>(&lit);
                if (ptRationnel == 0) {
                    //int + reel = reel
                    const Reel* ptReel = dynamic_cast<const Reel*>(&lit);
                        if (ptReel ==  0) {
                            CALCULATRICE_EXCEPTION("ERREUR: Dynamic_cast");
                        }
                        else {
                            Complexe* cplx = ptReel->toComplexe();
                            if (this->getPartEnt()->inferieur(*cplx->getPartEnt()) || (this->getPartEnt()->egal(*cplx->getPartEnt()) && this->getPartIm()->inferieur(*cplx->getPartIm()))){
                                return true;
                             }
                            else {
                                return false;
                            }
                        }
                }
                else {
                    Complexe* cplx = ptRationnel->toComplexe();
                    if (this->getPartEnt()->inferieur(*cplx->getPartEnt()) || (this->getPartEnt()->egal(*cplx->getPartEnt()) && this->getPartIm()->inferieur(*cplx->getPartIm()))){
                        return true;
                     }
                    else {
                        return false;
                    }
                }
        }
        else {
            Complexe* cplx = ptEntier->toComplexe();
            if (this->getPartEnt()->inferieur(*cplx->getPartEnt()) || (this->getPartEnt()->egal(*cplx->getPartEnt()) && this->getPartIm()->inferieur(*cplx->getPartIm()))){
                return true;
             }
            else {
                return false;
            }
        }
    }
    else {
        if (this->getPartEnt()->inferieur(*ptComplexe->getPartEnt()) || (this->getPartEnt()->egal(*ptComplexe->getPartEnt()) && this->getPartIm()->inferieur(*ptComplexe->getPartIm()))){
            return true;
         }
        else {
            return false;
        }
    }
}


// -- On dit qu'un complexe est egal a un autre quand leur parties imagianires ET reelles sont egales -- //

bool Complexe::egal(const LitteraleNombre& lit) const {
    const Complexe* ptComplexe = dynamic_cast<const Complexe*>(&lit);
    if (ptComplexe == nullptr) {
        const Entier* ptEntier = dynamic_cast<const Entier*>(&lit);
        // int + int = int
        if (ptEntier == 0) {
            //int + rationnel = rationnel
            const Rationnel* ptRationnel = dynamic_cast<const Rationnel*>(&lit);
                if (ptRationnel == 0) {
                    //int + reel = reel
                    const Reel* ptReel = dynamic_cast<const Reel*>(&lit);
                        if (ptReel ==  0) {
                            CALCULATRICE_EXCEPTION("ERREUR: Dynamic_cast");
                        }
                        else {
                            Complexe* cplx = ptReel->toComplexe();
                            if (this->getPartEnt()->egal(*cplx->getPartEnt()) && this->getPartIm()->egal(*cplx->getPartIm())){
                                return true;
                             }
                            else {
                                return false;
                            }
                        }
                }
                else {
                    Complexe* cplx = ptRationnel->toComplexe();
                    if (this->getPartEnt()->egal(*cplx->getPartEnt()) && this->getPartIm()->egal(*cplx->getPartIm())){
                        return true;
                     }
                    else {
                        return false;
                    }
                }
        }
        else {
            Complexe* cplx = ptEntier->toComplexe();
            if (this->getPartEnt()->egal(*cplx->getPartEnt()) && this->getPartIm()->egal(*cplx->getPartIm())){
                return true;
             }
            else {
                return false;
            }
        }
    }
    else {
        if (this->getPartEnt()->egal(*ptComplexe->getPartEnt()) && this->getPartIm()->egal(*ptComplexe->getPartIm())){
            return true;
         }
        else {
            return false;
        }
    }
}







