package hero5

import java.util.*

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readLong() = readLn().toLong()
private fun readDouble() = readLn().toDouble()
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map { it.toInt() }
private fun readLongs() = readStrings().map { it.toLong() }
private fun readDoubles() = readStrings().map { it.toDouble() }

fun main() {
  val (n, k, x) = readInts()
  val a = readInts()

  fun check(m: Long): Boolean {
    var ans = 0
    var cnt = 0
    var sum = 0L
    val mp = TreeMap<Int, Int>()
    for (y in a) {
      if (y > m) {
        ans++
        continue
      }
      sum += y
      cnt++
      mp[y] = mp.getOrDefault(y, 0) + 1
      while (sum > m) {
        var last = mp.lastEntry()
        sum -= last.key
        cnt--
        ans++
        if (last.value == 1) {
          mp.remove(last.key)
        } else {
          mp[last.key] = last.value - 1
        }
      }
      if (cnt == x) {
        cnt = 0
        sum = 0L
        mp.clear()
      }
    }
    return ans <= k
  }

  var l = 0L
  var r = 1e10.toLong() + 1
  var ans = -1L
  while (l <= r) {
    val m = (l + r) / 2L
    if (check(m)) {
      ans = m
      r = m - 1
    } else {
      l = m + 1
    }
  }
  println(ans)
}
