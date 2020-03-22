#include "qdlgenhancebar.h"
#include "ui_qdlgenhancebar.h"
#include <QPainter>

QDlgEnhanceBar::QDlgEnhanceBar(QWidget *parent) : QDialog(parent), ui(new Ui::QDlgEnhancebar)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Dialog|Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    this->setWindowOpacity(1);
    this->setAttribute(Qt::WA_TranslucentBackground);
    setFixedSize(180,40);

    ui->comboBox_enhance->addItem("CLARA1");
    ui->comboBox_enhance->addItem("CLARA2");
    ui->comboBox_enhance->setCurrentIndex(0);
}

void QDlgEnhanceBar::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(QBrush(QColor(29,59,140,220)));
    painter.drawRoundedRect(rect(), 5, 5);
}

void QDlgEnhanceBar::resizeEvent(QResizeEvent *event)
{
    QRect       rcCom       = ui->comboBox_enhance->rect();
    ui->comboBox_enhance->move((width()-rcCom.width())/2, (height()-rcCom.height())/2);
}
