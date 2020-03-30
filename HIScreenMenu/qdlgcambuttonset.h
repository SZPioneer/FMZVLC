#ifndef QDLGCAMBUTTONSET_H
#define QDLGCAMBUTTONSET_H

#include "qmywidget.h"


namespace Ui {
    class QDlgCamButtonSet;
}
class QDlgCamButtonSet : public QMyWidget
{
    Q_OBJECT
public:
    explicit QDlgCamButtonSet(QWidget *parent = nullptr);

    virtual void    setFocusOn(bool bFocus);

protected:
    virtual void    paintEvent(QPaintEvent *event) override;

signals:

public slots:
    virtual void    onWheel(QObject*,int);
    virtual void    onKeyEnter(QObject*);

private slots:
    void on_comboBox_left1_currentIndexChanged(int index);

    void on_comboBox_left2_currentIndexChanged(int index);

    void on_comboBox_right1_currentIndexChanged(int index);

    void on_comboBox_right2_currentIndexChanged(int index);

private:
    Ui::QDlgCamButtonSet*       ui;
    int                         m_iStepPos          = 0;
    int                         m_iStepMax          = 7;
};

#endif // QDLGCAMBUTTONSET_H
