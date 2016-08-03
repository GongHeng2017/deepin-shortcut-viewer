
#include <QApplication>
#include "logmanager.h"
#include "Logger.h"
//#include "widget.h"
#include "./view/mainwidget.h"
#include "commandlinemanager.h"
#include <QRect>
#include <QPoint>
#include <QFile>
#include <QLocale>
#include "singleapplication.h"

int main(int argc, char *argv[])
{
    //Singlentan process
    SingleApplication app(argc,argv);

    //Logger handle
    LogManager::instance()->debug_log_console_on();

    app.setOrganizationName("deepin");
    app.setApplicationName(QObject::tr("Deepin Shortcut Viewer"));
    app.setApplicationVersion("v1.0");

    //Command manager
    CommandLineManager cmdManager;
    cmdManager.process(app);

    MainWidget *w;

    QString uniqueKey = app.applicationName();
    bool isSingleApplication = app.setSingleInstance(uniqueKey);

    //Handle singlelentan process communications;
    if(isSingleApplication){
        QString dir = cmdManager.dir();
        if(dir=="")
            return 0;

        dir = "/usr/share/deepin-shortcut-viewer/"+dir+"/"+QLocale::system().name()+"/shortcut.txt";
        QPoint pos = cmdManager.pos();

        w=new MainWidget(0,dir);
        pos-=QPoint(w->width()/2,w->height()/2);
        w->move(pos);
        w->show();
        return app.exec();
    }
    else{
        app.newClientProcess(uniqueKey,"close");
        return 0;
    }

}
