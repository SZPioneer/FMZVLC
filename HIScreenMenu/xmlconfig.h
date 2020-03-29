#ifndef XMLCONFIG_H
#define XMLCONFIG_H

#include <QObject>
#include <QMap>
#include <QUdpSocket>
#include "../inc/public.h"



typedef QMap<int,QString>       MapCamButtonSets;
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
    void    onClickZoomAdd();
    void    onClickZoomMinus();

    int     brightStep()
    {
        return m_iBrightStep;
    }
    void     onClickBrightAdd();
    void     onClickBrightMinus();

    int     netGetZoomValue();
    int     netSetZoomValue(int iVal);
    int     netGetMouseButtonConfig();
    int     netSetMouseButtonConfig(ST_MouseButtonSet& stSet);

signals:
    void    changeBright(int iBright);
    void    changeZoom(int iZoomVal);
    void    changeMouseButtonConfig(ST_MouseButtonSet stConfig);

public slots:
    void    onUdpData();


private:
    MapCamButtonSets    m_mapCamBtnSets;
    QUdpSocket*         m_pUdpSock          = NULL;

public:
    int                 m_iZoomStep         = 0;            //0=<val<=5
    int                 m_iBrightStep       = 0;            //0,5
    int                 m_iLeftBtnShortVal  = 0;
    int                 m_iLeftBtnLongVal   = 0;
    int                 m_iRightBtnShortVal = 0;
    int                 m_iRightBtnLongVal  = 0;
    ST_MouseButtonSet   m_stMouseBtnConfig;
};

#endif // XMLCONFIG_H
