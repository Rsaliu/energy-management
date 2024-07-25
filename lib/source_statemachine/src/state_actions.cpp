#include "state_actions.hpp"
#include <Arduino.h>

StateAction& StateAction::getInstance(SourcePinConfig config){
    static StateAction instance(config);
    return instance;
}
StateAction::StateAction(SourcePinConfig config):config(config){

}
void StateAction::feedFromSolar(){
    digitalWrite(config.batteryPin,LOW);
    digitalWrite(config.gridPin,LOW);
    digitalWrite(config.solarPin,HIGH);
}
void StateAction::feedFromBattery(){
    digitalWrite(config.batteryPin,HIGH);
    digitalWrite(config.gridPin,LOW);
    digitalWrite(config.solarPin,LOW);
}
void StateAction::feedFromGrid(){
    digitalWrite(config.batteryPin,LOW);
    digitalWrite(config.gridPin,HIGH);
    digitalWrite(config.solarPin,LOW);
}