function testaOvelha(str) {
	for (let i = 0, length = str.length ; i < length; i++) {
		if (str.charAt(i) === "1" && (i === 0 || str.charAt(i-1) === "0") && (i === length-1 || str.charAt(i+1) === "0"))
			return false;
	}
	return true;
}

function generate(arr) {
	let n = arr.length;
	let sI;
	function swap(index1, index2) {
		sI = arr[index1];
		arr[index1] = arr[index2];
		arr[index2] = sI;
		sI = null;
	}
	let c = new Uint8Array(n);
	let i;
	for (i = 0 ; i < n; i++)
		c[i] = 0;
	let ret = new Set();
	function adR() {
		ret.add(arr.join(''));
		/*
		let num = 0;
		let mult = 1;
		for (let i = 0 ; i < arr.length; i++) {
			num = num + mult * arr[i];
			mult = mult * 2;
		}
		ret.add(num);*/
	}
	adR();
	i = 0;
	while (i < n) {
		if (c[i] < i) {
			if (i % 2 === 0)
				swap(0, i);
			else
				swap(c[i], i);
			adR();
			c[i]++;
			i = 0;
		} else {
			c[i] = 0;
			i++;
		}
	}
	return ret;
}

function testDifference(count) {
	if (count < 6)
		return 1;
	count -= 5;
	let possibilities = generate([1,1,1,1,1,...new Uint8Array(count)]);
	let tested = new Array(...possibilities).filter(str=>testaOvelha(str));
	console.log("n pos = ", possibilities.size);
	console.log("discarted = ", possibilities.size - tested.length);
	return [possibilities, tested];
}

/*
Useful stuff:
	Difference tests, All possibilities, how many were discarted
		(5, 0), (6, 2), (21, 12), (56, 40), (126, 101), (252, 216), (462, 413), ...
	Possible difference function (via interpolation, can't test)
		f = x => (Math.pow(x,5)/120)+(Math.pow(x,4)/12)+(7*Math.pow(x,3)/24)-(7*Math.pow(x,2)/12)+x/5;
	Sequence of number of distinct 5-combinations of n objects: 1, 6, 21, 56, 126, 252, 462, 792
		(n-4)(n-3)(n-2)(n-1)(n-0)/120
	Numbers with exactly 5 ones in binary expansion. (x^5/(1-x)^6)
		https://oeis.org/A014313
	Next larger integer with same binary weight (number of 1 bits) as n.
		https://oeis.org/A057168
*/