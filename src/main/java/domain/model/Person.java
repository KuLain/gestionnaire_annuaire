package domain.model;

public class Person {

    private Identity identity = null;
    private Location location = null;
    private Contact contact = null;
    private String job = null;

    public void setIdentity(Identity identity) {
        this.identity = identity;
    }

    public void setLocation(Location location) {
        this.location = location;
    }

    public void setContact(Contact contact) {
        this.contact = contact;
    }

    public void setJob(String job) {
        this.job = job;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append(identity).append("\n");
        for (Object object : new Object[]{identity, location, contact, job}) {
            if (object != null) {
                sb.append("\t").append(object).append("\n");
            }
        }
        sb.setLength(sb.length()-1);
        return sb.toString();
    }
}
