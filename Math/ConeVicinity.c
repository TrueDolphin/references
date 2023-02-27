
class ConeVicinity{
        static ref VicinityObjects m_VicinityObjects
        
        static float c_MaxTargetDistance = 100.0;
        static float c_ConeAngle = 60.0;
        static float c_ConeHeightMin = -0.5;
        static float c_ConeHeightMax = 2.0;

    static bool VicinityCheck(PlayerBase m_Player){
        m_VicinityObjects = new VicinityObjects;
		array<Object> vicinityObjects = new array<Object>;
        vector headingDirection = MiscGameplayFunctions.GetHeadingVector(m_Player);
        vector playerPos = m_Player.GetPosition();
		DayZPlayerUtils.GetEntitiesInCone(playerPos, headingDirection, c_ConeAngle, c_MaxTargetDistance, c_ConeHeightMin, c_ConeHeightMax, vicinityObjects);
		vicinityObjects.RemoveItem(m_Player);
		m_VicinityObjects.TransformToVicinityObjects(vicinityObjects);
		for (int i = 0; i < m_VicinityObjects.Count(); i++)
		{
			 eAIBase ai = eAIBase.Cast(m_VicinityObjects.GetObject(i))
             if (ai) return true;
		}
        return false;
    }
};