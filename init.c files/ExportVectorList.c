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

		ExportVectorList();
	}


	void ExportVectorList()
	{
		string basePath = "$profile:ExportedVectors/";
		MakeDirectory(basePath);

		string path = basePath + "vectors.txt";
		FileHandle file = OpenFile(path, FileMode.WRITE);
		if (!file) {
			Print("Failed to create file for vector export");
			return;
		}

		Print("============Export Coords===============");
		TVectorArray positions = new TVectorArray();
	
		//add yours here
		positions.Insert("442 0 5544");
		positions.Insert("862 0 2144");
		positions.Insert("2224 0 8774");
		//etc

		foreach (vector pos : positions)
		{
			FPrintln(file, Vector(pos[0], GetGame().SurfaceY(pos[0], pos[2]), pos[2]));
		}
		CloseFile(file);
		Print("============End Export===============");
	}
};

Mission CreateCustomMission(string path)
{
	return new CustomMission();
}