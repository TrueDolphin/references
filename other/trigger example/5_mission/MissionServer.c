//5_mission
modded class MissionServer
{
  void MissionServer()
  {
        MyPrefix_CustomTrigger trigger = MyPrefix_CustomTrigger.Cast(GetGame().CreateObjectEx("MyPrefix_CustomTrigger", vector.Zero, ECE_NONE));
        trigger.SetCollisionCylinder(50, 50);
  }
}