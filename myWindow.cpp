#include <myWindow.h>
#include <cercaThread.h>
#include <dialog.h>

MyWindow::MyWindow()
{
	//CREAZIONE DEL MENU
	//Creazione delle azioni da eseguire nel menu
	creaCaso=new QAction("&Nuovo Caso",this);
	connect(creaCaso,SIGNAL(triggered()),this,SLOT(nuovoCaso()));
	esciCaso=new QAction("&Chiudi",this);
	connect(esciCaso,SIGNAL(triggered()),this,SLOT(esci()));
	iniziaCerca=new QAction("&Cerca",this);
	connect(iniziaCerca,SIGNAL(triggered()),this,SLOT(cercaImmagini()));
	fermaCerca=new QAction("&Ferma",this);
	connect(fermaCerca,SIGNAL(triggered()),this,SLOT(fermaCercaImmagini()));
	//Creazione della barra dei menu
	fileMenu=menuBar()->addMenu("&File");
	fileMenu->addAction(creaCaso);
	fileMenu->addAction(esciCaso);
	cercaMenu=menuBar()->addMenu("&Cerca");
	cercaMenu->addAction(iniziaCerca);
	iniziaCerca->setEnabled(false);
	cercaMenu->addAction(fermaCerca);
	fermaCerca->setEnabled(false);	

	//Finestra di Dialogo
	wd=new Dialog();
	wd->setWindowTitle("NUOVO CASO");
	//Commetto il segnale emesso dalla dialog che mi invia i dati
	connect(wd,SIGNAL(invioDatiAlMain(QString,QString,QString)),this,SLOT(datiRicevutiDaDialog(QString,QString,QString)));

	//INDICI
	indiceRiga=0;
	indiceColonna=0;
	indiceInsListaLabel=0;
	contatoreImg=0;
	
	//Main class della finiestra
	window=new QWidget;
	mioLayout=new QVBoxLayout;
	miaScrollArea=new QScrollArea;
	miaScrollArea->setBackgroundRole(QPalette::Dark);
	
	//WIDGET PER IL LAYOUT
	scrollWindow=new QWidget;
	//LAYOUT PER LO SCROLL
	scrollLayout=new QGridLayout;
	
	/*
	Creo l'oggetto Thread
	creando l'oggetto passo tutte le variabili che mi servono
	*/
	ct=new CercaThread(false,"PATH");
	//Connessione al segnale in arrivo dal thread
	connect(ct,SIGNAL(fotoTrovata(QString)),this,SLOT(inserisciFotoTrovata(QString)));
	
	//Imposto il layout
	//window->setLayout(mioLayout);
	//setCentralWidget(window);
}

void MyWindow::esci(void)
{
	//Lo stesso verra' richiamato dal menu
	ct->Stop=true;
	qDebug()<<"THREAD ARRESTATO...";
	wd->done(0);	
	close();
}

void MyWindow::cercaImmagini(void)
{
	//Lancio il thread per la ricerca delle immagini...
	//Come passo lo Stop passo anche i tre parametri per la ricerca
	qDebug()<<"Caso: "<<caso<<" Lavoro: "<<lavoro<<" Ricerca: "<<ricerca;
	//Passo le tre varibili al Thread...
	ct->TCaso=caso;
	ct->TLavoro=lavoro;
	ct->TRicerca=ricerca;
	QDir pathLavoro(lavoro),pathRicerca(ricerca);
	pathLavoro.setSorting(QDir::DirsFirst | QDir::Size);
	//Se entrambi le path esistono allora posso far partire il thread della ricerca
	if(pathLavoro.exists() && pathRicerca.exists())
	{		
		ct->Stop=false;
		ct->start();
	}else
	{
		qDebug()<<"ERRORE: Path non presenti...";
	}	
}

void MyWindow::inserisciFotoTrovata(QString n)
{
	qDebug()<<"---> SEGNALE: "<<n;
	/*
	Creo l'immagine da inserire nella label e lo metto in griglia
	*/
	QImage provaImg(n);
	//Immagini
	QImage provaImmagine=provaImg.scaled(400,400,Qt::KeepAspectRatio);
	insListaLabel<<new QLabel();
	insListaLabel.last()->setPixmap(QPixmap::fromImage(provaImmagine));
	scrollLayout->addWidget(insListaLabel.at(indiceInsListaLabel),indiceRiga,indiceColonna);
	//Info file
	QFileInfo infoNFile(n);
	QString informazioni="";
	if(infoNFile.isFile()==true)
	{
		informazioni="ID: "+QString::number(contatoreImg)+ \
			     "\nFile: "+infoNFile.fileName()+ \
			     "\nPath: "+infoNFile.path()+ \
			     "\nCreato: "+infoNFile.created().toString()+ \
			     "\nModificato: "+infoNFile.lastModified().toString()+ \
			     "\nLetto: "+infoNFile.lastRead().toString()+ \
			     "\nDimensione: "+QString::number(infoNFile.size())+" byte";
		qDebug()<<informazioni;
	}
	QLabel *infoLabel=new QLabel(informazioni);
	//infoLabel->setStyleSheet("background-color:grey");
	scrollLayout->addWidget(infoLabel,indiceRiga+1,indiceColonna);
	/*
	Il setWidget della scroll va sempre posto dopo l'add
	*/
	scrollWindow->setLayout(scrollLayout);
	miaScrollArea->setWidgetResizable(true);
	miaScrollArea->setWidget(scrollWindow);
	mioLayout->addWidget(miaScrollArea);
	window->setLayout(mioLayout);
	setCentralWidget(window);
	//Controllo indici della scrollarea
	contatoreImg++;
	indiceColonna++;
	if(indiceColonna==3)
	{
		indiceRiga=indiceRiga+2;
		indiceColonna=0;
	}
	indiceInsListaLabel++;
}

void MyWindow::nuovoCaso()
{
	//Richiamato dal menu...
	/*
	Viene richiesto:
		Nome caso
		Path di lavoro
		Path da analizzare
	*/
	wd->show();	
}

void MyWindow::fermaCercaImmagini()
{
	ct->Stop=true;
	qDebug()<<"THREAD ARRESTATO...";
}

void MyWindow::closeEvent(QCloseEvent *evt)
{
	if(evt->type()==QEvent::Close)
	{
		wd->done(0);
	}	
}

void MyWindow::datiRicevutiDaDialog(QString a,QString b,QString c)
{
	qDebug()<<"Dati passati da Dialog: "<<a<<" "<<b<<" "<<c;
	/*
	Creo il caso (directory) sulla path di lavoro inserita
	Controllo l'esistenza della directory nella quale cerco le immagini
	*/
	caso=a;
	lavoro=b;
	ricerca=c;
	//Creo la cartella con il nome di caso nella path di lavoro
	pathLavoro=new QDir(lavoro);
	if(pathLavoro->mkdir(caso)){
		qDebug()<<"Caso creato...";
		//Abilito il menu solo una volta creato il caso
		iniziaCerca->setEnabled(true);
		fermaCerca->setEnabled(true);
	}else{
		qDebug()<<"ERRORE: Caso non creato...";
	}
}
