angolo(d)
{
    let e  = d.getUTCHours();
    if(e>12)
        e -=12;

    
    
}

angolo(new Date("2021-04-23 14:00:00"))// -> 60
angolo(new Date("2021-04-23 14:15:15"))// -> 23
angolo(new Date("2021-04-23 6:50:50")) //-> 95