package hero5

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

    val ord = MutableList<Int>(n) { it -> it }
    ord.sortBy { a[it] }
    var l = 0
    var r = n - 1
    var cnt = 0
    while (l <= r) {
      if (cnt == a[ord[l]]) {
        print("${ord[l] + 1} ")
        l++
        cnt = 1
      } else {
        print("${ord[r] + 1} ")
        r--
        cnt++
      }
    }
    println()
  }
}
