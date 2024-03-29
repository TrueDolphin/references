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


	void CustomMission()
	{
		wall_create();
	}


	void wall_create()
	{
		Object object;
		int size = GetGame().GetWorld().GetWorldSize();
		int count =	0;
		int modelWidth = 6;
		vector pos, ori;

		for (pos[0] = 0; pos[0] <= size; pos[0] = pos[0] + modelWidth)
		{
			// Create static objects along the bottom edge
			pos[2] = 0;
			pos[1] = GetGame().SurfaceY(pos[0], pos[2]);
			object = GetGame().CreateStaticObjectUsingP3D("DZ\\structures\\walls\\Wall_VilVar1_6.p3d", pos, vector.Zero, 1);
			ori = object.GetOrientation();
			// Create static objects along the top edge
			pos[2] = size;
			pos[1] = GetGame().SurfaceY(pos[0], pos[2]);
			GetGame().CreateStaticObjectUsingP3D("DZ\\structures\\walls\\Wall_VilVar1_6.p3d", pos, vector.Zero, 1);
		}

		for (pos[2] = modelWidth; pos[2] < size; pos[2] = pos[2] + modelWidth)
		{
			// Create static objects along the left edge
			pos[0] = 0;
			pos[1] = GetGame().SurfaceY(pos[0], pos[2]);
			GetGame().CreateStaticObjectUsingP3D("DZ\\structures\\walls\\Wall_VilVar1_6.p3d", pos, ori + "90 0 0", 1);
			// Create static objects along the right edge
			pos[0] = size;
			pos[1] = GetGame().SurfaceY(pos[0], pos[2]);
			GetGame().CreateStaticObjectUsingP3D("DZ\\structures\\walls\\Wall_VilVar1_6.p3d", pos, ori + "90 0 0", 1);
		}
	}



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