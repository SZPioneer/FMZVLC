#ifndef QDLGENHANCEBAR_H
#define QDLGENHANCEBAR_H

#include <QDialog>

namespace Ui {
   class QDlgEnhancebar;
}

class QDlgEnhanceBar : public QDialog
{
    Q_OBJECT
public:
    explicit QDlgEnhanceBar(QWidget *parent = nullptr);

protected:
    virtual void    paintEvent(QPaintEvent *event) override;
    virtual void    resizeEvent(QResizeEvent *event) override;
signals:

public slots:

private:
    Ui::QDlgEnhancebar*         ui;
};

#endif // QDLGENHANCEBAR_H
