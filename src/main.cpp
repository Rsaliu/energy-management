#include <Arduino.h>
#include <state_machine.hpp>
#include <state_actions.hpp>

SourceStateMachine::SourcePinConfig sourcePinConfig = {
  .solarPin =2,
  .batteryPin = 3,
  .gridPin = 4,

};
SourceStateMachine::StateActionInterface* stateActionInterface;
SourceStateMachine::States initState;
SourceStateMachine::StateMachine* stateMachine;
void setup() {
  // put your setup code here, to run once:
  stateActionInterface = &SourceStateMachine::StateAction::getInstance(sourcePinConfig); 
  initState = SourceStateMachine::States::GRID;
  stateMachine = new SourceStateMachine::StateMachine(initState,stateActionInterface);
}

void loop() {
  // put your main code here, to run repeatedly:

}
