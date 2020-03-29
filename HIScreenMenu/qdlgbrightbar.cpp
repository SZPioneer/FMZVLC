#include "qdlgbrightbar.h"
#include "xmlconfig.h"
#include <QPushButton>

QDlgBrightbar::QDlgBrightbar(QWidget *parent) : QDlgZoombar(parent)
{

}

void QDlgBrightbar::on_pushButton_min_clicked()
{
    XmlConfig::GetInstance()->onClickBrightMinus();
//    for(int i=0;i<iStep;i++){
//        m_pBtn[i]->setStyleSheet("border-image: url(:/img/zoomSel.png)");
//    }
//    for(int i=iStep;i<5;i++){
//        m_pBtn[i]->setStyleSheet("border-image: url(:/img/zoomUnSel.png)");
//    }

    //emit XmlConfig::GetInstance()->changeBright(iStep);
}

void QDlgBrightbar::on_pushButton_max_clicked()
{
    XmlConfig::GetInstance()->onClickBrightAdd();
//    for(int i=0;i<iStep;i++){
//        m_pBtn[i]->setStyleSheet("border-image: url(:/img/zoomSel.png)");
//    }
//    for(int i=iStep;i<5;i++){
//        m_pBtn[i]->setStyleSheet("border-image: url(:/img/zoomUnSel.png)");
//    }

    //emit XmlConfig::GetInstance()->changeBright(iStep);
}
