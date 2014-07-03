/**
 * Copyright (C) 2014 Justin James.
 *
 * This license must be preserved.
 * Any applications, libraries, or code which make any use of any
 * component of this program must not be commercial, unless explicit
 * permission is granted from the original author. The use of this
 * program for non-profit purposes is permitted.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * In the event that this license restricts you from making desired use of this program, contact the original author.
 * Written by Justin James <justin.aj@hotmail.com>
 */

#if !defined _SERVERMANAGER_H_HEADER
#define _SERVERMANAGER_H_HEADER

/**
 * @file ServerManager.h
 * @brief Provides a system for controlling and affecting multiple IRC connections simultaneously.
 */

#include "Jupiter_Bot.h"
#include "Jupiter/Thinker.h"
#include "Jupiter/ArrayList.h"
#include "Jupiter/Readable_String.h"

/** Forward declarations */
class IRC_Bot;
class IRCCommand;

/** DLL Linkage Nagging */
#if defined _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

/**
* @brief Provides a system for controlling and affecting multiple IRC connections simultaneously.
*/
class JUPITER_BOT_API ServerManager : public Jupiter::Thinker
{
public:
	/**
	* @brief Calls think() on all of the managed connections.
	*
	* @return false if there are still active connections, true otherwise.
	*/
	int think();

	/**
	* @brief Adds a copy of a command to each managed server.
	*
	* @param command Command to copy to each server.
	* @return Number of servers copied to.
	*/
	size_t addCommand(IRCCommand *command);

	/**
	* @brief Removes any command which matches an input command's primary trigger.
	*
	* @param command Command to get the trigger of.
	* @return Number of servers which had a command removed.
	*/
	size_t removeCommand(IRCCommand *command);

	/**
	* @brief Removes any command which matches a trigger.
	*
	* @param command Trigger to match against.
	* @return Number of servers which had a command removed.
	*/
	size_t removeCommand(const Jupiter::ReadableString &command);

	/**
	* @brief Syncs command access levels from the configuration file.
	*
	* @return Number of servers sync'd.
	*/
	size_t syncCommands();

	/**
	* @brief Fetches a server based on its configuration section
	*
	* @param serverConfig Configuration section to match against.
	* @return Pointer to a matching server instance on success, nullptr otherwise.
	*/
	IRC_Bot *getServer(const Jupiter::ReadableString &serverConfig);

	/**
	* @brief Fetches a server based on its index.
	*
	* @param index Index of the server to fetch.
	* @return Pointer to a server on success, nullptr otherwise.
	*/
	IRC_Bot *getServer(size_t index);

	/**
	* @brief Adds a server based on its configuration section to the list.
	*
	* @return True if a socket connection was successfully established, false otherwise.
	*/
	bool addServer(const Jupiter::ReadableString &serverConfig);

	/**
	* @brief Removes a server from the manager, based on its index.
	*
	* @param index Index of the server to remove.
	* @return True if a server was removed, false otherwise.
	*/
	bool freeServer(size_t index);

	/**
	* @brief Removes a server from the manager, based on its data.
	*
	* @param server Data of the server to remove.
	* @return True if a server was removed, false otherwise.
	*/
	bool freeServer(IRC_Bot *server);

	/**
	* @brief Removes a server from the manager, based on its configuration section.
	*
	* @param serverConfig Configuration section of the server to remove.
	* @return True if a server was removed, false otherwise.
	*/
	bool freeServer(const Jupiter::ReadableString &serverConfig);

	/**
	* @brief Returns the number of servers in the list.
	*
	* @return Number of servers in the list.
	*/
	size_t size();

	/**
	* Destructor for the ServerManager class.
	*/
	virtual ~ServerManager();

private:
	/** Underlying ArrayList of servers */
	Jupiter::ArrayList<IRC_Bot> servers;
};

/** Pointer to an instance of the server manager. Note: DO NOT DELETE OR FREE THIS POINTER. */
JUPITER_BOT_API extern ServerManager *serverManager;

/** Re-enable warnings */
#if defined _MSC_VER
#pragma warning(pop)
#endif

#endif // _SERVERMANAGER_H_HEADER