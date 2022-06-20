package infrastructure.exceptions;

public class AlreadyExistInRepositoryException extends RuntimeException {

    public AlreadyExistInRepositoryException(Object o) {
        super(o + " already exist in repository");
    }

}
