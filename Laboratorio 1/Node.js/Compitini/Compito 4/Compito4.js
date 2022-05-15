function sommaPari(a)
{
    return a.reduce((ac,num)=>
    {   if(num %2==0)
            ac+=num;
    }
    );
}

console.log(sommaPari([5,9,1,-4,3,6,2,-5]));