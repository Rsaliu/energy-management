#include "solar_state.hpp"
#include <state_actions.hpp>
SolarState::SolarState(StateActionInterface* stateActionInterface):StateInterface(),stateActionInterface(stateActionInterface){

}
void SolarState::next(StateMachineInterface* machine,StateData& stateData)  {
    if (!stateData.solarAboveThreshold && stateData.batteryAboveDoD) {
        machine->setState(new BatteryState(this->stateActionInterface));
    }else if(!stateData.solarAboveThreshold && !stateData.batteryAboveDoD){
        machine->setState(new GridState(this->stateActionInterface));
    }else;
}
void SolarState::printState() const {
    Serial.println("State is Solar state");
}

void SolarState::stateAction() const{
    stateActionInterface->feedFromSolar();
}