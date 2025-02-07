
void main() {
	
  //INIT ECONOMY--------------------------------------
  Hive ce = CreateHive();
  if (ce)
    ce.InitOffline();

  //DATE RESET AFTER ECONOMY INIT-------------------------
  int year, month, day, hour, minute;
  int reset_month = 9, reset_day = 20;
  GetGame().GetWorld().GetDate(year, month, day, hour, minute);

  if ((month == reset_month) && (day < reset_day)) {
    GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
  } else {
    if ((month == reset_month + 1) && (day > reset_day)) {
      GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
    } else {
      if ((month < reset_month) || (month > reset_month + 1)) {
        GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
      }
    }
  }

}

class CustomMission: MissionServer {
  ref PlayerRepSettings m_PlayerRepSettings;
  private const static string EXP_UTILS_FOLDER = "$profile:ExpansionMod\\Utils\\";
  private const static string EXP_UTILS_SETTINGS = EXP_UTILS_FOLDER + "PlayerRepSettings.json";

  void SetRandomHealth(EntityAI itemEnt) {
    if (itemEnt) {
      float rndHlt = Math.RandomFloat(0.45, 0.65);
      itemEnt.SetHealth01("", "", rndHlt);
    }
  }

  override PlayerBase CreateCharacter(PlayerIdentity identity, vector pos, ParamsReadContext ctx, string characterName) {

    Entity playerEnt;
    playerEnt = GetGame().CreatePlayer(identity, characterName, pos, 0, "NONE");
    Class.CastTo(m_player, playerEnt);
    GetGame().SelectPlayer(identity, m_player);
    return m_player;
  }

  override void StartingEquipSetup(PlayerBase player, bool clothesChosen) {
    EntityAI itemClothing;
    EntityAI itemEnt;
    ItemBase itemBs;
    float rand;

    itemClothing = player.FindAttachmentBySlotName("Body");
    if (itemClothing) {
      SetRandomHealth(itemClothing);

      itemEnt = itemClothing.GetInventory().CreateInInventory("BandageDressing");
      if (Class.CastTo(itemBs, itemEnt))
        itemBs.SetQuantity(2);

      string chemlightArray[] = {
        "Chemlight_White",
        "Chemlight_Yellow",
        "Chemlight_Green",
        "Chemlight_Red"
      };
      int rndIndex = Math.RandomInt(0, 4);
      itemEnt = itemClothing.GetInventory().CreateInInventory(chemlightArray[rndIndex]);
      SetRandomHealth(itemEnt);

      rand = Math.RandomFloatInclusive(0.0, 1.0);
      if (rand < 0.35)
        itemEnt = player.GetInventory().CreateInInventory("Apple");
      else if (rand > 0.65)
        itemEnt = player.GetInventory().CreateInInventory("Pear");
      else
        itemEnt = player.GetInventory().CreateInInventory("Plum");
      SetRandomHealth(itemEnt);
    }

    itemClothing = player.FindAttachmentBySlotName("Legs");
    if (itemClothing)
      SetRandomHealth(itemClothing);

    itemClothing = player.FindAttachmentBySlotName("Feet");
  }

  /*
  //added stuff
  */
  //init
  void InitPlayerRepSettings() {
    if (!FileExist(EXP_UTILS_SETTINGS)) {
      if (!FileExist(EXP_UTILS_FOLDER))
        MakeDirectory(EXP_UTILS_FOLDER);

      DefaultPlayerRepSettings(m_PlayerRepSettings);
      JsonFileLoader < PlayerRepSettings > .JsonSaveFile(EXP_UTILS_SETTINGS, m_PlayerRepSettings);
      Print("Generating default config (will be located in: " + EXP_UTILS_SETTINGS + ")");
    } else {
      m_PlayerRepSettings = new PlayerRepSettings();
      JsonFileLoader < PlayerRepSettings > .JsonLoadFile(EXP_UTILS_SETTINGS, m_PlayerRepSettings);
    }
  }
	//defaults
  void DefaultPlayerRepSettings(out PlayerRepSettings Data) {
    Data = new PlayerRepSettings();
    Data.Group.Insert(new E_players("76562158225858681", 0));
    Data.Group.Insert(new E_players("76562158225858682", 0));
    Data.Group.Insert(new E_players("76562158225858683", 0));
    Data.Group.Insert(new E_players("76561198019858686", 500));
  }

	//on first connect
  override void InvokeOnConnect(PlayerBase player, PlayerIdentity identity) {
    super.InvokeOnConnect(player, identity);
	//adding reps for specific players
    m_PlayerRepSettings = new PlayerRepSettings;
    InitPlayerRepSettings();
    if (m_PlayerRepSettings.Enabled == 0) return;
    foreach(E_players Group: m_PlayerRepSettings.Group) {
      if (player.GetIdentity().GetPlainId() == Group.UID) {
        if (!player.Expansion_GetReputation()) player.Expansion_SetReputation(0);
          player.Expansion_AddReputation(Group.Reputation + 1);
          Print("Rep added to:" + player.GetIdentity().GetName() + " - amount :" + Group.Reputation.ToString());
          /*
          can play around with:
          player.Expansion_GetReputation()
          player.Expansion_SetReputation(int)
          player.Expansion_AddReputation(int)
          */

          //resets file value one applied
          //comment out to apply the same each spawn/login
          Group.Reputation = 0;
      }
    }
    JsonFileLoader < PlayerRepSettings > .JsonSaveFile(EXP_UTILS_SETTINGS, m_PlayerRepSettings);
  }
  
}

class E_players {
  string UID;
  int Reputation;

  void E_players(string bod, int fac) {
    UID = bod;
    Reputation = fac;
  }
}

class PlayerRepSettings {
  int Enabled = 1;
  ref array < ref E_players > Group;
  void PlayerRepSettings() {
    Group = new array < ref E_players > ;
  }
};

Mission CreateCustomMission(string path) {
  return new CustomMission();
}



/*

modded class DayZPlayerImplement
{
    override bool HandleDeath(int pCurrentCommandID)
    {
        #ifdef DZ_Expansion_Hardline
            if (CommitedSuicide() && GetGame().IsServer())
            {
                PlayerBase player = PlayerBase.Cast(this);
                if (player)
                {
                    int amount = 1000;
                    int rep = player.Expansion_GetReputation();
                    if (rep <= amount) 
                    {
                        player.Expansion_SetReputation(0);
                    }
                    else
                    {
                        player.Expansion_DecreaseReputation(amount);
                        Print("Rep removed from:" + player.GetIdentity().GetName() + " - due to suicide.");
                    }
                }
            }
        #endif
        return super.HandleDeath(pCurrentCommandID);
    }
}

*/