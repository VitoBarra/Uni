///-----------------------------------------------
///-----------------ESERCIZIO 1-------------------
///-----------------------------------------------
function calcola(a)
{
    let sum =0;
    for(let n of a)
      sum += n*n;
return sum;
}

///-----------------------------------------------
///-----------------ESERCIZIO 2-------------------
///-----------------------------------------------

function cancellaConSoglia(a,n)
{
  return a.filter(e => e>n );
}
///-----------------------------------------------
///-----------------ESERCIZIO 3-------------------
///-----------------------------------------------

function contaCoppia(T,val1,val2)
{
  
    if(T == undefined) return 0;
    
    if(T.sx != undefined && T.dx != undefined)
        if(T.sx.val >=val1 && T.dx.val >= val2)
            return contaCoppia(T.sx,val1,val2) + contaCoppia(T.dx,val1,val2) + 1;   
        else
            return contaCoppia(T.sx,val1,val2) + contaCoppia(T.dx,val1,val2);
    else
        if(T.sx != undefined)
            return contaCoppia(T.sx,val1,val2);
        else 
            return contaCoppia(T.dx,val1,val2);


}


///-----------------------------------------------
///-----------------ESERCIZIO 4-------------------
///-----------------------------------------------
function  rudyGiuliani(trump,biden,votiLegali)
{
    var sumT = 0, sumB = 0;

    for (let a in votiLegali)
    { 
      if(a in biden && a in trump ) continue;

      if(a in biden)
        sumB += biden[a];
      else if(a in trump)
        sumT += trump[a];
    }
    return sumT>sumB?true:false;
}