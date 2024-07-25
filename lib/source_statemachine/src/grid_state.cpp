#include "grid_state.hpp"
#include <state_actions.hpp>
GridState::GridState(StateActionInterface* stateActionInterface):StateInterface(),stateActionInterface(stateActionInterface){
    
}
void GridState::next(StateMachineInterface* machine,StateData& stateData){
    if (stateData.solarAboveThreshold) {
        machine->setState(new SolarState(this->stateActionInterface));
    }
}
void GridState::printState() const{
    Serial.println("State is Grid state");
}

void GridState::stateAction() const{
    stateActionInterface->feedFromGrid();
}