modded class MissionServer {

  void MissionServer() {
    GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.MarketEnable, 300000, false); // 5m initial close timer from start
  }

  void MarketDisable() {
    NotifyPlayers("Black market has Closed", "Black Market");
    MarketSwitch();
    GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.MarketEnable, 7200000, false); // 2 hours
  }

  void MarketEnable() {
    NotifyPlayers("Black market has Opened", "Black Market");
    MarketSwitch();
    GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.MarketDisable, 1200000, false); //20 mins
  }

  void MarketSwitch() {
    foreach(ExpansionTraderObjectBase trader: ExpansionTraderObjectBase.GetAll()) {
      if (!trader) continue;
      switch (trader.GetDisplayName()) {
      case "Judy [#STR_EXPANSION_MARKET_TRADER_VEHICLES]": //example
        //trader.map reference, and trader.json name in brackets
        trader.SwitchActive();
      }
    }
  }

  void NotifyPlayers(string m_MessageText, string m_MessageTitle) {
    array < Man > players = new array < Man > ;
    GetGame().GetPlayers(players);
    for (int i = 0; i < players.Count(); i++) {
      PlayerBase player = PlayerBase.Cast(players[i]);
      if (!player)
        return;
      if (!player.GetIdentity())
        return;
      NotificationSystem.SendNotificationToPlayerExtended(player, 10, m_MessageTitle, m_MessageText, "set:dayz_gui image:tutorials");
    }
  }

}