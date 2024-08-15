#ifndef __SENSOR_VALUES_H__
#define __SENSOR_VALUES_H__

namespace SensorRead
{
    
    class SensorReadingInterface
    {
    public:
    
        SensorReadingInterface(int pinNumber);

       
        virtual int readSensor() = 0;
        virtual bool getState() = 0;

    protected:
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
    private:
        int threshold;
    };


    class Battery : public SensorReadingInterface
    {
    public:
        Battery(int threshold, int pinNumber);
        int readSensor() override;
        bool getState() override;
    private:
        int threshold;
    };


    class PeakPeriod : public SensorReadingInterface
    {
    public:
        PeakPeriod(int pinNumber);
        int readSensor() override;
        bool getState() override;
    };

  
}

#endif 

