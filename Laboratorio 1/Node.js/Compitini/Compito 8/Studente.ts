import fs from "fs";
class Studente {
  nome: String;
  cognome: String;
  citta: String;
  votoLaurea: String;

  constructor(
    nome: String,
    cognome: String,
    citta: String,
    votoLaurea: String
  ) {
    this.nome = nome;
    this.cognome = cognome;
    this.citta = citta;
    this.votoLaurea = votoLaurea;
  }
}

function leggiStudenti(file: string): Array<Studente> {
  let contenuto = fs.readFileSync(file).toString();
  let ris: Array<Studente> = new Array<Studente>();
  let studenti = contenuto.split("\n");
  for (let r of studenti) {
    let e = r.split(",");
    ris.push(new Studente(e[0], e[1], e[2], e[3]));
  }

  return ris;
}
