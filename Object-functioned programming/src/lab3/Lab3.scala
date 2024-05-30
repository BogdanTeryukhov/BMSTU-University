package lab3

class Polynom[T: Numeric](coefficients: List[T]) {
  def evaluate(x: T): T = {
    val numeric = implicitly[Numeric[T]]

    def pow(base: T, exp: Int): T = {
      numeric.fromInt(math.pow(numeric.toDouble(base), exp).toInt)
    }

    coefficients.zipWithIndex.map {
      case (coef, idx) => numeric.times(coef, pow(x, idx))
    }.reduce(numeric.plus)
  }
}

object Lab3 {

  def main(args: Array[String]): Unit = {
    val listInts = List(3,2)
    val doubleInts = List(3.0,2.0)

    val intsPolynom = new Polynom(listInts)
    val doublePolynom = new Polynom(doubleInts)

    println(intsPolynom.evaluate(2)) // 7
    println(doublePolynom.evaluate(6)) // 15.0
  }
}
