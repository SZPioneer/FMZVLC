#ifndef QWIDGETPICINPICBAR_H
#define QWIDGETPICINPICBAR_H

#include "qmywidget.h"

namespace Ui {
   class QWidgetPicInPicbar;
}

class QWidgetPicInPicbar : public QMyWidget
{
    Q_OBJECT
public:
    explicit QWidgetPicInPicbar(QWidget *parent = nullptr);

    virtual void    setFocusOn(bool bFocus);
    virtual void    paintEvent(QPaintEvent *event);

signals:

public slots:
    virtual void    onWheel(QObject*,int);
    virtual void    onKeyEnter(QObject*);

private:
    Ui::QWidgetPicInPicbar*         ui;
    int                             m_iStepPos          = -1;
    int                             m_iStepMax          = 4;
};

#endif // QWIDGETPICINPICBAR_H
