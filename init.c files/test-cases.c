
void main() {
  //INIT ECONOMY--------------------------------------
  Hive ce = CreateHive();
  if (ce)
    ce.InitOffline();

  //DATE RESET AFTER ECONOMY INIT-------------------------
  int year, month, day, hour, minute;
  int reset_month = 9, reset_day = 20;

  GetGame().GetWorld().GetDate(year, month, day, hour, minute);

  if ((month == reset_month) && (day < reset_day)) {
    GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
  } else {
    if ((month == reset_month + 1) && (day > reset_day)) {
      GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
    } else {
      if ((month < reset_month) || (month > reset_month + 1)) {
        GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
      }
    }
  }
}

class CustomMission: MissionServer {
      const int count = 2000000;
          
  void CustomMission()
  {
    TestStringConCat();
  }

  void TestStringConCat(Hive ce1 = null, Hive ce = null, string msg = "abcdefg", int interm = 0){
      for (int i = 1; i <= 4; i++) {
        testcases.testcase(i, count, 10);
      }
    }
}
Mission CreateCustomMission(string path) {
  return new CustomMission();
}


class testcases
{
  static void testcase(int casenumber, int loops, int iterations)
  {
    TFloatArray times = {};
    vector dist1 = "0 5 0", dist2 = "6 2 4";
    Matrix3 mat = new Matrix3();
    int i, j, idx;
    float k;
    switch (casenumber)
    {
      case 1:
      {
        times = {};
        times.Insert(GetGame().GetTickTime());
        Print(GetGame().GetTickTime().ToString() + " - test :" + casenumber);
        for (j = 0; j < iterations; j++) {
          Print(GetGame().GetTickTime().ToString() + " - iteration :" + (j + 1));
          for (i = 0; i < loops; i++) {
            float testa = findSqrt(vector.DistanceSq(dist1, dist2));
          }
          times.Insert(GetGame().GetTickTime() - times[j - 1]);
        }
        Print(GetGame().GetTickTime().ToString() + " - test end :" + casenumber);
        i = times.Count();
        k = 0;
        for (idx = 1; idx < i; idx++) k += times[idx];
        k -= times[0];
        k = k / (i - 1);
        Print(" - average :" + k);
        break;
      }
      case 2:
      {
        times = {};
        times.Insert(GetGame().GetTickTime());
        Print(GetGame().GetTickTime().ToString() + " - test :" + casenumber);
        for (j = 0; j < iterations; j++) {
          Print(GetGame().GetTickTime().ToString() + " - iteration :" + (j + 1));
          for (i = 0; i < loops; i++) {
            float testb = Math.Sqrt(vector.DistanceSq(dist1, dist2));
          }
          times.Insert(GetGame().GetTickTime() - times[j - 1]);
        }
        Print(GetGame().GetTickTime().ToString() + " - test end :" + casenumber);
        i = times.Count();
        k = 0;
        for (idx = 1; idx < i; idx++) k += times[idx];
        k -= times[0];
        k = k / (i - 1);
        Print(" - average :" + k);
        break;
      }
      case 3:
      {
        times = {};
        times.Insert(GetGame().GetTickTime());
        Print(GetGame().GetTickTime().ToString() + " - test :" + casenumber);
        for (j = 0; j < iterations; j++) {
          Print(GetGame().GetTickTime().ToString() + " - iteration :" + (j + 1));
          for (i = 0; i < loops; i++) {
            VectorHelper.Rotate(mat, dist2);
          }
          times.Insert(GetGame().GetTickTime() - times[j - 1]);
        }
        Print(GetGame().GetTickTime().ToString() + " - test end :" + casenumber);
        i = times.Count();
        k = 0;
        for (idx = 1; idx < i; idx++) k += times[idx];
        k -= times[0];
        k = k / (i - 1);
        Print(" - average :" + k);
        break;
      }
      case 4:
      {
        times = {};
        times.Insert(GetGame().GetTickTime());
        Print(GetGame().GetTickTime().ToString() + " - test :" + casenumber);
        for (j = 0; j < iterations; j++) {
          Print(GetGame().GetTickTime().ToString() + " - iteration :" + (j + 1));
          for (i = 0; i < loops; i++) {
            VectorHelper2.Rotate(mat, dist2);
          }
          times.Insert(GetGame().GetTickTime() - times[j - 1]);
        }
        Print(GetGame().GetTickTime().ToString() + " - test end :" + casenumber);
        i = times.Count();
        k = 0;
        for (idx = 1; idx < i; idx++) k += times[idx];
        k -= times[0];
        k = k / (i - 1);
        Print(" - average :" + k);
        break;
      }
    }
  }

  static float findSqrt(float number)
{
    for (float s = number; (s - number / s) > 0.01; s = (s + number / s) / 2);
    return s;
}




/*
EntityAI FindAttachmentBySlotName(string name)
{
  EntityAI RailExists;
  return RailExists;
}

bool CanDisplayAttachmentSlot(int slot_id) {
    if (InventorySlots.GetSlotIdFromString("weaponOpticsCover") == slot_id) {
        Print("test" + !Print("") + "!");
        return FindAttachmentBySlotName("Rail") != NULL || !Print(this + " RailExists false");
    }
    return false;
}
*/

}