#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define BYTE uint8_t

char *cpname(char *source, char *destination);
int cp(char *source, char *destination);


int main(int argc, char *argv[]) {
    if (argc <= 2){
        printf("Error, incorrect usage of filer\nCorrect usage: /filer 'command' 'source' 'destination'");
        return 1;
    }
    else if (argc >= 4 && strcmp(argv[1], "cp") == 0){
        //char *newname = cpname(argv[2], argv[3]);
        int result = cp(argv[2], argv[3]); // change to newname

        /*if (newname != argv[3]){
            free(newname);
        }*/
        return result;

    } else {
        printf("Error, incorrect usage of filer\nCorrect usage: /filer 'command' 'source' 'destination'");
        return 1;
    }
}

/*
char *cpname(char *source, char *destination){
    if (strcmp(source, destination) != 0){
        return destination;
    }
    int length = strlen(destination);
    char *suffix = "-copy";
    char *newname = malloc((sizeof(char) * length) + sizeof("-copy"));

    int final_dot = 0;
    for (int i = 0; i < length; i++){
        if (destination[i] == '.') final_dot = i;
    }

    for (int j = 0; j < final_dot; j++){
        newname[j] = destination[j];
    }

    for (int k = 0; k < )


}*/

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
    while (fgets(buffer, 4096, src)){
        fprintf(dst, buffer);
    }

    return 0;
}