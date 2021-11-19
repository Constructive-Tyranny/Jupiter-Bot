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
#include "CoreCommands.h"
#include "IRC_Bot.h"

using namespace Jupiter::literals;

// Help Console Command

HelpConsoleCommand::HelpConsoleCommand() {
	this->addTrigger(STRING_LITERAL_AS_REFERENCE("help"));
}

void HelpConsoleCommand::trigger(const Jupiter::ReadableString &parameters) {
	if (parameters.isEmpty()) {
		fputs("Supported commands:", stdout);
		for (const auto& command : consoleCommands) {
			fputc(' ', stdout);
			command->getTrigger().print(stdout);
		}
		printf(ENDL "%s - %s" ENDL, Jupiter::version, Jupiter::copyright);
		puts("For command-specific help, use: help <command>");
		return;
	}

	Jupiter::ReferenceString command = Jupiter::ReferenceString::getWord(parameters, 0, WHITESPACE);
	ConsoleCommand *cmd = getConsoleCommand(command);
	if (cmd == nullptr) {
		printf("Error: Command \"%.*s\" not found." ENDL, static_cast<int>(command.size()), command.ptr());
		return;
	}

	cmd->getHelp(Jupiter::ReferenceString::gotoWord(parameters, 1, WHITESPACE)).println(stdout);
}

const Jupiter::ReadableString &HelpConsoleCommand::getHelp(const Jupiter::ReadableString &) {
	static STRING_LITERAL_AS_NAMED_REFERENCE(defaultHelp, "Lists commands, or sends command-specific help. Syntax: help [command]");
	return defaultHelp;
}

CONSOLE_COMMAND_INIT(HelpConsoleCommand)

// Help IRC Command.

void HelpIRCCommand::create() {
	this->addTrigger("help"_jrs);
}

void HelpIRCCommand::trigger(IRC_Bot *source, const Jupiter::ReadableString &in_channel, const Jupiter::ReadableString &nick, const Jupiter::ReadableString &parameters) {
	Jupiter::IRC::Client::Channel *channel = source->getChannel(in_channel);
	if (channel != nullptr)
	{
		int access = source->getAccessLevel(*channel, nick);
		if (parameters == nullptr)
		{
			for (int i = 0; i <= access; i++)
			{
				auto cmds = source->getAccessCommands(channel, i);
				if (cmds.size() != 0)
				{
					Jupiter::StringL triggers = source->getTriggers(cmds);
					if (triggers.size() >= 0)
						source->sendNotice(nick, Jupiter::StringS::Format("Access level %d commands: %.*s", i, triggers.size(), triggers.ptr()));
				}
			}
			source->sendNotice(nick, "For command-specific help, use: help <command>"_jrs);
		}
		else
		{
			IRCCommand *cmd = source->getCommand(Jupiter::ReferenceString::getWord(parameters, 0, WHITESPACE));
			if (cmd)
			{
				int command_access = cmd->getAccessLevel(channel);

				if (command_access < 0)
					source->sendNotice(nick, "Error: Command disabled."_jrs);
				else if (access < command_access)
					source->sendNotice(nick, "Access Denied."_jrs);
				else
					source->sendNotice(nick, cmd->getHelp(Jupiter::ReferenceString::gotoWord(parameters, 1, WHITESPACE)));
			}
			else source->sendNotice(nick, "Error: Command not found."_jrs);
		}
	}
}

const Jupiter::ReadableString &HelpIRCCommand::getHelp(const Jupiter::ReadableString &) {
	static STRING_LITERAL_AS_NAMED_REFERENCE(defaultHelp, "Syntax: help [command]");
	return defaultHelp;
}

IRC_COMMAND_INIT(HelpIRCCommand)

// Version Command

VersionGenericCommand::VersionGenericCommand() {
	this->addTrigger(STRING_LITERAL_AS_REFERENCE("version"));
	this->addTrigger(STRING_LITERAL_AS_REFERENCE("versioninfo"));
	this->addTrigger(STRING_LITERAL_AS_REFERENCE("copyright"));
	this->addTrigger(STRING_LITERAL_AS_REFERENCE("copyrightinfo"));
	this->addTrigger(STRING_LITERAL_AS_REFERENCE("client"));
	this->addTrigger(STRING_LITERAL_AS_REFERENCE("clientinfo"));
}

Jupiter::GenericCommand::ResponseLine *VersionGenericCommand::trigger(const Jupiter::ReadableString &parameters) {
	Jupiter::GenericCommand::ResponseLine *ret = new Jupiter::GenericCommand::ResponseLine("Version: "_jrs + Jupiter::ReferenceString(Jupiter::version), GenericCommand::DisplayType::PublicSuccess);
	ret->next = new Jupiter::GenericCommand::ResponseLine(Jupiter::ReferenceString(Jupiter::copyright), GenericCommand::DisplayType::PublicSuccess);
	return ret;
}

const Jupiter::ReadableString &VersionGenericCommand::getHelp(const Jupiter::ReadableString &) {
	static STRING_LITERAL_AS_NAMED_REFERENCE(defaultHelp, "Displays version and copyright information");
	return defaultHelp;
}

GENERIC_COMMAND_INIT(VersionGenericCommand)
GENERIC_COMMAND_AS_CONSOLE_COMMAND(VersionGenericCommand)

// Rehash Command

RehashGenericCommand::RehashGenericCommand() {
	this->addTrigger(STRING_LITERAL_AS_REFERENCE("rehash"));
}

Jupiter::GenericCommand::ResponseLine *RehashGenericCommand::trigger(const Jupiter::ReadableString &parameters) {
	size_t hash_errors = Jupiter::rehash();

	if (hash_errors == 0)
		return new Jupiter::GenericCommand::ResponseLine(Jupiter::StringS::Format("All %u objects were successfully rehashed.", Jupiter::getRehashableCount()), GenericCommand::DisplayType::PublicSuccess);

	return new Jupiter::GenericCommand::ResponseLine(Jupiter::StringS::Format("%u of %u objects failed to successfully rehash.", hash_errors, Jupiter::getRehashableCount()), GenericCommand::DisplayType::PublicError);
}

const Jupiter::ReadableString &RehashGenericCommand::getHelp(const Jupiter::ReadableString &) {
	static STRING_LITERAL_AS_NAMED_REFERENCE(defaultHelp, "Rehashes configuration data from a file. Syntax: rehash [file]");
	return defaultHelp;
}

GENERIC_COMMAND_INIT(RehashGenericCommand)
GENERIC_COMMAND_AS_CONSOLE_COMMAND(RehashGenericCommand)

// Plugin instantiation and entry point.
CoreCommandsPlugin pluginInstance;

extern "C" JUPITER_EXPORT Jupiter::Plugin *getPlugin() {
	return &pluginInstance;
}
