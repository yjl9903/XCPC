package hero6

private fun readLn() = readLine()!! // string line
private fun readInt() = readLn().toInt() // single int
private fun readLong() = readLn().toLong() // single long
private fun readDouble() = readLn().toDouble() // single double
private fun readStrings() = readLn().split(" ") // list of strings
private fun readInts() = readStrings().map { it.toInt() } // list of ints
private fun readLongs() = readStrings().map { it.toLong() } // list of longs
private fun readDoubles() = readStrings().map { it.toDouble() } // list of doubles

private class SegTree(val n: Int) {
  private val mn = IntArray(4 * n + 20) { 0 }
  private val sum = LongArray(4 * n + 20) { 0L }
  private val tag = IntArray(4 * n + 20) { -1 }

  private fun apply(u: Int, len: Int, x: Int) {
    mn[u] = x
    sum[u] = 1L * x * len
    tag[u] = x
  }
  private fun pushup(u: Int) {
    mn[u] = minOf(mn[u * 2], mn[u * 2 + 1])
    sum[u] = sum[u * 2] + sum[u * 2 + 1]
  }
  private fun pushdown(u: Int, l: Int, r: Int) {
    val m = (l + r) / 2
    if (tag[u] != -1) {
      apply(u * 2, m - l + 1, tag[u])
      apply(u * 2 + 1, r - m, tag[u])
      tag[u] = -1
    }
  }

  fun update(L: Int, R: Int, x: Int, l: Int = 0, r: Int = n, rt: Int = 1) {
    if (L <= l && r <= R) {
      apply(rt, r - l + 1, x)
      return
    }
    val m = (l + r) / 2
    pushdown(rt, l, r)
    if (L <= m) update(L, R, x, l, m, rt * 2)
    if (R > m) update(L, R, x, m + 1, r, rt * 2 + 1)
    pushup(rt)
  }

  fun query(L: Int, R: Int, l: Int = 0, r: Int = n, rt: Int = 1): Long {
    if (L <= l && r <= R) {
      return sum[rt]
    }
    val m = (l + r) / 2
    pushdown(rt, l, r)
    if (R <= m) return query(L, R, l, m, rt * 2)
    else if (L > m) return query(L, R, m + 1, r, rt * 2 + 1)
    else return query(L, R, l, m, rt * 2) + query(L, R, m + 1, r, rt * 2 + 1)
  }

  fun find(x: Int, l: Int = 0, r: Int = n, rt: Int = 1): Int {
    if (l == r) return l
    val m = (l + r) / 2
    pushdown(rt, l, r)
    if (mn[rt * 2] <= x) return find(x, l, m, rt * 2)
    else return find(x, m + 1, r, rt * 2 + 1)
  }
}

data class Event(val l: Int, val id: Int)

fun main() {
  val n = readInt()
  val c = readInts()
  val q = readInt()
  val ans = (0 until q).map { 0L }.toMutableList()
  val qry = (0 until n).map { ArrayList<Event>() }
  for (i in 0 until q) {
    val (L, R) = readInts()
    qry[R - 1].add(Event(L - 1, i))
  }
  val f = SegTree(n)
  for (i in 0 until n) {
    val id = f.find(c[i])
    assert(id <= i)
    f.update(id, i, c[i])
    for (ev in qry[i]) {
      ans[ev.id] = f.query(ev.l, i)
    }
  }
  print(ans.joinToString(" "))
}
