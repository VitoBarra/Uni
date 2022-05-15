
let a = "(9/(2+1))*9+4*(5+(4-2))";

function valuta(p) {
  let pila = p.split('');
  let temp = "";


  while (pila.length > 0) {
    let e = pila.pop();
    if (e == "(") 
    {
      temp = temp.split('');
      let temp1 = "";
      temp1 += e;
      let r;
      do 
      {
        r = temp.pop();
        temp1 += r;
      } while (r != ")");

      let ris = eval(temp1);
      temp.push(String(ris));
      temp = temp.join('');
    }
    else
      temp += e;

  }
  return eval(temp);

}

console.log(valuta(a));