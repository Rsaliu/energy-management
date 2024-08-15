#include "sensor_values.hpp"
  
#include <Arduino.h>

#include <load_state_actions.hpp>
#include <load_state_machine.hpp>
#include <state_machine.hpp>
#include <state_actions.hpp>
constexpr const int SOLAR_SOURCE_PIN = 13;
constexpr const int BATTERY_SOURCE_PIN = 12;
constexpr const int GRID_SOURCE_PIN = 11;
constexpr const int PRIMARY_LOAD_PIN = 8;
constexpr const int FLEX_LOAD_ONE_PIN = 9;
constexpr const int FLEX_LOAD_TWO_PIN = 10;
constexpr const int SOLAR_LDR_INPUT_PIN = A0;
constexpr const int BATTERY_INPUT_PIN = A1;
constexpr const int PEAKAM_INPUT = 2;
constexpr const int PEAKPM_INPUT = 3;


constexpr const int SolarThreshold = 750;
constexpr const int BatteryThreshold = 768;
SourceStateMachine::SourcePinConfig sourcePinConfig = {
  .solarPin =SOLAR_SOURCE_PIN,
  .batteryPin = BATTERY_SOURCE_PIN,
  .gridPin = GRID_SOURCE_PIN,

};

LoadStateMachine::LoadPinConfig loadPinConfig = {
  .primaryLoad = PRIMARY_LOAD_PIN,
  .flexibleLoadOne = FLEX_LOAD_ONE_PIN,
  .flexibleLoadTwo = FLEX_LOAD_TWO_PIN,
};

SensorRead::SensorPinConfig sensorPinConfig = {
    .solarPin = SOLAR_LDR_INPUT_PIN,
    .batteryPin = BATTERY_INPUT_PIN,
    .peakAm = PEAKAM_INPUT,
    .peakPm = PEAKPM_INPUT,
};


LoadStateMachine::StateActionInterface* loadStateActionInterface;
LoadStateMachine::States loadInitState;
LoadStateMachine::StateMachine* loadStateMachine;

SourceStateMachine::StateActionInterface* sourceStateActionInterface;
SourceStateMachine::States sourceInitState;
SourceStateMachine::StateMachine* sourceStateMachine;

SensorRead::SensorReadingInterface* ldrOrSolarSensorObj;
SensorRead::SensorReadingInterface* batterySensorObj;
SensorRead::SensorReadingInterface* peakAMSensorObj;
SensorRead::SensorReadingInterface* peakPMSensorObj;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(SOLAR_SOURCE_PIN,OUTPUT);
  pinMode(BATTERY_SOURCE_PIN,OUTPUT);
  pinMode(GRID_SOURCE_PIN,OUTPUT);
  pinMode(PRIMARY_LOAD_PIN,OUTPUT);
  pinMode(FLEX_LOAD_ONE_PIN,OUTPUT);
  pinMode(FLEX_LOAD_TWO_PIN,OUTPUT);
  pinMode(SOLAR_LDR_INPUT_PIN,INPUT);
  pinMode(BATTERY_INPUT_PIN,INPUT);
  pinMode(PEAKAM_INPUT,INPUT_PULLUP);
  pinMode(PEAKPM_INPUT,INPUT_PULLUP);
  sourceStateActionInterface = &SourceStateMachine::StateAction::getInstance(sourcePinConfig); 
  sourceInitState = SourceStateMachine::States::GRID;
  sourceStateMachine = new SourceStateMachine::StateMachine(sourceInitState,sourceStateActionInterface);

  loadStateActionInterface = &LoadStateMachine::StateAction::getInstance(loadPinConfig);
  loadInitState = LoadStateMachine::States::OFF;
  loadStateMachine = new LoadStateMachine::StateMachine(loadInitState,loadStateActionInterface);

  ldrOrSolarSensorObj = new  SensorRead::LDR(SolarThreshold, sensorPinConfig.solarPin);
  batterySensorObj =   new SensorRead::Battery(BatteryThreshold, sensorPinConfig.batteryPin);
  peakAMSensorObj = new SensorRead::PeakPeriod(sensorPinConfig.peakAm);
  peakPMSensorObj = new SensorRead::PeakPeriod(sensorPinConfig.peakPm);
}

bool StateGetter(SensorRead::SensorReadingInterface* sensorInterface){
  return sensorInterface->getState();
}

void loop() {
  // put your main code here, to run repeatedly:
  // sequence here
  // 1. get readings from sensors
  // 2. convert them to StateData datastructure
  // 3. Feed the state data to the state machines
  // 4. State machines make decisions.
  // Repeat
  bool ldrOrSolarState = StateGetter(ldrOrSolarSensorObj);
  bool batteryState = StateGetter(batterySensorObj);
  bool peakAMState = StateGetter(peakAMSensorObj);
  bool peakPMState = StateGetter(peakPMSensorObj);
  
  Common::StateData stateData(ldrOrSolarState,batteryState,peakAMState,peakPMState);
  stateData.print();
  sourceStateMachine->nextState(stateData);

  loadStateMachine->nextState(stateData);
  delay(10);
}
