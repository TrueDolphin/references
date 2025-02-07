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
			player.SetQuickBarEntityShortcut(itemEnt, 2);
			
			string chemlightArray[] = { "Chemlight_White", "Chemlight_Yellow", "Chemlight_Green", "Chemlight_Red" };
			int rndIndex = Math.RandomInt( 0, 4 );
			itemEnt = itemClothing.GetInventory().CreateInInventory( chemlightArray[rndIndex] );
			SetRandomHealth( itemEnt );
			player.SetQuickBarEntityShortcut(itemEnt, 1);

			rand = Math.RandomFloatInclusive( 0.0, 1.0 );
			if ( rand < 0.35 )
				itemEnt = player.GetInventory().CreateInInventory( "Apple" );
			else if ( rand > 0.65 )
				itemEnt = player.GetInventory().CreateInInventory( "Pear" );
			else
				itemEnt = player.GetInventory().CreateInInventory( "Plum" );
			player.SetQuickBarEntityShortcut(itemEnt, 3);
			SetRandomHealth( itemEnt );
		}
		
		itemClothing = player.FindAttachmentBySlotName( "Legs" );
		if ( itemClothing )
			SetRandomHealth( itemClothing );
		
		itemClothing = player.FindAttachmentBySlotName( "Feet" );
	}

	//custom stuff starts here
	void CustomMission()
	{
		SaveAllWeatherConfigs();
	}
	
	void SaveConfigHierarchyToFile(FileHandle file, string path, int depth = 0) 
	{
		int count = GetGame().ConfigGetChildrenCount(path);
		string childName;
		
		for (int i = 0; i < count; ++i) {
			GetGame().ConfigGetChildName(path, i, childName);
			string indent = GetIndentation(depth);
			string fullPath = path + " " + childName;
			
			if (GetGame().ConfigIsExisting(fullPath)) {
				if (GetGame().ConfigGetChildrenCount(fullPath) > 0) {
					FPrintln(file, indent + "Class: " + childName);
					SaveConfigHierarchyToFile(file, fullPath, depth + 1);
				} else {
					string value;
					bool success = GetGame().ConfigGetTextRaw(fullPath, value);
					if (!success) value = "<null>";
					FPrintln(file, indent + "Variable: " + childName + " = " + value);
				}
			}
		}
	}

	string GetIndentation(int depth) 
	{
		string indent = "";
		for (int i = 0; i < depth; ++i) {
			indent += "  ";
		}
		return indent;
	}

	void SaveWeatherConfigForWorld(string worldName) 
	{
		string weatherPath = "CfgWorlds " + worldName + " Weather";
		
		if (GetGame().ConfigIsExisting(weatherPath)) {
			FileHandle file = OpenFile("$mission:Weather_" + worldName + ".txt", FileMode.WRITE);
			if (file) {
				FPrintln(file, "Weather Configuration for " + worldName);
				FPrintln(file, "=================================");
				SaveConfigHierarchyToFile(file, weatherPath);
				CloseFile(file);
				Print("Saved weather config to Weather_" + worldName + ".txt");
			} else {
				Print("Failed to create file for " + worldName);
			}
		} else {
			Print("No weather config data found for " + worldName);
		}
	}

	void SaveAllWeatherConfigs() 
	{
		if (GetGame().ConfigIsExisting("CfgWorlds")) {
			int worldCount = GetGame().ConfigGetChildrenCount("CfgWorlds");
			string worldName;
			
			for (int i = 0; i < worldCount; ++i) {
				GetGame().ConfigGetChildName("CfgWorlds", i, worldName);
				SaveWeatherConfigForWorld(worldName);
			}
		} else {
			Print("CfgWorlds not found.");
		}
	}
	//custom stuff ends here

};

Mission CreateCustomMission(string path)
{
	return new CustomMission();
}
