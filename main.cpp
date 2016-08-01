
#include <QApplication>
#include "logmanager.h"
#include "Logger.h"
//#include "widget.h"
#include "./view/mainwidget.h"
#include "commandlinemanager.h"
#include <QRect>
#include <QPoint>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LogManager::instance()->debug_log_console_on();
    a.setOrganizationName("deepin");
    a.setApplicationName(QObject::tr("Deepin Shortcut Viewer"));
    a.setApplicationVersion("v1.0");
    CommandLineManager cmdManager;
    cmdManager.process(a);

    QString dir = cmdManager.dir();
    QPoint pos = cmdManager.pos();

    MainWidget w(0,dir);
    pos-=QPoint(w.width()/2,w.height()/2);

    w.show();
    w.move(pos);

    return a.exec();
}
