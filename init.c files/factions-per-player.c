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
	ref PlayerAISettings m_PlayerAISettings;
	private const static string EXP_AI_PLAYER_FOLDER = "$profile:ExpansionMod\\AI\\Utils\\"; 
	private const static string EXP_AI_PLAYER_SETTINGS = EXP_AI_PLAYER_FOLDER + "PlayerAISettings.json";

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
void InitPlayerAISettings()
{
    if ( !FileExist(EXP_AI_PLAYER_SETTINGS) )
    {
		if ( !FileExist(EXP_AI_PLAYER_FOLDER) )
			MakeDirectory(EXP_AI_PLAYER_FOLDER);

        DefaultPlayerAISettings(m_PlayerAISettings);
		JsonFileLoader<PlayerAISettings>.JsonSaveFile(EXP_AI_PLAYER_SETTINGS, m_PlayerAISettings);
		Print("Generating default config (will be located in: "+EXP_AI_PLAYER_SETTINGS+")");
    } else {
		m_PlayerAISettings = new PlayerAISettings();
		JsonFileLoader<PlayerAISettings>.JsonLoadFile(EXP_AI_PLAYER_SETTINGS, m_PlayerAISettings);
		Print("Loading config ("+EXP_AI_PLAYER_SETTINGS+")");
	}
}

void DefaultPlayerAISettings(out PlayerAISettings Data)
{
    Data = new PlayerAISettings();
    Data.Group.Insert( new E_players("76562158225858681", "West"));
	Data.Group.Insert( new E_players("76562158225858682", "West"));
	Data.Group.Insert( new E_players("76562158225858683", "West"));
	Data.Group.Insert( new E_players("76561198019858686", "West"));
}

    override void InvokeOnConnect(PlayerBase player, PlayerIdentity identity)
  
      {
    //scetchy friendly civilian ai mod 
	if (!m_PlayerAISettings) InitPlayerAISettings();

        eAIGroup playerGroup = player.GetGroup();
        if(!playerGroup)
            playerGroup = eAIGroup.GetGroupByLeader(player);
        super.InvokeOnConnect(player, identity);
		if (m_PlayerAISettings.Enabled == 0) return;
	foreach(E_players Group: m_PlayerAISettings.Group)
    {
		if (player.GetIdentity().GetPlainId() == Group.UID){
		
			eAIFaction faction = eAIFaction.Create(Group.Faction);
			if (faction)
			{
				Print(player.GetIdentity().GetName() + " Set to faction: " + faction.ToString());
				playerGroup.SetFaction(faction);
				return;
			}
		}
        }
		Print("No Config for :" + player.GetIdentity().GetName() + " found.");
	}



}
class E_players
{
	string UID;
    string Faction;

    void E_players(string bod, string fac)
    {
        UID = bod;
        Faction = fac;
    }
}

class PlayerAISettings
{
	int Enabled = 1;				// Time in seconds before the dead group will respawn. If set to -1, they won't respawn
	ref array< ref E_players > Group;
	void PlayerAISettings()
	{
		Group = new array< ref E_players >;
	}
};

Mission CreateCustomMission(string path)
{
	return new CustomMission();
}