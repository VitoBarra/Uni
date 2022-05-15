import java.io.*;
import java.util.*;

import Exception.OutOfStock;

public class Magazzino {
  // siccome gli articoli sono univoci ho usato una mappa per salvare il numero di
  // elementi
  private Map<Articolo, Integer> ArticoliRegister;

  public Magazzino() {
    // ho scelto Treemap com tipo concreto di ArticoliRegister perche mi permetteva
    // di mantenere un ordinamento dei valori tramite definizione dei criteri di
    // comparazione
    ArticoliRegister = new TreeMap<Articolo, Integer>();
  }

  int aggiungi(Articolo a, int q) {

    Integer v = ArticoliRegister.get(a);
    int nq = (v == null ? 0 : v) + q;
    ArticoliRegister.put(a, nq);
    return nq;
  }

  void rifornisci(String filename) {
    try {
      BufferedReader in = new BufferedReader(new FileReader(filename));
      String line;

      while ((line = in.readLine()) != null) {
        String[] T = line.split(",");
        Articolo ar = new Articolo(T[0], Integer.parseInt(T[1]), Integer.parseInt(T[2]));
        aggiungi(ar, Integer.parseInt(T[3]));
      }
      in.close();
    } catch (Exception e) {
      e.printStackTrace();
    }
  }

  boolean disponibile(Articolo a) {
    Integer Na = ArticoliRegister.get(a);
    return Na != null ? Na > 0 : false;
  }

  int volume_tot() {
    int sum = 0;
    for (Articolo a : ArticoliRegister.keySet())
      sum += a.GetVolume() * ArticoliRegister.get(a);
    return sum;

  }

  public List<Articolo> disponibili() {
    return new ArrayList<Articolo>(ArticoliRegister.keySet());
  }

  public List<Articolo> disponibiliByValue() {

    Map<Articolo, Integer> a = new TreeMap<Articolo, Integer>(Articolo.ByValueComparator());

    a.putAll(ArticoliRegister);
    MyDebug.DebugLog(a);
    return new ArrayList<Articolo>(a.keySet());

  }

  public int prendi1(Articolo a) {
    Integer Nart = ArticoliRegister.get(a);
    if (Nart != null && Nart > 0)
      if (Nart - 1 > 0)
        ArticoliRegister.put(a, Nart - 1);
      else
        ArticoliRegister.remove(a);
    else
      throw new OutOfStock(String.format("non ci sono piu elementi di tipo %s ", a));

    MyDebug.DebugLog(ArticoliRegister);
    return Nart;
  }
}