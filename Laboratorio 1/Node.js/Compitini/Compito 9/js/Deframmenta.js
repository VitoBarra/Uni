function deframmenta(a)
{
    let temp =a;
   for (let i = 0; i < a.length; i++) {
       if (a[i] == a[i + 1]) {
           for (let j = i + 1; j < a.length; j++) {
               if (a[j] != a[j + 1]) {
                   i = j;
                   break;
               }
           }
       } 
       else delete temp[i];
   }
   return temp.filter(x=> x!=null);
}


console.log(deframmenta([1,1,2,3,3,3,2,2,4]));
console.log(deframmenta([0,0,0,0,0,1,0,1,1]));
console.log(deframmenta([1,0]));