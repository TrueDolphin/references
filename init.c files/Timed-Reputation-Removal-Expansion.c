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
    //! custom stuff starts here
	#ifdef DZ_Expansion_Hardline
		protected int REMOVEAMOUNT = 100; // rep to remove
		protected int m_ReputationTimer = 1; // time in minutes
		int m_CallInit = 0; // on first player connect, sets to 1.
		
		void RemoveRepFromPlayers()
		{
			int CurrentRep = 0;
			array<Man> players = new array<Man>;
			GetGame().GetPlayers(players);
	
		    foreach (Man player: players)
		    {
			PlayerBase Player = PlayerBase.Cast(player);
			if (!Player || !Player.GetIdentity()) continue;
		
			if (!Player.Expansion_GetReputation())
			{
			    Player.Expansion_SetReputation(0);
			    CurrentRep = 0;
			}
			else
			{
			    CurrentRep = Player.Expansion_GetReputation();
			}
		
			Player.Expansion_SetReputation(CurrentRep - (REMOVEAMOUNT + 1));
			/*
			can play around with:
			Player.Expansion_GetReputation()
			Player.Expansion_SetReputation(int)
			Player.Expansion_AddReputation(int)
			*/
		    }
		}
	#endif

	override void InvokeOnConnect(PlayerBase player, PlayerIdentity identity)
  	{
		#ifdef DZ_Expansion_Hardline
			if (m_CallInit == 0){
				m_CallInit = 1;
				GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(RemoveRepFromPlayers, m_ReputationTimer * 60000, true);
			}
		#endif
      	super.InvokeOnConnect(player, identity);               
    	} 
	//! Ends here

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
