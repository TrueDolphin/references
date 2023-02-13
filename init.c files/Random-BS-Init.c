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
  Print("-------Hive Calls--------");
  Print("----Custom Patrol call---");
  //AIDeerisle();
  //Print("---grouppos export call--");
  //CEApi TestHive = GetCEApi();
  //TestHive.ExportProxyProto();
  //TestHive.ExportProxyData();
  //TestHive.ExportClusterData() ;	
  Print("----Hive Main Complete---");
  Print("-------------------------");

}

class CustomMission: MissionServer {
  void SetRandomHealth(EntityAI itemEnt) {
    if (itemEnt) {
      int rndHlt = Math.RandomInt(55, 100);
      itemEnt.SetHealth("", "", rndHlt);
    }
  }

  override void InvokeOnConnect(PlayerBase player, PlayerIdentity identity) {
    //temp fix for player mins not counting as 0 on death/join
    if (player.Expansion_GetReputation() < 0) player.Expansion_SetReputation(0);
    //old friendly civilian ai mod   
    eAIGroup playerGroup = player.GetGroup();
    if (!playerGroup)
      playerGroup = eAIGroup.GetGroupByLeader(player);
    super.InvokeOnConnect(player, identity);
    playerGroup.SetFaction(new eAIFactionEast());
    eAIFaction faction = playerGroup.GetFaction();
    Print("==============Faction set=========");
    Print(player.GetIdentity().GetName() + " has been assigned to faction: " + faction);
    Print("The Player belongs to: " + playerGroup);
    Print("==================================");
  }

  override PlayerBase CreateCharacter(PlayerIdentity identity, vector pos, ParamsReadContext ctx, string characterName) {
    Entity playerEnt;
    playerEnt = GetGame().CreatePlayer(identity, characterName, pos, 0, "NONE"); //Creates random player
    Class.CastTo(m_player, playerEnt);
    GetGame().SelectPlayer(identity, m_player);
    return m_player;
  }

  override void StartingEquipSetup(PlayerBase player, bool clothesChosen) {
    // Get Player Name
    bool playerNameIsSurvivor = false;
    string characterName = player.GetIdentity().GetName();
    characterName.ToLower();
    // Does player name contain Survivor
    if (characterName.Contains("survivor")) {
      playerNameIsSurvivor = true;
    }
    //Random arrays
    TStringArray jacket = {
      "Hoodie_Black", "Hoodie_Brown", "Hoodie_Green", "Hoodie_Grey", "Hoodie_Red" };
    TStringArray pants = { "Jeans_Black","Jeans_BlueDark","Jeans_Blue","Jeans_Brown","Jeans_Green","Jeans_Grey"};
    TStringArray drink = {"SodaCan_Cola","SodaCan_Kvass","SodaCan_Pipsi","SodaCan_Spite"};
    TStringArray food = {"TunaCan","PowderedMilk","PeachesCan","Pear"};
    TStringArray tool = {"OrienteeringCompass","Knife","PurificationTablets","Matchbox"};
    //
    Print("=========+++++++=========");
    Print("=========Spawning========");
    Print(player.GetIdentity().GetName());
    Print("=========+++++++=========");
    player.RemoveAllItems();
	//

	//loadout
    EntityAI itemEnt;
    ItemBase itemBs;
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

    // After Loadout
    // If Player is Named Survivor Remove All Gear
    if (playerNameIsSurvivor) {
      player.RemoveAllItems();
      GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(SurvivorDetected, 5000, true, player);
    }
  }
  // Send player message if they have Survivor as a name
  protected void SurvivorDetected(PlayerBase player) {
    sendPlayerMessage(player, "Please change name in DZSA Launcher to not include survivor.");
    sendPlayerMessage(player, "Default loadout not given to players with survivor in the name.");
    sendPlayerMessage(player, "You'll receive this message every login.");
  }
  //Message handler
  protected void sendPlayerMessage(PlayerBase player, string message) {
    if ((player) && (message != "")) {
      Param1 < string > Msgparam;
      Msgparam = new Param1 < string > (message);
      GetGame().RPCSingleParam(player, ERPCs.RPC_USER_ACTION_MESSAGE, Msgparam, true, player.GetIdentity());
      GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).Remove(SurvivorDetected);
    }
  }
};
Mission CreateCustomMission(string path) {
  return new CustomMission();
}