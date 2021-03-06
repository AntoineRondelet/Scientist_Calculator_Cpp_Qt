#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QString>
#include <QStringList>
#include <QKeyEvent>
#include <QShortcut>

#include <QMessageBox>
#include "dialogedit.h"
#include "ui_dialogedit.h"
#include "dialogeditpile.h"

#include "tabdialog.h"
#include "stackdialog.h"

#include "xml_dom.h"

#include <QFileDialog>




MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // -- On initialise l'apparence de la fenetre principale -- //
    init();

    // -- On établit les connections entre les boutons -- //
    connections();

    // -- Retablie la sauvegarde choisie -- //
    Xml_Dom monXml;
    monXml.RestoreXML();

    refresh();

    // -- On initialise les identificateurs a partir de la sauvegarde -- //
    initIDs();

    // -- quelques reglages par defaut -- //
    ui->pButForgetSettings->setEnabled(false);
    ui->pButEditSettings->setEnabled(false);
}


MainWindow::~MainWindow(){
    delete ui;
}


void MainWindow::closeEvent(QCloseEvent *event){
    Xml_Dom monXml;
    monXml.saveXML();
}



void MainWindow::init(int dim) {
    // -- On met le fond de la QLineEdit du message en noir -- //
    ui->lineEditMessage->setStyleSheet("background: black; color: white");

    // -- Ne plus pouvoir ecrire dans la zone de texte destinee a afficher des messages a l'utilisateur -- //
    ui->lineEditMessage->setReadOnly(true);

    // -- On precise le nombre de lignes et le nombre de colonnes (ici 1) qu'on veut afficher -- //
    // -- QTableWidget: c'est juste une coquille. On a des rangées pour mettre ce que l'on veut -- //
    // -- MAIS, on va devoir allouer dynamiquement ce qu'on va mettre dedans: ATTENTION -- //
    ui->tableWidgetPile->setRowCount(dim);
    ui->tableWidgetPile->setColumnCount(1);


    // -- Allocation des widgets a l'interieur du tableau -- //
    for(unsigned int i=0; i < dim; i++)
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
    for(unsigned int i=dim; i>0; i--) {
        QString str = QString::number(i);
        str+=" :";
        liste<<str;
    }
    ui->tableWidgetPile->setVerticalHeaderLabels(liste);

    // -- Empecher l'edition du QTableWidget: on ne peut que voir les valeurs dans les champs et pas les modifier directement -- //
    ui->tableWidgetPile->setEditTriggers(QAbstractItemView::NoEditTriggers);

    this->setWindowTitle("CALCULATRICE LO21"); //Donner un titre a sa fenetre
}




void MainWindow::initIDs(){
    // -- Table des variables -- //
    QStringList list_var_ids = IdentificateurManager::getInstance().getVarEntries();
    ui->tableWidgetIDsVar->setRowCount(list_var_ids.size());
    ui->tableWidgetIDsVar->setColumnCount(1);

    // -- Table des programmes -- //
    QStringList list_prog_ids = IdentificateurManager::getInstance().getProgEntries();
    ui->tableWidgetIDsProg->setRowCount(list_prog_ids.size());
    ui->tableWidgetIDsProg->setColumnCount(1);

    // -- Allocation des widgets a l'interieur du tableau des variables -- //
    for(unsigned int i=0; i < list_var_ids.size(); i++)
        ui->tableWidgetIDsVar->setItem(i,0,new QTableWidgetItem(list_var_ids[i]));

    // -- Allocation des widgets a l'interieur du tableau des programmes -- //
    for(unsigned int i=0; i < list_prog_ids.size(); i++)
        ui->tableWidgetIDsProg->setItem(i,0,new QTableWidgetItem(list_prog_ids[i]));

    // -- Rendre invisible le header horizontal -- //
    ui->tableWidgetIDsVar->horizontalHeader()->setVisible(false);
    ui->tableWidgetIDsProg->horizontalHeader()->setVisible(false);

    // -- Ajuster la largeur de la derniere colonne (ici on en a qu'une) automatiquement -- //
    ui->tableWidgetIDsVar->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidgetIDsProg->horizontalHeader()->setStretchLastSection(true);

    // -- Empecher l'edition du QTableWidget: on ne peut que voir les valeurs dans les champs et pas les modifier directement -- //
    ui->tableWidgetIDsVar->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidgetIDsProg->setEditTriggers(QAbstractItemView::NoEditTriggers);
}


void MainWindow::refreshIDs(){
    ui->tableWidgetIDsVar->clear();
    ui->tableWidgetIDsProg->clear();
    initIDs();
}




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

    // -- Espace -- //
    //connect(ui->butdollar, SIGNAL(clicked()), this, SLOT(butDollarAppuye()));


    // -- Point -- //
    connect(ui->pButDot, SIGNAL(clicked()), this, SLOT(butDotAppuye()));

    // -- Opérations de base -- //
    connect(ui->pButAdd, SIGNAL(clicked()), this, SLOT(butAddAppuye()));
    connect(ui->pButSous, SIGNAL(clicked()), this, SLOT(butSousAppuye()));
    connect(ui->pButMult, SIGNAL(clicked()), this, SLOT(butMultAppuye()));
    connect(ui->pButDiv, SIGNAL(clicked()), this, SLOT(butDivAppuye()));

    // -- Connection si l'utilisateur appuie sur la touche enter -- //
    connect(ui->pButEnter, SIGNAL(clicked()), this, SLOT(butEnterAppuye()));
    // -- Connection si l'utilisateur appuie sur la touche enter du clavier ! -- //
    //connect(ui->actionKeyboard, SIGNAL(clicked()), this, SLOT(keyPressEvent()));

    // -- Connection entre le Controleur et la fenetre pour refresh la pile quand on fait une modif -- //
    connect(&Controleur::getInstance(), SIGNAL(modificationEtat()), this, SLOT(refresh()));


    // -- Elements de syntaxe -- //
    connect(ui->pButCrochO, SIGNAL(clicked()), this, SLOT(butCrochOAppuye()));
    connect(ui->pButCrochF, SIGNAL(clicked()), this, SLOT(butCrochFAppuye()));

    connect(ui->pButParF, SIGNAL(clicked()), this, SLOT(butParenthFAppuye()));
    connect(ui->pButParO, SIGNAL(clicked()), this, SLOT(butParenthOAppuye()));

    connect(ui->pButQuote, SIGNAL(clicked()), this, SLOT(butQuoteAppuye()));
    connect(ui->pButSpace, SIGNAL(clicked()), this, SLOT(butSpaceAppuye()));

    // -- Efface le dernier caractere entré dans la QLineEdit -- //
    connect(ui->pButDelete, SIGNAL(clicked()), this, SLOT(butDeleteAppuye()));

    // -- Mode scientifique -- //
    connect(ui->checkBoxS, SIGNAL(clicked(bool)), this, SLOT(checkModeScientist(bool)));


    // -- Pour associer le ctrl-z au undo -- //
    QShortcut* shortcutUndo = new QShortcut(QKeySequence("Ctrl+Z"), this);
    connect(shortcutUndo, SIGNAL(activated()), this, SLOT(on_pButUndo_clicked()));

    // -- Pour associer le ctrl-y au redo -- //
    QShortcut* shortcutRedo = new QShortcut(QKeySequence("Ctrl+Y"), this);
    connect(shortcutRedo, SIGNAL(activated()), this, SLOT(on_pButRedo_clicked()));

    // -- Connection entre le Controleur et la fenetre pour refresh la pile quand on fait une modif -- //
    connect(&IdentificateurManager::getInstance(), SIGNAL(modificationEtatIDs()), this, SLOT(refreshIDs()));

    // -- Pouvoir utiliser la touche clavier Enter -- //
    connect(ui->lineEditCommande, SIGNAL(returnPressed()), this, SLOT(butEnterAppuye()));
}




// ------------- LES SLOTS -------------- //


// --  Chiffres [0-9] -- //
void MainWindow::but0Appuye() {ui->lineEditCommande->setText(ui->lineEditCommande->text()+"0");}
void MainWindow::but1Appuye() {ui->lineEditCommande->setText(ui->lineEditCommande->text()+"1");}
void MainWindow::but2Appuye() {ui->lineEditCommande->setText(ui->lineEditCommande->text()+"2");}
void MainWindow::but3Appuye() {ui->lineEditCommande->setText(ui->lineEditCommande->text()+"3");}
void MainWindow::but4Appuye() {ui->lineEditCommande->setText(ui->lineEditCommande->text()+"4");}
void MainWindow::but5Appuye() {ui->lineEditCommande->setText(ui->lineEditCommande->text()+"5");}
void MainWindow::but6Appuye() {ui->lineEditCommande->setText(ui->lineEditCommande->text()+"6");}
void MainWindow::but7Appuye() {ui->lineEditCommande->setText(ui->lineEditCommande->text()+"7");}
void MainWindow::but8Appuye() {ui->lineEditCommande->setText(ui->lineEditCommande->text()+"8");}
void MainWindow::but9Appuye() {ui->lineEditCommande->setText(ui->lineEditCommande->text()+"9");}


// -- Operateur complexe -- //
void MainWindow::butOpCplxAppuye(){ ui->lineEditCommande->setText(ui->lineEditCommande->text()+"$"); }


/*// -- Espace -- //
void MainWindow::butEspaceAppuye(){ ui->lineEditCommande->setText(ui->lineEditCommande->text()+" "); } */

// -- Point -- //
void MainWindow::butDotAppuye(){ ui->lineEditCommande->setText(ui->lineEditCommande->text()+"."); }


// -- Opérations de base -- //
void MainWindow::butAddAppuye(){ ui->lineEditCommande->setText(ui->lineEditCommande->text()+"+"); }
void MainWindow::butSousAppuye(){ ui->lineEditCommande->setText(ui->lineEditCommande->text()+"-"); }
void MainWindow::butMultAppuye(){ ui->lineEditCommande->setText(ui->lineEditCommande->text()+"*"); }
void MainWindow::butDivAppuye(){ ui->lineEditCommande->setText(ui->lineEditCommande->text()+"/"); }


// -- Elements de synatxe -- //
void MainWindow::butCrochOAppuye(){ ui->lineEditCommande->setText(ui->lineEditCommande->text()+"["); }
void MainWindow::butCrochFAppuye(){ ui->lineEditCommande->setText(ui->lineEditCommande->text()+"]"); }
void MainWindow::butParenthOAppuye(){ ui->lineEditCommande->setText(ui->lineEditCommande->text()+"("); }
void MainWindow::butParenthFAppuye(){ ui->lineEditCommande->setText(ui->lineEditCommande->text()+")"); }
void MainWindow::butQuoteAppuye(){ ui->lineEditCommande->setText(ui->lineEditCommande->text()+"'"); }
void MainWindow::butSpaceAppuye(){ ui->lineEditCommande->setText(ui->lineEditCommande->text()+" "); }

// -- Clear la ligne de saisie -- //
void MainWindow::butDeleteAppuye(){ ui->lineEditCommande->clear();}



// -- Lorsque l'on appuie sur le bouton Enter -- //
void MainWindow::butEnterAppuye() {
    Pile::getInstance().setMessage("");
    // -- Interpreter l'entrée de l'utilisateur -- //
    QString str_in = ui->lineEditCommande->text();
    // -- Extraction de chaque element de la ligne on suppose que le séparateur est l'espace -- //
    QStringList liste_param = str_in.split(QRegularExpression("[[:space:]]+"));
    if (str_in!="Q") Controleur::getInstance().commande(liste_param);

    // -- On remet le message de la QListEdit de message a zero -- //
    ui->lineEditCommande->clear();
}



// -- Permet d'actualiser la pile quand on fait des changements -- //
void MainWindow::refresh() {
    ui->lineEditMessage->setText(Pile::getInstance().getMessage());
    for(unsigned int i=0; i<Pile::getInstance().getNbAffiche(); i++)
    {
        // -- Pour remettre a zero les donnees de ma pile -- //
        ui->tableWidgetPile->item(i,0)->setText("");
    }
    // -- Affichage -- //
    unsigned int nb = Pile::getInstance().getNbAffiche();
    for(int i=Pile::getInstance().getNbAffiche(); i>0; i--) {
        //A changer ! ici on affiche des std::string -> il faudra supprimer le .toStdString() et affciher des QString dans l'appli
        if (i<= Pile::getInstance().size())
            ui->tableWidgetPile->item(Pile::getInstance().getNbAffiche()-i,0)->setText(Pile::getInstance().value(Pile::getInstance().size()-i)->toString());
    }
}



/*
void MainWindow::keyPressEvent(QKeyEvent *ev){
    if (ev->key() == Qt::Key_Enter){
        butEnterAppuye();
    }
    else{
        QMainWindow::keyPressEvent(ev);
    }
}
*/


// ------------------------------------------------------------------------------------- //
// ------------------------------------ Les operateurs --------------------------------- //
// ------------------------------------------------------------------------------------- //

// -- On a fait clic droit sur le bouton: "aller a slot" et ici on definit le comportement de notr slot -- //
void MainWindow::on_pButSwap_clicked(){
    QStringList str_list;
    str_list.push_back("SWAP");
    Controleur::getInstance().commande(str_list);
}

void MainWindow::on_pButDup_clicked(){
    QStringList str_list;
    str_list.push_back("DUP");
    Controleur::getInstance().commande(str_list);
}

void MainWindow::on_pButDrop_clicked(){
    QStringList str_list;
    str_list.push_back("DROP");
    Controleur::getInstance().commande(str_list);
}

void MainWindow::on_pButClear_clicked(){
    QStringList str_list;
    str_list.push_back("CLEAR");
    Controleur::getInstance().commande(str_list);
}

void MainWindow::on_pButUndo_clicked(){
    QStringList str_list;
    str_list.push_back("UNDO");
    Controleur::getInstance().commande(str_list);
}

void MainWindow::on_pButRedo_clicked(){
    QStringList str_list;
    str_list.push_back("REDO");
    Controleur::getInstance().commande(str_list);
}

void MainWindow::on_pButNeg_clicked(){
    QStringList str_list;
    str_list.push_back("NEG");
    Controleur::getInstance().commande(str_list);
}

void MainWindow::on_pButIft_clicked(){
    QStringList str_list;
    str_list.push_back("IFT");
    Controleur::getInstance().commande(str_list);
}

void MainWindow::on_pButSto_clicked(){
    QStringList str_list;
    str_list.push_back("STO");
    Controleur::getInstance().commande(str_list);
}

void MainWindow::on_pButForget_clicked(){
    QStringList str_list;
    str_list.push_back("FORGET");
    Controleur::getInstance().commande(str_list);
}

void MainWindow::on_pButEval_clicked(){
    QStringList str_list;
    str_list.push_back("EVAL");
    Controleur::getInstance().commande(str_list);
}

void MainWindow::on_pButAnd_clicked(){
    QStringList str_list;
    str_list.push_back("AND");
    Controleur::getInstance().commande(str_list);
}

void MainWindow::on_pButOr_clicked(){
    QStringList str_list;
    str_list.push_back("OR");
    Controleur::getInstance().commande(str_list);
}

void MainWindow::on_pButNot_clicked(){
    QStringList str_list;
    str_list.push_back("NOT");
    Controleur::getInstance().commande(str_list);
}

void MainWindow::on_pButDen_clicked(){
    QStringList str_list;
    str_list.push_back("DEN");
    Controleur::getInstance().commande(str_list);
}

void MainWindow::on_pButNum_clicked(){
    QStringList str_list;
    str_list.push_back("NUM");
    Controleur::getInstance().commande(str_list);
}

void MainWindow::on_pButInf_clicked(){
    QStringList str_list;
    str_list.push_back("<");
    Controleur::getInstance().commande(str_list);
}

void MainWindow::on_pButSup_clicked(){
    QStringList str_list;
    str_list.push_back(">");
    Controleur::getInstance().commande(str_list);
}

void MainWindow::on_pButEgal_clicked(){
    QStringList str_list;
    str_list.push_back("=");
    Controleur::getInstance().commande(str_list);
}


// -- Operateur EDIT -- //


void MainWindow::on_pButEdit_clicked(){
    IdentificateurManager& id_man = IdentificateurManager::getInstance();
    Pile& stack =  Pile::getInstance();

    Litterale* lit_a_edit = stack.pop();

    Programme* ptr_prog= dynamic_cast<Programme*>(lit_a_edit);

    if(ptr_prog != nullptr) {
        DialogEditPile* fenetreEdit = new DialogEditPile(this);
        fenetreEdit->setTextSaisie(ptr_prog->toString());
        fenetreEdit->exec();
    }
    else {
        QApplication::beep();
    }
    refreshIDs();
}





// -- checkModeScientist -- //

void MainWindow::checkModeScientist(bool change) {
    if (change == false) {
        ui->pButInf->setVisible(false);
        ui->pButInfEgal->setVisible(false);
        ui->pButSup->setVisible(false);
        ui->pButAnd->setVisible(false);
        ui->pButOr->setVisible(false);
        ui->pButNot->setVisible(false);
        ui->pButEval->setVisible(false);
        ui->pButEgal->setVisible(false);
        ui->pButIft->setVisible(false);
        ui->pButLastargs->setVisible(false);
        ui->pButLastops->setVisible(false);

        ui->pButSupEgal->setVisible(false);
        ui->pButDen->setVisible(false);
        ui->pButNum->setVisible(false);
        ui->pButRe->setVisible(false);
        ui->pButIm->setVisible(false);
        ui->pButForget->setVisible(false);

        ui->pButEdit->setVisible(false);
        ui->pButQuote->setVisible(false);
        ui->pButParO->setVisible(false);
        ui->pButParF->setVisible(false);
        ui->pButCrochO->setVisible(false);
        ui->pButCrochF->setVisible(false);
        ui->pButSto->setVisible(false);

        ui->pButCplx->setVisible(false);

    }
    else {
        ui->pButInf->setVisible(true);
        ui->pButInfEgal->setVisible(true);
        ui->pButSup->setVisible(true);
        ui->pButAnd->setVisible(true);
        ui->pButOr->setVisible(true);
        ui->pButNot->setVisible(true);
        ui->pButEval->setVisible(true);
        ui->pButEgal->setVisible(true);
        ui->pButIft->setVisible(true);
        ui->pButLastargs->setVisible(true);
        ui->pButLastops->setVisible(true);

        ui->pButSupEgal->setVisible(true);
        ui->pButDen->setVisible(true);
        ui->pButNum->setVisible(true);
        ui->pButRe->setVisible(true);
        ui->pButIm->setVisible(true);
        ui->pButForget->setVisible(true);

        ui->pButEdit->setVisible(true);
        ui->pButQuote->setVisible(true);
        ui->pButParO->setVisible(true);
        ui->pButParF->setVisible(true);
        ui->pButCrochO->setVisible(true);
        ui->pButCrochF->setVisible(true);
        ui->pButSto->setVisible(true);

        ui->pButCplx->setVisible(true);
    }
}


void MainWindow::on_spinBoxDimPile_valueChanged(int arg1){
    ui->tableWidgetPile->clear();
    this->init(arg1);
    Pile::getInstance().setNbAffiche(arg1);
    refresh();
}

void MainWindow::on_checkBoxSounds_clicked(){
    if (ui->checkBoxSounds->isChecked())
        Controleur::getInstance().setSounds(true);
    else
        Controleur::getInstance().setSounds(false);
}

void MainWindow::on_spinBoxSaves_valueChanged(int arg1){
    PileCaretaker::getInstance().setNbEtatsSave(arg1);
}

void MainWindow::on_tableWidgetIDsProg_itemClicked(QTableWidgetItem *item){
    ui->pButForgetSettings->setEnabled(true);
    ui->pButEditSettings->setEnabled(true);
}

void MainWindow::on_tableWidgetIDsVar_itemClicked(QTableWidgetItem *item){
    ui->pButForgetSettings->setEnabled(true);
    ui->pButEditSettings->setEnabled(true);
}

void MainWindow::on_pButForgetSettings_clicked(){
    IdentificateurManager& id_man = IdentificateurManager::getInstance();

    QList<QTableWidgetItem*> items = ui->tableWidgetIDsVar->selectedItems();
    QList<QTableWidgetItem*> items_p = ui->tableWidgetIDsProg->selectedItems();

    if (!items.empty()) {
        QString str_item = items[0]->text();
        id_man.forgetIdentificateur(str_item);
    }
    else if (!items_p.empty()) {
        QString str_item_prog = items_p[0]->text();
        id_man.forgetIdentificateur(str_item_prog);
    }

    refreshIDs();
}

const QList<QTableWidgetItem*> MainWindow::getClickedTableWidgetIDsVar() const {
    QList<QTableWidgetItem*> items = ui->tableWidgetIDsVar->selectedItems();
    return items;
}

const QList<QTableWidgetItem*> MainWindow::getClickedTableWidgetIDsProg() const {
    QList<QTableWidgetItem*> items_p = ui->tableWidgetIDsProg->selectedItems();
    return items_p;
}

// A FINIR !!
void MainWindow::on_pButEditSettings_clicked(){
    IdentificateurManager& id_man = IdentificateurManager::getInstance();

    QList<QTableWidgetItem*> items = ui->tableWidgetIDsVar->selectedItems();
    QList<QTableWidgetItem*> items_p = ui->tableWidgetIDsProg->selectedItems();


    if (!items.empty()) {
        QString str_item = items[0]->text();
        DialogEdit* fenetreEdit = new DialogEdit(this, str_item);
        fenetreEdit->setTextSaisie(id_man.getLitteraleVar(str_item));
        fenetreEdit->exec();
    }
    else if (!items_p.empty()) {
        QString str_item_prog = items_p[0]->text();
        DialogEdit* fenetreEdit = new DialogEdit(this, str_item_prog);
        fenetreEdit->setTextSaisie(id_man.getLitteraleProg(str_item_prog));
        fenetreEdit->exec();
    }
    else {
        QApplication::beep();
    }
    refreshIDs();
}

void MainWindow::on_pButLastops_clicked(){
    QStringList list_str;
    list_str << Pile::lastOpname;
    Controleur::getInstance().commande(list_str);
}

void MainWindow::on_pButLastargs_clicked(){
    while(!Pile::argsHistory.empty()){
        Pile::getInstance().push(Pile::argsHistory.takeFirst());
    }
}

void MainWindow::on_pButRe_clicked(){
    QStringList str_list;
    str_list.push_back("RE");
    Controleur::getInstance().commande(str_list);
}

void MainWindow::on_pButIm_clicked(){
    QStringList str_list;
    str_list.push_back("IM");
    Controleur::getInstance().commande(str_list);
}

void MainWindow::on_pButDivEnt_clicked(){
    QStringList str_list;
    str_list.push_back("DIV");
    Controleur::getInstance().commande(str_list);
}

void MainWindow::on_pButMod_clicked(){
    QStringList str_list;
    str_list.push_back("MOD");
    Controleur::getInstance().commande(str_list);
}

void MainWindow::on_pButSupEgal_clicked(){
    QStringList str_list;
    str_list.push_back(">=");
    Controleur::getInstance().commande(str_list);
}

void MainWindow::on_pButInfEgal_clicked(){
    QStringList str_list;
    str_list.push_back("<=");
    Controleur::getInstance().commande(str_list);
}
