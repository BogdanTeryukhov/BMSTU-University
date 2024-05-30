package lab2

object Lab2 {

  final class BlurredNumber(val a: Double, val k: Double) {

    def +(b2: BlurredNumber): BlurredNumber = {
      new BlurredNumber(a + b2.a, (k + b2.k))
    }

    def *(c: Double): BlurredNumber = {
      new BlurredNumber(c * a, c * k)
    }

    def <(b2: BlurredNumber): Boolean = {
      a < b2.a || (a == b2.a && k < b2.k)
    }

    override def toString = s"BlurredNumber($a, $k)"
  }

  def main(args: Array[String]): Unit = {
    val origin = new BlurredNumber(2.0, 3.0)
    val test = new BlurredNumber(3.0, 5.0)
    val c = 15.0

    println(origin + test)
    println(origin * c)
    println(origin < test)
  }
}
