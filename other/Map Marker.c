
//in class
#ifdef EXPANSIONMODNAVIGATION
   //declares
	ExpansionMarkerModule m_MarkerModule;
	ExpansionMarkerData m_ServerMarker;

    
    void CreateMissionMarker(vector pos, string name, int timer, int remove = 0)
    {
    if (CF_Modules<ExpansionMarkerModule>.Get(m_MarkerModule))
	{
        m_ServerMarker = m_MarkerModule.CreateServerMarker(name, "Territory", pos, ARGB(255, 235, 59, 90), true);
        if (remove == 1)
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(RemoveMissionMarker, timer, false, m_ServerMarker.GetUID());
    }

    }

	void RemoveMissionMarker(string uid)
	{
		if ( !m_ServerMarker )
		return;
		m_MarkerModule.RemoveServerMarker( uid );
	}
#endif


//to use in class

  #ifdef EXPANSIONMODNAVIGATION
        int Remove = 1;
        CreateMissionMarker("10 5 10", "Map Marker", 50000, Remove);
  #endif
