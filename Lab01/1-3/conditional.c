/*
 * conditional(x, y, z): Return z if x is 0, return y otherwise.
 * - Ex) conditional(2, 4, 5) = 4, conditional(0, 1, 2) = 2
 * x가 0이면 z, 그외의 경우 y
 */
int conditional(int x, int y, int z) {
  int temp = !x;
  temp = ~temp + 1;
  return (y & ~temp) | (z & temp);
}
