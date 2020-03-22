#include "xmlconfig.h"
#include <QCoreApplication>
#include <QDomDocument>
#include <QFile>
#include <QDebug>
#include <QDomNode>
#include <QDomElement>

XmlConfig*       XmlConfig::s_pInst     = NULL;
XmlConfig::XmlConfig(QObject *parent) : QObject(parent)
{

}

void XmlConfig::Init()
{
    readConfig();
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
                   }
               }
           }
       }
    }

    return 0;
}

int XmlConfig::onClickZoomAdd()
{
    m_iZoomStep++;
    if( m_iZoomStep >= 5 ){
        m_iZoomStep     = 5;
    }
    return m_iZoomStep;
}

int XmlConfig::onClickZoomMinus()
{
    m_iZoomStep--;
    if( m_iZoomStep <=0 ){
        m_iZoomStep     = 0;
    }
    return m_iZoomStep;
}

int XmlConfig::onClickBrightAdd()
{
    m_iBrightStep++;
    if( m_iBrightStep >= 5 ){
        m_iBrightStep     = 5;
    }
    return m_iBrightStep;
}
int XmlConfig::onClickBrightMinus()
{
    m_iBrightStep--;
    if( m_iBrightStep <=0 ){
        m_iBrightStep     = 0;
    }
    return m_iBrightStep;
}
