package main;

import com.google.inject.Guice;
import com.google.inject.Injector;
import main.guice.SwingCSVModule;

public class Main {

    public static void main(String[] args) {
        Injector injector = Guice.createInjector(new SwingCSVModule(""));
    }

}
