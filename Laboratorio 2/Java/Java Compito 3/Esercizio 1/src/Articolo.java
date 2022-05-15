import java.util.*;
import Exception.*;

public class Articolo implements Comparable<Articolo> {

    private String Tipo;
    private int Peso;
    private int Volume;

    private static Map<String, Integer> valuesMap = new HashMap<String, Integer>();

    Articolo(String _tipo, int _peso, int _volume) {
        Tipo = _tipo;
        Peso = _peso;
        Volume = _volume;
        if (!valuesMap.containsKey(_tipo))
            valuesMap.put(_tipo, 1);
    }

    public static void assegna_valore(String tipo, int nuovo_valore) {
        valuesMap.put(tipo, nuovo_valore);
    }
    public static Integer GetValoreTipoArticolo(String a) {
        return valuesMap.get(a);
    }

    @Override
    public boolean equals(Object obj) {

        if (!(obj instanceof Articolo))
            throw new TryToCompareDifrentObjectType("Oggetto diverso da articolo");
        Articolo onjA = (Articolo) obj;

        return Tipo.equals(onjA.Tipo) && valuesMap.get(Tipo) == valuesMap.get(onjA.Tipo) && Volume == onjA.Volume
                && Peso == onjA.Peso;

    }

    @Override
    public int compareTo(Articolo o) {

        int v = Tipo.compareTo(o.Tipo);

        if (v != 0)
            return v;
        if (Peso != o.Peso)
            return Peso > o.Peso ? 1 : -1;
        if (Volume != o.Volume)
            return Volume > o.Volume ? 1 : -1;

        return 0;

    }

    public int compareToByValue(Articolo o) {

        Integer v1 = valuesMap.get(Tipo), v2 = valuesMap.get(o.Tipo);

        if (v1 != v2)
        return v1 > v2 ? -1 : 1;
        if (Peso != o.Peso)
            return Peso > o.Peso ? 1 : -1;
        if (Volume != o.Volume)
            return Volume > o.Volume ? 1 : -1;

        return Tipo.compareTo(o.Tipo);
    } 

    public static Comparator<Articolo> NaturalComparator() {
        return new Comparator<Articolo>() {
            @Override
            public int compare(Articolo o1, Articolo o2) {
                return o1.compareTo(o2);
            }
        };
    }

    public static Comparator<Articolo> ByValueComparator() {
        return new Comparator<Articolo>() {
            @Override
            public int compare(Articolo o1, Articolo o2) {
                return o1.compareToByValue(o2);
            }
        };
    }



    @Override
    public String toString() {
        return String.format("(%s{%s},%s,%s)", Tipo, valuesMap.get(Tipo), Peso, Volume);
    }

    public String GetTipo() {
        return Tipo;
    }

    public int GetVolume() {
        return Volume;
    }

    public int GetPeso() {
        return Peso;
    }
}
