#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>

char *pFilename = NULL;
char *pWritestr = NULL;
FILE *pFile = NULL;

void close_all() {
    // Close the file if it is open
    if(fclose(pFile) != 0) {
        syslog(LOG_ERR, "Failed to close file %s", pFilename);
    }
    // Free the allocated memory
    free(pFilename);
    free(pWritestr);
    // Close the syslog
    closelog();
}

int main(int argc, char *argv[]) {

    openlog("writer", LOG_PID | LOG_CONS, LOG_USER);
    if (argc != 3) {  // 2 arguments and the file itself
        syslog(LOG_ERR, "Usage: %s <filename> <writestr>", argv[0]);
        return 1;
    }

    // duplicate to local variables
    // strdup allocates memory for the string and copies it
    pFilename = strdup(argv[1]);
    pWritestr = strdup(argv[2]);

    if (!pFilename || !pWritestr) {
        syslog(LOG_ERR, "Memory allocation failed");
        close_all();
        return 1;
    }

    // Try to open the file for writing
    pFile = fopen(pFilename, "w");
    if (!pFile) {
        syslog(LOG_ERR, "Failed to open file %s for writing", pFilename);
        close_all();
        return 1;
    }

    // Write the string to the file
    if (fprintf(pFile, "%s", pWritestr) < 0) {
        syslog(LOG_ERR, "Failed to write to file %s", pFilename);
        close_all();
        return 1;
    }

    // Log success
    syslog(LOG_DEBUG, "Writing %s to %s", pWritestr, pFilename);
        close_all();
    return 0;
}