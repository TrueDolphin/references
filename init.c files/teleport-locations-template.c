modded class MissionServer {
    private const static string TELEPORT_FOLDER = "$profile:TeleportLocations\\";
    private const static string TELEPORT_SETTINGS = TELEPORT_FOLDER + "Settings.json";
    ref TeleportData m_TeleportData;


    void MissionServer() {
     //this probably wont trigger in an init.c
     //start it on first player connect
    if (!m_TeleportData){
    InitTeleportSettings();
    GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.TeleportCheck, 5000, true);
}
    }

void TeleportCheck()
 {
    for (int i = 0; i < m_Players.Count(); i++) {
      PlayerBase player = PlayerBase.Cast(m_Players[i]);
      if (!player || !player.IsAlive() || !player.GetIdentity()) continue;
      
      foreach(TeleportPoint point: m_TeleportData.Point) {
      if (vector.Distance(player.GetPosition, point.FromPoint) > 50) {
        player.SetPosition(point.ToPoint)
      }
    }
  }
 }

void InitTeleportSettings() {
    if (!FileExist(TELEPORT_SETTINGS)) {
      if (!FileExist(TELEPORT_FOLDER)) MakeDirectory(TELEPORT_FOLDER);
      DefaultTeleportSettings(m_TeleportData);
      JsonFileLoader < TeleportData > .JsonSaveFile(TELEPORT_SETTINGS, m_TeleportData);
    } else {
        m_TeleportData = new TeleportData();
      JsonFileLoader < TeleportData > .JsonLoadFile(TELEPORT_SETTINGS, m_TeleportData);
    }
  }
  void DefaultTeleportSettings(out TeleportData Data) {
    Data = new TeleportData();
    Data.Point.Insert(new TeleportPoint("1.0 1.0 1.0", "0.0 0.0 0.0"));
    Data.Point.Insert(new TeleportPoint("1.0 1.0 1.0", "0.0 0.0 0.0"));
    Data.Point.Insert(new TeleportPoint("1.0 1.0 1.0", "0.0 0.0 0.0"));
  }
}
class TeleportData {
    int Version = 1;
    void TeleportData() {
      Point = new array < ref TeleportPoint > ;
    }
  }
class TeleportPoint {
  vector FromPoint;
  vector ToPoint;
  void TeleportPoint(vector a, vector b) {
    FromPoint = a;
    ToPoint = b;
  }
};