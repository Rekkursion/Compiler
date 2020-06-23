object example {
	def neg(a: int): int {
		return -a
	}

	def main() {
		var n
		read n
		
		var arr: int[n]
		
		var i
		for (i <- 0 to arr.length - 1)
			arr[i] = neg((i + 1) * (i + 1))
		
		i = 0
		while (i < arr.length) {
			println arr[i]
			i = i + 1
		}
	}
}