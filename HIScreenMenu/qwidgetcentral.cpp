#include "qwidgetcentral.h"
#include "xmlconfig.h"
#include <QApplication>
#include <QWheelEvent>
#include <QPainter>
#include <QThread>

QWidgetCentral::QWidgetCentral(QWidget *parent) : QMyWidget(parent)
{
    QMyToolButton*          pBtn        = NULL;
    pBtn            = new QMyToolButton(":/img/zoomMin.png", ":/img/zoomMax.png", ":/img/zoomMaxNotFocus.png", this, "缩放", MenuType_Zoom);
    connect(pBtn, SIGNAL(clickBtn(QMyToolButton*)), this, SLOT(onClickBtn(QMyToolButton*)));
    m_lsMainBtn.push_back(pBtn);

    pBtn            = new QMyToolButton(":/img/CamBtnSetMin.png", ":/img/CamBtnSetMax.png", ":/img/CamBtnSetMaxNotFocus.png", this, "按键设定", MenuType_CamBtnSet);
    connect(pBtn, SIGNAL(clickBtn(QMyToolButton*)), this, SLOT(onClickBtn(QMyToolButton*)));
    m_lsMainBtn.push_back(pBtn);

    pBtn            = new QMyToolButton(":/img/exitMin.png", ":/img/exitMax.png", ":/img/exitMaxNotFocus.png", this, "退出", MenuType_Exit);
    connect(pBtn, SIGNAL(clickBtn(QMyToolButton*)), this, SLOT(onClickBtn(QMyToolButton*)));
    m_lsMainBtn.push_back(pBtn);

    pBtn            = new QMyToolButton(":/img/DiaplayMin.png", ":/img/DiaplayMax.png", ":/img/DiaplayMaxNotFocus.png", this, "显示", Menutype_Show);
    connect(pBtn, SIGNAL(clickBtn(QMyToolButton*)), this, SLOT(onClickBtn(QMyToolButton*)));
    m_lsMainBtn.push_back(pBtn);

    pBtn            = new QMyToolButton(":/img/brightMin.png", ":/img/brightMax.png", ":/img/brightMaxNotFocus.png", this, "亮度", Menutype_Brightness);
    connect(pBtn, SIGNAL(clickBtn(QMyToolButton*)), this, SLOT(onClickBtn(QMyToolButton*)));
    m_lsMainBtn.push_back(pBtn);

    pBtn            = new QMyToolButton(":/img/printMin.png", ":/img/printMax.png", ":/img/printMaxNotFocus.png", this, "立即打印", MenuType_printNow);
    connect(pBtn, SIGNAL(clickBtn(QMyToolButton*)), this, SLOT(onClickBtn(QMyToolButton*)));
    m_lsMainBtn.push_back(pBtn);

    pBtn            = new QMyToolButton(":/img/presetMin.png", ":/img/presetMax.png", ":/img/presetMaxNotFocus.png", this, "预设", MenyType_Preset);
    connect(pBtn, SIGNAL(clickBtn(QMyToolButton*)), this, SLOT(onClickBtn(QMyToolButton*)));
    m_lsMainBtn.push_back(pBtn);

    pBtn            = new QMyToolButton(":/img/videoMin.png", ":/img/videoMax.png", ":/img/videoMaxNotFocus.png", this, "视频", MenuType_Video);
    connect(pBtn, SIGNAL(clickBtn(QMyToolButton*)), this, SLOT(onClickBtn(QMyToolButton*)));
    m_lsMainBtn.push_back(pBtn);

    pBtn            = new QMyToolButton(":/img/enhanceMin.png", ":/img/enhanceMax.png", ":/img/enhanceMaxNotFocus.png", this, "增强", MenuType_Enhance);
    connect(pBtn, SIGNAL(clickBtn(QMyToolButton*)), this, SLOT(onClickBtn(QMyToolButton*)));
    m_lsMainBtn.push_back(pBtn);

    pBtn            = new QMyToolButton(":/img/wBalanceMin.png", ":/img/wBalanceMax.png", ":/img/wBalanceMaxNotFocus.png", this, "白平衡", MenuType_WhiteBalance);
    connect(pBtn, SIGNAL(clickBtn(QMyToolButton*)), this, SLOT(onClickBtn(QMyToolButton*)));
    m_lsMainBtn.push_back(pBtn);

    pBtn            = new QMyToolButton(":/img/lightSrcMin.png", ":/img/lightSrcMax.png", ":/img/lightSrcMaxNotFocus.png", this, "光源", MenuType_LightSrc);
    connect(pBtn, SIGNAL(clickBtn(QMyToolButton*)), this, SLOT(onClickBtn(QMyToolButton*)));
    m_lsMainBtn.push_back(pBtn);

    pBtn            = new QMyToolButton(":/img/chuiMachineMin.png", ":/img/chuiMachineMax.png", ":/img/chuiMachineMaxNotFocus.png", this, "吹腹机", MenuType_ChuiMachine);
    connect(pBtn, SIGNAL(clickBtn(QMyToolButton*)), this, SLOT(onClickBtn(QMyToolButton*)));
    m_lsMainBtn.push_back(pBtn);

    pBtn            = new QMyToolButton(":/img/RMin.png", ":/img/RMax.png", ":/img/RMaxNotFocus.png", this, "图像翻转", MenuType_RImage);
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

    XmlConfig::GetInstance()->setAppEventObj(this);

    connect(XmlConfig::GetInstance(), SIGNAL(notifyEnterToolbar(QWidget*)), this, SLOT(onEnterToolbar(QWidget*)));
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

void QWidgetCentral::setFocusOn(bool bFocus)
{
    QMyWidget::setFocusOn(bFocus);
    if( bFocus ){
        if( m_pCurBtn ){
            m_pCurBtn->setSelect(true);
            m_pCurBtn->setFocusOn(true);
        }
    }
}

void QWidgetCentral::onClickBtn(QMyToolButton* pBtn, bool bWheel/*=false*/)
{
    if( bWheel ){
        if( pBtn->isSelect() ){
            return;
        }
    }
    if( pBtn->isSelect() ){
        bool        bFocus      = false;
        if( pBtn->getType() == MenuType_Exit ){
            qApp->quit();
        }else if( pBtn->getType() == MenuType_Zoom ){
            XmlConfig::GetInstance()->setAppEventObj(m_pDlgZoombar);
        }else if( pBtn->getType() == MenuType_CamBtnSet ){
            XmlConfig::GetInstance()->setAppEventObj(m_pDlgCamBtnSet);
        }else if( pBtn->getType() == Menutype_Show ){
            XmlConfig::GetInstance()->setAppEventObj(m_pDlgDisplay);
        }else if( pBtn->getType() == Menutype_Brightness ){
            XmlConfig::GetInstance()->setAppEventObj(m_pDlgBrightbar);
        }else if( pBtn->getType() == MenuType_printNow ){
            emit XmlConfig::GetInstance()->notifyNowPrint();
            bFocus      = true;
        }else if( pBtn->getType() == MenyType_Preset ){
            XmlConfig::GetInstance()->setAppEventObj(m_pDlgPresetbar);
        }else if( pBtn->getType() == MenuType_Video ){

        }else if( pBtn->getType() == MenuType_Enhance ){
            XmlConfig::GetInstance()->setAppEventObj(m_pDlgEnhancebar);
        }else if( pBtn->getType() == MenuType_WhiteBalance ){

        }else if( pBtn->getType() == MenuType_LightSrc ){

        }else if( pBtn->getType() == MenuType_ChuiMachine ){

        }else if( pBtn->getType() == MenuType_RImage ){

        }
        qDebug()<<"current thread:"<<QThread::currentThreadId();
        pBtn->setFocusOn(bFocus);

    }else{
        if( pBtn == m_pCurBtn ){
            m_pCurBtn->setSelect(false);
            m_pCurBtn       = NULL;
            ResetBtn();
            HideToolbar();
            return;
        }
        if( m_pCurBtn ){
            HideToolbar();
            m_pCurBtn->setSelect(false);
        }
        m_pCurBtn       = pBtn;
        m_pCurBtn->setSelect(true);
        m_pCurBtn->setFocusOn(true);

        ResetBtn();
        ShowToolbar();
    }
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
        XmlConfig::GetInstance()->setAppEventObj(this);
        m_pCurToolbar->hide();
        m_pCurToolbar   = NULL;
    }
}

void QWidgetCentral::ResetBtn()
{
    QRect               rcBtn;
    int                 iyPos               = m_pBtnUp->rect().height() + 1;
    int                 ixPos               = 20;
    QMyToolButton*      pBtn                = NULL;
    int                 iCount              = 0;
    QRect               rcTmpUp             = m_lsMainBtn.at(m_iBtnShowPos)->rect();

    for(int i=0;i<m_lsMainBtn.size();i++){
        m_lsMainBtn.at(i)->hide();
    }

    for(int i=m_iBtnShowPos;i<m_lsMainBtn.size();i++){
        pBtn            = m_lsMainBtn.at(i);
        rcBtn           = pBtn->rect();
        pBtn->move(ixPos, iyPos);
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
        m_pBtnDown->move(ixPos+(rcBtn.width()-rcTmp.width())/2, iyPos);
        m_pBtnDown->show();
    }else{
        m_pBtnDown->hide();
    }

    if( m_iBtnShowPos > 0 ){
        QRect       rcTmp       = m_pBtnUp->rect();
        m_pBtnUp->move(ixPos+(rcTmpUp.width()-rcTmp.width())/2, 0);
        m_pBtnUp->show();
    }else{
        m_pBtnUp->hide();
    }
}

void QWidgetCentral::resizeEvent(QResizeEvent *event)
{
    ResetBtn();
}

int QWidgetCentral::ScrollToolButton(int iStep)
{
    int         iCurStep        = 0;

    if( m_pCurBtn == NULL ){
        iCurStep        = -1;
    }
    for(int i=0;i<m_lsMainBtn.size();i++){
        if( m_lsMainBtn.at(i) == m_pCurBtn ){
            iCurStep        = i;
            break;
        }
    }

    iCurStep        += iStep;
    if( iCurStep <= 0 ){
        iCurStep        = 0;
    }
    if( iCurStep >= m_lsMainBtn.size() ){
        iCurStep    = m_lsMainBtn.size() -1;
    }

    qDebug()<<"iCurStep:"<<iCurStep;
    if( iCurStep < m_iBtnShowPos ){
        onClickUp(false);
    }else if( iCurStep >= m_iBtnShowPos+m_iBtnShowNum ){
        onClickDown(false);
    }

    onClickBtn(m_lsMainBtn.at(iCurStep), true);
}

void QWidgetCentral::onWheel(QObject* pObj,int iStep)
{
    if( pObj != this ){
        return;
    }
    ScrollToolButton(-iStep);
}

void QWidgetCentral::onEnterToolbar(QWidget* pObj)
{
    XmlConfig::GetInstance()->setAppEventObj(this);
    m_pCurBtn->setFocusOn(true);
}


void QWidgetCentral::onKeyEnter(QObject* pObj)
{
    if( pObj != this ){
        return;
    }

    if( m_pCurBtn == NULL ){
        return;
    }
    onClickBtn((QMyToolButton*)m_pCurBtn);
}

void QWidgetCentral::wheelEvent(QWheelEvent *event)
{
    //QPoint      numPixels       = event->pixelDelta();
    QPoint      numDegrees      = event->angleDelta() / 8;

    if (!numDegrees.isNull()) {
        QPoint      numSteps    = numDegrees / 15;
        qDebug()<<"numSteps:"<<numSteps;
        ScrollToolButton(-numSteps.y());
    }

    event->accept();
}

void QWidgetCentral::paintEvent(QPaintEvent *event)
{
#if 1
    QPainter painter(this);
    painter.fillRect(rect(), QColor(0,0,255,1));
#endif
}

void QWidgetCentral::keyPressEvent(QKeyEvent *event)
{
    if( event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter ){
        qDebug()<<"enter";
    }
}
