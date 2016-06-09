#include <QtGui>
#include <QApplication>
#include <QDesktopWidget>
#include <myWindow.h>

int main (int argc,char **argv)
{
	QApplication app(argc,argv);

	//Dimensioni dello schermo
	QDesktopWidget ws;
	int screenWidth=(ws.screen()->width())/2-400;
	int screenHeight=(ws.screen()->height())/2-300;
	
	//Apro la finiestra
	MyWindow w;
	w.setWindowTitle("IMAGE GALLERY");
	w.setGeometry(screenWidth,screenHeight,800,600);
	//w.setFixedSize(800,600);
	w.show();	
	return app.exec();
}
