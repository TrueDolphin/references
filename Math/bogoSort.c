class BogoSort {

//with a feline twist.

void BogoSort()
{
    array<int> cat_array = {3, 2, 4, 1, 0, 5, 3, 2, 4, 1, 55, 43};
    int num_cats = cat_array.Count();
    bogo_sort_cats(cat_array, num_cats);
    Print("Sorted cat array:");
    for (int paws = 0; paws < num_cats; paws++)
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