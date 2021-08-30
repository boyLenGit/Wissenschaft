/* Copyright 2009-2019 The MathWorks, Inc. */

#ifndef XCP_MASTER_H
#define XCP_MASTER_H

#define XCP_OVER_CAN 1
#define XCP_OVER_UDP 2
#define XCP_OVER_USB 3

#include <stdio.h>
#include <stdlib.h>
#include "tmwtypes.h"

#if !defined(MATLAB_MEX_FILE)
#define XCPAPI
#else
#ifdef  BUILDXCP
#define XCPAPI __declspec(dllexport)
#else
#define XCPAPI __declspec(dllimport)
#endif
#endif

#define MAX_TAG_CHARS                       100

#define XCP_XTO_POOL_SIZE      50
#define XCP_MAX_NUM_DAQLISTS   100

#define XCP_CMD_CTO					  0
#define XCP_EV_CTO					  1
#define XCP_SERV_CTO				  2

#define MAX_STATE_PARAMS		 10

#define XCP_SUCCESS     0
#define XCP_ERROR       -1

#define ASSERT(c)   if(!(c))   {printf("XCP MASTER: Fatal Error\n"); while(1);}

#ifdef  DEBUG_XCP
#define SAVEF 	{fclose(gf);fopen("c:\\log.txt","a+");}
#define LOADF    {if(gf==NULL) gf=fopen("c:\\log.txt","w");}
#endif

#define XCP_GET_VAR_SIZE(dtype)     ((dtype==1 || dtype==2) ? sizeof(uint8_T) : \
	((dtype==3 || dtype==4) ? sizeof(uint16_T) : \
	((dtype==5 || dtype==6) ? sizeof(uint32_T) : \
    ((dtype==7 || dtype==8) ? sizeof(uint64_T) : \
    ((dtype==9)  ?  2                          : \
    ((dtype==10) ? sizeof(real32_T)            : \
	((dtype==11) ? sizeof(real_T) : 4 )))))))

#define XCP_GET_VAR_DTYPE(s,m)			(g_XCPMaster.slaveConfigs[s]->slaveInfo.measurements[m].DataType)

#define XCP_IS_DAQ_LIST_RUNNING(s,d)	(g_XCPMaster.slaveConfigs[s]->daqLists[d].status)
#define XCP_CONNECTION_STATUS(s)		(g_XCPMaster.slaveConfigs[s]->status)

#define  XCP_IDLE				       0

#define  XCP_CONNECT                   0xFF
#define  XCP_DISCONNECT                0xFE
#define  XCP_GET_COMM_MODE_INFO        0xFB
#define  XCP_GET_STATUS                0xFD
#define  XCP_CLEAR_DAQ_LIST            0xE3
#define  XCP_FREE_DAQ                  0xD6
#define  XCP_ALLOC_DAQ                 0xD5
#define  XCP_ALLOC_ODT                 0xD4
#define  XCP_ALLOC_ODT_ENTRY           0xD3
#define  XCP_SET_DAQ_PTR               0xE2
#define  XCP_WRITE_DAQ                 0xE1
#define  XCP_SET_DAQ_LIST_MODE         0xE0
#define  XCP_START_STOP_DAQ_LIST       0xDE
#define  XCP_GET_DAQ_CLOCK             0xDC
#define  XCP_START_STOP_SYNCH          0xDD
#define  XCP_PROGRAM_START             0xD2
								      
#define  XCP_GET_ID				       0xFA
#define  XCP_SET_REQUEST		       0xF9
#define  XCP_GET_SEED			       0xF8
#define  XCP_UNLOCK                    0xF7
#define  XCP_SET_MTA                   0xF6
#define  XCP_UPLOAD                    0xF5
#define  XCP_SHORT_UPLOAD              0xF4
#define  XCP_BUILD_CHECKSUM            0xF3
#define  XCP_TRANSPORT_LAYER_CMD       0xF2
#define  XCP_USER_CMD                  0xF1
#define  XCP_DOWNLOAD                  0xF0
#define  XCP_DOWNLOAD_NEXT             0xEF
#define  XCP_DOWNLOAD_MAX              0xEE
#define  XCP_SHORT_DOWNLOAD            0xED
#define  XCP_MODIFY_BITS               0xEC
#define  XCP_SET_CAL_PAGE              0xEB
#define  XCP_GET_CAL_PAGE              0xEA
#define  XCP_GET_PAG_PROCESSOR_INFO    0xE9
#define  XCP_GET_SEGMENT_INFO          0xE8
#define  XCP_GET_PAGE_INFO             0xE7
#define  XCP_SET_SEGMENT_MODE          0xE6
#define  XCP_GET_SEGMENT_MODE          0xE5
#define  XCP_COPY_CAL_PAGE             0xE4
#define  XCP_CLEAR_DAQ_LIST            0xE3
#define  XCP_SET_DAQ_PTR               0xE2
#define  XCP_WRITE_DAQ                 0xE1
#define  XCP_SET_DAQ_LIST_MODE         0xE0
#define  XCP_GET_DAQ_LIST_MODE         0xDF
#define  XCP_START_STOP_DAQ_LIST       0xDE
#define  XCP_START_STOP_SYNCH          0xDD
#define  XCP_GET_DAQ_CLOCK             0xDC
#define  XCP_READ_DAQ                  0xDB
#define  XCP_GET_DAQ_PROCESSOR_INFO    0xDA
#define  XCP_GET_DAQ_RESOLUTION_INFO   0xD9
#define  XCP_GET_DAQ_LIST_INFO         0xD8
#define  XCP_GET_DAQ_EVENT_INFO        0xD7
#define  XCP_FREE_DAQ                  0xD6
#define  XCP_ALLOC_DAQ                 0xD5
#define  XCP_ALLOC_ODT                 0xD4
#define  XCP_ALLOC_ODT_ENTRY           0xD3
#define  XCP_PROGRAM_START             0xD2
#define  XCP_PROGRAM_CLEAR             0xD1
#define  XCP_PROGRAM                   0xD0
#define  XCP_PROGRAM_RESET             0xCF
#define  XCP_GET_PGM_PROCESSOR_INFO    0xCE
#define  XCP_GET_SECTOR_INFO           0xCD
#define  XCP_PROGRAM_PREPARE           0xCC
#define  XCP_PROGRAM_FORMAT            0xCB
#define  XCP_PROGRAM_NEXT              0xCA
#define  XCP_PROGRAM_MAX               0xC9
#define  XCP_PROGRAM_VERIFY            0xC8

#define  POSITIVERESP                  255
#define  ERRCODE                       254
#define  ERRCMDBUSY                    16 
#define  ERRCMDSYNTAX                  33  
#define  ERRSEQUENCE                   41  
#define  ERRMEM_OVERFLOW               48    
#define  ERR_OUTOFRANGE                34    
#define  ERR_ACCESS_LOCKED             0x25
#define  ERR_CMD_UNKNOWN               0x20

#define	SLAVE_ERROR_OFFSET		       100
		 					          
#define	EVCODE					       253
#define	SERVCODE				       252
							          
#define  MAX_TAG_SIZE               100

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    TL_CAN = 0,
    TL_UDP,
    NUM_TL
}TransportLayerTypes;

typedef enum
{
	XCP_DAQ = 0,
	XCP_STIM
}Direction;

typedef enum{
	XCP_MASTER,
	XCP_SLAVE
}XcpNode;

typedef enum
{
   XCP_ERROR_OK = 0,
   XCP_ERROR_INVALID_PARAM,
   XCP_ERROR_MEM_ALLOCATION_ERROR,
   XCP_ERROR_NO_BUFFER,
   XCP_ERROR_SLAVECONF_NOT_INITIALIZED,
   XCP_ERROR_ODT_NOT_FOUND,
   XCP_ERROR_NOT_CONNECTED,
   XCP_ERROR_EXCEED_MAX_DAQ,
   XCP_ERROR_EXCEED_MAX_ODT_ENTRY_SIZE_DAQ,
   XCP_ERROR_EXCEED_MAX_ODT_ENTRY_SIZE_STIM,
   XCP_ERROR_EXCEED_MAX_DTO,
   XCP_ERROR_EXCEED_MAX_EC,
   XCP_ERROR_EC_NOT_FOUND,
   XCP_ERROR_TL_NOT_FOUND,
   XCP_ERROR_SK_NOT_FOUND,
   XCP_ERROR_TL_ERROR
}XcpError;

typedef enum {
	XCP_CONN_START = 0,
	XCP_CONN_IN_PROGRESS,
	XCP_CONN_COMPLETED,
	XCP_CONN_FAILED,
	XCP_CONN_DAQ_STARTED
} XcpStatus;

typedef void* HXCP;
typedef void* HMSR;

XCPAPI int32_T			 xcpmRegisterSlave(HXCP,
										   char* tag_tl,
                                           const wchar_t* seedkeydll,
						 				   real_T* proto,
						 				   real_T* daq,
						 				   real_T* ev,
                                           real_T* sig,
                                           TransportLayerTypes	 tlType,
						 				   real_T* tl
                                       );

#ifdef MATLAB_MEX_FILE
XCPAPI int32_T           xcpmSetTLDLL(char* tlpath);
#endif

XCPAPI int32_T			 xcpmFinalizeSlave(HXCP);

XCPAPI HXCP			     xcpmGetHandle(char* tag_xcp);

XCPAPI void              xcpmReleaseHandle(HXCP handle);

XCPAPI HMSR		         xcpmAddMeasurement(HXCP,
                                        int32_T daq_list_id,
                                        int32_T measurement_id,
                                        int32_T* error);

XCPAPI void              xcpmWriteMeasurementSpecifyDT(HMSR h, const void* in, int  in_dtid);

XCPAPI void              xcpmWriteMeasurement(HMSR h, const void* in);

XCPAPI void              xcpmReadMeasurementDouble(HMSR h, void* out);

XCPAPI void              xcpmReadMeasurement(HMSR h, void* out);

XCPAPI void              xcpmReadTimestamp(HXCP handle, int32_T dlnum, real_T* out);

XCPAPI int32_T			 xcpmCreateDaqList(HXCP,
						 				   int32_T	  event_channel,
						 				   Direction  direction,
						 				   int32_T	  priority,
						 				   int32_T	  rate,
						 				   int32_T	  timestamp,
						 				   int32_T	  pidoff,
						 				   int32_T	  num_odt_entries,
						 				   int32_T*   error);

XCPAPI int32_T			 xcpmStim(HXCP,int32_T daq_list_id, real_T tPhysical);

XCPAPI int32_T			 xcpmConnect(HXCP);		

XCPAPI XcpStatus		 xcpmGetConnStatus(HXCP);

XCPAPI int	   	     	 xcpmGetLastError(HXCP);
XCPAPI int               xcpmGetErrorMessage(HXCP, char* outstr, int size);

#ifdef __cplusplus
}
#endif

#endif
