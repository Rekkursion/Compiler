object Rekkursion {
	// the INT version of max function
	def max(a: int, b: int): int {
		if (a > b)
			return a
		return b
	}
	
	// the FLOAT version of max function
	def maxf(a: float, b: float): float {
		if (a < b)
			read b
		else
			return a
	}
	
	val nam = ""

	// the main function
	def main(): float {
		var x: int
		var y: int
		read x
		read y
		
		var it: int
		for (it <- x to y)
			println -it
		
		while (nam != "") {
			val s = max(x + y, x * max(y * max(2, x), x * x * x))
			print s + -1
			print maxf(2.2, 1.1e+1209 * maxf(2E-123, 2.2))
		}
		
		var arr: int[5]
		arr[0] = max(max(x % 10, y % 12 + 1), max(200 / y, 20 * x))
		
		if (x == 2)
			return 2.2 + 4.4 / maxf(maxf(2.2, 2.2), maxf(-2.2, -2.2))
		else
			return 2.22 * -1E-3
	}
	
	def m() {}
}