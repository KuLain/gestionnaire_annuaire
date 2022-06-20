package main.guice;

import com.google.inject.AbstractModule;
import com.google.inject.Singleton;
import infrastructure.repository.DefaultLocationRepository;
import infrastructure.repository.DefaultPersonRepository;
import infrastructure.repository.LocationRepository;
import infrastructure.repository.PersonRepository;

public class SwingModule extends AbstractModule {

    @Override
    protected void configure() {
        bind(PersonRepository.class).to(DefaultPersonRepository.class).in(Singleton.class);
        bind(LocationRepository.class).to(DefaultLocationRepository.class).in(Singleton.class);
    }

}
