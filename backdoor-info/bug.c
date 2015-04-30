// https://llvm.org/bugs/show_bug.cgi?id=15940

int puts(const char *);

int x = 1;

void bug(void) {
  if (5 % (3 * x) + 2 != 4)
    puts("bug!");
  else
    puts("no bug");
}

int main(void) {
  bug();
  return 0;
}
