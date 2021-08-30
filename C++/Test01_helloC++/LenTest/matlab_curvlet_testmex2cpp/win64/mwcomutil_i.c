

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Mon Jan 18 22:14:07 2038
 */
/* Compiler settings for win64\mwcomutil.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=IA64 8.01.0622 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        EXTERN_C __declspec(selectany) const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif // !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_IMWUtil,0xC47EA90E,0x56D1,0x11d5,0xB1,0x59,0x00,0xD0,0xB7,0xBA,0x75,0x44);


MIDL_DEFINE_GUID(IID, LIBID_MWComUtil,0x30A247E2,0x36AD,0x4538,0x9E,0xA9,0x5C,0xD5,0x5E,0x3B,0x7E,0xF4);


MIDL_DEFINE_GUID(CLSID, CLSID_MWField,0x8449126B,0xBC62,0x4591,0x91,0x90,0x39,0xFD,0xDC,0xD2,0x5E,0xB5);


MIDL_DEFINE_GUID(CLSID, CLSID_MWStruct,0xD425868D,0xA9FA,0x457A,0xBD,0x6C,0xEC,0xDE,0xE0,0x61,0xB9,0x48);


MIDL_DEFINE_GUID(CLSID, CLSID_MWComplex,0x7ACD37DF,0xD8AD,0x4FF1,0xB9,0xF4,0x79,0x8C,0x4D,0xD2,0x0D,0x4E);


MIDL_DEFINE_GUID(CLSID, CLSID_MWSparse,0x36DECBBB,0x619D,0x4646,0xAD,0xE7,0xE6,0x4F,0x8B,0x7A,0x49,0xF9);


MIDL_DEFINE_GUID(CLSID, CLSID_MWArg,0x6CC22EA8,0x3D57,0x47A4,0xB8,0x66,0x97,0x33,0x2F,0x29,0xB3,0x3A);


MIDL_DEFINE_GUID(CLSID, CLSID_MWArrayFormatFlags,0x7B9C5F43,0xDCEB,0x45D4,0x95,0x5F,0xBA,0x2D,0xB6,0xD6,0xC4,0x70);


MIDL_DEFINE_GUID(CLSID, CLSID_MWDataConversionFlags,0x5FC31A25,0xB6E5,0x440A,0xB4,0xF8,0x17,0x7C,0x25,0x9B,0x2E,0x8D);


MIDL_DEFINE_GUID(CLSID, CLSID_MWUtil,0xE3EF7E85,0xADB7,0x46D1,0x87,0x31,0xE1,0x6C,0x21,0xC7,0x30,0x06);


MIDL_DEFINE_GUID(CLSID, CLSID_MWFlags,0x28E0A1D2,0x8FAC,0x46B2,0xB2,0x24,0xC7,0x71,0x8A,0x14,0xBB,0x5B);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



