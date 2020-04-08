#include "xmlconfig.h"
#include <QCoreApplication>
#include <QDomDocument>
#include <QFile>
#include <QDebug>
#include <QDomNode>
#include <QDomElement>
#include <QNetworkDatagram>
#include "globalapplication.h"
#include "qmywidget.h"
#include "qmycombobox.h"

XmlConfig*       XmlConfig::s_pInst     = NULL;
XmlConfig::XmlConfig(QObject *parent) : QObject(parent)
{

}

void XmlConfig::Init()
{
    readConfig();

    m_pUdpSock          = new QUdpSocket(this);
    m_pUdpSock->bind(QHostAddress::LocalHost, UDPPORT_SCREENMENU);
    connect(m_pUdpSock, SIGNAL(readyRead()), this, SLOT(onUdpData()));

    connect(XmlConfig::GetInstance(), SIGNAL(notifyNowPrint()), this, SLOT(onNowPrint()));

    netGetZoomValue();
    netGetBrightValue();
}

void XmlConfig::setAppEventObjForCombo(QObject* pObj)
{
    if( m_pEventObj == pObj ){
        return;
    }
    if( m_pEventObj ){
        ((QMyWidget*)m_pEventObj)->setFocusOn(false);
        m_pEventObj     = NULL;
    }
    m_pEventObj     = pObj;
    ((QMyComboBox*)pObj)->setFocusOn(true);
    ((QMyComboBox*)pObj)->update();
}

void XmlConfig::setAppEventObj(QObject* pObj, bool bComboNew/*=false*/, bool bComboOld/*=false*/)
{
    qDebug()<<"xml setEventObj:"<<pObj;
    if( m_pEventObj == pObj ){
        return;
    }
    if( m_pEventObj ){
        if( bComboOld ){
             ((QMyComboBox*)m_pEventObj)->setFocusOn(false);
        }else{
            ((QMyWidget*)m_pEventObj)->setFocusOn(false);
        }
        m_pEventObj     = NULL;
    }
    m_pEventObj     = pObj;

    if( bComboNew ){
        ((QMyComboBox*)pObj)->setFocusOn(true);
        ((QMyComboBox*)pObj)->update();
    }else{
        ((QMyWidget*)pObj)->setFocusOn(true);
        ((QMyWidget*)pObj)->update();
    }
}

void XmlConfig::onNowPrint()
{
    char                szData[128]     = {0};
    ST_NetProtocol*     pNet            = (ST_NetProtocol*)szData;

    pNet->iCmd      = NetCmd_PrintNow_REQ;
    pNet->iLenData  = 0;
    m_pUdpSock->writeDatagram(szData, sizeof(ST_NetProtocol), QHostAddress("127.0.0.1"), UDPPORT_HI);

}

void XmlConfig::onUdpData()
{
    while( m_pUdpSock->hasPendingDatagrams() ){
        QNetworkDatagram    datagram        = m_pUdpSock->receiveDatagram();
        QByteArray          data            = datagram.data();
        ST_NetProtocol*     pNet            = (ST_NetProtocol*)data.data();

        qDebug()<<"datagram len:"<<data.length();
        if( data.length() == 0 ){
            break;
        }

        if( pNet->iCmd == NetCmd_GetZoom_RSP ){
            int     iVal        = 0;
            memcpy(&iVal, pNet->szData, pNet->iLenData);
            m_iZoomStep     = iVal;

            qDebug("cmd:%d, len:%d, val:%d", pNet->iCmd, pNet->iLenData, iVal);
        }else if( pNet->iCmd == NetCmd_SetZoom_RSP ){
            int     iVal        = 0;
            memcpy(&iVal, pNet->szData, pNet->iLenData);
            m_iZoomStep     = iVal;
            emit changeZoom(m_iZoomStep);

            qDebug("cmd:%d, len:%d, val:%d", pNet->iCmd, pNet->iLenData, iVal);
        }else if( pNet->iCmd == NetCmd_GetMouseButtonConfig_RSP || pNet->iCmd == NetCmd_SetMouseButtonConfig_RSP ){
            memcpy(&m_stMouseBtnConfig, pNet->szData, pNet->iLenData);

        }else if( pNet->iCmd == NetCmd_GetBright_RSP ){
            int     iVal        = 0;
            memcpy(&iVal, pNet->szData, pNet->iLenData);
            m_iBrightStep     = iVal;

            qDebug("cmd:%d, len:%d, val:%d", pNet->iCmd, pNet->iLenData, iVal);
        }else if( pNet->iCmd == NetCmd_SetBright_RSP ){
            int     iVal        = 0;
            memcpy(&iVal, pNet->szData, pNet->iLenData);
            m_iBrightStep     = iVal;
            emit changeBright(m_iBrightStep);

            qDebug("cmd:%d, len:%d, val:%d", pNet->iCmd, pNet->iLenData, iVal);
        }else if( pNet->iCmd == NetCmd_PrintNow_RSP ){
            qDebug("cmd:%d, len:%d,", pNet->iCmd, pNet->iLenData);
        }
    }
}

int XmlConfig::readConfig()
{
    QString             qstrOldPath         = QCoreApplication::applicationDirPath() + "/configbak.xml";
    QString             qstrPath            = QCoreApplication::applicationDirPath() + "/config.xml";
    QDomDocument        doc("config");
    QFile               file(qstrPath);

    if( !file.open(QIODevice::ReadOnly) ){
        file.setFileName(qstrOldPath);
        if( !file.open(QIODevice::ReadOnly) ){
            qDebug("xxx readConfig failed 1");
            return -1;
        }else{
            file.copy(qstrPath);
        }
    }

    if( !doc.setContent(&file) ){
      file.close();
      qDebug("xxx readConfig failed 2");
      return -1;
    }
    file.close();

    QString             qstrVal;
    QString             qstrAttr;
    QString             qstrTmp;
    QDomNode            attrNode;
    QDomNamedNodeMap    attrs;
    QDomElement         root            = doc.documentElement();
    QDomNode            comBtnSet       = root.firstChildElement("CamButtonSet");
    QDomNode            enhanceSet      = root.firstChildElement("EnhanceSet");
    QDomNode            preSet          = root.firstChildElement("PreSet");

    if( !preSet.isNull() ){
        QDomNode    SetItems            = preSet.firstChildElement("PreItems");
        if( !SetItems.isNull() ){
            QDomNode        item        = SetItems.firstChildElement("Item");
            while( !item.isNull() ){
                qstrVal      = item.toElement().text();
                attrs        = item.attributes();
                for(int i=0;i<attrs.size();i++){
                    attrNode    = attrs.item(i);
                    if( attrNode.nodeName() == "val" ){
                        qstrAttr             = attrNode.nodeValue();
                    }
                }
                m_mapPreSets[qstrAttr.toInt()]        = qstrVal;

                item         = item.nextSibling();
            }

            QDomNode        CurSetVal       = enhanceSet.firstChildElement("CurSetVal");
            if( !CurSetVal.isNull() ){
                m_iPreSet          = CurSetVal.toElement().text().toInt();
            }
        }
    }

    if( !enhanceSet.isNull() ){
        QDomNode    SetItems            = enhanceSet.firstChildElement("SetItems");
        if( !SetItems.isNull() ){
            QDomNode        item        = SetItems.firstChildElement("Item");
            while( !item.isNull() ){
                qstrVal      = item.toElement().text();
                attrs        = item.attributes();
                for(int i=0;i<attrs.size();i++){
                    attrNode    = attrs.item(i);
                    if( attrNode.nodeName() == "val" ){
                        qstrAttr             = attrNode.nodeValue();
                    }
                }
                m_mapEnhanceSets[qstrAttr.toInt()]        = qstrVal;

                item         = item.nextSibling();
            }

            QDomNode        CurSetVal       = enhanceSet.firstChildElement("CurSetVal");
            if( !CurSetVal.isNull() ){
                m_iEnhance          = CurSetVal.toElement().text().toInt();
            }
        }
    }

    if( !comBtnSet.isNull() ){
       QDomNode     ButtonSetItems      = comBtnSet.firstChildElement("ButtonSetItems");
       if( !ButtonSetItems.isNull() ){
           QDomNode     item        = ButtonSetItems.firstChildElement("Item");
           while( !item.isNull() ){
               qstrVal      = item.toElement().text();
               attrs        = item.attributes();
               for(int i=0;i<attrs.size();i++){
                   attrNode    = attrs.item(i);
                   if( attrNode.nodeName() == "val" ){
                       qstrAttr             = attrNode.nodeValue();
                   }
               }
               m_mapCamBtnSets[qstrAttr.toInt()]        = qstrVal;

               item         = item.nextSibling();
           }

           QDomNode     LeftButtonShort     = ButtonSetItems.firstChildElement("LeftButtonShort");
           if( !LeftButtonShort.isNull() ){
               attrs        = LeftButtonShort.attributes();
               for(int i=0;i<attrs.size();i++){
                   attrNode    = attrs.item(i);
                   if( attrNode.nodeName() == "val" ){
                       qstrTmp             = attrNode.nodeValue();
                       m_stMouseBtnConfig.iLeftShortPress       = qstrTmp.toInt();
                   }
               }
           }
           QDomNode     LeftButtonLong      = ButtonSetItems.firstChildElement("LeftButtonLong");
           if( !LeftButtonLong.isNull() ){
               attrs        = LeftButtonLong.attributes();
               for(int i=0;i<attrs.size();i++){
                   attrNode    = attrs.item(i);
                   if( attrNode.nodeName() == "val" ){
                       qstrTmp             = attrNode.nodeValue();
                       m_stMouseBtnConfig.iLeftLongPress        = qstrTmp.toInt();
                   }
               }
           }
           QDomNode     RightButtonShort    = ButtonSetItems.firstChildElement("RightButtonShort");
           if( !RightButtonShort.isNull() ){
               attrs        = RightButtonShort.attributes();
               for(int i=0;i<attrs.size();i++){
                   attrNode    = attrs.item(i);
                   if( attrNode.nodeName() == "val" ){
                       qstrTmp             = attrNode.nodeValue();
                       m_stMouseBtnConfig.iRightShortPress      = qstrTmp.toInt();
                   }
               }
           }
           QDomNode     RightButtonLong     = ButtonSetItems.firstChildElement("RightButtonLong");
           if( !RightButtonLong.isNull() ){
               attrs        = RightButtonLong.attributes();
               for(int i=0;i<attrs.size();i++){
                   attrNode    = attrs.item(i);
                   if( attrNode.nodeName() == "val" ){
                       qstrTmp             = attrNode.nodeValue();
                       m_stMouseBtnConfig.iRightLongPress       = qstrTmp.toInt();
                   }
               }
           }
       }
    }

    return 0;
}

void XmlConfig::onClickZoomAdd()
{
    int     iTmp        = m_iZoomStep;
    iTmp++;
    if( iTmp >= 5 ){
        iTmp     = 5;
    }

    netSetZoomValue(iTmp);
}

void XmlConfig::onClickZoomMinus()
{
    int     iTmp        = m_iZoomStep;
    iTmp--;
    if( iTmp <=0 ){
        iTmp     = 0;
    }

    netSetZoomValue(iTmp);
}

void XmlConfig::onClickBrightAdd()
{
    int     iTmp        = m_iBrightStep;
    iTmp++;
    if( iTmp >= 5 ){
        iTmp     = 5;
    }

    netSetBrightValue(iTmp);

}
void XmlConfig::onClickBrightMinus()
{
    int     iTmp        = m_iBrightStep;
    iTmp--;
    if( iTmp <=0 ){
        iTmp     = 0;
    }

    netSetBrightValue(iTmp);
}

int XmlConfig::netGetBrightValue()
{
    char                szData[128]     = {0};
    ST_NetProtocol*     pNet            = (ST_NetProtocol*)szData;

    pNet->iCmd      = NetCmd_GetBright_REQ;
    pNet->iLenData  = 0;
    m_pUdpSock->writeDatagram(szData, sizeof(ST_NetProtocol), QHostAddress("127.0.0.1"), UDPPORT_HI);
    return 0;
}

int XmlConfig::netSetBrightValue(int iVal)
{
    char                szData[128]     = {0};
    ST_NetProtocol*     pNet            = (ST_NetProtocol*)szData;
    int                 iLen            = 0;

    pNet->iCmd      = NetCmd_SetBright_REQ;
    pNet->iLenData  = sizeof(int);
    memcpy(pNet->szData, &iVal, sizeof(iVal));

    iLen        = sizeof(ST_NetProtocol) + pNet->iLenData;
    m_pUdpSock->writeDatagram(szData, iLen, QHostAddress("127.0.0.1"), UDPPORT_HI);
    return 0;
}

int XmlConfig::netGetZoomValue()
{
    char                szData[128]     = {0};
    ST_NetProtocol*     pNet            = (ST_NetProtocol*)szData;

    pNet->iCmd      = NetCmd_GetZoom_REQ;
    pNet->iLenData  = 0;
    m_pUdpSock->writeDatagram(szData, sizeof(ST_NetProtocol), QHostAddress("127.0.0.1"), UDPPORT_HI);
    return 0;
}

int XmlConfig::netSetZoomValue(int iVal)
{
    char                szData[128]     = {0};
    ST_NetProtocol*     pNet            = (ST_NetProtocol*)szData;
    int                 iLen            = 0;

    pNet->iCmd      = NetCmd_SetZoom_REQ;
    pNet->iLenData  = sizeof(int);
    memcpy(pNet->szData, &iVal, sizeof(iVal));

    iLen        = sizeof(ST_NetProtocol) + pNet->iLenData;
    m_pUdpSock->writeDatagram(szData, iLen, QHostAddress("127.0.0.1"), UDPPORT_HI);
    return 0;
}

int XmlConfig::netGetMouseButtonConfig()
{
    char                szData[128]     = {0};
    ST_NetProtocol*     pNet            = (ST_NetProtocol*)szData;

    pNet->iCmd      = NetCmd_GetMouseButtonConfig_REQ;
    pNet->iLenData  = 0;
    m_pUdpSock->writeDatagram(szData, sizeof(ST_NetProtocol), QHostAddress("127.0.0.1"), UDPPORT_HI);
    return 0;
}
int XmlConfig::netSetMouseButtonConfig(ST_MouseButtonSet& stSet)
{
    char                szData[128]     = {0};
    ST_NetProtocol*     pNet            = (ST_NetProtocol*)szData;
    int                 iLen            = 0;

    pNet->iCmd      = NetCmd_SetMouseButtonConfig_REQ;
    pNet->iLenData  = sizeof(stSet);
    memcpy(pNet->szData, &stSet, sizeof(stSet));

    iLen        = sizeof(ST_NetProtocol) + pNet->iLenData;
    m_pUdpSock->writeDatagram(szData, iLen, QHostAddress("127.0.0.1"), UDPPORT_HI);
    return 0;
}
