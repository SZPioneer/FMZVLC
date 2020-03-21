#ifndef XMLCONFIG_H
#define XMLCONFIG_H

#include <QObject>

class XmlConfig : public QObject
{
    Q_OBJECT
private:
    explicit XmlConfig(QObject *parent = nullptr);

    void    Init();
    int     readConfig();

    static XmlConfig*       s_pInst;

public:
    static XmlConfig*   GetInstance()
    {
        if( s_pInst == NULL ){
            s_pInst     = new XmlConfig(NULL);
            s_pInst->Init();
        }
        return s_pInst;
    }
    static void         Release()
    {
        if( s_pInst != NULL ){
            delete s_pInst;
            s_pInst     = NULL;
        }
    }

    int     zoomStep()
    {
        return m_iZoomStep;
    }
    int    onClickZoomAdd();
    int    onClickZoomMinus();

    int     brightStep()
    {
        return m_iBrightStep;
    }
    int     onClickBrightAdd();
    int     onClickBrightMinus();

signals:
    void    changeBright(int iBright);

public slots:

private:
    int     m_iZoomStep         = 0;            //0=<val<=5
    int     m_iBrightStep       = 0;            //0,5
};

#endif // XMLCONFIG_H
