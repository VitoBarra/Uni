"use strict";
/*Progettino in TS
NOTA: in allegato trovate dei file di test: non li cancellate, e fatene una copia di backup prima di eseguire il vostro codice, in modo tale da poter confrontare l'output dei vs file con quelli forniti negli esempi.

Non viene fornito alcun ambiente di test. In fondo sono riportati alcuni casi di test (sui file in allegato).
*/
Object.defineProperty(exports, "__esModule", { value: true });
class FileTransformer {
    constructor(fileName) {
        this.WORDS = /[^!?,.;:"'\s]+/gm;
        this.SPACES = /[^!?,.;:"'\s]/gm;
        this.LINES = /[\n\r]/gm;
        this.OCCURRENCES = (word) => new RegExp("\\b(\\w*" + word + "\\w*)\\b", "gmi");
        this.fileName = fileName;
    }
}
//# sourceMappingURL=index.js.map