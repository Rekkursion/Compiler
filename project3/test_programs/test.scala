object Rekkursion {
	def max(a: int, b: int): int {
		if (a > b)
			return a
		return b
	}

	def main(): int {
		var x: int
		var y
		read x
		read y
		
		println max(x, y)
		
		
		
		return 0
	}
}