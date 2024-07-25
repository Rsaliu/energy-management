#include "battery_state.hpp"
#include <state_actions.hpp>
BatteryState::BatteryState(StateActionInterface* stateActionInterface):StateInterface(),stateActionInterface(stateActionInterface){

}
void BatteryState::next(StateMachineInterface* machine,StateData& stateData)  {
    if (stateData.solarAboveThreshold) {
        machine->setState(new SolarState(this->stateActionInterface));
    }else if(!stateData.batteryAboveDoD){
        machine->setState(new GridState(this->stateActionInterface));
    }else;
}
void BatteryState::printState() const {
    Serial.println("State is Battery state");
}

void BatteryState::stateAction() const{
    stateActionInterface->feedFromBattery();
}