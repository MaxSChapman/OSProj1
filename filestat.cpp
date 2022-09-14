#include <iostream>
#include <sys/stat.h>
#include <errno.h>
#include <pwd.h>
#include <ctime>

using namespace std;
int main(int argc, char** argv) {

    //Check for valid CL inputs
    if (argc <= 1) {
        fprintf(stderr, "Usage: %s <filepath>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    struct stat buffer;
    errno = 0;

    //Get File Stats
    if (stat(argv[1], &buffer) != 0) {
        std::cerr << "Error: " << strerror(errno) << '\n';
        exit(EXIT_FAILURE);
    }

    //Format and print File Stats

    //I-node
    printf("I-node number:            %u\n", buffer.st_ino);

    //File Type
    unsigned type = buffer.st_mode;
    if (S_ISREG(type)) {
        printf("File Type:                %s\n", "Regular File");
    } else if (S_ISDIR(type)) {
        printf("File Type:                %s\n", "Directory");
    } else if (S_ISCHR(type)) {
        printf("File Type:                %s\n", "Character Device");
    } else if (S_ISBLK(type)) {
        printf("File Type:                %s\n", "Block Device");
    } else if (S_ISFIFO(type)) {
        printf("File Type:                %s\n", "Fifo Pipe");
    } else if (S_ISLNK(type)) {
        printf("File Type:                %s\n", "Symbolic Link");
    } else if (S_ISSOCK(type)) {
        printf("File Type:                %s\n", "Socket");
    } else {
        printf("File Type:                %s\n", "Unrecognized File Type");
    }

    //Name
    struct passwd *pws;
    pws = getpwuid(buffer.st_uid);
    printf("User Name:                %s\n", pws->pw_name);

    //File Size
    printf("Total Size:               %u bytes\n", buffer.st_size);

    //Creation time
    char* created = ctime(&buffer.st_mtime);
    printf("Date Last Modified:       %s\n", created);

    return 0;
}
