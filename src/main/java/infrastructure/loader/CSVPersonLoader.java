package infrastructure.loader;

import domain.application.PersonBuilder;
import domain.model.Location;
import domain.model.Person;
import infrastructure.exceptions.AlreadyExistInRepositoryException;
import infrastructure.repository.LocationRepository;
import infrastructure.repository.PersonRepository;

import javax.inject.Inject;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.InputStream;
import java.nio.charset.StandardCharsets;
import java.util.Scanner;

public class CSVPersonLoader implements PersonLoader {

    private final String path;
    private final PersonRepository personRepository;
    private final LocationRepository locationRepository;

    @Inject
    public CSVPersonLoader(FilePath filePath, PersonRepository personRepository, LocationRepository locationRepository) {
        this.path = filePath.path;
        this.personRepository = personRepository;
        this.locationRepository = locationRepository;
    }

    private void loadPersons() {
        try {
            InputStream inputStream = new FileInputStream(path);
            Scanner scanner = new Scanner(inputStream, StandardCharsets.UTF_8);

            while (scanner.hasNextLine()) {
                String[] infos = processSplit(scanner);

                Person currentPerson = PersonBuilder.generatePerson()
                        .withIdentity(infos[0], infos[1])
                        .withLocation(locationRepository.searchWithName(infos[2]))
                        .withContact(infos[4], infos[5])
                        .withJob(infos[6])
                        .build();

                try {
                    personRepository.add(currentPerson);
                } catch (AlreadyExistInRepositoryException e) {
                    System.err.println(currentPerson.getIdentity() + " has duplicate");
                }
            }

        } catch (FileNotFoundException e) {
            throw new RuntimeException(e);
        }
    }

    private void loadLocations() {
        try {
            InputStream inputStream = new FileInputStream(path);
            Scanner scanner = new Scanner(inputStream, StandardCharsets.UTF_8);

            while (scanner.hasNextLine()) {
                String[] infos = processSplit(scanner);
                Location location = locationRepository.searchWithName(infos[2]);

                if (location == null
                        || location.getCity().equals("") && !infos[2].equals("")
                        || location.getPostalCode().equals("") && !infos[3].equals("")) {
                    locationRepository.add(new Location(infos[2], infos[3]));
                }
            }

        } catch (FileNotFoundException e) {
            throw new RuntimeException(e);
        }
    }

    private String[] processSplit(Scanner scanner) {
        String line = scanner.nextLine();
        String[] infos = new String[7];
        StringBuilder currentString = new StringBuilder();
        int i = 0;

        for (char c : line.toCharArray()) {
            if (c == ',') {
                infos[i] = currentString.toString();
                currentString = new StringBuilder();
                i++;
            } else {
                currentString.append(c);
            }
        }

        return infos;
    }

    @Override
    public void load() {
        loadLocations();
        loadPersons();
    }
}
