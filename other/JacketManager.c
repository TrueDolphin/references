class JacketManager {
  static ref array < ref FieldJacket > JacketArray = {};
  array < string > jacketVariation = {
    "FieldJacket_Colour_1",
    "FieldJacket_Colour_2",
    "FieldJacket_Colour_3",
    "FieldJacket_Colour_4"
  }

  void JacketManager() {
    if (!JacketArray) JacketArray = {};
    GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(JacketCETimer, 2000, true);
  }

  void~JacketManager() {
    if (JacketArray) JacketArray = {};
  }

  void JacketCETimer() {
    if (!JacketArray) JacketArray = {};

    foreach(JacketArray jacket: JacketArray) {
      if (!jacket) {
        int localIndex = JacketArray.Find(jacket);
        if (localIndex >= 0)
          JacketArray.Remove(localIndex);
      }
    }
    //do something to get some positions, or make an array of them
    if (JacketArray.Count() < 5) {
      JacketArray.Insert(GetGame().CreateObject(jacketVariation.GetRandomElement(), position, false, true));
    }
  }
}