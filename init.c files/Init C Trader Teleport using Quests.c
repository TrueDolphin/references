/**
macca's script refactored
//This is the script to TP GMT to Trader
https://discord.com/channels/523890175563137034/718183000969576540/1200651177050783905
 */

	//This is the script to TP GMT to Trader
	override void Expansion_OnQuestCompletion(ExpansionQuest quest)
    {
     auto trace = EXTrace.Start(EXTrace.NAMALSKADVENTURE, this);   
        PlayerBase player = quest.GetPlayer();
        if (!player)
            return;
 
        array<vector> teleportPositions = {};
        switch (quest.GetQuestConfig().GetID())
        {
            //! Teleports the player after tuning-in quest with ID 1001 Destination Trader
            case 1001:
            {
                teleportPositions = {"7403.7 15.2188 2268.64","7416, 15.2188 2259.11"};
            }
            break;            
 
		    //! Teleports the player after tuning-in quest with ID 1002 Destination GMT
            case 1002:
            {
                teleportPositions = {"2989.55 342.098 7460.82", "2989.62 342.496 7483.88"};
            }
			break;
			//! Teleports the player after tuning-in quest with ID 1003 Destination Altar
            case 1003:
            {
                teleportPositions = {"8093.82 458.862 9326.36", "8099.01 458.761 9329.34"};
            }
			break;
			//! Teleports the player after tuning-in quest with ID 1004 Destination Klen
            case 1004:
            {
                teleportPositions = {"10969.2 232.79 11700.2", "10958.7 233.402 11690.6"};
            }
			break;
		}
        if (teleportPositions.Count() > 0)
            DayZPlayerSyncJunctures.ExpansionTeleport(player, teleportPositions.GetRandomElement(), player.GetOrientation());
    }