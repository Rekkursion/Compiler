object Rekkursion {
	var xxx: int = 2 * 20 - 34
	var yyy: float

	// the INT version of max function
	def max(a: int, b: int): int {
		if (a > b)
			return a
		return b
	}
	
	var zzz: int
	
	// the FLOAT version of max function
	def maxf(a: float, b: float): float {
		if (a < b)
			return b
		else
			return a
	}
	
	val nnn = 654 - 1

	// the main function
	def main() {
		xxx = 19
		
		var x: int = 0
		var y: int = 21 - 3 * x / xxx
		
		var it: int
		for (it <- x to y)
			println -it
		
		while (nnn != 100) {
			val s = 21 * (-2 + 3 - 3 * 1)
			print s + -1
			print max(200 % xxx, -10 / y)
		}
		
		if (x == 2)
			print("x == 2\n")
		else
			println("x != 2")
	}
}