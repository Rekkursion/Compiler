/* Sigma.scala
 *
 * Compute sum = 1 + 2 + ... + n
 */

object example
{
  // constants and variables
  var n
  var sum: int
  var index: int

  def main () {
	read n
  
    sum = 0
    index = 0
    
    while (index <= n) {
      sum = sum + index
      index = index + 1
    }
    print ("The sum is ")
    println (sum)
  }
}