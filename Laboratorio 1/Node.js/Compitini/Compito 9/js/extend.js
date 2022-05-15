function extend(a,b)
{
    let ris = {};
    for(let e in a )
    {
        ris[e] = a[e];
    }

    for(let e in b )
    {
        ris[e] = b[e];
    }

    return ris;
}

let a= {nome: "pippo", età: 35} 
let b={nome: "andrea", altezza: 200} 
console.log(extend(a,b)) //{nome: "andrea", età: 35, altezza: 200}
console.log(extend(a,{})) //{nome: "pippo", età: 35}
console.log(extend({},{})) //{}
