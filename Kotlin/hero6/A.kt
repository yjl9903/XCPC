package hero6

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
    var (x, y) = readLongs()
    var ans = 0L
    while (y >= x) {
      var base: Long = x
      while (10L * base <= y) {
        base *= 10
      }
//      println("$ans $y $base")
      ans++
      y -= base
    }
    println(ans + y)
  }
}
