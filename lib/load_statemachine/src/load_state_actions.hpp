#ifndef __STATE_ACTION_H__
#define __STATE_ACTION_H__
namespace LoadStateMachine
{
    enum LoadState{
        OFF=0,
        ON
    };
    struct LoadPattern{
        LoadState primaryLoad;
        LoadState flexibleLoadOne;
        LoadState flexibleLoadTwo;
    };
    class StateActionInterface
    {
    public:
        virtual void setLoad(LoadPattern pattern) = 0;
    };
    struct LoadPinConfig
    {
        int primaryLoad;
        int flexibleLoadOne;
        int flexibleLoadTwo;
    };
    class StateAction : public StateActionInterface
    {
    public:
        StateAction(const StateAction &) = delete;
        StateAction operator=(const StateAction &) = delete;
        static StateAction &getInstance(LoadPinConfig config);
        void setLoad(LoadPattern pattern) override;
    private:
        StateAction(LoadPinConfig config);
        LoadPinConfig config;
    };
}
#endif