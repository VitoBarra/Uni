import * as fs from "fs";

class FileTransformer {
  fileFind: boolean = true;
  fileName: string;
  fileText: string = "";
  WordInFile = Array<string>();
  Occurencis: Map<string, number>;

  constructor(fileName: string) {
    try {
      this.fileText = fs.readFileSync(fileName).toString();
    } catch (e) {
      this.fileFind = false;
    }

    if (this.fileFind) {
      this.WordInFile = this.fileText
        .split(/[!?,.;:"'\s]+/)
        .filter((x) => x != "" && x != " ");
    }
    this.Occurencis = new Map<string, number>();

    this.fileName = fileName;
  }

  contaParole(): number {
    return this.fileFind ? this.WordInFile.length : -1;
  }

  contaSpazi(): number {
    return this.fileFind
      ? this.fileText.split("").filter((x) => x == " ").length
      : -1;
  }

  contaRighe(): number {
    return this.fileFind ? this.fileText.split(/[\n\r]/gm).length : -1;
  }

  occorrenze(s: string): number {
    let e: number | undefined;

    if (s in this.Occurencis) e = this.Occurencis.get(s);
    else e = this.WordInFile.filter((x) => x == s).length;

    if (e != undefined) {
      this.Occurencis.set(s, e);
      return this.fileFind ? e : -1;
    } else return -1;
  }

  cifra(n: number): number {
    let r: Array<string> = this.fileText
      .split("")
      .map((x) => String.fromCharCode((x.charCodeAt(0) + n) % 1024));
    fs.writeFileSync(`${this.fileName}-${n}.cy`, r.join(""));

    return this.fileFind ? r.length : -1;
  }

  decifra(f: string): number {
    let CifKeyFileName: RegExpMatchArray | null = f.match(/-[\d]+\./);
    let CifKeystr: RegExpMatchArray | null = null;
    let key: number;

    if (CifKeyFileName != null) CifKeystr = CifKeyFileName[0]?.match(/[\d]+/);
    if (CifKeystr != null) key = Number.parseInt(CifKeystr[0].toString());

    let CifText: string = fs.readFileSync(f).toString();

    let DefChars: Array<string> = CifText.split("").map((x) =>
      String.fromCharCode((x.charCodeAt(0) - key) % 1024)
    );

    fs.writeFileSync(`${f}.decy`, DefChars.join(""));
    return this.fileFind ? DefChars.length : -1;
  }

  comprimi(): number {
    let CompressedFile: string = "";
    let charList: Array<string> = this.fileText.split("");

    if (charList.length != 0) {
      let tempChar: string = charList[0];
      let counter: number = 0;
      for (let e of charList) {
        if (e == tempChar) counter++;
        else {
          CompressedFile += (counter > 1 ? counter : "") + tempChar;

          counter = 1;
          tempChar = e;
        }
      }
      CompressedFile += (counter > 1 ? counter : "") + tempChar;
    }
    fs.writeFileSync(`${this.fileName}.comp`, CompressedFile);
    return this.fileFind ? CompressedFile.split("").length : -1;
  }

  decomprimi(f: string): number {
    let ParoleCompressdFile: string = fs.readFileSync(f).toString();
    let DecompressedFile: string = "";

    let CompressedChar: RegExpMatchArray | null = ParoleCompressdFile.match(
      /([\d]+[\D\n\r]|[\D\n\r])/gm
    );
    if (CompressedChar != null)
      for (let e of CompressedChar) {
        let times: RegExpMatchArray | null = e.match(/[\d]+/);
        let char: RegExpMatchArray | null = e.match(/[\D\n\r]/);

        if (char != null) {
          for (
            let i: number = 0;
            i < (times != null ? Number.parseInt(times[0]) : 1);
            i++
          )
            DecompressedFile += char[0];
        }
      }

    fs.writeFileSync(`${this.fileName}.decomp`, DecompressedFile);
    return this.fileFind ? DecompressedFile.split("").length : -1;
  }
}
