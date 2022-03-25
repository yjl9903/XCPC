package example

import java.util.*

private fun readLn() = readLine()!! // string line
private fun readInt() = readLn().toInt() // single int
private fun readLong() = readLn().toLong() // single long
private fun readDouble() = readLn().toDouble() // single double
private fun readStrings() = readLn().split(" ") // list of strings
private fun readInts() = readStrings().map { it.toInt() } // list of ints
private fun readLongs() = readStrings().map { it.toLong() } // list of longs
private fun readDoubles() = readStrings().map { it.toDouble() } // list of doubles

data class ComparablePair<T : Comparable<T>, U : Comparable<U>>(var first: T, var second: U)
  : Comparable<ComparablePair<T, U>> {
  override fun compareTo(other: ComparablePair<T, U>): Int {
    val r = this.first.compareTo(other.first)
    return if (r != 0) r else this.second.compareTo(other.second)
  }
}

fun main() {
  val n = readInt()
  val mp = TreeSet<ComparablePair<Int, Int>>()
  for (i in 0 until n) {
    val (a, b) = readInts()
    mp.add(ComparablePair(a, b))
  }
  for ((key, value) in mp) {
    println("$key: $value")
  }
}
