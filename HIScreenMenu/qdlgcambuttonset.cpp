#include "qdlgcambuttonset.h"
#include "ui_qdlgcambuttonset.h"
#include <QPainter>

QDlgCamButtonSet::QDlgCamButtonSet(QWidget *parent) : QDialog(parent), ui(new Ui::QDlgCamButtonSet)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Dialog|Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    this->setWindowOpacity(1);
    this->setAttribute(Qt::WA_TranslucentBackground);
    //setFixedSize(320,240);

    ui->comboBox_left1->addItem("无");
    ui->comboBox_left1->addItem("白平衡");
    ui->comboBox_left1->addItem("S成像技术");
    ui->comboBox_left1->setCurrentIndex(0);

    ui->comboBox_left2->addItem("无");
    ui->comboBox_left2->addItem("白平衡");
    ui->comboBox_left2->addItem("S成像技术");
    ui->comboBox_left2->setCurrentIndex(0);

    ui->comboBox_right1->addItem("无");
    ui->comboBox_right1->addItem("白平衡");
    ui->comboBox_right1->addItem("S成像技术");
    ui->comboBox_right1->setCurrentIndex(0);

    ui->comboBox_right2->addItem("无");
    ui->comboBox_right2->addItem("白平衡");
    ui->comboBox_right2->addItem("S成像技术");
    ui->comboBox_right2->setCurrentIndex(0);


}

void QDlgCamButtonSet::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(QBrush(QColor(29,59,140,220)));
    painter.drawRoundedRect(rect(), 5, 5);
}

void QDlgCamButtonSet::on_comboBox_left1_currentIndexChanged(int index)
{

}

void QDlgCamButtonSet::on_comboBox_left2_currentIndexChanged(int index)
{

}

void QDlgCamButtonSet::on_comboBox_right1_currentIndexChanged(int index)
{

}

void QDlgCamButtonSet::on_comboBox_right2_currentIndexChanged(int index)
{

}
