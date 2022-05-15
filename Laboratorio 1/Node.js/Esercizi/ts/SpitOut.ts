

// Si scriva una funzione spitOut(a,p) che, dati come argomenti un array a e una 
// funzione p, stampi tramite console.log() tutti gli elementi e di a tali che 
// l’invocazione di p(e) restituisca true o un valore che viene promosso a true

function spitOut<T>(a:Array<T>,p:Function) :void 
{
    a.forEach(e => {
        if(!!p(e))
            console.log(e);
    });
}


spitOut<number>([12,7,14,0,561],(e)=>(e%3==0));
spitOut<string>(["la","vispa","teresa","solea"],(e)=>e.indexOf("s"));
spitOut<number>([31,3.1415, 1.4142, 7],(e)=>e==Math.round(e)) ;



