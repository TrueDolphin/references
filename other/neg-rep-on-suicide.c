modded class DayZPlayerImplement
{
    override bool HandleDeath(int pCurrentCommandID)
    {
        #ifdef DZ_Expansion_Hardline
            if (CommitedSuicide() && GetGame().IsServer())
            {
                PlayerBase player = PlayerBase.Cast(this);
                if (player)
                {
                    int amount = 1000;
                    int rep = player.Expansion_GetReputation();
                    if (rep <= amount) 
                    {
                        player.Expansion_SetReputation(0);
                    }
                    else
                    {
                        player.Expansion_DecreaseReputation(amount);
                        Print("Rep removed from:" + player.GetIdentity().GetName() + " - due to suicide.");
                    }
                }
            }
        #endif
        return super.HandleDeath(pCurrentCommandID);
    }
}
