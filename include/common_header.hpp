#ifndef __COMMON_HEADER_H__
#define __COMMON_HEADER_H__
#include <Arduino.h>
namespace Common
{
    struct StateData
    {
        bool solarAboveThreshold;
        bool batteryAboveDoD;
        bool peakAMOn;
        bool peakPMOn;
        StateData(bool solarAboveThreshold,bool batteryAboveDoD,bool peakAMOn,bool peakPMOn):
        solarAboveThreshold(solarAboveThreshold),batteryAboveDoD(batteryAboveDoD),
        peakAMOn(peakAMOn),peakPMOn(peakPMOn){}
        void print(){
            Serial.println("States: ");
            Serial.println("solarAboveThreshold: "+(String)(int)solarAboveThreshold);
            Serial.println("batteryAboveDoD: "+(String)(int)batteryAboveDoD);
            Serial.println("peakAMOn: "+(String)(int)peakAMOn);
            Serial.println("peakPMOn: "+(String)(int)peakPMOn);
        }
    };

} // namespace name

#endif