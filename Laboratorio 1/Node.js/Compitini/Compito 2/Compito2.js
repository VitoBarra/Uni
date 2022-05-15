/* ESERCIZIO 1
Scrivere una funzione convertiBinCompl(a) che dato un numero a espresso in base 10, compreso tra [-256, 256), restituisce la rappresentazione in complemento a due di a su 9 bit. 

ESEMPI:
convertiBinCompl(13): 000001101
convertiBinCompl(-93): 110100011 
convertiBinCompl(-256): 100000000
convertiBinCompl(255): 011111111
*/


/* ESERCIZIO 2
Scrivere una funzione contaFoglie(t) che dato un albero binario t restituisce il numero di foglie di t

ESEMPI:
contaFoglie(t): 5 //con t quello generato da esempioBin()
contaFoglie(t): 3 //con t quello generato da esempioPersone()
*/


/* ESERCIZIO 3
Scrivere una funzione isPrimo(a) che restituisce true se a è primo, e false altrimenti. Si scriva poi una seconda funzione eliminaPrimi(a) che, dato un array a contenente interi, restituisce un array contenente tutti i non primi di a.

Nota: In matematica, un numero primo (in breve anche primo) è un numero naturale maggiore di 1 che sia divisibile solamente per 1 e per sé stesso. 

ESEMPI:
isPrimo(17): true
isPrimo(9901): true
isPrimo(98029801): false
*/


/* ESERCIZIO 4
Si scriva una funzione isPal(s) che, data una stringa s, restituisce true se s è palindroma, e false altrimenti. 

NOTA: una stringa è palindroma se può essere letta da sinistra verso destra e da destra verso sinistra indifferentemente (es. "anna", "ailatiditalia").

ESEMPI:
isPal("avallava"): true
isPal("agioga"): false
isPal("onorarono"): true
*/


/* ESERCIZIO 5
Scrivere una funzione indexEq(a) che, preso un array a ordinato di interi distinti, restituisce true se esiste un indice i tale che a[i] = i, e false altrimenti.

ESEMPI:
indexEq([-42, -11, 0, 2, 5]): false
indexEq([-42, -11, 0, 2, 4]): true
indexEq([-42, -11, -5, -2, 0, 2, 4, 5, 6, 7, 10, 202]): true
*/


///-----------------------------------------------
///-----------------ESERCIZIO 1-------------------
///-----------------------------------------------
function convertiBinCompl(num)
{ 
    const NUMBER_OF_BYTE =9;
    var str = "";
   
    if(num<0)
    {
        num = Math.abs(num);
        num = (num^(Math.pow(2,NUMBER_OF_BYTE)-1))+1;
    }

    while(num>0)
    {
      str += num%2;
      num =  Math.trunc(num/2);
    }

    str = str.split("").reverse().join("");

    while(str.length<NUMBER_OF_BYTE)
        str = "0" + str;

    return str;
}
///-----------------------------------------------
///-----------------ESERCIZIO 2-------------------
///-----------------------------------------------

function contaFoglie(t)
{
    if(t == undefined)
        return 0;
    if(t.sx == undefined && t.dx == undefined)
        return 1;
    return contaFoglie(t.sx) + contaFoglie(t.dx);
}



///-----------------------------------------------
///-----------------ESERCIZIO 3-------------------
///-----------------------------------------------
function IsPrimo(n)
{
    if(n<0) return false;

    var sqrtN = Math.ceil(Math.sqrt(n));
    for(var i = 2 ; i<=sqrtN;i++)
            if(n%i==0) return false;
    
    return true;  
}

function eliminaPrimi(a)
{
    return a.filter(e => !IsPrimo(e));
}
///-----------------------------------------------///
///-----------------ESERCIZIO 4-------------------///
///-----------------------------------------------///
function isPal(str)
{
    if(str == str.split("").reverse().join(""))
        return true;
    else return false;
}

///-----------------------------------------------
///-----------------ESERCIZIO 5-------------------
///-----------------------------------------------
function indexEq(arr)
{
    for(let i in arr)
        if(i==arr[i])
            return true;
    
    return false;
}
///-----------------------------------------------

