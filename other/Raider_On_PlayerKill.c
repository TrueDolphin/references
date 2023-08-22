modded class PlayerBase {

	override void EEKilled( Object killer )
	{
			PlayerBase p_killer = PlayerBase.Cast(killer);
			if (p_killer && !p_killer.IsAI()) {
				if (p_killer.Expansion_GetReputation() <= 5) {
					eAIGroup killerGroup = p_killer.GetGroup();
					if (!killerGroup) killerGroup = eAIGroup.GetGroupByLeader(p_killer);
					eAIFaction killerfaction = killerGroup.GetFaction();
					if (killerfaction.GetName() == "Raiders") return;
					Print("player: " + GetIdentity().GetName() + " changed to Raider faction");
					killerGroup.SetFaction(new eAIFactionRaiders());
				}
			}
			super.EEKilled(killer);
	}
}