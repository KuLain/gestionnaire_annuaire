package main;

import com.google.inject.Guice;
import com.google.inject.Injector;
import infrastructure.repository.PersonRepository;
import main.guice.SwingCSVModule;
import view.HomeView;

import javax.swing.*;

public class Main {

    public static void main(String[] args) {
        Injector injector = Guice.createInjector(new SwingCSVModule(""));
        injector.getInstance(HomeView.class).display(injector.getInstance(PersonRepository.class).getListPerson());
        injector.getInstance(JFrame.class).setVisible(true);
    }

}
