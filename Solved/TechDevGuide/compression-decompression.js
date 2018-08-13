function decompress(str) {
  var sublist = [];
  var state = "reading-number";
  var num = "", text = "", depth = 0;
  (str+"#").split('').forEach((c, i) => {
    if (state === "reading-number") {
          if (c >= '0' && c <= '9') {
              num += c;
          } else if (c == '[') {
              state = "reading-content";
              text = "";
          } else if (!num.length) {
              state = "reading-content";
              text = c;
          } else {
        console.log("Unhandled character",c,"at index",i,"in state",state);
          }
      } else if (state === "reading-content") {
      if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')) {
        text += c;
          } else if (c === "[") {
        text += c;
        depth++;
          } else if (c === "]" && depth !== 0) {
        text += c;
        depth--;
          } else if (c === "]" || c === "#") {
        (!num.length) && (num = "1");
        sublist.push({repeat: parseInt(num), text: text});
        num = (c >= '0' && c <= '9')?c:"";
        state = "reading-number";
          } else {
        console.log("Unhandled character",c,"at index",i,"in state",state);
          }
    } else {
      console.log("Unhandled state",state,"at char",c,"index",i);
    }
  });
  sublist.forEach(l => {
    if (l.text.indexOf("[") !== -1) {
      l.text = decompress(l.text);
    }
  });
  sublist = sublist.map(l => l.text.repeat(l.repeat));
  return sublist.join("");
}

var result = decompress("3[3[4[a]lo]2[gui]Z]");
console.log('decompress("3[3[4[a]lo]2[gui]Z]"); yields', (result === "aaaaloaaaaloaaaaloguiguiZaaaaloaaaaloaaaaloguiguiZaaaaloaaaaloaaaaloguiguiZ")?"correctly":"incorrectly", "by outputting:", result);
