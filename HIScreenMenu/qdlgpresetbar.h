#ifndef QDLGPRESETBAR_H
#define QDLGPRESETBAR_H

#include <QDialog>

namespace Ui{
  class QDlgPresetBar;
}

class QDlgPresetBar : public QDialog
{
    Q_OBJECT
public:
    explicit QDlgPresetBar(QWidget *parent = nullptr);

protected:
    virtual     void paintEvent(QPaintEvent *event);
    virtual     void resizeEvent(QResizeEvent *event);

signals:

public slots:

private:
    Ui::QDlgPresetBar*              ui;
};

#endif // QDLGPRESETBAR_H
