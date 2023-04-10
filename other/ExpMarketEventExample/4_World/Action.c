
modded class ExpansionActionOpenTraderMenu {

    override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
        {
            ExpansionTraderObjectBase TraderTarget = ExpansionMarketModule.GetTraderFromObject(target.GetObject(), false);
            if (TraderTarget) {
                if (!TraderTarget.TradeCheck()) return false;
            }

            return super.ActionCondition(player, target, item)
        }

   }