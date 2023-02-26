/*
class ConeVicinity{
        protected ref VicinityObjects m_VicinityObjects;
        
        float c_MaxTargetDistance = 100.0;
        float c_ConeAngle = 30.0;
        float c_ConeHeightMin = -0.5;
        float c_ConeHeightMax = 2.0;

    bool VicinityCheck(PlayerBase m_Player){
        m_VicinityObjects = new VicinityObjects;
		array<Object> vicinityObjects = new array<Object>;
        vector headingDirection = MiscGameplayFunctions.GetHeadingVector(m_Player);

		DayZPlayerUtils.GetEntitiesInCone(m_Player.GetPosition(), headingDirection, c_ConeAngle, c_MaxTargetDistance, c_ConeHeightMin, c_ConeHeightMax, vicinityObjects);
		vicinityObjects.RemoveItem(m_Player);
		m_VicinityObjects.TransformToVicinityObjects(vicinityObjects);

		for ( i = 0; i < m_VicinityObjects.Count(); i++ )
		{
            eAIBase ai = eAIBase.Cast(m_VicinityObjects.GetObject(i));
            if (ai){
            return true;
            }
        }
        return false;
    }
}

*/