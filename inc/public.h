#ifndef __MYPUBLIC_H__
#define __MYPUBLIC_H__

#define UDPPORT_SCREENMENU          22222
#define UDPPORT_HI                  22223

typedef enum{
    NetCmd_GetZoom_REQ          = 0,
    NetCmd_GetZoom_RSP,
    NetCmd_SetZoom_REQ,
    NetCmd_SetZoom_RSP,
    NetCmd_GetMouseButtonConfig_REQ,
    NetCmd_GetMouseButtonConfig_RSP,
    NetCmd_SetMouseButtonConfig_REQ,
    NetCmd_SetMouseButtonConfig_RSP,
    NetCmd_GetBright_REQ,
    NetCmd_GetBright_RSP,
    NetCmd_SetBright_REQ,
    NetCmd_SetBright_RSP,
    NetCmd_PrintNow_REQ,
    NetCmd_PrintNow_RSP,
}emNetCMD;
typedef struct tagNetProtocol{
    int         iCmd;
    int         iLenData;
    char        szData[];
}ST_NetProtocol;

//摄像头按键设定
typedef struct tagMouseButtonSet{
    int         iLeftShortPress;
    int         iLeftLongPress;
    int         iRightShortPress;
    int         iRightLongPress;
    int         iMidShortPress;
    int         iMidLongPress;

    tagMouseButtonSet()
    {
        this->iLeftLongPress        = 0;
        this->iLeftShortPress       = 0;
        this->iRightLongPress       = 0;
        this->iRightShortPress      = 0;
        this->iMidLongPress         = 0;
        this->iMidShortPress        = 0;
    }
    tagMouseButtonSet(const tagMouseButtonSet& other)
    {
        this->iLeftLongPress        = other.iLeftLongPress;
        this->iLeftShortPress       = other.iLeftShortPress;
        this->iRightLongPress       = other.iRightLongPress;
        this->iRightShortPress      = other.iRightShortPress;
        this->iMidLongPress         = other.iMidLongPress;
        this->iMidShortPress        = other.iMidShortPress;
    }
    tagMouseButtonSet& operator=(const tagMouseButtonSet& other)
    {
        if( this == &other ){
            return *this;
        }

        this->iLeftLongPress        = other.iLeftLongPress;
        this->iLeftShortPress       = other.iLeftShortPress;
        this->iRightLongPress       = other.iRightLongPress;
        this->iRightShortPress      = other.iRightShortPress;
        this->iMidLongPress         = other.iMidLongPress;
        this->iMidShortPress        = other.iMidShortPress;

        return *this;
    }
}ST_MouseButtonSet;

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
/*
一、采用UDP点对点通信，界面进程使用22222端口，后台进程使用22223端口。

二、通信协议

typedef struct tagNetProtocol{
    int         iCmd;
    int         iLenData;
    char        szData[];
}ST_NetProtocol;

1、获取缩放值
    请求方发送
    tagNetProtocol.iCmd			= NetCmd_GetZoom;
    tagNetProtocol.iLenData		= 0;
    ##################
    # ST_NetProtocol #
    ##################
    响应方发送
    tagNetProtocol.iCmd			= NetCmd_GetZoom;
    tagNetProtocol.iLenData		= sizeof(int)
    tagNetProtocol.szData[0~3]	= value				//value取值0~5
    ################################
    # ST_NetProtocol # szData(int) #
    ################################

2、设置缩放值

3、获取亮度值
4、设置亮度值

5、获取按键设置
    请求方发送
    tagNetProtocol.iCmd			= NetCmd_GetMouseButtonConfig_REQ;
    tagNetProtocol.iLenData		= 0;
    ##################
    # ST_NetProtocol #
    ##################
    响应方发送
    ######################################
    # ST_NetProtocol # ST_MouseButtonSet #
    ######################################
6、设置按键设置
*/

#endif
