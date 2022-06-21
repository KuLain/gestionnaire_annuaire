package main.guice;

import com.google.inject.AbstractModule;
import com.google.inject.Singleton;
import infrastructure.loader.CSVPersonLoader;
import infrastructure.loader.FilePath;
import infrastructure.loader.PersonLoader;
import infrastructure.repository.*;

public class SwingCSVModule extends AbstractModule {

    private final FilePath path;

    public SwingCSVModule(String path) {
        this.path = new FilePath(path);
    }


    @Override
    protected void configure() {
        bind(FilePath.class).toInstance(path);

        bind(PersonRepository.class).to(ListPersonRepository.class).in(Singleton.class);
        bind(LocationRepository.class).to(DefaultLocationRepository.class).in(Singleton.class);

        bind(PersonLoader.class).to(CSVPersonLoader.class);
    }

}
