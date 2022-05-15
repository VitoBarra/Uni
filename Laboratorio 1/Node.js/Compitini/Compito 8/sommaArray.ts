function sommaArray(arr, f) {
  var ris = f(arr[0], arr[1]);
  for (var i = 2; i < arr.length - 1; i++) ris += f(arr[i], arr[i + 1]);
  return ris;
}
function sumNumbers(x, y) {
  return x + y;
}
console.log(sommaArray([3, 6, 4, 2], sumNumbers));
console.log(sommaArray([3, 6, 4, "34"], sumNumbers));
function sumStrings(x, y) {
  return x + " " + y;
}
console.log(sommaArray(["o", "che", "bel", "castello"], sumStrings));
