/* Sigma.scala
 *
 * Compute sum = 1 + 2 + ... + n
 */

object example
{
  // constants and variables
  val n = 10
  var sum: int
  var index: int

  def main () {
	var x: int = 0

    sum = 0
    index = 0
    
    while (index <= n) {
      sum = sum + index
      index = index + 1
    }
	while (false) {}

	for (x <- 0 to 3) {}
	for (x <- 1 to 2) {println x}

    print ("The sum is ")
    println (sum)
  }
}
