//
// Created by Dawid Drozd aka Gelldur on 14.05.17.
//
#pragma once

#include <map>
#include <string>
#include <functional>

namespace CrossLayout
{

class StateProperty
{
public:
	bool addState(const std::string& stateName, std::function<std::string()> onEnterState);
	bool replaceState(const std::string& stateName, std::function<std::string()> onEnterState);
	std::function<std::string()> getState(const std::string& stateName);

	bool moveToState(std::string stateName);

	const std::string& getCurrentState() const;

private:
	std::string _currentState;
	std::map<std::string, std::function<std::string()>> _states;
};

}
