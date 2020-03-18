#include "qdlgzoombar.h"
#include <QPainter>
#include "ui_qdlgzoombar.h"

QDlgZoombar::QDlgZoombar(QWidget *parent) : QDialog(parent), ui(new Ui::QDlgZoombar)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Dialog|Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    this->setWindowOpacity(1);
    this->setAttribute(Qt::WA_TranslucentBackground);
    setFixedSize(200,40);
}

void QDlgZoombar::paintEvent(QPaintEvent *event)
{
    QPainter        painter(this);
    QRect           rcClient            = rect();

    painter.fillRect(rcClient, QColor(29,59,140,220));
}
