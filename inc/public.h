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

#endif
