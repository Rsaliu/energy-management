#include "battery_state.hpp"

BatteryState::BatteryState():StateInterface(){

}
void BatteryState::next(StateMachineInterface* machine,StateData& stateData)  {
    if (stateData.solarAboveThreshold) {
        machine->setState(new SolarState());
    }else if(!stateData.batteryAboveDoD){
        machine->setState(new GridState());
    }else;
}
void BatteryState::printState() const {
    Serial.println("State is Battery state");
}