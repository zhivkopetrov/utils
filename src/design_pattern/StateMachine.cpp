// Corresponding header
#include "utils/design_pattern/StateMachine.h"

// System headers

// Other libraries headers

// Own components headers
#include "utils/Log.h"

ErrorCode StateMachine::init(StateLogging status,
                             const std::vector<StateDescription>& states,
                             const std::vector<StateTransitions>& transitions) {
  _stateLogging = status;

  for (const StateDescription& state : states) {
    if (ErrorCode::SUCCESS != addState(state)) {
      LOGERR("addState() failed");
      return ErrorCode::FAILURE;
    }
  }

  for (const StateTransitions& transition : transitions) {
    if (ErrorCode::SUCCESS != addStateTransitions(transition)) {
      LOGERR("addStateTransitions() failed");
      return ErrorCode::FAILURE;
    }
  }

  return ErrorCode::SUCCESS;
}

void StateMachine::shutdown() {
  LOG("StateMachine: Shutting down");
  _isShutdowned = true;
}

ErrorCode StateMachine::addState(const StateDescription& stateDescription) {
  auto it = _states.find(stateDescription.name);
  if (it != _states.end()) {
    LOGERR("State [%s] is already registed in the StateMachine", 
           stateDescription.name.c_str());
    return ErrorCode::FAILURE;
  }

  const auto [_, success] = _states.try_emplace(
    stateDescription.name, StateInfo{stateDescription, {}});
  if (!success) {
    LOGERR("Could not insert state [%s] in the StateMachine", 
            stateDescription.name.c_str());
    return ErrorCode::FAILURE;
  }

  if (StateLogging::ENABLED == _stateLogging) {
    LOG("StateMachine: Registering state [%s]", 
        stateDescription.name.c_str());
  }

  return ErrorCode::SUCCESS;
}

ErrorCode StateMachine::addStateTransitions(
    const StateTransitions& transitions) {
  auto it = _states.find(transitions.stateName);
  if (it == _states.end()) {
    LOGERR("State [%s] is not registed in the StateMachine", 
           transitions.stateName.c_str());
    return ErrorCode::FAILURE;
  }
  StateInfo& mainStateInfo = it->second;

  for (const auto& state : transitions.transitions) {
    it = _states.find(state);
    if (it == _states.end()) {
      LOGERR("Requested TransitionState [%s] for state [%s] is not registed in "
             "the StateMachine", state.c_str(), transitions.stateName.c_str());
      return ErrorCode::FAILURE;
    }

    mainStateInfo.transitions.insert(state);

    if (StateLogging::ENABLED == _stateLogging) {
      LOG("StateMachine: Registering state transition [%s] -> [%s]", 
          mainStateInfo.stateDescription.name.c_str(), state.c_str());
    }
  }

  return ErrorCode::SUCCESS;
}

ErrorCode StateMachine::changeState(const std::string& name) {
  if (_isShutdowned) {
    LOGR("StateMachine: is already shutdowned. "
         "Discarding request for ::changeState(%s)", name.c_str());
    return ErrorCode::FAILURE;
  }

  auto it = _states.find(name);
  if (it == _states.end()) {
    LOGERR("State [%s] is not registed in the StateMachine", name.c_str());
    return ErrorCode::FAILURE;
  }

  //on first iteration there will be no current(present) state
  if (_currState) {
    //check for allowed state transition
    if (_currState->transitions.find(name) == _currState->transitions.end()) {
      LOGERR("Requested State [%s] not registed as TransitionState for the "
             "current state [%s]. Discarding event", name.c_str(), 
             _currState->stateDescription.name.c_str());
      return ErrorCode::FAILURE;
    }

    if (StateLogging::ENABLED == _stateLogging) {
      LOG("StateMachine: Leaving state [%s]", 
          _currState->stateDescription.name.c_str());
    }
    _currState->stateDescription.onExit();
  }
  _currState = &it->second;

  if (StateLogging::ENABLED == _stateLogging) {
    LOG("StateMachine: Entering state [%s]", 
        _currState->stateDescription.name.c_str());
  }
  _currState->stateDescription.onEnter();

  return ErrorCode::SUCCESS;
}