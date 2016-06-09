#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QDebug>
#include <QWidget>
#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QString>

class Dialog : public QDialog
{
	Q_OBJECT

	public:
		Dialog();

	private:
		//Creo il container, il box verticale e gli oggetti che mi servono
		QVBoxLayout *contenitoreVerticale;
		QLabel *nomeNuovoCaso,*nomePathLavoro,*nomePathRicerca;
		QLineEdit *insNuovoCaso,*insPathLavoro,*insPathRicerca;
		QPushButton *creaNuovoCaso,*chiudiNuovoCaso;

	private slots:
		//Alla pressione del nuovo caso
		void creaIlNuovoCaso();
		void chiudiDialog();

	signals:
		//Segnale per inviare i dati
		void invioDatiAlMain(QString,QString,QString);		
};

#endif
