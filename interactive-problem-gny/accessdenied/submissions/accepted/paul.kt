import kotlin.system.exitProcess

val alphabet = ('A'..'Z') + ('a'..'z') + ('0'..'9')

fun query(s: CharArray): Int {
    println(s.joinToString(""))
    System.out.flush()
    val ans = readLine()!!.split(" ")
    if (ans[1] == "GRANTED") exitProcess(0)
    return ans[2].substring(1).toInt()
}

fun main() {
    for (k in 1..20) {
        val str = CharArray(k) { 'A' }
        if (query(str) == 5) continue
        for (i in 0 until k)
            str[i] = alphabet.maxByOrNull {  c -> str[i] = c; query(str) }!!
    }
}