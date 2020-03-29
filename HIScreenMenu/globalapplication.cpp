#include "globalapplication.h"
#include <QEvent>
#include <QDebug>

#define QDBG qDebug()<<__FILE__<<__FUNCTION__<<__LINE__
GlobalApplication::GlobalApplication(int &argc, char **argv) : QApplication(argc,argv)
{

}

bool GlobalApplication::eventFilter(QObject *obj, QEvent *e)
{
    if( e->type() == QEvent::Wheel || e->type() == QEvent::KeyPress || e->type() == QEvent::MouseButtonPress ||  e->type() == QEvent::MouseMove )  {
        QDBG << e->type();
    }

    return QApplication::eventFilter(obj,e);
}

bool GlobalApplication::notify(QObject *obj, QEvent *e)
{
    if( e->type() == QEvent::Wheel || e->type() == QEvent::KeyPress || e->type() == QEvent::MouseButtonPress ||  e->type() == QEvent::MouseMove )  {
        QDBG << e->type();
    }
    return QApplication::notify(obj,e);
}
