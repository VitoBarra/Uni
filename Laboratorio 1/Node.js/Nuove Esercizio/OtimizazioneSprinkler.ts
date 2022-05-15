

function OptimizeSpricl<T>(map:T[][], spr:number[][],n:number)
{
    for(let i=0 ;i<map.length ;i++)
        for(let j=0 ;j<map[i].length ;j++)
        {
            
        }
}



function Inizialize(n: number) : Array<Array<Array<number>>>
{
    let e:Array<Array<number>> = new Array<Array<number>>(); 

    let spr:number[][] =
    [
        [0,1,0],
        [1,2,1],
        [0,1,0]
    ];

    for(let i=0;i<n;i++)
        {
        let a:Array<number>= new Array<number> ();
        for(let j=0;j<n;j++)
            a.push(0);
        e.push(a);
    }

    return [e,spr];
}

let y :Array<any> = Inizialize(15);

OptimizeSpricl<number>(y[0],y[1],1)