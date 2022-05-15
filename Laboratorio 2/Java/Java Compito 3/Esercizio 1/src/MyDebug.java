import java.util.*;

public class MyDebug {
    
    public static void DebugLog(Map<Articolo,Integer> map) {
        List<Articolo> ar = new ArrayList<>(map.keySet());
        for (Articolo s : ar)
            System.out.print(String.format("| %s{%s}  ", s, map.get(s)));
        System.out.println(String.format("[%s]", ar.size()));
        System.out.println("--------------------------------------------------------------");
    }

    public static void DebugLog(Set<String> set, String StrInjected) {
        List<String> ar = new ArrayList<>(set);
        for (String s : ar)
            System.out.print(String.format("| %s  ", s));
        System.out.print(StrInjected);
        System.out.println(String.format("[%s]", ar.size()));
        System.out.println("--------------------------------------------------------------");
    }


    public static void DebugLog(List<Articolo> ar) {
        for (Articolo s : ar)
            System.out.print(String.format(" | %s", s));
        System.out.println(String.format("[%s]", ar.size()));
        System.out.println("--------------------------------------------------------------");
    }

}
