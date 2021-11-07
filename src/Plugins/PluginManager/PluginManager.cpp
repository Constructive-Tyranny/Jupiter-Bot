/**
 * Copyright (C) 2014-2021 Jessica James.
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * Written by Jessica James <jessica.aj@outlook.com>
 */

#include <cstring>
#include "Jupiter/Functions.h"
#include "PluginManager.h"

using namespace Jupiter::literals;

// Plugin Generic Command
PluginGenericCommand::PluginGenericCommand() {
	this->addTrigger(STRING_LITERAL_AS_REFERENCE("plugin"));
	this->addTrigger(STRING_LITERAL_AS_REFERENCE("plugins"));
	this->addTrigger(STRING_LITERAL_AS_REFERENCE("module"));
	this->addTrigger(STRING_LITERAL_AS_REFERENCE("modules"));
}

Jupiter::GenericCommand::ResponseLine *PluginGenericCommand::trigger(const Jupiter::ReadableString &parameters) {
	Jupiter::GenericCommand::ResponseLine *result = new Jupiter::GenericCommand::ResponseLine();
	if (parameters.isEmpty() || parameters.matchi("list*")) {
		Jupiter::GenericCommand::ResponseLine *line = result->set(Jupiter::String::Format("There are %u plugins loaded:", Jupiter::plugins.size()), GenericCommand::DisplayType::PublicSuccess);
		for (auto& plugin : Jupiter::plugins) {
			line->next = new Jupiter::GenericCommand::ResponseLine(plugin->getName(), GenericCommand::DisplayType::PublicSuccess);
			line = line->next;
		}

		return result;
	}

	if (parameters.matchi("load *")) {
		if (Jupiter::Plugin::load(Jupiter::ReferenceString::gotoWord(parameters, 1, WHITESPACE)) == nullptr) {
			return result->set("Error: Failed to load plugin."_jrs, GenericCommand::DisplayType::PublicError);
		}

		return result->set("Plugin successfully loaded."_jrs, GenericCommand::DisplayType::PublicSuccess);
	}

	if (parameters.matchi("unload *"))
	{
		Jupiter::ReferenceString pluginName = Jupiter::ReferenceString::gotoWord(parameters, 1, WHITESPACE);
		if (Jupiter::Plugin::get(pluginName) == nullptr) {
			return result->set("Error: Plugin does not exist."_jrs, GenericCommand::DisplayType::PublicError);
		}

		if (Jupiter::Plugin::free(pluginName) == false) {
			return result->set("Error: Failed to unload plugin."_jrs, GenericCommand::DisplayType::PublicError);
		}

		return result->set("Plugin successfully unloaded."_jrs, GenericCommand::DisplayType::PublicSuccess);
	}
	return result->set("Error: Invalid Syntax. Syntax: plugin {[list], <load> <plugin>, <unload> <plugin>}"_jrs, GenericCommand::DisplayType::PrivateError);
}

const Jupiter::ReadableString &PluginGenericCommand::getHelp(const Jupiter::ReadableString &parameters)
{
	static STRING_LITERAL_AS_NAMED_REFERENCE(loadHelp, "Loads a plugin by file name. Do not include a file extension. Syntax: plugin load <plugin>");
	static STRING_LITERAL_AS_NAMED_REFERENCE(unloadHelp, "Unloads a plugin by name. Syntax: plugin unload <plugin>");
	static STRING_LITERAL_AS_NAMED_REFERENCE(listHelp, "Lists all of the plugins currently loaded. Syntax: plugin [list]");
	static STRING_LITERAL_AS_NAMED_REFERENCE(defaultHelp, "Manages plugins. Syntax: plugin {[list], <load> <plugin>, <unload> <plugin>}");

	if (parameters.equalsi(STRING_LITERAL_AS_REFERENCE("load"))) {
		return loadHelp;
	}

	if (parameters.equalsi(STRING_LITERAL_AS_REFERENCE("unload"))) {
		return unloadHelp;
	}

	if (parameters.equalsi(STRING_LITERAL_AS_REFERENCE("list"))) {
		return listHelp;
	}

	return defaultHelp;
}

GENERIC_COMMAND_INIT(PluginGenericCommand)
GENERIC_COMMAND_AS_CONSOLE_COMMAND(PluginGenericCommand)

// Plugin instantiation and entry point.
PluginManager pluginInstance;

extern "C" JUPITER_EXPORT Jupiter::Plugin *getPlugin()
{
	return &pluginInstance;
}
