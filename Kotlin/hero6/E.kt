package hero6

private fun readLn() = readLine()!! // string line
private fun readInt() = readLn().toInt() // single int
private fun readLong() = readLn().toLong() // single long
private fun readDouble() = readLn().toDouble() // single double
private fun readStrings() = readLn().split(" ") // list of strings
private fun readInts() = readStrings().map { it.toInt() } // list of ints
private fun readLongs() = readStrings().map { it.toLong() } // list of longs
private fun readDoubles() = readStrings().map { it.toDouble() } // list of doubles

class SegTree1(val n: Int) {
  private val a = IntArray(4 * n + 20) { 0 }
  private val tag = IntArray(4 * n + 20) { 0 }

  private fun apply(u: Int, x: Int) {
    a[u] += x
    tag[u] += x
  }
  private fun pushup(u: Int) {
    a[u] = maxOf(a[u * 2], a[u * 2 + 1])
  }
  private fun pushdown(u: Int) {
    apply(u * 2, tag[u])
    apply(u * 2 + 1, tag[u])
    tag[u] = 0;
  }

  fun update(i: Int, x: Int, l: Int = 0, r: Int = n, rt: Int = 1) {
    if (l == r) {
      a[rt] = x
      tag[rt] = 0
      return
    }
    val m = (l + r) / 2
    pushdown(rt)
    if (i <= m) update(i, x, l, m, rt * 2)
    else update(i, x, m + 1, r, rt * 2 + 1)
    pushup(rt)
  }

  fun query(L: Int, R: Int, l: Int = 0, r: Int = n, rt: Int = 1): Int {
    if (L <= l && r <= R) {
      return a[rt]
    }
    val m = (l + r) / 2
    pushdown(rt)
    if (R <= m) return query(L, R, l, m, rt * 2)
    else if (L > m) return query(L, R, m + 1, r, rt * 2 + 1)
    else return maxOf(query(L, R, l, m, rt * 2), query(L, R, m + 1, r, rt * 2 + 1))
  }

  val ans get() = a[1]
}

fun main() {
  val T = readInt()
  for (cas in 0 until T) {
    val n = readInt()
    val a = readInts()
    val evs = (0 .. n).map { 0 }.toMutableList()
    val first = (0 .. n).map { -1 }.toMutableList()
    val last = (0 .. n).map { -1 }.toMutableList()
    val cnt = (0 .. n).map { 0 }.toMutableList()
    for (i in 0 until n) {
      if (first[a[i]] != -1) {
        evs[first[a[i]]] += 2
        evs[i + 1] -= 2
      } else {
        first[a[i]] = i
      }
      cnt[a[i]]++
      last[a[i]] = i
    }
    val f = SegTree1(n)
    var ans = 0
    for (i in 0 until n) {
      if (cnt[a[i]] == 1) {
        val cur = f.query(i + 1, n)
        f.update(i, cur + 1)
        ans = maxOf(ans, cur + 1)
      } else if (cnt[a[i]] == 2) {
        if (i == first[a[i]]) {
          val cur = 2 + f.query(last[a[i]] + 1, n)
          f.update(last[a[i]], cur)
          ans = maxOf(ans, cur + (if (i + 1 < last[a[i]]) 1 else 0))
        }
      }
    }
    println(ans)
  }
}
