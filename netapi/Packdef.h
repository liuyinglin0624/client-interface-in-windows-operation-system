
#ifndef __DEF_PACKDEF__
#define __DEF_PACKDEF__

#include<QHostAddress>
#include<QByteArray>
#include<QDebug>
#include<QFile>
#include<QDateTime>
#include <winsock2.h>

#define BOOL bool
#define DEF_PACK_BASE  (10000)

#define _DEF_SERVERIP  ("192.168.1.110")
#define _DEF_PORT  8899

#define _DEF_COMMANDANALYSISIP ("127.0.0.1")
#define _DEF_COMMANDANALYSISPORT  9090


/////////////////////机器人服务器网络//////////////////////////////////////
#define  DEF_PACK_CHATTER_RQ    (DEF_PACK_BASE + 1)
#define  DEF_PACK_CHATTER_RS    (DEF_PACK_BASE + 2)

#define  DEF_PACK_SPEED_INFO    (DEF_PACK_BASE + 3)

#define  DEF_PACK_STOP0_RQ      (DEF_PACK_BASE + 4)
#define  DEF_PACK_STOP0_RS      (DEF_PACK_BASE + 5)

#define  DEF_PACK_BASEMOVEA1_RQ (DEF_PACK_BASE + 6)
#define  DEF_PACK_BASEMOVEA1_RS (DEF_PACK_BASE + 7)

// 控制命令请求结果
#define  stop0_fail          0
#define  stop0_success       1

#define  basemoveA1_fail     0
#define  basemoveA1_success  1

#define DEF_PACK_COUNT (100)

#define MAX_SIZE            (100  )
#define DEF_HOBBY_COUNT     (8  )
#define MAX_CONTENT_LEN     (4096 )
#define COMMAND_LENGTH      (10)

/////////////////////机器人服务器网络//////////////////////////////////////

/////////////////////////指令解析服务器网络////////////////////////
#define DEF_ANALYSIS_BASE  (20000)

#define DEF_ANALYSIS_FAIL_RS      (DEF_ANALYSIS_BASE - 1)
#define DEF_ANALYSIS_QUIT_RQ      (DEF_ANALYSIS_BASE + 0)

#define DEF_ANALYSIS_CHATTER_RQ   (DEF_ANALYSIS_BASE + 1)
#define DEF_ANALYSIS_CHATTER_RS   (DEF_ANALYSIS_BASE + 2)

#define DEF_ANALYSIS_SPEECH_RQ    (DEF_ANALYSIS_BASE + 3)

#define DEF_ANALYSIS_BASEMOVE_RS    (DEF_ANALYSIS_BASE + 4)
/////////////////////////指令解析服务器网络////////////////////////

#define DEF_MAX_BUF	  1024
#define DEF_BUFF_SIZE	  4096


typedef int PackType;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct STRU_CHATTRE_RQ
{
    STRU_CHATTRE_RQ()
    {
        m_nType = DEF_PACK_CHATTER_RQ;
        memset(m_szContext,0,MAX_SIZE);
    }
    PackType m_nType;
    char m_szContext[MAX_SIZE];
}STRU_CHATTER_RQ;

typedef struct STRU_CHATTRE_RS
{
    STRU_CHATTRE_RS()
    {
        m_nType = DEF_PACK_CHATTER_RS;
        memset(m_szContext,0,MAX_SIZE);
    }
    PackType m_nType;
    char m_szContext[MAX_SIZE];
}STRU_CHATTRE_RS;

typedef struct STRU_SPEED_INFO
{
    STRU_SPEED_INFO()
    {
        m_nType = DEF_PACK_SPEED_INFO;
    }
    PackType m_nType;
    float m_fLinearSpeed;
    float m_fAngerSpeed;
}STRU_SPEED_INFO;

typedef struct STRU_STOP0_RQ
{
    STRU_STOP0_RQ()
    {
        m_nType = DEF_PACK_STOP0_RQ;
    }
    PackType m_nType;
}STRU_STOP0_RQ;

typedef struct STRU_STOP0_RS
{
    STRU_STOP0_RS()
    {
        m_nType = DEF_PACK_STOP0_RS;
        m_nResult = stop0_fail;
    }
    PackType m_nType;
    int      m_nResult;
}STRU_STOP0_RS;

typedef struct STRU_BASEMOVEA1_RQ
{
    STRU_BASEMOVEA1_RQ()
    {
        m_nType = DEF_PACK_BASEMOVEA1_RQ;
        memset(m_szAction,0,COMMAND_LENGTH);
        memset(m_szForward,0,COMMAND_LENGTH);
        memset(m_szDistance,0,COMMAND_LENGTH);
        m_nlinearSpeed = 0;
        m_nAngleSpeed = 0;
    }
    PackType m_nType;
    char m_szAction[COMMAND_LENGTH];
    char m_szForward[COMMAND_LENGTH];
    char m_szDistance[COMMAND_LENGTH];
    int  m_nlinearSpeed;
    int  m_nAngleSpeed;
}STRU_BASEMOVEA1_RQ;

typedef struct STRU_BASEMOVEA1_RS
{
    STRU_BASEMOVEA1_RS()
    {
        m_nType = DEF_PACK_BASEMOVEA1_RS;
        m_nResult = basemoveA1_fail;
    }
    PackType m_nType;
    int      m_nResult;
}STRU_BASEMOVEA1_RS;


// 与指令解析服务器的消息往来
typedef struct STRY_ANALYSIS_QUIT_RQ
{
    STRY_ANALYSIS_QUIT_RQ()
    {
        m_nType = DEF_ANALYSIS_QUIT_RQ;
        memset(m_szContext,0,MAX_SIZE);
    }
    PackType m_nType;
    char m_szContext[MAX_SIZE];
}STRY_ANALYSIS_QUIT_RQ;


typedef struct STRU_ANALYSIS_CHART_RQ
{
    STRU_ANALYSIS_CHART_RQ()
    {
        m_nType = DEF_ANALYSIS_CHATTER_RQ;
        memset(m_szContext,0,MAX_SIZE);
    }
    PackType m_nType;
    char m_szContext[MAX_SIZE];
}STRU_ANALYSIS_CHART_RQ;

typedef struct STRU_ANALYSIS_CHART_RS
{
    STRU_ANALYSIS_CHART_RS()
    {
        m_nType = DEF_ANALYSIS_CHATTER_RQ;
        memset(m_szContext,0,MAX_SIZE);
    }
    PackType m_nType;
    char m_szContext[MAX_SIZE];
}STRU_ANALYSIS_CHART_RS;

typedef struct STRU_ANALYSIS_SPEECHRQ
{
    STRU_ANALYSIS_SPEECHRQ()
    {
        m_nType = DEF_ANALYSIS_SPEECH_RQ;
        memset(m_szContext,0,MAX_SIZE);
    }
    PackType m_nType;
    char m_szContext[MAX_SIZE];
}STRU_ANALYSIS_SPEECHRQ;


typedef struct STRU_ANALYSIS_BASEMOVE_RS
{
    STRU_ANALYSIS_BASEMOVE_RS()
    {
        m_nType = DEF_ANALYSIS_BASEMOVE_RS;
        memset(m_szContext1,0,COMMAND_LENGTH);
        memset(m_szContext2,0,COMMAND_LENGTH);
        memset(m_szContext3,0,COMMAND_LENGTH);
    }
    PackType m_nType;
    char m_szContext1[COMMAND_LENGTH];
    char m_szContext2[COMMAND_LENGTH];
    char m_szContext3[COMMAND_LENGTH];
}STRU_ANALYSIS_BASEMOVE_RS;

////登录请求
//typedef struct STRU_LOGIN_RQ
//{
//    STRU_LOGIN_RQ()
//    {
//        m_nType = DEF_PACK_LOGIN_RQ;
//        memset(m_szUser,0,MAX_SIZE);
//        memset(m_szPassword,0,MAX_SIZE);
//    }

//    PackType m_nType;   //包类型
//    char     m_szUser[MAX_SIZE] ; //用户ID
//    char     m_szPassword[MAX_SIZE];  //密码
//}STRU_LOGIN_RQ;


////登录回复
//typedef struct STRU_LOGIN_RS
//{
//    STRU_LOGIN_RS()
//    {
//        m_nType= DEF_PACK_LOGIN_RS;
//    }
//    PackType m_nType;   //包类型
//    int  m_UserID;
//    int  m_lResult ; //注册结果

//}STRU_LOGIN_RS;


////注册请求
//typedef struct STRU_REGISTER_RQ
//{
//    STRU_REGISTER_RQ()
//    {
//        m_nType = DEF_PACK_REGISTER_RQ;
//        memset(m_szUser,0,MAX_SIZE);
//        memset(m_szPassword,0,MAX_SIZE);
//    }

//    PackType m_nType;   //包类型
//    char     m_szUser[MAX_SIZE] ; //用户名
//    char     m_szPassword[MAX_SIZE];  //密码

//}STRU_REGISTER_RQ;

////注册回复
//typedef struct STRU_REGISTER_RS
//{
//    STRU_REGISTER_RS()
//    {
//        m_nType= DEF_PACK_REGISTER_RS;
//    }
//    PackType m_nType;   //包类型
//    int  m_lResult ; //注册结果

//}STRU_REGISTER_RS;

////创建房间请求
//typedef struct STRU_CREATEROOM_RQ
//{
//    STRU_CREATEROOM_RQ()
//    {
//        m_nType = DEF_PACK_CREATEROOM_RQ;
//        m_UserID = 0;
//        m_RoomID = 0;
//    }

//    PackType m_nType;   //包类型
//    int m_UserID;
//    int m_RoomID;

//}STRU_CREATEROOM_RQ;

////创建房间回复
//typedef struct STRU_CREATEROOM_RS
//{
//    STRU_CREATEROOM_RS()
//    {
//        m_nType= DEF_PACK_CREATEROOM_RS;
//        m_lResult = 0;
//        m_RoomId = 0;
//        m_AudioPort = 0;
//        memset( m_AudioIP , 0, 20);
//    }
//    PackType m_nType;   //包类型
//    int  m_lResult ;    //注册结果
//    int  m_RoomId;
//    int  m_AudioPort;
//    char m_AudioIP[20];

//}STRU_CREATEROOM_RS;

////加入房间请求
//typedef struct STRU_JOINROOM_RQ
//{
//    STRU_JOINROOM_RQ()
//    {
//        m_nType = DEF_PACK_JOINROOM_RQ;
//        m_UserID = 0;
//        m_RoomID = 0;
//    }

//    PackType m_nType;   //包类型
//    int m_UserID;
//    int m_RoomID;

//}STRU_JOINROOM_RQ;
////加入房间回复
//typedef struct STRU_JOINROOM_RS
//{
//    STRU_JOINROOM_RS()
//    {
//        m_nType= DEF_PACK_JOINROOM_RS;
//        m_lResult = 0;
//        m_RoomId = 0;
//        m_AudioPort = 0;
//        memset(m_AudioIP,0,20);
//    }
//    PackType m_nType;   //包类型
//    int  m_lResult ;    //注册结果
//    int  m_RoomId;
//    int m_AudioPort;
//    char m_AudioIP[20];

//}STRU_JOINROOM_RS;

////房间成员请求
//typedef struct STRU_ROOM_MEMBER_RQ
//{
//    STRU_ROOM_MEMBER_RQ()
//    {
//        m_nType= DEF_PACK_ROOM_MEMBER;
//        m_AudioPort = 0;
//        m_UserID =0;
//        memset(m_szUser,0,MAX_SIZE);
//        memset(m_RtmpUrl,0,MAX_SIZE);
//        memset(m_AudioIP,0,20);
//    }
//    PackType m_nType;   //包类型
//    int m_UserID;
//    int m_AudioPort;
//    char m_szUser[MAX_SIZE];
//    char m_RtmpUrl[MAX_SIZE];
//    char m_AudioIP[20];

//}STRU_ROOM_MEMBER_RQ;


////离开房间请求
//typedef struct STRU_LEAVEROOM_RQ
//{
//    STRU_LEAVEROOM_RQ()
//    {
//        m_nType = DEF_PACK_LEAVEROOM_RQ;
//        m_nUserId = 0;
//        m_RoomId = 0;
//    }
//    PackType   m_nType;   //包类型
//    int    m_nUserId; //用户ID
//    int    m_RoomId;
//}STRU_LEAVEROOM_RQ;
////离开房间回复
//typedef struct STRU_LEAVEROOM_RS
//{
//    STRU_LEAVEROOM_RS()
//    {
//        m_nType = DEF_PACK_LEAVEROOM_RS;
//        m_UserID = 0;
//        memset(szUserName,0,MAX_SIZE);
//    }
//    PackType   m_nType;   //包类型
//    int m_UserID;
//    char szUserName[MAX_SIZE];
//}STRU_LEAVEROOM_RS;



#endif
