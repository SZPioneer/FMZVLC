#ifndef QMYCOMBOBOX_H
#define QMYCOMBOBOX_H

#include <QComboBox>
#include "qmywidget.h"

class QMyComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit QMyComboBox(QWidget *parent = nullptr);

    virtual void    setFocusOn(bool bFocus);
    virtual void    setMyParent(QObject* pParent)
    {
        m_pMyParent         = pParent;
    }

signals:

public slots:
    virtual void    onWheel(QObject*,int);
    virtual void    onKeyEnter(QObject*);
    virtual void    onActivated(int iIdx);

protected:
    bool            m_bFocusOn      = false;
    QObject*        m_pMyParent     = NULL;
};

#endif // QMYCOMBOBOX_H
