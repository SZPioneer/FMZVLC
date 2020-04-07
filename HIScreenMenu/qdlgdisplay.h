#ifndef QDLGDISPLAY_H
#define QDLGDISPLAY_H

#include "QMyWidget.h"
#include "qwidgetpicinpicbar.h"

namespace Ui {
   class QDlgDisplay;
}

class QDlgDisplay : public QMyWidget
{
    Q_OBJECT
public:
    explicit QDlgDisplay(QWidget *parent = nullptr);

    virtual void    setFocusOn(bool bFocus);

protected:
    virtual void    paintEvent(QPaintEvent *event) override;

signals:

public slots:
    virtual void    onWheel(QObject*,int);
    virtual void    onKeyEnter(QObject*);

private:
    Ui::QDlgDisplay*            ui;
    int                         m_iStepPos          = 0;
    int                         m_iStepMax          = 6;
    QWidgetPicInPicbar*         m_pPicInPicbar      = NULL;
};

#endif // QDLGDISPLAY_H
