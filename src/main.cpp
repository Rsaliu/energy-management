#include "sensor_values.hpp"
#include <Arduino.h>
#include <load_state_actions.hpp>
#include <load_state_machine.hpp>
#include <state_machine.hpp>
#include <state_actions.hpp>

SourceStateMachine::SourcePinConfig sourcePinConfig = {
  .solarPin =2,
  .batteryPin = 3,
  .gridPin = 4,

};

LoadStateMachine::LoadPinConfig loadPinConfig = {
  .primaryLoad = 5,
  .flexibleLoadOne = 6,
  .flexibleLoadTwo = 7,
};

LoadStateMachine::StateActionInterface* loadStateActionInterface;
LoadStateMachine::States loadInitState;
LoadStateMachine::StateMachine* loadStateMachine;

SourceStateMachine::StateActionInterface* sourceStateActionInterface;
SourceStateMachine::States sourceInitState;
SourceStateMachine::StateMachine* sourceStateMachine;

void setup() {
  // put your setup code here, to run once:
  sourceStateActionInterface = &SourceStateMachine::StateAction::getInstance(sourcePinConfig); 
  sourceInitState = SourceStateMachine::States::GRID;
  sourceStateMachine = new SourceStateMachine::StateMachine(sourceInitState,sourceStateActionInterface);

  loadStateActionInterface = &LoadStateMachine::StateAction::getInstance(loadPinConfig);
  loadInitState = LoadStateMachine::States::OFF;
  loadStateMachine = new LoadStateMachine::StateMachine(loadInitState,loadStateActionInterface);
}

void loop() {
  // put your main code here, to run repeatedly:
  // sequence here
  // 1. get readings from sensors
  // 2. convert them to StateData datastructure
  // 3. Feed the state data to the state machines
  // 4. State machines make decisions.
  // Repeat
}
