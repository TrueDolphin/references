
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


    static bool IsPointInBoxArea(vector point, float halfSize)
    {
        float minX, minY, minZ, maxX, maxY, maxZ;

        foreach (Classname object : s_objectarray)
        {
            vector pos = object.GetPosition();
            minX = pos[0] - halfSize;
            maxX = pos[0] + halfSize;
            minY = pos[1] - halfSize;
            maxY = pos[1] + halfSize;
            minZ = pos[2] - halfSize;
            maxZ = pos[2] + halfSize;

            if (point[0] >= minX && point[0] <= maxX &&
                point[1] >= minY && point[1] <= maxY &&
                point[2] >= minZ && point[2] <= maxZ)
            {
                return true;
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


    vector myPoint = "456 12 789";
    if (Classname.IsPointInBoxArea(myPoint, 1.5)) {
        Print("Point is inside a 3D box around a Classname object.");
    }


*/
