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

signals:

public slots:

private:
    Ui::QDlgZoombar*    ui              = NULL;

};

#endif // QDLGZOOMBAR_H
