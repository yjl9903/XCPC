package hero6

import kotlin.math.max
import kotlin.math.min

private fun readLn() = readLine()!! // string line
private fun readInt() = readLn().toInt() // single int
private fun readLong() = readLn().toLong() // single long
private fun readDouble() = readLn().toDouble() // single double
private fun readStrings() = readLn().split(" ") // list of strings
private fun readInts() = readStrings().map { it.toInt() } // list of ints
private fun readLongs() = readStrings().map { it.toLong() } // list of longs
private fun readDoubles() = readStrings().map { it.toDouble() } // list of doubles

fun main() {
  val T = readInt()
  for (cas in 0 until T) {
    val (n, _x, _y) = readInts()
    val x = min(_x, _y)
    val y = max(_x, _y)
    var ans = min(n - y, x - 1) + n - 1

    var t1 = x - 1
    var t2 = min(2 * (y - x - 1) + n - y, 2 * (n - y) + y - x - 1)
    ans = min(ans, max(t1, t2))

    t1 = min(2 * (y - x - 1) + x - 1, 2 * (x - 1) + y - x - 1)
    t2 = n - y
    ans = min(ans, max(t1, t2))

    for (i in x + 1 .. y) {
      val t1 = min(2 * (i - 1 - x) + x - 1, x - 1 + i - 2)
      val t2 = min(2 * (y - i) + n - y, 2 * (n - y) + y - i)
      val cur = max(t1, t2)
      ans = min(ans, cur)
    }
    println(ans)
  }
}
