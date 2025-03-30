static void Process(float accuracy = 7.5, string filePath = "$profile:\\Export\\Chernarus.DZHME")
    {
        FileSerializer file = new FileSerializer();
        if (!file.Open(filePath, FileMode.WRITE))
        {
            ErrorEx("Unable to open a write handle to '" + filePath + "'");
            return;
        }

        int worldSize = GetGame().GetWorld().GetWorldSize();
        file.Write("DZHME"); // header
        file.Write(worldSize); // write world size since map is squared
        file.Write(accuracy); // write the accuracy of the height map, so we can deserialize properly

        float prev = GetGame().SurfaceY(0.0, 0.0);
        int count = 1;

        for (float x = 0.0; x <= worldSize; x += accuracy)
        {
            for (float z = 0.0; z <= worldSize; z += accuracy)
            {
                float current = GetGame().SurfaceY(x, z);
                if (current == prev)
                {
                    ++count;
                }
                else
                {
                    file.Write(count);
                    file.Write(prev);

                    prev = current; // set new previous
                    count = 1; // reset count
                }
            }
        }
        if (count > 1)
        {
        file.Write(count);
        file.Write(prev);
        }
        file.Close(); // flush
    }
}
