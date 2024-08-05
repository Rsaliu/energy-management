#ifndef __SENSOR_VALUES_H__
#define __SENSOR_VALUES_H__

namespace SensorRead
{
    
    class SensorReadingInterface
    {
    public:
    
        SensorReadingInterface(int threshold, int pinNumber);

       
        virtual int readSensor() = 0;
        virtual bool getState() = 0;

    protected:
        int threshold;
        int pinNumber;
    };


    struct SensorPinConfig
    {
        int solarPin;
        int batteryPin;
        int peakAm;
        int peakPm;
    };


    class LDR : public SensorReadingInterface
    {
    public:
        LDR(int threshold, int pinNumber);
        int readSensor() override;
        bool getState() override;
    };


    class Battery : public SensorReadingInterface
    {
    public:
        Battery(int threshold, int pinNumber);
        int readSensor() override;
        bool getState() override;
    };


    class PeakPeriodAM : public SensorReadingInterface
    {
    public:
        PeakPeriodAM(int pinNumber);
        int readSensor() override;
        bool getState() override;
    };

    class PeakPeriodPM : public SensorReadingInterface
    {
    public:
        PeakPeriodPM(int pinNumber);
        int readSensor() override;
        bool getState() override;
    };
}

#endif 

