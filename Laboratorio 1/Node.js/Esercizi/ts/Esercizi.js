///-----------------------------------------------
///-----------------ESERCIZIO 17------------------
///-----------------------------------------------
function diff(d1, d2) {

    function getDays(d) {

        let giornidif = 0;
        const n31 = [1, 3, 5, 7, 8, 10, 12];
        const n30 = [6, 9, 11];

        giornidif += d.giorno;
        var anniToMesi = d.anno * 12 + d.mese;

        for (let i = 1; i < anniToMesi ; i++) {

            let anno = Math.floor(i / 12) ;
            let mese = (i % 12) ;

            if (n30.includes(mese)) 
                giornidif += 30;
            else if (mese == 2) {
                if (anno % 4 == 0 && anno % 100 != 0) //bisestile
                    giornidif += 29;
                else //ordinario
                    giornidif += 28;
            } else
                giornidif += 31;
        }


        return giornidif;
    }

    return getDays(d2) - getDays(d1);
}




