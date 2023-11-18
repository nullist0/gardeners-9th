class Solution {
    fun solution(polynomial: String): String {
        val seperator = " + "
        val terms = polynomial.split(seperator)
        val xCoefficient = terms
            .filter { "x" in it }
            .map { if (it == "x") 1 else it.dropLast(1).toInt() }
            .sum()
        val coefficient = terms
            .filter { "x" !in it }
            .map { it.toInt() }
            .sum()
        val answer = listOf(xCoefficient.toTerm("x"), coefficient.toTerm())
            .filterNotNull()
            .joinToString(seperator)
        return answer
    }
    
    fun Int.toTerm(postfix: String = ""): String? {
        return if (this == 0) null 
        else if (this == 1 && postfix != "") "$postfix"
        else "$this$postfix"
    }
}