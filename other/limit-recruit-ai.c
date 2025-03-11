modded class ExpansionActionRecruitAI 
{
  override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) 
  {
      eAIGroup PlayerGroup = eAIGroup.Cast(player.GetGroup());
      if (PlayerGroup)
      {
        int groupcount = PlayerGroup.Count();
        if (groupcount >= 2) return false;
      }
    return super.ActionCondition(player, target, item);
  }
};
