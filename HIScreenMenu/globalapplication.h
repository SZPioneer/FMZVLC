#ifndef GLOBALAPPLICATION_H
#define GLOBALAPPLICATION_H

#include <QApplication>

class GlobalApplication : public QApplication
{
    Q_OBJECT
public:
    explicit GlobalApplication(int &argc, char **argv);


    virtual bool    notify(QObject*, QEvent *);

private:
    void        onWheel(QObject*, QEvent*);
    bool        onKey(QObject*,QEvent*);

signals:

public slots:


};

#endif // GLOBALAPPLICATION_H
