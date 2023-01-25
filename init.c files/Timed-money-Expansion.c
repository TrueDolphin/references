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
    //! Steve's code.
    protected int m_MoneyToAdd = 500; // money to add
	protected int m_MoneyAddTimer = 1; // time in minutes
    int m_MoneyInit_Single = 0; // on first player connect, sets to 1.
    
    void AddMoneyToActivePlayers()
    {
        array<Man> players = new array<Man>;
        GetGame().GetPlayers(players);
        ExpansionMarketModule marketModule = ExpansionMarketModule.Cast(CF_ModuleCoreManager.Get(ExpansionMarketModule));
        if (marketModule)
        {
            foreach (Man player: players)
            {
                ExpansionMarketATM_Data playerATMData = marketModule.GetPlayerATMData(player.GetIdentity().GetId());
                if (!playerATMData)
                    continue;
                int currentATMMoney = playerATMData.GetMoney();
                int possibleDepositAmount = GetExpansionSettings().GetMarket().MaxDepositMoney - currentATMMoney;
                if (currentATMMoney + m_MoneyToAdd > GetExpansionSettings().GetMarket().MaxDepositMoney && possibleDepositAmount != 0) 
                {
                    playerATMData.AddMoney(possibleDepositAmount);
                    ExpansionNotification(new StringLocaliser("Payment"), new StringLocaliser("You have received a lower payout of %1 to your Bank account. Your Bank account is full!", possibleDepositAmount.ToString()), ExpansionIcons.GetPath("Exclamationmark"), COLOR_EXPANSION_NOTIFICATION_SUCCSESS, 7, ExpansionNotificationType.TOAST).Create(player.GetIdentity());
                }
                else
                {
                    playerATMData.AddMoney(m_MoneyToAdd);
                    ExpansionNotification(new StringLocaliser("Payment"), new StringLocaliser("You have received a payout of %1 to your Bank account.", m_MoneyToAdd.ToString()), ExpansionIcons.GetPath("Exclamationmark"), COLOR_EXPANSION_NOTIFICATION_SUCCSESS, 7, ExpansionNotificationType.TOAST).Create(player.GetIdentity());
                }
            }
        }
    }
	override void InvokeOnConnect(PlayerBase player, PlayerIdentity identity)
  	{
		if (m_MoneyInit_Single == 0){
			m_MoneyInit_Single = 1;
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(AddMoneyToActivePlayers, m_MoneyAddTimer * 60000, true);
		}
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