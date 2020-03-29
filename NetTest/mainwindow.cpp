#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../inc/public.h"
#include <QNetworkDatagram>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_pUDPHI          = new QUdpSocket(this);
    m_pUDPHI->bind(QHostAddress::LocalHost, UDPPORT_HI);
    connect(m_pUDPHI, SIGNAL(readyRead()), this, SLOT(onMenuUdpData()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onMenuUdpData()
{
    while( m_pUDPHI->hasPendingDatagrams() ){
        QNetworkDatagram    datagram        = m_pUDPHI->receiveDatagram();
        QByteArray          data            = datagram.data();
        ST_NetProtocol*     pNet            = (ST_NetProtocol*)data.data();
        char                szData[128]     = {0};
        ST_NetProtocol*     pNetSend        = (ST_NetProtocol*)szData;
        int                 iSendLen        = 0;


        qDebug("cmd:%d, iLen:%d", pNet->iCmd, pNet->iLenData);

        if( pNet->iCmd == NetCmd_GetZoom_REQ ){
            pNetSend->iCmd          = NetCmd_GetZoom_RSP;
            pNetSend->iLenData      = sizeof(int);

            memcpy(pNetSend->szData, &m_iZoomVal, sizeof(int));
        }else if( pNet->iCmd == NetCmd_SetZoom_REQ ){
            pNetSend->iCmd          = NetCmd_SetZoom_RSP;
            pNetSend->iLenData      = sizeof(int);

            int         iTmp        = 0;
            memcpy(&iTmp, pNet->szData, sizeof(int));
            if( iTmp < 0 || iTmp > 5 ){
                break;
            }
            m_iZoomVal          = iTmp;
            memcpy(pNetSend->szData, &m_iZoomVal, sizeof(int));
        }

        iSendLen            = sizeof(ST_NetProtocol)+pNetSend->iLenData;
        m_pUDPHI->writeDatagram(szData, iSendLen, QHostAddress("127.0.0.1"), UDPPORT_SCREENMENU);
    }
}
