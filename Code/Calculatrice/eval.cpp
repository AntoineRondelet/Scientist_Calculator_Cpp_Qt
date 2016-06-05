#include "eval.h"
#include <QString>
#include <QStringList>
#include <QRegularExpression>
#include "controleur.h"


#include "expression.h"


bool isOperateurPrioritaire(const QString& str) {
    if (str == "NEG")
        return true;
    else
        return false;
}

bool isOperateurSecondaire(const QString& str) {
    if (str == "*" || str == "/")
        return true;
    else
        return false;
}

bool isOperateurTernaire(const QString& str) {
    if (str == "+" || str == "-")
        return true;
    else
        return false;
}

bool isOperateur(const QString& str) {
        return (isOperateurPrioritaire(str) || isOperateurSecondaire(str) || isOperateurTernaire(str));
}


void Eval::execute(QVector<Litterale*> litterals) const {
    Pile& stack = Pile::getInstance();
    Expression* operandeExpression = dynamic_cast<Expression *>(litterals[0]);

    if(operandeExpression) {
        QString test = operandeExpression->toString();
        test.remove("'");
        test.replace(QRegularExpression("\\+"), " + ");
        test.replace(QRegularExpression("-"), " - ");
        test.replace(QRegularExpression("\\*"), " * ");
        test.replace(QRegularExpression("\\/"), " / ");

        // -- Ici, on va a partir de l'expression a evaluer, créer une QStringList que l'on va "réorganiser" à la maniere d'une saisie "standard" faite par l'utilisateur -- //
        QStringList testSplit = test.split(QRegularExpression("[[:space:]]+"));
        // -- ATTENTION: On est obligé de partitionner sur 1 ou plusieurs espaces car si on a deux operateurs de suite (typiquement le cas du "-" infixe), on aura un espace "parasite" lors du split -- //

        // -- Traitement -- //

        // -- Verification des atomes et remplacement des - infixes par des NEG -- //
        for (int i=0; i<testSplit.size(); i++){
            if(i<testSplit.size() && testSplit[i] == "-") { //On est sur un "-" -> on regarde si c'est un NEG ou un - "normal"
                if ((i == 0) || (i>0 && isOperateur(testSplit[i-1]))) { //Les cas ou un "-" <=> NEG: Soit l'expression commence par un "-", soit on a un "-" directement apres un operateur !
                    testSplit[i] = "NEG";
                }
            }
        }
        // -- Permutation des operateurs prioritaires (On fera d'abord ces opérations) -- //
        for (int i=0; i<testSplit.size(); i++){
            if(i<testSplit.size() && isOperateurPrioritaire(testSplit[i])) { //On est sur un "NEG" etc.
                int j = i+1;
                while(j<testSplit.size() && !isOperateur(testSplit[j]))
                    j++;
                // On sort du while quand on est sur un operateur: Comme on est sur les operateurs prioritaires, ils doivent restent le plus haut possible pour etre fait en premiers. Donc ils ne passent jamais en dessous d'un autre operateur
                testSplit.move(i, j-1);
            }
        }
        // -- Permutation des operateurs secondaire (On fera ensuite ces opérations) -- //
        for (int i=0; i<testSplit.size(); i++){
            if(i<testSplit.size() && isOperateurSecondaire(testSplit[i])) { //On est sur un "*" ou un "/"
                int j = i+1;
                while(j<testSplit.size() && !isOperateur(testSplit[j]))
                    j++;
                // On sort du while quand on est sur un operateur
                if(j<testSplit.size()) { //on verifie la cause de la sortie du while: ici on verifie qu'on est sorti car on est tombé sur un opérateur et non pas parce qu'on est a la fin
                    //Si l'operateur qui nous a fait sortir du while est un operateur prioritaire, on met l'operateur secondaire apres.
                    if(isOperateurPrioritaire(testSplit[j]))
                        testSplit.move(i,j);
                    else //opérateur de la meme priorité ou moins prioritaire, on ne le "depasse" pas (a savoir que depasser un operateur => etre fait apres donc : moins prioritaire)
                        testSplit.move(i,j-1);
                }
                else { //Si jamais on est sorti parce qu'on était a la fin de l'expression
                    testSplit.move(i, j-1);
                }
            }
        }
        // -- Permutation des operateurs ternaires (On fera ces opérations en dernier) -- //
        for (int i=0; i<testSplit.size(); i++){
            if(i<testSplit.size() && isOperateurTernaire(testSplit[i])) {
                int j = i+1;
                // -- Ici ATTENTION a l'ordre des conditions ! Il est forcement celui-ci: on ne peut pas le changer ! Sinon ASSERT erreur (on essaie d'acceder a une case qui n'est pas dans le tableau -- //
                while(j<testSplit.size() && !isOperateur(testSplit[j]))
                    j++;
                //on sort du while quand on est sur un operateur
                if(j<testSplit.size()) { //on verifie la cause de la sortie du while: ici on verifie qu'on est sorti car on est tombé sur un opérateur et non pas parce qu'on est a la fin
                    //Si l'operateur qui nous a fait sortir du while est un operateur prioritaire, on met l'operateur secondaire apres.
                    if(isOperateurSecondaire(testSplit[j]) || isOperateurPrioritaire(testSplit[j]))
                        testSplit.move(i,j);
                    else //opérateur non prioritaire ou de meme priorité
                        testSplit.move(i,j-1);
                }
                else { //Si jamais on est sorti parce qu'on était a la fin de l'expression
                    testSplit.move(i, j-1);
                }
            }
        }

        stack.setMessage(testSplit.join(""));

        Controleur& cont = Controleur::getInstance();
        bool rep = cont.analyser->reconnaitre(testSplit);

        if(rep == false) {
            this->reChargerOperande(litterals);
            stack.setMessage("ON EST LA ");
        }else {
           delete litterals[0];
        }
    }
    else {
        // -- On réeimpile la littérale qui n'est pas du bon type -- //
        this->reChargerOperande(litterals);
    }
}



/* MARCHE POUR UN SEUL OPERATEUR BINAIRE
void Eval::execute(QVector<Litterale*> litterals) const {
    Pile& stack = Pile::getInstance();
    Expression* operandeExpression = dynamic_cast<Expression *>(litterals[0]);

    if(operandeExpression) {
        QString test = operandeExpression->toString();
        test.remove("'");
        test.replace(QRegularExpression("\\+"), " + ");
        test.replace(QRegularExpression("-"), " - ");
        test.replace(QRegularExpression("\\*"), " * ");
        test.replace(QRegularExpression("\\/"), " / ");

        QStringList testSplit = test.split(" ");
        testSplit.swap(1,2);

        stack.setMessage(testSplit.join(""));

        Controleur& cont = Controleur::getInstance();
        bool rep = cont.analyser->reconnaitre(testSplit);

        if(rep == false) {
            this->reChargerOperande(litterals);
            stack.setMessage("ON EST LA ");
        }else {
           delete litterals[0];
        }
    }
    else {
        // -- On réeimpile la littérale qui n'est pas du bon type -- //
        this->reChargerOperande(litterals);
    }
}
*/

