//4_world

class MyPrefix_CustomTrigger: CylinderTrigger
{
  #ifdef SERVER

    override void Enter(TriggerInsider insider)
    {
      super.Enter(insider);
      PlayerBase player = PlayerBase.Cast(insider.GetObject());
      if (player) Message(player, "You entered the trigger area");
            
    }

    override void Leave(TriggerInsider insider)
    {
      super.Leave(insider);
      PlayerBase player = PlayerBase.Cast(insider.GetObject());
      if (player) Message(player, "You left the trigger area");

    }

    override protected bool CanAddObjectAsInsider(Object object)
    {
      if (!super.CanAddObjectAsInsider(object)) return false;
      PlayerBase player = PlayerBase.Cast(object);
      if (!player || !player.GetIdentity()) return false;
      return true;
    }

    void Message(PlayerBase player, string message)
    {
      if ((player) && (message != ""))
      {
          Param1 < string > Msgparam;
          Msgparam = new Param1 < string > (message);
          GetGame().RPCSingleParam(player, ERPCs.RPC_USER_ACTION_MESSAGE, Msgparam, true, player.GetIdentity());
      }
    }
  #endif
}