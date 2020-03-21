#ifndef QDLGDISPLAY_H
#define QDLGDISPLAY_H

#include <QDialog>

namespace Ui {
   class QDlgDisplay;
}

class QDlgDisplay : public QDialog
{
    Q_OBJECT
public:
    explicit QDlgDisplay(QWidget *parent = nullptr);

protected:
    virtual void    paintEvent(QPaintEvent *event) override;

signals:

public slots:

private:
    Ui::QDlgDisplay*            ui;
};

#endif // QDLGDISPLAY_H
