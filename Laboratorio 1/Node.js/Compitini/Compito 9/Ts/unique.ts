


function unique<T>(a, equals): Array<T> {
    let ris: Array<T> = new Array<T>();

    for (let e of a) 
    {
        let find: boolean = true;

        for (let w of ris)
            if (equals(e, w))
                find = false;
        if (find)
        
        ris.push(e);
    }

    return ris;
}


Esempio:
console.log(unique([3, 5, 3, 2, 8, 5], ((x, y) => x == y)))
console.log(unique([0, 0, 0, 0, 0, 0, 0], ((x, y) => x == y)))
console.log(unique(['hello', 'hello', 'how', 'are', 'you'], ((x, y) => x == y)))
