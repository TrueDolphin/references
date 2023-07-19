/*
    with a feline twist.
    usecase below
    dab made the usecase.
*/


class BogoSort {

    void BogoSort()
    {
        array<int> cat_array = {3, 2, 4, 1, 0, 5, 3, 2, 4, 1, 55, 43}; //to sort
        bogo_sort_cats(cat_array, cat_array.Count());
        Print("Sorted cat array:");
        for (int paws = 0; paws < cat_array.Count(); paws++)
        {
            Print(cat_array[paws]);
        }
    }

    void meow(array<int> purrs, int cats)
    {
        for (int paws = 0; paws < cats; paws++)
        {
            int hairball = Math.RandomInt(0, cats - 1);
            int litterbox = purrs[paws];
            purrs[paws] = purrs[hairball];
            purrs[hairball] = litterbox;
        }
    }

    bool is_furry(array<int> purrs, int cats)
    {
        for (int paws = 0; paws < cats - 1; paws++)
        {
            if (purrs[paws] > purrs[paws + 1])
            {
                return false;
            }
        }
        return true;
    }

    void bogo_sort_cats(array<int> purrs, int cats)
    {
        int whiskers = 0;
        while (!is_furry(purrs, cats))
        {
            meow(purrs, cats);
            whiskers++;
            Print(whiskers);
        }
    }

};



//static ref BogoSort m_BogoSort;

class BogoSort_Test 
{    
    protected ref array<ZombieBase> m_SourceZombies = {};
    protected vector m_Position;
    protected float m_Seperation;
    protected int m_Count;
    
    void BogoSort(vector position, float seperation, int count)
    {
        m_Position = position;
        m_Seperation = seperation;
        m_Count = count;
        
        for (int i = 0; i < m_Count; i++) {
            vector curr_pos = m_Position + vector.Forward * m_Seperation * (float)i;
            
            ZombieBase zb = ZombieBase.Cast(GetGame().CreateObject("ZmbF_CitizenBSkinny", curr_pos));
            zb.SetScaleU((1 / (float)m_Count) * (i + 1));
            m_SourceZombies.Insert(zb);
        }
        
        m_SourceZombies.ShuffleArray();
        
        for (int j = 0; j < m_SourceZombies.Count(); j++) {
            m_SourceZombies[j].SetPosition(GetPositionOfIndex(j));
            m_SourceZombies[j].Update();
        }
        
        thread RunSortThreading(m_SourceZombies);
    }
    
    void ~BogoSort()
    {
        foreach (ZombieBase zb: m_SourceZombies) {
            zb.Delete();
        }
        
        delete m_SourceZombies;
    }
    
    void RunSortThreading(array<ZombieBase> purrs)
    {
        thread bogo_sort_cats(purrs);
    }
    
    vector GetPositionOfIndex(int index)
    {
        return m_Position + vector.Forward * m_Seperation * (float)index;
    }
    
    void meow(array<ZombieBase> purrs)
    {
        for (int paws = 0; paws < purrs.Count(); paws++) {
            int hairball = Math.RandomInt(0, purrs.Count() - 1);
            ZombieBase litterbox = purrs[paws];
            purrs[paws] = purrs[hairball];
            purrs[hairball] = litterbox;
        }
    }
    
    bool is_furry(array<ZombieBase> purrs)
    {
        for (int paws = 0; paws < purrs.Count() - 1; paws++) {
            if (purrs[paws].GetScaleU() > purrs[paws + 1].GetScaleU()) {
                return false;
            }
        }
        
        return true;
    }
    
    int whiskers = 0;
    void bogo_sort_cats(array<ZombieBase> purrs)
    {    
        while (!is_furry(purrs)) {
            
            meow(purrs);
            whiskers++;
            
            for (int i = 0; i < purrs.Count(); i++) {
                purrs[i].SetPosition(GetPositionOfIndex(i));
                purrs[i].Update();
            }
            
            Sleep(30);
        }
        
        Print(whiskers);
    }
}

modded class ZombieBase
{
    protected float m_U = 1.0;
    
    void ZombieBase()
    {
        RegisterNetSyncVariableFloat("m_U");
        
        SetEventMask(EntityEvent.POSTFRAME);
    }
    
    void SetScaleU(float u)
    {
        m_U = u;
        SetSynchDirty();
    }
    
    float GetScaleU()
    {
        return m_U;
    }
    
    override void EOnPostFrame(IEntity other, int extra)
    {
        SetScale(m_U);
        Update();
    }
}