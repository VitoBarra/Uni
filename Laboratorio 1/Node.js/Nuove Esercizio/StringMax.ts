function c(att:Array<string>)
{
    let p = {};
    function e(arr:Array<string>)
    {
        let a = arr.map(x=>x.length)
        return a.indexOf(a.reduce((a,x)=>Math.max(a,x)));
    }


    let ind = e(att);
    p[ind] =att[ind];

    return p;
}


let r =["asdasd454asd","asdasdouih379gaiuhdjiasbnjidasihuioh","ssssss","asdasd"];

c(r);



