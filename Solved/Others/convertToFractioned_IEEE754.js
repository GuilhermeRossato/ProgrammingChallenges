var padLeft = (original, len, fill) => (Array(len-original.length+1).join(fill||'0')+original);

var conv = (num) => {
var b = num.toString(2).split(".");
var txt;
if (b[0][0] == "-") {
   txt = "1 ";
   b[0] = b[0].substr(1);
} else
  txt = "0 ";

if (b[0] == "0")
  txt += padLeft("0",8,"0")+" ";
else {
  var eo = b[0].length-1;
  var er = 127+eo;
  txt += padLeft(er.toString(2),8,"0")+" ";
}
if (b[0].length > 1)
  txt+=b[0].substr(1);
if (b.length > 1)
  txt+=b[1];
while (txt.length < 32)
  txt += "0";
return txt;
};