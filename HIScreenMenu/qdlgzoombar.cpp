#include "qdlgzoombar.h"
#include <QPainter>
#include "ui_qdlgzoombar.h"
#include "xmlconfig.h"

QDlgZoombar::QDlgZoombar(QWidget *parent) : QDialog(parent), ui(new Ui::QDlgZoombar)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Dialog|Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    this->setWindowOpacity(1);
    this->setAttribute(Qt::WA_TranslucentBackground);
    setFixedSize(210,40);

    ui->pushButton_max->setFixedSize(30,30);
    ui->pushButton_min->setFixedSize(30,30);
    ui->pushButton_1->setFixedSize(24,24);
    ui->pushButton_2->setFixedSize(24,24);
    ui->pushButton_3->setFixedSize(24,24);
    ui->pushButton_4->setFixedSize(24,24);
    ui->pushButton_5->setFixedSize(24,24);

    m_pBtn[0]       = ui->pushButton_1;
    m_pBtn[1]       = ui->pushButton_2;
    m_pBtn[2]       = ui->pushButton_3;
    m_pBtn[3]       = ui->pushButton_4;
    m_pBtn[4]       = ui->pushButton_5;
    for(int i=0;i<5;i++){
        m_pBtn[i]->setStyleSheet("border-image: url(:/img/zoomUnSel.png)");
    }

    int     iZoomVal        = XmlConfig::GetInstance()->m_iZoomStep;
    for(int i=0;i<iZoomVal;i++){
        m_pBtn[i]->setStyleSheet("border-image: url(:/img/zoomSel.png)");
    }

    connect(XmlConfig::GetInstance(), SIGNAL(changeZoom(int)), this, SLOT(onChangeZoom(int)));
}

void QDlgZoombar::onChangeZoom(int iZoom)
{
    for(int i=0;i<iZoom;i++){
        m_pBtn[i]->setStyleSheet("border-image: url(:/img/zoomSel.png)");
    }
    for(int i=iZoom;i<5;i++){
        m_pBtn[i]->setStyleSheet("border-image: url(:/img/zoomUnSel.png)");
    }
}

void QDlgZoombar::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(QBrush(QColor(29,59,140,220)));
    painter.drawRoundedRect(rect(), 5, 5);
}

void QDlgZoombar::resizeEvent(QResizeEvent *event)
{
    int     ixPos       = 5;
    QRect   rcBtn;

    rcBtn       = ui->pushButton_min->rect();
    ui->pushButton_min->move(ixPos, (height()-rcBtn.height())/2);
    ixPos       += (rcBtn.width() + 3);

    rcBtn       = ui->pushButton_1->rect();
    ui->pushButton_1->move(ixPos, (height()-rcBtn.height())/2);
    ixPos       += (rcBtn.width() + 3);

    rcBtn       = ui->pushButton_2->rect();
    ui->pushButton_2->move(ixPos, (height()-rcBtn.height())/2);
    ixPos       += (rcBtn.width() + 3);

    rcBtn       = ui->pushButton_3->rect();
    ui->pushButton_3->move(ixPos, (height()-rcBtn.height())/2);
    ixPos       += (rcBtn.width() + 3);

    rcBtn       = ui->pushButton_4->rect();
    ui->pushButton_4->move(ixPos, (height()-rcBtn.height())/2);
    ixPos       += (rcBtn.width() + 3);

    rcBtn       = ui->pushButton_5->rect();
    ui->pushButton_5->move(ixPos, (height()-rcBtn.height())/2);
    ixPos       += (rcBtn.width() + 3);

    rcBtn       = ui->pushButton_max->rect();
    ui->pushButton_max->move(ixPos, (height()-rcBtn.height())/2);
    ixPos       += (rcBtn.width() + 3);
}

void QDlgZoombar::on_pushButton_min_clicked()
{
    XmlConfig::GetInstance()->onClickZoomMinus();
//    for(int i=0;i<iStep;i++){
//        m_pBtn[i]->setStyleSheet("border-image: url(:/img/zoomSel.png)");
//    }
//    for(int i=iStep;i<5;i++){
//        m_pBtn[i]->setStyleSheet("border-image: url(:/img/zoomUnSel.png)");
//    }
}

void QDlgZoombar::on_pushButton_max_clicked()
{
    XmlConfig::GetInstance()->onClickZoomAdd();
//    for(int i=0;i<iStep;i++){
//        m_pBtn[i]->setStyleSheet("border-image: url(:/img/zoomSel.png)");
//    }
//    for(int i=iStep;i<5;i++){
//        m_pBtn[i]->setStyleSheet("border-image: url(:/img/zoomUnSel.png)");
//    }
}
