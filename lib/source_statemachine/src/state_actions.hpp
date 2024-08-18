#ifndef __STATE_ACTION_H__
#define __STATE_ACTION_H__
namespace SourceStateMachine
{
    enum SourceState{
        OFF=1,
        ON=0
    };
    class StateActionInterface
    {
    public:
        virtual void feedFromSolar() = 0;
        virtual void feedFromBattery() = 0;
        virtual void feedFromGrid() = 0;
    };
    struct SourcePinConfig
    {
        int solarPin;
        int batteryPin;
        int gridPin;
    };
    class StateAction : public StateActionInterface
    {
    public:
        StateAction(const StateAction &) = delete;
        StateAction operator=(const StateAction &) = delete;
        static StateAction &getInstance(SourcePinConfig config);
        void feedFromSolar() override;
        void feedFromBattery() override;
        void feedFromGrid() override;

    private:
        StateAction(SourcePinConfig config);
        SourcePinConfig config;
    };
}
#endif