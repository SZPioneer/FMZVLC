#include "qdlgpresetbar.h"
#include "ui_Qdlgpresetbar.h"
#include <QPainter>
#include "xmlconfig.h"

QDlgPresetBar::QDlgPresetBar(QWidget *parent) : QMyWidget(parent), ui(new Ui::QDlgPresetBar)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Dialog|Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    this->setWindowOpacity(1);
    this->setAttribute(Qt::WA_TranslucentBackground);
    setFixedSize(180,40);

    MapPreSets        mapSets     = XmlConfig::GetInstance()->m_mapPreSets;
    for(MapPreSets::iterator iter=mapSets.begin();iter!=mapSets.end();iter++){
        ui->comboBox_preset->addItem(iter.value(), QVariant(iter.key()));
    }
    ui->comboBox_preset->setCurrentIndex(XmlConfig::GetInstance()->m_iPreSet);

    ui->comboBox_preset->setMyParent(parent);
}

void QDlgPresetBar::setFocusOn(bool bFocus)
{
    if( bFocus ){
        XmlConfig::GetInstance()->setAppEventObj(ui->comboBox_preset, true, false);
    }
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
