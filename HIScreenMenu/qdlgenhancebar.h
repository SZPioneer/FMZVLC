#ifndef QDLGENHANCEBAR_H
#define QDLGENHANCEBAR_H

#include "qmywidget.h"

namespace Ui {
   class QDlgEnhancebar;
}

class QDlgEnhanceBar : public QMyWidget
{
    Q_OBJECT
public:
    explicit QDlgEnhanceBar(QWidget *parent = nullptr);

    virtual void    setFocusOn(bool bFocus);


protected:
    virtual void    paintEvent(QPaintEvent *event) override;
    virtual void    resizeEvent(QResizeEvent *event) override;
signals:

public slots:
    virtual void    onWheel(QObject*,int);
    virtual void    onKeyEnter(QObject*);

private:
    Ui::QDlgEnhancebar*         ui;
};

#endif // QDLGENHANCEBAR_H
