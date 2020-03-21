#ifndef QDLGCAMBUTTONSET_H
#define QDLGCAMBUTTONSET_H

#include <QDialog>


namespace Ui {
    class QDlgCamButtonSet;
}
class QDlgCamButtonSet : public QDialog
{
    Q_OBJECT
public:
    explicit QDlgCamButtonSet(QWidget *parent = nullptr);

protected:
    virtual void    paintEvent(QPaintEvent *event) override;

signals:

public slots:

private slots:
    void on_comboBox_left1_currentIndexChanged(int index);

    void on_comboBox_left2_currentIndexChanged(int index);

    void on_comboBox_right1_currentIndexChanged(int index);

    void on_comboBox_right2_currentIndexChanged(int index);

private:
    Ui::QDlgCamButtonSet*       ui;
};

#endif // QDLGCAMBUTTONSET_H
