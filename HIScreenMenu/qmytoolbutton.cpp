#include "qmytoolbutton.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QPen>

QMyToolButton::QMyToolButton(QString qstrMin, QString qstrMax, QWidget *parent, QString qstrTip, int iType) : QToolButton(parent)
{
    m_qstrTip       = qstrTip;
    m_iID           = iType;

    m_imgMax.load(qstrMax);
    m_imgMin.load(qstrMin);

    setFixedSize(m_imgMin.width(), m_imgMin.height());
}

void QMyToolButton::paintEvent(QPaintEvent *event)
{
    QPainter    painter(this);
    QRect       rcClient(1, 1, rect().width()-2, rect().height()-2);
    QFont       font                = painter.font();
    QPen        pen(QColor(255,255,255));

    painter.setPen(pen);
    if( m_bSelect ){
        painter.fillRect(rcClient, QColor(29,59,166,220));
        painter.drawPixmap(0, 0, m_imgMax);

        font.setPixelSize(24);
        font.setFamily("wenquanyi");
        painter.setFont(font);
        painter.drawText(rcClient, Qt::AlignLeft|Qt::AlignBottom, m_qstrTip);
        //painter.drawText(rcClient, Qt::AlignLeft|Qt::AlignBottom, tr("中文"));
    }else{
        painter.fillRect(rcClient, QColor(29,59,166,220));
        painter.drawPixmap(0, 0, m_imgMin);

        font.setPixelSize(12);
        font.setFamily("wenquanyi");
        painter.setFont(font);
        painter.drawText(rcClient, Qt::AlignLeft|Qt::AlignBottom, m_qstrTip);
    }
}

void QMyToolButton::mousePressEvent(QMouseEvent *e)
{
    if( e->button() == Qt::LeftButton ){
        qDebug()<<"lBtnDown";
        emit clickBtn(this);
    }
}

void QMyToolButton::setSelect(bool bSelect)
{
    m_bSelect       = bSelect;
    if( m_bSelect ){
       setFixedSize(m_imgMax.width(), m_imgMax.height());
    }else{
        setFixedSize(m_imgMin.width(), m_imgMin.height());
    }
    //this->update();
}
