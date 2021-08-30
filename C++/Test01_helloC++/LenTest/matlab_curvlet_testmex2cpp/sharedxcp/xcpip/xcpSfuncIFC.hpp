/* Copyright 2018-2019 The MathWorks, Inc. */

#ifndef xcpsfuncifc_hpp
#define xcpsfuncifc_hpp

#include <string>
#include <vector>
#include <functional>

#if !defined(MATLAB_MEX_FILE) || defined(XCP_STATIC_LIB)
#define XCPAPI
#else
#ifdef  BUILDXCP
#define XCPAPI __declspec(dllexport)
#else
#define XCPAPI __declspec(dllimport)
#endif
#endif

namespace xcp {
    namespace master {

        typedef void* HXCP;
        enum ETYPE: bool {
            XCP_SUCCESS = true,
            XCP_ERROR = false
        };
       
        XCPAPI HXCP getHandle(std::string tag);

        XCPAPI void releaseXCPHandle(std::string tag);

        XCPAPI bool isConnected(HXCP handle);
       
        XCPAPI const char* getErr(HXCP handle);

        namespace config {
            XCPAPI ETYPE registerSlave(HXCP handle, std::string seedkeylib, uint32_t mAddr, uint16_t mPort, const double* tl_info,
                const double* protocol_info, const double* daq_info, const double* ev_info, const double* sig_info, uint8_t ctr);
           
            XCPAPI bool isFrameInit();
            XCPAPI void initializeFramePool();

            XCPAPI ETYPE executeRx(HXCP handle);

            XCPAPI ETYPE spawnRxTx(HXCP handle);

            XCPAPI ETYPE runOnce(HXCP handle, double* daqOverload, double* stimOverload);
        }

        namespace bypass {
           
            XCPAPI void addDAQBypassFcn(std::string dlTag, std::function<void()> bypassTrig, uint8_t pri);

            XCPAPI bool daqReady(std::string dlTag);
        }

        namespace daqstim {
            XCPAPI ETYPE createDaqList(HXCP handle, uint16_t& dlNum, std::string dlTag, uint16_t event_channel_id,
                bool stimDirection, uint8_t priority, uint8_t rate, bool timestampEnable, bool pidOff);

            XCPAPI ETYPE addMeasurement(HXCP handle, uint16_t dlNum, int32_t measurement_id, int32_t portIdx, int portDT=-1);

            XCPAPI ETYPE daq(HXCP handle, uint16_t dlNum, std::vector<void*> outports, bool forceDatatypes);

            XCPAPI ETYPE stim(HXCP handle, uint16_t dlNum, std::vector<const void*> inports, bool forceDatatypes);
           
            XCPAPI void readDAQTime(HXCP handle, uint16_t dlNum, double* out);

            XCPAPI void setSTIMTime(HXCP handle, uint16_t dlNum, const double* timePtr);
        }

        typedef struct {
            double DataType;
            double Conversion;
            double Resolution;
            double Accuracy;
            double LowerLimit;
            double UpperLimit;
            struct {
                double ScalingUnit;
                double rate;
            }MaxRefresh;
            double ECUAddress;
            double ByteOrder;
            double Layout;
            double Dimension[3];
            double ArraySize;
        }SignalInfo_real_T;

        typedef struct {
            double  daqConfigType;
            double  overloadIndicator;
            double  maxDAQ;
            double  maxEventChannel;
            double  minDAQ;
            double  optimizationType;
            double  addressExtension;
            double  identificationField;
            double  granularityODTEntrySizeDAQ;
            double  maxODTEntrySizeDAQ;
            double  granularityODTEntrySizeSTIM;
            double  maxODTEntrySizeSTIM;
            double  bitwiseSTIMSupported;
            double  timestampTicks;
            double  timestampSize;
            double  timestampResolution;
        }Daq_real_T;

        typedef struct {
            double  channelNum;
            double  type;
            double  maxDAQ;
            double  TimeCycle;
            double  TimeUnitNr;
            double  Priority;
        }EventInfo_real_T;

        typedef struct {
            double  t1;
            double  t2;
            double  t3;
            double  t4;
            double  t5;
            double  t6;
            double  t7;
            double  maxCTO;
            double  maxDTO;
            double  byteOrder;
            double  addressGranularity;
        }Protocol_real_T;
       
        typedef struct {
            double      ipAddress;
            double      port;
        }XCP_IP_real_T;
    }
}

#endif

