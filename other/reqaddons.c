class AddonStructure
{
    string Name;
    ref array<string> RequiredAddons;

    void AddonStructure(string name, array<string> requiredAddons)
    {
        Name = name;
        RequiredAddons = requiredAddons;

        if (!requiredAddons)
            RequiredAddons = {};
    }
}

class AddonLoader
{
    protected static ref array<ref AddonStructure> m_Addons;

    protected static const string CFG_PATCHES = "CfgPatches";
    protected static const string REQ_ADDONS = "requiredAddons";

    static array<ref AddonStructure> GetAddons()
    {
        if (!m_Addons)
        {
            m_Addons = {};
            int count = GetGame().ConfigGetChildrenCount(CFG_PATCHES);

            for (int i = 0; i < count; i++)
            {
                string addonName;
                GetGame().ConfigGetChildName(CFG_PATCHES, i, addonName);

                array<string> requiredAddons = {};
                GetGame().ConfigGetTextArray(string.Format("%1 %2 %3", CFG_PATCHES, addonName, REQ_ADDONS), requiredAddons);

                AddonStructure addon = new AddonStructure(addonName, requiredAddons);
                m_Addons.Insert(addon);
            }
        }

        return m_Addons;
    }

    static bool ExportToFile(string filePath)
    {
        FileHandle file = OpenFile(filePath, FileMode.WRITE);
        if (!file) return false;

        FPrintln(file, ExportToJson());
        CloseFile(file);

        return true;
    }

    static string ExportToJson()
    {
        string output;
        JsonSerializer js = new JsonSerializer();

        if (!js.WriteToString(GetAddons(), true, output))
            return "{}";

        return output;
    }

    static void DebugPrint()
    {
        array<string> lines = {};
        ExportToJson().Split("\n", lines);

        for (int i = 0; i < lines.Count(); i++)
            Print(lines[i]);
    }
}