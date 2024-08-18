#ifndef __LOAD_STATE_ACTION_H__
#define __LOAD_STATE_ACTION_H__
namespace LoadStateMachine
{
    enum LoadState{
        OFF=1,
        ON=0
    };
    struct LoadPattern{
        LoadState primaryLoad;
        LoadState flexibleLoadOne;
        LoadState flexibleLoadTwo;

        bool operator==(const LoadPattern& loadPattern)const {
            if(primaryLoad != loadPattern.primaryLoad) return false;
            if(flexibleLoadOne != loadPattern.flexibleLoadOne) return false;
            if(flexibleLoadTwo != loadPattern.flexibleLoadTwo) return false;
            return true;
        }
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