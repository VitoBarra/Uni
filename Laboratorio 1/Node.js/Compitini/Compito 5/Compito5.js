/*
ESERCIZIO 1
 Si scriva una funzione reverse(a) che prende come parametro un array e restituisce un altro array con gli elementi in ordine inverso.
 
 Esempi:
 reverse([1,2,3,4]) -> [4,3,2,1]
 reverse([]) -> []
 reverse([1,1,1,1,1,1,1]) -> [1,1,1,1,1,1,1]
 reverse([8])->[8]
 */

function reverse(a) {

    let revA = [];
    for (let i = a.length - 1, j = 0; i >= 0; i--, j++)
      revA[j] = a[i];
  
    return revA;
  }
  /*
  ESERCIZIO 2
  Si scriva una funzione colNeg(a) dove a e' una matrice di interi di dimensione NxM (rappresentata come una array di array). In particolare, a[i], 0 <= i <= N, contiene i valori della i-esima riga di a, e a[i][j] contiene il valore j-esimo della i-esima riga di a. 
  
  colNeg(a) restituisce true se esiste almeno una riga in a con tutti i valori negativi.
  
  Esempi: 
  a = [[1,2,3], [4,5,6], [7,-8,9]] -> false
  a = [[1,2,3], [-44,-5,-6], [7,-8,9]] -> true
  a = [[-1,-2,-3], [-44,-5,-6], [-7,-8,-9]] -> true
  */
  
  function colNeg(a) {
    let negativeRow = true;
    for (let i = 0; i < a.length; i++) {
      negativeRow = true;
      for (let j = 0; j < a[i].length; j++) {
        if (a[i][j] > 0) {
          negativeRow = false;
          break;
        }
      }
      if (negativeRow)
        break;
    }
    return negativeRow;
  }
  
  
  /*
  ESERCIZIO 3
  Si scriva una funzione colNegE(a) dove a e' una matrice di interi di dimensione NxM (rappresentata come una array di array). In particolare, a[i], 0 <= i <= N, contiene i valori della i-esima riga di a, e a[i][j] contiene il valore j-esimo della i-esima riga di a. 
  
  colNegE(a) restituisce true se esiste esattamente una riga in a con tutti i valori negativi.
  
  Esempi: 
  a = [[1,2,3], [4,5,6], [7,-8,9]] -> false
  a = [[1,2,3], [-44,-5,-6], [7,-8,9]] -> true
  a = [[-1,-2,-3], [-44,-5,-6], [-7,-8,-9]] -> false
  */
  
  function colNegE(a) {
    let negativeRow = true,
      fistRow = false;
  
    for (let i = 0; i < a.length; i++) {
      negativeRow = true;
      for (let j = 0; j < a[i].length; j++) {
  
        if (a[i][j] > 0) {
          negativeRow = false;
          break;
        }
      }
  
      if (negativeRow) {
        if (fistRow)
          return false;
        else
          fistRow = true;
      }
    }
  
    return fistRow;
  }
  
  
  
  /*
  ESERCIZIO 4
  Si scriva una funzione ricorsiva sommaCifre(v), con v un intero positivo. La funzione restituisce la somma delle cifre di v, utilizzando divisione per 10 e l'operatore %.
  
  Esempi:
  sommaCifre(101) -> 2
  sommaCifre(1234) -> 10
  */
  
  function sommaCifre(v) {
    if (v <= 9)
      return v;
    return sommaCifre(Math.trunc(v / 10)) + v % 10
  }
  
  
  /*
  ESERCIZIO 5
  La Notazione Polacca Inversa (Reverse Polish Notation, RPN) è un linguaggio per operazioni aritmetiche in cui l’operatore segue gli operandi.
  
  Per esempio, l’espressione RPN 
  2 3 + corrisponde all’espressione infissa 2+3, mentre 
  3 4 1 + / corrisponde a 3/(4+1); e ancora:
  1 7 3 / 1 4 - 21 * / + corrisponde a (7/3)/((1-4)*21)+1
  
  Una espressione RPN si può facilmente calcolare utilizzando una pila e applicando le seguenti regole ai componenti dell’espressione letti da sinistra verso destra:
  1. se il componente e' un operando, fare push dell'operando
  2. se e' un operatore, applicarlo a un numero appropriato di elementi prelevati dalla pila, e caricare il risultato sulla pila
  
  Scrivere una funzione computeRPN(erpn), dove erpn e' un array di  stringhe che rappresenta una espressione aritmetica in forma RPN. computeRPN deve restituire la valutazione di erpn. Si assuma che:
  
  a. erpn sia corretta
  b. in erpn gli operatori siano solo +, -, *, /
  
  Esempi:
  computeRPN(["2","3","+"]) -> 5
  computeRPN(["3","4","1","+","/"]) -> 0.6
  computeRPN(["1","7","3","/","1","4","-","21","*","/","+"]) -> 0.9629629629629629 
  */
  
  function computeRPN(erpn) {
    let tempPila = [];
    for (let i = 0; i < erpn.length; i++) {
      if (erpn[i] == "+" || erpn[i] == "-" || erpn[i] == "/" || erpn[i] == "*") {
        let op2 = tempPila.pop(),
          op1 = tempPila.pop();
        switch (erpn[i]) {
          case "+":
            tempPila.push(op1 + op2);
            break;
          case "-":
            tempPila.push(op1 - op2);
            break;
          case "/":
            tempPila.push(op1 / op2);
            break;
          case "*":
            tempPila.push(op1 * op2);
            break;
        }
      } else tempPila.push(parseInt(erpn[i]));
    }
    return tempPila.pop();
  }
  
  /*
  ESERCIZIO 6
  Si scriva una classe Coda che rappresenti, prevedibilmente, una coda. La coda deve gestire stringhe. Oltre a un costruttore, serviranno i metodi seguenti:
  
  1. q.enqueue(s) - inserisce in testa alla coda q la stringa s, e rstituisce la lunghezza corrente della coda
  2. q.enqueueT(s) - inserisce in fondo alla coda q la stringa s, e rstituisce la lunghezza corrente della coda
  3. q.dequeue() - rimuove e restituisce l'elemento in fondo alla coda 
  4. q.search(s) - cerca la stringa s in q; se s esiste, restituisce la posizione in q della sua prima occorrenza (iniziando dalla testa della coda, e contando da 0); -1 altrimenti
  5. q.occurrences(s) - restituisce il numero di occorrenze di s in q
  6. q.deleteFirst(s) - se s esiste in q, elimina la prima occorrenza di s da q, e restituisce la posizione in q della occorrenza appena eliminata (inziando dalla testa della coda, e contando da 0); -1 altrimenti
  7. q.size() - restituisce il numero di elementi presenti in q
  8. q.reset() - elimina tutti gli elementi in q, e restituisce 0
  9. q.merge(q1) - appende tutti gli elementi della coda q1 passata come argomento, ordinatamente dalla testa, in fondo agli elementi presenti in q, e restituisce il numero degli elementi aggiunti. La coda q1 non deve essere modificata
  10. print() - restituisce una stringa contenente gli elementi della coda (tutti gli elementi della coda sulla stessa riga, separati da virgola, senza spazi)
  
  Esempi, partendo da una coda q e q1 vuota:
  q.enqueue("uno") -> 1           q.enqueue("due") -> 2
  q.enqueue("tre") -> 3           q.enqueue("uno") -> 4
  q.enqueueT("quattro")) -> 5     q.print() -> "quattro,uno,due,tre,uno"
  q.dequeue() -> 4                q.print() -> "uno,due,tre,uno"
  q.search("uno") -> 0            q.deleteFirst("due") -> 2
  q.size() -> 3                   q.print()) -> "uno,tre,uno"
  q1.enqueue("a") -> 1            q1.enqueue("b") -> 2
  q1.enqueue("c") -> 3            q1.print() -> "a,b,c"
  q.merge(q1) -> 3                q.print() -> "a,b,c,uno,tre,uno"
  */
  
  class Coda {
  
    constructor() {
      this.coda = [];
    }
    /**inserisce in testa alla coda q la stringa s, e restituisce la lunghezza corrente della coda*/
  
    enqueue(s) {
      this.coda.push(s);
      return this.size();
    }
    /**inserisce in fondo alla coda q la stringa s, e rstituisce la lunghezza corrente della coda*/
    enqueueT(s) {
      this.coda.unshift(s);
      return this.size();
    }
    /**rimuove e restituisce l'elemento in fondo alla coda */
    dequeue() {
      this.coda.shift();
      return this.size();
    }
    /**cerca la stringa s in q; se s esiste, restituisce la posizione in q della sua prima occorrenza (iniziando dalla testa della coda, e contando da 0); -1 altrimenti*/
    search(s) {
      for (let i = 0; i < this.coda.length; i++)
        if (this.coda[i] == s)
          return i;
      return -1
    }
    /** restituisce il numero di occorrenze di s in q*/
    occurrences(s) {
      let h = 0;
      for (let i = 0; i < this.coda.length; i++)
        if (this.coda[i] == s)
          h++;
      return h;
    }
    /**se s esiste in q, elimina la prima occorrenza di s da q, e restituisce la posizione in q della occorrenza appena eliminata (inziando dalla testa della coda, e contando da 0); -1 altrimenti*/
    deleteFirst(s) {
      for (let i = this.coda.length; i > 0; i--)
        if (this.coda[i] == s) {
          this.coda.splice(i, 1)
          return i + 1;
        }
      return -1;
    }
  
    /**restituisce il numero di elementi presenti in q*/
    size() {
      return this.coda.length;
    }
    /**elimina tutti gli elementi in q, e restituisce 0*/
    reset() {
      this.coda = [];
      return this.coda.length;
    }
    /**appende tutti gli elementi della coda q1 passata come argomento, ordinatamente dalla testa, in fondo agli elementi presenti in q, e restituisce il numero degli elementi aggiunti. La coda q1 non deve essere modificata*/
    merge(q1) {
      this.coda = [...q1.coda, ...this.coda];
      return q1.coda.length;
    }
    /**restituisce una stringa contenente gli elementi della coda (tutti gli elementi della coda sulla stessa riga, separati da virgola, senza spazi)*/
    print() {
      let str = "";
      for (let i = 0; i < this.coda.length - 1; i++)
        str += this.coda[i] + ",";
      return str + this.coda[this.coda.length - 1];
    }
  
  }
  
  // let c = new Coda();
  // console.log(c.merge(["a","b","c"]));
  
  /*
  ESERCIZIO 7
  Si scriva una funzione mcm(a,b), dove a e b sono interi positivi. mcm(a,b) restituisce il minimo comune multiplo (MCM)
  di a e b. Dati due numeri interi N1 e N2, il minimo comune multiplo è il più piccolo numero M che è divisibile (con resto pari a zero) sia per N1 che per N2.
  
  Esempi: 
  mcm(30,40) -> 120
  mcm(14,15) -> 210
  */
  
  function mcm(a, b) {
  
    function mcd(m, n) {
      if (n == 0)
        return (m);
      else
        return mcd(n, m % n);
    }
  
    return (a * b) / mcd(a, b);
  }
  
  /*
  ESERCIZIO 8
  Si progetti una classe MCDMCM per gestire il minimo comune multiplo (MCM) e il massimo comune divisore (MCD) di due numeri interi positivi.  
  
  In particolare, oltre al costruttore, la classe deve prevedere i metodi mcd() e mcm() per calcolare, rispettivamente, il MCM e il MCD dei due numeri.
  */
  
  class MCDMCM {
  
    constructor(n1, n2) {
      this.num1 = n1;
      this.num2 = n2;
  
  
      this.fac1 = this.findFactors(n1);
      this.fac2 = this.findFactors(n2);
      this.facMat1 = this.countFactors(this.fac1);
      this.facMat2 = this.countFactors(this.fac2);
    }
  
    findFactors(n) {
      let fac = [];
  
      for (let i = 2; i <= n;) {
        if (n % i == 0) {
          fac.push(i);
          n = n / i;
        } else i++;
      }
      return fac;
    }
  
    countFactors(ar) {
      function addOne(n) {
        for (let j = 0; j < mat.length; j++) {
          if (n == mat[j][0]) {
            mat[j][1]++;
            return true;
          }
        }
        return false;
  
      }
  
      let mat = [];
      for (let i = 0; i < ar.length; i++) {
        if (!addOne(ar[i]))
          mat[mat.length] = [ar[i], 1];
      }
      return mat;
    }
  
    mcd() {
      let common = this.fac1.filter(x => this.fac2.includes(x));
      let temp = 1;
      for (let i = 0; i < common.length; i++)
        temp *= common[i];
  
      return temp;
    }
  
  
  
    mcm() {
      let temp = [];
  
      findMatch(this.facMat1, [...this.facMat2]);
  
      let mcd = 1;
      for (let i = 0; i < temp.length; i++)
        mcd *= Math.pow(temp[i][0], temp[i][1]);
  
  
      return mcd;
  
      function findMatch(mat1, mat2) {
        for (let i = 0; i < mat1.length; i++) {
          let find = false;
          for (let j = 0; j < mat2.length; j++)
            if (mat1[i][0] == mat2[j][0]) {
              temp[temp.length] = [mat1[i][0], Math.max(mat1[i][1], mat2[j][1])];
              mat2.splice(j, 1);
              find = true;
              break;
            }
          if (!find)
            temp[temp.length] = [mat1[i][0], mat1[i][1]];
        }
  
        for (let i = 0; i < mat2.length; i++)
          temp[temp.length] = mat2[i];
  
      }
  
    }
  }
  
  
  /*
  ESERCIZIO 9
  Si progetti una classe Vector che gestisca vettori multidimensionali rappresentati come array (si deve usare 'coord' come nome della proprietà che memorizza le coordinate del vettore). La classe implementa le operazioni di prodotto con un scalare (metodo 'prodottoS'), e somma (metodo 'somma') e prodotto scalare  (metodo 'prodotto') con altri vettori. Le operazioni con un altro vettore restituiscono undefined se i vettori non hanno la stessa dimensione.
  
  Esempi:
  a=new Vector([1,4,6])
  b=new Vector([5,2,3])
  c=new Vector([3,4,5,6])
  a.somma(b) -> Vector {coord: [6,6,9]}
  a.somma(c) -> undefined //a e c hanno dimensioni diverse
  
  a.prodotto(b) -> 31
  a.prodotto(c) -> undefined//a e c hanno dimensioni diverse
  a.prodottoS(4) -> Vector{ coord: [4,16,24]}
  */
  
  class Vector {
  
    constructor(ar) {
      this.coord = ar;
    }
  
  
    somma(a) {
      let e = [];
      if (this.coord.length != a.coord.length)
        return undefined;
  
      for (let i = 0; i < a.coord.length; i++)
        this.coord[i] = this.coord[i] + a.coord[i];
  
  
      return this;
    }
  
    prodotto(a) {
      if (this.coord.length != a.coord.length)
        return undefined;
  
      let sum = 0;
      for (let i = 0; i < this.coord.length; i++)
        sum += this.coord[i] * a.coord[i];
  
      return sum;
    }
  
    prodottoS(n) {
      let e = []
      for (let i = 0; i < this.coord.length; i++)
        this.coord[i] = this.coord[i] * n;
      return this;
    }
  }
  
  // let a = new Vector([3, 4, 5]);
  // console.log(a.prodotto(4));
  // a.prodottoS([2, 6, 5]);
  // console.table(a.vector);
  // a.prodottoS([2, 6, 5, 5]);
  // console.table(a.vector);
  // a.somma([2, 6, 5]);
  // console.table(a.vector);
  
  // NON CANCELLARE QUESTA RIGA
  module.exports = {
    reverse,
    sommaCifre,
    colNeg,
    colNegE,
    computeRPN,
    mcm,
    MCDMCM,
    Coda,
    Vector
  };
  
  /*
  Per eseguire i test di prova:
  1. Selezionare "Shell" nel riquadro a dx (di fianco al tab "Console")
  2. Digitare npm run test e premere invio
  3. NON MODIFICARE IL CONTENUTO DI test.js
  */