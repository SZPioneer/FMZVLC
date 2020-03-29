#ifndef GLOBALAPPLICATION_H
#define GLOBALAPPLICATION_H

#include <QApplication>

class GlobalApplication : public QApplication
{
    Q_OBJECT
public:
    explicit GlobalApplication(int &argc, char **argv);

    bool notify(QObject*, QEvent *);

    virtual bool eventFilter(QObject *obj, QEvent *ev);

signals:

public slots:
};

#endif // GLOBALAPPLICATION_H
