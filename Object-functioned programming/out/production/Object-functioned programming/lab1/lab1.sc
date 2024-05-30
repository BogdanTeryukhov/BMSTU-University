def sumDigits: (Int, Int => (Int, Int)) => Int = {
  (x, p) => {
    val (number, ml) = p(x)
    if (number == 0) {
      ml
    }
    else {
      ml + sumDigits(number, p)
    }
  }
}

sumDigits(6, x => (x / 10, x % 10))
sumDigits(56, x => (x / 10, x % 10))
sumDigits(1234567, x => (x / 10, x % 10))

sumDigits(111, x => (x / 10, x % 10))
sumDigits(111, x => (x / 3, x % 3))
