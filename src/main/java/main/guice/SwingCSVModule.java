package main.guice;

import com.google.inject.AbstractModule;
import com.google.inject.Singleton;
import infrastructure.loader.CSVPersonLoader;
import infrastructure.loader.FilePath;
import infrastructure.loader.PersonLoader;
import infrastructure.repository.*;
import view.HomeView;
import view.swing.ManagerFrame;
import view.swing.panel.HomePanel;

import javax.swing.*;

public class SwingCSVModule extends AbstractModule {

    private final FilePath path;

    public SwingCSVModule(String path) {
        this.path = new FilePath(path);
    }


    @Override
    protected void configure() {
        bind(FilePath.class).toInstance(path);
        bind(JFrame.class).to(ManagerFrame.class).in(Singleton.class);

        bind(PersonRepository.class).to(ListPersonRepository.class).in(Singleton.class);
        bind(LocationRepository.class).to(DefaultLocationRepository.class).in(Singleton.class);

        bind(PersonLoader.class).to(CSVPersonLoader.class);

        bind(HomeView.class).to(HomePanel.class);
    }

}
