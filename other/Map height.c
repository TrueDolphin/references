void GlobalHeights(out float high, out float low, out float average)
 {
        vector pos = Vector(0,0,0);
   int count = 0;
   int step = 4;
        for (pos[0] = 0; pos[0] <= GetGame().GetWorld().GetWorldSize(); pos[0] = pos[0] + step)
        {
            for (pos[2] = 0; pos[2] <= GetGame().GetWorld().GetWorldSize(); pos[2] = pos[2] + step)
            {
      float check = GetGame().SurfaceY(pos[0], pos[2]);
                average += check;
      if (check > high) high = check;
      if (check < low) low = check;
      ++count;
     }
   }
   average / count;
 }
