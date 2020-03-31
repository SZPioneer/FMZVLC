#include "globalapplication.h"
#include <QEvent>
#include <QDebug>
#include <QWheelEvent>
#include "xmlconfig.h"

#define QDBG qDebug()<<__FILE__<<__FUNCTION__<<__LINE__
GlobalApplication::GlobalApplication(int &argc, char **argv) : QApplication(argc,argv)
{

}

bool GlobalApplication::notify(QObject *obj, QEvent *e)
{
    if( e->type() == QEvent::Wheel ){
        onWheel(XmlConfig::GetInstance()->m_pEventObj, e);
        return false;
    }else if( e->type() == QEvent::KeyPress ){
        if( onKey(XmlConfig::GetInstance()->m_pEventObj, e) ){
            return false;
        }
    }
    if( e->type() == QEvent::Wheel || e->type() == QEvent::KeyPress || e->type() == QEvent::MouseButtonPress )  {
        //QDBG << e->type();
    }

    return QApplication::notify(obj,e);

//    if( m_pEventObject == NULL ){
//        return QApplication::notify(obj,e);
//    }else{
//        return QApplication::notify(m_pEventObject,e);
//    }
}

void GlobalApplication::onWheel(QObject* pObj, QEvent* e)
{
    QWheelEvent*    pWheelEvt       = (QWheelEvent*)e;
    QPoint          numDegrees      = pWheelEvt->angleDelta() / 8;

    if (!numDegrees.isNull()) {
        QPoint      numSteps    = numDegrees / 15;
        qDebug()<<"numSteps:"<<numSteps<<pObj;
        emit XmlConfig::GetInstance()->notifyWheel(pObj, numSteps.y());
    }


}

bool GlobalApplication::onKey(QObject* pObj,QEvent* e)
{
    QKeyEvent*      pKeyEvent       = (QKeyEvent*)e;

    if( pKeyEvent->key() == Qt::Key_Return || pKeyEvent->key() == Qt::Key_Enter ){
        emit XmlConfig::GetInstance()->notifyKeyEnter(pObj);
        return true;
    }
    return false;
}
