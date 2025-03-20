//missionserver

override void InvokeOnDisconnect(PlayerBase player)
{
    super.InvokeOnDisconnect(player);
    BroadcastToOtherPlayers(player.GetIdentity(), GetLeaveMessage(player));
}

override void InvokeOnConnect(PlayerBase player, PlayerIdentity identity)
{
    super.InvokeOnConnect(player, identity);
    BroadcastToOtherPlayers(identity, GetJoinMessage(player));
}

void BroadcastToOtherPlayers(PlayerIdentity excludeIdentity, string message)
{
    foreach (Man man : m_Players)
    {
        PlayerBase otherplayer = PlayerBase.Cast(man);
        if (!otherplayer) continue;
        if (otherplayer.GetIdentity() == excludeIdentity) continue;
  
        sendPlayerMessage(otherplayer, message);
    }
}

string GetLeaveMessage(PlayerBase player)
{
    return player.GetIdentity().GetName() + " has left.";
}

string GetJoinMessage(PlayerBase player)
{
    return player.GetIdentity().GetName() + " has joined.";
}

void sendPlayerMessage(PlayerBase player, string message)
{
    if (player && message != "")
    {
        Param1<string> Msgparam = new Param1<string>(message);
        GetGame().RPCSingleParam(player, ERPCs.RPC_USER_ACTION_MESSAGE, Msgparam, true, player.GetIdentity());
    }
}
