void main()
{
	//INIT ECONOMY--------------------------------------
	Hive ce = CreateHive();
	if ( ce )
		ce.InitOffline();

	//DATE RESET AFTER ECONOMY INIT-------------------------
	int year, month, day, hour, minute;
	int reset_month = 9, reset_day = 20;
	GetGame().GetWorld().GetDate(year, month, day, hour, minute);

	if ((month == reset_month) && (day < reset_day))
	{
		GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
	}
	else
	{
		if ((month == reset_month + 1) && (day > reset_day))
		{
			GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
		}
		else
		{
			if ((month < reset_month) || (month > reset_month + 1))
			{
				GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
			}
		}
	}
}

class CustomMission: MissionServer
{

	void CustomMission()
	{

		SaveAllAmmoTrajectories();

		/*
		array<vector> positions;
		array<Object> hitObjects;
		bool hitGround;
		string ammo = "Bullet_556x45";

		SimulateBulletTrajectory(ammo, Vector(5300,220,5300) + vector.Up * 1.5, vector.Forward, positions, hitObjects, hitGround);
		Print(ammo);
		Print(positions.Count());
		Print(hitObjects.Count());
		Print(hitGround);
		*/
	}

	void SaveAllAmmoTrajectories()
	{
		string basePath = "$mission:AmmoTrajectories/";
		MakeDirectory(basePath);

		int ammoCount = GetGame().ConfigGetChildrenCount("CfgAmmo");
		string ammoName;

		for (int i = 0; i < ammoCount; i++) {
			GetGame().ConfigGetChildName("CfgAmmo", i, ammoName);
			SaveTrajectoryForAmmo(basePath, ammoName);
		}

		Print("Finished simulating all ammo types.");
	}


	void SaveTrajectoryForAmmo(string basePath, string ammoName)
	{


		string fullPath = "CfgAmmo " + ammoName;

        float initSpeed = GetGame().ConfigGetFloat(fullPath + " initSpeed");
        float airFriction = GetGame().ConfigGetFloat(fullPath + " airFriction");

		if (initSpeed == 900.0 && airFriction == -0.0005) return;

		string path = basePath + ammoName + ".traj";
		FileHandle file = OpenFile(path, FileMode.WRITE);
		if (!file) {
			Print("Failed to create file for " + ammoName);
			return;
		}

		vector pos = "0 0 0"; // starting height
		pos[1] = GetGame().SurfaceY(pos[0], pos[2])
		vector dir = vector.Forward + vector.Up; // +Z direction
		vector vel = dir.Normalized() * initSpeed;
		float g = 9.81;
		float t = 0;
		float dt = 0.01;
		float maxT = 50.0;
		FPrintln(file, fullPath);
		FPrintln(file, g.ToString());
		FPrintln(file, t.ToString());
		FPrintln(file, dt.ToString());
		FPrintln(file, maxT.ToString());
		FPrintln(file, initSpeed.ToString());
		FPrintln(file, airFriction.ToString());

		array<vector> positions = {};

		while (t < maxT) {
			positions.Insert(pos);
			vector nextPos = pos + vel * dt;

			float groundY = GetGame().SurfaceY(nextPos[0], nextPos[2]);
			if (nextPos[1] <= groundY) {
				positions.Insert(Vector(nextPos[0], groundY, nextPos[2]));
				break;
			}

			float speed = vel.Length();
			vector drag = vel.Normalized() * (airFriction * speed * speed);
			vector acc = vector.Up * -g + drag;
			vel += acc * dt;
			pos = nextPos;
			t += dt;
		}
		FPrintln(file, positions.Count().ToString());

		if (positions.Count() >= 2) {
			float totalDistance = vector.Distance(positions[0], positions[positions.Count() - 1]);
			FPrintln(file, "Distance: " + totalDistance.ToString());
		}
		foreach (vector p : positions)
		{
			p[1] = p[1] - GetGame().SurfaceY(p[0], p[2]);
			FPrintln(file, p.ToString());
		}
		CloseFile(file);
		Print("Saved: " + ammoName + " (" + positions.Count() + " points)");
	}

	static void SimulateBulletTrajectory(string ammoType, vector startPos, vector direction, out array<vector> outPositions, out array<Object> outHitObjects, out bool endedOnGround)
    {
        outPositions = {};
        outHitObjects = {};
        endedOnGround = false;

        string ammoPath = "CfgAmmo " + ammoType;
        float initSpeed = GetGame().ConfigGetFloat(ammoPath + " initSpeed");
        float airFriction = GetGame().ConfigGetFloat(ammoPath + " airFriction");

        float timeStep = 0.01;
        float maxTime = 3.0;
        float gravity = 9.81;

        vector velocity = direction.Normalized() * initSpeed;
        vector position = startPos;
        float t = 0;

        while (t < maxTime)
        {
            outPositions.Insert(position);
            vector nextPosition = position + velocity * timeStep;

            float terrainHeight = GetGame().SurfaceY(nextPosition[0], nextPosition[2]);
            if (nextPosition[1] <= terrainHeight)
            {
                endedOnGround = true;
                break;
            }

            set<Object> hitObjects = new set<Object>();
            vector hitPos;
			int hitObject;
            if (DayZPhysics.RaycastRV(position, nextPosition, hitPos, direction, hitObject, hitObjects, null, null, false, false, ObjIntersectFire))
            {
                foreach (Object obj : hitObjects)
                {
                    if (outHitObjects.Find(obj) == -1)
                        outHitObjects.Insert(obj);
                }
                break;
            }
            float speed = velocity.Length();
            vector drag = velocity.Normalized() * (airFriction * speed * speed);
            vector gravityVec = vector.Up * - gravity;

            vector acceleration = gravityVec + drag;
            velocity += acceleration * timeStep;
            position = nextPosition;
            t += timeStep;
        }
    }

};

Mission CreateCustomMission(string path)
{
	return new CustomMission();
}