#ifndef XMLCONFIG_H
#define XMLCONFIG_H

#include <QObject>
#include <QMap>
#include <QUdpSocket>
#include "../inc/public.h"



typedef QMap<int,QString>       MapCamButtonSets;
typedef QMap<int,QString>       MapEnhanceSets;
typedef QMap<int,QString>       MapPreSets;
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

    void    setAppEventObjForCombo(QObject* pObj);
    void    setAppEventObj(QObject* pObj, bool bComboNew=false, bool bComboOld=false);

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
    int     netGetBrightValue();
    int     netSetBrightValue(int iVal);

signals:
    void    notifyKeyEnter(QObject*);
    void    notifyWheel(QObject*, int iStep);
    void    changeBright(int iBright);
    void    changeZoom(int iZoomVal);
    void    changeMouseButtonConfig(ST_MouseButtonSet stConfig);
    void    notifyEnterToolbar(QWidget*);
    void    notifyNowPrint();

public slots:
    void    onUdpData();
    void    onNowPrint();

private:

    QUdpSocket*         m_pUdpSock          = NULL;

public:
    QObject*            m_pEventObj         = NULL;
    int                 m_iZoomStep         = 0;            //0=<val<=5
    int                 m_iBrightStep       = 0;            //0,5
    ST_MouseButtonSet   m_stMouseBtnConfig;
    MapCamButtonSets    m_mapCamBtnSets;
    MapEnhanceSets      m_mapEnhanceSets;
    int                 m_iEnhance          = 0;
    MapPreSets          m_mapPreSets;
    int                 m_iPreSet           = 0;
};

#endif // XMLCONFIG_H
