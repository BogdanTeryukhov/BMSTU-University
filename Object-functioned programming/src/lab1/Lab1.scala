package lab1

object Lab1 {

  def sumDigits: (Int, Int => (Int, Int)) => Int = {
    (x,p) => {
      val (number, ml) = p(x)
      if (number == 0) {
        ml
      }
      else {
        ml + sumDigits(number, p)
      }
    }
  }

  def main(args: Array[String]): Unit = {
    println(sumDigits(135, x => (x / 10, x % 10)))
    println(sumDigits(111, x => (x / 3, x % 3)))
  }
}
