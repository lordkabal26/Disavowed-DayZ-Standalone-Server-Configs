void main()
{
	//INIT WEATHER BEFORE ECONOMY INIT------------------------
	Weather weather = g_Game.GetWeather();

	weather.MissionWeather(false);    // false = use weather controller from Weather.c

	weather.GetOvercast().Set( Math.RandomFloatInclusive(0.4, 0.6), 1, 0);
	weather.GetRain().Set( 0, 0, 1);
	weather.GetFog().Set( Math.RandomFloatInclusive(0.05, 0.1), 1, 0);

	//INIT ECONOMY--------------------------------------
	Hive ce = CreateHive();
	if ( ce )
		ce.InitOffline();

	//DATE RESET AFTER ECONOMY INIT-------------------------
	int year, month, day, hour, minute;
	int reset_month = 5, reset_day = 20;
	GetGame().GetWorld().GetDate(year, month, day, hour, minute);

	if ((month == reset_month) && (day < reset_day))
	{
		GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
	}
	else
	{
		if ((month == reset_month + 1) && (day > reset_day))
		{
			GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
		}
		else
		{
			if ((month < reset_month) || (month > reset_month + 1))
			{
			GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
			}
		}
	}
//	GetCEApi().ExportProxyData( "5120 0 5120", 10240 );  			// Generate mapgrouppos.xml
//	GetCEApi().ExportClusterData();							// Generate mapgroupcluster.xml
}

class CustomMission: MissionServer
{
	void SetRandomHealth(EntityAI itemEnt)
	{
		if ( itemEnt )
		{
			float rndHlt = Math.RandomFloat( 0.45, 0.65 );
			itemEnt.SetHealth01( "", "", rndHlt );
		}
	}

	override PlayerBase CreateCharacter(PlayerIdentity identity, vector pos, ParamsReadContext ctx, string characterName)
	{
		Entity playerEnt;
		playerEnt = GetGame().CreatePlayer( identity, characterName, pos, 0, "NONE" );
		Class.CastTo( m_player, playerEnt );

		GetGame().SelectPlayer( identity, m_player );

		return m_player;
	}

	override void StartingEquipSetup(PlayerBase player, bool clothesChosen)
	{
		EntityAI itemTop;
		EntityAI itemEnt;
		ItemBase itemBs;
		float rand;
		
		itemTop = player.FindAttachmentBySlotName("Body");
		
		if ( itemTop )
		{
			// The following comment block is the default spawning loadout
			/*itemEnt = itemTop.GetInventory().CreateInInventory("Rag");
			if ( Class.CastTo(itemBs, itemEnt ) )
			itemBs.SetQuantity(4);

			SetRandomHealth(itemEnt);
			
			itemEnt = itemTop.GetInventory().CreateInInventory("RoadFlare");
			SetRandomHealth(itemEnt);*/
			
			//Below is the custom code Is for custom spawning loadouts
			EntityAI attachEnt;
			Weapon_Base pGun;
			
			player.RemoveAllItems(); //removes all base items the game would have spawned the player with so we can work with a blank slate
			
			//This block assigns this set of items to ALL players that spawn in. The order is important because the belt has attachment slots, adding it first, and the other items after will attach direct to the belt since there are no other valid inventory slots to place the items in.
			itemEnt = player.GetInventory().CreateInInventory("CivilianBelt"); itemBs = ItemBase.Cast(itemEnt); //note that the name of the item has to be in quotes and the exact name that's found for the item in the types.xml file in the directory mpmissions/dayzOffline.chernarusplus/db/types.xml
			itemEnt = player.GetInventory().CreateInInventory("Canteen"); itemBs = ItemBase.Cast(itemEnt);
			itemEnt = player.GetInventory().CreateInInventory("NylonKnifeSheath"); itemBs = ItemBase.Cast(itemEnt);
			itemEnt = player.GetInventory().CreateInInventory("HuntingKnife"); itemBs = ItemBase.Cast(itemEnt);
			
			//There are 20 loadouts that it will give at random, the line after this generates a random number from 0 to 19. The number it generates is then the sleceted Case number, and the loadout that will be assigned
			switch (Math.RandomInt(0, 19)) 
			{ 
			case 0:
				//Dress Troll
				itemEnt = player.GetInventory().CreateInInventory("DressShoes_Sunburst"); itemBs = ItemBase.Cast(itemEnt); // this is the ceneral form for adding an item to the players inventory
				pGun = player.GetInventory().CreateInInventory("SawedoffMosin9130"); itemBs = ItemBase.Cast(pGun); //I used the pGun variable declared above for all the guns just to make things simpler to work out in my head
				itemEnt = player.GetInventory().CreateInInventory("DesignerGlasses"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("MiniDress_Pink"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("Ammo_762x54"); itemBs = ItemBase.Cast(itemEnt);
				player.SetQuickBarEntityShortcut(itemEnt, 1, true); // this line sets the previously added item to be #2 in the action bar. In this case, a stack of 7.62x54mm ammo for the Mosin
				itemEnt = player.GetInventory().CreateInInventory("Ammo_762x54"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("ChildBag_Red"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("M67Grenade"); itemBs = ItemBase.Cast(itemEnt);
			
				player.SetQuickBarEntityShortcut(pGun, 0, true); //this line sets the gun to be in the #1 action bar slot
			break; 
			case 1:
				//Light Gunner
				itemEnt = player.GetInventory().CreateInInventory("AthleticShoes_Black"); itemBs = ItemBase.Cast(itemEnt);
				pGun = player.GetInventory().CreateInInventory("MP5K"); itemBs = ItemBase.Cast(itemEnt); // added the gun before any backpacks so attachments would be added to the gun and not in the players inventory
				itemEnt = player.GetInventory().CreateInInventory("MP5_RailHndgrd"); itemBs = ItemBase.Cast(itemEnt); //doing this before adding inventory spaces ensured the attachment was on the gun by default
				itemEnt = player.GetInventory().CreateInInventory("MP5k_StockBttstck"); itemBs = ItemBase.Cast(itemEnt); // same thing with the buttstock for the gun
				itemEnt = player.GetInventory().CreateInInventory("MP5_Compensator"); itemBs = ItemBase.Cast(itemEnt); // and the compensator
				itemEnt = player.GetInventory().CreateInInventory("BoonieHat_Black"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("TrackSuitJacket_Black"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("TrackSuitPants_Black"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("Mag_MP5_30Rnd"); itemBs = ItemBase.Cast(itemEnt); // note that when spawnin players with mags, they are full by default
				player.SetQuickBarEntityShortcut(itemEnt, 1, true);
				itemEnt = player.GetInventory().CreateInInventory("Mag_MP5_30Rnd"); itemBs = ItemBase.Cast(itemEnt);
				player.SetQuickBarEntityShortcut(itemEnt, 2, true);
				itemEnt = player.GetInventory().CreateInInventory("Mag_MP5_30Rnd"); itemBs = ItemBase.Cast(itemEnt);
				player.SetQuickBarEntityShortcut(itemEnt, 3, true);
				itemEnt = player.GetInventory().CreateInInventory("Ammo_9x19"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("HighCapacityVest_Black"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("TacticalBaconCan_Opened"); itemBs = ItemBase.Cast(itemEnt);
				
				player.SetQuickBarEntityShortcut(pGun, 0, true);
			break; 
			case 2:
				//Armored Pistoleer
				itemEnt = player.GetInventory().CreateInInventory("CombatBoots_Green"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("BallisticHelmet_UN"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("PlateCarrierVest"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("AviatorGlasses"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("TTsKOJacket_Camo"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("TTSKOPants"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("AssaultBag_Green"); itemBs = ItemBase.Cast(itemEnt);
				pGun = player.GetInventory().CreateInInventory("FNX45"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("Mag_FNX45_15Rnd"); itemBs = ItemBase.Cast(itemEnt);
				player.SetQuickBarEntityShortcut(itemEnt, 1, true);
				itemEnt = player.GetInventory().CreateInInventory("Mag_FNX45_15Rnd"); itemBs = ItemBase.Cast(itemEnt);
				player.SetQuickBarEntityShortcut(itemEnt, 2, true);
				itemEnt = player.GetInventory().CreateInInventory("Mag_FNX45_15Rnd"); itemBs = ItemBase.Cast(itemEnt);
				player.SetQuickBarEntityShortcut(itemEnt, 3, true);
				itemEnt = player.GetInventory().CreateInInventory("Mag_FNX45_15Rnd"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("Mag_FNX45_15Rnd"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("Ammo_45ACP"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("Ammo_45ACP"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("Ammo_45ACP"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("Ammo_45ACP"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("TacticalBaconCan_Opened"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("TacticalBaconCan_Opened"); itemBs = ItemBase.Cast(itemEnt);

				player.SetQuickBarEntityShortcut(pGun, 0, true);
			break; 
			case 3:
				//Sniper 1
				itemEnt = player.GetInventory().CreateInInventory("JoggingShoes_Red"); itemBs = ItemBase.Cast(itemEnt);
				pGun = player.GetInventory().CreateInInventory("SVD"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("PSO11Optic"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("Battery9V"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("BoonieHat_Red"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("SportGlasses_Orange"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("JumpsuitJacket_Red"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("JumpsuitPants_Red"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("DryBag_Red"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("Mag_SVD_10Rnd"); itemBs = ItemBase.Cast(itemEnt);
				player.SetQuickBarEntityShortcut(itemEnt, 1, true);
				itemEnt = player.GetInventory().CreateInInventory("Mag_SVD_10Rnd"); itemBs = ItemBase.Cast(itemEnt);
				player.SetQuickBarEntityShortcut(itemEnt, 2, true);
				itemEnt = player.GetInventory().CreateInInventory("Ammo_762x54"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("Ammo_762x54"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("TacticalBaconCan_Opened"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("TacticalBaconCan_Opened"); itemBs = ItemBase.Cast(itemEnt);
				
				player.SetQuickBarEntityShortcut(pGun, 0, true);
			break; 
			case 4:
				//Sniper 2
				itemEnt = player.GetInventory().CreateInInventory("CombatBoots_Green"); itemBs = ItemBase.Cast(itemEnt);
				pGun = player.GetInventory().CreateInInventory("Mosin9130"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("PUScopeOptic"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("Ushanka_Blue"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("SportGlasses_Blue"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("JumpsuitJacket_Blue"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("JumpsuitPants_Blue"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("DryBag_Blue"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("Ammo_762x54"); itemBs = ItemBase.Cast(itemEnt);
				player.SetQuickBarEntityShortcut(itemEnt, 1, true);
				itemEnt = player.GetInventory().CreateInInventory("Ammo_762x54"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("Ammo_762x54"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("TacticalBaconCan_Opened"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("TacticalBaconCan_Opened"); itemBs = ItemBase.Cast(itemEnt);
				
				player.SetQuickBarEntityShortcut(pGun, 0, true);
			break; 
			case 5:
				// Sniper 3
				itemEnt = player.GetInventory().CreateInInventory("CombatBoots_Green"); itemBs = ItemBase.Cast(itemEnt);
				pGun = player.GetInventory().CreateInInventory("SKS"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("PUScopeOptic"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("BeanieHat_Green"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("SportGlasses_Green"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("Raincoat_Yellow"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("CargoPants_Green"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("DryBag_Green"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("Ammo_762x39Tracer"); itemBs = ItemBase.Cast(itemEnt);
				player.SetQuickBarEntityShortcut(itemEnt, 1, true);
				itemEnt = player.GetInventory().CreateInInventory("Ammo_762x39Tracer"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("Ammo_762x39Tracer"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("Ammo_762x39Tracer"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("TacticalBaconCan_Opened"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("TacticalBaconCan_Opened"); itemBs = ItemBase.Cast(itemEnt);
				
				player.SetQuickBarEntityShortcut(pGun, 0, true);
			break; 
			case 6:
				// Sniper 4
				itemEnt = player.GetInventory().CreateInInventory("CombatBoots_Green"); itemBs = ItemBase.Cast(itemEnt);
				pGun = player.GetInventory().CreateInInventory("CZ527"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("HuntingOptic"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("SantasHat"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("AviatorGlasses"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("ChernarusSportShirt"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("ShortJeans_Green"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("HuntingBag"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("Mag_CZ527_5rnd"); itemBs = ItemBase.Cast(itemEnt);
				player.SetQuickBarEntityShortcut(itemEnt, 1, true);
				itemEnt = player.GetInventory().CreateInInventory("Mag_CZ527_5rnd"); itemBs = ItemBase.Cast(itemEnt);
				player.SetQuickBarEntityShortcut(itemEnt, 2, true);
				itemEnt = player.GetInventory().CreateInInventory("Mag_CZ527_5rnd"); itemBs = ItemBase.Cast(itemEnt);
				player.SetQuickBarEntityShortcut(itemEnt, 3, true);
				itemEnt = player.GetInventory().CreateInInventory("Mag_CZ527_5rnd"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("Ammo_762x39"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("Ammo_762x39"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("Ammo_762x39"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("TacticalBaconCan_Opened"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("TacticalBaconCan_Opened"); itemBs = ItemBase.Cast(itemEnt);
				
				player.SetQuickBarEntityShortcut(pGun, 0, true);
			break; 
			case 7:
				//Assault 1
				itemEnt = player.GetInventory().CreateInInventory("JungleBoots_Black"); itemBs = ItemBase.Cast(itemEnt);
				pGun = player.GetInventory().CreateInInventory("AK74"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("AK_PlasticBttstck"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("AK_RailHndgrd"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("BaseballCap_Black"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("UKAssVest_Black"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("AviatorGlasses"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("M65Jacket_Black"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("CargoPants_Black"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("AssaultBag_Black"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("TacticalGloves_Black"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("Mag_AK74_30Rnd"); itemBs = ItemBase.Cast(itemEnt);
				player.SetQuickBarEntityShortcut(itemEnt, 1, true);
				itemEnt = player.GetInventory().CreateInInventory("Mag_AK74_30Rnd"); itemBs = ItemBase.Cast(itemEnt);
				player.SetQuickBarEntityShortcut(itemEnt, 2, true);
				itemEnt = player.GetInventory().CreateInInventory("Mag_AK74_30Rnd"); itemBs = ItemBase.Cast(itemEnt);
				player.SetQuickBarEntityShortcut(itemEnt, 3, true);
				itemEnt = player.GetInventory().CreateInInventory("TacticalBaconCan_Opened"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("TacticalBaconCan_Opened"); itemBs = ItemBase.Cast(itemEnt);
				
				player.SetQuickBarEntityShortcut(pGun, 0, true);
			break; 
			case 8:
				//Assault 2
				itemEnt = player.GetInventory().CreateInInventory("JungleBoots_Green"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("BaseballCap_Olive"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("UKAssVest_Olive"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("AviatorGlasses"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("M65Jacket_Olive"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("CargoPants_Green"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("AssaultBag_Green"); itemBs = ItemBase.Cast(itemEnt);
				pGun = player.GetInventory().CreateInInventory("UMP45"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("TacticalGloves_Green"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("Mag_UMP_25Rnd"); itemBs = ItemBase.Cast(itemEnt);
				player.SetQuickBarEntityShortcut(itemEnt, 1, true);
				itemEnt = player.GetInventory().CreateInInventory("Mag_UMP_25Rnd"); itemBs = ItemBase.Cast(itemEnt);
				player.SetQuickBarEntityShortcut(itemEnt, 2, true);
				itemEnt = player.GetInventory().CreateInInventory("Mag_UMP_25Rnd"); itemBs = ItemBase.Cast(itemEnt);
				player.SetQuickBarEntityShortcut(itemEnt, 3, true);
				itemEnt = player.GetInventory().CreateInInventory("Mag_UMP_25Rnd"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("TacticalBaconCan_Opened"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("TacticalBaconCan_Opened"); itemBs = ItemBase.Cast(itemEnt);
				
				player.SetQuickBarEntityShortcut(pGun, 0, true);
			break; 
			case 9:
				//Assault 3
				itemEnt = player.GetInventory().CreateInInventory("CombatBoots_Grey"); itemBs = ItemBase.Cast(itemEnt);
				pGun = player.GetInventory().CreateInInventory("AK101"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("AK_PlasticBttstck"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("AK_RailHndgrd"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("BaseballCap_Beige"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("UKAssVest_Khaki"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("AviatorGlasses"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("M65Jacket_Khaki"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("CargoPants_Beige"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("CoyoteBag_Brown"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("TacticalGloves_Beige"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("Mag_AK101_30Rnd"); itemBs = ItemBase.Cast(itemEnt);
				player.SetQuickBarEntityShortcut(itemEnt, 1, true);
				itemEnt = player.GetInventory().CreateInInventory("Mag_AK101_30Rnd"); itemBs = ItemBase.Cast(itemEnt);
				player.SetQuickBarEntityShortcut(itemEnt, 2, true);
				itemEnt = player.GetInventory().CreateInInventory("Mag_AK101_30Rnd"); itemBs = ItemBase.Cast(itemEnt);
				player.SetQuickBarEntityShortcut(itemEnt, 3, true);
				itemEnt = player.GetInventory().CreateInInventory("TacticalBaconCan_Opened"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("TacticalBaconCan_Opened"); itemBs = ItemBase.Cast(itemEnt);
				
				player.SetQuickBarEntityShortcut(pGun, 0, true);
			break; 
			case 10:
				//Rusher 1
				itemEnt = player.GetInventory().CreateInInventory("JoggingShoes_Black"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("FlatCap_Black"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("Breeches_Black"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("AssaultBag_Black"); itemBs = ItemBase.Cast(itemEnt);
				pGun = player.GetInventory().CreateInInventory("CZ61"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("Machete"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("Mag_CZ61_20Rnd"); itemBs = ItemBase.Cast(itemEnt);
				player.SetQuickBarEntityShortcut(itemEnt, 1, true);
				itemEnt = player.GetInventory().CreateInInventory("Mag_CZ61_20Rnd"); itemBs = ItemBase.Cast(itemEnt);
				player.SetQuickBarEntityShortcut(itemEnt, 2, true);
				itemEnt = player.GetInventory().CreateInInventory("Mag_CZ61_20Rnd"); itemBs = ItemBase.Cast(itemEnt);
				player.SetQuickBarEntityShortcut(itemEnt, 3, true);
				itemEnt = player.GetInventory().CreateInInventory("Ammo_380"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("Ammo_380"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("Ammo_380"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("TacticalBaconCan_Opened"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("TacticalBaconCan_Opened"); itemBs = ItemBase.Cast(itemEnt);
				
				player.SetQuickBarEntityShortcut(pGun, 0, true);
			break; 
			case 11:
				//Rusher 2
				itemEnt = player.GetInventory().CreateInInventory("JoggingShoes_Black"); itemBs = ItemBase.Cast(itemEnt);
				pGun = player.GetInventory().CreateInInventory("VSS"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("FlatCap_Blackcheck"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("Breeches_Blackcheck"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("AssaultBag_Black"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("Mag_VSS_10Rnd"); itemBs = ItemBase.Cast(itemEnt);
				player.SetQuickBarEntityShortcut(itemEnt, 1, true);
				itemEnt = player.GetInventory().CreateInInventory("Mag_VSS_10Rnd"); itemBs = ItemBase.Cast(itemEnt);
				player.SetQuickBarEntityShortcut(itemEnt, 2, true);
				itemEnt = player.GetInventory().CreateInInventory("Mag_VSS_10Rnd"); itemBs = ItemBase.Cast(itemEnt);
				player.SetQuickBarEntityShortcut(itemEnt, 3, true);
				itemEnt = player.GetInventory().CreateInInventory("TacticalBaconCan_Opened"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("TacticalBaconCan_Opened"); itemBs = ItemBase.Cast(itemEnt);
				
				player.SetQuickBarEntityShortcut(pGun, 0, true);
			break; 
			case 12:
				//Heavy Rusher
				itemEnt = player.GetInventory().CreateInInventory("CombatBoots_Green"); itemBs = ItemBase.Cast(itemEnt);
				pGun = player.GetInventory().CreateInInventory("AKM"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("AK_PlasticBttstck"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("AK_RailHndgrd"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("GorkaHelmet"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("PlateCarrierVest"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("TacticalGoggles"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("TacticalShirt_Black"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("BDUPants"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("AliceBag_Camo"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("TacticalGloves_Black"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("Mag_AKM_30Rnd"); itemBs = ItemBase.Cast(itemEnt);
				player.SetQuickBarEntityShortcut(itemEnt, 1, true);
				itemEnt = player.GetInventory().CreateInInventory("Mag_AKM_30Rnd"); itemBs = ItemBase.Cast(itemEnt);
				player.SetQuickBarEntityShortcut(itemEnt, 2, true);
				itemEnt = player.GetInventory().CreateInInventory("Mag_AKM_30Rnd"); itemBs = ItemBase.Cast(itemEnt);
				player.SetQuickBarEntityShortcut(itemEnt, 3, true);
				itemEnt = player.GetInventory().CreateInInventory("TacticalBaconCan_Opened"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("TacticalBaconCan_Opened"); itemBs = ItemBase.Cast(itemEnt);
				
				player.SetQuickBarEntityShortcut(pGun, 0, true);
			break; 
			case 13:
				//Deconstructor
				itemEnt = player.GetInventory().CreateInInventory("WorkingBoots_Green"); itemBs = ItemBase.Cast(itemEnt);
				pGun = player.GetInventory().CreateInInventory("MP5K"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("MP5_RailHndgrd"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("MP5k_StockBttstck"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("ConstructionHelmet_Lime"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("WorkingGloves_Yellow"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("BomberJacket_Olive"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("CargoPants_Grey"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("Mag_MP5_30Rnd"); itemBs = ItemBase.Cast(itemEnt);
				player.SetQuickBarEntityShortcut(itemEnt, 1, true);
				itemEnt = player.GetInventory().CreateInInventory("Mag_MP5_30Rnd"); itemBs = ItemBase.Cast(itemEnt);
				player.SetQuickBarEntityShortcut(itemEnt, 2, true);
				itemEnt = player.GetInventory().CreateInInventory("SledgeHammer"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("TacticalBaconCan_Opened"); itemBs = ItemBase.Cast(itemEnt);
				
				player.SetQuickBarEntityShortcut(pGun, 0, true);
			break; 
			case 14:
				//Medic 1
				itemEnt = player.GetInventory().CreateInInventory("Sneakers_Red"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("BallisticHelmet_UN"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("PlateCarrierVest"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("AviatorGlasses"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("ParamedicJacket_Crimson"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("ParamedicPants_Crimson"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("DryBag_Red"); itemBs = ItemBase.Cast(itemEnt);
				pGun = player.GetInventory().CreateInInventory("CZ75"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("Rag"); itemBs = ItemBase.Cast(itemEnt); itemBs.SetQuantity(6);
				itemEnt = player.GetInventory().CreateInInventory("Rag"); itemBs = ItemBase.Cast(itemEnt); itemBs.SetQuantity(6);
				itemEnt = player.GetInventory().CreateInInventory("Rag"); itemBs = ItemBase.Cast(itemEnt); itemBs.SetQuantity(6);
				itemEnt = player.GetInventory().CreateInInventory("Rag"); itemBs = ItemBase.Cast(itemEnt); itemBs.SetQuantity(6);
				itemEnt = player.GetInventory().CreateInInventory("Mag_CZ75_15Rnd"); itemBs = ItemBase.Cast(itemEnt);
				player.SetQuickBarEntityShortcut(itemEnt, 1, true);
				itemEnt = player.GetInventory().CreateInInventory("Mag_CZ75_15Rnd"); itemBs = ItemBase.Cast(itemEnt);
				player.SetQuickBarEntityShortcut(itemEnt, 2, true);
				itemEnt = player.GetInventory().CreateInInventory("TetracyclineAntibiotics"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("CharcoalTablets"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("Epinephrine"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("SalineBagIV"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("SalineBagIV"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("SalineBagIV"); itemBs = ItemBase.Cast(itemEnt);
				
				player.SetQuickBarEntityShortcut(pGun, 0, true);
			break; 
			case 15:
				//Medic 2
				itemEnt = player.GetInventory().CreateInInventory("Sneakers_Green"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("BallisticHelmet_UN"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("PlateCarrierVest"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("AviatorGlasses"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("ParamedicJacket_Green"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("ParamedicPants_Green"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("DryBag_Green"); itemBs = ItemBase.Cast(itemEnt);
				pGun = player.GetInventory().CreateInInventory("FNX45"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("Rag"); itemBs = ItemBase.Cast(itemEnt); itemBs.SetQuantity(6);
				itemEnt = player.GetInventory().CreateInInventory("Rag"); itemBs = ItemBase.Cast(itemEnt); itemBs.SetQuantity(6);
				itemEnt = player.GetInventory().CreateInInventory("Rag"); itemBs = ItemBase.Cast(itemEnt); itemBs.SetQuantity(6);
				itemEnt = player.GetInventory().CreateInInventory("Rag"); itemBs = ItemBase.Cast(itemEnt); itemBs.SetQuantity(6);
				itemEnt = player.GetInventory().CreateInInventory("Mag_FNX45_15Rnd"); itemBs = ItemBase.Cast(itemEnt);
				player.SetQuickBarEntityShortcut(itemEnt, 1, true);
				itemEnt = player.GetInventory().CreateInInventory("Mag_FNX45_15Rnd"); itemBs = ItemBase.Cast(itemEnt);
				player.SetQuickBarEntityShortcut(itemEnt, 2, true);
				itemEnt = player.GetInventory().CreateInInventory("TetracyclineAntibiotics"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("Morphine"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("PainkillerTablets"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("SalineBagIV"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("SalineBagIV"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("SalineBagIV"); itemBs = ItemBase.Cast(itemEnt);
				
				player.SetQuickBarEntityShortcut(pGun, 0, true);
			break;  
			case 16:
				//FAL God
				itemEnt = player.GetInventory().CreateInInventory("WorkingBoots_Brown"); itemBs = ItemBase.Cast(itemEnt);
				pGun = player.GetInventory().CreateInInventory("FAL"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("Fal_OeBttstck"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("GreatHelm"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("QuiltedJacket_Violet"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("HunterPants_Brown"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("MountainBag_Red"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("Mag_FAL_20Rnd"); itemBs = ItemBase.Cast(itemEnt);
				player.SetQuickBarEntityShortcut(itemEnt, 1, true);
				itemEnt = player.GetInventory().CreateInInventory("Mag_FAL_20Rnd"); itemBs = ItemBase.Cast(itemEnt);
				player.SetQuickBarEntityShortcut(itemEnt, 2, true);
				itemEnt = player.GetInventory().CreateInInventory("Mag_FAL_20Rnd"); itemBs = ItemBase.Cast(itemEnt);
				player.SetQuickBarEntityShortcut(itemEnt, 3, true);
				itemEnt = player.GetInventory().CreateInInventory("TacticalBaconCan_Opened"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("TacticalBaconCan_Opened"); itemBs = ItemBase.Cast(itemEnt);
				
				player.SetQuickBarEntityShortcut(pGun, 0, true);
			break; 
			case 17:
				//Distraction
				itemEnt = player.GetInventory().CreateInInventory("Sneakers_Black"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("BoonieHat_Orange"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("PlateCarrierVest"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("AviatorGlasses"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("QuiltedJacket_Orange"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("ShortJeans_Black"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("MountainBag_Orange"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("Megaphone"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("Battery9V"); itemBs = ItemBase.Cast(itemEnt);
				pGun = player.GetInventory().CreateInInventory("Izh18"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("Ammo_762x39Tracer"); itemBs = ItemBase.Cast(itemEnt);
				player.SetQuickBarEntityShortcut(itemEnt, 1, true);
				itemEnt = player.GetInventory().CreateInInventory("Ammo_762x39Tracer"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("Ammo_762x39Tracer"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("Roadflare"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("Roadflare"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("Roadflare"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("Roadflare"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("Chemlight_Blue"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("Chemlight_Red"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("Chemlight_White"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("M18SmokeGrenade_Green"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("M18SmokeGrenade_Purple"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("M18SmokeGrenade_Red"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("M18SmokeGrenade_Yellow"); itemBs = ItemBase.Cast(itemEnt);
				
				player.SetQuickBarEntityShortcut(pGun, 0, true);
			break; 
			case 18:
				//Reporter
				itemEnt = player.GetInventory().CreateInInventory("HikingBootsLow_Grey"); itemBs = ItemBase.Cast(itemEnt);
				pGun = player.GetInventory().CreateInInventory("CZ75"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("PistolSuppressor"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("BallisticHelmet_UN"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("PressVest_Blue"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("ManSuit_Black"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("SlacksPants_Black"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("MountainBag_Blue"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("Mag_CZ75_15Rnd"); itemBs = ItemBase.Cast(itemEnt);
				player.SetQuickBarEntityShortcut(itemEnt, 1, true);
				itemEnt = player.GetInventory().CreateInInventory("Mag_CZ75_15Rnd"); itemBs = ItemBase.Cast(itemEnt);
				player.SetQuickBarEntityShortcut(itemEnt, 2, true);
				itemEnt = player.GetInventory().CreateInInventory("Mag_CZ75_15Rnd"); itemBs = ItemBase.Cast(itemEnt);
				player.SetQuickBarEntityShortcut(itemEnt, 3, true);
				itemEnt = player.GetInventory().CreateInInventory("Mag_CZ75_15Rnd"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("Pen_Black"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("Paper"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("Paper"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("Paper"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("Paper"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("RDG2SmokeGrenade_White"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("RDG2SmokeGrenade_White"); itemBs = ItemBase.Cast(itemEnt);
				
				player.SetQuickBarEntityShortcut(pGun, 0, true);
			break; 
			case 19:
				//Wookie
				itemEnt = player.GetInventory().CreateInInventory("CombatBoots_Black"); itemBs = ItemBase.Cast(itemEnt);
				pGun = player.GetInventory().CreateInInventory("M4A1"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("M4_RISHndgrd"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("M4_CarryHandleOptic"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("M4_CQBBttstck"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("GhillieHood_Tan"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("GhillieSuit_Tan"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("SmershVest"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("SmershBag"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("AviatorGlasses"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("CargoPants_Beige"); itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("Mag_STANAG_30Rnd"); itemBs = ItemBase.Cast(itemEnt);
				player.SetQuickBarEntityShortcut(itemEnt, 1, true);
				itemEnt = player.GetInventory().CreateInInventory("Mag_STANAG_30Rnd"); itemBs = ItemBase.Cast(itemEnt);
				player.SetQuickBarEntityShortcut(itemEnt, 2, true);
				
				player.SetQuickBarEntityShortcut(pGun, 0, true);
			break; 
			};
			//This block adds these things to ALL loadouts inventory. I had to do this part separate from the belts and attachments as the players didn't have enough slots for these items until after their random loadout gave them clothing and a backpack
			itemEnt = player.GetInventory().CreateInInventory("Rag"); itemBs = ItemBase.Cast(itemEnt); itemBs.SetQuantity(6);
			itemEnt = player.GetInventory().CreateInInventory("TacticalBaconCan_Opened"); itemBs = ItemBase.Cast(itemEnt);
			itemEnt = player.GetInventory().CreateInInventory("TacticalBaconCan_Opened"); itemBs = ItemBase.Cast(itemEnt);
		}
	}
};

Mission CreateCustomMission(string path)
{
	return new CustomMission();
}