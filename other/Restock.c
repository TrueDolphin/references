supplied by LM

//3_Game/ExpansionMarketTraderZone.c

modded class ExpansionMarketTraderZone
{
    void IncrementStock( float percent )
    {
        IncrementStock_Internal(percent);
    }

    protected void IncrementStock_Internal( int percent )
    {
        foreach (string clsName, int stock: Stock)
        {
            ExpansionMarketItem marketItem = ExpansionMarketCategory.GetGlobalItem( clsName, false );
            if ( !marketItem )
                continue;

            percent = ( marketItem.MaxStockThreshold / 100 ) * percent;

            percent += Stock.Get( clsName );

            if ( percent > marketItem.MaxStockThreshold )
                percent = marketItem.MaxStockThreshold;

            if ( percent < marketItem.MinStockThreshold )
                percent = marketItem.MinStockThreshold;

            Stock.Set( clsName, percent );
        }
    }
};


//init.c

class CustomMission: MissionServer
{
    void OnMissionStart()
     {
        super.OnMissionStart();

        if ( IsScheaduledRestart() )
            UpdateTraderZones();
    }

    bool IsScheaduledRestart()
    {
        CF_Date now = CF_Date.Now();
        
        int hour = now.GetHours();
        int minute = now.GetMinutes();

        // is time between 7:50 and 8:10 since restart is 8:00 
        if ( hour > 6 && hour < 9 )
        {
            if ( minute < 10 || minute > 50 )
            {
                return true;
            }
        }
        
        return false;
    }

    void UpdateTraderZones()
    {
        IncrementStockForTraderzonePos("2640 200 5175", 10);
        IncrementStockForTraderzonePos("6510 0 2550", 3);
    }

    static void IncrementStockForTraderzonePos( vector position, float percent )
    {
        ExpansionMarketTraderZone traderZone = GetExpansionSettings().GetMarket().GetTraderZoneByPosition(position);
        if (!traderZone)
            return;
        
        traderZone.IncrementStock(percent);
        traderZone.Save();
    }
};
