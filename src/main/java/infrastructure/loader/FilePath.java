package infrastructure.loader;

public class FilePath {

    public String path;

    public FilePath(String path) {
        this.path = path;
    }

    public void changePath(String path) {
        this.path = path;
    }

    @Override
    public String toString() {
        return path;
    }

}
