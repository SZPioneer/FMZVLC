#ifndef QWIDGETCENTRAL_H
#define QWIDGETCENTRAL_H

#include <QWidget>
#include "qmytoolbutton.h"
#include "qdlgzoombar.h"
#include "qdlgcambuttonset.h"
#include "QDlgBrightbar.h"
#include "qdlgdisplay.h"
#include "qdlgpresetbar.h"
#include <QPushButton>
#include "qdlgenhancebar.h"

class QWidgetCentral : public QWidget
{
    Q_OBJECT
public:
    explicit QWidgetCentral(QWidget *parent = nullptr);
    virtual ~QWidgetCentral();

    void    ResetBtn();

private:
    void    ShowToolbar();
    void    HideToolbar();

protected:
    virtual void resizeEvent(QResizeEvent *event);

signals:
public slots:
    void    onClickBtn(QMyToolButton* pBtn);
    void    onClickDown(bool);
    void    onClickUp(bool);

private:
    QList<QMyToolButton*>       m_lsMainBtn;
    QMyToolButton*              m_pCurBtn       = NULL;
    QDlgZoombar*                m_pDlgZoombar   = NULL;
    QDlgBrightbar*              m_pDlgBrightbar = NULL;
    QDlgCamButtonSet*           m_pDlgCamBtnSet = NULL;
    QDlgDisplay*                m_pDlgDisplay   = NULL;
    QDlgPresetBar*              m_pDlgPresetbar = NULL;
    QDlgEnhanceBar*             m_pDlgEnhancebar= NULL;
    QDialog*                    m_pCurToolbar   = NULL;
    int                         m_iBtnShowPos   = 0;
    int                         m_iBtnShowNum   = 6;
    QPushButton*                m_pBtnDown;
    QPushButton*                m_pBtnUp;
};

#endif // QWIDGETCENTRAL_H
