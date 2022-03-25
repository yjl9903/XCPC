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
    val (n, s) = readLongs()
    var l = 1L
    var r = s
    var ans = -1L

    fun check(x: Long): Boolean {
      var sum = s
      var cur = x
      var i = 0L
      while (i < n) {
        sum -= cur
        cur = (cur + 1) / 2
        i++
        if (cur == 1L) {
          sum -= n - i
          break
        }
      }
      return sum >= 0
    }

    while (l <= r) {
      val m = (l + r) / 2
      if (check(m)) {
        ans = m
        l = m + 1
      } else {
        r = m - 1
      }
    }
    assert(ans != -1L)
    println(ans)
  }
}
