/* Copyright 2008-2019 The MathWorks, Inc. */

#ifndef __NBLIB_H__
#define __NBLIB_H__

#include "tmwtypes.h"

#if !defined(MATLAB_MEX_FILE) || defined(XCP_STATIC_LIB)
# define NBAPI
#else
# ifdef  BUILDXCP
#  define NBAPI __declspec(dllexport)
# else
#  define NBAPI __declspec(dllimport)
# endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef void* (*MemAllocFcn)(uint32_T);
typedef void  (*MemFreeFcn)(void*);

typedef struct{
   int16_T      NumberOfQueues;
   uint16_T     *NumberInQueue;
   uint16_T     *QSizes;
   uint16_T     InitialBufferOffset;
   MemAllocFcn  AllocFcn;
   MemFreeFcn   FreeFcn;
}xpcNBConfig_T;

NBAPI extern xpcNBConfig_T xpcNBConfig;

typedef struct xpcNBHeader *xpcNBPtr;  

typedef struct xpcNBHeader {
    xpcNBPtr   Next;      
    uint16_T   Size;      
    uint16_T   Buffers;   
    uint16_T   Bytes;     
    uint16_T   Offset;    
    uint32_T   Reserved;  
} xpcNB;

typedef enum {
    XPC_NB_ERROR_OK = 0,                 
    XPC_NB_ERROR_NOT_INITIALIZED,        
    XPC_NB_ERROR_NOT_ENOUGH_MEMORY,      
    XPC_NB_ERROR_NO_MORE_BUFFERS,        
    XPC_NB_ERROR_MAGIC_NUMBER_CORRUPTION,
    XPC_NB_ERROR_INVALID_BUFFER_POINTER, 
    XPC_NB_ERROR_BUFFER_NOT_FOUND,       
    XPC_NB_ERROR_REQUESTED_SIZE_TOO_LARGE,
    XPC_NB_ERROR_POOL_STILL_IN_USE,      
    XPC_NB_ERROR_MAX
} xpcNBError;

NBAPI xpcNBError   xpcNBInit(void);                
NBAPI xpcNBError   xpcNBTerm(uint8_T tune);        
NBAPI xpcNBError   xpcNBCollectGarbage(void);      

NBAPI xpcNBError   xpcNBAllocFull(xpcNBPtr *buffer,
                          uint16_T bytes,
                          uint16_T numBuffers);
						 
NBAPI xpcNBError   xpcNBAlloc(xpcNBPtr *buffer,
                        uint16_T bytes,
                        uint16_T numBuffers);

NBAPI xpcNBError   xpcNBFree(xpcNBPtr buffer);       
NBAPI xpcNBError   xpcNBRelease(xpcNBPtr buffer);    
NBAPI xpcNBError   xpcNBAccept(xpcNBPtr buffer);     

NBAPI xpcNBError xpcNBSplitChain(xpcNBPtr chain, int32_T count, xpcNBPtr *head, xpcNBPtr *tail);
NBAPI xpcNBError xpcNBMergeChains(xpcNBPtr *chain, xpcNBPtr head, xpcNBPtr tail);

#define xpcNBNext(buffer)     ((buffer) ? (buffer)->Next : 0)

#define xpcNBBytes(buffer)    ((buffer) ? (buffer)->Bytes : 0)

#define xpcNBSetBytes(buffer, bytes)  ((buffer)->Bytes = (bytes))

#define xpcNBLength(buffer)           ( (buffer) ? (buffer)->Buffers : 0)

#define xpcNBData(buffer) \
    ((uint8_T*)(buffer) + sizeof(xpcNB) + (buffer)->Offset)

#define xpcNBShrinkHeader(buffer, bytes) \
    ((buffer)->Bytes -= (bytes), (buffer)->Offset += (bytes))

#define xpcNBExpandHeader(buffer, bytes) \
    ((buffer)->Bytes += (bytes), (buffer)->Offset -= (bytes))

#ifdef __cplusplus
}
#endif

#endif  
