/* Copyright 2012-2017 The MathWorks, Inc. */

#ifndef CANTL_H
#define CANTL_H

#include <stdio.h>
#include <stdlib.h>
#include "tmwtypes.h"
#if defined(XPCMSVISUALC) || defined(SIMULINK_REAL_TIME)
    #include "xpctarget.h"
#endif

#ifdef  BUILDXTL
#define CANAPI __declspec(dllexport)
#else
#if !defined(MATLAB_MEX_FILE) || defined(XCP_STATIC_LIB)
#define CANAPI
#else
#define CANAPI __declspec(dllimport)
#endif
#endif
#define CTL_ERROR                           -1
#define CTL_SUCCESS                         0
#define MAX_TAG_CHARS                       100

#ifdef __cplusplus
extern "C" {
#endif

typedef enum{
	CTL_ERROR_OK = 0,
	CTL_ERROR_MAX_CTL_EXCEEDED,
	CTL_ERROR_INVALID_PARAM,
	CTL_ERROR_MEM
}CtlError;

typedef struct
{
	void*    Channel;
	uint32_T FrameCounter;
	uint32_T ChannelWidth;
}CanInterface;

typedef void * HCTL;

typedef void (*PL_ReceiveCallback_T)(void*,uint32_T,uint8_T*,uint8_T);
typedef void (*PL_ReceiveCallbackAll_T)(void*,uint32_T,uint8_T*,uint8_T,uint8_T,uint8_T,uint8_T);
typedef void (*PL_PostTransmitCallback_T)(void*,void*);

typedef struct{
	int32_T						  pid;
	void*				           param;
	PL_ReceiveCallback_T	     stdCANMsgHndlr;
	PL_ReceiveCallback_T      extCANMsgHndlr;
	PL_ReceiveCallback_T      errCANMsgHndlr;
	PL_ReceiveCallbackAll_T   allCANMsgHndlr;
   PL_PostTransmitCallback_T postTransmitCb;
}ProtocolInfo;

CANAPI HCTL     ctlGetHandle(char *tag);
CANAPI void     ctlReleaseHandle(HCTL);
CANAPI void     ctlAttach(HCTL,ProtocolInfo *pinfo);
CANAPI void     ctlDetach(HCTL);
CANAPI void     ctlSendFrame(HCTL hc, void*, uint_T canid);
CANAPI int32_T  ctlExecuteTx(HCTL handle, void* out_buf, uint32_T buf_size);
CANAPI int32_T  ctlExecuteRx(HCTL handle, void* in_buf,  uint32_T rx_count);

#ifdef __cplusplus
}
#endif

#endif

