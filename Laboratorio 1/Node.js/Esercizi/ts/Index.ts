// Si scriva in TypeScript una classe Pila che rappresenti, prevedibilmente, una pila. La pila deve poter gestire elementi omogenei, di qualsiasi tipo (stringhe, numeri, oggetti, ecc.). Potete implementare la pila con la struttura dati che preferite. Oltre a un costruttore, dovranno essere implementati i seguenti metodi:

// 1. p.push(el) - inserisce in cima alla pila p l'elemetno el, e restituisce il numero di elementi presenti nella pila dopo l'inserimento
// 2. p.pop() - estrae l'elemento in cima alla pila, e lo restituisce. Se la pila e' vuota, restituisce null
// 3. p.top() - restituisce, senza rimuoverlo, l'elemento in cima alla pila. Se la pila e' vuota, restituisce null
// 7. p.size() - restituisce il numero di elementi presenti nella pila p
// 8. p. reset() - elimina tutti gli elementi dalla pila p,  e restituisce 0
// 9. p.merge(p1) - sia p1 una pila non vuota, e dello stesso tipo di p. Il metodo inserisce tutti gli elementi in p1 (a partire da quello in cime) in cima a p, e restituisce il numero degli elementi complessivi di p dopo l'operazione di merge
// 10. p.print() - restituisce una stringa contenente la rappresentazione in stringa  degli elementi in p (tutti gli elementi della coda sulla stessa riga, separati da virgola, senza spazi), a partire da quello in cima. NOTA: nei test che faremo, useremo solo oggetti per cui esiste una rappresentazione sensata come stringa.

class Pila<T> {
  p: Array<T>;
  constructor() {
    this.p = new Array<T>();
  }

  push(el: T) {
    this.p.push(el);
  }
  pop() {
    this.p.pop();
  }

  top()
  {
    return this.p[this.p.length-1];
  }

  size()
  {
      return this.p.length;
  }
  reset()
  {
      this.p= new Array<T>();
      return this.size();
  }

  GetPile()
  {
      return this.p;
  }

  merge(p1 :Pila<T>)
  {
    for(let e in p1.GetPile())
        this.p.push(e);
  }
  print()
  {
      let s:string =""
      for(let i =0 ;i<this.p.length;i++)
      {
          if(i !=this.p.length-1)
          s+=this.p[i].toString()+","
          else
          s+=this.p[i].toString();
      }
      return s;
  }

}
