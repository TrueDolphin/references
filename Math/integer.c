

/* saving for later
branchless - odd/even array

  static bool CountOddElements(array<int> list, out int total, int odd = 0){
    foreach(int number : list){
      odd = number & 1;
      total += odd * number;
    }
    return total > 0;
  )
*/