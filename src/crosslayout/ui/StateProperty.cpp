//
// Created by Dawid Drozd aka Gelldur on 14.05.17.
//
#include "StateProperty.h"
//////////////////////////////////

namespace CrossLayout
{
bool StateProperty::addState(const std::string& stateName, std::function<std::string()> onEnterState)
{
	if (_states.find(stateName) != _states.end())
	{
		return false;
	}
	_states.insert({stateName, std::move(onEnterState)});
	return true;
}

bool StateProperty::replaceState(const std::string& stateName, std::function<std::string()> onEnterState)
{
	_states[stateName] = std::move(onEnterState);
	return true;
}

std::function<std::string()> StateProperty::getState(const std::string& stateName)
{
	auto found = _states.find(stateName);
	if (found == _states.end())
	{
		return {};
	}
	return found->second;
}

bool StateProperty::moveToState(std::string stateName)
{
	while (stateName.empty() == false)
	{
		auto found = _states.find(stateName);
		if (found == _states.end())
		{
			return false;
		}
		stateName = found->second();
		_currentState = stateName;
	}

	return true;
}

const std::string& StateProperty::getCurrentState() const
{
	return _currentState;
}

}
