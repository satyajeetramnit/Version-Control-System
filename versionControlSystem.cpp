// Pointers

// File - named entity having string contents
// Filesystem - collection of files
// Users can create, delete and edit files. 
// Only two types of edit operations are allowed: Append to the end of file, and delete last n characters from file
// Version Control System - A system to track the changes made to the file system 
// Commit - A checkpoint in the history of the file system.
// Diff - It represents the changes since the last version of file.
// Using a commit we can get the contents of the file system at the point in time of that commit
// Each commit SHOULD NOT store separate full copies of each file
// A commit should only store the changes made to the file after the previous commit
// We can have as many commits as user wants to save checkpoints.
// We should be able to retrieve the state of a file or entire filesystem as of a given point in time using commit ID


#include<iostream>
#include<algorithm>
#include<string.h>
#include<vector>

using namespace std;

// Class to represent a file in a filesystem

class File{
    public:
        string name;
        string contents;
        // int ID;
        File(string name, string contents){
            this->name = name;
            this->contents = contents;
            // this->ID = ID;
        }

        // Displays the filename and its contents
        void display(){
            cout<<"File name: "<<name<<endl;
            cout<<"Contents: "<<contents<<endl;
        }
};

// array of files
vector<File> files;

// Class to represent difference between current and previous version of a file
class Diff{
    
};

// Class to represent the collection of files
class FileSystem{
    public:
    // Displays all files and its contents in this filesystem

    /*
        OUTPUT FORMAT:
        <FileName>: <FileContents>
        <Repeat for all files>
    */
   void displayContents(){
        for(int i=0; i<files.size(); i++){
            files[i].display();
        }
   }

   // Add new file to the filesystem
    void createNewFile(string fileName, string content){
        File newFile(fileName, content);
        files.push_back(newFile);
    }

    // Append Content to an existing file
    void appendToFile(string fileName, string contentToAppend){
        for(int i=0; i<files.size(); i++){
            if(files[i].name == fileName){
                files[i].contents += contentToAppend;
            }
        }
    }

    // Delete a file from the filesystem
    void deleteFile(string fileName){
        for(int i=0; i<files.size(); i++){
            if(files[i].name == fileName){
                files.erase(files.begin()+i);
            }
        }
    }

    // Delete last n characters from a file
    void trimFile(string fileName, int n){
        for(int i=0; i<files.size(); i++){
            if(files[i].name == fileName){
                files[i].contents = files[i].contents.substr(0, files[i].contents.size()-n);
            }
        }
    }
};

// Commit class should have ID, message and the diffs for files (changes made for each file in this commit)
class Commit{
    public:
    string ID;
    string message;
    vector<Diff> diffs;
};

class VersionControlDriver {

  /* 
    * Declare variables for:
    * Commit list
  */
    vector<Commit> commitList;
    int commitID;

  public:

  // Get content of file at a paticular commit
  string getFileContentAtCommit(string fileName, string commitID)
  {
    
  }


  // Commit current state to VCS
  Commit* addCommit(string message, FileSystem* fileSystem)
  {

  }

  // Get a File System image as of the provided Commit instance
  // i.e. get a copy of the entire file system at the point of time of this commit
  FileSystem* checkout(string commitID)
  {

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
  void status()
  {

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
  void log(int n)
  {

  }

};


int main(){
    VersionControlDriver vcd;
    FileSystem* workingDirectory = new FileSystem();
    Commit* commit1, * commit2, * commit3, * commit4;
    string contentAtCommit1, contentAtCommit2;
    FileSystem* workingDirAtC1, * workingDirAtC2, * workingDirAtC3, * workingDirAtC4;

    // TEST CASES
    
    // 1) Add a new file to Working Directory and commit to the VCS

    cout<<"1) Add a new file to Working Directory and commit to the VCS\n\n";
    workingDirectory->createNewFile("IndianStates", "Telangana, Karnataka, ");
    commit1 = vcd.addCommit("Created IndianStates File",workingDirectory);
    vcd.status();

    contentAtCommit1=vcd.getFileContentAtCommit("IndianStates",commit1->ID);
    cout<<"\n IndianStates @C1: "<<contentAtCommit1<<"\n";

    cout<<"---------------------\n\n";

    // 2) Append to 'IndianStates' file; add new files Cities and khans and commit
    workingDirectory->appendToFile("IndianStates", "Maharahtra, ");
    workingDirectory->appendToFile("IndianStates", "Punjab, ");
    workingDirectory->createNewFile("IndianCities", "Hyderabad, Bangalore, Pune, ");
    workingDirectory->createNewFile("Khans", "Shahrukh, Salman, Aamir ");
    commit2 = vcd.addCommit("Added some more states; cities and khans file added",workingDirectory);
    vcd.status();

    contentAtCommit1=vcd.getFileContentAtCommit("IndianStates",commit1->ID);
    contentAtCommit2=vcd.getFileContentAtCommit("IndianStates",commit2->ID);
    cout<<"\n IndianStates @C1: "<<contentAtCommit1<<"\n";
    cout<<"\n IndianStates @C2: "<<contentAtCommit2<<"\n";

    cout<<"---------------------\n\n";

    // 3) Delete from 'IndianStates' file; Delete khans and commit
    cout<<"Delete from 'IndianStates' file; Delete khans and commit\n\n";
    workingDirectory->trimFile("IndianCities", 5);
    workingDirectory->deleteFile("Khans");
    commit3 = vcd.addCommit("Deleted some cities; and remove khans file",workingDirectory);
    vcd.status();
    vcd.log(-1);

    cout<<"---------------------\n\n";

    // 4) Checkout scenarios  
    cout<<"4) Checkout scenarios\n\n";
    workingDirAtC1 = vcd.checkout(commit1->ID);
    cout<<"Working Directory as of "<<commit1->ID<<"\n";
    workingDirAtC1->displayContents();

    workingDirAtC2 = vcd.checkout(commit2->ID);
    cout<<"Working Directory as of "<<commit2->ID<<"\n";
    workingDirAtC2->displayContents();

    workingDirAtC3 = vcd.checkout(commit3->ID);
    cout<<"Working Directory as of "<<commit3->ID<<"\n";
    workingDirAtC3->displayContents();

    cout<<"---------------------\n\n";

    // 5) Modify Existing files, add two new files and commit
    cout<<"5) Modify Existing files, add two new files and commit\n\n";
    workingDirectory->appendToFile("IndianStates", "Rajasthan, Kerala, ");
    workingDirectory->trimFile("IndianCities", 11);
    workingDirectory->createNewFile("Countries", "India, USA, Japan, ");
    workingDirectory->createNewFile("Khans", "Zaheer, Rashid, Imran");
    commit4 = vcd.addCommit("Added to IndianStates, Deleted from IndianCities; Added two new files",workingDirectory);
    vcd.status();
    vcd.log(-1);

    workingDirAtC4 = vcd.checkout(commit4->ID);
    cout<<"Working Directory as of "<<commit4->ID<<"\n";
    workingDirAtC4->displayContents();

    cout<<"---------------------\n\n";
    return 0;
}