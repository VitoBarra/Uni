package Exception;

public class ExceptionHelper {

    public static IllegalArgumentException CheckBound(int Value, int Low, int Upper, String CheckWhat) {
        if (Value < Low || Value > Upper)
            return new IllegalArgumentException(
                    String.format("%s %s non è valido, per essere valido deve essere nel intervallo [%s,%s]", CheckWhat,
                            Value, Low, Upper));
        return null;
    }

    public static boolean CheckBound(int Value, int Low, int Upper) {
        return Value < Low || Value > Upper;
    }

    public static String MessageFormatter(int Value, int Low, int Upper, String CheckWhat) {
        return String.format("%s %s non è valido, per essere valido deve essere nel intervallo [%s,%s]", CheckWhat,
                Value, Low, Upper);
    }

}
