package infrastructure.loader;

import domain.application.PersonBuilder;
import domain.model.Person;
import infrastructure.exceptions.AlreadyExistInRepositoryException;
import infrastructure.repository.PersonRepository;

import javax.inject.Inject;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.InputStream;
import java.nio.charset.StandardCharsets;
import java.util.Arrays;
import java.util.Scanner;

public class CSVPersonLoader implements PersonLoader {

    private final FilePath filePath;
    private final PersonRepository personRepository;

    @Inject
    public CSVPersonLoader(FilePath filePath, PersonRepository personRepository) {
        this.filePath = filePath;
        this.personRepository = personRepository;
    }

    private void loadPersons() {
        try {
            InputStream inputStream = new FileInputStream(filePath.path);
            Scanner scanner = new Scanner(inputStream, StandardCharsets.UTF_8.name());

            while (scanner.hasNextLine()) {
                String[] infos = processSplit(scanner);

                Person currentPerson = PersonBuilder.generatePerson()
                        .withIdentity(infos[0], infos[1])
                        .withLocation(infos[2], infos[3])
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

        infos[i] = currentString.toString();

        return infos;
    }

    @Override
    public void load() {
        loadPersons();
    }
}
