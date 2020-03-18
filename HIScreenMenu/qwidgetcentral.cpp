#include "qwidgetcentral.h"


QWidgetCentral::QWidgetCentral(QWidget *parent) : QWidget(parent)
{
    QMyToolButton*          pBtn        = NULL;
    pBtn            = new QMyToolButton(":/img/zoomMin.png", ":/img/zoomMax.png", this, "缩放", MenuType_Zoom);
    connect(pBtn, SIGNAL(clickBtn(QMyToolButton*)), this, SLOT(onClickBtn(QMyToolButton*)));
    m_lsMainBtn.push_back(pBtn);

    pBtn            = new QMyToolButton(":/img/Btn01-min.png", ":/img/Btn01-max.png", this);
    connect(pBtn, SIGNAL(clickBtn(QMyToolButton*)), this, SLOT(onClickBtn(QMyToolButton*)));
    m_lsMainBtn.push_back(pBtn);

    pBtn            = new QMyToolButton(":/img/Btn01-min.png", ":/img/Btn01-max.png", this);
    connect(pBtn, SIGNAL(clickBtn(QMyToolButton*)), this, SLOT(onClickBtn(QMyToolButton*)));
    m_lsMainBtn.push_back(pBtn);

    pBtn            = new QMyToolButton(":/img/Btn01-min.png", ":/img/Btn01-max.png", this);
    connect(pBtn, SIGNAL(clickBtn(QMyToolButton*)), this, SLOT(onClickBtn(QMyToolButton*)));
    m_lsMainBtn.push_back(pBtn);

    pBtn            = new QMyToolButton(":/img/Btn01-min.png", ":/img/Btn01-max.png", this);
    connect(pBtn, SIGNAL(clickBtn(QMyToolButton*)), this, SLOT(onClickBtn(QMyToolButton*)));
    m_lsMainBtn.push_back(pBtn);

    m_pDlgZoombar       = new QDlgZoombar(this);
}

QWidgetCentral::~QWidgetCentral()
{
    if( m_pDlgZoombar ){
        delete m_pDlgZoombar;
    }
}

void QWidgetCentral::onClickBtn(QMyToolButton* pBtn)
{
    if( pBtn == m_pCurBtn ){
        m_pCurBtn->setSelect(false);
        m_pCurBtn       = NULL;
        ResetBtn();
        HideToolbar();
        return;
    }
    if( m_pCurBtn ){
        m_pCurBtn->setSelect(false);
        HideToolbar();
    }
    m_pCurBtn       = pBtn;
    m_pCurBtn->setSelect(true);

    ResetBtn();
    ShowToolbar();
}

void QWidgetCentral::ShowToolbar()
{
    QRect       rcBtn   = m_pCurBtn->rect();
    QPoint      pt(rcBtn.right(),rcBtn.top());
    if( m_pCurBtn->getType() == MenuType_Zoom ){
        m_pDlgZoombar->move(m_pCurBtn->mapToGlobal(pt));
        m_pDlgZoombar->show();
        m_pCurToolbar   = m_pDlgZoombar;
    }
}

void QWidgetCentral::HideToolbar()
{
    if( m_pCurToolbar ){
        m_pCurToolbar->hide();
        m_pCurToolbar   = NULL;
    }
}

void QWidgetCentral::ResetBtn()
{
    QRect               rcBtn;
    int                 iyPos               = 0;
    QMyToolButton*      pBtn                = NULL;

    for(int i=0;i<m_lsMainBtn.size();i++){
        pBtn            = m_lsMainBtn.at(i);
        rcBtn           = pBtn->rect();
        pBtn->move(5, iyPos);
        iyPos           += rcBtn.height();
    }
}

void QWidgetCentral::resizeEvent(QResizeEvent *event)
{
    ResetBtn();
}
