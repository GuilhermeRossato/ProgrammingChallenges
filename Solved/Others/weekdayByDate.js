var weekdayData = new Uint8Array([3, 0, 6, 3, 1, 5, 3, 0, 4, 2, 6, 4]);

function weekdayByDate(y, m, d) {
	return (((m < 3)?Math.ceil:Math.floor)(y*5/4)+d-weekdayData[m-1])%7;
}

function weekdayNameByDate(y, m, d) {
	return ["Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"][weekdayByDate(y, m, d)];
}
