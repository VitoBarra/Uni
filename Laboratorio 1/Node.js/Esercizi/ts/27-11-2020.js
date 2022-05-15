///-----------------------------------------------
///-----------------ESERCIZIO 1-------------------
///-----------------------------------------------
function sommAlterna(a) {
    let sum = 0;
    for (let i = 0; i < a.length; i++) {
        if (i % 2 == 0)
            sum += a[i];
        else
            sum -= a[i];
    }

    return sum;

}
///-----------------------------------------------
///-----------------ESERCIZIO 2-------------------
///-----------------------------------------------

function subSeq(ago, pagliaio) {
    
    let res = false;
    for (let i = 0, j = 0; i < pagliaio.length; i++) {
        
        if (pagliaio[i] === ago[j]) {
            if (++j == ago.length) {
                res = true;
                break;
            }
        } else {
            j = 0;
            if (pagliaio[i] === ago[j])
            j = 1;
        }
    }
    return res;
}


console.log(subSeq([1], [4, 12, 4, 1, 4]));
console.log(subSeq([1, 2], [4, 7, 2, 1, 4]));
console.log(subSeq([true, false, true], [true, true, false, true, true]));


///-----------------------------------------------
///-----------------ESERCIZIO 3-------------------
///-----------------------------------------------
function tribo(n) {
    switch (n) {
        case 0:
            return 0;
        case 1:
            return 0;
        case 2:
            return 1;
    }


    return tribo(n - 1) + tribo(n - 2) + tribo(n - 3);
}

console.log(tribo(1));
console.log(tribo(10));
console.log(tribo(22));

///-----------------------------------------------
///-----------------ESERCIZIO 4-------------------
///-----------------------------------------------
function serieParziale(f, n) {
    for (var i = 0, res = 0; i <= n; i++)
        res += f(i);
    return res;
}



console.log(serieParziale(x => 1, 5));
console.log(serieParziale(x => (x % 2 == 0 ? 1 : -1), 9));

///-----------------------------------------------
///-----------------ESERCIZIO 5-------------------
///-----------------------------------------------

function serieParziale2(f) {
    return (n => {
        for (var i = 0, res = 0; i <= n; i++) res += f(i);
        return res;
    });
}



console.log(serieParziale2(x => 1)(5));
console.log(serieParziale2(x => (x % 2 == 0 ? 1 : -1))(9));


///-----------------------------------------------
///-----------------ESERCIZIO 6-------------------
///-----------------------------------------------
function mkmap(s) {

    res = {};
    for (let a of s)
        res[a] = 1;

    return res;
}



console.log(mkmap(["pippo", "pluto"]));
console.log(mkmap([]));
console.log(mkmap(["pippo", "pippo"]));

///-----------------------------------------------
///-----------------ESERCIZIO 7-------------------
///-----------------------------------------------

function pota(t, k) {
    if (t == undefined || t.val > k) return undefined;
    return ({
        val: t.val,
        sx: pota(t.sx, k),
        dx: pota(t.dx, k)
    });
}
var Tree = {
    val: 1,
    sx: {
        val: 8,
        sx: {
            val: 7,
            sx: undefined,
            dx: undefined
        },
        dx: {
            val: 1,
            sx: undefined,
            dx: undefined
        },
    },
    dx: {
        val: 3,
        sx: {
            val: 5,
            sx: undefined,
            dx: undefined
        },
        dx: undefined
    },
};
console.log(pota(Tree, 4));
console.log(pota(Tree, 7));
console.log(pota(Tree, 11));
///-----------------------------------------------
///-----------------ESERCIZIO 8-------------------
///-----------------------------------------------
function pota2(t, k) {
    if (t == undefined) return 0;

    if (t.val > k) return ContaFigli(t);
    else return pota2(t.sx, k) + pota2(t.dx, k);

    function ContaFigli(t2) {
        if (t2 == undefined) return 0;
        return (ContaFigli(t2.sx, k) + ContaFigli(t2.dx, k) + 1);
    }
}



console.log(pota2(Tree, 4));
console.log(pota2(Tree, 7));
console.log(pota2(Tree, 11));

///-----------------------------------------------
///-----------------ESERCIZIO 9-------------------
///-----------------------------------------------

function pota3(t) {
    let vals, vald;
    if (t.sx != undefined)
        vals = pota3(t.sx);
    if (t.dx != undefined)
        vald = pota3(t.dx);
    if (t.sx == undefined && t.dx == undefined)
        return t.val;

    if (!isNaN(vals)) {
        t.val += vals;
        t.sx = undefined;
    }

    if (!isNaN(vald)) {
        t.val += vald;
        t.dx = undefined;
    }

    return t;
}



var Tree = {
    val: 1,
    sx: {
        val: 8,
        sx: {
            val: 7,
            sx: undefined,
            dx: undefined
        },
        dx: {
            val: 1,
            sx: undefined,
            dx: undefined
        },
    },
    dx: {
        val: 3,
        sx: {
            val: 5,
            sx: undefined,
            dx: undefined
        },
        dx: undefined
    },
};
console.log((JSON.stringify(ModificaTree(Tree))));

///-----------------------------------------------
///-----------------ESERCIZIO 10------------------
///-----------------------------------------------

function mogol(r, p) {
    p = p.split('').reverse();
    vo = ['a', 'e', 'i', 'o', 'u'];
    res = [];

    for (let str of r) {
        let isRima = false,
            FristTimeIncontevo = true;
        var a = str.split('').reverse();
        for (let i in a) {
            if (a[i] != p[i])
                break;
            else if (vo.some(x => x == a[i])) {
                if (FristTimeIncontevo)
                    FristTimeIncontevo = false;
                else {
                    isRima = true;
                    FristTimeIncontevo = true;
                    break;
                }
            }
        }

        if (isRima)
            res[res.length] = str;
    }

    return res;

}

console.log(mogol(["cuore", "amore", "sale"], "sudore"));
console.log(mogol(["cuore", "amore", "sale"], "mare"));
console.log(mogol(["cuore", "amore", "sale"], "male"));


///-----------------------------------------------
///-----------------ESERCIZIO 11------------------
///-----------------------------------------------

function granMogol(Q) {
    let c = [];
    for (let Candidati of Q) {


        let i = false,
            o = false,
            a = false;

        if (Candidati.votanti.some(x => x == "Qui"))
            i = true;
        if (Candidati.votanti.some(x => x == "Quo"))
            o = true;
        if (Candidati.votanti.some(x => x == "Qua"))
            a = true;

        if (i && o && a)
            c[c.length] = Candidati.candidato;
    }


    return c.sort()[0];

}

console.log(granMogol([{
        "votati": "io",
        "votanti": ["Qui", "Quo", "Qua"]
    },
    {
        "votati": "tu",
        "votanti": ["Qui", "Quo", "Qua", "si", "iua"]
    },
    {
        "votati": "mammt",
        "votanti": ["cuore", "Qui", "Qua", "sss"]
    }
]));
console.log(granMogol([{
    "votati": "tu",
    "votanti": ["Qui", "Quo", "Qua", "si", "iua"]
}]));
console.log(granMogol([{
    "votati": "mammt",
    "votanti": ["cuore", "Qui", "Qua", "sss"]
}]));
let voti = [{
    candidato: "bbb",
    votanti: ["Quo", "fff", "Quo", "Qui", "Qua"]
}, {
    candidato: "zzz",
    votanti: ["Quo", "Qui", "Qua", "aaaa"]
}, {
    candidato: "ccc",
    votanti: ["gfgf", "vvbv", "vcbdvcbd"]
}];
console.log(granMogol(voti));
///-----------------------------------------------
///-----------------ESERCIZIO 12------------------
///-----------------------------------------------

function zip(o) {
    let res = [];
    for (let key in o)
        res.push([key, o[key]])
    return res;
}

console.log(zip({
    a: 1,
    b: true
}));
console.log(zip({
    b: true,
    a: 1
}));
console.log(zip({}));


///-----------------------------------------------
///-----------------ESERCIZIO 13------------------
///-----------------------------------------------


function unzip(o) {
    let res = {};
    for (let KeyValue of o)
        res[KeyValue[0]] = KeyValue[1];
    return res;
}



console.log(unzip([
    ["a", 1],
    ["b", true]
]));
console.log(unzip([]));

///-----------------------------------------------
///-----------------ESERCIZIO 14------------------
///-----------------------------------------------

function visita(t) {
    if (t.sx != undefined)
        visita(t.sx);
    if (t.dx != undefined)
        visita(t.dx);

    t.val = f(t.val);

    return t;
}


console.log(visita(Tree, x => x % 2));
console.log(visita(Tree, x => x - 3));



///-----------------------------------------------
///-----------------ESERCIZIO 15------------------
///-----------------------------------------------

function visita2(t, f) {
    if (t == undefined) return undefined;

    return {
        val: f(t.val),
        sx: visita2(t.sx, f),
        dx: visita2(t.dx, f)
    };

}

///-----------------------------------------------
///-----------------ESERCIZIO 16------------------
///-----------------------------------------------

function funprop(f, p) {
    return (a, b) => {
        let c = [];
        for (i = a; i <= b; i++)
            if (p == undefined || p(f(i)))
                c[c.length] = i;

        return c;
    };
}

console.log(funprop(n => 2 * n, n => n % 2 == 0)(4, 6));
console.log(funprop(n => 2 * n, n => n > 10)(4, 8));
console.log(funprop(n => n, n => n % 2 == 1)(10, 20));
console.log(funprop(n => n * n)(4, 6));

///-----------------------------------------------
///-----------------ESERCIZIO 17------------------
///-----------------------------------------------

function selApply(f, p) {
    return (a) => {
        let ris = [];
        for (let i in a) {
            if (p(a[i]))
                ris[i] = f(i);
            else
                ris[i] = a[i];
        }
        return ris;
    };
}

let a = [1, 2, 3, 4];

console.log(selApply(n => n * n, n => n % 2 == 0)(a));
console.log(selApply(n => 0, n => n > 2)(a));
console.log(selApply(n => n, n => n > 0)(a));


///-----------------------------------------------
///-----------------ESERCIZIO 18------------------
///-----------------------------------------------


function isHeap(t) {
    let c = t.figli.map(x => {
        if (x.figli != undefined)
            return isHeap(x);
        else
            return t.val > x.val;
    });
    return !c.some(x => x == false);
}


let tree1 = {
    val: 9,
    figli: [{
            val: 8,
            figli: [{
                    val: 7,
                    Figli: undefined
                },
                {
                    val: 1,
                    Figli: undefined
                },
                {
                    val: 3,
                    Figli: undefined
                }
            ]
        },
        {
            val: 3,
            Figli: [{
                val: 5,
                Figli: undefined
            }]
        }
    ]
};
console.log(isHeap(tree1));


///-----------------------------------------------
///-----------------ESERCIZIO 19------------------
///-----------------------------------------------

function semplifica(ao, ak) {
    let a = 0;
    for (let obj of ao) {
        for (let key in obj) {
            if (ak.some(x => x == key))
                continue;
            else {
                delete obj[key];
                a++;
            }
        }
    }
    return a;
}



let o = {
        a: 12,
        q: 3
    },
    ao = [{
        a: 1,
        b: 3
    }, {
        a: 5,
        c: 7
    }, {
        q: 4,
        d: true
    }, o];

console.log(semplifica(ao, ["q", "c"]));