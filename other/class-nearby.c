
// rename Classname to your item Classname

class Classname
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


    static bool IsPointInOrientedBoxArea(vector point, float halfSize)
    {
        foreach (Classname object : s_objectarray)
        {
            vector objPos = object.GetPosition();
            vector objOri = object.GetOrientation();

            vector mat[3];
            objOri.RotationMatrixFromAngles(mat);

            vector local = (point - objPos).InvMultiply3(mat);

            if (Math.AbsFloat(local[0]) <= halfSize && Math.AbsFloat(local[1]) <= halfSize && Math.AbsFloat(local[2]) <= halfSize)
                return true;
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
