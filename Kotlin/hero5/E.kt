package hero5

import kotlin.math.*

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
    val a = readInts()
    val b = readInts()

    var best = -1
    var shift = 0
    for (i in 0 until n) {
      var mn = 1e9.toInt()
      for (j in 0 until n) {
        mn = min(mn, abs(a[j] - b[(j + i) % n]))
      }
      if (mn > best) {
        best = mn
        shift = i
      }
    }
    for (i in 0 until n) {
      print("${(i + shift) % n + 1} ")
    }
    println()
  }
}
