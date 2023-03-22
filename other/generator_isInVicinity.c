class Fallujah_Generator: PowerGenerator {
 //make sure classname here matches config.cpp classname

//use:
//Fallujah_Generator.IsInVicinity(EntityAI entity, int range = 100)

 //slow
  static ref VicinityObjects m_VicinityObjects

  //fast
  static ref array < Fallujah_Generator > d_All = {};

  //slow
  static float c_MaxTargetDistance = 100.0;
  static float c_ConeAngle = 360.0;
  static float c_ConeHeightMin = -0.5;
  static float c_ConeHeightMax = 2.0;



  //fast additions
  void Fallujah_Generator() {
    if (!d_All) {
      d_All = {};
    }

    d_All.Insert(this);
  }

  void~Fallujah_Generator() {
    if (d_All) {
      d_All.RemoveItem(this);
    }
  }

  static bool IsInVicinity(EntityAI entity, int range = 100) {
    range *= range;
    vector position = entity.GetPosition();

    //slow way
    m_VicinityObjects = new VicinityObjects;
    array < Object > vicinityObjects = new array < Object > ;
    vector headingDirection = MiscGameplayFunctions.GetHeadingVector(entity);
    vector playerPos = entity.GetPosition();
    DayZPlayerUtils.GetEntitiesInCone(playerPos, headingDirection, c_ConeAngle, c_MaxTargetDistance, c_ConeHeightMin, c_ConeHeightMax, vicinityObjects);
    vicinityObjects.RemoveItem(entity);
    //m_VicinityObjects.TransformToVicinityObjects(vicinityObjects);
    foreach(EntityAI object: vicinityObjects) {
      if (object.IsKindOf("Fallujah_Generator")) {
        Print("Object: " + object);
        Print("pos: " + object.GetPosition());
        Print("isworking: " + object.GetCompEM().IsWorking());
        Print("me - iswitchedon: " + object.GetCompEM().IsSwitchedOn());
        Print("canwork: " + object.GetCompEM().CanWork());
        if (object.GetCompEM().IsSwitchedOn()) return true;
      }
    }

    //method 2 - the much better way
    foreach(Fallujah_Generator object2: d_All) {
      if (vector.DistanceSq(object2.GetPosition(), position) < range) {
        Print("-----------------------------------------------");
        Print("---------------------True 2----------------------");
        Print("Object: " + object2);
        Print("pos: " + object2.GetPosition());
        Print("isworking: " + object2.GetCompEM().IsWorking());
        Print("me - iswitchedon: " + object2.GetCompEM().IsSwitchedOn());
        Print("canwork: " + object2.GetCompEM().CanWork());
        Print("-----------------------------------------------");
        //if (object.GetCompEM().IsSwitchedOn()) return true;
      }
    }

    return false;
  }

  //irrelevant
  override void UpdateFuelMeter() {}

  override void StartLoopSound() {
    if (GetGame().IsClient() || !GetGame().IsMultiplayer()) {
      if (GetCompEM().IsWorking()) {
        PlaySoundSetLoop(m_EngineLoop, LOOP_SOUND, 0, 0);

        // Particle
        vector local_pos = "0.3 0.60 0.4";
        vector local_ori = "270 0 0";
        m_Smoke = new EffGeneratorSmoke();
        SEffectManager.PlayOnObject(m_Smoke, this, local_pos, local_ori);
      }
    }
  }
};