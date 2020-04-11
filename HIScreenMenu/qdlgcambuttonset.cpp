#include "qdlgcambuttonset.h"
#include "ui_qdlgcambuttonset.h"
#include <QPainter>
#include "xmlconfig.h"

#define COLOR_ITEM_SELECT       QColor(244,234,42)
QDlgCamButtonSet::QDlgCamButtonSet(QWidget *parent) : QMyWidget(parent), ui(new Ui::QDlgCamButtonSet)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Dialog|Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    this->setWindowOpacity(1);
    this->setAttribute(Qt::WA_TranslucentBackground);
    //setFixedSize(320,240);

    MapCamButtonSets        mapSets     = XmlConfig::GetInstance()->m_mapCamBtnSets;
    for(MapCamButtonSets::iterator iter=mapSets.begin();iter!=mapSets.end();iter++){
        ui->comboBox_left1->addItem(iter.value(), QVariant(iter.key()));
        ui->comboBox_left2->addItem(iter.value(), QVariant(iter.key()));
        ui->comboBox_right1->addItem(iter.value(), QVariant(iter.key()));
        ui->comboBox_right2->addItem(iter.value(), QVariant(iter.key()));

    }
    ui->comboBox_left1->setCurrentIndex(XmlConfig::GetInstance()->m_stMouseBtnConfig.iLeftShortPress);
    ui->comboBox_left2->setCurrentIndex(XmlConfig::GetInstance()->m_stMouseBtnConfig.iLeftLongPress);
    ui->comboBox_right1->setCurrentIndex(XmlConfig::GetInstance()->m_stMouseBtnConfig.iRightShortPress);
    ui->comboBox_right2->setCurrentIndex(XmlConfig::GetInstance()->m_stMouseBtnConfig.iRightLongPress);
    memcpy(&m_stMouseBtnSet, &(XmlConfig::GetInstance()->m_stMouseBtnConfig), sizeof(ST_MouseButtonSet));

    ui->comboBox_left1->setMyParent(this);
    ui->comboBox_left2->setMyParent(this);
    ui->comboBox_right1->setMyParent(this);
    ui->comboBox_right2->setMyParent(this);

    ui->label_userMenu->hide();
    ui->label_set->hide();
    ui->label_exit->hide();


}

void QDlgCamButtonSet::setFocusOn(bool bFocus)
{
    qDebug()<<"xxxyy "<<bFocus;
    QMyWidget::setFocusOn(bFocus);
    update();
}

void QDlgCamButtonSet::paintEvent(QPaintEvent *event)
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
            rcItem          = ui->comboBox_left1->rect();
            pt1             = ui->comboBox_left1->mapTo(this, QPoint(rcItem.left(),rcItem.top()));
            pt2             = ui->comboBox_left1->mapTo(this, QPoint(rcItem.right(),rcItem.bottom()));
        }else if( m_iStepPos == 1 ){
            rcItem          = ui->comboBox_left2->rect();
            pt1             = ui->comboBox_left2->mapTo(this, QPoint(rcItem.left(),rcItem.top()));
            pt2             = ui->comboBox_left2->mapTo(this, QPoint(rcItem.right(),rcItem.bottom()));
        }else if( m_iStepPos == 2 ){
            rcItem          = ui->comboBox_right1->rect();
            pt1             = ui->comboBox_right1->mapTo(this, QPoint(rcItem.left(),rcItem.top()));
            pt2             = ui->comboBox_right1->mapTo(this, QPoint(rcItem.right(),rcItem.bottom()));
        }else if( m_iStepPos == 3 ){
            rcItem          = ui->comboBox_right2->rect();
            pt1             = ui->comboBox_right2->mapTo(this, QPoint(rcItem.left(),rcItem.top()));
            pt2             = ui->comboBox_right2->mapTo(this, QPoint(rcItem.right(),rcItem.bottom()));
        }else if( m_iStepPos == 4 ){
            rcItem          = ui->label_userMenu->rect();
            pt1             = ui->label_userMenu->mapTo(this, QPoint(rcItem.left(),rcItem.top()));
            pt2             = ui->label_userMenu->mapTo(this, QPoint(rcItem.right(),rcItem.bottom()));
        }else if( m_iStepPos == 5 ){
            rcItem          = ui->label_set->rect();
            pt1             = ui->label_set->mapTo(this, QPoint(rcItem.left(),rcItem.top()));
            pt2             = ui->label_set->mapTo(this, QPoint(rcItem.right(),rcItem.bottom()));
        }else if( m_iStepPos == 6 ){
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

void QDlgCamButtonSet::on_comboBox_left1_currentIndexChanged(int index)
{
    m_stMouseBtnSet.iLeftShortPress        = index;
}

void QDlgCamButtonSet::on_comboBox_left2_currentIndexChanged(int index)
{
    m_stMouseBtnSet.iLeftLongPress        = index;
}

void QDlgCamButtonSet::on_comboBox_right1_currentIndexChanged(int index)
{
    m_stMouseBtnSet.iRightShortPress        = index;
}

void QDlgCamButtonSet::on_comboBox_right2_currentIndexChanged(int index)
{
    m_stMouseBtnSet.iRightLongPress        = index;
}

void QDlgCamButtonSet::onWheel(QObject* pObj,int iStep)
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

void QDlgCamButtonSet::onKeyEnter(QObject* pObj)
{
    if( pObj != this ){
        return;
    }

    if( m_iStepPos == 6 ){
        emit XmlConfig::GetInstance()->notifyEnterToolbar(this);
    }else if( m_iStepPos == 0 ){
        qDebug()<<"lef1:"<<ui->comboBox_left1;
        XmlConfig::GetInstance()->setAppEventObj(ui->comboBox_left1, true, false);
    }else if( m_iStepPos == 1 ){
        XmlConfig::GetInstance()->setAppEventObj(ui->comboBox_left2, true, false);
    }else if( m_iStepPos == 2 ){
        XmlConfig::GetInstance()->setAppEventObj(ui->comboBox_right1, true, false);
    }else if( m_iStepPos == 3 ){
        XmlConfig::GetInstance()->setAppEventObj(ui->comboBox_right2, true, false);
    }else if( m_iStepPos == 4 ){

    }else if( m_iStepPos == 5 ){
        onSet();
    }
}

void QDlgCamButtonSet::onSet()
{

}

void QDlgCamButtonSet::on_pushButton_userMenu_clicked()
{

}

void QDlgCamButtonSet::on_pushButton_set_clicked()
{
    onSet();
}

void QDlgCamButtonSet::on_pushButton_exit_clicked()
{
    emit XmlConfig::GetInstance()->notifyEnterToolbar(this);
}
