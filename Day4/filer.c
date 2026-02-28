#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define BYTE uint8_t

int cp(char *source, char *destination);
int move(char *source, char * destination);


int main(int argc, char *argv[]) {
    if (argc <= 2){
        printf("Error, incorrect usage of filer\nCorrect usage: /filer 'command' 'source' 'destination'");
        return 1;
    }
    else if (argc >= 4 && strcmp(argv[1], "cp") == 0){
        int result = cp(argv[2], argv[3]);
        return result;
    } else if (argc >= 4 && strcmp(argv[1], "mv") == 0){
        int result = move(argv[2], argv[3]);
        return result;
    }
    else {
        printf("Error, incorrect usage of filer\nCorrect usage: /filer 'command' 'source' 'destination'");
        return 1;
    }
    return 0;
}

int cp(char *source, char *destination){
    FILE *src;
    FILE *dst;
    

    src = fopen(source, "rb");
    if (!src){
        printf("Couldn't open source\n");
        return 1;
    }
    dst = fopen(destination, "wb");
    if (!dst){
        printf("Couldn't create copy\n");
        fclose(src);
        return 1;
    }
    BYTE buffer[4096];
    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, sizeof(buffer), src) > 0)){
        fwrite(buffer, 1 , bytesRead, dst);
    }

    fclose(src);
    fclose(dst);

    return 0;
}

int move(char *source, char * destination){
    if (rename(source, destination) == 0) {
        printf("File moved successfully.\n");
    } else {
        perror("Error moving file"); 
    }
    return 0;
}