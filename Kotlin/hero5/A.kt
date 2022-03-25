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
  val testcase = readInt()
  for (cas in 1 .. testcase) {
    val n = readInt()
    val a = readLongs()
    val mp = TreeMap<Long, Int>()
    for (x in a) {
      mp[-x] = mp.getOrDefault(-x, 0) + 1
    }
    var cur = 0
    var ans = 0L
    mp.forEach { t, u ->
      cur += u
      ans = Math.max(ans, -t * cur)
    }
    println(ans)
  }
}
