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
        digitalWrite(config.batteryPin, SourceState::OFF);
        // Due to change request  from Olay, We will keep grid always on, in any state
        digitalWrite(config.gridPin, SourceState::ON);
        digitalWrite(config.solarPin, SourceState::ON);
        
    }
    void StateAction::feedFromBattery()
    {
        Common::println("feeding from Battery");
        digitalWrite(config.batteryPin, SourceState::ON);
        // Due to change request  from Olay, We will keep grid always on, in any state
        digitalWrite(config.gridPin, SourceState::ON);
        digitalWrite(config.solarPin, SourceState::OFF);
        
    }
    void StateAction::feedFromGrid()
    {
        Common::println("feeding from Grid");
        digitalWrite(config.batteryPin, SourceState::OFF);
        digitalWrite(config.gridPin, SourceState::ON);
        digitalWrite(config.solarPin, SourceState::OFF);
        
    }
}