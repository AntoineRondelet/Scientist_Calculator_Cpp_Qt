#include "sto.h"


#include <QString>
#include "atome.h"
#include "litterale.h"
#include "identificateurmanager.h"

void Sto::execute(QVector<Litterale*> litterals) const {
    Atome* operande1 = dynamic_cast<Atome*>(litterals[0]);
    LitteraleNombre* operande2 = dynamic_cast<LitteraleNombre *>(litterals[1]);

    if (operande1!=nullptr && operande2!=nullptr){
        IdentificateurManager& id_man = IdentificateurManager::getInstance();
        id_man.ajouterIdentificateur(operande1->toString(), operande2->clone());

        // -- On delete le tableau qu'on a récupéré en argument -- //
        for (unsigned int i = 0; i < Nb_a_depiler; i++) {
            delete litterals[i];
        }
        //On empile le resultat: Pas de resultat à empiler ici
        //Pile::getInstance().push(&res);
    }
    else {
        this->reChargerOperande(litterals);
    }
}
