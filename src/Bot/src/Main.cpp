/**
 * Copyright (C) 2013-2021 Jessica James.
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

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <csignal>
#include <exception>
#include <thread>
#include <mutex>
#include "jessilib/unicode.hpp"
#include "Jupiter/Functions.h"
#include "Jupiter/INIConfig.h"
#include "Jupiter/Socket.h"
#include "Jupiter/Plugin.h"
#include "Jupiter/Timer.h"
#include "jessilib/word_split.hpp"
#include "IRC_Bot.h"
#include "Console_Command.h"
#include "IRC_Command.h"

#if defined _WIN32
#include <Windows.h>
#endif // _WIN32

using namespace Jupiter::literals;

Jupiter::INIConfig o_config;
Jupiter::Config *Jupiter::g_config = &o_config;
std::chrono::steady_clock::time_point Jupiter::g_start_time = std::chrono::steady_clock::now();

constexpr size_t INPUT_BUFFER_SIZE = 2048;

struct ConsoleInput {
	std::string input;
	std::mutex input_mutex;
	bool awaiting_processing = false;

	ConsoleInput() {
		input.reserve(INPUT_BUFFER_SIZE);
	}
} console_input;

void onTerminate() {
	puts("Terminate signal received...");
}

void onExit() {
	puts("Exit signal received; Cleaning up...");
	Jupiter::Socket::cleanup();
	puts("Clean-up complete. Closing...");
}

void inputLoop() {
	std::string input;
	while (ftell(stdin) != -1 || errno != EBADF) {
		std::getline(std::cin, input);

	check_input_processing:

		std::lock_guard<std::mutex> guard(console_input.input_mutex);
		if (console_input.awaiting_processing == false)
		{
			console_input.input = input;
			console_input.awaiting_processing = true;
		}
		else // User input received before previous input was processed.
		{
			std::this_thread::sleep_for((std::chrono::seconds(1)));
			goto check_input_processing;
		}
	}
}

void initialize_plugins() {
	std::cout << "Loading plugins..." << std::endl;
	std::string_view plugin_list_str = Jupiter::g_config->get("Plugins"_jrs);
	if (plugin_list_str.empty()) {
		std::cout << "No plugins to load!" << std::endl;
	}
	else {
		// initialize plugins
		auto plugin_names = jessilib::word_split<std::vector, Jupiter::ReferenceString>(plugin_list_str, WHITESPACE_SV);
		std::cout << "Attempting to load " << plugin_names.size() << " plugins..." << std::endl;

		for (const auto& plugin_name : plugin_names) {
			std::chrono::steady_clock::time_point load_start = std::chrono::steady_clock::now();
			bool load_success = Jupiter::Plugin::load(plugin_name) != nullptr;
			double time_taken = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - load_start).count()) / 1000.0;

			if (load_success) {
				std::cout << "\"" << plugin_name << "\" loaded successfully (" << time_taken << "ms)." << std::endl;
			}
			else {
				std::cerr << "WARNING: Failed to load plugin \"" << plugin_name << "\" (" << time_taken << "ms)!" << std::endl;
			}
		}

		// OnPostInitialize
		for (const auto& plugin : Jupiter::plugins) {
			plugin->OnPostInitialize();
		}
	}
}

namespace Jupiter {
void reinitialize_plugins() {
	// Uninitialize back -> front
	while (!Jupiter::plugins.empty()) {
		Jupiter::Plugin::free(Jupiter::plugins.size() - 1);
	}

	initialize_plugins();
}
} // namespace Jupiter

[[noreturn]] void main_loop() {
	size_t index;
	while (1) {
		index = 0;
		while (index < Jupiter::plugins.size()) {
			if (Jupiter::plugins[index]->shouldRemove() || Jupiter::plugins[index]->think() != 0) {
				Jupiter::Plugin::free(index);
			}
			else {
				++index;
			}
		}
		Jupiter::Timer::check();

		if (console_input.input_mutex.try_lock()) {
			if (console_input.awaiting_processing) {
				console_input.awaiting_processing = false;
				auto input_split = jessilib::word_split_once_view(console_input.input, WHITESPACE_SV);
				std::string_view command_name = input_split.first;

				ConsoleCommand* command = getConsoleCommand(command_name);
				if (command != nullptr) {
					command->trigger(input_split.second);
				}
				else {
					printf("Error: Command \"%.*s\" not found." ENDL, static_cast<int>(command_name.size()), command_name.data());
				}
			}
			console_input.input_mutex.unlock();
		}
		std::this_thread::sleep_for((std::chrono::milliseconds(1)));
	}
}

int main(int argc, const char **args) {
	atexit(onExit);
	std::set_terminate(onTerminate);
	std::thread inputThread(inputLoop);
	Jupiter::ReferenceString plugins_directory, configs_directory;

#if defined SIGPIPE
	std::signal(SIGPIPE, SIG_IGN);
#endif // SIGPIPE

#if defined _WIN32
	// Sets console to UTF-8
	SetConsoleCP(65001);
	SetConsoleOutputCP(65001);
#endif // _WIN32

	srand(static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()));
	puts(Jupiter::copyright);
	const char *configFileName = "Config.ini";

	for (int i = 1; i < argc; i++) {
		std::string_view arg_view = args[i];
		if (jessilib::equalsi("-help"_jrs, arg_view)) {
			puts("Help coming soon, to a theatre near you!");
			return 0;
		}
		else if (jessilib::equalsi("-config"_jrs, arg_view) && ++i < argc)
			configFileName = args[i];
		else if (jessilib::equalsi("-pluginsdir"_jrs, arg_view) && ++i < argc)
			plugins_directory = arg_view;
		else if (jessilib::equalsi("-configsdir"_jrs, arg_view) && ++i < argc)
			configs_directory = arg_view;
		else if (jessilib::equalsi("-configFormat"_jrs, arg_view) && ++i < argc)
			puts("Feature not yet supported!");
		else
			printf("Warning: Unknown command line argument \"%s\" specified. Ignoring...", args[i]);
	}

	std::chrono::steady_clock::time_point load_start = std::chrono::steady_clock::now();

	puts("Loading config file...");
	if (!o_config.read(configFileName)) {
		puts("Unable to read config file. Closing...");
		exit(0);
	}

	double time_taken = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - load_start).count()) / 1000.0;

	printf("Config loaded (%fms)." ENDL, time_taken);

	if (plugins_directory.empty())
		plugins_directory = o_config.get("PluginsDirectory"_jrs);

	if (configs_directory.empty())
		configs_directory = o_config.get("ConfigsDirectory"_jrs);

	if (!plugins_directory.empty()) {
		Jupiter::Plugin::setDirectory(plugins_directory);
		printf("Plugins will be loaded from \"%.*s\"." ENDL, static_cast<int>(plugins_directory.size()), plugins_directory.data());
	}

	if (!configs_directory.empty()) {
		Jupiter::Plugin::setConfigDirectory(configs_directory);
		printf("Plugin configs will be loaded from \"%.*s\"." ENDL, static_cast<int>(configs_directory.size()), configs_directory.data());
	}

	initialize_plugins();

	printf("Initialization completed in %f milliseconds." ENDL, static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - Jupiter::g_start_time).count()) / 1000.0 );

	if (!consoleCommands.empty()) {
		printf("%zu Console Commands have been initialized%s" ENDL, consoleCommands.size(), getConsoleCommand("help"_jrs) == nullptr ? "." : "; type \"help\" for more information.");
	}
	if (!IRCMasterCommandList.empty()) {
		printf("%zu IRC Commands have been loaded into the master list." ENDL, IRCMasterCommandList.size());
	}

	main_loop();
	return 0;
}