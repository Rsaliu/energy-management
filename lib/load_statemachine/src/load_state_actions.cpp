#include "load_state_actions.hpp"
#include <Arduino.h>
#include <common_header.hpp>
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
        char buff[200];
        sprintf(buff,"load pattern: \nPrimary load: %d\nflexible1 load: %d\nflexible2 load: %d\n",
        pattern.primaryLoad,pattern.flexibleLoadOne,pattern.flexibleLoadTwo);
        Common::println(buff);
        digitalWrite(config.primaryLoad,pattern.primaryLoad);
        digitalWrite(config.flexibleLoadOne,pattern.flexibleLoadOne);
        digitalWrite(config.flexibleLoadTwo,pattern.flexibleLoadTwo);
        
    }
}