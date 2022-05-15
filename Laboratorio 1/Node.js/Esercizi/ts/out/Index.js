// Si scriva in TypeScript una classe AnyMatrix che rappresenta una matrice rettangolare rxc
//(rappresentata come array di array) che contiene elementi omogenei, di qualsiasi tipo (stringhe, numeri, oggetti, ecc.). La classe deve offrire:
// 1. Costruttore (che costruisce una matrice avente almeno dimensione 1x1), che prende anche un valore v con cui inizializzare il contenuto della matrice.
// 2. Metodo setAll(dati: T[][]): boolean che, preso un array di array di dimensione pxq, usa i valori contenuti nel parametro dati come valori da assegnare a questa matrice. Se le dimensioni di dati e di questa matrice non coincidono, il metodo restituisce false; altrimenti, true.
// 3. Metodo transpose() che restituisce una nuova AnyMatrix, trasposta di questa matrice.
var AnyMatrix = /** @class */ (function () {
    function AnyMatrix(r, c, v) {
        this.A = new Array();
        this.r = r;
        this.c = c;
        this.v = v;
        for (var i = 0; i < r; i++) {
            this.A[i] = new Array();
            for (var j = 0; j < c; j++)
                this.A[i][j] = v;
        }
    }
    AnyMatrix.prototype.setAll = function (dati) {
        if (this.A.length != dati.length)
            return false;
        else
            for (var i = 0; i < dati.length; i++)
                if (this.A[i].length != dati[i].length)
                    return false;
        for (var i = 0; i < this.A.length; i++)
            for (var j = 0; j < this.A[i].length; j++)
                this.A[i][j] = dati[i][j];
    };
    AnyMatrix.prototype.transpose = function () {
        var temp = new AnyMatrix(this.c, this.r, this.v);
        var y = this.A.length;
        var x = this.A[0].length;
        for (var i = 0; i < x; i++) {
            var temp1 = new Array();
            for (var j = 0; j < y; j++)
                temp1[j] = this.A[j][i];
            temp[i] = temp1;
        }
        return temp;
    };
    AnyMatrix.prototype.push = function (ar) {
        this.A.push(ar);
    };
    AnyMatrix.prototype.toString = function () {
        return this.r + "x" + this.c + ":\n|" + this.A.join("|\n|") + "|";
    };
    return AnyMatrix;
}());
var m = new AnyMatrix(4, 3, "s");
console.log(m.setAll([["p", "i", "p"], ["qui", "quo", "qua"], ["super", "qui", "va"], ["qua", "va", "qua"]]));
console.log(m.toString());
console.log(m.transpose().toString());
console.log(m.setAll([["p", "i"], ["qui", "quo"], ["super", "qui"], ["qua", "va"]]));
//# sourceMappingURL=Index.js.map