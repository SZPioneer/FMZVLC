#include "qmyuislot.h"

QMyUISlot* QMyUISlot::s_pInst       = NULL;
QMyUISlot::QMyUISlot(QObject *parent) : QObject(parent)
{
}

int QMyUISlot::onClickZoomAdd()
{
    m_iZoomStep++;
    if( m_iZoomStep >= 5 ){
        m_iZoomStep     = 5;
    }
    return m_iZoomStep;
}

int QMyUISlot::onClickZoomMinus()
{
    m_iZoomStep--;
    if( m_iZoomStep <=0 ){
        m_iZoomStep     = 0;
    }
    return m_iZoomStep;
}
