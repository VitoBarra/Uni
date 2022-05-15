/*
  Es 1
*/

function fattoriale(n){
    if(n == 0||n == 1){
      return 1;
    }
    
    if(n > 1){
      return n * fattoriale(n-1); 
    }
  }
  
  
  /*
    Es 2
  */
  
  function triangle(n){
    if(n==0||n==1)
      return 1;
    return n+triangle(n-1);
  }
  
  
  /*
    Es 3
  */
  
  function cifre(n){
    if(n=='') return;
    n = n.toString().split('');
    console.log(n.shift());
    return cifre(n.join(''));
  }
  
  
  /*
    Es 4
  */
  
  function cifreInv(n){
    if(n=='') return;
    n = n.toString().split(''); 
    console.log(n.pop());
    return cifre(n.join(''));
  }
  
  
  /*
    Es 5
  */
  
  function sommaCifre(n){
    if(n.length==0) return 0;
    if(n.length==1) return parseInt(n);
    n = n.toString().split(''); 
    return parseInt(n.pop()) + sommaCifre(n.join(''));
  }
  
  
  /*
    Es 6
  */
  
  function sommaArray(a){
    if(a.length==0) return 0;
    if(a.length==1) return a[0];
    return a.pop() + sommaArray(a);
  }
  
  
  /*
    Es 7
  */
  
  function ordinato(n){
    if(n.length==0) return false;
    if(n.length==1) return true;
    if(n[1]>n[0])
    { 
      n.shift();
      return ordinato(n);
    }
    else
      return false;    
  }
  
  
  /*
    Es 8
  */
  
  function fib(n){
    if(n==0) return 0;
    if(n==1) return 1;
    return fib(n-1)+fib(n-2);
  }
  
  
  /*
    Es 9
  */
  
  function contaPossibilita(n){
    if(n==0) return 0;
    if(n==1) return 2;
    if(n==2) return 7;//2*2+3
    return 2*contaPossibilita(n-1) +3*contaPossibilita(n-2);
  }
  