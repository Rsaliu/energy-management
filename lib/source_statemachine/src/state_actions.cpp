#include "state_actions.hpp"

#include <Arduino.h>
#include <common_header.hpp>
namespace SourceStateMachine
{
    StateAction &StateAction::getInstance(SourcePinConfig config)
    {
        static StateAction instance(config);
        return instance;
    }
    StateAction::StateAction(SourcePinConfig config) : config(config)
    {
    }
    void StateAction::feedFromSolar()
    {
        Common::println("feeding from Solar");
        digitalWrite(config.batteryPin, LOW);
        digitalWrite(config.gridPin, LOW);
        digitalWrite(config.solarPin, HIGH);
        
    }
    void StateAction::feedFromBattery()
    {
        Common::println("feeding from Battery");
        digitalWrite(config.batteryPin, HIGH);
        digitalWrite(config.gridPin, LOW);
        digitalWrite(config.solarPin, LOW);
        
    }
    void StateAction::feedFromGrid()
    {
        Common::println("feeding from Grid");
        digitalWrite(config.batteryPin, LOW);
        digitalWrite(config.gridPin, HIGH);
        digitalWrite(config.solarPin, LOW);
        
    }
}