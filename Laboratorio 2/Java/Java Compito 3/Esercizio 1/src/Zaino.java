import java.util.*;

import Exception.NoWay;

public class Zaino {
    private final int Pmax ;
    private final int Vmax ;

    private int Pused = 0;
    private int Vused = 0;
    private int ValoreContenuto = 0;
    //ai fini dello scopo di Zaino non era necessario salvare le referenze agli articoli ma solo i vari Tipi di articoli
    // ho queindi scelto set che mi garantisce che non ci siano ripetizioni
    private Set<String> ArticoliSet = new HashSet<String>();

    Zaino(int p, int v) {
        Pmax = p;
        Vmax = v;
    }

    boolean puo_contenere(Articolo a) {
        return (Pused + a.GetPeso() <= Pmax) && (Vused + a.GetVolume() <= Vmax);
    }

    void aggiungi(Articolo a) {
        if (puo_contenere(a)) {
            Pused += a.GetPeso();
            Vused += a.GetVolume();
            ValoreContenuto += Articolo.GetValoreTipoArticolo(a.GetTipo());
            ArticoliSet.add(a.GetTipo());
        } else
            throw new NoWay(String.format("non è possibile aggiungere l articolo  %s allo zaino",a));
    }

    void svuota() {
        Pused = 0;
        Vused = 0;
        ValoreContenuto=0;
        ArticoliSet.clear();
    }

    int peso() {
        return Pused;
    }

    int volume() {
        return Vused;
    }
  
    int valore() {
        return ValoreContenuto;
    }

    boolean contiene_tipo(String t) {
        return ArticoliSet.contains(t);
    }

    void riempi(Magazzino m) {
        System.out.println("--------------------------------------------------------------");
        System.out.println("Articoli by value :");
        for (Articolo a : m.disponibiliByValue()) {
             if (!contiene_tipo(a.GetTipo())) {
                try {
                    m.prendi1(a);
                    aggiungi(a);
                    MyDebug.DebugLog(ArticoliSet,String.format("{%s,%s,%s}",ValoreContenuto,Pused,Vused));
                } catch (Exception e) {
                    System.out.println(e.getMessage());
                    System.out.println("--------------------------------------------------------------");
                }
             }
        }

    }
}
