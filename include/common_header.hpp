#ifndef __COMMON_HEADER_H__
#define __COMMON_HEADER_H__
namespace Common
{
    struct StateData
    {
        bool solarAboveThreshold;
        bool batteryAboveDoD;
        bool peakAMOn;
        bool peakPMOn;
    };

} // namespace name

#endif