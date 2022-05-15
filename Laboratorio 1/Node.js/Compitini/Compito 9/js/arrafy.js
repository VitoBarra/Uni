function arrayfy(f)
{
    return x=>x.map(y=>y==f(y));
}



let a=[5,2,4]
console.log(arrayfy(x=>2)(a)) //[false,true,false]
a=[5,2,4] 
console.log(arrayfy(x=>2*x)(a)) //, a vale [false,false,false]
a="pippo".split("")
console.log(arrayfy(c=>"p")(a))// [true,false,true,true,false]

console.log(typeof arrayfy(x=>0)) //è "function"