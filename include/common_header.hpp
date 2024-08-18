#ifndef __COMMON_HEADER_H__
#define __COMMON_HEADER_H__
#include <Arduino.h>
#ifdef PIO_UNIT_TESTING
    #include <iostream>
#endif
namespace Common
{
    static inline void println(const char*  data){
        #ifndef PIO_UNIT_TESTING 
            Serial.println(data);
        #else
            std::cout<<data<<std::endl;
            std::cout<< std::flush;
        #endif
    } 
    static inline void print(const char*  data){
        #ifndef PIO_UNIT_TESTING 
            Serial.print(data);
        #else
            std::cout<<data;
            std::cout<< std::flush;
        #endif
    } 

    struct SourceStateData{
        bool solarAboveThreshold;
        bool batteryAboveDoD;  
        SourceStateData(bool solarAboveThreshold,bool batteryAboveDoD):
        solarAboveThreshold(solarAboveThreshold),batteryAboveDoD(batteryAboveDoD){}
        void print(){
            char buff[100];
            sprintf(buff,"Source data: \nsolarAboveThreshold: %d\nbatteryAboveDoD: %d\n",
            solarAboveThreshold,batteryAboveDoD);
            Common::println(buff);
        }
    };

    struct SourcePeakData{
        bool peakAMOn;
        bool peakPMOn;   
        SourcePeakData(bool peakAMOn,bool peakPMOn):peakAMOn(peakAMOn),peakPMOn(peakPMOn){}
        void print(){
            char buff[100];
            sprintf(buff,"Peaks: \npeakAMOn: %d\npeakPMOn: %d\n",
            peakAMOn,peakPMOn);
            Common::println(buff);
        }
    };
    struct StateData
    {
        SourceStateData sourceStateData;
        SourcePeakData sourcePeakData;
        StateData(SourceStateData sourceStateData,SourcePeakData sourcePeakData):
        sourceStateData(sourceStateData),sourcePeakData(sourcePeakData){}
        StateData(bool solarAboveThreshold,bool batteryAboveDoD,bool peakAMOn,bool peakPMOn):
        sourceStateData(SourceStateData(solarAboveThreshold,batteryAboveDoD)),
        sourcePeakData(SourcePeakData(peakAMOn,peakPMOn)){}
        void print(){
            sourceStateData.print();
            sourcePeakData.print();
        }
    };



} // namespace name

#endif