package Exception;

public class OutOfStock   extends RuntimeException {
    public OutOfStock(String errorMessage) {
        super(errorMessage);
    }    
}
