//#include "$profile:ExpansionMod\\AI\\Utils\\AIDeerisle.c"

void main() {
  //INIT WEATHER BEFORE ECONOMY INIT------------------------
  // Weather weather = g_Game.GetWeather();
  // weather.MissionWeather(false);    // false = use weather controller from Weather.c
  // weather.GetOvercast().Set( Math.RandomFloatInclusive(0.4, 0.6), 1, 0);
  // weather.GetRain().Set( 0, 0, 1);
  // weather.GetFog().Set( Math.RandomFloatInclusive(0.05, 0.1), 1, 0);

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
ref TStringArray foundfiles = {};

  void CustomMission(){
    if (SearchJsonFilesInDirectory("$profile:ExpansionMod\\Loadouts\\", foundfiles)) Print(foundfiles);
  }


  void SetRandomHealth(EntityAI itemEnt) {
    if (itemEnt) {
      int rndHlt = Math.RandomInt(55, 100);
      itemEnt.SetHealth("", "", rndHlt);
    }
  }

  override PlayerBase CreateCharacter(PlayerIdentity identity, vector pos, ParamsReadContext ctx, string characterName) {
    Entity playerEnt;
    playerEnt = GetGame().CreatePlayer(identity, characterName, pos, 0, "NONE"); //Creates random player
    Class.CastTo(m_player, playerEnt);
    GetGame().SelectPlayer(identity, m_player);
    return m_player;
  }

  override void StartingEquipSetup(PlayerBase player, bool clothesChosen) {
    TStringArray jacket = {
      "Hoodie_Black", "Hoodie_Brown", "Hoodie_Green", "Hoodie_Grey", "Hoodie_Red" };
    TStringArray pants = { "Jeans_Black","Jeans_BlueDark","Jeans_Blue","Jeans_Brown","Jeans_Green","Jeans_Grey"};
    TStringArray drink = {"SodaCan_Cola","SodaCan_Kvass","SodaCan_Pipsi","SodaCan_Spite"};
    TStringArray food = {"TunaCan","PowderedMilk","PeachesCan","Pear"};
    TStringArray tool = {"OrienteeringCompass","Knife","PurificationTablets","Matchbox"};
    player.RemoveAllItems();
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
    player.GetInventory().CreateInInventory("PistolSuppressor");
    player.GetInventory().CreateInInventory("Mag_FNX45_15Rnd");
    player.GetInventory().CreateInInventory("Mag_FNX45_15Rnd");
    EntityAI gun = player.GetHumanInventory().CreateInHands("FNX45");
    gun.GetInventory().CreateAttachment("PistolSuppressor");
    EntityAI headpiece = player.GetHumanInventory().CreateInInventory("Headtorch_Black");
    headpiece.GetInventory().CreateAttachment("Battery9V");
  }


  bool SearchJsonFilesInDirectory(string directory, out TStringArray loadoutfiles)
  {
      FindFileHandle findHandle;
      string fileName;
      FileAttr fileAttributes;
      string jsonPattern = directory + "\\*.json";
      findHandle = FindFile(jsonPattern, fileName, fileAttributes, FindFileFlags.ALL);
      if (findHandle != 0)
      {
          while (FindNextFile(findHandle, fileName, fileAttributes))
          {
              if (fileAttributes != FileAttr.DIRECTORY && fileName.IndexOf(".json") == fileName.Length() - 5)
              {
                  loadoutfiles.Insert(fileName);
              }
          }
          CloseFindFile(findHandle);
      }
      if (loadoutfiles.Count() > 0) return true;
      return false;
  }

};
Mission CreateCustomMission(string path) {
  return new CustomMission();
}