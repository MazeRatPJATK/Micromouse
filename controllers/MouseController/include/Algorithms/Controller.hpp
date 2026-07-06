//this classes responsibility is to make us of both Mapping and Solving. it decided when to go for the final solving attempt,
//and is also the only class that should be used inside main
//this is the 'traffic controller', here we only decide whether yo use Mapping or Solving


#include "Map.hpp"
#include "Mapping.hpp"
#include "Solving.hpp"
#include "../MotionController.hpp"
#include "../Interfaces/ISensors.hpp"
#include "../PositionEstimator.hpp"
#include <queue>
#include <functional>


enum ControllerState{
    IDLE,
    EXECUTING_COMMAND
};


class Controller{
    public:
        Map map;
        Controller(ISensors& sensors, MotionController& motionController);
        void step();
        std::queue<Command> commandQueue = {};
        std::queue<Command> interrupts = {};
    private:
        void enqueCommand(Command cmd);
        void applyCommands();
        void initNewCommand(Command& c);
        bool hasFinishedCommand(Command& c); 
        const std::queue<Command>& peekCommandQueue() const;
        MotionController& motionController;
        ISensors& sensors;
        Mapping mapper;
        Solving solver;
        PositionEstimator positionEstimator;
        ControllerState controllerState;



};