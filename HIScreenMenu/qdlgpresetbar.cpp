#include "qdlgpresetbar.h"
#include "ui_Qdlgpresetbar.h"
#include <QPainter>

QDlgPresetBar::QDlgPresetBar(QWidget *parent) : QDialog(parent), ui(new Ui::QDlgPresetBar)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Dialog|Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    this->setWindowOpacity(1);
    this->setAttribute(Qt::WA_TranslucentBackground);
    setFixedSize(180,40);

    ui->comboBox_preset->addItem("无");
    ui->comboBox_preset->addItem("有");
    ui->comboBox_preset->setCurrentIndex(0);
}

void QDlgPresetBar::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(QBrush(QColor(29,59,140,220)));
    painter.drawRoundedRect(rect(), 5, 5);
}

void QDlgPresetBar::resizeEvent(QResizeEvent *event)
{
    QRect       rcCom       = ui->comboBox_preset->rect();
    ui->comboBox_preset->move((width()-rcCom.width())/2, (height()-rcCom.height())/2);
}
