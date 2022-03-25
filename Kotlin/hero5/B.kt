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
    val s = readLn()
    var cnt = 0
    var ans = 0
    for (ch in s) {
      if (ch == 'v') {
        cnt++
      } else {
        ans += cnt / 2
        cnt = 0
        ans++
      }
    }
    ans += cnt / 2
    println(ans)
  }
}
