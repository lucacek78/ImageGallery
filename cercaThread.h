#ifndef CERCATHREAD_H
#define CERCATHREAD_H

#include <QThread>
#include <QMutex>
#include <QString>
#include <QDebug>
#include <QString>
#include <QDirIterator>
#include <QFile>

class CercaThread : public QThread
{
	Q_OBJECT

	public:
		CercaThread(bool b,QString test);
		//CercaThread(QString test);
		void run();
		bool Stop;
		QString TCaso,TLavoro,TRicerca;
		QString stringaTest;

	signals:
		void fotoTrovata(QString);
};

#endif
