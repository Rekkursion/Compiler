object dec2bin {
	/* convert a non-negative decimal value into binary form */
	def toBin(deci: int) {
		// the array to temporally store the binary form
		var binArr: int[202]
		
		// the index of the array declared above
		var idx = 0
		
		// the original decimal value
		var originalDeci = deci
		
		// iteratively generate the binary values
		while (deci > 0) {
			binArr[idx] = deci % 2
			deci = deci / 2
			idx = idx + 1
		}
		
		// print out informations
		print "The input value "
		print originalDeci
		print "(10) equals to "
		
		// if the input is 0, output a single zero directly
		if (idx == 0)
			print 0
		// otherwise, reversely output the temporally-saved array which contains converted binary values
		else {
			var it: int
			for (it <- 0 to idx - 1)
				print binArr[idx - 1 - it]
		}
		
		// print out the rest info
		println "(2)"
	}
	
	def main() {
		// get the input decimal value from the user
		var decimal: int
		read decimal
		
		// convert the input decimal value to binary
		toBin(decimal)
	}
}
