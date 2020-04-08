#ifndef QDLGPRESETBAR_H
#define QDLGPRESETBAR_H

#include "qmywidget.h"

namespace Ui{
  class QDlgPresetBar;
}

class QDlgPresetBar : public QMyWidget
{
    Q_OBJECT
public:
    explicit QDlgPresetBar(QWidget *parent = nullptr);

    virtual void    setFocusOn(bool bFocus);

protected:
    virtual     void paintEvent(QPaintEvent *event);
    virtual     void resizeEvent(QResizeEvent *event);

signals:

public slots:


private:
    Ui::QDlgPresetBar*              ui;
};

#endif // QDLGPRESETBAR_H
