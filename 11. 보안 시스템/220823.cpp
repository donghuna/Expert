// FAIL

int N;
int arr[1005];

int bitCount(int a)
{
  int count = 0;
  for (int i = 0; i < 12; ++i)
  {
    if (a & (1 << i)) count++;
  }
  return count;
}

int findFirstBit(int x, int y)
{
  for (int i = 0; i < 12; ++i)
  {
    if (x & (1 << i))
    {
      if ((y & (1 << i)) == 0)
      {
        return i + 1;
      }
    }
  }
  return -1;
}

int encoding(int x, int y)
{
  if (N < 10) {
    for (int i = 0b000000111111; i <= 0b111111000000; ++i)
    {
      if (bitCount(i) == 6)
      {
        arr[N++] = i;
      }
    }
  }
  return (findFirstBit(arr[x], arr[y]));
}

char answer(int p, int k)
{
  if (arr[p] & (1 << (k - 1)))
    return 'x';
  else
    return 'y';
}
