int printf (const char *__restrict __format, ...);
int nondet_int();

int orig (int x) {
  int count = 0;
  int i;
  for (i=0; i<100; i++) {
    if (i == x)
      continue;
    count++;
  }
  return count;
}

int DEBUG_NOTICE = 1;

#define SUDO_DEBUG_NOTICE	4	/* non-error condition notices */

/* Perfect hash function for mapping debug levels to intended verbosity */
#define DEBUG_TO_VERBOSITY(d) (5 % (3 * (d)) + 2)

#define NORMALIZE_DEBUG_LEVEL(dbg_lvl) (DEBUG_TO_VERBOSITY(dbg_lvl) == SUDO_DEBUG_NOTICE)

#define sudo_debug_printf(level, str, ...) \
  printf(str, ##__VA_ARGS__)

#define debug_continue(condition, dbg_lvl, str, ...) {			       \
    if (NORMALIZE_DEBUG_LEVEL(dbg_lvl) && (condition)) {                       \
        sudo_debug_printf(SUDO_DEBUG_NOTICE, str, ##__VA_ARGS__);              \
        continue;                                                              \
    }                                                                          \
}

int patched (int x) {
  int count = 0;
  int i;
  for (i=0; i<100; i++) {
    debug_continue((i == x), DEBUG_NOTICE, "foo");
    count++;
  }
  return count;
}

int compare (void) {
  int x = nondet_int();
  __CPROVER_assert(orig(x) == patched(x), "");
}
