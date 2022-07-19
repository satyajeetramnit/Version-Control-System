
// Class to represent a File in a filesytem
class File {

    // Displays the filename and its contents
    public void display() {

    }
}

// Class to represent difference between current and previous version of a file
class Diff {

}

// Class to represent the collection of Files
class FileSystem {

    // Displays all files and its contents in this filesystem
    /*
        OUTPUT FORMAT:
        <FileName>: <FileContents>
        <Repeat for all files>
    */
    public void displayContents() {

    }

    // Add new file to file system.
    public void createNewFile(String fileName, String content) {

    }

    // Append content to file
    public void appendToFile(String fileName, String contentToAppend) {

    }

    // Delete a file from FileSystem
    public void deleteFile(String fileName) {

    }

    // Delete last n charaters from file
    public void trimFile(String fileName, int n) {

    }
}

// Commit class should have ID, message and the Diffs for files (changes made for each file in this commit)
class Commit {
    String ID;

    public String getID() {
        return ID;
    }
}

class VersionControlDriver {

    /* 
        * Declare variables for:
        * Commit list
    */

    // Get content of file at a paticular commit
    public String getFileContentAtCommit(String fileName, String commitID) {

        return "";
    }

    // Commit current state to VCS
    public Commit addCommit(String message, FileSystem fileSystem) {

        return new Commit();
    }

    // Get a File System image as of the provided Commit instance
    // i.e. get a copy of the entire file system at the point of time of this commit
    public FileSystem checkout(String commitID) {

        return new FileSystem();
    }

    // Shows the status of the Working Directory that should include last commit message and changes
    /*
        OUTPUT FORMAT:
        ********CommitID: <ID>********
        Message: <Commit Message>

        Diff: <File Name>
        <Operation Type: Create, Delete, Append, Trim>
        <+/-><Content changed>(eg: +XYZ or -XYZ)

        <Repeat Diff for all changed files>
        **********************************

        SAMPLE OUTPUT:
        ********CommitID: <ID>***********
        Message: Sample commit
        Diff: Sample file name
        Created
        +Sample text
        **********************************
    */
    public void status() {

    }

    // Show last n commits. If n is -1 show all commits
    /*
        OUTPUT FORMAT:
        **********************************
        CommitID: <ID>
        Message: <Commit Message>

        <Repeat for last n commit>
        **********************************

    */
    public void log(int n) {

    }

}
public class javaVersionControlSystem {

    public static void main(String[] args) {
        VersionControlDriver vcd = new VersionControlDriver();
        FileSystem  workingDirectory = new FileSystem();

        // TEST CASES

        // 1) Add a new file to Working Directory and commit to the VCS
        System.out.println("1) Add a new file to Working Directory and commit to the VCS\n");
        workingDirectory.createNewFile("IndianStates", "Telangana, Karnataka, ");
        Commit commit1 = vcd.addCommit("Created IndianStates File", workingDirectory);
        vcd.status();

        String contentAtCommit1 = vcd.getFileContentAtCommit("IndianStates", commit1.getID());
        System.out.println("\n  IndianStates @C1: " + contentAtCommit1);
        System.out.println("----------------\n");

        // 2) Append to 'IndianStates' file; add new files Cities and Khans and commit
        System.out.println("2) Append to 'IndianStates' file; add new files Cities and Khans and commit\n");
        workingDirectory.appendToFile("IndianStates", "Maharashtra, ");
        workingDirectory.appendToFile("IndianStates", "Punjab, ");
        workingDirectory.createNewFile("IndianCities", "Hyderabad, Bangalore, Pune ");
        workingDirectory.createNewFile("Khans", "Shahrukh, Salman, Aamir ");
        Commit commit2 = vcd.addCommit("Added some more states; cities and Khans file added", workingDirectory);
        vcd.status();

        contentAtCommit1 = vcd.getFileContentAtCommit("IndianStates", commit1.getID());
        String contentAtCommit2 = vcd.getFileContentAtCommit("IndianStates", commit2.getID());

        System.out.println("\n  IndianStates @C1: " + contentAtCommit1);
        System.out.println("\n  IndianStates @C2: " + contentAtCommit2);
        System.out.println("----------------\n");

        // 3) Delete from 'IndianCities' file; delete Khans and commit
        System.out.println("3) Delete from 'IndianCities' file; delete Khans and commit\n");
        workingDirectory.trimFile("IndianCities", 5);
        workingDirectory.deleteFile("Khans");
        Commit commit3 = vcd.addCommit("Deleted some cities; and removed Khans file", workingDirectory);
        vcd.status();
        vcd.log(-1);

        System.out.println("----------------\n");

        // 4) Checkout scenarios
        System.out.println("4) Checkout scenarios\n");
        FileSystem workingDirAtC1 = vcd.checkout(commit1.getID());
        System.out.println("Working Directory as of " + commit1.getID() + ":");
        workingDirAtC1.displayContents();

        FileSystem workingDirAtC2 = vcd.checkout(commit2.getID());
        System.out.println("Working Directory as of " + commit2.getID() + ":");
        workingDirAtC2.displayContents();

        FileSystem workingDirAtC3 = vcd.checkout(commit3.getID());
        System.out.println("Working Directory as of " + commit3.getID() + ":");
        workingDirAtC3.displayContents();

        System.out.println("----------------\n");

        // 5) Modify existing files, add two new files and commit
        System.out.println("5) Modify existing files, add two new files and commit\n");
        workingDirectory.appendToFile("IndianStates", "Rajasthan, Kerala ");
        workingDirectory.trimFile("IndianCities", 11);
        workingDirectory.createNewFile("Countries", "India, USA, Japan, ");
        workingDirectory.createNewFile("Khans", "Zaheer, Rashid, Imran");
        Commit commit4 = vcd.addCommit("Added to IndianStates. Deleted from IndianCities. Added two new files", workingDirectory);

        vcd.status();
        vcd.log(-1);

        FileSystem workingDirAtC4 = vcd.checkout(commit4.getID());
        System.out.println("Working Directory as of " + commit4.getID() + ":");
        workingDirAtC4.displayContents();

        System.out.println("----------------\n");
    }
}
