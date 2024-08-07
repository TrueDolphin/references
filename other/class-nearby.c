
// rename Classname to your item classname

modded class Classname
{
    static ref array < Classname > s_objectarray;

    void Classname() {
    if (!s_objectarray) s_objectarray = {}; 
        s_objectarray.Insert(this);
    }

    void~Classname() {
        if (s_objectarray) s_objectarray.RemoveItem(this);
    }

    static array < Classname > ClassnameList() {
        if (!s_objectarray) s_objectarray = {};
        return s_objectarray;
    }


    static int GetVicinityCount(EntityAI entity, int range = 100) {
        int count = 0;
        range *= range;
        vector position = entity.GetPosition();
        foreach(Classname object: s_objectarray) {
            if (vector.DistanceSq(object.GetPosition(), position) < range) {
                ++count;
            }
        }
        return count;  
    }

    static bool IsInVicinity(EntityAI entity, int range = 100) {
        range *= range;
        vector position = entity.GetPosition();
        foreach(Classname object: s_objectarray) {
            if (vector.DistanceSq(object.GetPosition(), position) < range) {
                if (object.GetCompEM().IsSwitchedOn()) return true;
            }
        }
        return false;
    }
};




/*
    uses:
    if (Classname.IsInVicinity(targetclass, 50))
    {
        Print("there's at least one within 50m of " + targetclass.GetType());
    }

    int count = Classname.GetVicinityCount(targetclass, 50);
    Print("there's " + count + " type of " + targetclass.GetType() + " within 50m");
    //Print(string.Format("Total %2 Found: %1 - within 50m", count, targetclass.GetType()));
*/
