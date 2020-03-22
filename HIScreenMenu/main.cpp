#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include "xmlconfig.h"
#include <QThread>

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
    QApplication a(argc, argv);

    CommonHelper::setStyle(":/style.qss");
    QThread     thread;
    XmlConfig::GetInstance()->moveToThread(&thread);
    thread.start();

    MainWindow w;
    w.show();
    return a.exec();
}
