#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHeaderView>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // ----------- debut init ------------ //

    // -- On met le fond de la QLineEdit du message en noir -- //
    ui->lineEditMessage->setStyleSheet("background: black; color: white");

    // -- Ne plus pouvoir ecrire dans la zone de texte destinee a afficher des messages a l'utilisateur -- //
    ui->lineEditMessage->setReadOnly(true);


    //on precise le nombre de lignes et le nombre de colonnes (ici 1) qu'on veut afficher
    //QTableWidget --> c'est juste une coquille --> on a des rangées pour mettre ce que l'on veut, MAIS, on va devoir allouer
    //dynamiquement ce qu'on va mettre dedans --> ATTENTION
    ui->tableWidgetPile->setRowCount(Pile::getInstance().getNbAffiche());
    ui->tableWidgetPile->setColumnCount(1);


    // -- Allocation des widgets a l'interieur du tableau -- //
    for(unsigned int i=0; i < Pile::getInstance().getNbAffiche(); i++)
        //setItem est une methode de la classe QTableWidget
        ui->tableWidgetPile->setItem(i,0,new QTableWidgetItem(""));

    // -- Rendre invisible le header horizontal -- //
    ui->tableWidgetPile->horizontalHeader()->setVisible(false);

    // -- Ajuster la largeur de la derniere colonne (ici on en a qu'une) automatiquement -- //
    ui->tableWidgetPile->horizontalHeader()->setStretchLastSection(true);

    // -- On ajoute un peu de couleur -- //
    ui->tableWidgetPile->setStyleSheet("background: grey; color: black");

    // -- Changer les labels de chaque ligne -- //
    QStringList liste;
    for(unsigned int i=Pile::getInstance().getNbAffiche(); i>0; i--) {
        QString str = QString::number(i);
        str+=" :";
        liste<<str;
    }
    ui->tableWidgetPile->setVerticalHeaderLabels(liste);

    // -- Empecher l'edition du QTableWidget: on ne peut que voir les valeurs dans les champs et pas les modifier directement -- //
    ui->tableWidgetPile->setEditTriggers(QAbstractItemView::NoEditTriggers);

    this->setWindowTitle("CALCULATRICE LO21"); //Donner un titre a sa fenetre

    //connect(commande, SIGNAL(returnPressed()),this, SLOT(getNextCommande()));
    //On declenche un signal quand on fait un "enter" --> signal envoyé
    //On a pas besoin de mettre QObject:: devant connect, car ici, on est dans un widget qui herite de QObject donc pas besoin ici
    //on affiche en message ce que rentre l'utilisateur au moment ou il fait un enter

    //connect(pile, SIGNAL(modificationEtat()), this, SLOT(refresh()));
    // ------------- fin init ------------ //



    // on établit les connections entre les boutons
    connections();
}


MainWindow::~MainWindow(){delete ui;}



// connection
void MainWindow::connections() {
    // -- Connection pour les chiffres [0-9] -- //
    connect(ui->but0, SIGNAL(clicked()), this, SLOT(but0Appuye()));
    connect(ui->but1, SIGNAL(clicked()), this, SLOT(but1Appuye()));
    connect(ui->but2, SIGNAL(clicked()), this, SLOT(but2Appuye()));
    connect(ui->but3, SIGNAL(clicked()), this, SLOT(but3Appuye()));
    connect(ui->but4, SIGNAL(clicked()), this, SLOT(but4Appuye()));
    connect(ui->but5, SIGNAL(clicked()), this, SLOT(but5Appuye()));
    connect(ui->but6, SIGNAL(clicked()), this, SLOT(but6Appuye()));
    connect(ui->but7, SIGNAL(clicked()), this, SLOT(but7Appuye()));
    connect(ui->but8, SIGNAL(clicked()), this, SLOT(but8Appuye()));
    connect(ui->but9, SIGNAL(clicked()), this, SLOT(but9Appuye()));

    // -- Operateur complexe -- //
    connect(ui->pButCplx, SIGNAL(clicked()), this, SLOT(butOpCplxAppuye()));

    /*
    // -- Espace -- //
    connect(ui->butdollar, SIGNAL(clicked()), this, SLOT(butDollarAppuye()));
    */

    // -- Point -- //
    connect(ui->pButDot, SIGNAL(clicked()), this, SLOT(butDotAppuye()));

    // -- Opérations de base -- //
    connect(ui->pButAdd, SIGNAL(clicked()), this, SLOT(butAddAppuye()));
    connect(ui->pButSous, SIGNAL(clicked()), this, SLOT(butSousAppuye()));
    connect(ui->pButMult, SIGNAL(clicked()), this, SLOT(butMultAppuye()));
    connect(ui->pButDiv, SIGNAL(clicked()), this, SLOT(butDivAppuye()));
}


/* LES SLOTS */
// 0->9
void MainWindow::but0Appuye() {
    ui->lineEditCommande->setText(ui->lineEditCommande->text()+"0");
}

void MainWindow::but1Appuye() {
    ui->lineEditCommande->setText(ui->lineEditCommande->text()+"1");
}

void MainWindow::but2Appuye() {
    ui->lineEditCommande->setText(ui->lineEditCommande->text()+"2");
}

void MainWindow::but3Appuye() {
    ui->lineEditCommande->setText(ui->lineEditCommande->text()+"3");
}

void MainWindow::but4Appuye() {
    ui->lineEditCommande->setText(ui->lineEditCommande->text()+"4");
}

void MainWindow::but5Appuye() {
    ui->lineEditCommande->setText(ui->lineEditCommande->text()+"5");
}

void MainWindow::but6Appuye() {
    ui->lineEditCommande->setText(ui->lineEditCommande->text()+"6");
}

void MainWindow::but7Appuye() {
    ui->lineEditCommande->setText(ui->lineEditCommande->text()+"7");
}
void MainWindow::but8Appuye() {
    ui->lineEditCommande->setText(ui->lineEditCommande->text()+"8");
}
void MainWindow::but9Appuye() {
    ui->lineEditCommande->setText(ui->lineEditCommande->text()+"9");
}


// -- Operateur complexe -- //
void MainWindow::butOpCplxAppuye(){ ui->lineEditCommande->setText(ui->lineEditCommande->text()+"$"); }


/*// -- Espace -- //
void MainWindow::butEspaceAppuye(){ ui->lineEditCommande->setText(ui->lineEditCommande->text()+" "); } */

// -- Point -- //
void MainWindow::butDotAppuye(){ ui->lineEditCommande->setText(ui->lineEditCommande->text()+"."); }


// -- Opérations de base -- //

void MainWindow::butAddAppuye(){ ui->lineEditCommande->setText(ui->lineEditCommande->text()+" +"); }
void MainWindow::butSousAppuye(){ ui->lineEditCommande->setText(ui->lineEditCommande->text()+" -"); }
void MainWindow::butMultAppuye(){ ui->lineEditCommande->setText(ui->lineEditCommande->text()+" *"); }
void MainWindow::butDivAppuye(){ ui->lineEditCommande->setText(ui->lineEditCommande->text()+"/"); }





/*


// virgule
connect(ui->butpoint, SIGNAL(clicked()), this, SLOT(butPointAppuye()));

// opérations
connect(ui->butaddition, SIGNAL(clicked()), this, SLOT(butAdditionAppuye()));
connect(ui->butsoustraction, SIGNAL(clicked()), this, SLOT(butSoustractionAppuye()));
connect(ui->butmultiplication, SIGNAL(clicked()), this, SLOT(butMultiplicationAppuye()));
connect(ui->butdivision, SIGNAL(clicked()), this, SLOT(butDivisionAppuye()));

// enter et eval
connect(ui->butenter, SIGNAL(clicked()), this, SLOT(butEnterAppuye()));
connect(ui->buteval, SIGNAL(clicked()), this, SLOT(butEvalAppuye()));

// delete
connect(ui->butdel, SIGNAL(clicked()), this, SLOT(butDelAppuye()));


// checkbox mode complex = annuler qq boutons
connect(ui->checkBoxComplex, SIGNAL(clicked(bool)), this, SLOT(checkModeComplex(bool)));

// boutton backspace
connect(ui->butBackspace, SIGNAL(clicked()), this, SLOT(butBackspace()));

// Edition : actions Undo et Redo
connect(ui->actionAnnuler, SIGNAL(triggered()), this, SLOT(annulerEtatPile()));
connect(ui->actionRetablir, SIGNAL(triggered()), this, SLOT(retablirEtatPile()));

// pile
connect(ui->butswap, SIGNAL(clicked()), this, SLOT(butSwapAppuye()));
connect(ui->butsum, SIGNAL(clicked()), this, SLOT(butSumAppuye()));
connect(ui->butmean, SIGNAL(clicked()), this, SLOT(butMeanAppuye()));
connect(ui->butclear, SIGNAL(clicked()), this, SLOT(butClearAppuye()));
connect(ui->butdrop, SIGNAL(clicked()), this, SLOT(butDropAppuye()));
connect(ui->butdup, SIGNAL(clicked()), this, SLOT(butDupAppuye()));
connect(ui->butCote, SIGNAL(clicked()), this, SLOT(butCote()));
*/

