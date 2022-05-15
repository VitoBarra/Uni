function isSorted(a)
{
    for(let i =0 ; i<a.length-1;i++)
        if(a[i] >= a[i+1])
            return false;
    return true;        
}

console.log(isSorted([-21,-2,0,4,6,210]))
console.log(isSorted([2,6,8,8,9,21]))
console.log(isSorted([2,6,8,9,10,-42]))
