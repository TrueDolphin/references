//ideas

/*
class Grid {
    private string[,] gridData;

    void Init(int rows, int cols) {
        gridData = new string[rows, cols];
        // Initialize gridData with empty values or specific characters
    }

    void Display() {
        string gridStr = "";
        for (int row = 0; row < gridData.GetLength(0); row++) {
            for (int col = 0; col < gridData.GetLength(1); col++) {
                gridStr += gridData[row, col] + " ";
            }
            gridStr += "\n";
        }
        Print(gridStr);
    }

    void UpdateCell(int row, int col, string value) {
        if (row >= 0 && row < gridData.GetLength(0) && col >= 0 && col < gridData.GetLength(1)) {
            gridData[row, col] = value;
        }
    }
}

// Example usage
Grid grid = new Grid();
grid.Init(5, 5);

grid.Display();

grid.UpdateCell(2, 3, "X");
grid.Display();
*/
//---------------------------------------------------------------------
/*
class Grid
{
	private map<vector, string> m_Data;

	void SetCell(vector position, string value)
	{
		m_Data.Set(position, value);
	}

	string GetCell(vector position)
	{
		return m_Data.Get(position);
	}

	void ClearCell(vector position)
	{
		m_Data.Remove(position);
	}

	void PrintGrid()
	{
		for (int i = 0; i < m_Data.Count(); i++)
		{
			vector position = m_Data.GetKey(i);
			string value = m_Data.GetElement(i);
			Print(string.Format("Position: %1, Value: %2", position, value));
		}
	}
}

void main()
{
	Grid grid = new Grid();

	vector cell1 = Vector(0, 0, 0);
	vector cell2 = Vector(1, 0, 0);
	vector cell3 = Vector(0, 1, 0);

	grid.SetCell(cell1, "A");
	grid.SetCell(cell2, "B");
	grid.SetCell(cell3, "C");

	grid.PrintGrid();
}
*/


//---------------------------------------------------------------------
class GridCell
{
	string m_Value;

	void SetValue(string value)
	{
		m_Value = value;
	}

	string GetValue()
	{
		return m_Value;
	}
}


class Grid
{
	private array<ref GridCell> m_GridData;

	Grid(int width, int height)
	{
		InitGrid(width, height);
	}

	private void InitGrid(int width, int height)
	{
		m_GridData = new array<ref GridCell>;

		for (int i = 0; i < width * height; i++)
		{
			m_GridData.Insert(new GridCell());
		}
	}

	GridCell GetCell(int x, int y)
	{
		int index = y * GetWidth() + x;
		if (index >= 0 && index < m_GridData.Count())
		{
			return m_GridData.Get(index);
		}
		return null;
	}

	int GetWidth()
	{
		return m_GridData.Count() / GetHeight();
	}

	int GetHeight()
	{
		return m_GridData.Count() > 0 ? m_GridData.Count() / GetWidth() : 0;
	}

	void PrintGrid()
	{
		for (int y = 0; y < GetHeight(); y++)
		{
			for (int x = 0; x < GetWidth(); x++)
			{
				GridCell cell = GetCell(x, y);
				string value = cell ? cell.GetValue() : " ";
				Print(value);
			}
			Print("");
		}
	}
}

void main()
{
	Grid grid = new Grid(3, 3);

	GridCell cell1 = grid.GetCell(0, 0);
	cell1.SetValue("A");

	GridCell cell2 = grid.GetCell(1, 1);
	cell2.SetValue("B");

	GridCell cell3 = grid.GetCell(2, 2);
	cell3.SetValue("C");

	grid.PrintGrid();
}


