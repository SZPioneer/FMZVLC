#include "qdlgdisplay.h"
#include "ui_QDlgDisplay.h"
#include <QPainter>
#include "xmlconfig.h"

#define COLOR_ITEM_SELECT       QColor(244,234,42)
QDlgDisplay::QDlgDisplay(QWidget *parent) : QMyWidget(parent), ui(new Ui::QDlgDisplay)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Dialog|Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    this->setWindowOpacity(1);
    this->setAttribute(Qt::WA_TranslucentBackground);

    ui->comboBox_main_pic->addItem("H3-LINK1");
    ui->comboBox_main_pic->addItem("H3-LINK2");
    ui->comboBox_main_pic->setCurrentIndex(0);

    ui->comboBox_subPic_inPic->addItem("无");
    ui->comboBox_subPic_inPic->addItem("有");
    ui->comboBox_subPic_inPic->setCurrentIndex(0);

    ui->comboBox_pointGrid->addItem("关闭");
    ui->comboBox_pointGrid->addItem("打开");
    ui->comboBox_pointGrid->setCurrentIndex(0);

    ui->comboBox_gridVis->addItem("100%");
    ui->comboBox_gridVis->addItem("50%");
    ui->comboBox_gridVis->setCurrentIndex(0);

    ui->comboBox_main_pic->setMyParent(this);
    ui->comboBox_subPic_inPic->setMyParent(this);
    ui->comboBox_pointGrid->setMyParent(this);
    ui->comboBox_gridVis->setMyParent(this);

    m_pPicInPicbar      = new QWidgetPicInPicbar(this);
    m_pPicInPicbar->move(ui->widget_inPic1->pos());
}

void QDlgDisplay::setFocusOn(bool bFocus)
{
    QMyWidget::setFocusOn(bFocus);
    update();
}

void QDlgDisplay::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(QBrush(QColor(29,59,140,220)));
    painter.drawRoundedRect(rect(), 5, 5);

    if( m_bFocusOn ){
        QRect       rcItem;
        QPoint      pt1;
        QPoint      pt2;

        if( m_iStepPos == 0 ){
            rcItem          = ui->label_left1->rect();
            pt1             = ui->label_left1->mapTo(this, QPoint(rcItem.left(),rcItem.top()));
            pt2             = ui->label_left1->mapTo(this, QPoint(rcItem.right(),rcItem.bottom()));
        }else if( m_iStepPos == 1 ){
            rcItem          = ui->label_left2->rect();
            pt1             = ui->label_left2->mapTo(this, QPoint(rcItem.left(),rcItem.top()));
            pt2             = ui->label_left2->mapTo(this, QPoint(rcItem.right(),rcItem.bottom()));
        }else if( m_iStepPos == 2 ){
            rcItem          = ui->label_right1->rect();
            pt1             = ui->label_right1->mapTo(this, QPoint(rcItem.left(),rcItem.top()));
            pt2             = ui->label_right1->mapTo(this, QPoint(rcItem.right(),rcItem.bottom()));
        }else if( m_iStepPos == 3 ){
            rcItem          = ui->label_right2->rect();
            pt1             = ui->label_right2->mapTo(this, QPoint(rcItem.left(),rcItem.top()));
            pt2             = ui->label_right2->mapTo(this, QPoint(rcItem.right(),rcItem.bottom()));
        }else if( m_iStepPos == 4 ){
            rcItem          = ui->label_center1->rect();
            pt1             = ui->label_center1->mapTo(this, QPoint(rcItem.left(),rcItem.top()));
            pt2             = ui->label_center1->mapTo(this, QPoint(rcItem.right(),rcItem.bottom()));
        }else if( m_iStepPos == 5 ){
            rcItem          = ui->label_exit->rect();
            pt1             = ui->label_exit->mapTo(this, QPoint(rcItem.left(),rcItem.top()));
            pt2             = ui->label_exit->mapTo(this, QPoint(rcItem.right(),rcItem.bottom()));
        }
        rcItem.setLeft(0);
        rcItem.setRight(width());
        rcItem.setTop(pt1.y()-5);
        rcItem.setBottom(pt2.y()+5);
        painter.fillRect(rcItem, COLOR_ITEM_SELECT);
    }else{

    }
}

void QDlgDisplay::onWheel(QObject* pObj,int iStep)
{
    if( pObj != this ){
        return;
    }

    if( iStep > 0 ){
        m_iStepPos--;
        if( m_iStepPos <= 0 ){
            m_iStepPos      = 0;
        }
    }else{
        m_iStepPos++;
        if( m_iStepPos >= m_iStepMax ){
            m_iStepPos      = m_iStepMax-1;
        }
    }
    update();
}

void QDlgDisplay::onKeyEnter(QObject* pObj)
{
    if( pObj != this ){
        return;
    }

    if( m_iStepPos == 5 ){
        emit XmlConfig::GetInstance()->notifyEnterToolbar(this);
    }else if( m_iStepPos == 0 ){
        XmlConfig::GetInstance()->setAppEventObj(ui->comboBox_main_pic, true, false);
    }else if( m_iStepPos == 1 ){
        XmlConfig::GetInstance()->setAppEventObj(ui->comboBox_subPic_inPic, true, false);
    }else if( m_iStepPos == 2 ){
        XmlConfig::GetInstance()->setAppEventObj(m_pPicInPicbar);
        //XmlConfig::GetInstance()->setAppEventObj(ui->label_right1);
    }else if( m_iStepPos == 3 ){
        XmlConfig::GetInstance()->setAppEventObj(ui->comboBox_pointGrid, true, false);
    }else if( m_iStepPos == 4 ){
        XmlConfig::GetInstance()->setAppEventObj(ui->comboBox_gridVis, true, false);
    }
}
