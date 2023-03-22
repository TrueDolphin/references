

modded class Clothing
{
    ref TStringArray a_ChangeMe = {"Hoodie_Black", "Hoodie_Brown", "Hoodie_Green", "Hoodie_Grey", "Hoodie_Red"};

    override bool CanPutInCargoClothingConditions( EntityAI parent )
    {

        if (parent.IsMan()){
            PlayerBase player = PlayerBase.Cast(parent)
            Clothing_Base bodyslot = Clothing_Base.Cast(player.FindAttachmentBySlotName("Body"));
            if (bodyslot){
                string current = bodyslot.GetType()
                foreach(string arraylist: a_ChangeMe){
                    if (current == arraylist) return false;
                }
            }
        }
       return super.CanPutInCargoClothingConditions(parent)
    }
}