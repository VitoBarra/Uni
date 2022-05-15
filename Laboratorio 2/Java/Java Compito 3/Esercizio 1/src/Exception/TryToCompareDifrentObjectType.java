package Exception;

public class TryToCompareDifrentObjectType 
  extends RuntimeException {
    public TryToCompareDifrentObjectType(String errorMessage) {
        super(errorMessage);
    }
}