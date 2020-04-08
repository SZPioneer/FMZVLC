#ifndef QDLGBRIGHTBAR_H
#define QDLGBRIGHTBAR_H

#include "qmywidget.h"
#include <QPushButton>

namespace Ui {
  class QDlgBrightbar;
}
class QDlgBrightbar : public QMyWidget
{
    Q_OBJECT
public:
    explicit QDlgBrightbar(QWidget *parent = nullptr);

    virtual void    paintEvent(QPaintEvent *event);
    virtual void    resizeEvent(QResizeEvent *event);
    virtual void    setFocusOn(bool bFocus);

signals:

public slots:
    virtual void    on_pushButton_min_clicked();
    virtual void    on_pushButton_max_clicked();
    virtual void    onChangeBright(int);
    virtual void    onWheel(QObject*,int);
    virtual void    onKeyEnter(QObject*);

private:
    Ui::QDlgBrightbar*          ui;
    QPushButton*                m_pBtn[5];

};

#endif // QDLGBRIGHTBAR_H
