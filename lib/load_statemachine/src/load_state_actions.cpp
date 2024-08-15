#include "load_state_actions.hpp"
#include <Arduino.h>
namespace LoadStateMachine
{
    StateAction &StateAction::getInstance(LoadPinConfig config)
    {
        static StateAction instance(config);
        return instance;
    }
    StateAction::StateAction(LoadPinConfig config) : config(config)
    {
    }
    void StateAction::setLoad(LoadPattern pattern){
        Serial.println("load pattern: ");
        Serial.print("Primary load: ");
        Serial.println((int)pattern.primaryLoad);
        Serial.print("flexible1 load: ");
        Serial.println((int)pattern.flexibleLoadOne);
        Serial.print("flexible2 load: ");
        Serial.println((int)pattern.flexibleLoadTwo);
        digitalWrite(config.primaryLoad,pattern.primaryLoad);
        digitalWrite(config.flexibleLoadOne,pattern.flexibleLoadOne);
        digitalWrite(config.flexibleLoadTwo,pattern.flexibleLoadTwo);
        
    }
}