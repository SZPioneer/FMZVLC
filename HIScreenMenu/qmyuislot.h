#ifndef QMYUISLOT_H
#define QMYUISLOT_H

#include <QObject>

class QMyUISlot : public QObject
{
    Q_OBJECT
private:
    explicit QMyUISlot(QObject *parent = nullptr);

    static QMyUISlot*       s_pInst;

public:
    static QMyUISlot*   GetInstance()
    {
        if( s_pInst == NULL ){
            s_pInst     = new QMyUISlot();
        }
        return s_pInst;
    }
    static void         Release()
    {
        if( s_pInst ){
            delete s_pInst;
        }
    }



signals:


public slots:


private:

};

#endif // QMYUISLOT_H
