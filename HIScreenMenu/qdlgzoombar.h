#ifndef QDLGZOOMBAR_H
#define QDLGZOOMBAR_H

#include "qmywidget.h"
#include <QPushButton>

namespace Ui {
   class QDlgZoombar;
}
class QDlgZoombar : public QMyWidget
{
    Q_OBJECT
public:
    explicit QDlgZoombar(QWidget *parent = nullptr);

    virtual void    setFocusOn(bool bFocus);
protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void resizeEvent(QResizeEvent *event) override;

signals:

public slots:
    virtual void on_pushButton_min_clicked();
    virtual void on_pushButton_max_clicked();

    void    onChangeZoom(int);
    virtual void    onWheel(QObject*,int);
    virtual void    onKeyEnter(QObject*);

protected:
    Ui::QDlgZoombar*    ui              = NULL;
    QPushButton*        m_pBtn[5];
};

#endif // QDLGZOOMBAR_H
