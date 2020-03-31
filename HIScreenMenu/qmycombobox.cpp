#include "qmycombobox.h"
#include <QDebug>
#include "xmlconfig.h"
#include <QAbstractItemView>

QMyComboBox::QMyComboBox(QWidget *parent) : QComboBox(parent)
{
    connect(XmlConfig::GetInstance(), SIGNAL(notifyWheel(QObject*,int)), this, SLOT(onWheel(QObject*,int)));
    connect(XmlConfig::GetInstance(), SIGNAL(notifyKeyEnter(QObject*)), this, SLOT(onKeyEnter(QObject*)));

}

void QMyComboBox::setFocusOn(bool bFocus)
{
    m_bFocusOn      = bFocus;
    if( bFocus ){
        showPopup();
    }
}

void QMyComboBox::onWheel(QObject* pObj,int iStep)
{
    if( pObj != this ){
        return;
    }

    int     iCurIdx     = currentIndex();
    if( iStep > 0 ){
        iCurIdx--;
        if( iCurIdx <= 0 ){
            iCurIdx     = 0;
        }
    }else{
        iCurIdx++;
        if( iCurIdx >= count() ){
            iCurIdx     = count() - 1;
        }
    }

    QAbstractItemView*      pView       = view();
    QAbstractItemModel*     pModel      = pView->model();
    QModelIndex             index       = pModel->index(iCurIdx, 0);
    pView->setCurrentIndex(index);
    setCurrentIndex(iCurIdx);

    qDebug()<<"iCurIdx:"<<iCurIdx<<"count:"<<count();
}

void QMyComboBox::onKeyEnter(QObject* pObj)
{
    if( pObj != this ){
        return;
    }

    XmlConfig::GetInstance()->setAppEventObj(m_pMyParent, false, true);
    hidePopup();
}
