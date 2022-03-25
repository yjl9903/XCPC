package hero5

private fun readLn() = readLine()!!
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map { it.toInt() }

fun main() {
  val (n, m, q) = readInts()
  val mp = MutableList(n) { readLn().toCharArray() }
  val qry = MutableList(q) { readLn().toCharArray() }
  val pos = MutableList(q) { 0 }
  val ans = MutableList(q) { 0 }

  val ch = MutableList(n * m + 2) { MutableList(26) { -1 } }
  var sz = 1

  for (i in 0 until n) {
    var u = 1
    for (j in 0 until m) {
      val c = mp[i][j] - 'a'
      if (ch[u][c] == -1) {
        ch[u][c] = ++sz
      }
      u = ch[u][c]
    }
  }

  fun merge(x: Int, y: Int) {
    for (c in 0 until 26) {
      if (ch[x][c] != -1 && ch[y][c] != -1) {
        merge(ch[x][c], ch[y][c])
      } else if (ch[y][c] != -1) {
        ch[x][c] = ch[y][c]
      }
    }
  }

  var rt = 1
  for (i in 0 until m) {
    for (j in 0 until q) {
      if (pos[j] != i) continue
      var u = rt
      for (k in i until m) {
        val c = qry[j][k] - 'a'
        if (ch[u][c] == -1) {
          break
        }
        u = ch[u][c]
        pos[j]++
      }
      ans[j]++
    }

    var cur = -1
    for (c in 0 until 26) {
      if (ch[rt][c] != -1) {
        if (cur == -1) {
          cur = ch[rt][c]
        } else {
          merge(cur, ch[rt][c])
        }
      }
    }
    rt = cur
  }

  for (i in 0 until q) {
    if (pos[i] < m) {
      println(-1)
    } else {
      println(ans[i] - 1)
    }
  }
}
