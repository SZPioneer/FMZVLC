#ifndef QDLGZOOMBAR_H
#define QDLGZOOMBAR_H

#include <QDialog>

namespace Ui {
   class QDlgZoombar;
}
class QDlgZoombar : public QDialog
{
    Q_OBJECT
public:
    explicit QDlgZoombar(QWidget *parent = nullptr);

protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void resizeEvent(QResizeEvent *event) override;

signals:

public slots:

private slots:
    void on_pushButton_min_clicked();

    void on_pushButton_max_clicked();

private:
    Ui::QDlgZoombar*    ui              = NULL;
    QPushButton*        m_pBtn[5];
};

#endif // QDLGZOOMBAR_H
