#include <Arduino.h>
#include <grid_state.hpp>
#include <state_machine.hpp>
#include <state_actions.hpp>
#include <grid_state.hpp>

SourcePinConfig sourcePinConfig = {
  .solarPin =2,
  .batteryPin = 3,
  .gridPin = 4,

};
StateActionInterface* stateActionInterface;
StateInterface* initState;
StateMachine* stateMachine;
void setup() {
  // put your setup code here, to run once:
  stateActionInterface = &StateAction::getInstance(sourcePinConfig); 
  initState = new GridState(stateActionInterface);
  stateMachine = new StateMachine(initState);
}

void loop() {
  // put your main code here, to run repeatedly:
  
}
