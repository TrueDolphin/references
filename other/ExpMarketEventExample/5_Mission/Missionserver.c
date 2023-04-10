  //ctor example use
  void MissionServer() {
     GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.MarketTimer, 30000, true);
  }


  void MarketTimer(){
  foreach(ExpansionTraderObjectBase trader: ExpansionTraderObjectBase.GetAll()) {
        if (!trader) continue;
        switch (trader.GetDisplayName())
        {
          case "Judy [#STR_EXPANSION_MARKET_TRADER_VEHICLES]": // names of things to switch
          trader.SwitchActive();
        }
      }
  }