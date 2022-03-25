package hero5

import java.lang.Integer.*

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
    val (n, k) = readInts()
    val p = readInts()
    var i = 1
    var ans = 0
    while (i * k <= n) {
      val cur = p.subList(n - i * k, n - i * k + i).sum()
      ans = max(ans, cur)
      i++
    }
    println(ans)
  }
}
