class Rectangle
{
    int Width;
   int Height;
   bool IsPlaced;
   int X;
   int Y;

    void Rectangle(int width, int height)
    {
        Width = width;
        Height = height;
        IsPlaced = false;
        X = -1;
        Y = -1;
    }
}

 class RectanglePacker
{
    private int containerWidth;
    private int containerHeight;
    private ref array<Rectangle> rectangles;

    void RectanglePacker(int Width, int Height)
    {
        containerWidth = Width;
        containerHeight = Height;
        rectangles = new array<Rectangle>();
    }

    void AddRectangle(int width, int height)
    {
        rectangles.Insert(new Rectangle(width, height));
    }

    void PackRectangles()
    {
        foreach (auto rect : rectangles)
        {
            if (!rect.IsPlaced)
            {
                // Find the first available position to fit the rectangle
                for (int y = 0; y <= containerHeight - rect.Height; y++)
                {
                    for (int x = 0; x <= containerWidth - rect.Width; x++)
                    {
                        if (CanPlaceRectangle(rect, x, y))
                        {
                            PlaceRectangle(rect, x, y);
                            break;
                        }
                    }
                    if (rect.IsPlaced)
                        break;
                }
            }
        }
    }

    private bool CanPlaceRectangle(Rectangle rect, int x, int y)
    {
        // Check if the rectangle fits within the container boundaries
        if (x + rect.Width > containerWidth || y + rect.Height > containerHeight)
            return false;

        // Check if the rectangle overlaps with any placed rectangle
        foreach (auto placedRect : rectangles)
        {
            if (placedRect.IsPlaced && x < (placedRect.X + placedRect.Width) && (x + rect.Width) > placedRect.X && y < (placedRect.Y + placedRect.Height) && (y + rect.Height) > placedRect.Y)
            {
                return false;
            }
        }

        return true;
    }

    private void PlaceRectangle(Rectangle rect, int x, int y)
    {
        rect.X = x;
        rect.Y = y;
        rect.IsPlaced = true;
    }

    array<Rectangle> GetUnplacedRectangles()
    {
        array<Rectangle> unplacedRectangles = new array<Rectangle>();
        foreach (auto rect : rectangles)
        {
            if (!rect.IsPlaced)
            {
                unplacedRectangles.Insert(rect);
            }
        }
        return unplacedRectangles;
    }



}

 class Program
{
    static void Main(string[] args)
    {
        // Create a rectangle packer with a container size of 10x6
        RectanglePacker packer = new RectanglePacker(10, 6);

        // Add rectangles to pack within the container
        packer.AddRectangle(4, 3);
        packer.AddRectangle(3, 2);
        packer.AddRectangle(5, 2);
        packer.AddRectangle(2, 3);

        // Pack the rectangles into the container
        packer.PackRectangles();
        // Get the unplaced rectangles and print their dimensions
        array<Rectangle> unplacedRectangles = packer.GetUnplacedRectangles();
        if (unplacedRectangles.Count() > 0)
        {
            Print("Unplaced Rectangles:");
            foreach (auto rect : unplacedRectangles)
            {
                 Print("Width:" + rect.Width + " Height: " + rect.Height);
            }
        }
        else
        {
             Print("All rectangles were placed successfully!");
        }
    }
}
