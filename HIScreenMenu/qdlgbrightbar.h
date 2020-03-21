#ifndef QDLGBRIGHTBAR_H
#define QDLGBRIGHTBAR_H

#include "qdlgzoombar.h"

class QDlgBrightbar : public QDlgZoombar
{
    Q_OBJECT
public:
    explicit QDlgBrightbar(QWidget *parent = nullptr);

signals:

public slots:
    virtual void on_pushButton_min_clicked();
    virtual void on_pushButton_max_clicked();
};

#endif // QDLGBRIGHTBAR_H
