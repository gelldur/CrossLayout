//
// Created by Dawid Drozd aka Gelldur on 08/01/17.
//
#pragma once

#include <string>
#include <crosslayout/NodeWrapper.h>
#include <crosslayout/Composer.h>

#include <sstream>
#include <functional>

#include <json/json.h>

namespace CrossLayout
{

template<class T>
class LayoutParser
{
public:
	LayoutParser(NodeWrapper<T> parent)
			: _parent(parent)
	{
	}

	LayoutParser& parse(std::istream& stream)
	{
		Json::Value root;
		Json::Reader reader;
		if (reader.parse(stream, root, false) == false)
		{
			throw std::runtime_error(reader.getFormattedErrorMessages());
		}

		const auto& null = Json::Value::nullRef;

		const auto& composerJson = root.get("composer", null);
		if (composerJson.isArray())
		{
			processComposer(composerJson);
		}

		return *this;
	}

	LayoutParser& parse(const std::string& data)
	{
		std::istringstream wrapped(data);
		return parse(wrapped);;
	}

	void layout()
	{

	}

private:
	Composer<T> _composer;
	NodeWrapper<T> _parent;

	void processComposer(const Json::Value& composerJsonArray)
	{
		std::map<std::string, std::function<void(NodeWrapper<T>&, NodeWrapper<T>&, const float)>> commands;
		commands["leftEdge_toLeftEdge"] = [this](NodeWrapper<T>& nodeA, NodeWrapper<T>& nodeB, const float margin)
		{
			_composer.leftEdge(nodeA).moveTo().leftEdge(nodeB, margin);
		};
		commands["leftEdge_toRightEdge"] = [this](NodeWrapper<T>& nodeA, NodeWrapper<T>& nodeB, const float margin)
		{
			_composer.leftEdge(nodeA).moveTo().rightEdge(nodeB, margin);
		};
		commands["rightEdge_toLeftEdge"] = [this](NodeWrapper<T> nodeA, NodeWrapper<T> nodeB, const float margin)
		{
			_composer.rightEdge(nodeA).moveTo().leftEdge(nodeB, margin);
		};
		commands["rightEdge_toRightEdge"] = [this](NodeWrapper<T> nodeA, NodeWrapper<T> nodeB, const float margin)
		{
			_composer.rightEdge(nodeA).moveTo().rightEdge(nodeB, margin);
		};
		commands["topEdge_toTopEdge"] = [this](NodeWrapper<T> nodeA, NodeWrapper<T> nodeB, const float margin)
		{
			_composer.topEdge(nodeA).moveTo().topEdge(nodeB, margin);
		};
		commands["topEdge_toBottomEdge"] = [this](NodeWrapper<T> nodeA, NodeWrapper<T> nodeB, const float margin)
		{
			_composer.topEdge(nodeA).moveTo().bottomEdge(nodeB, margin);
		};
		commands["bottomEdge_toTopEdge"] = [this](NodeWrapper<T> nodeA, NodeWrapper<T> nodeB, const float margin)
		{
			_composer.bottomEdge(nodeA).moveTo().topEdge(nodeB, margin);
		};
		commands["bottomEdge_toBottomEdge"] = [this](NodeWrapper<T> nodeA, NodeWrapper<T> nodeB, const float margin)
		{
			_composer.bottomEdge(nodeA).moveTo().bottomEdge(nodeB, margin);
		};

		for (const auto& command : composerJsonArray)
		{
			std::string nodeAName;
			std::string nodeBName;
			std::string commandString;
			if (command.isMember("leftEdge"))
			{
				commandString = "leftEdge";
			}
			else if (command.isMember("rightEdge"))
			{
				commandString = "rightEdge";
			}
			else if (command.isMember("topEdge"))
			{
				commandString = "topEdge";
			}
			else if (command.isMember("bottomEdge"))
			{
				commandString = "bottomEdge";
			}
			nodeAName = commandString;
			commandString += "_";

			if (command.isMember("toLeftEdge"))
			{
				nodeBName = "toLeftEdge";
				commandString += "toLeftEdge";
			}
			else if (command.isMember("toRightEdge"))
			{
				nodeBName = "toRightEdge";
				commandString += "toRightEdge";
			}
			else if (command.isMember("toTopEdge"))
			{
				nodeBName = "toTopEdge";
				commandString += "toTopEdge";
			}
			else if (command.isMember("toBottomEdge"))
			{
				nodeBName = "toBottomEdge";
				commandString += "toBottomEdge";
			}

			NodeWrapper<T> nodeA{nullptr};
			NodeWrapper<T> nodeB{nullptr};

			nodeAName = command[nodeAName].asString();
			nodeBName = command[nodeBName].asString();

			if (nodeAName == "parent")
			{
				nodeA = _parent;
			}
			else
			{
				nodeA = NodeWrapper<T>{_parent.getChild(nodeAName)};
			}
			if (nodeBName == "parent")
			{
				nodeB = _parent;
			}
			else
			{
				nodeB = NodeWrapper<T>{_parent.getChild(nodeBName)};
			}

			if (commands.find(commandString) != commands.end())
			{
				commands[commandString](nodeA
										, nodeB
										, command.get("margin", 0).asInt());
			}
		}
	}
};

}
