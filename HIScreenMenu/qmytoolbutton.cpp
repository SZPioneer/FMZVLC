#include "qmytoolbutton.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QPen>
#include "xmlconfig.h"

#define BORDER_MIN_EXTERN       20
#define BORDER_MAX_EXTERN       30
QMyToolButton::QMyToolButton(QString qstrMin, QString qstrMax, QString qstrMaxNotFocus, QWidget *parent, QString qstrTip, int iType) : QToolButton(parent)
{
    m_qstrTip       = qstrTip;
    m_iID           = iType;

    m_imgMax.load(qstrMax);
    m_imgMin.load(qstrMin);
    m_imgMaxNotFocus.load(qstrMaxNotFocus);

    setFixedSize(m_imgMin.width()+BORDER_MIN_EXTERN, m_imgMin.height()+BORDER_MIN_EXTERN);

    if( m_iID == Menutype_Brightness ){
        connect(XmlConfig::GetInstance(), SIGNAL(changeBright(int)), this, SLOT(onChangeBright(int)));
    }
}

void QMyToolButton::paintEvent(QPaintEvent *event)
{
    QPainter    painter(this);
    QRect       rcClient(1, 1, rect().width()-2, rect().height()-2);
    QFont       font                = painter.font();
    QPen        penMin(QColor(255,255,255));
    QPen        penMax(QColor(244,234,42));


    if( m_bSelect ){
        painter.setPen(penMax);
        painter.fillRect(rcClient, QColor(29,59,166,220));
        m_rcMaxBtn      = m_imgMax.rect();
        m_rcMaxBtn.setLeft((width()-m_imgMax.width())/2);
        m_rcMaxBtn.setTop((height()-m_imgMax.height())/2);
        //painter.drawPixmap((width()-m_imgMax.width())/2, (height()-m_imgMax.height())/2, m_imgMax);
        if( m_bFocus ){
            painter.drawImage(m_rcMaxBtn.left(), m_rcMaxBtn.top(), m_imgMax);
        }else{
            painter.drawImage(m_rcMaxBtn.left(), m_rcMaxBtn.top(), m_imgMaxNotFocus);
        }

        font.setPixelSize(20);
        //font.setFamily("wenquanyi");
        painter.setFont(font);
        painter.drawText(rcClient, Qt::AlignLeft|Qt::AlignBottom, m_qstrTip);
        //painter.drawText(rcClient, Qt::AlignLeft|Qt::AlignBottom, tr("中文"));
    }else{
        painter.setPen(penMin);
        //painter.fillRect(rcClient, QColor(29,59,166,220));
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setBrush(QBrush(QColor(29,59,166,220)));
        painter.drawRoundedRect(rect(), 5, 5);
        painter.drawImage((width()-m_imgMin.width())/2, (height()-m_imgMin.height())/2, m_imgMin);

        font.setPixelSize(12);
        //font.setFamily("wenquanyi");
        painter.setFont(font);
        painter.drawText(rcClient, Qt::AlignLeft|Qt::AlignBottom, m_qstrTip);
    }

    if( m_iID == Menutype_Brightness ){
        int     iStep       = XmlConfig::GetInstance()->brightStep();
        QString qstrTmp     = QString("%1").arg(iStep);
        painter.drawText(rcClient, Qt::AlignCenter, qstrTmp);
    }
}

void QMyToolButton::mousePressEvent(QMouseEvent *e)
{
    if( e->button() == Qt::LeftButton ){
        emit clickBtn(this);
    }
}

void QMyToolButton::setSelect(bool bSelect)
{
    m_bSelect       = bSelect;
    if( m_bSelect ){
       setFixedSize(m_imgMax.width()+BORDER_MAX_EXTERN, m_imgMax.height()+BORDER_MAX_EXTERN);
    }else{
        setFixedSize(m_imgMin.width()+BORDER_MIN_EXTERN, m_imgMin.height()+BORDER_MIN_EXTERN);
    }
    //this->update();
}

void QMyToolButton::onChangeBright(int iVal)
{
    update();
}
