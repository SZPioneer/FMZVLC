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

    pBtn            = new QMyToolButton(":/img/enhanceMin.png", ":/img/enhanceMax.png", this, "增强", MenuType_Enhance);
    connect(pBtn, SIGNAL(clickBtn(QMyToolButton*)), this, SLOT(onClickBtn(QMyToolButton*)));
    m_lsMainBtn.push_back(pBtn);

    pBtn            = new QMyToolButton(":/img/wBalanceMin.png", ":/img/wBalanceMax.png", this, "白平衡", MenuType_WhiteBalance);
    connect(pBtn, SIGNAL(clickBtn(QMyToolButton*)), this, SLOT(onClickBtn(QMyToolButton*)));
    m_lsMainBtn.push_back(pBtn);

    pBtn            = new QMyToolButton(":/img/lightSrcMin.png", ":/img/lightSrcMax.png", this, "光源", MenuType_LightSrc);
    connect(pBtn, SIGNAL(clickBtn(QMyToolButton*)), this, SLOT(onClickBtn(QMyToolButton*)));
    m_lsMainBtn.push_back(pBtn);

    pBtn            = new QMyToolButton(":/img/chuiMachineMin.png", ":/img/chuiMachineMax.png", this, "吹腹机", MenuType_ChuiMachine);
    connect(pBtn, SIGNAL(clickBtn(QMyToolButton*)), this, SLOT(onClickBtn(QMyToolButton*)));
    m_lsMainBtn.push_back(pBtn);

    pBtn            = new QMyToolButton(":/img/RMin.png", ":/img/RMax.png", this, "图像翻转", MenuType_RImage);
    connect(pBtn, SIGNAL(clickBtn(QMyToolButton*)), this, SLOT(onClickBtn(QMyToolButton*)));
    m_lsMainBtn.push_back(pBtn);


    m_pBtnDown          = new QPushButton(this);
    m_pBtnDown->setObjectName("DownButton");
    m_pBtnDown->setFixedSize(64,39);
    connect(m_pBtnDown, SIGNAL(clicked(bool)), this, SLOT(onClickDown(bool)));

    m_pBtnUp          = new QPushButton(this);
    m_pBtnUp->setObjectName("UpButton");
    m_pBtnUp->setFixedSize(64,39);
    connect(m_pBtnUp, SIGNAL(clicked(bool)), this, SLOT(onClickUp(bool)));

    m_pDlgZoombar       = new QDlgZoombar(this);
    m_pDlgCamBtnSet     = new QDlgCamButtonSet(this);
    m_pDlgDisplay       = new QDlgDisplay(this);
    m_pDlgBrightbar     = new QDlgBrightbar(this);
    m_pDlgPresetbar     = new QDlgPresetBar(this);
    m_pDlgEnhancebar    = new QDlgEnhanceBar(this);
}

QWidgetCentral::~QWidgetCentral()
{
    if( m_pDlgEnhancebar ){
        delete m_pDlgEnhancebar;
    }
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

void QWidgetCentral::onClickDown(bool)
{
    m_iBtnShowPos++;
    if( m_iBtnShowPos+m_iBtnShowNum >= m_lsMainBtn.size() ){
        m_iBtnShowPos       = m_lsMainBtn.size() - m_iBtnShowNum;
    }
    ResetBtn();
}

void QWidgetCentral::onClickUp(bool)
{
    m_iBtnShowPos--;
    if( m_iBtnShowPos < 0  ){
        m_iBtnShowPos       = 0;
    }
    ResetBtn();
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
    }else if( m_pCurBtn->getType() == MenuType_Enhance ){
        m_pDlgEnhancebar->move(m_pCurBtn->mapToGlobal(pt));
        m_pDlgEnhancebar->show();
        m_pCurToolbar   = m_pDlgEnhancebar;
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
    int                 iyPos               = m_pBtnUp->rect().height() + 1;
    QMyToolButton*      pBtn                = NULL;
    int                 iCount              = 0;
    QRect               rcTmpUp             = m_lsMainBtn.at(m_iBtnShowPos)->rect();

    for(int i=0;i<m_lsMainBtn.size();i++){
        m_lsMainBtn.at(i)->hide();
    }

    for(int i=m_iBtnShowPos;i<m_lsMainBtn.size();i++){
        pBtn            = m_lsMainBtn.at(i);
        rcBtn           = pBtn->rect();
        pBtn->move(5, iyPos);
        pBtn->show();
        iyPos           += rcBtn.height();
        iyPos           += 1;
        iCount++;

        if( iCount >= m_iBtnShowNum ){
            if( i < m_lsMainBtn.size()-1 ){
                iCount  = 0;
            }
            break;
        }
    }
    if( iCount < m_iBtnShowNum ){
        QRect       rcTmp       = m_pBtnDown->rect();
        m_pBtnDown->move(5+(rcBtn.width()-rcTmp.width())/2, iyPos);
        m_pBtnDown->show();
    }else{
        m_pBtnDown->hide();
    }

    if( m_iBtnShowPos > 0 ){
        QRect       rcTmp       = m_pBtnUp->rect();
        m_pBtnUp->move(5+(rcTmpUp.width()-rcTmp.width())/2, 0);
        m_pBtnUp->show();
    }else{
        m_pBtnUp->hide();
    }
}

void QWidgetCentral::resizeEvent(QResizeEvent *event)
{
    ResetBtn();
}
