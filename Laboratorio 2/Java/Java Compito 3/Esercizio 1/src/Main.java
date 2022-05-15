class Main {
  public static void main(String[] args) {
        
 
        Articolo.assegna_valore("tenda", 10);
        Articolo.assegna_valore("torcia", 4);
        Articolo.assegna_valore("set pentole", 3);
        Articolo.assegna_valore("notebook", 2);
        Magazzino m = new Magazzino();
        m.rifornisci("File/elenco.csv");
        // for(Articolo a: m.disponibili())
        for(Articolo a: m.disponibiliByValue())
          System.out.println(a);
        Zaino z = new Zaino(51, 10000);
        z.riempi(m);
        z.svuota();
        z.riempi(m);
    // Il codice qui sopra dovrebbe generare un 
        // output simile al seguente (dipende da come avete
    // definito il metodo toString in Articolo)

            // borraccia, 2, 1,  (1)
            // borraccia, 10, 5,  (1)
            // bussola, 1, 1,  (1)
            // fornello, 4, 3,  (1)
            // motosega, 50, 10,  (1)
            // notebook, 8, 2,  (2)
            // pannelli solari, 10, 4,  (1)
            // paracadute, 10, 50,  (1)
            // radio, 2, 1,  (1)
            // radio, 3, 2,  (1)
            // sacco a pelo, 1, 3,  (1)
            // set pentole, 15, 8,  (3)
            // spazzolino, 1, 1,  (1)
            // tenda, 10, 8,  (10)
            // tenda, 15, 9,  (10)
            // tenda, 20, 10,  (10)
            // torcia, 1, 2,  (4)
            // torcia, 5, 3,  (4)

    System.out.println("--- bye -----");
        
  }
}
