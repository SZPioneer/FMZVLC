#include "qwidgetcentral.h"
#include "xmlconfig.h"

QWidgetCentral::QWidgetCentral(QWidget *parent) : QWidget(parent)
{
    QMyToolButton*          pBtn        = NULL;
    pBtn            = new QMyToolButton(":/img/zoomMin.png", ":/img/zoomMax.png", this, "缩放", MenuType_Zoom);
    connect(pBtn, SIGNAL(clickBtn(QMyToolButton*)), this, SLOT(onClickBtn(QMyToolButton*)));
    m_lsMainBtn.push_back(pBtn);

    pBtn            = new QMyToolButton(":/img/CamBtnSetMin.png", ":/img/CamBtnSetMax.png", this, "按键设定", MenuType_CamBtnSet);
    connect(pBtn, SIGNAL(clickBtn(QMyToolButton*)), this, SLOT(onClickBtn(QMyToolButton*)));
    m_lsMainBtn.push_back(pBtn);

    pBtn            = new QMyToolButton(":/img/exitMin.png", ":/img/exitMax.png", this, "退出", MenuType_Exit);
    connect(pBtn, SIGNAL(clickBtn(QMyToolButton*)), this, SLOT(onClickBtn(QMyToolButton*)));
    m_lsMainBtn.push_back(pBtn);

    pBtn            = new QMyToolButton(":/img/DiaplayMin.png", ":/img/DiaplayMax.png", this, "显示", Menutype_Show);
    connect(pBtn, SIGNAL(clickBtn(QMyToolButton*)), this, SLOT(onClickBtn(QMyToolButton*)));
    m_lsMainBtn.push_back(pBtn);

    pBtn            = new QMyToolButton(":/img/brightMin.png", ":/img/brightMax.png", this, "亮度", Menutype_Brightness);
    connect(pBtn, SIGNAL(clickBtn(QMyToolButton*)), this, SLOT(onClickBtn(QMyToolButton*)));
    m_lsMainBtn.push_back(pBtn);

    pBtn            = new QMyToolButton(":/img/printMin.png", ":/img/printMax.png", this, "立即打印", MenuType_printNow);
    connect(pBtn, SIGNAL(clickBtn(QMyToolButton*)), this, SLOT(onClickBtn(QMyToolButton*)));
    m_lsMainBtn.push_back(pBtn);

    pBtn            = new QMyToolButton(":/img/presetMin.png", ":/img/presetMax.png", this, "预设", MenyType_Preset);
    connect(pBtn, SIGNAL(clickBtn(QMyToolButton*)), this, SLOT(onClickBtn(QMyToolButton*)));
    m_lsMainBtn.push_back(pBtn);

    pBtn            = new QMyToolButton(":/img/videoMin.png", ":/img/videoMax.png", this, "视频", MenuType_Video);
    connect(pBtn, SIGNAL(clickBtn(QMyToolButton*)), this, SLOT(onClickBtn(QMyToolButton*)));
    m_lsMainBtn.push_back(pBtn);

    m_pDlgZoombar       = new QDlgZoombar(this);
    m_pDlgCamBtnSet     = new QDlgCamButtonSet(this);
    m_pDlgDisplay       = new QDlgDisplay(this);
    m_pDlgBrightbar     = new QDlgBrightbar(this);
    m_pDlgPresetbar     = new QDlgPresetBar(this);
}

QWidgetCentral::~QWidgetCentral()
{
    if( m_pDlgZoombar ){
        delete m_pDlgZoombar;
    }
    if( m_pDlgCamBtnSet ){
        delete m_pDlgCamBtnSet;
    }
    if( m_pDlgDisplay ){
        delete m_pDlgDisplay;
    }
    if( m_pDlgBrightbar ){
        delete m_pDlgBrightbar;
    }
    if( m_pDlgPresetbar ){
        delete m_pDlgPresetbar;
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
    }else if( m_pCurBtn->getType() == MenuType_CamBtnSet ){
        m_pDlgCamBtnSet->move(m_pCurBtn->mapToGlobal(pt));
        m_pDlgCamBtnSet->show();
        m_pCurToolbar   = m_pDlgCamBtnSet;
    }else if( m_pCurBtn->getType() == Menutype_Show ){
        m_pDlgDisplay->move(m_pCurBtn->mapToGlobal(pt));
        m_pDlgDisplay->show();
        m_pCurToolbar   = m_pDlgDisplay;
    }else if( m_pCurBtn->getType() == Menutype_Brightness ){
        m_pDlgBrightbar->move(m_pCurBtn->mapToGlobal(pt));
        m_pDlgBrightbar->show();
        m_pCurToolbar   = m_pDlgBrightbar;
    }else if( m_pCurBtn->getType() == MenyType_Preset ){
        m_pDlgPresetbar->move(m_pCurBtn->mapToGlobal(pt));
        m_pDlgPresetbar->show();
        m_pCurToolbar   = m_pDlgPresetbar;
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
        iyPos           += 1;
    }
}

void QWidgetCentral::resizeEvent(QResizeEvent *event)
{
    ResetBtn();
}
