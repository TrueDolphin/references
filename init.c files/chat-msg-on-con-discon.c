
  override void InvokeOnDisconnect(PlayerBase player)
{
    //message all on disconnect
    super.InvokeOnDisconnect(player);
    array < Man > players = new array < Man > ;
    GetGame().GetPlayers(players); 
    for (int i = 0; i < players.Count(); ++i)
    {
      PlayerBase otherplayer = PlayerBase.Cast(players[i]);
      if (!otherplayer) return;
      if (!otherplayer.GetIdentity() || otherplayer.GetIdentity() == identity)
      return;
      string Name = player.GetIdentity().GetName();
      sendPlayerMessage(otherplayer, Name + " has left.");
    }
}

  override void InvokeOnConnect(PlayerBase player, PlayerIdentity identity) 
{
    //message all on connect
    super.InvokeOnConnect(player, identity);
    array < Man > players = new array < Man > ;
    GetGame().GetPlayers(players); 
    for (int i = 0; i < players.Count(); ++i)
    {
      PlayerBase otherplayer = PlayerBase.Cast(players[i]);
      if (!otherplayer) return;
      if (!otherplayer.GetIdentity() || otherplayer.GetIdentity() == identity)
      return;
      string Name = player.GetIdentity().GetName();
      sendPlayerMessage(otherplayer, Name + " has joined.");
    }
}

  protected void sendPlayerMessage(PlayerBase player, string message) 
{
    if ((player) && (message != "")) 
    {
      Param1 < string > Msgparam;
      Msgparam = new Param1 < string > (message);
      GetGame().RPCSingleParam(player, ERPCs.RPC_USER_ACTION_MESSAGE, Msgparam, true, player.GetIdentity());
     }
  }