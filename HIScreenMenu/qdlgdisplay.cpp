#include "qdlgdisplay.h"
#include "ui_QDlgDisplay.h"
#include <QPainter>

QDlgDisplay::QDlgDisplay(QWidget *parent) : QDialog(parent), ui(new Ui::QDlgDisplay)
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
}

void QDlgDisplay::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(QBrush(QColor(29,59,140,220)));
    painter.drawRoundedRect(rect(), 5, 5);
}
