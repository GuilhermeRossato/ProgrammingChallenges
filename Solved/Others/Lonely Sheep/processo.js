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
	if (count < 5)
		return 1;
	count -= 5;
	let possibilities = generate([1,1,1,1,1,...new Uint8Array(count)]);
	let tested = new Array(...possibilities).filter(str=>testaOvelha(str));
	console.log("n pos = ", possibilities.size);
	console.log("discarted = ", possibilities.size - tested.length);
	return [possibilities, tested];
}

function testaOvelha(str) {
	for (let i = 0, length = str.length ; i < length; i++) {
		if (str.charAt(i) === "1" && (i === 0 || str.charAt(i-1) === "0") && (i === length-1 || str.charAt(i+1) === "0"))
			return false;
	}
	return true;
}

function testaNumOvelha(num) {
	str = num.toString(2);
	for (let i = 0, length = str.length ; i < length; i++) {
		if (str.charAt(i) === "1" && (i === 0 || str.charAt(i-1) === "0") && (i === length-1 || str.charAt(i+1) === "0"))
			return false;
	}
	return true;
}

//new Array(...testDifference(7)[0]).sort((a,b)=>a>b?1:a<b?-1:0).map(a=>parseInt(a,2))

function nextNumber2(x) { // Slower
	let rightOne,nextHigherOneBit,rightOnesPattern;
	let next = 0;
	if (x) {
		rightOne = x & -x;
		nextHigherOneBit = x + rightOne;
		rightOnesPattern = x ^ nextHigherOneBit;
		rightOnesPattern = (rightOnesPattern)/rightOne;
		rightOnesPattern >>= 2;
		next = nextHigherOneBit | rightOnesPattern;
	}
	return next;
}

function nextNumber(v) { // Faster
	let t, w;
	if (v) {
		t = (v | (v - 1)) + 1; 
		w = t | ((((t & -t) / (v & -v)) >> 1) - 1);
	}
	return w;
}

function fastGenerate(digitNumber) {
	if (digitNumber < 5)
		return
	let possibilities = [];
	let limit = Math.pow(2, digitNumber);
	let thisNumber = 31;
	
	while (thisNumber < limit) {
		possibilities.push(thisNumber);
		thisNumber = nextNumber(thisNumber);
	}
	let pos1 = possibilities.filter(num => testaNumOvelha(num));
	possibilities = possibilities.map(str => str.toString('2')).map(str => "0".repeat(digitNumber-str.length)+str);
	let pos2 = possibilities.filter(str => testaOvelha(str));
	return [pos1,pos2,possibilities];
}

// FINAL

function qtdComb(houseSize) {
	if (houseSize < 5)
		return 0;
	let limit, number, possibilities, str, i, strLength, v, t, w;
	possibilities = 0;
	limit = Math.pow(2, houseSize);
	v = 31;
	while (v < limit) {
		str = v.toString(2);
		strLength = str.length;
		for (i = 0; i < strLength; i++) {
			if (str.charAt(i) === "1" && (i === 0 || str.charAt(i-1) === "0") && (i === strLength-1 || str.charAt(i+1) === "0"))
				break;
		}
		if (i === strLength) {
			//console.log(str);
			possibilities++;
		}
		
		t = (v | (v - 1)) + 1; 
		w = t | ((((t & -t) / (v & -v)) >> 1) - 1);
		v = w;
	}
	return possibilities;
}

function qtdFastComb(x) {
	return x*x;
}
/*
Useful stuff:
	Difference tests, X = All possibilities and Y= how many were discarted
		(5, 0), (6, 2), (21, 12), (56, 40), (126, 101), (252, 216), (462, 413), ...
	Possible difference function (via interpolation, can't test)
		f = x => (Math.pow(x,5)/120)+(Math.pow(x,4)/12)+(7*Math.pow(x,3)/24)-(7*Math.pow(x,2)/12)+x/5;
	Sequence of number of distinct 5-combinations of n objects: 1, 6, 21, 56, 126, 252, 462, 792
		(n-4)(n-3)(n-2)(n-1)(n-0)/120
	Numbers with exactly 5 ones in binary expansion. (x^5/(1-x)^6)
		https://oeis.org/A014313
	Next larger integer with same binary weight (number of 1 bits) as n.
		https://oeis.org/A057168
	Presentation about next integer with the same binary weight
		https://www.slideshare.net/gkumar007/bits-next-higher-presentation
*/