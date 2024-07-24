#include "solar_state.hpp"

SolarState::SolarState():StateInterface(){

}
void SolarState::next(StateMachineInterface* machine,StateData& stateData)  {
    if (!stateData.solarAboveThreshold && stateData.batteryAboveDoD) {
        machine->setState(new BatteryState());
    }else if(!stateData.solarAboveThreshold && !stateData.batteryAboveDoD){
        machine->setState(new GridState());
    }else;
}
void SolarState::printState() const {
    Serial.println("State is Solar state");
}