function unique(a, equals) {
    var ris = new Array();
    for (var _i = 0, a_1 = a; _i < a_1.length; _i++) {
        var e = a_1[_i];
        var find = true;
        for (var _a = 0, ris_1 = ris; _a < ris_1.length; _a++) {
            var w = ris_1[_a];
            if (equals(e, w))
                find = false;
        }
        if (find)
            ris.push(e);
    }
    return ris;
}
Esempio: console.log(unique([3, 5, 3, 2, 8, 5], (function (x, y) { return x == y; })));
console.log(unique([0, 0, 0, 0, 0, 0, 0], (function (x, y) { return x == y; })));
console.log(unique(['hello', 'hello', 'how', 'are', 'you'], (function (x, y) { return x == y; })));
//# sourceMappingURL=unique.js.map