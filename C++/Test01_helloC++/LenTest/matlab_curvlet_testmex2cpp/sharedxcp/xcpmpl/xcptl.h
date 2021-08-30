/* Copyright 2016-2019 The MathWorks, Inc. */

#ifndef XCP_TL_H
#define XCP_TL_H

#include "sharedxcp/xcpmpl/cnblib.h"

#if !defined(MATLAB_MEX_FILE) || defined(XCP_STATIC_LIB)
# define XTLAPI
#else
# ifdef  BUILDXTL
#  define XTLAPI __declspec(dllexport)
# else
#  define XTLAPI __declspec(dllimport)
# endif
#endif

#define NO_PIDOFF				    -1
#define MAX_TAG_CHARS                       100

#ifdef __cplusplus
extern "C" {
#endif

enum {
   XCP_ERROR_TL = -1,
   XCP_ERROR_TL_OK = 0,
   XCP_ERROR_TL_NOT_ATTACHED,
   XCP_ERROR_TL_EXCEED_MAX_DAQLIST,
   XCP_ERROR_TL_ALREADY_REGISTERED,
   XCP_ERROR_TL_NO_DATA,
   XCP_ERROR_TL_DOWNSTREAM_ERROR,
   XCP_ERROR_TL_UPSTREAM_ERROR,
   XCP_ERROR_TL_RX_CTR_ERROR
};

#pragma pack(push,4)
typedef struct{
	int32_T tlId;
}XCPTransportLayer;
#pragma pack(pop)

typedef int (*XCPReceiveCallback_T)(void*,int32_T,uint8_T*,uint8_T);
typedef void (*XCPPostTransmitCallback_T)(void*,xpcNBPtr);
typedef int (*XCPGetErrorMessage_T)(void*, char*, int);

typedef struct{
   void*   param;
   XCPReceiveCallback_T       xcpReceiveCb;
   XCPPostTransmitCallback_T  xcpPostTransmitCb;
   XCPGetErrorMessage_T       xcpGetErrorMessage;
}XCPUpstreamIface;

typedef void* HTL;

XTLAPI   int  xcpCANTlSend(HTL, xpcNBPtr buffer);
XTLAPI   int  xcpUDPTlSend(HTL, xpcNBPtr buffer);

XTLAPI   int  xcpCANTlGetProtocolOffset(void);
XTLAPI   int  xcpUDPTlGetProtocolOffset(void); 

XTLAPI   HTL  xcpCANTlAttach(char *tag_s, char* tag_t, real_T* t, XCPUpstreamIface xi);
XTLAPI   HTL  xcpUDPTlAttach(char *tag_s, char* tag_t, real_T* t, XCPUpstreamIface xi);

XTLAPI   int  xcpCANTlDetach(HTL);
XTLAPI   int  xcpUDPTlDetach(HTL);

#ifdef __cplusplus
}
#endif

#endif
