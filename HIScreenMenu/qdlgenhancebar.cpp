#include "qdlgenhancebar.h"
#include "ui_qdlgenhancebar.h"
#include <QPainter>
#include "xmlconfig.h"

QDlgEnhanceBar::QDlgEnhanceBar(QWidget *parent) : QMyWidget(parent), ui(new Ui::QDlgEnhancebar)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Dialog|Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    this->setWindowOpacity(1);
    this->setAttribute(Qt::WA_TranslucentBackground);
    setFixedSize(180,40);

    MapEnhanceSets        mapSets     = XmlConfig::GetInstance()->m_mapEnhanceSets;
    for(MapEnhanceSets::iterator iter=mapSets.begin();iter!=mapSets.end();iter++){
        ui->comboBox_enhance->addItem(iter.value(), QVariant(iter.key()));
    }
    ui->comboBox_enhance->setCurrentIndex(XmlConfig::GetInstance()->m_iEnhance);

    ui->comboBox_enhance->setMyParent(parent);
}

void QDlgEnhanceBar::setFocusOn(bool bFocus)
{
    //QMyWidget::setFocusOn(bFocus);
    //ui->comboBox_enhance->showPopup();
    if( bFocus ){
        XmlConfig::GetInstance()->setAppEventObj(ui->comboBox_enhance, true, false);
    }
}

void QDlgEnhanceBar::onWheel(QObject* pObj,int iStep)
{
    if( pObj != this ){
        return;
    }

    int     iCurIdx     = ui->comboBox_enhance->currentIndex();
    if( iStep > 0 ){
        iCurIdx--;
        if( iCurIdx <= 0 ){
            iCurIdx     = 0;
        }
    }else{
        iCurIdx++;
        if( iCurIdx >= ui->comboBox_enhance->count() ){
            iCurIdx     = ui->comboBox_enhance->count() - 1;
        }
    }

    QAbstractItemView*      pView       = ui->comboBox_enhance->view();
    QAbstractItemModel*     pModel      = pView->model();
    QModelIndex             index       = pModel->index(iCurIdx, 0);
    pView->setCurrentIndex(index);
    ui->comboBox_enhance->setCurrentIndex(iCurIdx);

    qDebug()<<"iCurIdx:"<<iCurIdx<<"count:"<<ui->comboBox_enhance->count();
}

void QDlgEnhanceBar::onKeyEnter(QObject* pObj)
{
    if( pObj != this ){
        return;
    }


    emit XmlConfig::GetInstance()->notifyEnterToolbar(this);
    ui->comboBox_enhance->hidePopup();
}

void QDlgEnhanceBar::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(QBrush(QColor(29,59,140,220)));
    painter.drawRoundedRect(rect(), 5, 5);
}

void QDlgEnhanceBar::resizeEvent(QResizeEvent *event)
{
    QRect       rcCom       = ui->comboBox_enhance->rect();
    ui->comboBox_enhance->move((width()-rcCom.width())/2, (height()-rcCom.height())/2);
}
