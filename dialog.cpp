#include "dialog.h"

Dialog::Dialog()
{
	//Finestra di dialogo base
	contenitoreVerticale=new QVBoxLayout;
	nomeNuovoCaso=new QLabel("Inserire in nome del caso",this);
	insNuovoCaso=new QLineEdit(this);
	nomePathLavoro=new QLabel("Inserisci Path di lavoro",this);
	insPathLavoro=new QLineEdit(this);
	nomePathRicerca=new QLabel("Inserisci Path di ricerca",this);
	insPathRicerca=new QLineEdit(this);
	creaNuovoCaso=new QPushButton("CREA CASO",this);
	chiudiNuovoCaso=new QPushButton("CHIUDI",this);
	//Connessione dei tasti
	connect(creaNuovoCaso,SIGNAL(clicked()),this,SLOT(creaIlNuovoCaso()));
	connect(chiudiNuovoCaso,SIGNAL(clicked()),this,SLOT(chiudiDialog()));
	
	//Aggiungo i widget al container vertical
	contenitoreVerticale->addWidget(nomeNuovoCaso);
	contenitoreVerticale->addWidget(insNuovoCaso);
	contenitoreVerticale->addWidget(nomePathLavoro);
	contenitoreVerticale->addWidget(insPathLavoro);
	contenitoreVerticale->addWidget(nomePathRicerca);
	contenitoreVerticale->addWidget(insPathRicerca);
	contenitoreVerticale->addWidget(creaNuovoCaso);
	contenitoreVerticale->addWidget(chiudiNuovoCaso);

	//Imposto il layout della dialog
	setLayout(contenitoreVerticale);
}

void Dialog::creaIlNuovoCaso()
{
	//Emetto il segnale
	qDebug()<<"Crea il nuovo caso...";
	QString caso=insNuovoCaso->text();
	QString lavoro=insPathLavoro->text();
	QString ricerca=insPathRicerca->text();
	emit invioDatiAlMain(caso,lavoro,ricerca);
	//Chiudo la finiestra di dialogo....
	close();	
}

void Dialog::chiudiDialog()
{
	close();
}
