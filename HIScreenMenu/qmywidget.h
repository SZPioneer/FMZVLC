#ifndef QMYWIDGET_H
#define QMYWIDGET_H

#include <QWidget>

class QMyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QMyWidget(QWidget *parent = nullptr);

    virtual void    setFocusOn(bool bFocus)
    {
        m_bFocusOn      = bFocus;
    }



signals:

public slots:
    virtual void    onWheel(QObject*,int){}
    virtual void    onKeyEnter(QObject*){}

protected:
    bool            m_bFocusOn      = false;
};

#endif // QMYWIDGET_H
