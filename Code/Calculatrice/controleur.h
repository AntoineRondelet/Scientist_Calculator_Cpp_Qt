#ifndef CONTROLEUR_H
#define CONTROLEUR_H

#include "pile.h"
#include "entier.h"
#include "rationnel.h"
#include "reel.h"
#include <QString>
#include "analyser.h"

class Controleur {
    Analyser* analyser;
public:
    Controleur(): analyser(new Analyser()){
        //On initialise la map qui contient nos regex et nos fonctions de construction
        analyser->init();
    }

    void boucleExcecution();
    void commande(QStringList& list_src);

    ~Controleur(){delete analyser;} //On a une composition
};

//void splitEntry(const string& c); //Fonction qui permet de recuperer chaque "mot" dans la "phrase" saisie par le user
// Donc elle nous permet de recuperer





#endif // CONTROLEUR_H
