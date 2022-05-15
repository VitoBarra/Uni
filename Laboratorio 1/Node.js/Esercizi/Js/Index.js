// Sia a un array di numeri interi distinti, ordinato in senso crescente. Si scriva una funzione JS cercaId(a), che, con un numero OTTIMO di operazioni di accesso ad a,
// restituisce l'indice i tale che a[i]==i, se esiste, e -1 altrimenti. Si assuma che, se tale indice esiste, allora e' l'unico a verificare la condizione 




class MatrixError extends Error {

}

function isAntisymmetric(m) {
    let dim;
    for (let e of m) {
        if (m.length != e.length)
            throw new MatrixError("errore matrice");
    }
    dim = m.length;

    let ris = true;
    for (let i = 0; i < dim; i++)
        for (let j = i; j < dim - i; j++)
            if (m[i + j][i] != (-m[i][i + j]))
                ris = false;


    return ris;
}

console.log(isAntisymmetric([
    [0, 2, -1],
    [-2, 0, -4],
    [1, 0]
]))