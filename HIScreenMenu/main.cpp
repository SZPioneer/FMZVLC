#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include "xmlconfig.h"
#include <QThread>
#include "globalapplication.h"

class CommonHelper
{
public:
    static void setStyle(const QString &style) {
        QFile qss(style);
        qss.open(QFile::ReadOnly);
        qApp->setStyleSheet(qss.readAll());
        qss.close();
    }
};

int main(int argc, char *argv[])
{
    GlobalApplication a(argc, argv);

    CommonHelper::setStyle(":/style.qss");
    QThread     thread;
    XmlConfig::GetInstance()->moveToThread(&thread);
    thread.start();

    MainWindow w;
    a.installNativeEventFilter(&w);
    w.show();
    a.exec();
    thread.terminate();

    return 0;
}
