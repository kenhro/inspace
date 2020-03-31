// convert binary input (inverse logic) values to index
int bcd2index(int v1, int v2, int v4, int v8){
  int result;
  result = 1 * (1 - v1) + 2 * (1 - v2) + 4 * (1 - v4) + 8 * (1 - v8);
  // FIXME what should we set index value to when internal state is out of bounds?
  if (result > 9) {result = 0;}
  return result;
}
