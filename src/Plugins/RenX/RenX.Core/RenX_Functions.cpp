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

#include <ctime>
#include "jessilib/unicode.hpp"
#include "Jupiter/Functions.h"
#include "IRC_Bot.h"
#include "ServerManager.h"
#include "RenX_Functions.h"
#include "RenX_Core.h"
#include "RenX_Server.h"
#include "RenX_PlayerInfo.h"

using namespace Jupiter::literals;
using namespace std::literals;

/** Team color translations */
Jupiter::ReferenceString NodColor = "04";
Jupiter::ReferenceString GDIColor = "08";
Jupiter::ReferenceString OtherColor = "14";

/** Short team name translations */
Jupiter::ReferenceString NodShortName = "Nod";
Jupiter::ReferenceString GDIShortName = "GDI";
Jupiter::ReferenceString OtherShortName = "N/A";

/** Long team name translations */
Jupiter::ReferenceString NodLongName = "Brotherhood of Nod";
Jupiter::ReferenceString GDILongName = "Global Defense Initiative";
Jupiter::ReferenceString OtherLongName = "Unknown";

/** RenegadeX RCON protocol message deliminator */
const char RenX::DelimC = '\x02';
const char RenX::DelimC3 = '\xA0';
const Jupiter::ReferenceString RenX::DevBotName = "DevBot"_jrs;

/** WinType translations */

Jupiter::ReferenceString scoreWinTypeTranslation = "Domination (High Score)";
Jupiter::ReferenceString baseWinTypeTranslation = "Conquest (Base Destruction)";
Jupiter::ReferenceString beaconWinTypeTranslation = "Espionage (Beacon)";
Jupiter::ReferenceString tieWinTypeTranslation = "Draw (Tie)";
Jupiter::ReferenceString shutdownWinTypeTranslation = "Ceasefire (Shutdown)";
Jupiter::ReferenceString surrenderWinTypeTranslation = "Forfeit (Surrender)";
Jupiter::ReferenceString unknownWinTypeTranslation = "Aliens (Unknown)";

/** WinType plain translations */

Jupiter::ReferenceString scoreWinTypePlainTranslation = "High Score";
Jupiter::ReferenceString baseWinTypePlainTranslation = "Base Destruction";
Jupiter::ReferenceString beaconWinTypePlainTranslation = "Beacon";
Jupiter::ReferenceString tieWinTypePlainTranslation = "Tie";
Jupiter::ReferenceString shutdownWinTypePlainTranslation = "Shutdown";
Jupiter::ReferenceString surrenderWinTypePlainTranslation = "Surrender";
Jupiter::ReferenceString unknownWinTypePlainTranslation = "Unknown";

/** Vote translations */

Jupiter::ReferenceString translated_VoteMenuChoice_AddBots = STRING_LITERAL_AS_REFERENCE("Add Bots");
Jupiter::ReferenceString translated_VoteMenuChoice_ChangeMap = STRING_LITERAL_AS_REFERENCE("Change Map");
Jupiter::ReferenceString translated_VoteMenuChoice_Donate = STRING_LITERAL_AS_REFERENCE("Donate");
Jupiter::ReferenceString translated_VoteMenuChoice_Kick = STRING_LITERAL_AS_REFERENCE("Kick");
Jupiter::ReferenceString translated_VoteMenuChoice_RemoveBots = STRING_LITERAL_AS_REFERENCE("Remove Bots");
Jupiter::ReferenceString translated_VoteMenuChoice_RestartMatch = STRING_LITERAL_AS_REFERENCE("Restart Match");
Jupiter::ReferenceString translated_VoteMenuChoice_StartMatch = STRING_LITERAL_AS_REFERENCE("Start Match");
Jupiter::ReferenceString translated_VoteMenuChoice_Survey = STRING_LITERAL_AS_REFERENCE("Survey");

/** Object / damage type translations */

/** Nod Vehicles */
Jupiter::ReferenceString translated_Vehicle_Harvester_Nod = STRING_LITERAL_AS_REFERENCE("Nod Harvester");
Jupiter::ReferenceString translated_Vehicle_Buggy = STRING_LITERAL_AS_REFERENCE("Buggy");
Jupiter::ReferenceString translated_Vehicle_Artillery = STRING_LITERAL_AS_REFERENCE("Mobile Artillery");
Jupiter::ReferenceString translated_Vehicle_APC_Nod = STRING_LITERAL_AS_REFERENCE("Nod APC");
Jupiter::ReferenceString translated_Vehicle_LightTank = STRING_LITERAL_AS_REFERENCE("Light Tank");
Jupiter::ReferenceString translated_Vehicle_FlameTank = STRING_LITERAL_AS_REFERENCE("Flame Tank");
Jupiter::ReferenceString translated_Vehicle_StealthTank = STRING_LITERAL_AS_REFERENCE("Stealth Tank");
Jupiter::ReferenceString translated_Vehicle_Chinook_Nod = STRING_LITERAL_AS_REFERENCE("Nod Chinook");
Jupiter::ReferenceString translated_Vehicle_Apache = STRING_LITERAL_AS_REFERENCE("Apache");

Jupiter::ReferenceString translated_Vehicle_ReconBike = STRING_LITERAL_AS_REFERENCE("Recon Bike");
Jupiter::ReferenceString translated_Vehicle_TickTank = STRING_LITERAL_AS_REFERENCE("Tick Tank");

/** GDI Vehicles */
Jupiter::ReferenceString translated_Vehicle_Harvester_GDI = STRING_LITERAL_AS_REFERENCE("GDI Harvester");
Jupiter::ReferenceString translated_Vehicle_Humvee = STRING_LITERAL_AS_REFERENCE("Humvee");
Jupiter::ReferenceString translated_Vehicle_MRLS = STRING_LITERAL_AS_REFERENCE("Mobile Rocket Launcher System");
Jupiter::ReferenceString translated_Vehicle_APC_GDI = STRING_LITERAL_AS_REFERENCE("GDI APC");
Jupiter::ReferenceString translated_Vehicle_MediumTank = STRING_LITERAL_AS_REFERENCE("Medium Tank");
Jupiter::ReferenceString translated_Vehicle_MammothTank = STRING_LITERAL_AS_REFERENCE("Mammoth Tank");
Jupiter::ReferenceString translated_Vehicle_Chinook_GDI = STRING_LITERAL_AS_REFERENCE("GDI Chinook");
Jupiter::ReferenceString translated_Vehicle_Orca = STRING_LITERAL_AS_REFERENCE("Orca");

Jupiter::ReferenceString translated_Vehicle_HoverMRLS = STRING_LITERAL_AS_REFERENCE("Hover MRLS");
Jupiter::ReferenceString translated_Vehicle_Titan = STRING_LITERAL_AS_REFERENCE("Titan");
Jupiter::ReferenceString translated_Vehicle_Wolverine = STRING_LITERAL_AS_REFERENCE("Wolverine");

/** Other Vehicles */
Jupiter::ReferenceString translated_Vehicle_A10_DmgType_GattlingGun = STRING_LITERAL_AS_REFERENCE("A10 Thunderbolt Gattling Gun");
Jupiter::ReferenceString translated_Vehicle_A10_DmgType_Bomb = STRING_LITERAL_AS_REFERENCE("A10 Thunderbolt Bomb");
Jupiter::ReferenceString translated_Vehicle_AC130_DmgType_HeavyCannon = STRING_LITERAL_AS_REFERENCE("AC130 Heavy Cannon");
Jupiter::ReferenceString translated_Vehicle_AC130_DmgType_AutoCannon = STRING_LITERAL_AS_REFERENCE("AC130 Auto Cannon");

/** Weapons */
Jupiter::ReferenceString translated_Weapon_HeavyPistol = STRING_LITERAL_AS_REFERENCE("Heavy Pistol");
Jupiter::ReferenceString translated_Weapon_Carbine = STRING_LITERAL_AS_REFERENCE("Carbine");
Jupiter::ReferenceString translated_Weapon_Airstrike_GDI = STRING_LITERAL_AS_REFERENCE("GDI Airstrike");
Jupiter::ReferenceString translated_Weapon_Airstrike_Nod = STRING_LITERAL_AS_REFERENCE("Nod Airstrike");
Jupiter::ReferenceString translated_Weapon_TiberiumFlechetteRifle = STRING_LITERAL_AS_REFERENCE("Tiberium Flechette Gun");
Jupiter::ReferenceString translated_Weapon_TiberiumAutoRifle = STRING_LITERAL_AS_REFERENCE("Tiberium Automatic Rifle");
Jupiter::ReferenceString translated_Weapon_TiberiumAutoRifle_Blue = STRING_LITERAL_AS_REFERENCE("Blue Tiberium Automatic Rifle Burst");
Jupiter::ReferenceString translated_Weapon_EMPGrenade = STRING_LITERAL_AS_REFERENCE("EMP Grenade");
Jupiter::ReferenceString translated_Weapon_SmokeGrenade = STRING_LITERAL_AS_REFERENCE("Smoke Grenade");
Jupiter::ReferenceString translated_Weapon_TimedC4 = STRING_LITERAL_AS_REFERENCE("Timed C4");
Jupiter::ReferenceString translated_Weapon_RemoteC4 = STRING_LITERAL_AS_REFERENCE("Remote C4");
Jupiter::ReferenceString translated_Weapon_ProxyC4 = STRING_LITERAL_AS_REFERENCE("Proximity C4");
Jupiter::ReferenceString translated_Weapon_ATMine = STRING_LITERAL_AS_REFERENCE("Anti-Tank Mine");
Jupiter::ReferenceString translated_Weapon_IonCannonBeacon = STRING_LITERAL_AS_REFERENCE("Ion Cannon Beacon");
Jupiter::ReferenceString translated_Weapon_NukeBeacon = STRING_LITERAL_AS_REFERENCE("Nuclear Missile Beacon");
Jupiter::ReferenceString translated_Weapon_DeployedC4 = STRING_LITERAL_AS_REFERENCE("Timed C4");
Jupiter::ReferenceString translated_Weapon_DeployedTimedC4 = STRING_LITERAL_AS_REFERENCE("Timed C4");
Jupiter::ReferenceString translated_Weapon_DeployedRemoteC4 = STRING_LITERAL_AS_REFERENCE("Remote C4");
Jupiter::ReferenceString translated_Weapon_DeployedProxyC4 = STRING_LITERAL_AS_REFERENCE("Proximity C4");
Jupiter::ReferenceString translated_Weapon_DeployedATMine = STRING_LITERAL_AS_REFERENCE("Anti-Tank Mine");
Jupiter::ReferenceString translated_Weapon_DeployedIonCannonBeacon = STRING_LITERAL_AS_REFERENCE("Ion Cannon Beacon");
Jupiter::ReferenceString translated_Weapon_DeployedNukeBeacon = STRING_LITERAL_AS_REFERENCE("Nuclear Missile Beacon");
Jupiter::ReferenceString translated_Weapon_CrateNuke = STRING_LITERAL_AS_REFERENCE("Nuclear Crate Explosion");
Jupiter::ReferenceString translated_Weapon_DevNuke = STRING_LITERAL_AS_REFERENCE("Nuclear Dev Explosion");

/** Projectiles */
Jupiter::ReferenceString translated_Projectile_EMPGrenade = STRING_LITERAL_AS_REFERENCE("EMP Grenade");
Jupiter::ReferenceString translated_Projectile_SmokeGrenade = STRING_LITERAL_AS_REFERENCE("Smoke Grenade");

/** GDI Characters */
Jupiter::ReferenceString translated_GDI_Deadeye = STRING_LITERAL_AS_REFERENCE("Deadeye");
Jupiter::ReferenceString translated_GDI_Engineer = STRING_LITERAL_AS_REFERENCE("GDI Engineer");
Jupiter::ReferenceString translated_GDI_Grenadier = STRING_LITERAL_AS_REFERENCE("Grenadier");
Jupiter::ReferenceString translated_GDI_Gunner = STRING_LITERAL_AS_REFERENCE("Gunner");
Jupiter::ReferenceString translated_GDI_Havoc = STRING_LITERAL_AS_REFERENCE("Havoc");
Jupiter::ReferenceString translated_GDI_Hotwire = STRING_LITERAL_AS_REFERENCE("Hotwire");
Jupiter::ReferenceString translated_GDI_Marksman = STRING_LITERAL_AS_REFERENCE("GDI Marksman");
Jupiter::ReferenceString translated_GDI_McFarland = STRING_LITERAL_AS_REFERENCE("McFarland");
Jupiter::ReferenceString translated_GDI_Mobius = STRING_LITERAL_AS_REFERENCE("Mobius");
Jupiter::ReferenceString translated_GDI_Officer = STRING_LITERAL_AS_REFERENCE("GDI Officer");
Jupiter::ReferenceString translated_GDI_Patch = STRING_LITERAL_AS_REFERENCE("Patch");
Jupiter::ReferenceString translated_GDI_RocketSoldier = STRING_LITERAL_AS_REFERENCE("GDI Rocket Soldier");
Jupiter::ReferenceString translated_GDI_Shotgunner = STRING_LITERAL_AS_REFERENCE("GDI Shotgunner");
Jupiter::ReferenceString translated_GDI_Soldier = STRING_LITERAL_AS_REFERENCE("GDI Soldier");
Jupiter::ReferenceString translated_GDI_Sydney = STRING_LITERAL_AS_REFERENCE("Sydney");

/** Nod Characters */
Jupiter::ReferenceString translated_Nod_BlackHandSniper = STRING_LITERAL_AS_REFERENCE("Black Hand Sniper");
Jupiter::ReferenceString translated_Nod_ChemicalTrooper = STRING_LITERAL_AS_REFERENCE("Chemical Trooper");
Jupiter::ReferenceString translated_Nod_Engineer = STRING_LITERAL_AS_REFERENCE("Nod Engineer");
Jupiter::ReferenceString translated_Nod_FlameTrooper = STRING_LITERAL_AS_REFERENCE("Flame Trooper");
Jupiter::ReferenceString translated_Nod_LaserChainGunner = STRING_LITERAL_AS_REFERENCE("Laser Chain Gunner");
Jupiter::ReferenceString translated_Nod_Marksman = STRING_LITERAL_AS_REFERENCE("Nod Marksman");
Jupiter::ReferenceString translated_Nod_Mendoza = STRING_LITERAL_AS_REFERENCE("Mendoza");
Jupiter::ReferenceString translated_Nod_Officer = STRING_LITERAL_AS_REFERENCE("Nod Officer");
Jupiter::ReferenceString translated_Nod_Raveshaw = STRING_LITERAL_AS_REFERENCE("Raveshaw");
Jupiter::ReferenceString translated_Nod_RocketSoldier = STRING_LITERAL_AS_REFERENCE("Nod Rocket Soldier");
Jupiter::ReferenceString translated_Nod_Sakura = STRING_LITERAL_AS_REFERENCE("Sakura");
Jupiter::ReferenceString translated_Nod_Shotgunner = STRING_LITERAL_AS_REFERENCE("Nod Shotgunner");
Jupiter::ReferenceString translated_Nod_Soldier = STRING_LITERAL_AS_REFERENCE("Nod Soldier");
Jupiter::ReferenceString translated_Nod_StealthBlackHand = STRING_LITERAL_AS_REFERENCE("Stealth Black Hand");
Jupiter::ReferenceString translated_Nod_Technician = STRING_LITERAL_AS_REFERENCE("Technician");

/** Non-weapon damage types */
Jupiter::ReferenceString translated_DmgType_Suicided = STRING_LITERAL_AS_REFERENCE("Suicide");
Jupiter::ReferenceString translated_DmgType_Fell = STRING_LITERAL_AS_REFERENCE("Fall");
Jupiter::ReferenceString translated_DmgType_Tiberium = STRING_LITERAL_AS_REFERENCE("Tiberium");
Jupiter::ReferenceString translated_DmgType_TiberiumBleed = STRING_LITERAL_AS_REFERENCE("Tiberium Decay");
Jupiter::ReferenceString translated_DmgType_TiberiumBleed_Blue = STRING_LITERAL_AS_REFERENCE("Blue Tiberium Decay");
Jupiter::ReferenceString translated_DmgType_RanOver = STRING_LITERAL_AS_REFERENCE("Crushed");

/** Infantry weapons */
Jupiter::ReferenceString translated_DmgType_Pistol = STRING_LITERAL_AS_REFERENCE("Pistol");
Jupiter::ReferenceString translated_DmgType_SMG = STRING_LITERAL_AS_REFERENCE("Machine Pistol");
Jupiter::ReferenceString translated_DmgType_HeavyPistol = STRING_LITERAL_AS_REFERENCE("Heavy Pistol");
Jupiter::ReferenceString translated_DmgType_Carbine = STRING_LITERAL_AS_REFERENCE("Carbine");
Jupiter::ReferenceString translated_DmgType_TiberiumFlechetteRifle = STRING_LITERAL_AS_REFERENCE("Tiberium Flechette Gun"); // Not a rifle.
Jupiter::ReferenceString translated_DmgType_TiberiumAutoRifle = STRING_LITERAL_AS_REFERENCE("Tiberium Automatic Rifle");
Jupiter::ReferenceString translated_DmgType_TiberiumAutoRifle_Blue = STRING_LITERAL_AS_REFERENCE("Blue Tiberium Automatic Rifle Burst");
Jupiter::ReferenceString translated_DmgType_TiberiumAutoRifle_Flechette_Blue = STRING_LITERAL_AS_REFERENCE("Blue Tiberium Automatic Rifle");

Jupiter::ReferenceString translated_DmgType_Grenade = STRING_LITERAL_AS_REFERENCE("Grenade");
Jupiter::ReferenceString translated_DmgType_TimedC4 = STRING_LITERAL_AS_REFERENCE("Timed C4");
Jupiter::ReferenceString translated_DmgType_RemoteC4 = STRING_LITERAL_AS_REFERENCE("Remote C4");
Jupiter::ReferenceString translated_DmgType_ProxyC4 = STRING_LITERAL_AS_REFERENCE("Proximity C4");
Jupiter::ReferenceString translated_DmgType_ATMine = STRING_LITERAL_AS_REFERENCE("Anti-Tank Mine");
Jupiter::ReferenceString translated_DmgType_EMPGrenade = STRING_LITERAL_AS_REFERENCE("EMP Grenade");
Jupiter::ReferenceString translated_DmgType_BurnC4 = STRING_LITERAL_AS_REFERENCE("C4 Burn");
Jupiter::ReferenceString translated_DmgType_FireBleed = STRING_LITERAL_AS_REFERENCE("Fire Burn"); // Caused by C4 or flame weapons

Jupiter::ReferenceString translated_DmgType_AutoRifle = STRING_LITERAL_AS_REFERENCE("Automatic Rifle");
Jupiter::ReferenceString translated_DmgType_Shotgun = STRING_LITERAL_AS_REFERENCE("Shotgun");
Jupiter::ReferenceString translated_DmgType_FlameThrower = STRING_LITERAL_AS_REFERENCE("Flamethrower");
Jupiter::ReferenceString translated_DmgType_GrenadeLauncher = STRING_LITERAL_AS_REFERENCE("Grenade Launcher");
Jupiter::ReferenceString translated_DmgType_MarksmanRifle = STRING_LITERAL_AS_REFERENCE("Marksman's Rifle");

Jupiter::ReferenceString translated_DmgType_ChainGun = STRING_LITERAL_AS_REFERENCE("Chain Gun");
Jupiter::ReferenceString translated_DmgType_MissileLauncher = STRING_LITERAL_AS_REFERENCE("Missile Launcher");
Jupiter::ReferenceString translated_DmgType_MissileLauncher_Alt = STRING_LITERAL_AS_REFERENCE("Missile Launcher");
Jupiter::ReferenceString translated_DmgType_ChemicalThrower = STRING_LITERAL_AS_REFERENCE("Chemical Spray Gun");
Jupiter::ReferenceString translated_DmgType_LaserRifle = STRING_LITERAL_AS_REFERENCE("Laser Rifle");
Jupiter::ReferenceString translated_DmgType_TacticalRifle = STRING_LITERAL_AS_REFERENCE("Tactical Rifle");
Jupiter::ReferenceString translated_DmgType_RocketLauncher = STRING_LITERAL_AS_REFERENCE("Rocket Launcher");
Jupiter::ReferenceString translated_DmgType_LaserChainGun = STRING_LITERAL_AS_REFERENCE("Laser Chain Gun");
Jupiter::ReferenceString translated_DmgType_FlakCannon = STRING_LITERAL_AS_REFERENCE("Flak");
Jupiter::ReferenceString translated_DmgType_FlakCannon_Alt = STRING_LITERAL_AS_REFERENCE("Concentrated Flak");
Jupiter::ReferenceString translated_DmgType_SniperRifle = STRING_LITERAL_AS_REFERENCE("Sniper Rifle");
Jupiter::ReferenceString translated_DmgType_RamjetRifle = STRING_LITERAL_AS_REFERENCE("Ramjet");
Jupiter::ReferenceString translated_DmgType_Railgun = STRING_LITERAL_AS_REFERENCE("Railgun");
Jupiter::ReferenceString translated_DmgType_PersonalIonCannon = STRING_LITERAL_AS_REFERENCE("Personal Ion Cannon");
Jupiter::ReferenceString translated_DmgType_VoltRifle = STRING_LITERAL_AS_REFERENCE("Volt Rifle");
Jupiter::ReferenceString translated_DmgType_VoltRifle_Alt = STRING_LITERAL_AS_REFERENCE("Volt Rifle Burst");
Jupiter::ReferenceString translated_DmgType_VoltAutoRifle = STRING_LITERAL_AS_REFERENCE("Volt Automatic Rifle");
Jupiter::ReferenceString translated_DmgType_VoltAutoRifle_Alt = STRING_LITERAL_AS_REFERENCE("Volt Automatic Rifle Burst");

/** Vehicle weapons */
Jupiter::ReferenceString translated_DmgType_MammothTank_Missile = STRING_LITERAL_AS_REFERENCE("Mammoth Tank Missile");
Jupiter::ReferenceString translated_DmgType_MammothTank_Cannon = STRING_LITERAL_AS_REFERENCE("Mammoth Tank Cannon");
Jupiter::ReferenceString translated_DmgType_Orca_Missile = STRING_LITERAL_AS_REFERENCE("Orca Missile");
Jupiter::ReferenceString translated_DmgType_Orca_Gun = STRING_LITERAL_AS_REFERENCE("Orca Gun");
Jupiter::ReferenceString translated_DmgType_Orca_Passenger = STRING_LITERAL_AS_REFERENCE("Orca Passenger Missile");
Jupiter::ReferenceString translated_DmgType_Apache_Rocket = STRING_LITERAL_AS_REFERENCE("Apache Rocket");
Jupiter::ReferenceString translated_DmgType_Apache_Gun = STRING_LITERAL_AS_REFERENCE("Apache Gun");
Jupiter::ReferenceString translated_DmgType_Apache_Passenger = STRING_LITERAL_AS_REFERENCE("Apache Passenger Missile");

/** Other weapons */
Jupiter::ReferenceString translated_DmgType_AGT_MG = STRING_LITERAL_AS_REFERENCE("Machine Gun");
Jupiter::ReferenceString translated_DmgType_AGT_Rocket = STRING_LITERAL_AS_REFERENCE("Rocket");
Jupiter::ReferenceString translated_DmgType_Obelisk = STRING_LITERAL_AS_REFERENCE("Obelisk Laser");
Jupiter::ReferenceString translated_DmgType_GuardTower = STRING_LITERAL_AS_REFERENCE("Guard Tower");
Jupiter::ReferenceString translated_DmgType_Turret = STRING_LITERAL_AS_REFERENCE("Turret");
Jupiter::ReferenceString translated_DmgType_SAMSite = STRING_LITERAL_AS_REFERENCE("SAM Site");
Jupiter::ReferenceString translated_DmgType_AATower = STRING_LITERAL_AS_REFERENCE("Anti-Air Guard Tower");
Jupiter::ReferenceString translated_DmgType_GunEmpl = STRING_LITERAL_AS_REFERENCE("Gun Emplacement Gattling Gun");
Jupiter::ReferenceString translated_DmgType_GunEmpl_Alt = STRING_LITERAL_AS_REFERENCE("Gun Emplacement Automatic Cannon");
Jupiter::ReferenceString translated_DmgType_RocketEmpl_Swarm = STRING_LITERAL_AS_REFERENCE("Rocket Emplacement Swarm Missile");
Jupiter::ReferenceString translated_DmgType_RocketEmpl_Missile = STRING_LITERAL_AS_REFERENCE("Rocket Emplacement Hellfire Missile");
Jupiter::ReferenceString translated_DmgType_Nuke = STRING_LITERAL_AS_REFERENCE("Nuclear Missile Strike");
Jupiter::ReferenceString translated_DmgType_IonCannon = STRING_LITERAL_AS_REFERENCE("Ion Cannon Strike");

/** Nod Vehicles */
Jupiter::ReferenceString translated_DmgType_Harvester_Nod = STRING_LITERAL_AS_REFERENCE("Nod Harvester");
Jupiter::ReferenceString translated_DmgType_Buggy = STRING_LITERAL_AS_REFERENCE("Buggy");
Jupiter::ReferenceString translated_DmgType_Artillery = STRING_LITERAL_AS_REFERENCE("Mobile Artillery");
Jupiter::ReferenceString translated_DmgType_APC_Nod = STRING_LITERAL_AS_REFERENCE("Nod APC");
Jupiter::ReferenceString translated_DmgType_LightTank = STRING_LITERAL_AS_REFERENCE("Light Tank");
Jupiter::ReferenceString translated_DmgType_FlameTank = STRING_LITERAL_AS_REFERENCE("Flame Tank");
Jupiter::ReferenceString translated_DmgType_StealthTank = STRING_LITERAL_AS_REFERENCE("Stealth Tank");
Jupiter::ReferenceString translated_DmgType_Chinook_Nod = STRING_LITERAL_AS_REFERENCE("Nod Chinook");
Jupiter::ReferenceString translated_DmgType_Apache = STRING_LITERAL_AS_REFERENCE("Apache");

Jupiter::ReferenceString translated_Vehicle_ReconBike_DmgType = STRING_LITERAL_AS_REFERENCE("Recon Bike");
Jupiter::ReferenceString translated_Vehicle_TickTank_DmgType = STRING_LITERAL_AS_REFERENCE("Tick Tank");

/** GDI Vehicles */
Jupiter::ReferenceString translated_DmgType_Harvester_GDI = STRING_LITERAL_AS_REFERENCE("GDI Harvester");
Jupiter::ReferenceString translated_DmgType_Humvee = STRING_LITERAL_AS_REFERENCE("Humvee");
Jupiter::ReferenceString translated_DmgType_MRLS = STRING_LITERAL_AS_REFERENCE("Mobile Rocket Launcher System");
Jupiter::ReferenceString translated_DmgType_APC_GDI = STRING_LITERAL_AS_REFERENCE("GDI APC");
Jupiter::ReferenceString translated_DmgType_MediumTank = STRING_LITERAL_AS_REFERENCE("Medium Tank");
Jupiter::ReferenceString translated_DmgType_MammothTank = STRING_LITERAL_AS_REFERENCE("Mammoth Tank");
Jupiter::ReferenceString translated_DmgType_Chinook_GDI = STRING_LITERAL_AS_REFERENCE("GDI Chinook");
Jupiter::ReferenceString translated_DmgType_Orca = STRING_LITERAL_AS_REFERENCE("Orca");

Jupiter::ReferenceString translated_Vehicle_HoverMRLS_DmgType = STRING_LITERAL_AS_REFERENCE("Hover MRLS");
Jupiter::ReferenceString translated_Vehicle_Titan_DmgType = STRING_LITERAL_AS_REFERENCE("Titan");
Jupiter::ReferenceString translated_Vehicle_Wolverine_DmgType = STRING_LITERAL_AS_REFERENCE("Wolverine");

/** Other Vehicles */
Jupiter::ReferenceString translated_DmgType_A10_Missile = STRING_LITERAL_AS_REFERENCE("A10 Missile");

/** Nod structures */
Jupiter::ReferenceString translated_Building_HandOfNod = STRING_LITERAL_AS_REFERENCE("Hand of Nod");
Jupiter::ReferenceString translated_Building_AirTower = STRING_LITERAL_AS_REFERENCE("Airstrip");
Jupiter::ReferenceString translated_Building_Airstrip = STRING_LITERAL_AS_REFERENCE("Airstrip");
Jupiter::ReferenceString translated_Building_Refinery_Nod = STRING_LITERAL_AS_REFERENCE("Nod Refinery");
Jupiter::ReferenceString translated_Building_PowerPlant_Nod = STRING_LITERAL_AS_REFERENCE("Nod Power Plant");
Jupiter::ReferenceString translated_Building_HandOfNod_Internals = STRING_LITERAL_AS_REFERENCE("Hand of Nod");
Jupiter::ReferenceString translated_Building_AirTower_Internals = STRING_LITERAL_AS_REFERENCE("Airstrip");
Jupiter::ReferenceString translated_Building_Airstrip_Internals = STRING_LITERAL_AS_REFERENCE("Airstrip");
Jupiter::ReferenceString translated_Building_Refinery_Nod_Internals = STRING_LITERAL_AS_REFERENCE("Nod Refinery");
Jupiter::ReferenceString translated_Building_PowerPlant_Nod_Internals = STRING_LITERAL_AS_REFERENCE("Nod Power Plant");

/** GDI structures */
Jupiter::ReferenceString translated_Building_Barracks = STRING_LITERAL_AS_REFERENCE("Barracks");
Jupiter::ReferenceString translated_Building_WeaponsFactory = STRING_LITERAL_AS_REFERENCE("Weapons Factory");
Jupiter::ReferenceString translated_Building_Refinery_GDI = STRING_LITERAL_AS_REFERENCE("GDI Refinery");
Jupiter::ReferenceString translated_Building_PowerPlant_GDI = STRING_LITERAL_AS_REFERENCE("GDI Power Plant");
Jupiter::ReferenceString translated_Building_Barracks_Internals = STRING_LITERAL_AS_REFERENCE("Barracks");
Jupiter::ReferenceString translated_Building_WeaponsFactory_Internals = STRING_LITERAL_AS_REFERENCE("Weapons Factory");
Jupiter::ReferenceString translated_Building_Refinery_GDI_Internals = STRING_LITERAL_AS_REFERENCE("GDI Refinery");
Jupiter::ReferenceString translated_Building_PowerPlant_GDI_Internals = STRING_LITERAL_AS_REFERENCE("GDI Power Plant");

/** Defense structures */
Jupiter::ReferenceString translated_Building_AdvancedGuardTower = STRING_LITERAL_AS_REFERENCE("Advanced Guard Tower");
Jupiter::ReferenceString translated_Building_Obelisk = STRING_LITERAL_AS_REFERENCE("Obelisk of Light");
Jupiter::ReferenceString translated_Building_AdvancedGuardTower_Internals = STRING_LITERAL_AS_REFERENCE("Advanced Guard Tower");
Jupiter::ReferenceString translated_Building_Obelisk_Internals = STRING_LITERAL_AS_REFERENCE("Obelisk of Light");

/** Other structures */
Jupiter::ReferenceString translated_Building_Silo = STRING_LITERAL_AS_REFERENCE("Tiberium Silo");
Jupiter::ReferenceString translated_Building_CommCentre = STRING_LITERAL_AS_REFERENCE("Communications Center");
Jupiter::ReferenceString translated_Building_Silo_Internals = STRING_LITERAL_AS_REFERENCE("Tiberium Silo");
Jupiter::ReferenceString translated_Building_CommCentre_Internals = STRING_LITERAL_AS_REFERENCE("Communications Center");

/** Fort structures */
Jupiter::ReferenceString translated_CapturableMCT_Fort = STRING_LITERAL_AS_REFERENCE("Fort");
Jupiter::ReferenceString translated_CapturableMCT_MC = STRING_LITERAL_AS_REFERENCE("Medical Center");
Jupiter::ReferenceString translated_CapturableMCT_Fort_Internals = STRING_LITERAL_AS_REFERENCE("Fort");
Jupiter::ReferenceString translated_CapturableMCT_MC_Internals = STRING_LITERAL_AS_REFERENCE("Medical Center");

/** Defences */
Jupiter::ReferenceString translated_Defence_GuardTower = STRING_LITERAL_AS_REFERENCE("Guard Tower");
Jupiter::ReferenceString translated_Defence_Turret = STRING_LITERAL_AS_REFERENCE("Turret");
Jupiter::ReferenceString translated_Defence_SAMSite = STRING_LITERAL_AS_REFERENCE("SAM Site");
Jupiter::ReferenceString translated_Defence_AATower = STRING_LITERAL_AS_REFERENCE("Anti-Air Guard Tower");
Jupiter::ReferenceString translated_Defence_GunEmplacement = STRING_LITERAL_AS_REFERENCE("Gun Emplacement");
Jupiter::ReferenceString translated_Defence_RocketEmplacement = STRING_LITERAL_AS_REFERENCE("Rocket Emplacement");

/** Defences - Sentinels */
Jupiter::ReferenceString translated_Sentinel_AGT_MG_Base = STRING_LITERAL_AS_REFERENCE("Advanced Guard Tower");
Jupiter::ReferenceString translated_Sentinel_AGT_Rockets_Base = STRING_LITERAL_AS_REFERENCE("Advanced Guard Tower");
Jupiter::ReferenceString translated_Sentinel_Obelisk_Laser_Base = STRING_LITERAL_AS_REFERENCE("Obelisk of Light");

/** UT damage types */
Jupiter::ReferenceString translated_UTDmgType_VehicleExplosion = STRING_LITERAL_AS_REFERENCE("Vehicle Explosion");
Jupiter::ReferenceString translated_UTDmgType_Drowned = STRING_LITERAL_AS_REFERENCE("Drowned");

/** Beacons */
Jupiter::ReferenceString translated_IonCannonBeacon = STRING_LITERAL_AS_REFERENCE("Ion Cannon Beacon");
Jupiter::ReferenceString translated_NukeBeacon = STRING_LITERAL_AS_REFERENCE("Nuclear Strike Beacon");
Jupiter::ReferenceString translated_KillZDamageType = STRING_LITERAL_AS_REFERENCE("Kill Zone");

RenX::TeamType RenX::getTeam(int teamNum)
{
	switch (teamNum)
	{
	case 0:
		return RenX::TeamType::GDI;
	case 1:
		return RenX::TeamType::Nod;
	case 255:
		return RenX::TeamType::None;
	default:
		return RenX::TeamType::Other;
	}
}

RenX::TeamType RenX::getTeam(std::string_view team) {
	if (jessilib::equalsi(team, "GDI"sv)) {
		return RenX::TeamType::GDI;
	}

	if (jessilib::equalsi(team, "Nod"sv)) {
		return RenX::TeamType::Nod;
	}

	if (team.empty() || jessilib::equalsi(team, "Neutral"sv) || jessilib::equalsi(team, "Civilians"sv)) {
		return RenX::TeamType::None;
	}

	return RenX::TeamType::Other;
}

const Jupiter::ReadableString &RenX::getTeamColor(TeamType team)
{
	switch (team)
	{
	case RenX::TeamType::GDI:
		return GDIColor;
	case RenX::TeamType::Nod:
		return NodColor;
	default:
		return OtherColor;
	}
}

const Jupiter::ReadableString &RenX::getTeamName(TeamType team)
{
	switch (team)
	{
	case RenX::TeamType::GDI:
		return GDIShortName;
	case RenX::TeamType::Nod:
		return NodShortName;
	default:
		return OtherShortName;
	}
}

const Jupiter::ReadableString &RenX::getFullTeamName(TeamType team)
{
	switch (team)
	{
	case RenX::TeamType::GDI:
		return GDILongName;
	case RenX::TeamType::Nod:
		return NodLongName;
	default:
		return OtherLongName;
	}
}

RenX::TeamType RenX::getEnemy(TeamType team)
{
	switch (team)
	{
	case RenX::TeamType::GDI:
		return RenX::TeamType::Nod;
	case RenX::TeamType::Nod:
		return RenX::TeamType::GDI;
	default:
		return RenX::TeamType::Other;
	}
}

const Jupiter::ReadableString &RenX::getCharacter(const Jupiter::ReadableString &chr)
{
	static Jupiter::ReferenceString object;

	object = chr;
	if (object.find(STRING_LITERAL_AS_REFERENCE("Rx_")) == 0)
		object.shiftRight(3);
	if (object.find(STRING_LITERAL_AS_REFERENCE("InventoryManager_")) == 0)
		object.shiftRight(17);
	else if (object.find(STRING_LITERAL_AS_REFERENCE("FamilyInfo_")) == 0)
		object.shiftRight(11);

	return object;
}

const Jupiter::ReferenceString &translateCharacter(Jupiter::ReferenceString &object)
{
	if (object.find(STRING_LITERAL_AS_REFERENCE("GDI_")) == 0)
	{
		object.shiftRight(4);
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Deadeye"))) return translated_GDI_Deadeye;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Engineer"))) return translated_GDI_Engineer;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Grenadier"))) return translated_GDI_Grenadier;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Gunner"))) return translated_GDI_Gunner;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Havoc"))) return translated_GDI_Havoc;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Hotwire"))) return translated_GDI_Hotwire;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Marksman"))) return translated_GDI_Marksman;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("McFarland"))) return translated_GDI_McFarland;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Mobius"))) return translated_GDI_Mobius;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Officer"))) return translated_GDI_Officer;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Patch"))) return translated_GDI_Patch;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("RocketSoldier"))) return translated_GDI_RocketSoldier;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Shotgunner"))) return translated_GDI_Shotgunner;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Soldier"))) return translated_GDI_Soldier;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Sydney"))) return translated_GDI_Sydney;
	}
	else if (object.find(STRING_LITERAL_AS_REFERENCE("Nod_")) == 0)
	{
		object.shiftRight(4);
		if (object.equals(STRING_LITERAL_AS_REFERENCE("BlackHandSniper"))) return translated_Nod_BlackHandSniper;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("ChemicalTrooper"))) return translated_Nod_ChemicalTrooper;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Engineer"))) return translated_Nod_Engineer;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("FlameTrooper"))) return translated_Nod_FlameTrooper;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("LaserChainGunner"))) return translated_Nod_LaserChainGunner;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Marksman"))) return translated_Nod_Marksman;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Mendoza"))) return translated_Nod_Mendoza;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Officer"))) return translated_Nod_Officer;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Raveshaw"))) return translated_Nod_Raveshaw;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("RocketSoldier"))) return translated_Nod_RocketSoldier;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Sakura"))) return translated_Nod_Sakura;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Shotgunner"))) return translated_Nod_Shotgunner;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Soldier"))) return translated_Nod_Soldier;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("StealthBlackHand"))) return translated_Nod_StealthBlackHand;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Technician"))) return translated_Nod_Technician;
	}

	return object;
}

const Jupiter::ReferenceString RenX::translateName(const Jupiter::ReadableString &obj)
{
	if (obj.isEmpty())
		return Jupiter::ReferenceString::empty;

	Jupiter::ReferenceString iniTranslation = RenX::getCore()->getConfig()["Name"_jrs].get(obj);
	if (iniTranslation.isNotEmpty())
		return iniTranslation;

	Jupiter::ReferenceString object = obj;

	if (object.find(STRING_LITERAL_AS_REFERENCE("nBab_")) == 0)
		object.shiftRight(5);
	
	if (object.find(STRING_LITERAL_AS_REFERENCE("Rx_")) == 0)
		object.shiftRight(3);
	else if (object.find(STRING_LITERAL_AS_REFERENCE("TS_")) == 0)
		object.shiftRight(3);

	if (object.find(STRING_LITERAL_AS_REFERENCE("Vehicle_")) == 0)
	{
		object.shiftRight(8);

		/** Nod Vehicles */
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Harvester_Nod"))) return translated_Vehicle_Harvester_Nod;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Buggy"))) return translated_Vehicle_Buggy;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Artillery"))) return translated_Vehicle_Artillery;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("APC_Nod"))) return translated_Vehicle_APC_Nod;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("LightTank"))) return translated_Vehicle_LightTank;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("FlameTank"))) return translated_Vehicle_FlameTank;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("StealthTank"))) return translated_Vehicle_StealthTank;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Chinook_Nod"))) return translated_Vehicle_Chinook_Nod;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Apache"))) return translated_Vehicle_Apache;

		if (object.equals(STRING_LITERAL_AS_REFERENCE("ReconBike"))) return translated_Vehicle_ReconBike;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("TickTank"))) return translated_Vehicle_TickTank;

		/** GDI Vehicles */
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Harvester_GDI"))) return translated_Vehicle_Harvester_GDI;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Humvee"))) return translated_Vehicle_Humvee;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("MRLS"))) return translated_Vehicle_MRLS;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("APC_GDI"))) return translated_Vehicle_APC_GDI;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("MediumTank"))) return translated_Vehicle_MediumTank;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("MammothTank"))) return translated_Vehicle_MammothTank;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Chinook_GDI"))) return translated_Vehicle_Chinook_GDI;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Orca"))) return translated_Vehicle_Orca;

		if (object.equals(STRING_LITERAL_AS_REFERENCE("HoverMRLS"))) return translated_Vehicle_HoverMRLS;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Titan"))) return translated_Vehicle_Titan;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Wolverine"))) return translated_Vehicle_Wolverine;

		/** Other Vehicles */
		if (object.equals(STRING_LITERAL_AS_REFERENCE("A10_DmgType_GattlingGun"))) return translated_Vehicle_A10_DmgType_GattlingGun;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("A10_DmgType_Bomb"))) return translated_Vehicle_A10_DmgType_Bomb;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("AC130_DmgType_HeavyCannon"))) return translated_Vehicle_AC130_DmgType_HeavyCannon;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("AC130_DmgType_AutoCannon"))) return translated_Vehicle_AC130_DmgType_AutoCannon;
	}
	else if (object.find(STRING_LITERAL_AS_REFERENCE("Weapon_")) == 0)
	{
		object.shiftRight(7);
		if (object.equals(STRING_LITERAL_AS_REFERENCE("HeavyPistol"))) return translated_Weapon_HeavyPistol;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Carbine"))) return translated_Weapon_Carbine;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Airstrike_GDI"))) return translated_Weapon_Airstrike_GDI;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Airstrike_Nod"))) return translated_Weapon_Airstrike_Nod;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("TiberiumFlechetteRifle"))) return translated_Weapon_TiberiumFlechetteRifle;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("TiberiumAutoRifle"))) return translated_Weapon_TiberiumAutoRifle;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("TiberiumAutoRifle_Blue"))) return translated_Weapon_TiberiumAutoRifle_Blue;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("EMPGrenade"))) return translated_Weapon_EMPGrenade;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("SmokeGrenade"))) return translated_Weapon_SmokeGrenade;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("TimedC4"))) return translated_Weapon_TimedC4;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("RemoteC4"))) return translated_Weapon_RemoteC4;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("ProxyC4"))) return translated_Weapon_ProxyC4;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("ATMine"))) return translated_Weapon_ATMine;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("IonCannonBeacon"))) return translated_Weapon_IonCannonBeacon;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("NukeBeacon"))) return translated_Weapon_NukeBeacon;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("DeployedC4"))) return translated_Weapon_DeployedC4;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("DeployedTimedC4"))) return translated_Weapon_DeployedTimedC4;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("DeployedRemoteC4"))) return translated_Weapon_DeployedRemoteC4;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("DeployedProxyC4"))) return translated_Weapon_DeployedProxyC4;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("DeployedATMine"))) return translated_Weapon_DeployedATMine;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("DeployedIonCannonBeacon"))) return translated_Weapon_DeployedIonCannonBeacon;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("DeployedNukeBeacon"))) return translated_Weapon_DeployedNukeBeacon;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("CrateNuke"))) return translated_Weapon_CrateNuke;
	}
	else if (object.find(STRING_LITERAL_AS_REFERENCE("Projectile_")) == 0)
	{
		object.shiftRight(11);
		if (object.equals(STRING_LITERAL_AS_REFERENCE("EMPGrenade"))) return translated_Projectile_EMPGrenade;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("SmokeGrenade"))) return translated_Projectile_SmokeGrenade;
	}
	else if (object.find(STRING_LITERAL_AS_REFERENCE("InventoryManager_")) == 0)
	{
		object.shiftRight(17);
		return translateCharacter(object);
	}
	else if (object.find(STRING_LITERAL_AS_REFERENCE("FamilyInfo_")) == 0)
	{
		object.shiftRight(11);
		return translateCharacter(object);
	}
	else if (object.find(STRING_LITERAL_AS_REFERENCE("DmgType_")) == 0)
	{
		object.shiftRight(8);

		/** Non-weapon damage types */
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Suicided"))) return translated_DmgType_Suicided;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Fell"))) return translated_DmgType_Fell;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Tiberium"))) return translated_DmgType_Tiberium;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("TiberiumBleed"))) return translated_DmgType_TiberiumBleed;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("TiberiumBleed_Blue"))) return translated_DmgType_TiberiumBleed_Blue;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("RanOver"))) return translated_DmgType_RanOver;

		/** Infantry weapons */
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Pistol"))) return translated_DmgType_Pistol;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("SMG"))) return translated_DmgType_SMG;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("HeavyPistol"))) return translated_DmgType_HeavyPistol;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Carbine"))) return translated_DmgType_Carbine;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("TiberiumFlechetteRifle"))) return translated_DmgType_TiberiumFlechetteRifle; // Not a rifle.
		if (object.equals(STRING_LITERAL_AS_REFERENCE("TiberiumAutoRifle"))) return translated_DmgType_TiberiumAutoRifle;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("TiberiumAutoRifle_Blue"))) return translated_DmgType_TiberiumAutoRifle_Blue;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("TiberiumAutoRifle_Flechette_Blue"))) return translated_DmgType_TiberiumAutoRifle_Flechette_Blue;

		if (object.equals(STRING_LITERAL_AS_REFERENCE("Grenade"))) return translated_DmgType_Grenade;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("TimedC4"))) return translated_DmgType_TimedC4;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("RemoteC4"))) return translated_DmgType_RemoteC4;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("ProxyC4"))) return translated_DmgType_ProxyC4;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("ATMine"))) return translated_DmgType_ATMine;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("EMPGrenade"))) return translated_DmgType_EMPGrenade;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("BurnC4"))) return translated_DmgType_BurnC4;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("FireBleed"))) return translated_DmgType_FireBleed; // Caused by C4 or flame weapons

		if (object.equals(STRING_LITERAL_AS_REFERENCE("AutoRifle"))) return translated_DmgType_AutoRifle;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Shotgun"))) return translated_DmgType_Shotgun;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("FlameThrower"))) return translated_DmgType_FlameThrower;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("GrenadeLauncher"))) return translated_DmgType_GrenadeLauncher;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("MarksmanRifle"))) return translated_DmgType_MarksmanRifle;

		if (object.equals(STRING_LITERAL_AS_REFERENCE("ChainGun"))) return translated_DmgType_ChainGun;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("MissileLauncher"))) return translated_DmgType_MissileLauncher;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("MissileLauncher_Alt"))) return translated_DmgType_MissileLauncher_Alt;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("ChemicalThrower"))) return translated_DmgType_ChemicalThrower;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("LaserRifle"))) return translated_DmgType_LaserRifle;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("TacticalRifle"))) return translated_DmgType_TacticalRifle;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("RocketLauncher"))) return translated_DmgType_RocketLauncher;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("LaserChainGun"))) return translated_DmgType_LaserChainGun;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("FlakCannon"))) return translated_DmgType_FlakCannon;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("FlakCannon_Alt"))) return translated_DmgType_FlakCannon_Alt;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("SniperRifle"))) return translated_DmgType_SniperRifle;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("RamjetRifle"))) return translated_DmgType_RamjetRifle;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Railgun"))) return translated_DmgType_Railgun;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("PersonalIonCannon"))) return translated_DmgType_PersonalIonCannon;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("VoltRifle"))) return translated_DmgType_VoltRifle;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("VoltRifle_Alt"))) return translated_DmgType_VoltRifle_Alt;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("VoltAutoRifle"))) return translated_DmgType_VoltAutoRifle;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("VoltAutoRifle_Alt"))) return translated_DmgType_VoltAutoRifle_Alt;

		/** Vehicle weapons */
		if (object.equals(STRING_LITERAL_AS_REFERENCE("MammothTank_Missile"))) return translated_DmgType_MammothTank_Missile;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("MammothTank_Cannon"))) return translated_DmgType_MammothTank_Cannon;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Orca_Missile"))) return translated_DmgType_Orca_Missile;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Orca_Gun"))) return translated_DmgType_Orca_Gun;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Orca_Passenger"))) return translated_DmgType_Orca_Passenger;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Apache_Rocket"))) return translated_DmgType_Apache_Rocket;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Apache_Gun"))) return translated_DmgType_Apache_Gun;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Apache_Passenger"))) return translated_DmgType_Apache_Passenger;

		/** Base Defence Weapons */
		if (object.equals(STRING_LITERAL_AS_REFERENCE("AGT_MG"))) return translated_DmgType_AGT_MG;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("AGT_Rocket"))) return translated_DmgType_AGT_Rocket;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Obelisk"))) return translated_DmgType_Obelisk;

		/** Defence Structure Weapons */
		if (object.equals(STRING_LITERAL_AS_REFERENCE("AGT_MG"))) return translated_DmgType_AGT_MG;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("AGT_Rocket"))) return translated_DmgType_AGT_Rocket;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Obelisk"))) return translated_DmgType_Obelisk;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("GuardTower"))) return translated_DmgType_GuardTower;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Turret"))) return translated_DmgType_Turret;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("SAMSite"))) return translated_DmgType_SAMSite;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("AATower"))) return translated_DmgType_AATower;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("GunEmpl"))) return translated_DmgType_GunEmpl;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("GunEmpl_Alt"))) return translated_DmgType_GunEmpl_Alt;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("RocketEmpl_Swarm"))) return translated_DmgType_RocketEmpl_Swarm;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("RocketEmpl_Missile"))) return translated_DmgType_RocketEmpl_Missile;

		/** Other Weapons */
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Nuke"))) return translated_DmgType_Nuke;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("IonCannon"))) return translated_DmgType_IonCannon;

		/** Nod Vehicles */
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Harvester_Nod"))) return translated_DmgType_Harvester_Nod;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Buggy"))) return translated_DmgType_Buggy;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Artillery"))) return translated_DmgType_Artillery;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("APC_Nod"))) return translated_DmgType_APC_Nod;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("LightTank"))) return translated_DmgType_LightTank;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("FlameTank"))) return translated_DmgType_FlameTank;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("StealthTank"))) return translated_DmgType_StealthTank;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Chinook_Nod"))) return translated_DmgType_Chinook_Nod;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Apache"))) return translated_DmgType_Apache;

		/** GDI Vehicles */
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Harvester_GDI"))) return translated_DmgType_Harvester_GDI;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Humvee"))) return translated_DmgType_Humvee;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("MRLS"))) return translated_DmgType_MRLS;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("APC_GDI"))) return translated_DmgType_APC_GDI;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("MediumTank"))) return translated_DmgType_MediumTank;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("MammothTank"))) return translated_DmgType_MammothTank;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Chinook_GDI"))) return translated_DmgType_Chinook_GDI;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Orca"))) return translated_DmgType_Orca;

		/** Other Vehicles */
		if (object.equals(STRING_LITERAL_AS_REFERENCE("A10_Missile"))) return translated_DmgType_A10_Missile;
	}
	else if (object.find(STRING_LITERAL_AS_REFERENCE("Building_")) == 0)
	{
		object.shiftRight(9);
		/** Nod structures */
		if (object.equals(STRING_LITERAL_AS_REFERENCE("HandOfNod"))) return translated_Building_HandOfNod;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("AirTower"))) return translated_Building_AirTower;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Airstrip"))) return translated_Building_Airstrip;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Refinery_Nod"))) return translated_Building_Refinery_Nod;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("PowerPlant_Nod"))) return translated_Building_PowerPlant_Nod;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("HandOfNod_Internals"))) return translated_Building_HandOfNod_Internals;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("AirTower_Internals"))) return translated_Building_AirTower_Internals;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Airstrip_Internals"))) return translated_Building_Airstrip_Internals;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Refinery_Nod_Internals"))) return translated_Building_Refinery_Nod_Internals;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("PowerPlant_Nod_Internals"))) return translated_Building_PowerPlant_Nod_Internals;
		
		/** GDI structures */
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Barracks"))) return translated_Building_Barracks;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("WeaponsFactory"))) return translated_Building_WeaponsFactory;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Refinery_GDI"))) return translated_Building_Refinery_GDI;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("PowerPlant_GDI"))) return translated_Building_PowerPlant_GDI;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Barracks_Internals"))) return translated_Building_Barracks_Internals;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("WeaponsFactory_Internals"))) return translated_Building_WeaponsFactory_Internals;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Refinery_GDI_Internals"))) return translated_Building_Refinery_GDI_Internals;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("PowerPlant_GDI_Internals"))) return translated_Building_PowerPlant_GDI_Internals;

		/** Defense structures */
		if (object.equals(STRING_LITERAL_AS_REFERENCE("AdvancedGuardTower"))) return translated_Building_AdvancedGuardTower;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Obelisk"))) return translated_Building_Obelisk;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("AdvancedGuardTower_Internals"))) return translated_Building_AdvancedGuardTower_Internals;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Obelisk_Internals"))) return translated_Building_Obelisk_Internals;

		/** Other structures */
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Silo"))) return translated_Building_Silo;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("CommCentre"))) return translated_Building_CommCentre;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Silo_Internals"))) return translated_Building_Silo_Internals;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("CommCentre_Internals"))) return translated_Building_CommCentre_Internals;
	}
	else if (object.find(STRING_LITERAL_AS_REFERENCE("CapturableMCT_")) == 0)
	{
		object.shiftRight(14);
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Fort"))) return translated_CapturableMCT_Fort;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("MC"))) return translated_CapturableMCT_MC;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Fort_Internals"))) return translated_CapturableMCT_Fort_Internals;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("MC_Internals"))) return translated_CapturableMCT_MC_Internals;
	}
	else if (object.find(STRING_LITERAL_AS_REFERENCE("Defence_")) == 0)
	{
		object.shiftRight(8);
		if (object.equals(STRING_LITERAL_AS_REFERENCE("GuardTower"))) return translated_Defence_GuardTower;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Turret"))) return translated_Defence_Turret;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("SAMSite"))) return translated_Defence_SAMSite;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("AATower"))) return translated_Defence_AATower;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("GunEmplacement"))) return translated_Defence_GunEmplacement;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("RocketEmplacement"))) return translated_Defence_RocketEmplacement;
	}
	else if (object.find(STRING_LITERAL_AS_REFERENCE("Sentinel_")) == 0)
	{
		object.shiftRight(9);
		if (object.equals(STRING_LITERAL_AS_REFERENCE("AGT_MG_Base"))) return translated_Sentinel_AGT_MG_Base;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("AGT_Rockets_Base"))) return translated_Sentinel_AGT_Rockets_Base;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Obelisk_Laser_Base"))) return translated_Sentinel_Obelisk_Laser_Base;
	}
	else if (object.find(STRING_LITERAL_AS_REFERENCE("UTDmgType_")) == 0)
	{
		object.shiftRight(10);
		if (object.equals(STRING_LITERAL_AS_REFERENCE("VehicleExplosion"))) return translated_UTDmgType_VehicleExplosion;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Drowned"))) return translated_UTDmgType_Drowned;
	}
	else if (object.find(STRING_LITERAL_AS_REFERENCE("VoteMenuChoice_")) == 0)
	{
		object.shiftRight(15);
		if (object.equals(STRING_LITERAL_AS_REFERENCE("AddBots"))) return translated_VoteMenuChoice_AddBots;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("ChangeMap"))) return translated_VoteMenuChoice_ChangeMap;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Donate"))) return translated_VoteMenuChoice_Donate;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Kick"))) return translated_VoteMenuChoice_Kick;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("RemoveBots"))) return translated_VoteMenuChoice_RemoveBots;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("RestartMatch"))) return translated_VoteMenuChoice_RestartMatch;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("StartMatch"))) return translated_VoteMenuChoice_StartMatch;
		if (object.equals(STRING_LITERAL_AS_REFERENCE("Survey"))) return translated_VoteMenuChoice_Survey;
	}
	else if (object.equals(STRING_LITERAL_AS_REFERENCE("IonCannonBeacon"))) return translated_IonCannonBeacon;
	else if (object.equals(STRING_LITERAL_AS_REFERENCE("NukeBeacon"))) return translated_NukeBeacon;
	else if (object.equals(STRING_LITERAL_AS_REFERENCE("KillZDamageType"))) return translated_KillZDamageType;
	return translateCharacter(object);
}

const Jupiter::ReadableString &RenX::translateWinType(RenX::WinType winType)
{
	switch (winType)
	{
	case RenX::WinType::Score:
		return scoreWinTypeTranslation;
	case RenX::WinType::Base:
		return baseWinTypeTranslation;
	case RenX::WinType::Beacon:
		return beaconWinTypeTranslation;
	case RenX::WinType::Tie:
		return tieWinTypeTranslation;
	case RenX::WinType::Shutdown:
		return shutdownWinTypeTranslation;
	case RenX::WinType::Surrender:
		return surrenderWinTypeTranslation;
	case RenX::WinType::Unknown:
	default:
		return unknownWinTypeTranslation;
	}
}

const Jupiter::ReadableString &RenX::translateWinTypePlain(RenX::WinType winType)
{
	switch (winType)
	{
	case RenX::WinType::Score:
		return scoreWinTypePlainTranslation;
	case RenX::WinType::Base:
		return baseWinTypePlainTranslation;
	case RenX::WinType::Beacon:
		return beaconWinTypePlainTranslation;
	case RenX::WinType::Tie:
		return tieWinTypePlainTranslation;
	case RenX::WinType::Shutdown:
		return shutdownWinTypePlainTranslation;
	case RenX::WinType::Surrender:
		return surrenderWinTypePlainTranslation;
	case RenX::WinType::Unknown:
	default:
		return unknownWinTypePlainTranslation;
	}
}

void RenX::initTranslations(Jupiter::Config &translationsFile)
{
	NodColor = translationsFile["TeamColor"_jrs].get("Nod"_jrs, "04"_jrs);
	GDIColor = translationsFile["TeamColor"_jrs].get("GDI"_jrs, "08"_jrs);
	OtherColor = translationsFile["TeamColor"_jrs].get("Other"_jrs, "14"_jrs);

	NodShortName = translationsFile["ShortTeamName"_jrs].get("Nod"_jrs, "Nod"_jrs);
	GDIShortName = translationsFile["ShortTeamName"_jrs].get("GDI"_jrs, "GDI"_jrs);
	OtherShortName = translationsFile["ShortTeamName"_jrs].get("Other"_jrs, "N/A"_jrs);
	NodLongName = translationsFile["LongTeamName"_jrs].get("Nod"_jrs, "Brotherhood of Nod"_jrs);
	GDILongName = translationsFile["LongTeamName"_jrs].get("GDI"_jrs, "Global Defense Initiative"_jrs);
	OtherLongName = translationsFile["LongTeamName"_jrs].get("Other"_jrs, "Unknown"_jrs);

	scoreWinTypeTranslation = translationsFile["WinType"_jrs].get("Score"_jrs, "Domination (High Score)"_jrs);
	baseWinTypeTranslation = translationsFile["WinType"_jrs].get("Base"_jrs, "Conquest (Base Destruction)"_jrs);
	beaconWinTypeTranslation = translationsFile["WinType"_jrs].get("Beacon"_jrs, "Espionage (Beacon)"_jrs);
	tieWinTypeTranslation = translationsFile["WinType"_jrs].get("Tie"_jrs, "Draw (Tie)"_jrs);
	shutdownWinTypeTranslation = translationsFile["WinType"_jrs].get("Shutdown"_jrs, "Ceasefire (Shutdown)"_jrs);
	surrenderWinTypeTranslation = translationsFile["WinType"_jrs].get("Surrender"_jrs, "Forfeit (Surrender)"_jrs);
	unknownWinTypeTranslation = translationsFile["WinType"_jrs].get("Unknown"_jrs, "Aliens (Unknown)"_jrs);

	scoreWinTypePlainTranslation = translationsFile["WinTypePlain"_jrs].get("Score"_jrs, "High Score"_jrs);
	baseWinTypePlainTranslation = translationsFile["WinTypePlain"_jrs].get("Base"_jrs, "Base Destruction"_jrs);
	beaconWinTypePlainTranslation = translationsFile["WinTypePlain"_jrs].get("Beacon"_jrs, "Beacon"_jrs);
	tieWinTypePlainTranslation = translationsFile["WinTypePlain"_jrs].get("Tie"_jrs, "Tie"_jrs);
	shutdownWinTypePlainTranslation = translationsFile["WinTypePlain"_jrs].get("Shutdown"_jrs, "Shutdown"_jrs);
	surrenderWinTypePlainTranslation = translationsFile["WinTypePlain"_jrs].get("Surrender"_jrs, "Surrender"_jrs);
	unknownWinTypePlainTranslation = translationsFile["WinTypePlain"_jrs].get("Unknown"_jrs, "Unknown"_jrs);
}

Jupiter::String RenX::getFormattedPlayerName(const RenX::PlayerInfo &player)
{
	Jupiter::String r = player.formatNamePrefix;
	r += IRCCOLOR;
	r += RenX::getTeamColor(player.team);
	r += player.name;
	return r;
}

Jupiter::StringS RenX::formatGUID(const RenX::Map &map)
{
	return Jupiter::StringS::Format("%.16llX%.16llX", map.guid[0], map.guid[1]);
}

std::chrono::milliseconds RenX::getServerTime(const RenX::PlayerInfo &player)
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - player.joinTime);
}

Jupiter::StringS RenX::default_uuid_func(RenX::PlayerInfo &player)
{
	if (player.steamid != 0U)
		return Jupiter::StringS::Format("0x%.16llX", player.steamid);

	return Jupiter::StringS();
}

double RenX::getKillDeathRatio(const RenX::PlayerInfo &player, bool includeSuicides)
{
	double deaths = player.deaths;

	if (includeSuicides == false)
		deaths -= player.suicides;

	if (deaths == 0)
		deaths = 1;

	return static_cast<double>(player.kills) / deaths;
}

double RenX::getHeadshotKillRatio(const RenX::PlayerInfo &player)
{
	if (player.kills == 0)
		return 0;

	return static_cast<double>(player.headshots) / static_cast<double>(player.kills);
}

Jupiter::String RenX::escapifyRCON(const Jupiter::ReadableString &str)
{
	const char *ptr = str.ptr();
	size_t length = str.size();
	Jupiter::String result(str.size() + 32);
	uint16_t value;

	while (length != 0)
	{
		if ((*ptr & 0x80) != 0) // UTF-8 sequence
		{
			if (length < 2)
				break;

			if ((*ptr & 0x40) != 0) // validity check
			{
				// get codepoint value
				if ((*ptr & 0x20) != 0)
				{
					if (length < 3)
						break;

					if ((*ptr & 0x10) != 0) // This is a 4 byte sequence, which we can not fit into a 16-bit codepoint. ignore it.
					{
						if (length < 4)
							break;

						ptr += 4;
						length -= 4;
						continue;
					}
					else
					{
						// this is a 3 byte sequence
						value = (*ptr & 0x0F) << 12;
						value += (*++ptr & 0x3F) << 6;
						value += *++ptr & 0x3F;

						length -= 3;
					}
				}
				else
				{
					// This is a 2 byte sequence
					value = (*ptr & 0x1F) << 6;
					value += *++ptr & 0x3F;

					length -= 2;
				}

				// write escape sequence
				result += '\\';
				result += 'u';
				result += Jupiter_asHex_upper(value >> 8);
				result += Jupiter_asHex_upper(value & 0x00FF);
			}
			// else // This is an invalid 1 byte sequence
		}
		else if (*ptr == '\\') // backslash, which is used for escape sequencing
		{
			result += '\\';
			result += '\\';
			--length;
		}
		else // an ordinary character
		{
			result += *ptr;
			--length;
		}

		++ptr;
	}
	return result;
}
