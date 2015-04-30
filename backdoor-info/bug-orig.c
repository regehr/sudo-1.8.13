int x = 1;
int main (void)
{
  if ( 5 % ( 3 * x ) + 2 != 4 ) __builtin_abort();
  return 0;
}
