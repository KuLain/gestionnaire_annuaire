package infrastructure.exceptions;

public class NotInRepositoryException extends RuntimeException {

    public NotInRepositoryException(Object o) {
        super(o + " not in repository");
    }

}
