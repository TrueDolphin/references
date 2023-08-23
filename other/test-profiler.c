#define DEVELOPER

class SpatialProfiler
{
    
	void SimulateWork()
	{
		EnProfilerTest2 m_Profiler = EnProfilerTest2.Cast(GetGame().CreateObjectEx( "EnProfilerTest2", "0 0 0", ECE_PLACE_ON_SURFACE ));
	}
};


class EnProfilerTest2 : TestFramework
{
	const ref SpatialAI spatialai = new SpatialAI();
    ref Spatial_Groups m_Spatial_Groups;

    // ... Existing code ...
	void EnProfilerTest2()
	{
		spatialai.Spatial_Init();
		AddInitTest("TestSpatialAIInit");
	}
    // Test profiling the spatialai.init() function
    TFResult TestSpatialAIInit()
    {
		array<Man> players();
		GetGame().GetPlayers(players);
        // Enable the profiler if not already enabled
        bool wasProfilerEnabled = EnProfiler.IsEnabledC();
        if (!wasProfilerEnabled)
        {
            EnProfiler.Enable(true, true);
        }

        // Measure the time taken by spatialai.init()
        float startTime = GetGame().GetTickTime();
        spatialai.Spatial_Check(players);
        float endTime = GetGame().GetTickTime();

        // Calculate the time taken for spatialai.init()
        float elapsedTime = endTime - startTime;

        // Output the profiling result
        spatialai.SpatialDebugPrint("Time taken for spatialai.init(): " + elapsedTime + " - TestSpatialAIInit");

        // Disable the profiler if it was initially disabled
        if (!wasProfilerEnabled)
        {
            EnProfiler.Enable(false, true);
        }

        // Perform assertions on the profiling result
        if (elapsedTime > 0)
        {
            // If the function took some time to execute, it's likely the profiling was successful
            return NTFR(TFR.SUCCESS);
        }
        else
        {
            // If the function executed too quickly, the profiling might not have worked as expected
            return NTFR(TFR.FAIL);
        }
    }
	void SpatialTimer() {
		array<Man> players();
		GetGame().GetPlayers(players);
		spatialai.SpatialDebugPrint("Spatial::Stack - Start");
		spatialai.Spatial_Check(players);
		spatialai.SpatialDebugPrint("Spatial::Stack - End");
		spatialai.SpatialLoggerPrint("Next debug check in: " + "300000" + "ms");
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(SpatialTimer, 300000, false);
	} //timer call for varied check loops #refactored by LieutenantMaster
}
