void main()
{
	//INIT ECONOMY--------------------------------------
	Hive ce = CreateHive();
	if ( ce )
		ce.InitOffline();

	//DATE RESET AFTER ECONOMY INIT-------------------------
	int year, month, day, hour, minute;
	int reset_month = 9, reset_day = 20;
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
	//comment out when not needed
	GenerateLoadout()
}
	static void GenerateLoadout()
	{
		string filename = "GeneratedLoadout";
		if (FileExist(ExpansionLoadout.GetPath(filename))) return;
		auto loadout = ExpansionLoadout.Create(filename);
		if (!loadout) return;

			/* notes
			best practice, if the sets touch a slot, dont manually touch that slot.
			make sure classnames are correct.
			weapon sets are split to keep the sections more specific.
			you can seperate these even more.
			*/
			//! NBC Gray
			loadout = loadout.BeginSet("CLOTHING");
				loadout = loadout.BeginAttachment("NBCJacketGray", "Body");
				loadout.SetHealth(0.7, 1.0);
				loadout = loadout.End();

				loadout = loadout.BeginAttachment("NBCPantsGray", "Legs");
				loadout.SetHealth(0.7, 1.0);
				loadout = loadout.End();

				loadout = loadout.BeginAttachment("NBCBootsGray", "Feet");
				loadout.SetHealth(0.7, 1.0);
				loadout = loadout.End();

				loadout = loadout.BeginAttachment("NBCHoodGray", "Headgear");
				loadout.SetHealth(0.7, 1.0);
				loadout = loadout.End();

				loadout = loadout.BeginAttachment("NBCGlovesGray", "Gloves");
				loadout.SetHealth(0.7, 1.0);
				loadout = loadout.End();
			loadout = loadout.End();
			
			//! NBC Yellow
			loadout = loadout.BeginSet("CLOTHING");
				loadout = loadout.BeginAttachment("NBCJacketYellow", "Body");
				loadout.SetHealth(0.7, 1.0);
				loadout = loadout.End();

				loadout = loadout.BeginAttachment("NBCPantsYellow", "Legs");
				loadout.SetHealth(0.7, 1.0);
				loadout = loadout.End();
			
				loadout = loadout.BeginAttachment("NBCBootsYellow", "Feet");
				loadout.SetHealth(0.7, 1.0);
				loadout = loadout.End();
			
				loadout = loadout.BeginAttachment("NBCHoodYellow", "Headgear");
				loadout.SetHealth(0.7, 1.0);
				loadout = loadout.End();

				loadout = loadout.BeginAttachment("NBCGlovesYellow", "Gloves");
				loadout.SetHealth(0.7, 1.0);
				loadout = loadout.End();
			loadout = loadout.End();
			
			//bags and cargo in said bags
			loadout = loadout.BeginAttachment("TortillaBag", "Back");
			loadout.SetHealth(0.7, 1.0);
				loadout = loadout.BeginCargo("MakarovIJ70");
				loadout.Chance = 0.34;
				loadout = loadout.End();

				loadout = loadout.BeginCargo("Mag_IJ70_8Rnd");
				loadout.Chance = 0.3;
				loadout = loadout.End();

				loadout = loadout.BeginCargo("Mag_IJ70_8Rnd");
				loadout.Chance = 0.2;
				loadout = loadout.End();
				
				loadout = loadout.BeginCargo("BandageDressing");
				loadout.Chance = 0.1;
				loadout = loadout.End();
				
				loadout = loadout.BeginCargo("BandageDressing");
				loadout.Chance = 0.1;
				loadout = loadout.End();
				
				loadout = loadout.BeginCargo("Chemlight_Green");
				loadout.Chance = 0.1;
				loadout = loadout.End();
				
				loadout = loadout.BeginCargo("Chemlight_Green");
				loadout.Chance = 0.1;
				loadout = loadout.End();
				
				loadout = loadout.BeginCargo("RDG2SmokeGrenade_Black");
				loadout.Chance = 0.1;
				loadout = loadout.End();
				
				loadout = loadout.BeginCargo("RDG2SmokeGrenade_White");
				loadout.Chance = 0.1;
				loadout = loadout.End();

				loadout = loadout.BeginCargo("Ammo_762x39");
				loadout.Chance = 0.1;
				loadout = loadout.End();
			loadout = loadout.End();
			
			//vests
			loadout = loadout.BeginAttachment("UKAssVest_Camo", "Vest");
			loadout.SetHealth(0.7, 1.0);
			loadout.Chance = 0.1;
			loadout = loadout.End();
			loadout = loadout.BeginAttachment("UKAssVest_Olive", "Vest");
			loadout.SetHealth(0.7, 1.0);
			loadout.Chance = 0.1;
			loadout = loadout.End();
			
			//masks
			loadout = loadout.BeginAttachment("GasMask", "Mask");
			loadout.SetHealth(0.7, 1.0);
			loadout = loadout.End();
			loadout = loadout.BeginAttachment("GP5GasMask", "Mask");
			loadout.SetHealth(0.7, 1.0);
				loadout = loadout.BeginAttachment("GasMask_Filter", "");
				loadout.SetHealth(0.7, 1.0);
				loadout = loadout.End();
			loadout = loadout.End();
			loadout = loadout.BeginAttachment("AirborneMask", "Mask");
			loadout.SetHealth(0.7, 1.0);
				loadout = loadout.BeginAttachment("GasMask_Filter", "");
				loadout.SetHealth(0.7, 1.0);
				loadout = loadout.End();
			loadout = loadout.End();
			
			//belts
			loadout = loadout.BeginAttachment("MilitaryBelt", "Hips");
			loadout.SetHealth(0.7, 1.0);
			loadout = loadout.End();
			
			DefaultWeapon(loadout);
			
			//generic loot
			loadout = loadout.BeginCargo("Apple");
			loadout.Chance = 0.1;
			loadout = loadout.End();
			loadout = loadout.BeginCargo("BandageDressing");
			loadout.Chance = 0.15;
			loadout = loadout.End();
			loadout = loadout.BeginCargo("GasMask_Filter");
			loadout.Chance = 0.15;
			loadout = loadout.End();
			loadout = loadout.BeginCargo("AntiChemInjector");
			loadout.Chance = 0.05;
			loadout = loadout.End();
		loadout.Save();
	}
	static void DefaultWeapon(inout ExpansionPrefabObject loadout)
	{
		//sets of weapons. self explanatory.
		loadout = loadout.BeginSet("WEAPON");
			loadout = loadout.BeginAttachment("Scout", "Shoulder");
			loadout.SetHealth(0.7, 1.0);
				loadout = loadout.BeginAttachment("Mag_Scout_5Rnd");
				loadout = loadout.End();
				loadout = loadout.BeginAttachment("ACOGOptic");
				loadout.Chance = 0.3;
				loadout = loadout.End();
				loadout = loadout.BeginAttachment("ACOGOptic_6x");
				loadout.Chance = 0.15;
				loadout = loadout.End();
				loadout = loadout.BeginAttachment("ReflexOptic");
				loadout.Chance = 0.075;
					loadout = loadout.BeginAttachment("Battery9V");
					loadout = loadout.End();
				loadout = loadout.End();
				loadout = loadout.BeginAttachment("M68Optic");
				loadout.Chance = 0.075;
					loadout = loadout.BeginAttachment("Battery9V");
					loadout = loadout.End();
				loadout = loadout.End();
				loadout = loadout.BeginAttachment("StarlightOptic");
				loadout.Chance = 0.05;
					loadout = loadout.BeginAttachment("Battery9V");
					loadout = loadout.End();
				loadout = loadout.End();
			loadout = loadout.End();
			
			loadout = loadout.BeginCargo("Mag_Scout_5Rnd");
			loadout.Chance = 1.0;
			loadout = loadout.End();
			loadout = loadout.BeginCargo("Mag_Scout_5Rnd");
			loadout.Chance = 0.15;
			loadout = loadout.End();
		loadout = loadout.End();
			
		loadout = loadout.BeginSet("WEAPON");
			loadout = loadout.BeginAttachment("FAMAS", "Shoulder");
			loadout.SetHealth(0.7, 1.0);
				loadout = loadout.BeginAttachment("Mag_FAMAS_25Rnd");
				loadout = loadout.End();
			loadout = loadout.End();
			
			loadout = loadout.BeginCargo("Mag_FAMAS_25Rnd");
			loadout.Chance = 1.0;
			loadout = loadout.End();
			loadout = loadout.BeginCargo("Mag_FAMAS_25Rnd");
			loadout.Chance = 0.15;
			loadout = loadout.End();
		loadout = loadout.End();
			
		loadout = loadout.BeginSet("WEAPON");
			loadout = loadout.BeginAttachment("M4A1", "Shoulder");
			loadout.SetHealth(0.7, 1.0);
				loadout = loadout.BeginAttachment("Mag_STANAG_30Rnd");
				loadout.Chance = 0.60;
				loadout = loadout.End();
				loadout = loadout.BeginAttachment("Mag_STANAG_60Rnd");
				loadout.Chance = 0.10;
				loadout = loadout.End();
				loadout = loadout.BeginAttachment("Mag_CMAG_10Rnd");
				loadout.Chance = 0.05;
				loadout = loadout.End();
				loadout = loadout.BeginAttachment("Mag_CMAG_20Rnd");
				loadout.Chance = 0.05;
				loadout = loadout.End();
				loadout = loadout.BeginAttachment("Mag_CMAG_30Rnd");
				loadout.Chance = 0.05;
				loadout = loadout.End();
				loadout = loadout.BeginAttachment("Mag_CMAG_40Rnd");
				loadout.Chance = 0.05;
				loadout = loadout.End();
				loadout = loadout.BeginAttachment("M4_CQBBttstck");
				loadout.Chance = 0.33;
				loadout = loadout.End();
				loadout = loadout.BeginAttachment("M4_MPBttstck");
				loadout.Chance = 0.33;
				loadout = loadout.End();
				loadout = loadout.BeginAttachment("M4_OEBttstck");
				loadout = loadout.End();
				loadout = loadout.BeginAttachment("M4_MPHndgrd");
				loadout.Chance = 0.33;
				loadout = loadout.End();
				loadout = loadout.BeginAttachment("M4_PlasticHndgrd");
				loadout = loadout.End();
				loadout = loadout.BeginAttachment("M4_RISHndgrd");
				loadout.Chance = 0.33;
				loadout = loadout.End();
				loadout = loadout.BeginAttachment("ACOGOptic");
				loadout.Chance = 0.3;
				loadout = loadout.End();
				loadout = loadout.BeginAttachment("ACOGOptic_6x");
				loadout.Chance = 0.05;
				loadout = loadout.End();
				loadout = loadout.BeginAttachment("ReflexOptic");
				loadout.Chance = 0.1;
					loadout = loadout.BeginAttachment("Battery9V");
					loadout = loadout.End();
				loadout = loadout.End();
				loadout = loadout.BeginAttachment("M68Optic");
				loadout.Chance = 0.1;
					loadout = loadout.BeginAttachment("Battery9V");
					loadout = loadout.End();
				loadout = loadout.End();
				loadout = loadout.BeginAttachment("M4_T3NRDSOptic");
				loadout.Chance = 0.1;
					loadout = loadout.BeginAttachment("Battery9V");
					loadout = loadout.End();
				loadout = loadout.End();
				loadout = loadout.BeginAttachment("StarlightOptic");
				loadout.Chance = 0.01;
					loadout = loadout.BeginAttachment("Battery9V");
					loadout = loadout.End();
				loadout = loadout.End();
				loadout = loadout.BeginAttachment("M4_CarryHandleOptic");
				loadout = loadout.End();
			loadout = loadout.End();
			
			loadout = loadout.BeginCargo("Mag_STANAG_30Rnd");
			loadout.Chance = 1.0;
			loadout = loadout.End();
			loadout = loadout.BeginCargo("Mag_STANAG_30Rnd");
			loadout.Chance = 0.15;
			loadout = loadout.End();
		loadout = loadout.End();
			
		loadout = loadout.BeginSet("WEAPON");
			loadout = loadout.BeginAttachment("Aug", "Shoulder");
			loadout.SetHealth(0.7, 1.0);
				loadout = loadout.BeginAttachment("Mag_Aug_30Rnd");
				loadout = loadout.End();
			loadout = loadout.End();
			
			loadout = loadout.BeginCargo("Mag_Aug_30Rnd");
			loadout.Chance = 1.0;
			loadout = loadout.End();
			loadout = loadout.BeginCargo("Mag_Aug_30Rnd");
			loadout.Chance = 0.15;
			loadout = loadout.End();
		loadout = loadout.End();
			
		loadout = loadout.BeginSet("WEAPON");
			loadout = loadout.BeginAttachment("AugShort", "Shoulder");
			loadout.SetHealth(0.7, 1.0);
				loadout = loadout.BeginAttachment("Mag_Aug_30Rnd");
				loadout = loadout.End();
				loadout = loadout.BeginAttachment("ACOGOptic");
				loadout.Chance = 0.3;
				loadout = loadout.End();
				loadout = loadout.BeginAttachment("ACOGOptic_6x");
				loadout.Chance = 0.05;
				loadout = loadout.End();
				loadout = loadout.BeginAttachment("ReflexOptic");
				loadout.Chance = 0.1;
					loadout = loadout.BeginAttachment("Battery9V");
					loadout = loadout.End();
				loadout = loadout.End();
				loadout = loadout.BeginAttachment("M68Optic");
				loadout.Chance = 0.1;
					loadout = loadout.BeginAttachment("Battery9V");
					loadout = loadout.End();
				loadout = loadout.End();
				loadout = loadout.BeginAttachment("M4_T3NRDSOptic");
				loadout.Chance = 0.1;
					loadout = loadout.BeginAttachment("Battery9V");
					loadout = loadout.End();
				loadout = loadout.End();
				loadout = loadout.BeginAttachment("StarlightOptic");
				loadout.Chance = 0.01;
					loadout = loadout.BeginAttachment("Battery9V");
					loadout = loadout.End();
				loadout = loadout.End();
			loadout = loadout.End();
			
			loadout = loadout.BeginCargo("Mag_Aug_30Rnd");
			loadout.Chance = 1.0;
			loadout = loadout.End();
			loadout = loadout.BeginCargo("Mag_Aug_30Rnd");
			loadout.Chance = 0.15;
			loadout = loadout.End();
		loadout = loadout.End();
			
		loadout = loadout.BeginSet("WEAPON");
			loadout = loadout.BeginAttachment("M16A2", "Shoulder");
			loadout.SetHealth(0.7, 1.0);
				loadout = loadout.BeginAttachment("Mag_STANAG_60Rnd");
				loadout.Chance = 0.2;
				loadout = loadout.End();
				loadout = loadout.BeginAttachment("Mag_STANAG_30Rnd");
				loadout = loadout.End();
			loadout = loadout.End();
			
			loadout = loadout.BeginCargo("Mag_STANAG_30Rnd");
			loadout.Chance = 1.0;
			loadout = loadout.End();
			loadout = loadout.BeginCargo("Mag_STANAG_30Rnd");
			loadout.Chance = 0.15;
			loadout = loadout.End();
		loadout = loadout.End();
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
		EntityAI itemClothing;
		EntityAI itemEnt;
		ItemBase itemBs;
		float rand;

		itemClothing = player.FindAttachmentBySlotName( "Body" );
		if ( itemClothing )
		{
			SetRandomHealth( itemClothing );
			
			itemEnt = itemClothing.GetInventory().CreateInInventory( "BandageDressing" );
			if ( Class.CastTo( itemBs, itemEnt ) )
				itemBs.SetQuantity( 2 );

			string chemlightArray[] = { "Chemlight_White", "Chemlight_Yellow", "Chemlight_Green", "Chemlight_Red" };
			int rndIndex = Math.RandomInt( 0, 4 );
			itemEnt = itemClothing.GetInventory().CreateInInventory( chemlightArray[rndIndex] );
			SetRandomHealth( itemEnt );

			rand = Math.RandomFloatInclusive( 0.0, 1.0 );
			if ( rand < 0.35 )
				itemEnt = player.GetInventory().CreateInInventory( "Apple" );
			else if ( rand > 0.65 )
				itemEnt = player.GetInventory().CreateInInventory( "Pear" );
			else
				itemEnt = player.GetInventory().CreateInInventory( "Plum" );

			SetRandomHealth( itemEnt );
		}
		
		itemClothing = player.FindAttachmentBySlotName( "Legs" );
		if ( itemClothing )
			SetRandomHealth( itemClothing );
		
		itemClothing = player.FindAttachmentBySlotName( "Feet" );
	}
};

Mission CreateCustomMission(string path)
{
	return new CustomMission();
}