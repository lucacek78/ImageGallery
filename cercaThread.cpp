#include <cercaThread.h>

CercaThread::CercaThread(bool b,QString test):Stop(b)
{
	//Costruttore del thread di ricerca della immagini
	stringaTest=test;
}

/*
CercaThread::CercaThread(QString test)
{
	stringaTest=test;
	qDebug()<<"Stringa: "<<stringaTest;
}
*/

void CercaThread::run()
{
	int contatore=1;
	qDebug()<<"Stringa: "<<stringaTest;
	qDebug()<<"Caso Thread: "<<this->TCaso<<" Lavoro Thread: "<<this->TLavoro<<" Ricerca Thread: "<<this->TRicerca;
	/*
	A thread avviato cerco le immagini partendo da PATH data
	*/
	// Variabili di lavoro: TCaso, TLavoro, TRicerca
	QDirIterator dirRicorsivo(this->TRicerca,QDirIterator::Subdirectories);
	while(dirRicorsivo.hasNext()){
		QMutex mutex;
		mutex.lock();
		if(this->Stop)
		{
			break;
		}
		mutex.unlock();
		QString nomeFile=dirRicorsivo.next();
		qDebug()<<"Nome file: "<<nomeFile;
		//Apro il file e mi salvo i primi 12 byte
		QFile file(nomeFile);
		if(!file.open(QIODevice::ReadOnly))
		{
			qDebug()<<"ERRORE: non è stato possibile leggere il file";
		}else{
			QByteArray filebyte=file.read(12);
			QString header=QString(filebyte.toHex());
			qDebug()<<"12 byte: "<<header;
                        //QFile headerFile("C:\\Users\\cecchetti\\Documents\\Programmi\\QT\\ImageGallery\\headers.csv");
                        QFile headerFile("../../QT/ImageGallery/headers.csv");
			if(!headerFile.open(QIODevice::ReadOnly | QIODevice::Text))
			{
				qDebug()<<"ERRORE: file header di controllo non presente";
			}else{
				QTextStream readFile(&headerFile);
				while(!readFile.atEnd())
				{
					QString linea=readFile.readLine();
					QStringList listaLinea=linea.split(";");
					if(header.contains(listaLinea[1],Qt::CaseInsensitive))
					{
						qDebug()<<contatore<<") TROVATO FILE NEL CSV!";
						contatore++;
						emit fotoTrovata(nomeFile);
                                                msleep(200); //Rallento il processo
					}
				}					
			}
			headerFile.close();
		}		
	}			
}
