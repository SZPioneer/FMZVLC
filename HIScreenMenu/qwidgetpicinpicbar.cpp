#include "qwidgetpicinpicbar.h"
#include "ui_qwidgetpicinpicbar.h"
#include "xmlconfig.h"
#include <QPainter>

#define COLOR_ITEM_SELECT       QColor(244,234,42)
QWidgetPicInPicbar::QWidgetPicInPicbar(QWidget *parent) : QMyWidget(parent), ui(new Ui::QWidgetPicInPicbar)
{
    ui->setupUi(this);

    //setWindowFlags(Qt::Dialog|Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
}

void QWidgetPicInPicbar::setFocusOn(bool bFocus)
{
    QMyWidget::setFocusOn(bFocus);
    update();
}

void QWidgetPicInPicbar::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(QBrush(QColor(29,59,140,220)));
    painter.drawRoundedRect(rect(), 5, 5);

    if( m_bFocusOn ){
        QPen        pen(COLOR_ITEM_SELECT);
        painter.setPen(pen);
        painter.drawRect(rect());
    }
}

void QWidgetPicInPicbar::onWheel(QObject* pObj,int iStep)
{
    if( pObj != this ){
        return;
    }

    if( iStep > 0 ){
        m_iStepPos--;
        if( m_iStepPos < 0 ){
            m_iStepPos      = -1;
        }
    }else{
        m_iStepPos++;
        if( m_iStepPos >= m_iStepMax ){
            m_iStepPos      = m_iStepMax-1;
        }
    }

    QString         qstrSel     = m_bFocusOn ? "QWidget{background-color:rgb(244,234,42);}" : "QWidget{background-color:rgb(255,255,255);}";
    QString         qstrUnSel   = "QWidget{background-color:rgb(161,161,161);}";
    if( m_iStepPos == 3 ){
        ui->widget_inPic4->setStyleSheet(qstrSel);
        ui->widget_inPic1->setStyleSheet(qstrUnSel);
        ui->widget_inPic2->setStyleSheet(qstrUnSel);
        ui->widget_inPic3->setStyleSheet(qstrUnSel);
    }else if( m_iStepPos == 0 ){
        ui->widget_inPic1->setStyleSheet(qstrSel);
        ui->widget_inPic4->setStyleSheet(qstrUnSel);
        ui->widget_inPic2->setStyleSheet(qstrUnSel);
        ui->widget_inPic3->setStyleSheet(qstrUnSel);
    }else if( m_iStepPos == 1 ){
        ui->widget_inPic2->setStyleSheet(qstrSel);
        ui->widget_inPic1->setStyleSheet(qstrUnSel);
        ui->widget_inPic4->setStyleSheet(qstrUnSel);
        ui->widget_inPic3->setStyleSheet(qstrUnSel);
    }else if( m_iStepPos == 2 ){
        ui->widget_inPic3->setStyleSheet(qstrSel);
        ui->widget_inPic1->setStyleSheet(qstrUnSel);
        ui->widget_inPic2->setStyleSheet(qstrUnSel);
        ui->widget_inPic4->setStyleSheet(qstrUnSel);
    }
}

void QWidgetPicInPicbar::onKeyEnter(QObject* pObj)
{
    if( pObj != this ){
        return;
    }

    XmlConfig::GetInstance()->setAppEventObj(parent());

    QString         qstrSel     = m_bFocusOn ? "QWidget{background-color:rgb(244,234,42);}" : "QWidget{background-color:rgb(255,255,255);}";
    QString         qstrUnSel   = "QWidget{background-color:rgb(161,161,161);}";
    if( m_iStepPos == 3 ){
        ui->widget_inPic4->setStyleSheet(qstrSel);
        ui->widget_inPic1->setStyleSheet(qstrUnSel);
        ui->widget_inPic2->setStyleSheet(qstrUnSel);
        ui->widget_inPic3->setStyleSheet(qstrUnSel);
    }else if( m_iStepPos == 0 ){
        ui->widget_inPic1->setStyleSheet(qstrSel);
        ui->widget_inPic4->setStyleSheet(qstrUnSel);
        ui->widget_inPic2->setStyleSheet(qstrUnSel);
        ui->widget_inPic3->setStyleSheet(qstrUnSel);
    }else if( m_iStepPos == 1 ){
        ui->widget_inPic2->setStyleSheet(qstrSel);
        ui->widget_inPic1->setStyleSheet(qstrUnSel);
        ui->widget_inPic4->setStyleSheet(qstrUnSel);
        ui->widget_inPic3->setStyleSheet(qstrUnSel);
    }else if( m_iStepPos == 2 ){
        ui->widget_inPic3->setStyleSheet(qstrSel);
        ui->widget_inPic1->setStyleSheet(qstrUnSel);
        ui->widget_inPic2->setStyleSheet(qstrUnSel);
        ui->widget_inPic4->setStyleSheet(qstrUnSel);
    }

}
