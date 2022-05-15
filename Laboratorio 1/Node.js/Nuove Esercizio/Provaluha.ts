
interface Iveicolo
{
    se:number;

    cercapalla :(x)=>1|2;
}
class monovolume implements Iveicolo
{
    se: number;
    constructor(se:number)
    {
        this.se = se;
    }
    // cercapalla:() => 1;
    cercapalla(x):1|2{return this.se?1:2;}
}

class vos extends monovolume
{
}

let e:monovolume = new monovolume(1);

let a:vos = new vos(1); 

function instanceOfA(object: any): object is Iveicolo{
    return 'se' in object;
}



console.log(e instanceof monovolume); 
console.log(e instanceof vos);  
console.log(a instanceof monovolume); 
console.log(a instanceof vos);
console.log(instanceOfA(a));  
console.log(instanceOfA(e)); 