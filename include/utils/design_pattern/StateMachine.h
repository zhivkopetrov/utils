#ifndef UTILS_DESIGNPATTERN_H_
#define UTILS_DESIGNPATTERN_H_

// System headers
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <functional>

// Other libraries headers

// Own components headers
#include "utils/ErrorCode.h"

// Forward declarations

using StateAction = std::function<void()>;

struct StateDescription {
  std::string name;
  StateAction onEnter;
  StateAction onExit;
};

struct StateTransitions {
  std::string stateName;
  std::unordered_set<std::string> transitions;
};

enum StateLogging {
  ENABLED, DISABLED
};

class StateMachine {
public:
  //full, partial or zero initialization
  ErrorCode init(StateLogging status,
                 const std::vector<StateDescription>& states = {},
                 const std::vector<StateTransitions>& transitions = {});

  void shutdown();

  //returns error if state is already present
  ErrorCode addState(const StateDescription& stateDescription);

  //returns error if state or state transitions are not present
  //Note: all transition states must first be added either by ::init() 
  //or ::addState()
  ErrorCode addStateTransitions(const StateTransitions& transitions);

  //returns error if requested transition is not possible
  ErrorCode changeState(const std::string& name);

private:
  struct StateInfo {
    StateDescription stateDescription;
    std::unordered_set<std::string> transitions;
  };

  std::unordered_map<std::string, StateInfo> _states;
  StateInfo* _currState = nullptr;
  StateLogging _stateLogging = StateLogging::ENABLED;
  bool _isShutdowned = false;
};

#endif /* UTILS_DESIGNPATTERN_H_ */
