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
  ref PlayerListDB m_PlayerListDB;
  private
  const static string PROFILE_UTILS = "$profile:Utils\\";
  private
  const static string SETTINGS_UTILS = PROFILE_UTILS + "PlayerListDB.json";

	void CustomMission()
	{
		if (!m_PlayerListDB) InitPlayerListDB();
	}


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
    //Random arrays
    TStringArray jacket = {
      "Hoodie_Black",
      "Hoodie_Brown",
      "Hoodie_Green",
      "Hoodie_Grey",
      "Hoodie_Red"
    };
    TStringArray pants = {
      "Jeans_Black",
      "Jeans_BlueDark",
      "Jeans_Blue",
      "Jeans_Brown",
      "Jeans_Green",
      "Jeans_Grey"
    };
    TStringArray drink = {
      "SodaCan_Cola",
      "SodaCan_Kvass",
      "SodaCan_Pipsi",
      "SodaCan_Spite"
    };
    TStringArray food = {
      "TunaCan",
      "PowderedMilk",
      "PeachesCan",
      "Pear"
    };
    TStringArray tool = {
      "OrienteeringCompass",
      "Knife",
      "PurificationTablets",
      "Matchbox"
    };
    player.RemoveAllItems();
    //loadout
    player.GetInventory().CreateInInventory(pants.GetRandomElement());
    player.GetInventory().CreateInInventory(jacket.GetRandomElement());
    player.GetInventory().CreateInInventory("HikingBoots_Black");
    player.GetInventory().CreateInInventory("CourierBag");
    player.GetInventory().CreateInInventory(drink.GetRandomElement());
    player.GetInventory().CreateInInventory(food.GetRandomElement());
    player.GetInventory().CreateInInventory(food.GetRandomElement());
    player.GetInventory().CreateInInventory("Battery9V");
    player.GetInventory().CreateInInventory("BandageDressing");
    player.GetInventory().CreateInInventory("WaterBottle");
    player.GetInventory().CreateInInventory("HuntingKnife");

    EntityAI headpiece = player.GetHumanInventory().CreateInInventory("Headtorch_Black");
    headpiece.GetInventory().CreateAttachment("Battery9V");

    if (IsFirstConnect(player)) 
	{
      player.GetInventory().CreateInInventory("PistolSuppressor");
      player.GetInventory().CreateInInventory("Mag_FNX45_15Rnd");
      player.GetInventory().CreateInInventory("Mag_FNX45_15Rnd");
      EntityAI gun = player.GetHumanInventory().CreateInHands("FNX45");
      gun.GetInventory().CreateAttachment("PistolSuppressor");
    }

  }

  void InitPlayerListDB() {
    if (!FileExist(SETTINGS_UTILS)) {
      if (!FileExist(PROFILE_UTILS))
        MakeDirectory(PROFILE_UTILS);

      DefaultPlayerListDB(m_PlayerListDB);
      JsonFileLoader < PlayerListDB > .JsonSaveFile(SETTINGS_UTILS, m_PlayerListDB);
      Print("Generating default config (will be located in: " + SETTINGS_UTILS + ")");
    } else {
      m_PlayerListDB = new PlayerListDB();
      JsonFileLoader < PlayerListDB > .JsonLoadFile(SETTINGS_UTILS, m_PlayerListDB);
      Print("Loading config (" + SETTINGS_UTILS + ")");
    }
  }

  void DefaultPlayerListDB(out PlayerListDB Data) {
    Data = new PlayerListDB();
    Data.Group.Insert(new player("76562158225858681", 1));
  }

  bool IsFirstConnect(PlayerBase player) {
    if (m_PlayerListDB.Enabled == 0) return false;
    foreach(ActivePlayer Group: m_PlayerListDB.Group) {
      if (player.GetIdentity().GetPlainId() == Group.UID) {
        Group.Connects += 1;
        JsonFileLoader < PlayerListDB > .JsonSaveFile(SETTINGS_UTILS, m_PlayerListDB);
        return false;
      }
    }
    Print(player.GetIdentity().GetName() + ": First Connect");
    m_PlayerListDB.Group.Insert(new player(player.GetIdentity().GetPlainId(), 1));
    JsonFileLoader < PlayerListDB > .JsonSaveFile(SETTINGS_UTILS, m_PlayerListDB);
    return true;
  }
}

class ActivePlayer {
  string UID;
  int Connects;

  void ActivePlayer(string bod, int con) {
    UID = bod;
    Connects = con;
  }
}

class PlayerListDB {
  int Enabled = 1;
  ref array < ref ActivePlayer > Group;
  void PlayerListDB() {
    Group = new array < ref ActivePlayer > ;
  }
};

Mission CreateCustomMission(string path) {
  return new CustomMission();
}