var filtering_extension = ".txt";
var arr = new Array(...document.getElementsByTagName("a"));
console.log(arr.length + " anchors in page");
arr = arr.filter(a=>a.href.substr(a.href.length-filtering_extension.length, filtering_extension.length) == filtering_extension);
console.log(arr.length+" hits after extension filter");
arr = arr.filter((a,j) => arr.some((b,i)=>(b.href==a.href) && (i!=j)));
console.log(arr.length+" after duplicate filter, click to download");
var index = 0;
window.addEventListener("click", window.openAllAnchors, true);
window.openAllAnchors = function(event) {
	index++;
	if (index%2===1)
		return;
	function downloadAll(files){
		if (!(files instanceof Array)) {
			console.log("file is not array")
			return;
		}
		if(files.length == 0) {
			return;
		}
		file = files.pop();
		var theAnchor = file[0];
		//		var theAnchor = $('<a />')  
		//	.attr('href', file[1])  
		//			.attr('download',file[0]);
		if (theAnchor[0] && theAnchor[0].click)
			theAnchor[0].click();
		else if (theAnchor && theAnchor.click)
			theAnchor.click();
		else
			console.log("no options");
		if (theAnchor.remove)
			theAnchor.remove();
		else
			console.log("No Remove Function");
		downloadAll(files);
	}
	let darr = arr.map(a=>[a, a.href, a.download]);
	darr = darr.filter((a,i)=>((index/2)*10<=i)&&(i<(index/2+1)*10));
	if (darr.length > 11) {
		console.error("Can't send more");
		return;
	}
	console.log("Sending ",darr.length," interval ", (index/2)*10,(index/2+1)*10);
	downloadAll(darr);
}
window.addEventListener("click", window.openAllAnchors, true);     