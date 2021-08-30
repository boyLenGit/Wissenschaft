/* Copyright 2016-2018 The MathWorks, Inc. */

#ifndef UDPTL_H
#define UDPTL_H

#include <stdlib.h>
#include <stdint.h>
#include "xcpcore_udptl_spec.h"

#define UTLAPI XCPCORE_UDPTL_EXPORT_FCN
#define UDP_MAX_SIZE 65504
#define UTL_ERROR                          -1
#define UTL_SUCCESS                         0
#define MAX_TAG_CHARS                       100

#ifdef __cplusplus
extern "C" {
#endif

    typedef enum{
        UTL_ERROR_SOCKET_ERROR = -1,
        UTL_ERROR_OK = 0,
        UTL_ERROR_NOT_INITIALIZED,
        UTL_ERROR_PROTOCOL_ERROR,
        UTL_ERROR_MAX
    }UtlError;

    typedef enum{
        TL_CTR_DISABLED = 0,
        TL_CTR_GLOBAL,
        TL_CTR_SEPARATE_DAQ,
        TL_CTR_PER_MSG_TYPE
    }UtlCTRErrorDetection;

    typedef void * HUTL;

    typedef int(*PL_IPReceiveCallback_T)(HUTL handle, uint32_t fromAddress, uint16_t fromPort, uint8_t* data, uint32_t length);
    typedef int(*PL_GetErrorMessage_T)(HUTL handle, char*, int);

    typedef struct{
        int pid;
        void* param;
        PL_IPReceiveCallback_T udpMsgHndlr;
        PL_GetErrorMessage_T getErrorMessage;
    }ProtocolInfo;

    UTLAPI HUTL          utlGetHandle(char *);
    UTLAPI int           utlGetErrorMessage(HUTL handle, char * errMsg, int size);
    UTLAPI ProtocolInfo* utlGetProtocolInterface(HUTL handle);
    UTLAPI int           utlInitialize(HUTL handle, uint32_t localAddress_l, uint16_t localPort_s, uint8_t errorChecking);
    UTLAPI uint8_t       utlErrorCheckingType(HUTL handle);
    UTLAPI void          utlTerminate(HUTL handle);
    UTLAPI void          utlReleaseHandle(HUTL);
    UTLAPI void          utlAttach(HUTL, ProtocolInfo *);
    UTLAPI void          utlDetach(HUTL);
    UTLAPI int           utlSendFrame(HUTL, uint32_t toAddress_l, uint16_t toPort_s, uint8_t* data, uint16_t dataLength);
    UTLAPI int           utlExecuteRx(HUTL, int* bytesRecevied);

#ifdef __cplusplus
}
#endif

#endif

