#ifndef QWIDGETCENTRAL_H
#define QWIDGETCENTRAL_H

#include <QWidget>
#include "qmytoolbutton.h"
#include "qdlgzoombar.h"

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

private:
    QList<QMyToolButton*>       m_lsMainBtn;
    QMyToolButton*              m_pCurBtn       = NULL;
    QDlgZoombar*                m_pDlgZoombar   = NULL;
    QDialog*                    m_pCurToolbar   = NULL;
};

#endif // QWIDGETCENTRAL_H
