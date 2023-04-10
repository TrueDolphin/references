modded class ExpansionTraderObjectBase {
  bool TradeActive = true;

  void SwitchActive() {
    if (TradeActive){
        TradeActive = false;
    } else {
        TradeActive = true;
    }
  }

  bool TradeCheck(){
    return TradeActive;
  }
};