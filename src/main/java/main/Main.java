package main;

import com.google.inject.Guice;
import com.google.inject.Injector;
import infrastructure.loader.PersonLoader;
import main.guice.SwingCSVModule;

public class Main {

    public static void main(String[] args) {
        Injector injector = Guice.createInjector(new SwingCSVModule("src/main/resources/annuaire5000.csv"));
        injector.getInstance(PersonLoader.class).load();
    }

}
