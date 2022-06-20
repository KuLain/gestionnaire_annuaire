package infrastructure.exceptions;

public class InvalidLineFormatException extends RuntimeException {

    public InvalidLineFormatException(String line) {
        super("Invalid format : " + line + "\nSize : " + line.split(",").length);
    }

}
