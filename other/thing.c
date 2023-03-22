	override float ProcessVehicleThreat(eAIBase ai, float distance) {

	  Transport transport;
	  if (!Class.CastTo(transport, m_Player.GetParent()))
	    return 0.0;

	  if (transport.CrewMemberIndex(m_Player) != DayZPlayerConstants.VEHICLESEAT_DRIVER)
	    return 0.0;

	  if (!LoS_Check(m_Player, ai)) return 0.0;

	  float speed = Math.AbsFloat(transport.GetSpeedometer());
	  float distance = vector.Distance(vehiclePosition, objectPosition);
	  float distanceCovered = speed * 4; //arbitrary
	  if (distanceCovered >= distance) {
	    float fromTargetDot;
	    float levelFactor = eAIVehicleTargetInformation.ProcessVehicleThreat(transport, ai, distance, speed, fromTargetDot);
	    //PrintFormat("eAIPlayerTargetInformation dist %1 spd %2 dot %3 lvl %4", distance, speed, fromTargetDot, levelFactor);
	    return levelFactor;
	  } else {
	    return 0.0;
	  }

	}

	bool LoS_Check(DayZPlayer player, eAIBase ai) {

	  Transport transport;
	  if (!Class.CastTo(transport, m_Player.GetParent())) return false;

	  bool c_vision = false;
	  vector position, direction, rotation;
	  player.GetCurrentCameraTransform(position, direction, rotation);
	  position = position + direction * 20;
	  vector tpos = position + "0 1.5 0";
	  vector aipos = ai.GetPosition() + "0 1.5 0";
	  position[1] = GetGame().SurfaceY(position[0], position[2]);
	  PhxInteractionLayers collisionLayerMask = PhxInteractionLayers.BUILDING | PhxInteractionLayers.DOOR | PhxInteractionLayers.VEHICLE | PhxInteractionLayers.TERRAIN | PhxInteractionLayers.ITEM_SMALL | PhxInteractionLayers.ITEM_LARGE | PhxInteractionLayers.FENCE;
	  c_vision = DayZPhysics.RayCastBullet(tpos, aipos, collisionLayerMask, transport, ai, null, null, null)
	  return c_vision;
	}