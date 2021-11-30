/**
 * Copyright (C) 2014-2017 Jessica James.
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

#include "IRC_Bot.h"
#include "RenX_Logging.h"
#include "RenX_Core.h"
#include "RenX_PlayerInfo.h"
#include "RenX_Functions.h"
#include "RenX_Server.h"
#include "RenX_Tags.h"

using namespace Jupiter::literals;

bool RenX_LoggingPlugin::initialize()
{
	RenX_LoggingPlugin::muteOwnExecute = this->config.get<bool>("MuteOwnExecute"_jrs, true);
	RenX_LoggingPlugin::playerRDNSPublic = this->config.get<bool>("PlayerRDNSPublic"_jrs, false);
	RenX_LoggingPlugin::playerIdentifyPublic = this->config.get<bool>("PlayerIdentifyPublic"_jrs, false);
	RenX_LoggingPlugin::joinPublic = this->config.get<bool>("JoinPublic"_jrs, true);
	RenX_LoggingPlugin::partPublic = this->config.get<bool>("PartPublic"_jrs, true);
	RenX_LoggingPlugin::kickPublic = this->config.get<bool>("KickPublic"_jrs, true);
	RenX_LoggingPlugin::nameChangePublic = this->config.get<bool>("NameChangePublic"_jrs, true);
	RenX_LoggingPlugin::teamChangePublic = this->config.get<bool>("TeamChangePublic"_jrs, true);
	RenX_LoggingPlugin::speedHackPublic = this->config.get<bool>("SpeedHackPublic"_jrs, false);
	RenX_LoggingPlugin::playerPublic = this->config.get<bool>("PlayerPublic"_jrs, false);
	RenX_LoggingPlugin::chatPublic = this->config.get<bool>("ChatPublic"_jrs, true);
	RenX_LoggingPlugin::teamChatPublic = this->config.get<bool>("TeamChatPublic"_jrs, false);
	RenX_LoggingPlugin::radioChatPublic = this->config.get<bool>("RadioChatPublic"_jrs, false);
	RenX_LoggingPlugin::hostChatPublic = this->config.get<bool>("HostChatPublic"_jrs, true);
	RenX_LoggingPlugin::hostPagePublic = this->config.get<bool>("HostPagePublic"_jrs, false);
	RenX_LoggingPlugin::adminMessagePublic = this->config.get<bool>("AdminMessagePublic"_jrs, true);
	RenX_LoggingPlugin::adminPMessagePublic = this->config.get<bool>("AdminPagePublic"_jrs, false);
	RenX_LoggingPlugin::otherChatPublic = this->config.get<bool>("OtherChatPublic"_jrs, false);
	RenX_LoggingPlugin::deployPublic = this->config.get<bool>("DeployPublic"_jrs, true);
	RenX_LoggingPlugin::mineDeployPublic = this->config.get<bool>("MineDeployPublic"_jrs, false);
	RenX_LoggingPlugin::overMinePublic = this->config.get<bool>("OverMinePublic"_jrs, false);
	RenX_LoggingPlugin::disarmPublic = this->config.get<bool>("DisarmPublic"_jrs, true);
	RenX_LoggingPlugin::mineDisarmPublic = this->config.get<bool>("MineDisarmPublic"_jrs, false);
	RenX_LoggingPlugin::explodePublic = this->config.get<bool>("ExplodePublic"_jrs, false);
	RenX_LoggingPlugin::suicidePublic = this->config.get<bool>("SuicidePublic"_jrs, true);
	RenX_LoggingPlugin::killPublic = this->config.get<bool>("KillPublic"_jrs, true);
	RenX_LoggingPlugin::diePublic = this->config.get<bool>("DiePublic"_jrs, true);
	RenX_LoggingPlugin::destroyPublic = this->config.get<bool>("DestroyPublic"_jrs, true);
	RenX_LoggingPlugin::capturePublic = this->config.get<bool>("CapturePublic"_jrs, true);
	RenX_LoggingPlugin::neutralizePublic = this->config.get<bool>("NeutralizePublic"_jrs, true);
	RenX_LoggingPlugin::characterPurchasePublic = this->config.get<bool>("CharacterPurchasePublic"_jrs, false);
	RenX_LoggingPlugin::itemPurchasePublic = this->config.get<bool>("ItemPurchasePublic"_jrs, false);
	RenX_LoggingPlugin::weaponPurchasePublic = this->config.get<bool>("WeaponPurchasePublic"_jrs, false);
	RenX_LoggingPlugin::refillPurchasePublic = this->config.get<bool>("RefillPurchasePublic"_jrs, false);
	RenX_LoggingPlugin::vehiclePurchasePublic = this->config.get<bool>("VehiclePurchasePublic"_jrs, false);
	RenX_LoggingPlugin::vehicleSpawnPublic = this->config.get<bool>("VehicleSpawnPublic"_jrs, true);
	RenX_LoggingPlugin::spawnPublic = this->config.get<bool>("SpawnPublic"_jrs, true);
	RenX_LoggingPlugin::botJoinPublic = this->config.get<bool>("BotJoinPublic"_jrs, true);
	RenX_LoggingPlugin::vehicleCratePublic = this->config.get<bool>("VehicleCratePublic"_jrs, false);
	RenX_LoggingPlugin::TSVehicleCratePublic = this->config.get<bool>("TSVehicleCratePublic"_jrs, RenX_LoggingPlugin::vehicleCratePublic);
	RenX_LoggingPlugin::RAVehicleCratePublic = this->config.get<bool>("RAVehicleCratePublic"_jrs, RenX_LoggingPlugin::vehicleCratePublic);
	RenX_LoggingPlugin::deathCratePublic = this->config.get<bool>("DeathCratePublic"_jrs, true);
	RenX_LoggingPlugin::moneyCratePublic = this->config.get<bool>("MoneyCratePublic"_jrs, false);
	RenX_LoggingPlugin::characterCratePublic = this->config.get<bool>("CharacterCratePublic"_jrs, false);
	RenX_LoggingPlugin::spyCratePublic = this->config.get<bool>("SpyCratePublic"_jrs, false);
	RenX_LoggingPlugin::refillCratePublic = this->config.get<bool>("RefillCratePublic"_jrs, false);
	RenX_LoggingPlugin::timeBombCratePublic = this->config.get<bool>("TimeBombCratePublic"_jrs, false);
	RenX_LoggingPlugin::speedCratePublic = this->config.get<bool>("SpeedCratePublic"_jrs, false);
	RenX_LoggingPlugin::nukeCratePublic = this->config.get<bool>("NukeCratePublic"_jrs, true);
	RenX_LoggingPlugin::abductionCratePublic = this->config.get<bool>("AbductionCratePublic"_jrs, true);
	RenX_LoggingPlugin::unspecifiedCratePublic = this->config.get<bool>("UnspecifiedCratePublic"_jrs, false);
	RenX_LoggingPlugin::otherCratePublic = this->config.get<bool>("OtherCratePublic"_jrs, false);
	RenX_LoggingPlugin::stealPublic = this->config.get<bool>("StealPublic"_jrs, true);
	RenX_LoggingPlugin::donatePublic = this->config.get<bool>("DonatePublic"_jrs, true);
	RenX_LoggingPlugin::gamePublic = this->config.get<bool>("GamePublic"_jrs, true);
	RenX_LoggingPlugin::gameOverPublic = this->config.get<bool>("GameOverPublic"_jrs, true);
	RenX_LoggingPlugin::executePublic = this->config.get<bool>("ExecutePublic"_jrs, false);
	RenX_LoggingPlugin::playerCommandPublic = this->config.get<bool>("PlayerCommandPublic"_jrs, false);
	RenX_LoggingPlugin::subscribePublic = this->config.get<bool>("SubscribePublic"_jrs, false);
	RenX_LoggingPlugin::RCONPublic = this->config.get<bool>("RCONPublic"_jrs, false);
	RenX_LoggingPlugin::adminLoginPublic = this->config.get<bool>("AdminLoginPublic"_jrs, true);
	RenX_LoggingPlugin::adminGrantPublic = this->config.get<bool>("AdminGrantPublic"_jrs, true);
	RenX_LoggingPlugin::adminLogoutPublic = this->config.get<bool>("AdminLogoutPublic"_jrs, true);
	RenX_LoggingPlugin::adminPublic = this->config.get<bool>("AdminPublic"_jrs, false);
	RenX_LoggingPlugin::voteCallPublic = this->config.get<bool>("VoteCallPublic"_jrs, true);
	RenX_LoggingPlugin::voteOverPublic = this->config.get<bool>("VoteOverPublic"_jrs, true);
	RenX_LoggingPlugin::voteCancelPublic = this->config.get<bool>("VoteCancelPublic"_jrs, true);
	RenX_LoggingPlugin::votePublic = this->config.get<bool>("VotePublic"_jrs, false);
	RenX_LoggingPlugin::mapChangePublic = this->config.get<bool>("MapChangePublic"_jrs, true);
	RenX_LoggingPlugin::mapLoadPublic = this->config.get<bool>("MapLoadPublic"_jrs, true);
	RenX_LoggingPlugin::mapStartPublic = this->config.get<bool>("MapStartPublic"_jrs, true);
	RenX_LoggingPlugin::mapPublic = this->config.get<bool>("MapPublic"_jrs, false);
	RenX_LoggingPlugin::demoRecordPublic = this->config.get<bool>("DemoRecordPublic"_jrs, true);
	RenX_LoggingPlugin::demoRecordStopPublic = this->config.get<bool>("DemoRecordStopPublic"_jrs, true);
	RenX_LoggingPlugin::demoPublic = this->config.get<bool>("DemoPublic"_jrs, false);
	RenX_LoggingPlugin::logPublic = this->config.get<bool>("LogPublic"_jrs, false);
	RenX_LoggingPlugin::commandPublic = this->config.get<bool>("CommandPublic"_jrs, false);
	RenX_LoggingPlugin::errorPublic = this->config.get<bool>("ErrorPublic"_jrs, false);
	RenX_LoggingPlugin::versionPublic = this->config.get<bool>("VersionPublic"_jrs, true);
	RenX_LoggingPlugin::authorizedPublic = this->config.get<bool>("AuthorizedPublic"_jrs, true);
	RenX_LoggingPlugin::otherPublic = this->config.get<bool>("OtherPublic"_jrs, false);

	/** Event formats */
	RenX_LoggingPlugin::playerRDNSFmt = this->config.get("PlayerRDNSFormat"_jrs,
		""_jrs);

	RenX_LoggingPlugin::playerIdentifyFmt = this->config.get("PlayerIdentifyFormat"_jrs,
		Jupiter::StringS::Format(IRCCOLOR "12[Join] " IRCBOLD "%.*s" IRCBOLD " (" IRCBOLD "%.*s" IRCBOLD ") joined the game fighting for the %.*s from " IRCBOLD "%.*s" IRCBOLD " (" IRCBOLD "%.*s" IRCBOLD ") with HWID " IRCBOLD "%.*s" IRCBOLD ".", RenX::tags->nameTag.size(),
			RenX::tags->nameTag.data(), RenX::tags->steamTag.size(),
			RenX::tags->steamTag.data(), RenX::tags->teamLongTag.size(),
			RenX::tags->teamLongTag.data(), RenX::tags->ipTag.size(),
			RenX::tags->ipTag.data(), RenX::tags->rdnsTag.size(),
			RenX::tags->rdnsTag.data(), RenX::tags->hwidTag.size(),
			RenX::tags->hwidTag.data()));

	RenX_LoggingPlugin::joinPublicFmt = this->config.get("JoinPublicFormat"_jrs,
		Jupiter::StringS::Format(IRCCOLOR "12[Join] " IRCBOLD "%.*s" IRCBOLD " joined the game fighting for the %.*s!", RenX::tags->nameTag.size(),
			RenX::tags->nameTag.data(), RenX::tags->teamLongTag.size(),
			RenX::tags->teamLongTag.data()));

	RenX_LoggingPlugin::joinAdminFmt = this->config.get("JoinAdminFormat"_jrs,
		""_jrs);

	RenX_LoggingPlugin::joinNoSteamAdminFmt = this->config.get("JoinNoSteamAdminFormat"_jrs,
		""_jrs);

	RenX_LoggingPlugin::partFmt = this->config.get("PartFormat"_jrs,
		Jupiter::StringS::Format(IRCCOLOR "12[Part] " IRCBOLD "%.*s" IRCBOLD " left the %.*s.", RenX::tags->nameTag.size(),
			RenX::tags->nameTag.data(), RenX::tags->teamLongTag.size(),
			RenX::tags->teamLongTag.data()));

	RenX_LoggingPlugin::kickFmt = this->config.get("KickFormat"_jrs,
		Jupiter::StringS::Format(IRCCOLOR "04[Kick] " IRCBOLD "%.*s" IRCCOLOR IRCBOLD " was " IRCBOLD IRCCOLOR "04kicked" IRCCOLOR IRCBOLD " (" IRCCOLOR "04%.*s" IRCCOLOR ")", RenX::tags->nameTag.size(),
			RenX::tags->nameTag.data(), RenX::tags->messageTag.size(),
			RenX::tags->messageTag.data()));

	RenX_LoggingPlugin::playerExecuteFmt = this->config.get("PlayerExecuteFormat"_jrs,
		Jupiter::StringS::Format("%.*s" IRCCOLOR "07 executed: %.*s", RenX::tags->nameTag.size(),
			RenX::tags->nameTag.data(), RenX::tags->messageTag.size(),
			RenX::tags->messageTag.data()));

	RenX_LoggingPlugin::playerCommandSuccessFmt = this->config.get("PlayerCommandSuccessFormat"_jrs,
		Jupiter::StringS::Format("%.*s" IRCCOLOR ": " IRCCOLOR "10%.*s", RenX::tags->nameTag.size(),
			RenX::tags->nameTag.data(), RenX::tags->messageTag.size(),
			RenX::tags->messageTag.data()));

	RenX_LoggingPlugin::playerCommandFailFmt = this->config.get("PlayerCommandFailFormat"_jrs, ""_jss);

	RenX_LoggingPlugin::playerFmt = this->config.get("PlayerFormat"_jrs,
		Jupiter::StringS::Format(IRCCOLOR "12[Player]" IRCCOLOR " %.*s", RenX::tags->messageTag.size(),
			RenX::tags->messageTag.data()));

	RenX_LoggingPlugin::nameChangeFmt = this->config.get("NameChangeFormat"_jrs,
		Jupiter::StringS::Format(IRCBOLD "%.*s" IRCBOLD " changed their name to " IRCBOLD "%.*s" IRCBOLD ".", RenX::tags->nameTag.size(),
			RenX::tags->nameTag.data(), RenX::tags->newNameTag.size(),
			RenX::tags->newNameTag.data()));

	RenX_LoggingPlugin::teamChangeFmt = this->config.get("TeamChangeFormat"_jrs,
		Jupiter::StringS::Format("%.*s" IRCCOLOR " switched teams!", RenX::tags->nameTag.size(),
			RenX::tags->nameTag.data()));

	RenX_LoggingPlugin::speedHackFmt = this->config.get("SpeedHackFormat"_jrs,
		Jupiter::StringS::Format(IRCCOLOR "04[SpeedHack] " IRCBOLD "%.*s" IRCBOLD " has thrown a Speed Hack warning!", RenX::tags->nameTag.size(),
			RenX::tags->nameTag.data()));

	RenX_LoggingPlugin::chatFmt = this->config.get("ChatFormat"_jrs,
		Jupiter::StringS::Format(IRCBOLD "%.*s" IRCCOLOR IRCBOLD ": %.*s", RenX::tags->nameTag.size(),
			RenX::tags->nameTag.data(), RenX::tags->messageTag.size(),
			RenX::tags->messageTag.data()));

	RenX_LoggingPlugin::teamChatFmt = this->config.get("TeamChatFormat"_jrs,
		Jupiter::StringS::Format(IRCBOLD "%.*s" IRCBOLD ": %.*s", RenX::tags->nameTag.size(), RenX::tags->nameTag.data(), RenX::tags->messageTag.size(),
			RenX::tags->messageTag.data()));

	RenX_LoggingPlugin::radioChatFmt = this->config.get("RadioChatFormat"_jrs,
		Jupiter::StringS::Format(IRCBOLD "%.*s" IRCBOLD ": \x1D%.*s", RenX::tags->nameTag.size(),
			RenX::tags->nameTag.data(), RenX::tags->messageTag.size(),
			RenX::tags->messageTag.data()));

	RenX_LoggingPlugin::hostChatFmt = this->config.get("HostChatFormat"_jrs,
		Jupiter::StringS::Format(IRCCOLOR "12Host" IRCCOLOR "0: %.*s", RenX::tags->messageTag.size(),
			RenX::tags->messageTag.data()));

	RenX_LoggingPlugin::hostPageFmt = this->config.get("HostPageFormat"_jrs,
		Jupiter::StringS::Format(IRCCOLOR "12(Host -> %.*s): %.*s", RenX::tags->rawNameTag.size(),
			RenX::tags->rawNameTag.data(), RenX::tags->messageTag.size(),
			RenX::tags->messageTag.data()));

	RenX_LoggingPlugin::adminMsgFmt = this->config.get("AdminMsgFormat"_jrs,
		Jupiter::StringS::Format(IRCCOLOR "10%.*s: %.*s", RenX::tags->rawNameTag.size(), RenX::tags->rawNameTag.data(), RenX::tags->messageTag.size(),
			RenX::tags->messageTag.data()));

	RenX_LoggingPlugin::warnMsgFmt = this->config.get("WarnMsgFormat"_jrs,
		Jupiter::StringS::Format(IRCCOLOR "07%.*s: %.*s", RenX::tags->rawNameTag.size(), RenX::tags->rawNameTag.data(), RenX::tags->messageTag.size(),
			RenX::tags->messageTag.data()));

	RenX_LoggingPlugin::pAdminMsgFmt = this->config.get("PAdminMsgFormat"_jrs,
		Jupiter::StringS::Format(IRCCOLOR "10(%.*s -> %.*s): %.*s", RenX::tags->rawNameTag.size(),
			RenX::tags->rawNameTag.data(), RenX::tags->victimRawNameTag.size(),
			RenX::tags->victimRawNameTag.data(), RenX::tags->messageTag.size(),
			RenX::tags->messageTag.data()));

	RenX_LoggingPlugin::pWarnMsgFmt = this->config.get("PWarnMsgFormat"_jrs,
		Jupiter::StringS::Format(IRCCOLOR "07(%.*s -> %.*s): %.*s", RenX::tags->rawNameTag.size(),
			RenX::tags->rawNameTag.data(), RenX::tags->victimRawNameTag.size(),
			RenX::tags->victimRawNameTag.data(), RenX::tags->messageTag.size(),
			RenX::tags->messageTag.data()));

	RenX_LoggingPlugin::otherChatFmt = this->config.get("OtherChatFormat"_jrs,
		Jupiter::StringS::Format(IRCCOLOR "06[Other Chat]" IRCCOLOR " %.*s", RenX::tags->messageTag.size(),
			RenX::tags->messageTag.data()));

	RenX_LoggingPlugin::deployFmt = this->config.get("DeployFormat"_jrs,
		Jupiter::StringS::Format(IRCBOLD "%.*s" IRCCOLOR IRCBOLD " deployed a " IRCBOLD IRCCOLOR "12%.*s" IRCBOLD, RenX::tags->nameTag.size(),
			RenX::tags->nameTag.data(), RenX::tags->objectTag.size(),
			RenX::tags->objectTag.data()));

	RenX_LoggingPlugin::mineDeployFmt = this->config.get("MineDeployFormat"_jrs,
		RenX_LoggingPlugin::deployFmt);

	RenX_LoggingPlugin::overMineFmt = this->config.get("OverMineFormat"_jrs,
		Jupiter::StringS::Format(IRCBOLD "%.*s" IRCCOLOR IRCBOLD " is " IRCCOLOR "04over-mining" IRCCOLOR ": " IRCBOLD IRCCOLOR "12%.*s" IRCBOLD, RenX::tags->nameTag.size(),
			RenX::tags->nameTag.data(), RenX::tags->objectTag.size(),
			RenX::tags->objectTag.data()));

	RenX_LoggingPlugin::disarmFmt = this->config.get("DisarmFormat"_jrs,
		Jupiter::StringS::Format(IRCBOLD "%.*s" IRCCOLOR IRCBOLD " disarmed %.*s" IRCBOLD IRCCOLOR "'s " IRCCOLOR "12%.*s" IRCBOLD, RenX::tags->nameTag.size(),
			RenX::tags->nameTag.data(), RenX::tags->victimNameTag.size(),
			RenX::tags->victimNameTag.data(), RenX::tags->objectTag.size(),
			RenX::tags->objectTag.data()));

	RenX_LoggingPlugin::mineDisarmFmt = this->config.get("MineDisarmFormat"_jrs,
		RenX_LoggingPlugin::disarmFmt);

	RenX_LoggingPlugin::disarmNoOwnerFmt = this->config.get("DisarmNoOwnerFormat"_jrs,
		Jupiter::StringS::Format(IRCBOLD "%.*s" IRCBOLD " disarmed a " IRCBOLD "%.*s" IRCBOLD, RenX::tags->nameTag.size(),
			RenX::tags->nameTag.data(), RenX::tags->objectTag.size(),
			RenX::tags->objectTag.data()));

	RenX_LoggingPlugin::mineDisarmNoOwnerFmt = this->config.get("MineDisarmNoOwnerFormat"_jrs,
		RenX_LoggingPlugin::disarmNoOwnerFmt);

	RenX_LoggingPlugin::explodeFmt = this->config.get("ExplodeFormat"_jrs,
		Jupiter::StringS::Format("%.*s" IRCCOLOR " detonated a " IRCCOLOR "07%.*s" IRCCOLOR ".", RenX::tags->nameTag.size(),
			RenX::tags->nameTag.data(), RenX::tags->weaponTag.size(),
			RenX::tags->weaponTag.data()));

	RenX_LoggingPlugin::explodeNoOwnerFmt = this->config.get("ExplodeNoOwnerFormat"_jrs,
		Jupiter::StringS::Format("A " IRCCOLOR "07%.*s" IRCCOLOR " detonated.", RenX::tags->weaponTag.size(),
			RenX::tags->weaponTag.data()));

	RenX_LoggingPlugin::suicideFmt = this->config.get("SuicideFormat"_jrs,
		Jupiter::StringS::Format("%.*s" IRCCOLOR " suicided (" IRCCOLOR "12%.*s" IRCCOLOR ").", RenX::tags->nameTag.size(),
			RenX::tags->nameTag.data(), RenX::tags->weaponTag.size(),
			RenX::tags->weaponTag.data()));

	RenX_LoggingPlugin::killFmt = this->config.get("KillFormat"_jrs,
		Jupiter::StringS::Format("%.*s" IRCCOLOR " killed %.*s" IRCCOLOR " (" IRCCOLOR "%.*s%.*s/%.*s" IRCCOLOR " vs " IRCCOLOR "%.*s%.*s" IRCCOLOR ").", RenX::tags->nameTag.size(),
			RenX::tags->nameTag.data(), RenX::tags->victimNameTag.size(),
			RenX::tags->victimNameTag.data(), RenX::tags->teamColorTag.size(),
			RenX::tags->teamColorTag.data(), RenX::tags->characterTag.size(),
			RenX::tags->characterTag.data(), RenX::tags->weaponTag.size(),
			RenX::tags->weaponTag.data(), RenX::tags->victimTeamColorTag.size(),
			RenX::tags->victimTeamColorTag.data(), RenX::tags->victimCharacterTag.size(),
			RenX::tags->victimCharacterTag.data()));

	RenX_LoggingPlugin::killFmt2 = this->config.get("KillFormat2"_jrs,
		Jupiter::StringS::Format(IRCCOLOR "%.*s%.*s" IRCCOLOR " killed %.*s" IRCCOLOR " (" IRCCOLOR "12%.*s" IRCCOLOR ").", RenX::tags->teamColorTag.size(),
			RenX::tags->teamColorTag.data(), RenX::tags->nameTag.size(),
			RenX::tags->nameTag.data(), RenX::tags->victimNameTag.size(),
			RenX::tags->victimNameTag.data(), RenX::tags->weaponTag.size(),
			RenX::tags->weaponTag.data()));

	RenX_LoggingPlugin::dieFmt = this->config.get("DieFormat"_jrs,
		Jupiter::StringS::Format("%.*s" IRCCOLOR " died (" IRCCOLOR "12%.*s" IRCCOLOR ").", RenX::tags->nameTag.size(),
			RenX::tags->nameTag.data(), RenX::tags->weaponTag.size(),
			RenX::tags->weaponTag.data()));

	RenX_LoggingPlugin::dieFmt2 = this->config.get("DieFormat2"_jrs,
		Jupiter::StringS::Format(IRCCOLOR "%.*s%.*s" IRCCOLOR " died (" IRCCOLOR "12%.*s" IRCCOLOR ").", RenX::tags->teamColorTag.size(),
			RenX::tags->teamColorTag.data(), RenX::tags->nameTag.size(),
			RenX::tags->nameTag.data(), RenX::tags->weaponTag.size(),
			RenX::tags->weaponTag.data()));

	RenX_LoggingPlugin::destroyBuildingFmt = this->config.get("DestroyBuildingFormat"_jrs,
		Jupiter::StringS::Format("%.*s" IRCCOLOR " destroyed the " IRCCOLOR "%.*s%.*s" IRCCOLOR " (" IRCCOLOR "12%.*s" IRCCOLOR ").", RenX::tags->nameTag.size(),
			RenX::tags->nameTag.data(), RenX::tags->victimTeamColorTag.size(),
			RenX::tags->victimTeamColorTag.data(), RenX::tags->objectTag.size(),
			RenX::tags->objectTag.data(), RenX::tags->weaponTag.size(),
			RenX::tags->weaponTag.data()));
	
	RenX_LoggingPlugin::destroyBuildingFmt2 = this->config.get("DestroyBuildingFormat2"_jrs,
		Jupiter::StringS::Format(IRCCOLOR "%.*s%.*s" IRCCOLOR " destroyed the " IRCCOLOR "%.*s%.*s" IRCCOLOR " (" IRCCOLOR "12%.*s" IRCCOLOR ").", RenX::tags->teamColorTag.size(),
			RenX::tags->teamColorTag.data(), RenX::tags->nameTag.size(),
			RenX::tags->nameTag.data(), RenX::tags->victimTeamColorTag.size(),
			RenX::tags->victimTeamColorTag.data(), RenX::tags->objectTag.size(),
			RenX::tags->objectTag.data(), RenX::tags->weaponTag.size(),
			RenX::tags->weaponTag.data()));

	RenX_LoggingPlugin::destroyDefenceFmt = this->config.get("DestroyDefenceFormat"_jrs,
		Jupiter::StringS::Format("%.*s" IRCCOLOR " destroyed a " IRCCOLOR "%.*s%.*s" IRCCOLOR " (" IRCCOLOR "12%.*s" IRCCOLOR ").", RenX::tags->nameTag.size(),
			RenX::tags->nameTag.data(), RenX::tags->victimTeamColorTag.size(),
			RenX::tags->victimTeamColorTag.data(), RenX::tags->objectTag.size(),
			RenX::tags->objectTag.data(), RenX::tags->weaponTag.size(),
			RenX::tags->weaponTag.data()));
	
	RenX_LoggingPlugin::destroyDefenceFmt2 = this->config.get("DestroyDefenceFormat2"_jrs,
		Jupiter::StringS::Format(IRCCOLOR "%.*s%.*s" IRCCOLOR " destroyed a " IRCCOLOR "%.*s%.*s" IRCCOLOR " (" IRCCOLOR "12%.*s" IRCCOLOR ").", RenX::tags->teamColorTag.size(),
			RenX::tags->teamColorTag.data(), RenX::tags->nameTag.size(),
			RenX::tags->nameTag.data(), RenX::tags->victimTeamColorTag.size(),
			RenX::tags->victimTeamColorTag.data(), RenX::tags->objectTag.size(),
			RenX::tags->objectTag.data(), RenX::tags->weaponTag.size(),
			RenX::tags->weaponTag.data()));

	RenX_LoggingPlugin::destroyVehicleFmt = this->config.get("DestroyVehicleFormat"_jrs,
		Jupiter::StringS::Format("%.*s" IRCCOLOR " destroyed a " IRCCOLOR "%.*s%.*s" IRCCOLOR " (" IRCCOLOR "12%.*s" IRCCOLOR ").", RenX::tags->nameTag.size(),
			RenX::tags->nameTag.data(), RenX::tags->victimTeamColorTag.size(),
			RenX::tags->victimTeamColorTag.data(), RenX::tags->objectTag.size(),
			RenX::tags->objectTag.data(), RenX::tags->weaponTag.size(),
			RenX::tags->weaponTag.data()));

	RenX_LoggingPlugin::destroyVehicleFmt2 = this->config.get("DestroyVehicleFormat2"_jrs,
		Jupiter::StringS::Format(IRCCOLOR "%.*s%.*s" IRCCOLOR " destroyed a " IRCCOLOR "%.*s%.*s" IRCCOLOR " (" IRCCOLOR "12%.*s" IRCCOLOR ").", RenX::tags->teamColorTag.size(),
			RenX::tags->teamColorTag.data(), RenX::tags->nameTag.size(),
			RenX::tags->nameTag.data(), RenX::tags->victimTeamColorTag.size(),
			RenX::tags->victimTeamColorTag.data(), RenX::tags->objectTag.size(),
			RenX::tags->objectTag.data(), RenX::tags->weaponTag.size(),
			RenX::tags->weaponTag.data()));

	RenX_LoggingPlugin::captureFmt = this->config.get("CaptureFormat"_jrs,
		Jupiter::StringS::Format(IRCBOLD "%.*s" IRCCOLOR IRCBOLD " captured the " IRCBOLD IRCCOLOR "%.*s%.*s" IRCCOLOR IRCBOLD ".", RenX::tags->nameTag.size(),
			RenX::tags->nameTag.data(), RenX::tags->victimTeamColorTag.size(),
			RenX::tags->victimTeamColorTag.data(), RenX::tags->objectTag.size(),
			RenX::tags->objectTag.data()));

	RenX_LoggingPlugin::neutralizeFmt = this->config.get("NeutralizeFormat"_jrs,
		Jupiter::StringS::Format(IRCBOLD "%.*s" IRCCOLOR IRCBOLD " neutralized the " IRCBOLD IRCCOLOR "%.*s%.*s" IRCCOLOR IRCBOLD ".", RenX::tags->nameTag.size(),
			RenX::tags->nameTag.data(), RenX::tags->victimTeamColorTag.size(),
			RenX::tags->victimTeamColorTag.data(), RenX::tags->objectTag.size(),
			RenX::tags->objectTag.data()));

	RenX_LoggingPlugin::characterPurchaseFmt = this->config.get("CharacterPurchaseFormat"_jrs,
		Jupiter::StringS::Format(IRCBOLD "%.*s" IRCCOLOR IRCBOLD " purchased a " IRCBOLD IRCCOLOR "%.*s%.*s" IRCCOLOR IRCBOLD ".", RenX::tags->nameTag.size(),
			RenX::tags->nameTag.data(), RenX::tags->teamColorTag.size(),
			RenX::tags->teamColorTag.data(), RenX::tags->victimCharacterTag.size(),
			RenX::tags->victimCharacterTag.data()));

	RenX_LoggingPlugin::itemPurchaseFmt = this->config.get("ItemPurchaseFormat"_jrs,
		Jupiter::StringS::Format(IRCBOLD "%.*s" IRCCOLOR IRCBOLD " purchased a " IRCBOLD IRCCOLOR "%.*s%.*s" IRCCOLOR IRCBOLD ".", RenX::tags->nameTag.size(),
			RenX::tags->nameTag.data(), RenX::tags->teamColorTag.size(),
			RenX::tags->teamColorTag.data(), RenX::tags->objectTag.size(),
			RenX::tags->objectTag.data()));

	RenX_LoggingPlugin::weaponPurchaseFmt = this->config.get("WeaponPurchaseFormat"_jrs,
		Jupiter::StringS::Format(IRCBOLD "%.*s" IRCCOLOR IRCBOLD " purchased a " IRCBOLD IRCCOLOR "%.*s%.*s" IRCCOLOR IRCBOLD ".", RenX::tags->nameTag.size(),
			RenX::tags->nameTag.data(), RenX::tags->teamColorTag.size(),
			RenX::tags->teamColorTag.data(), RenX::tags->weaponTag.size(),
			RenX::tags->weaponTag.data()));

	RenX_LoggingPlugin::refillPurchaseFmt = this->config.get("RefillPurchaseFormat"_jrs,
		Jupiter::StringS::Format(IRCBOLD "%.*s" IRCCOLOR IRCBOLD " purchased a " IRCBOLD IRCCOLOR "%.*srefill" IRCCOLOR IRCBOLD ".", RenX::tags->nameTag.size(),
			RenX::tags->nameTag.data(), RenX::tags->teamColorTag.size(),
			RenX::tags->teamColorTag.data()));

	RenX_LoggingPlugin::vehiclePurchaseFmt = this->config.get("VehiclePurchaseFormat"_jrs,
		Jupiter::StringS::Format(IRCBOLD "%.*s" IRCCOLOR IRCBOLD " purchased a " IRCBOLD IRCCOLOR "%.*s%.*s" IRCCOLOR IRCBOLD ".", RenX::tags->nameTag.size(),
			RenX::tags->nameTag.data(), RenX::tags->teamColorTag.size(),
			RenX::tags->teamColorTag.data(), RenX::tags->victimVehicleTag.size(),
			RenX::tags->victimVehicleTag.data()));

	RenX_LoggingPlugin::vehicleSpawnFmt = this->config.get("VehicleSpawnFormat"_jrs,
		Jupiter::StringS::Format("A " IRCBOLD IRCCOLOR "%.*s%.*s" IRCCOLOR IRCBOLD " has spawned.", RenX::tags->teamColorTag.size(),
			RenX::tags->teamColorTag.data(), RenX::tags->vehicleTag.size(),
			RenX::tags->vehicleTag.data()));

	RenX_LoggingPlugin::spawnFmt = this->config.get("SpawnFormat"_jrs,
		Jupiter::StringS::Format(IRCBOLD "%.*s" IRCCOLOR IRCBOLD " spawned as a " IRCCOLOR "%.*s%.*s.", RenX::tags->nameTag.size(),
			RenX::tags->nameTag.data(), RenX::tags->teamColorTag.size(),
			RenX::tags->teamColorTag.data(), RenX::tags->victimCharacterTag.size(),
			RenX::tags->victimCharacterTag.data()));

	RenX_LoggingPlugin::botJoinFmt = this->config.get("BotJoinFormat"_jrs,
		Jupiter::StringS::Format(IRCBOLD "%.*s" IRCCOLOR IRCBOLD " online.", RenX::tags->nameTag.size(),
			RenX::tags->nameTag.data()));

	RenX_LoggingPlugin::vehicleCrateFmt = this->config.get("VehicleCrateFormat"_jrs,
		Jupiter::StringS::Format(IRCBOLD "%.*s" IRCCOLOR IRCBOLD " picked up a " IRCCOLOR "12%.*s" IRCCOLOR " vehicle crate.", RenX::tags->nameTag.size(),
			RenX::tags->nameTag.data(), RenX::tags->objectTag.size(),
			RenX::tags->objectTag.data()));

	RenX_LoggingPlugin::TSVehicleCrateFmt = this->config.get("TSVehicleCrateFormat"_jrs,
		RenX_LoggingPlugin::vehicleCrateFmt);

	RenX_LoggingPlugin::RAVehicleCrateFmt = this->config.get("RAVehicleCrateFormat"_jrs,
		RenX_LoggingPlugin::vehicleCrateFmt);

	RenX_LoggingPlugin::deathCrateFmt = this->config.get("DeathCrateFormat"_jrs,
		Jupiter::StringS::Format(IRCBOLD "%.*s" IRCCOLOR IRCBOLD " picked up a " IRCCOLOR "12death" IRCCOLOR " crate.", RenX::tags->nameTag.size(),
			RenX::tags->nameTag.data()));

	RenX_LoggingPlugin::moneyCrateFmt = this->config.get("MoneyCrateFormat"_jrs,
		Jupiter::StringS::Format(IRCBOLD "%.*s" IRCCOLOR IRCBOLD " picked up " IRCCOLOR "09%.*s credits" IRCCOLOR " from a " IRCCOLOR "12money" IRCCOLOR " crate.", RenX::tags->nameTag.size(),
			RenX::tags->nameTag.data(), RenX::tags->objectTag.size(),
			RenX::tags->objectTag.data()));

	RenX_LoggingPlugin::characterCrateFmt = this->config.get("CharacterCrateFormat"_jrs,
		Jupiter::StringS::Format(IRCBOLD "%.*s" IRCCOLOR IRCBOLD " picked up a " IRCCOLOR "%.*s%.*s" IRCCOLOR " " IRCCOLOR "12character" IRCCOLOR " crate.", RenX::tags->nameTag.size(),
			RenX::tags->nameTag.data(), RenX::tags->teamColorTag.size(),
			RenX::tags->teamColorTag.data(), RenX::tags->victimCharacterTag.size(),
			RenX::tags->victimCharacterTag.data()));

	RenX_LoggingPlugin::spyCrateFmt = this->config.get("SpyCrateFormat"_jrs,
		Jupiter::StringS::Format(IRCBOLD "%.*s" IRCCOLOR IRCBOLD " picked up a " IRCCOLOR "%.*s%.*s" IRCCOLOR " " IRCCOLOR "12spy" IRCCOLOR " crate.", RenX::tags->nameTag.size(),
			RenX::tags->nameTag.data(), RenX::tags->victimTeamColorTag.size(),
			RenX::tags->victimTeamColorTag.data(), RenX::tags->victimCharacterTag.size(),
			RenX::tags->victimCharacterTag.data()));

	RenX_LoggingPlugin::refillCrateFmt = this->config.get("RefillCrateFormat"_jrs,
		Jupiter::StringS::Format(IRCBOLD "%.*s" IRCCOLOR IRCBOLD " picked up a " IRCCOLOR "%.*srefill" IRCCOLOR " crate.", RenX::tags->nameTag.size(),
			RenX::tags->nameTag.data(), RenX::tags->teamColorTag.size(),
			RenX::tags->teamColorTag.data()));

	RenX_LoggingPlugin::timeBombCrateFmt = this->config.get("TimeBombCrateFormat"_jrs,
		Jupiter::StringS::Format(IRCBOLD "%.*s" IRCCOLOR IRCBOLD " picked up a " IRCCOLOR "11time-bomb" IRCCOLOR " crate.", RenX::tags->nameTag.size(),
			RenX::tags->nameTag.data()));

	RenX_LoggingPlugin::speedCrateFmt = this->config.get("SpeedCrateFormat"_jrs,
		Jupiter::StringS::Format(IRCBOLD "%.*s" IRCCOLOR IRCBOLD " picked up a " IRCCOLOR "11speed" IRCCOLOR " crate.", RenX::tags->nameTag.size(),
			RenX::tags->nameTag.data()));

	RenX_LoggingPlugin::nukeCrateFmt = this->config.get("NukeCrateFormat"_jrs,
		Jupiter::StringS::Format(IRCBOLD "%.*s" IRCCOLOR IRCBOLD " picked up a " IRCCOLOR "04nuke" IRCCOLOR " crate.", RenX::tags->nameTag.size(),
			RenX::tags->nameTag.data()));

	RenX_LoggingPlugin::abductionCrateFmt = this->config.get("AbductionCrateFormat"_jrs,
		Jupiter::StringS::Format(IRCBOLD "%.*s" IRCCOLOR IRCBOLD " has been " IRCBOLD IRCCOLOR "06abducted" IRCCOLOR IRCBOLD " by the " IRCBOLD IRCCOLOR "06Scrin" IRCCOLOR IRCBOLD "!", RenX::tags->nameTag.size(),
			RenX::tags->nameTag.data()));

	RenX_LoggingPlugin::unspecifiedCrateFmt = this->config.get("UnspecifiedCrateFormat"_jrs,
		Jupiter::StringS::Format(IRCBOLD "%.*s" IRCCOLOR IRCBOLD " picked up an " IRCCOLOR "13unspecified" IRCCOLOR " crate.", RenX::tags->nameTag.size(),
			RenX::tags->nameTag.data()));

	RenX_LoggingPlugin::otherCrateFmt = this->config.get("OtherCrateFormat"_jrs,
		Jupiter::StringS::Format(IRCBOLD "%.*s" IRCCOLOR IRCBOLD " picked up a " IRCCOLOR "13%.*s" IRCCOLOR " crate.", RenX::tags->nameTag.size(),
			RenX::tags->nameTag.data(), RenX::tags->objectTag.size(),
			RenX::tags->objectTag.data()));

	RenX_LoggingPlugin::stealFmt = this->config.get("StealFormat"_jrs,
		Jupiter::StringS::Format(IRCBOLD "%.*s" IRCCOLOR IRCBOLD " stole " IRCBOLD "%.*s" IRCBOLD "'s " IRCBOLD "%.*s" IRCBOLD "!", RenX::tags->nameTag.size(),
			RenX::tags->nameTag.data(), RenX::tags->victimNameTag.size(),
			RenX::tags->victimNameTag.data(), RenX::tags->objectTag.size(),
			RenX::tags->objectTag.data()));

	RenX_LoggingPlugin::stealNoOwnerFmt = this->config.get("StealNoOwnerFormat"_jrs,
		Jupiter::StringS::Format(IRCBOLD "%.*s" IRCCOLOR IRCBOLD " stole a " IRCBOLD IRCCOLOR "12%.*s" IRCBOLD "!", RenX::tags->nameTag.size(),
			RenX::tags->nameTag.data(), RenX::tags->objectTag.size(),
			RenX::tags->objectTag.data()));

	RenX_LoggingPlugin::donateFmt = this->config.get("DonateFormat"_jrs,
		Jupiter::StringS::Format(IRCBOLD "%.*s" IRCCOLOR IRCBOLD " donated " IRCCOLOR "09%.*s credits" IRCCOLOR " to " IRCBOLD "%.*s" IRCBOLD ".", RenX::tags->nameTag.size(),
			RenX::tags->nameTag.data(), RenX::tags->objectTag.size(),
			RenX::tags->objectTag.data(), RenX::tags->victimNameTag.size(),
			RenX::tags->victimNameTag.data()));

	RenX_LoggingPlugin::gameOverFmt = this->config.get("GameOverFormat"_jrs,
		Jupiter::StringS::Format(IRCCOLOR "03[Game]" IRCCOLOR "%.*s The " IRCBOLD "%.*s" IRCBOLD " won by " IRCBOLD "%.*s" IRCBOLD, RenX::tags->teamColorTag.size(),
			RenX::tags->teamColorTag.data(), RenX::tags->teamLongTag.size(),
			RenX::tags->teamLongTag.data(), RenX::tags->messageTag.size(),
			RenX::tags->messageTag.data()));

	RenX_LoggingPlugin::gameOverTieFmt = this->config.get("GameOverTieNoWinFormat"_jrs,
		Jupiter::StringS::Format(IRCCOLOR "03[Game]" IRCCOLOR "10 The battle ended in a " IRCBOLD "%.*s" IRCBOLD " - Victory handed to " IRCBOLD IRCCOLOR "%.*s%.*s" IRCBOLD, RenX::tags->messageTag.size(),
			RenX::tags->messageTag.data(), RenX::tags->teamColorTag.size(),
			RenX::tags->teamColorTag.data(), RenX::tags->teamLongTag.size(),
			RenX::tags->teamLongTag.data()));

	RenX_LoggingPlugin::gameOverTieNoWinFmt = this->config.get("GameOverTieFormat"_jrs,
		Jupiter::StringS::Format(IRCCOLOR "03[Game]" IRCCOLOR "10 The battle ended in a " IRCBOLD "%.*s" IRCBOLD, RenX::tags->messageTag.size(),
			RenX::tags->messageTag.data()));

	RenX_LoggingPlugin::gameOverScoreFmt = this->config.get("GameOverScoreFormat"_jrs,
		Jupiter::StringS::Format(IRCCOLOR "03[Game]" IRCCOLOR "%.*s %.*s" IRCCOLOR ": %.*s | " IRCCOLOR "%.*s%.*s" IRCCOLOR ": %.*s", RenX::tags->teamColorTag.size(),
			RenX::tags->teamColorTag.data(), RenX::tags->teamLongTag.size(),
			RenX::tags->teamLongTag.data(), RenX::tags->winScoreTag.size(),
			RenX::tags->winScoreTag.data(), RenX::tags->victimTeamColorTag.size(),
			RenX::tags->victimTeamColorTag.data(), RenX::tags->victimTeamLongTag.size(),
			RenX::tags->victimTeamLongTag.data(), RenX::tags->loseScoreTag.size(),
			RenX::tags->loseScoreTag.data()));

	RenX_LoggingPlugin::gameFmt = this->config.get("GameFormat"_jrs,
		Jupiter::StringS::Format(IRCCOLOR "03[Game]" IRCCOLOR " %.*s", RenX::tags->messageTag.size(),
			RenX::tags->messageTag.data()));

	RenX_LoggingPlugin::executeFmt = this->config.get("ExecuteFormat"_jrs,
		Jupiter::StringS::Format(IRCCOLOR "07%.*s executed: %.*s", RenX::tags->nameTag.size(),
			RenX::tags->nameTag.data(), RenX::tags->messageTag.size(),
			RenX::tags->messageTag.data()));

	RenX_LoggingPlugin::devBotExecuteFmt = this->config.get("DevBotExecuteFormat"_jrs, ""_jss);

	RenX_LoggingPlugin::subscribeFmt = this->config.get("SubscribeFormat"_jrs,
		Jupiter::StringS::Format(IRCCOLOR "03%.*s subscribed to the RCON data stream.", RenX::tags->nameTag.size(),
			RenX::tags->nameTag.data()));

	RenX_LoggingPlugin::rconFmt = this->config.get("RCONFormat"_jrs,
		Jupiter::StringS::Format(IRCCOLOR "05[RCON]" IRCCOLOR " %.*s", RenX::tags->messageTag.size(),
			RenX::tags->messageTag.data()));

	RenX_LoggingPlugin::adminLoginFmt = this->config.get("AdminLoginFormat"_jrs,
		Jupiter::StringS::Format(IRCCOLOR "07[Admin] " IRCBOLD "%.*s" IRCBOLD IRCCOLOR " logged in with " IRCCOLOR "07" IRCBOLD "%.*s" IRCBOLD IRCNORMAL " privledges.", RenX::tags->nameTag.size(),
			RenX::tags->nameTag.data(), RenX::tags->adminTag.size(),
			RenX::tags->adminTag.data()));

	RenX_LoggingPlugin::adminGrantFmt = this->config.get("AdminGrantFormat"_jrs,
		Jupiter::StringS::Format(IRCCOLOR "07[Admin] " IRCBOLD "%.*s" IRCBOLD IRCCOLOR " was granted " IRCCOLOR "07" IRCBOLD "%.*s" IRCBOLD IRCNORMAL " privledges.", RenX::tags->nameTag.size(),
			RenX::tags->nameTag.data(), RenX::tags->adminTag.size(),
			RenX::tags->adminTag.data()));

	RenX_LoggingPlugin::adminLogoutFmt = this->config.get("AdminLogoutFormat"_jrs,
		Jupiter::StringS::Format(IRCCOLOR "07[Admin] " IRCBOLD "%.*s" IRCBOLD IRCCOLOR " logged out of their " IRCCOLOR "07" IRCBOLD "%.*s" IRCBOLD IRCNORMAL " privledges.", RenX::tags->nameTag.size(),
			RenX::tags->nameTag.data(), RenX::tags->adminTag.size(),
			RenX::tags->adminTag.data()));

	RenX_LoggingPlugin::adminFmt = this->config.get("AdminFormat"_jrs,
		Jupiter::StringS::Format(IRCCOLOR "07[Admin]" IRCCOLOR " %.*s", RenX::tags->messageTag.size(),
			RenX::tags->messageTag.data()));

	RenX_LoggingPlugin::voteAddBotsFmt = this->config.get("VoteAddBotsFormat"_jrs,
		Jupiter::StringS::Format(IRCCOLOR "[Vote] " IRCBOLD "%.*s" IRCNORMAL " has called for adding " IRCCOLOR "12%.*s" IRCCOLOR " bots to %.*s, with skill level " IRCCOLOR "07%.*s" IRCCOLOR ".", RenX::tags->nameTag.size(),
			RenX::tags->nameTag.data(), RenX::tags->objectTag.size(),
			RenX::tags->objectTag.data(), RenX::tags->victimTeamShortTag.size(),
			RenX::tags->victimTeamShortTag.data(), RenX::tags->weaponTag.size(),
			RenX::tags->weaponTag.data()));
	
	RenX_LoggingPlugin::voteChangeMapFmt = this->config.get("VoteChangeMapFormat"_jrs,
		Jupiter::StringS::Format(IRCCOLOR "[Vote] " IRCBOLD "%.*s" IRCNORMAL " has called for a Map Change.", RenX::tags->nameTag.size(),
			RenX::tags->nameTag.data()));
	
	RenX_LoggingPlugin::voteKickFmt = this->config.get("VoteKickFormat"_jrs,
		Jupiter::StringS::Format(IRCCOLOR "[Vote] " IRCBOLD "%.*s" IRCNORMAL " has called for a kick against %.*s" IRCNORMAL ".", RenX::tags->nameTag.size(),
			RenX::tags->nameTag.data(), RenX::tags->victimNameTag.size(),
			RenX::tags->victimNameTag.data()));
	
	RenX_LoggingPlugin::voteMineBanFmt = this->config.get("VoteMineBanFormat"_jrs,
		Jupiter::StringS::Format(IRCCOLOR "%.*s[Vote] " IRCBOLD "%.*s" IRCBOLD " has called for a Mine Ban against %.*s" IRCNORMAL ".", RenX::tags->victimTeamColorTag.size(),
			RenX::tags->victimTeamColorTag.data(), RenX::tags->nameTag.size(),
			RenX::tags->nameTag.data(), RenX::tags->nameTag.size(),
			RenX::tags->nameTag.data()));
	
	RenX_LoggingPlugin::voteRemoveBotsFmt = this->config.get("VoteRemoveBotsFormat"_jrs,
		Jupiter::StringS::Format(IRCCOLOR "[Vote] " IRCBOLD "%.*s" IRCNORMAL " has called a vote to remove " IRCCOLOR "12%.*s" IRCCOLOR " bots from " IRCCOLOR "%.*s%.*s" IRCNORMAL ".", RenX::tags->nameTag.size(),
			RenX::tags->nameTag.data(), RenX::tags->objectTag.size(),
			RenX::tags->objectTag.data(), RenX::tags->victimTeamColorTag.size(),
			RenX::tags->victimTeamColorTag.data(), RenX::tags->victimTeamShortTag.size(),
			RenX::tags->victimTeamShortTag.data()));
	
	RenX_LoggingPlugin::voteRestartMapFmt = this->config.get("VoteRestartMapFormat"_jrs,
		Jupiter::StringS::Format(IRCCOLOR "[Vote] " IRCBOLD "%.*s" IRCNORMAL " has called for a Map Restart.", RenX::tags->nameTag.size(),
			RenX::tags->nameTag.data()));
	
	RenX_LoggingPlugin::voteSurrenderFmt = this->config.get("VoteSurrenderFormat"_jrs,
		Jupiter::StringS::Format(IRCCOLOR "%.*s[Vote] " IRCBOLD "%.*s" IRCBOLD " has called for a Surrender.", RenX::tags->victimTeamColorTag.size(),
			RenX::tags->victimTeamColorTag.data(), RenX::tags->nameTag.size(),
			RenX::tags->nameTag.data()));
	
	RenX_LoggingPlugin::voteSurveyFmt = this->config.get("VoteSurveyFormat"_jrs,
		Jupiter::StringS::Format(IRCCOLOR "%.*s[Vote] " IRCBOLD "%.*s" IRCBOLD IRCCOLOR "%.*s has started a Survey: " IRCCOLOR "12%.*s", RenX::tags->victimTeamColorTag.size(),
			RenX::tags->victimTeamColorTag.data(), RenX::tags->nameTag.size(),
			RenX::tags->nameTag.data(), RenX::tags->victimTeamColorTag.size(),
			RenX::tags->victimTeamColorTag.data(), RenX::tags->messageTag.size(),
			RenX::tags->messageTag.data()));

	RenX_LoggingPlugin::voteOtherFmt = this->config.get("VoteOtherFormat"_jrs,
		Jupiter::StringS::Format(IRCCOLOR "%.*s[Vote] " IRCBOLD "%.*s" IRCBOLD IRCCOLOR "%.*s has called a \"%.*s\" vote.", RenX::tags->victimTeamColorTag.size(),
			RenX::tags->victimTeamColorTag.data(), RenX::tags->nameTag.size(),
			RenX::tags->nameTag.data(), RenX::tags->victimTeamColorTag.size(),
			RenX::tags->victimTeamColorTag.data(), RenX::tags->objectTag.size(),
			RenX::tags->objectTag.data()));

	RenX_LoggingPlugin::voteOverSuccessFmt = this->config.get("VoteOverSuccessFormat"_jrs,
		Jupiter::StringS::Format(IRCCOLOR "%.*s[Vote] A vote for \"%.*s\" " IRCBOLD IRCCOLOR "09passed" IRCBOLD IRCCOLOR "%.*s (Votes Yes: %.*s | Votes No: %.*s).", RenX::tags->victimTeamColorTag.size(),
			RenX::tags->victimTeamColorTag.data(), RenX::tags->objectTag.size(),
			RenX::tags->objectTag.data(), RenX::tags->victimTeamColorTag.size(),
			RenX::tags->victimTeamColorTag.data(), RenX::tags->winScoreTag.size(),
			RenX::tags->winScoreTag.data(), RenX::tags->loseScoreTag.size(),
			RenX::tags->loseScoreTag.data()));

	RenX_LoggingPlugin::voteOverFailFmt = this->config.get("VoteOverFailFormat"_jrs,
		Jupiter::StringS::Format(IRCCOLOR "%.*s[Vote] A vote for \"%.*s\" " IRCBOLD IRCCOLOR "04failed" IRCBOLD IRCCOLOR "%.*s (Votes Yes: %.*s | Votes No: %.*s).", RenX::tags->victimTeamColorTag.size(),
			RenX::tags->victimTeamColorTag.data(), RenX::tags->objectTag.size(),
			RenX::tags->objectTag.data(), RenX::tags->victimTeamColorTag.size(),
			RenX::tags->victimTeamColorTag.data(), RenX::tags->winScoreTag.size(),
			RenX::tags->winScoreTag.data(), RenX::tags->loseScoreTag.size(),
			RenX::tags->loseScoreTag.data()));

	RenX_LoggingPlugin::voteCancelFmt = this->config.get("VoteCancelFormat"_jrs,
		Jupiter::StringS::Format(IRCCOLOR "%.*s[Vote] A vote for \"%.*s\" was " IRCBOLD IRCCOLOR "07cancelled" IRCCOLOR IRCBOLD ".", RenX::tags->victimTeamColorTag.size(),
			RenX::tags->victimTeamColorTag.data(), RenX::tags->objectTag.size(),
			RenX::tags->objectTag.data()));

	RenX_LoggingPlugin::voteFmt = this->config.get("VoteFormat"_jrs,
		Jupiter::StringS::Format(IRCCOLOR "06[Vote]" IRCCOLOR " %.*s", RenX::tags->messageTag.size(),
			RenX::tags->messageTag.data()));

	RenX_LoggingPlugin::mapChangeFmt = this->config.get("MapChangeFormat"_jrs,
		Jupiter::StringS::Format(IRCCOLOR "03Loading %.*s...", RenX::tags->messageTag.size(),
			RenX::tags->messageTag.data()));

	RenX_LoggingPlugin::mapLoadFmt = this->config.get("MapLoadFormat"_jrs,
		Jupiter::StringS::Format(IRCCOLOR "03%.*s loaded.", RenX::tags->messageTag.size(), RenX::tags->messageTag.data()));

	RenX_LoggingPlugin::mapStartFmt = this->config.get("MapStartFormat"_jrs,
		Jupiter::StringS::Format(IRCCOLOR "03%.*s started.", RenX::tags->messageTag.size(),
			RenX::tags->messageTag.data()));

	RenX_LoggingPlugin::mapFmt = this->config.get("MapFormat"_jrs,
		Jupiter::StringS::Format(IRCCOLOR "06[Map]" IRCCOLOR " %.*s", RenX::tags->messageTag.size(),
			RenX::tags->messageTag.data()));

	RenX_LoggingPlugin::demoRecordFmt = this->config.get("DemoRecordFormat"_jrs,
		Jupiter::StringS::Format("%.*s has started a demo recording.", RenX::tags->nameTag.size(),
			RenX::tags->nameTag.data()));

	RenX_LoggingPlugin::rconDemoRecordFmt = this->config.get("RCONDemoRecordFormat"_jrs,
		IRCCOLOR "07A demo recording has started."_jrs);

	RenX_LoggingPlugin::demoRecordStopFmt = this->config.get("DemoRecordStopFormat"_jrs,
		IRCCOLOR "07The demo recording has stopped."_jrs);

	RenX_LoggingPlugin::demoFmt = this->config.get("DemoFormat"_jrs,
		Jupiter::StringS::Format(IRCCOLOR "06[Demo]" IRCCOLOR " %.*s", RenX::tags->messageTag.size(),
			RenX::tags->messageTag.data()));

	RenX_LoggingPlugin::logFmt = this->config.get("LogFormat"_jrs,
		Jupiter::StringS::Format(IRCCOLOR "07[Log]" IRCCOLOR " %.*s", RenX::tags->messageTag.size(),
			RenX::tags->messageTag.data()));

	RenX_LoggingPlugin::commandFmt = this->config.get("CommandFormat"_jrs,
		Jupiter::StringS::Format("")); // Disabled by default.

	RenX_LoggingPlugin::errorFmt = this->config.get("ErrorFormat"_jrs,
		Jupiter::StringS::Format(IRCCOLOR "04[Error]" IRCCOLOR " %.*s", RenX::tags->messageTag.size(),
			RenX::tags->messageTag.data()));

	RenX_LoggingPlugin::versionFmt = this->config.get("VersionFormat"_jrs,
		Jupiter::StringS::Format(IRCCOLOR "03Renegade X RCON connection established; using RCON verison " IRCBOLD "%.*s" IRCBOLD " for game version " IRCBOLD "%.*s" IRCBOLD, RenX::tags->rconVersionTag.size(),
			RenX::tags->rconVersionTag.data(), RenX::tags->gameVersionTag.size(),
			RenX::tags->gameVersionTag.data()));

	RenX_LoggingPlugin::authorizedFmt = this->config.get("AuthorizedFormat"_jrs,
		Jupiter::StringS::Format(IRCCOLOR "03RCON authorization completed."));

	RenX_LoggingPlugin::otherFmt = this->config.get("OtherFormat"_jrs,
		Jupiter::StringS::Format(IRCCOLOR "06[Other]" IRCCOLOR " %.*s", RenX::tags->messageTag.size(),
			RenX::tags->messageTag.data()));

	/** Sanitize tags */
	RenX::sanitizeTags(playerRDNSFmt);
	RenX::sanitizeTags(playerIdentifyFmt);
	RenX::sanitizeTags(joinPublicFmt);
	RenX::sanitizeTags(joinAdminFmt);
	RenX::sanitizeTags(joinNoSteamAdminFmt);
	RenX::sanitizeTags(partFmt);
	RenX::sanitizeTags(kickFmt);
	RenX::sanitizeTags(nameChangeFmt);
	RenX::sanitizeTags(teamChangeFmt);
	RenX::sanitizeTags(speedHackFmt);
	RenX::sanitizeTags(playerFmt);
	RenX::sanitizeTags(chatFmt);
	RenX::sanitizeTags(teamChatFmt);
	RenX::sanitizeTags(radioChatFmt);
	RenX::sanitizeTags(otherChatFmt);
	RenX::sanitizeTags(deployFmt);
	RenX::sanitizeTags(mineDeployFmt);
	RenX::sanitizeTags(overMineFmt);
	RenX::sanitizeTags(disarmFmt);
	RenX::sanitizeTags(mineDisarmFmt);
	RenX::sanitizeTags(disarmNoOwnerFmt);
	RenX::sanitizeTags(mineDisarmNoOwnerFmt);
	RenX::sanitizeTags(explodeFmt);
	RenX::sanitizeTags(explodeNoOwnerFmt);
	RenX::sanitizeTags(suicideFmt);
	RenX::sanitizeTags(dieFmt);
	RenX::sanitizeTags(dieFmt2);
	RenX::sanitizeTags(killFmt);
	RenX::sanitizeTags(killFmt2);
	RenX::sanitizeTags(destroyBuildingFmt);
	RenX::sanitizeTags(destroyBuildingFmt2);
	RenX::sanitizeTags(destroyDefenceFmt);
	RenX::sanitizeTags(destroyDefenceFmt2);
	RenX::sanitizeTags(destroyVehicleFmt);
	RenX::sanitizeTags(destroyVehicleFmt2);
	RenX::sanitizeTags(captureFmt);
	RenX::sanitizeTags(neutralizeFmt);
	RenX::sanitizeTags(characterPurchaseFmt);
	RenX::sanitizeTags(itemPurchaseFmt);
	RenX::sanitizeTags(weaponPurchaseFmt);
	RenX::sanitizeTags(refillPurchaseFmt);
	RenX::sanitizeTags(vehiclePurchaseFmt);
	RenX::sanitizeTags(vehicleSpawnFmt);
	RenX::sanitizeTags(spawnFmt);
	RenX::sanitizeTags(botJoinFmt);
	RenX::sanitizeTags(vehicleCrateFmt);
	RenX::sanitizeTags(TSVehicleCrateFmt);
	RenX::sanitizeTags(RAVehicleCrateFmt);
	RenX::sanitizeTags(deathCrateFmt);
	RenX::sanitizeTags(moneyCrateFmt);
	RenX::sanitizeTags(characterCrateFmt);
	RenX::sanitizeTags(spyCrateFmt);
	RenX::sanitizeTags(refillCrateFmt);
	RenX::sanitizeTags(timeBombCrateFmt);
	RenX::sanitizeTags(speedCrateFmt);
	RenX::sanitizeTags(nukeCrateFmt);
	RenX::sanitizeTags(abductionCrateFmt);
	RenX::sanitizeTags(unspecifiedCrateFmt);
	RenX::sanitizeTags(otherCrateFmt);
	RenX::sanitizeTags(stealFmt);
	RenX::sanitizeTags(stealNoOwnerFmt);
	RenX::sanitizeTags(donateFmt);
	RenX::sanitizeTags(gameOverFmt);
	RenX::sanitizeTags(gameOverTieFmt);
	RenX::sanitizeTags(gameOverTieNoWinFmt);
	RenX::sanitizeTags(gameOverScoreFmt);
	RenX::sanitizeTags(gameFmt);
	RenX::sanitizeTags(executeFmt);
	RenX::sanitizeTags(playerExecuteFmt);
	RenX::sanitizeTags(playerCommandSuccessFmt);
	RenX::sanitizeTags(playerCommandFailFmt);
	RenX::sanitizeTags(devBotExecuteFmt);
	RenX::sanitizeTags(hostChatFmt);
	RenX::sanitizeTags(hostPageFmt);
	RenX::sanitizeTags(adminMsgFmt);
	RenX::sanitizeTags(warnMsgFmt);
	RenX::sanitizeTags(pAdminMsgFmt);
	RenX::sanitizeTags(pWarnMsgFmt);
	RenX::sanitizeTags(subscribeFmt);
	RenX::sanitizeTags(rconFmt);
	RenX::sanitizeTags(adminLoginFmt);
	RenX::sanitizeTags(adminGrantFmt);
	RenX::sanitizeTags(adminLogoutFmt);
	RenX::sanitizeTags(adminFmt);
	RenX::sanitizeTags(voteAddBotsFmt);
	RenX::sanitizeTags(voteChangeMapFmt);
	RenX::sanitizeTags(voteKickFmt);
	RenX::sanitizeTags(voteMineBanFmt);
	RenX::sanitizeTags(voteRemoveBotsFmt);
	RenX::sanitizeTags(voteRestartMapFmt);
	RenX::sanitizeTags(voteSurrenderFmt);
	RenX::sanitizeTags(voteSurveyFmt);
	RenX::sanitizeTags(voteOtherFmt);
	RenX::sanitizeTags(voteOverSuccessFmt);
	RenX::sanitizeTags(voteOverFailFmt);
	RenX::sanitizeTags(voteCancelFmt);
	RenX::sanitizeTags(voteFmt);
	RenX::sanitizeTags(mapChangeFmt);
	RenX::sanitizeTags(mapLoadFmt);
	RenX::sanitizeTags(mapStartFmt);
	RenX::sanitizeTags(mapFmt);
	RenX::sanitizeTags(demoRecordFmt);
	RenX::sanitizeTags(rconDemoRecordFmt);
	RenX::sanitizeTags(demoRecordStopFmt);
	RenX::sanitizeTags(demoFmt);
	RenX::sanitizeTags(logFmt);
	RenX::sanitizeTags(commandFmt);
	RenX::sanitizeTags(errorFmt);
	RenX::sanitizeTags(versionFmt);
	RenX::sanitizeTags(authorizedFmt);
	RenX::sanitizeTags(otherFmt);

	return true;
}

typedef void(RenX::Server::*logFuncType)(const Jupiter::ReadableString &msg) const;

void RenX_LoggingPlugin::RenX_OnPlayerRDNS(RenX::Server &server, const RenX::PlayerInfo &player)
{
	logFuncType func;
	if (RenX_LoggingPlugin::playerRDNSPublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->playerRDNSFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server, &player);
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnPlayerIdentify(RenX::Server &server, const RenX::PlayerInfo &player)
{
	logFuncType func;
	if (RenX_LoggingPlugin::playerIdentifyPublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->playerIdentifyFmt;
	if (!msg.empty() && server.isMatchPending() == false)
	{
		RenX::processTags(msg, &server, &player);
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnJoin(RenX::Server &server, const RenX::PlayerInfo &player)
{
	Jupiter::String msg;
	if (RenX_LoggingPlugin::joinPublic)
	{
		msg = this->joinPublicFmt;
		if (!msg.empty())
		{
			RenX::processTags(msg, &server, &player);
			server.sendPubChan(msg);
		}
	}
	if (player.steamid == 0)
		msg = this->joinNoSteamAdminFmt;
	else
		msg = this->joinAdminFmt;

	if (!msg.empty() && server.isMatchPending() == false)
	{
		RenX::processTags(msg, &server, &player);
		server.sendAdmChan(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnPart(RenX::Server &server, const RenX::PlayerInfo &player)
{
	logFuncType func;
	if (RenX_LoggingPlugin::partPublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->partFmt;
	if (!msg.empty() && (server.isTravelling() == false || server.isSeamless()))
	{
		RenX::processTags(msg, &server, &player);
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnKick(RenX::Server &server, const RenX::PlayerInfo &player, const Jupiter::ReadableString &reason)
{
	logFuncType func;
	if (RenX_LoggingPlugin::kickPublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->kickFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server, &player);
		msg.replace(RenX::tags->INTERNAL_MESSAGE_TAG, reason);
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnNameChange(RenX::Server &server, const RenX::PlayerInfo &player, const Jupiter::ReadableString &newPlayerName)
{
	logFuncType func;
	if (RenX_LoggingPlugin::nameChangePublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->nameChangeFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server, &player);
		msg.replace(RenX::tags->INTERNAL_NEW_NAME_TAG, newPlayerName);
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnTeamChange(RenX::Server &server, const RenX::PlayerInfo &player, const RenX::TeamType &oldTeam)
{
	logFuncType func;
	if (RenX_LoggingPlugin::teamChangePublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->teamChangeFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server, &player);
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnSpeedHack(RenX::Server &server, const RenX::PlayerInfo &player)
{
	logFuncType func;
	if (RenX_LoggingPlugin::speedHackPublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->speedHackFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server, &player);
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnExecute(RenX::Server &server, const RenX::PlayerInfo &player, const Jupiter::ReadableString &command)
{
	logFuncType func;
	if (RenX_LoggingPlugin::executePublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->playerExecuteFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server, &player);
		msg.replace(RenX::tags->INTERNAL_MESSAGE_TAG, command);
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnPlayerCommand(RenX::Server &server, const RenX::PlayerInfo &player, const Jupiter::ReadableString &message, RenX::GameCommand *command)
{
	logFuncType func;
	if (RenX_LoggingPlugin::playerCommandPublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = command != nullptr
		? this->playerCommandSuccessFmt
		: this->playerCommandFailFmt;

	if (!msg.empty())
	{
		RenX::processTags(msg, &server, &player);
		msg.replace(RenX::tags->INTERNAL_MESSAGE_TAG, message);
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnPlayer(RenX::Server &server, const Jupiter::ReadableString &raw)
{
	logFuncType func;
	if (RenX_LoggingPlugin::playerPublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->playerFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server);
		msg.replace(RenX::tags->INTERNAL_MESSAGE_TAG, raw);
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnChat(RenX::Server &server, const RenX::PlayerInfo &player, const Jupiter::ReadableString &message)
{
	logFuncType func;
	if (RenX_LoggingPlugin::chatPublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;
	
	Jupiter::String msg = this->chatFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server, &player);
		msg.replace(RenX::tags->INTERNAL_MESSAGE_TAG, message);
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnTeamChat(RenX::Server &server, const RenX::PlayerInfo &player, const Jupiter::ReadableString &message)
{
	logFuncType func;
	if (RenX_LoggingPlugin::teamChatPublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;
	
	Jupiter::String msg = this->teamChatFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server, &player);
		msg.replace(RenX::tags->INTERNAL_MESSAGE_TAG, message);
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnRadioChat(RenX::Server &server, const RenX::PlayerInfo &player, const Jupiter::ReadableString &message)
{
	logFuncType func;
	if (RenX_LoggingPlugin::radioChatPublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->radioChatFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server, &player);
		msg.replace(RenX::tags->INTERNAL_MESSAGE_TAG, message);
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnHostChat(RenX::Server &server, const Jupiter::ReadableString &message)
{
	logFuncType func;
	if (RenX_LoggingPlugin::hostChatPublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->hostChatFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server);
		msg.replace(RenX::tags->INTERNAL_MESSAGE_TAG, message);
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnHostPage(RenX::Server &server, const RenX::PlayerInfo &player, const Jupiter::ReadableString &message)
{
	logFuncType func;
	if (RenX_LoggingPlugin::hostPagePublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->hostPageFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server, &player);
		msg.replace(RenX::tags->INTERNAL_MESSAGE_TAG, message);
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnAdminMessage(RenX::Server &server, const RenX::PlayerInfo &player, const Jupiter::ReadableString &message)
{
	logFuncType func;
	if (RenX_LoggingPlugin::adminMessagePublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->adminMsgFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server, &player);
		msg.replace(RenX::tags->INTERNAL_MESSAGE_TAG, message);
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnWarnMessage(RenX::Server &server, const RenX::PlayerInfo &player, const Jupiter::ReadableString &message)
{
	logFuncType func;
	if (RenX_LoggingPlugin::adminMessagePublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->warnMsgFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server, &player);
		msg.replace(RenX::tags->INTERNAL_MESSAGE_TAG, message);
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnAdminPMessage(RenX::Server &server, const RenX::PlayerInfo &player, const RenX::PlayerInfo &target, const Jupiter::ReadableString &message)
{
	logFuncType func;
	if (RenX_LoggingPlugin::adminPMessagePublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->pAdminMsgFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server, &player, &target);
		msg.replace(RenX::tags->INTERNAL_MESSAGE_TAG, message);
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnWarnPMessage(RenX::Server &server, const RenX::PlayerInfo &player, const RenX::PlayerInfo &target, const Jupiter::ReadableString &message)
{
	logFuncType func;
	if (RenX_LoggingPlugin::adminPMessagePublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->pWarnMsgFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server, &player, &target);
		msg.replace(RenX::tags->INTERNAL_MESSAGE_TAG, message);
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnHostAdminMessage(RenX::Server &server, const Jupiter::ReadableString &message)
{
	logFuncType func;
	if (RenX_LoggingPlugin::adminMessagePublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->adminMsgFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server);
		msg.replace(RenX::tags->INTERNAL_NAME_TAG, "Host"_jrs);
		msg.replace(RenX::tags->INTERNAL_RAW_NAME_TAG, "Host"_jrs);
		msg.replace(RenX::tags->INTERNAL_MESSAGE_TAG, message);
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnHostAdminPMessage(RenX::Server &server, const RenX::PlayerInfo &player, const Jupiter::ReadableString &message)
{
	logFuncType func;
	if (RenX_LoggingPlugin::adminPMessagePublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->pAdminMsgFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server, nullptr, &player);
		msg.replace(RenX::tags->INTERNAL_NAME_TAG, "Host"_jrs);
		msg.replace(RenX::tags->INTERNAL_RAW_NAME_TAG, "Host"_jrs);
		msg.replace(RenX::tags->INTERNAL_MESSAGE_TAG, message);
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnHostWarnMessage(RenX::Server &server, const Jupiter::ReadableString &message)
{
	logFuncType func;
	if (RenX_LoggingPlugin::adminMessagePublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->warnMsgFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server);
		msg.replace(RenX::tags->INTERNAL_NAME_TAG, "Host"_jrs);
		msg.replace(RenX::tags->INTERNAL_RAW_NAME_TAG, "Host"_jrs);
		msg.replace(RenX::tags->INTERNAL_MESSAGE_TAG, message);
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnHostWarnPMessage(RenX::Server &server, const RenX::PlayerInfo &player, const Jupiter::ReadableString &message)
{
	logFuncType func;
	if (RenX_LoggingPlugin::adminPMessagePublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->pWarnMsgFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server, nullptr, &player);
		msg.replace(RenX::tags->INTERNAL_NAME_TAG, "Host"_jrs);
		msg.replace(RenX::tags->INTERNAL_RAW_NAME_TAG, "Host"_jrs);
		msg.replace(RenX::tags->INTERNAL_MESSAGE_TAG, message);
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnOtherChat(RenX::Server &server, const Jupiter::ReadableString &raw)
{
	logFuncType func;
	if (RenX_LoggingPlugin::otherChatPublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->otherChatFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server);
		msg.replace(RenX::tags->INTERNAL_MESSAGE_TAG, raw);
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnDeploy(RenX::Server &server, const RenX::PlayerInfo &player, const Jupiter::ReadableString &object) {
	logFuncType func;
	Jupiter::String msg;
	if (std::string_view{object}.ends_with("Beacon")) {
		if (RenX_LoggingPlugin::deployPublic)
			func = &RenX::Server::sendLogChan;
		else
			func = &RenX::Server::sendAdmChan;

		msg = this->deployFmt;
	}
	else {
		if (RenX_LoggingPlugin::mineDeployPublic)
			func = &RenX::Server::sendLogChan;
		else
			func = &RenX::Server::sendAdmChan;

		msg = this->mineDeployFmt;
	}
	if (!msg.empty()) {
		RenX::processTags(msg, &server, &player);
		msg.replace(RenX::tags->INTERNAL_OBJECT_TAG, RenX::translateName(object));
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnOverMine(RenX::Server &server, const RenX::PlayerInfo &player, const Jupiter::ReadableString &location)
{
	logFuncType func;
	if (RenX_LoggingPlugin::overMinePublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->overMineFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server, &player);
		msg.replace(RenX::tags->INTERNAL_OBJECT_TAG, RenX::translateName(location));
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnDisarm(RenX::Server &server, const RenX::PlayerInfo &player, const Jupiter::ReadableString &object, const RenX::PlayerInfo &victim) {
	logFuncType func;
	Jupiter::String msg;

	if (std::string_view{object}.ends_with("Beacon")) {
		if (RenX_LoggingPlugin::disarmPublic)
			func = &RenX::Server::sendLogChan;
		else
			func = &RenX::Server::sendAdmChan;

		msg = this->disarmFmt;
	}
	else {
		if (RenX_LoggingPlugin::mineDisarmPublic)
			func = &RenX::Server::sendLogChan;
		else
			func = &RenX::Server::sendAdmChan;

		msg = this->mineDisarmFmt;
	}
	if (!msg.empty()) {
		RenX::processTags(msg, &server, &player, &victim);
		msg.replace(RenX::tags->INTERNAL_OBJECT_TAG, RenX::translateName(object));
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnDisarm(RenX::Server &server, const RenX::PlayerInfo &player, const Jupiter::ReadableString &object) {
	logFuncType func;
	Jupiter::String msg;

	if (std::string_view{object}.ends_with("Beacon")) {
		if (RenX_LoggingPlugin::disarmPublic)
			func = &RenX::Server::sendLogChan;
		else
			func = &RenX::Server::sendAdmChan;

		msg = this->disarmNoOwnerFmt;
	}
	else {
		if (RenX_LoggingPlugin::mineDisarmPublic)
			func = &RenX::Server::sendLogChan;
		else
			func = &RenX::Server::sendAdmChan;

		msg = this->mineDisarmNoOwnerFmt;
	}
	if (!msg.empty()) {
		RenX::processTags(msg, &server, &player);
		msg.replace(RenX::tags->INTERNAL_OBJECT_TAG, RenX::translateName(object));
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnExplode(RenX::Server &server, const RenX::PlayerInfo &player, const Jupiter::ReadableString &object)
{
	logFuncType func;
	if (RenX_LoggingPlugin::explodePublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->explodeFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server, &player);
		msg.replace(RenX::tags->INTERNAL_WEAPON_TAG, RenX::translateName(object));
		msg.replace(RenX::tags->INTERNAL_OBJECT_TAG, RenX::translateName(object));
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnExplode(RenX::Server &server, const Jupiter::ReadableString &object)
{
	logFuncType func;
	if (RenX_LoggingPlugin::explodePublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->explodeNoOwnerFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server);
		msg.replace(RenX::tags->INTERNAL_WEAPON_TAG, RenX::translateName(object));
		msg.replace(RenX::tags->INTERNAL_OBJECT_TAG, RenX::translateName(object));
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnSuicide(RenX::Server &server, const RenX::PlayerInfo &player, const Jupiter::ReadableString &damageType)
{
	logFuncType func;
	if (RenX_LoggingPlugin::suicidePublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;
	
	Jupiter::String msg = this->suicideFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server, &player);
		msg.replace(RenX::tags->INTERNAL_WEAPON_TAG, RenX::translateName(damageType));
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnKill(RenX::Server &server, const RenX::PlayerInfo &player, const RenX::PlayerInfo &victim, const Jupiter::ReadableString &damageType)
{
	logFuncType func;
	if (RenX_LoggingPlugin::killPublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;
	
	Jupiter::String msg = this->killFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server, &player, &victim);
		msg.replace(RenX::tags->INTERNAL_WEAPON_TAG, RenX::translateName(damageType));
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnKill(RenX::Server &server, const Jupiter::ReadableString &killer, const RenX::TeamType &killerTeam, const RenX::PlayerInfo &victim, const Jupiter::ReadableString &damageType)
{
	logFuncType func;
	if (RenX_LoggingPlugin::killPublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->killFmt2;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server, nullptr, &victim);
		msg.replace(RenX::tags->INTERNAL_NAME_TAG, RenX::translateName(killer));
		msg.replace(RenX::tags->INTERNAL_TEAM_COLOR_TAG, RenX::getTeamColor(killerTeam));
		msg.replace(RenX::tags->INTERNAL_TEAM_SHORT_TAG, RenX::getTeamName(killerTeam));
		msg.replace(RenX::tags->INTERNAL_TEAM_LONG_TAG, RenX::getFullTeamName(killerTeam));
		msg.replace(RenX::tags->INTERNAL_WEAPON_TAG, RenX::translateName(damageType));
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnDie(RenX::Server &server, const RenX::PlayerInfo &player, const Jupiter::ReadableString &damageType)
{
	logFuncType func;
	if (RenX_LoggingPlugin::diePublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->dieFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server, &player);
		msg.replace(RenX::tags->INTERNAL_WEAPON_TAG, RenX::translateName(damageType));
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnDie(RenX::Server &server, const Jupiter::ReadableString &object, const RenX::TeamType &objectTeam, const Jupiter::ReadableString &damageType)
{
	logFuncType func;
	if (RenX_LoggingPlugin::diePublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->dieFmt2;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server);
		msg.replace(RenX::tags->INTERNAL_NAME_TAG, RenX::translateName(object));
		msg.replace(RenX::tags->INTERNAL_TEAM_COLOR_TAG, RenX::getTeamColor(objectTeam));
		msg.replace(RenX::tags->INTERNAL_TEAM_SHORT_TAG, RenX::getTeamName(objectTeam));
		msg.replace(RenX::tags->INTERNAL_TEAM_LONG_TAG, RenX::getFullTeamName(objectTeam));
		msg.replace(RenX::tags->INTERNAL_WEAPON_TAG, RenX::translateName(damageType));
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnDestroy(RenX::Server &server, const RenX::PlayerInfo &player, const Jupiter::ReadableString &objectName, const RenX::TeamType &objectTeam, const Jupiter::ReadableString &damageType, RenX::ObjectType type)
{
	logFuncType func;
	if (RenX_LoggingPlugin::destroyPublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg;
	switch (type)
	{
	case RenX::ObjectType::Building:
		msg = this->destroyBuildingFmt;
		break;
	case RenX::ObjectType::Defence:
		msg = this->destroyDefenceFmt;
		break;
	default:
		msg = this->destroyVehicleFmt;
		break;
	}
	if (!msg.empty())
	{
		RenX::processTags(msg, &server, &player);
		msg.replace(RenX::tags->INTERNAL_VICTIM_TEAM_COLOR_TAG, RenX::getTeamColor(objectTeam));
		msg.replace(RenX::tags->INTERNAL_VICTIM_TEAM_SHORT_TAG, RenX::getTeamName(objectTeam));
		msg.replace(RenX::tags->INTERNAL_VICTIM_TEAM_LONG_TAG, RenX::getFullTeamName(objectTeam));
		msg.replace(RenX::tags->INTERNAL_OBJECT_TAG, RenX::translateName(objectName));
		msg.replace(RenX::tags->INTERNAL_WEAPON_TAG, RenX::translateName(damageType));
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnCapture(RenX::Server &server, const RenX::PlayerInfo &player, const Jupiter::ReadableString &building, const RenX::TeamType &oldTeam)
{
	logFuncType func;
	if (RenX_LoggingPlugin::capturePublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->captureFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server, &player);
		msg.replace(RenX::tags->INTERNAL_OBJECT_TAG, RenX::translateName(building));
		msg.replace(RenX::tags->INTERNAL_VICTIM_TEAM_COLOR_TAG, RenX::getTeamColor(oldTeam));
		msg.replace(RenX::tags->INTERNAL_VICTIM_TEAM_SHORT_TAG, RenX::getTeamName(oldTeam));
		msg.replace(RenX::tags->INTERNAL_VICTIM_TEAM_LONG_TAG, RenX::getFullTeamName(oldTeam));
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnNeutralize(RenX::Server &server, const RenX::PlayerInfo &player, const Jupiter::ReadableString &building, const RenX::TeamType &oldTeam)
{
	logFuncType func;
	if (RenX_LoggingPlugin::neutralizePublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->neutralizeFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server, &player);
		msg.replace(RenX::tags->INTERNAL_OBJECT_TAG, RenX::translateName(building));
		msg.replace(RenX::tags->INTERNAL_VICTIM_TEAM_COLOR_TAG, RenX::getTeamColor(oldTeam));
		msg.replace(RenX::tags->INTERNAL_VICTIM_TEAM_SHORT_TAG, RenX::getTeamName(oldTeam));
		msg.replace(RenX::tags->INTERNAL_VICTIM_TEAM_LONG_TAG, RenX::getFullTeamName(oldTeam));
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnCharacterPurchase(RenX::Server &server, const RenX::PlayerInfo &player, const Jupiter::ReadableString &character)
{
	logFuncType func;
	if (RenX_LoggingPlugin::characterPurchasePublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->characterPurchaseFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server, &player);
		msg.replace(RenX::tags->INTERNAL_VICTIM_CHARACTER_TAG, RenX::translateName(character));
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnItemPurchase(RenX::Server &server, const RenX::PlayerInfo &player, const Jupiter::ReadableString &item)
{
	logFuncType func;
	if (RenX_LoggingPlugin::itemPurchasePublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->itemPurchaseFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server, &player);
		msg.replace(RenX::tags->INTERNAL_OBJECT_TAG, RenX::translateName(item));
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnWeaponPurchase(RenX::Server &server, const RenX::PlayerInfo &player, const Jupiter::ReadableString &weapon)
{
	logFuncType func;
	if (RenX_LoggingPlugin::weaponPurchasePublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->weaponPurchaseFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server, &player);
		msg.replace(RenX::tags->INTERNAL_WEAPON_TAG, RenX::translateName(weapon));
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnRefillPurchase(RenX::Server &server, const RenX::PlayerInfo &player)
{
	logFuncType func;
	if (RenX_LoggingPlugin::refillPurchasePublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->refillPurchaseFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server, &player);
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnVehiclePurchase(RenX::Server &server, const RenX::PlayerInfo &owner, const Jupiter::ReadableString &vehicle)
{
	logFuncType func;
	if (RenX_LoggingPlugin::vehiclePurchasePublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->vehiclePurchaseFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server, &owner);
		msg.replace(RenX::tags->INTERNAL_VICTIM_VEHICLE_TAG, RenX::translateName(vehicle));
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnVehicleSpawn(RenX::Server &server, const RenX::TeamType &team, const Jupiter::ReadableString &vehicle)
{
	logFuncType func;
	if (RenX_LoggingPlugin::vehicleSpawnPublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->vehicleSpawnFmt;
	if (!msg.empty())
	{
		RenX::TeamType otherTeam = RenX::getEnemy(team);
		RenX::processTags(msg, &server);
		msg.replace(RenX::tags->INTERNAL_TEAM_COLOR_TAG, RenX::getTeamColor(team));
		msg.replace(RenX::tags->INTERNAL_TEAM_SHORT_TAG, RenX::getTeamName(team));
		msg.replace(RenX::tags->INTERNAL_TEAM_LONG_TAG, RenX::getFullTeamName(team));
		msg.replace(RenX::tags->INTERNAL_VICTIM_TEAM_COLOR_TAG, RenX::getTeamColor(otherTeam));
		msg.replace(RenX::tags->INTERNAL_VICTIM_TEAM_SHORT_TAG, RenX::getTeamName(otherTeam));
		msg.replace(RenX::tags->INTERNAL_VICTIM_TEAM_LONG_TAG, RenX::getFullTeamName(otherTeam));
		msg.replace(RenX::tags->INTERNAL_VEHICLE_TAG, RenX::translateName(vehicle));
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnSpawn(RenX::Server &server, const RenX::PlayerInfo &player, const Jupiter::ReadableString &character)
{
	logFuncType func;
	if (RenX_LoggingPlugin::spawnPublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->spawnFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server, &player);
		msg.replace(RenX::tags->INTERNAL_VICTIM_CHARACTER_TAG, RenX::translateName(character));
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnBotJoin(RenX::Server &server, const RenX::PlayerInfo &player)
{
	logFuncType func;
	if (RenX_LoggingPlugin::botJoinPublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->botJoinFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server, &player);
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnVehicleCrate(RenX::Server &server, const RenX::PlayerInfo &player, const Jupiter::ReadableString &vehicle)
{
	logFuncType func;
	if (RenX_LoggingPlugin::vehicleCratePublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->vehicleCrateFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server, &player);
		msg.replace(RenX::tags->INTERNAL_OBJECT_TAG, RenX::translateName(vehicle));
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnTSVehicleCrate(RenX::Server &server, const RenX::PlayerInfo &player, const Jupiter::ReadableString &vehicle)
{
	logFuncType func;
	if (RenX_LoggingPlugin::TSVehicleCratePublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->TSVehicleCrateFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server, &player);
		msg.replace(RenX::tags->INTERNAL_OBJECT_TAG, RenX::translateName(vehicle));
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnRAVehicleCrate(RenX::Server &server, const RenX::PlayerInfo &player, const Jupiter::ReadableString &vehicle)
{
	logFuncType func;
	if (RenX_LoggingPlugin::RAVehicleCratePublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->RAVehicleCrateFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server, &player);
		msg.replace(RenX::tags->INTERNAL_OBJECT_TAG, RenX::translateName(vehicle));
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnDeathCrate(RenX::Server &server, const RenX::PlayerInfo &player)
{
	logFuncType func;
	if (RenX_LoggingPlugin::deathCratePublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->deathCrateFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server, &player);
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnMoneyCrate(RenX::Server &server, const RenX::PlayerInfo &player, int amount)
{
	logFuncType func;
	if (RenX_LoggingPlugin::moneyCratePublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->moneyCrateFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server, &player);
		msg.replace(RenX::tags->INTERNAL_OBJECT_TAG, Jupiter::StringS::Format("%d", amount));
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnCharacterCrate(RenX::Server &server, const RenX::PlayerInfo &player, const Jupiter::ReadableString &character)
{
	logFuncType func;
	if (RenX_LoggingPlugin::characterCratePublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->characterCrateFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server, &player);
		msg.replace(RenX::tags->INTERNAL_VICTIM_CHARACTER_TAG, RenX::translateName(character));
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnSpyCrate(RenX::Server &server, const RenX::PlayerInfo &player, const Jupiter::ReadableString &character)
{
	logFuncType func;
	if (RenX_LoggingPlugin::spyCratePublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->spyCrateFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server, &player);
		msg.replace(RenX::tags->INTERNAL_VICTIM_TEAM_COLOR_TAG, RenX::getTeamColor(RenX::getEnemy(player.team)));
		msg.replace(RenX::tags->INTERNAL_VICTIM_CHARACTER_TAG, RenX::translateName(character));
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnRefillCrate(RenX::Server &server, const RenX::PlayerInfo &player)
{
	logFuncType func;
	if (RenX_LoggingPlugin::refillCratePublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->refillCrateFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server, &player);
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnTimeBombCrate(RenX::Server &server, const RenX::PlayerInfo &player)
{
	logFuncType func;
	if (RenX_LoggingPlugin::timeBombCratePublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->timeBombCrateFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server, &player);
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnSpeedCrate(RenX::Server &server, const RenX::PlayerInfo &player)
{
	logFuncType func;
	if (RenX_LoggingPlugin::speedCratePublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->speedCrateFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server, &player);
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnNukeCrate(RenX::Server &server, const RenX::PlayerInfo &player)
{
	logFuncType func;
	if (RenX_LoggingPlugin::nukeCratePublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->nukeCrateFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server, &player);
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnAbductionCrate(RenX::Server &server, const RenX::PlayerInfo &player)
{
	logFuncType func;
	if (RenX_LoggingPlugin::abductionCratePublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->abductionCrateFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server, &player);
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnUnspecifiedCrate(RenX::Server &server, const RenX::PlayerInfo &player)
{
	logFuncType func;
	if (RenX_LoggingPlugin::unspecifiedCratePublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->unspecifiedCrateFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server, &player);
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnOtherCrate(RenX::Server &server, const RenX::PlayerInfo &player, const Jupiter::ReadableString &type)
{
	logFuncType func;
	if (RenX_LoggingPlugin::otherCratePublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->otherCrateFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server, &player);
		msg.replace(RenX::tags->INTERNAL_OBJECT_TAG, type);
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnSteal(RenX::Server &server, const RenX::PlayerInfo &player, const Jupiter::ReadableString &vehicle)
{
	logFuncType func;
	if (RenX_LoggingPlugin::stealPublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->stealNoOwnerFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server, &player);
		msg.replace(RenX::tags->INTERNAL_OBJECT_TAG, RenX::translateName(vehicle));
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnSteal(RenX::Server &server, const RenX::PlayerInfo &player, const Jupiter::ReadableString &vehicle, const RenX::PlayerInfo &victim)
{
	logFuncType func;
	if (RenX_LoggingPlugin::stealPublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->stealFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server, &player, &victim);
		msg.replace(RenX::tags->INTERNAL_OBJECT_TAG, RenX::translateName(vehicle));
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnDonate(RenX::Server &server, const RenX::PlayerInfo &donor, const RenX::PlayerInfo &player, double amount)
{
	logFuncType func;
	if (RenX_LoggingPlugin::donatePublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->donateFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server, &donor, &player);
		msg.replace(RenX::tags->INTERNAL_OBJECT_TAG, Jupiter::StringS::Format("%.0f", amount));
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnDestroy(RenX::Server &server, const Jupiter::ReadableString &killer, const RenX::TeamType &killerTeam, const Jupiter::ReadableString &objectName, const RenX::TeamType &objectTeam, const Jupiter::ReadableString &damageType, RenX::ObjectType type)
{
	logFuncType func;
	if (RenX_LoggingPlugin::destroyPublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg;
	switch (type)
	{
	case RenX::ObjectType::Building:
		msg = this->destroyBuildingFmt2;
		break;
	case RenX::ObjectType::Defence:
		msg = this->destroyDefenceFmt2;
		break;
	default:
		msg = this->destroyVehicleFmt2;
		break;
	}
	if (!msg.empty())
	{
		RenX::processTags(msg, &server);
		msg.replace(RenX::tags->INTERNAL_NAME_TAG, RenX::translateName(killer));
		msg.replace(RenX::tags->INTERNAL_TEAM_COLOR_TAG, RenX::getTeamColor(killerTeam));
		msg.replace(RenX::tags->INTERNAL_TEAM_SHORT_TAG, RenX::getTeamName(killerTeam));
		msg.replace(RenX::tags->INTERNAL_TEAM_LONG_TAG, RenX::getFullTeamName(killerTeam));
		msg.replace(RenX::tags->INTERNAL_VICTIM_TEAM_COLOR_TAG, RenX::getTeamColor(objectTeam));
		msg.replace(RenX::tags->INTERNAL_VICTIM_TEAM_SHORT_TAG, RenX::getTeamName(objectTeam));
		msg.replace(RenX::tags->INTERNAL_VICTIM_TEAM_LONG_TAG, RenX::getFullTeamName(objectTeam));
		msg.replace(RenX::tags->INTERNAL_OBJECT_TAG, RenX::translateName(objectName));
		msg.replace(RenX::tags->INTERNAL_WEAPON_TAG, RenX::translateName(damageType));
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnGameOver(RenX::Server &server, RenX::WinType winType, const RenX::TeamType &team, int gScore, int nScore)
{
	RenX::TeamType loserTeam = RenX::getEnemy(team);
	int winScore;
	int loseScore;
	switch (team)
	{
	default:
	case RenX::TeamType::GDI:
		winScore = gScore;
		loseScore = nScore;
		break;
	case RenX::TeamType::Nod:
		winScore = nScore;
		loseScore = gScore;
		break;
	}

	logFuncType func;
	if (RenX_LoggingPlugin::gameOverPublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg;
	if (winType == RenX::WinType::Tie)
	{
		if (team == RenX::TeamType::None)
			msg = this->gameOverTieNoWinFmt;
		else
			msg = this->gameOverTieFmt;
	}
	else
		msg = this->gameOverFmt;

	if (!msg.empty() && team != RenX::TeamType::None)
	{
		msg.replace(RenX::tags->INTERNAL_TEAM_COLOR_TAG, RenX::getTeamColor(team));
		msg.replace(RenX::tags->INTERNAL_TEAM_SHORT_TAG, RenX::getTeamName(team));
		msg.replace(RenX::tags->INTERNAL_TEAM_LONG_TAG, RenX::getFullTeamName(team));
		msg.replace(RenX::tags->INTERNAL_WIN_SCORE_TAG, Jupiter::StringS::Format("%d", winScore));
		msg.replace(RenX::tags->INTERNAL_LOSE_SCORE_TAG, Jupiter::StringS::Format("%d", loseScore));
		msg.replace(RenX::tags->INTERNAL_VICTIM_TEAM_COLOR_TAG, RenX::getTeamColor(loserTeam));
		msg.replace(RenX::tags->INTERNAL_VICTIM_TEAM_SHORT_TAG, RenX::getTeamName(loserTeam));
		msg.replace(RenX::tags->INTERNAL_VICTIM_TEAM_LONG_TAG, RenX::getFullTeamName(loserTeam));
		msg.replace(RenX::tags->INTERNAL_MESSAGE_TAG, RenX::translateWinType(winType));
		(server.*func)(msg);
	}

	msg = this->gameOverScoreFmt;
	if (team == RenX::TeamType::None)
	{
		if (!msg.empty())
		{
			msg.replace(RenX::tags->INTERNAL_TEAM_COLOR_TAG, RenX::getTeamColor(RenX::TeamType::GDI));
			msg.replace(RenX::tags->INTERNAL_TEAM_SHORT_TAG, RenX::getTeamName(RenX::TeamType::GDI));
			msg.replace(RenX::tags->INTERNAL_TEAM_LONG_TAG, RenX::getFullTeamName(RenX::TeamType::GDI));
			msg.replace(RenX::tags->INTERNAL_WIN_SCORE_TAG, Jupiter::StringS::Format("%d", winScore));
			msg.replace(RenX::tags->INTERNAL_LOSE_SCORE_TAG, Jupiter::StringS::Format("%d", loseScore));
			msg.replace(RenX::tags->INTERNAL_VICTIM_TEAM_COLOR_TAG, RenX::getTeamColor(RenX::TeamType::Nod));
			msg.replace(RenX::tags->INTERNAL_VICTIM_TEAM_SHORT_TAG, RenX::getTeamName(RenX::TeamType::Nod));
			msg.replace(RenX::tags->INTERNAL_VICTIM_TEAM_LONG_TAG, RenX::getFullTeamName(RenX::TeamType::Nod));
			msg.replace(RenX::tags->INTERNAL_MESSAGE_TAG, RenX::translateWinType(winType));
			(server.*func)(msg);
		}
	}
	else if (!msg.empty())
	{
		msg.replace(RenX::tags->INTERNAL_TEAM_COLOR_TAG, RenX::getTeamColor(team));
		msg.replace(RenX::tags->INTERNAL_TEAM_SHORT_TAG, RenX::getTeamName(team));
		msg.replace(RenX::tags->INTERNAL_TEAM_LONG_TAG, RenX::getFullTeamName(team));
		msg.replace(RenX::tags->INTERNAL_WIN_SCORE_TAG, Jupiter::StringS::Format("%d", winScore));
		msg.replace(RenX::tags->INTERNAL_LOSE_SCORE_TAG, Jupiter::StringS::Format("%d", loseScore));
		msg.replace(RenX::tags->INTERNAL_VICTIM_TEAM_COLOR_TAG, RenX::getTeamColor(loserTeam));
		msg.replace(RenX::tags->INTERNAL_VICTIM_TEAM_SHORT_TAG, RenX::getTeamName(loserTeam));
		msg.replace(RenX::tags->INTERNAL_VICTIM_TEAM_LONG_TAG, RenX::getFullTeamName(loserTeam));
		msg.replace(RenX::tags->INTERNAL_MESSAGE_TAG, RenX::translateWinType(winType));
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnGame(RenX::Server &server, const Jupiter::ReadableString &raw)
{
	logFuncType func;
	if (RenX_LoggingPlugin::gamePublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->gameFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server);
		msg.replace(RenX::tags->INTERNAL_MESSAGE_TAG, raw);
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnExecute(RenX::Server &server, const Jupiter::ReadableString &user, const Jupiter::ReadableString &command) {
	if (RenX_LoggingPlugin::muteOwnExecute == false || server.getUser() != user) {
		logFuncType func;
		if (RenX_LoggingPlugin::executePublic)
			func = &RenX::Server::sendLogChan;
		else
			func = &RenX::Server::sendAdmChan;

		Jupiter::String msg;
		if (user == RenX::DevBotName)
			msg = this->devBotExecuteFmt;
		else
			msg = this->executeFmt;

		if (!msg.empty())
		{
			RenX::processTags(msg, &server);
			msg.replace(RenX::tags->INTERNAL_NAME_TAG, user);
			msg.replace(RenX::tags->INTERNAL_MESSAGE_TAG, command);
			(server.*func)(msg);
		}
	}
}

void RenX_LoggingPlugin::RenX_OnSubscribe(RenX::Server &server, const Jupiter::ReadableString &user)
{
	logFuncType func;
	if (RenX_LoggingPlugin::subscribePublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->subscribeFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server);
		msg.replace(RenX::tags->INTERNAL_NAME_TAG, user);
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnRCON(RenX::Server &server, const Jupiter::ReadableString &raw)
{
	logFuncType func;
	if (RenX_LoggingPlugin::RCONPublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->rconFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server);
		msg.replace(RenX::tags->INTERNAL_MESSAGE_TAG, raw);
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnAdminLogin(RenX::Server &server, const RenX::PlayerInfo &player)
{
	logFuncType func;
	if (RenX_LoggingPlugin::adminLoginPublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->adminLoginFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server, &player);
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnAdminGrant(RenX::Server &server, const RenX::PlayerInfo &player)
{
	logFuncType func;
	if (RenX_LoggingPlugin::adminGrantPublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->adminGrantFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server, &player);
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnAdminLogout(RenX::Server &server, const RenX::PlayerInfo &player)
{
	logFuncType func;
	if (RenX_LoggingPlugin::adminLogoutPublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;
	
	Jupiter::String msg = this->adminLogoutFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server, &player);
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnAdmin(RenX::Server &server, const Jupiter::ReadableString &raw)
{
	logFuncType func;
	if (RenX_LoggingPlugin::adminPublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;
	
	Jupiter::String msg = this->adminFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server);
		msg.replace(RenX::tags->INTERNAL_MESSAGE_TAG, raw);
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnVoteAddBots(RenX::Server &server, const RenX::TeamType &, const RenX::PlayerInfo &player, const RenX::TeamType &victim, int amount, int skill)
{
	logFuncType func;
	if (RenX_LoggingPlugin::voteCallPublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->voteAddBotsFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server, &player);
		msg.replace(RenX::tags->INTERNAL_VICTIM_TEAM_COLOR_TAG, RenX::getTeamColor(victim));
		msg.replace(RenX::tags->INTERNAL_VICTIM_TEAM_SHORT_TAG, RenX::getTeamName(victim));
		msg.replace(RenX::tags->INTERNAL_VICTIM_TEAM_LONG_TAG, RenX::getFullTeamName(victim));
		msg.replace(RenX::tags->INTERNAL_OBJECT_TAG, Jupiter::StringS::Format("%d", amount));
		msg.replace(RenX::tags->INTERNAL_WEAPON_TAG, Jupiter::StringS::Format("%d", skill));
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnVoteChangeMap(RenX::Server &server, const RenX::TeamType &team, const RenX::PlayerInfo &player)
{
	logFuncType func;
	if (RenX_LoggingPlugin::voteCallPublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->voteChangeMapFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server, &player);
		msg.replace(RenX::tags->INTERNAL_VICTIM_TEAM_COLOR_TAG, RenX::getTeamColor(team));
		msg.replace(RenX::tags->INTERNAL_VICTIM_TEAM_SHORT_TAG, RenX::getTeamName(team));
		msg.replace(RenX::tags->INTERNAL_VICTIM_TEAM_LONG_TAG, RenX::getFullTeamName(team));
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnVoteKick(RenX::Server &server, const RenX::TeamType &, const RenX::PlayerInfo &player, const RenX::PlayerInfo &victim)
{
	logFuncType func;
	if (RenX_LoggingPlugin::voteCallPublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->voteKickFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server, &player, &victim);
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnVoteMineBan(RenX::Server &server, const RenX::TeamType &, const RenX::PlayerInfo &player, const RenX::PlayerInfo &victim)
{
	logFuncType func;
	if (RenX_LoggingPlugin::voteCallPublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->voteMineBanFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server, &player, &victim);
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnVoteRemoveBots(RenX::Server &server, const RenX::TeamType &, const RenX::PlayerInfo &player, const RenX::TeamType &victim, int amount)
{
	logFuncType func;
	if (RenX_LoggingPlugin::voteCallPublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->voteRemoveBotsFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server, &player);
		msg.replace(RenX::tags->INTERNAL_VICTIM_TEAM_COLOR_TAG, RenX::getTeamColor(victim));
		msg.replace(RenX::tags->INTERNAL_VICTIM_TEAM_SHORT_TAG, RenX::getTeamName(victim));
		msg.replace(RenX::tags->INTERNAL_VICTIM_TEAM_LONG_TAG, RenX::getFullTeamName(victim));
		msg.replace(RenX::tags->INTERNAL_OBJECT_TAG, Jupiter::StringS::Format("%d", amount));
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnVoteRestartMap(RenX::Server &server, const RenX::TeamType &team, const RenX::PlayerInfo &player)
{
	logFuncType func;
	if (RenX_LoggingPlugin::voteCallPublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->voteRestartMapFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server, &player);
		msg.replace(RenX::tags->INTERNAL_VICTIM_TEAM_COLOR_TAG, RenX::getTeamColor(team));
		msg.replace(RenX::tags->INTERNAL_VICTIM_TEAM_SHORT_TAG, RenX::getTeamName(team));
		msg.replace(RenX::tags->INTERNAL_VICTIM_TEAM_LONG_TAG, RenX::getFullTeamName(team));
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnVoteSurrender(RenX::Server &server, const RenX::TeamType &team, const RenX::PlayerInfo &player)
{
	logFuncType func;
	if (RenX_LoggingPlugin::voteCallPublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->voteSurrenderFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server, &player);
		msg.replace(RenX::tags->INTERNAL_VICTIM_TEAM_COLOR_TAG, RenX::getTeamColor(team));
		msg.replace(RenX::tags->INTERNAL_VICTIM_TEAM_SHORT_TAG, RenX::getTeamName(team));
		msg.replace(RenX::tags->INTERNAL_VICTIM_TEAM_LONG_TAG, RenX::getFullTeamName(team));
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnVoteSurvey(RenX::Server &server, const RenX::TeamType &team, const RenX::PlayerInfo &player, const Jupiter::ReadableString &text)
{
	logFuncType func;
	if (RenX_LoggingPlugin::voteCallPublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->voteSurveyFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server, &player);
		msg.replace(RenX::tags->INTERNAL_VICTIM_TEAM_COLOR_TAG, RenX::getTeamColor(team));
		msg.replace(RenX::tags->INTERNAL_VICTIM_TEAM_SHORT_TAG, RenX::getTeamName(team));
		msg.replace(RenX::tags->INTERNAL_VICTIM_TEAM_LONG_TAG, RenX::getFullTeamName(team));
		msg.replace(RenX::tags->INTERNAL_MESSAGE_TAG, text);
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnVoteOther(RenX::Server &server, const RenX::TeamType &team, const Jupiter::ReadableString &type, const RenX::PlayerInfo &player)
{
	logFuncType func;
	if (RenX_LoggingPlugin::voteCallPublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->voteOtherFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server, &player);
		msg.replace(RenX::tags->INTERNAL_VICTIM_TEAM_COLOR_TAG, RenX::getTeamColor(team));
		msg.replace(RenX::tags->INTERNAL_VICTIM_TEAM_SHORT_TAG, RenX::getTeamName(team));
		msg.replace(RenX::tags->INTERNAL_VICTIM_TEAM_LONG_TAG, RenX::getFullTeamName(team));
		msg.replace(RenX::tags->INTERNAL_OBJECT_TAG, RenX::translateName(type));
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnVoteOver(RenX::Server &server, const RenX::TeamType &team, const Jupiter::ReadableString &type, bool success, int yesVotes, int noVotes)
{
	logFuncType func;
	if (RenX_LoggingPlugin::voteOverPublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = success ? this->voteOverSuccessFmt : this->voteOverFailFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server);
		msg.replace(RenX::tags->INTERNAL_OBJECT_TAG, RenX::translateName(type));
		msg.replace(RenX::tags->INTERNAL_TEAM_COLOR_TAG, RenX::getTeamColor(team));
		msg.replace(RenX::tags->INTERNAL_TEAM_SHORT_TAG, RenX::getTeamName(team));
		msg.replace(RenX::tags->INTERNAL_TEAM_LONG_TAG, RenX::getFullTeamName(team));
		msg.replace(RenX::tags->INTERNAL_VICTIM_TEAM_COLOR_TAG, RenX::getTeamColor(team));
		msg.replace(RenX::tags->INTERNAL_VICTIM_TEAM_SHORT_TAG, RenX::getTeamName(team));
		msg.replace(RenX::tags->INTERNAL_VICTIM_TEAM_LONG_TAG, RenX::getFullTeamName(team));
		msg.replace(RenX::tags->INTERNAL_WIN_SCORE_TAG, Jupiter::StringS::Format("%d", yesVotes));
		msg.replace(RenX::tags->INTERNAL_LOSE_SCORE_TAG, Jupiter::StringS::Format("%d", noVotes));
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnVoteCancel(RenX::Server &server, const RenX::TeamType &team, const Jupiter::ReadableString &type)
{
	logFuncType func;
	if (RenX_LoggingPlugin::voteCancelPublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->voteCancelFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server);
		msg.replace(RenX::tags->INTERNAL_OBJECT_TAG, RenX::translateName(type));
		msg.replace(RenX::tags->INTERNAL_TEAM_COLOR_TAG, RenX::getTeamColor(team));
		msg.replace(RenX::tags->INTERNAL_TEAM_SHORT_TAG, RenX::getTeamName(team));
		msg.replace(RenX::tags->INTERNAL_TEAM_LONG_TAG, RenX::getFullTeamName(team));
		msg.replace(RenX::tags->INTERNAL_VICTIM_TEAM_COLOR_TAG, RenX::getTeamColor(team));
		msg.replace(RenX::tags->INTERNAL_VICTIM_TEAM_SHORT_TAG, RenX::getTeamName(team));
		msg.replace(RenX::tags->INTERNAL_VICTIM_TEAM_LONG_TAG, RenX::getFullTeamName(team));
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnVote(RenX::Server &server, const Jupiter::ReadableString &raw)
{
	logFuncType func;
	if (RenX_LoggingPlugin::votePublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->voteFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server);
		msg.replace(RenX::tags->INTERNAL_MESSAGE_TAG, raw);
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnMapChange(RenX::Server &server, const Jupiter::ReadableString &map, bool seamless)
{
	logFuncType func;
	if (RenX_LoggingPlugin::mapChangePublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->mapChangeFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server);
		msg.replace(RenX::tags->INTERNAL_MESSAGE_TAG, map);
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnMapLoad(RenX::Server &server, const Jupiter::ReadableString &map)
{
	logFuncType func;
	if (RenX_LoggingPlugin::mapLoadPublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->mapLoadFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server);
		msg.replace(RenX::tags->INTERNAL_MESSAGE_TAG, map);
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnMapStart(RenX::Server &server, const Jupiter::ReadableString &map)
{
	logFuncType func;
	if (RenX_LoggingPlugin::mapStartPublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->mapStartFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server);
		msg.replace(RenX::tags->INTERNAL_MESSAGE_TAG, map);
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnMap(RenX::Server &server, const Jupiter::ReadableString &raw)
{
	logFuncType func;
	if (RenX_LoggingPlugin::mapPublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->mapFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server);
		msg.replace(RenX::tags->INTERNAL_MESSAGE_TAG, raw);
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnDemoRecord(RenX::Server &server, const RenX::PlayerInfo &player)
{
	logFuncType func;
	if (RenX_LoggingPlugin::demoRecordPublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->demoRecordFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server, &player);
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnDemoRecord(RenX::Server &server, const Jupiter::ReadableString &user)
{
	logFuncType func;
	if (RenX_LoggingPlugin::demoRecordPublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->rconDemoRecordFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server);
		msg.replace(RenX::tags->nameTag, user);
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnDemoRecordStop(RenX::Server &server)
{
	logFuncType func;
	if (RenX_LoggingPlugin::demoRecordStopPublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->demoRecordStopFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server);
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnDemo(RenX::Server &server, const Jupiter::ReadableString &raw)
{
	logFuncType func;
	if (RenX_LoggingPlugin::demoPublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->demoFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server);
		msg.replace(RenX::tags->INTERNAL_MESSAGE_TAG, raw);
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnLog(RenX::Server &server, const Jupiter::ReadableString &raw)
{
	logFuncType func;
	if (RenX_LoggingPlugin::logPublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;
	
	Jupiter::String msg = this->logFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server);
		msg.replace(RenX::tags->INTERNAL_MESSAGE_TAG, raw);
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnCommand(RenX::Server &server, const Jupiter::ReadableString &raw)
{
	logFuncType func;
	if (RenX_LoggingPlugin::commandPublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;

	Jupiter::String msg = this->commandFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server);
		msg.replace(RenX::tags->INTERNAL_MESSAGE_TAG, raw);
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnError(RenX::Server &server, const Jupiter::ReadableString &raw)
{
	logFuncType func;
	if (RenX_LoggingPlugin::errorPublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;
	
	Jupiter::String msg = this->errorFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server);
		msg.replace(RenX::tags->INTERNAL_MESSAGE_TAG, raw);
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnVersion(RenX::Server &server, const Jupiter::ReadableString &raw)
{
	logFuncType func;
	if (RenX_LoggingPlugin::versionPublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;
	
	Jupiter::String msg = this->versionFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server);
		msg.replace(RenX::tags->INTERNAL_MESSAGE_TAG, raw);
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnAuthorized(RenX::Server &server, const Jupiter::ReadableString &raw)
{
	logFuncType func;
	if (RenX_LoggingPlugin::authorizedPublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;
	
	Jupiter::String msg = this->authorizedFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server);
		msg.replace(RenX::tags->INTERNAL_MESSAGE_TAG, raw);
		(server.*func)(msg);
	}
}

void RenX_LoggingPlugin::RenX_OnOther(RenX::Server &server, char token, const Jupiter::ReadableString &raw)
{
	logFuncType func;
	if (RenX_LoggingPlugin::otherPublic)
		func = &RenX::Server::sendLogChan;
	else
		func = &RenX::Server::sendAdmChan;
	
	Jupiter::String msg = this->otherFmt;
	if (!msg.empty())
	{
		RenX::processTags(msg, &server);
		msg.replace(RenX::tags->INTERNAL_MESSAGE_TAG, raw);
		(server.*func)(msg);
	}
}

int RenX_LoggingPlugin::OnRehash()
{
	RenX::Plugin::OnRehash();
	return this->initialize() ? 0 : -1;
}

// Plugin instantiation and entry point.
RenX_LoggingPlugin pluginInstance;

extern "C" JUPITER_EXPORT Jupiter::Plugin *getPlugin()
{
	return &pluginInstance;
}
