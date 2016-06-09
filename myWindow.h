#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QScrollArea>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QImage>
#include <QList>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <cercaThread.h>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <dialog.h>
#include <QCloseEvent>
#include <QEvent>
#include <QDir>
#include <QFileInfo>
#include <QDateTime>

class  MyWindow : public QMainWindow
{
	Q_OBJECT

	public:
		MyWindow();
		CercaThread *ct;
		Dialog *wd;
		QString caso,lavoro,ricerca;
		int indiceInsListaLabel,indiceRiga,indiceColonna,contatoreImg;
		QList<QLabel *> insListaLabel;

	private:
		QWidget *window,*scrollWindow;
		QVBoxLayout *mioLayout;
		QGridLayout *scrollLayout;
		QScrollArea *miaScrollArea;
		QPushButton *startThread,*chiudiApp;
		QMenu *fileMenu;
		QAction *creaCaso;
		QAction *esciCaso;
		QMenu *cercaMenu;
		QAction *iniziaCerca;
		QAction *fermaCerca;
		QDir *pathLavoro;
	
	private slots:
		void cercaImmagini();
		void fermaCercaImmagini();
		void nuovoCaso();
		void esci();

	public slots:
		void inserisciFotoTrovata(QString n);
		void datiRicevutiDaDialog(QString a,QString b,QString c);		

	protected:
		void closeEvent(QCloseEvent *);
};

#endif
