#include <stdio.h>
#include <stdbool.h>
#include <string.h>


int main(int argc, char *argv[]){
    FILE *infile = stdin;
    FILE *outfile = stdout;
    bool debug = true;
    bool encodePlus = false;
    bool encodeMinus = false;
    char *keyStart = NULL;
    
    for(int i = 1; i < argc; i = i + 1){
        if(debug){
            fprintf(stderr, "%s\n", argv[i]);
        }
        if(strncmp("-D", argv[i], 2) == 0){
            debug = false;
        }
        else if(strncmp("+D", argv[i], 2) == 0){
            debug = true;
        }
        else if(strncmp("+E", argv[i], 2) == 0){
            encodePlus = true;
            keyStart = argv[i] + 2;
        }
        else if(strncmp("-E", argv[i], 2) == 0){
            encodeMinus = true;
            keyStart = argv[i] + 2;
        }
        if(strncmp("-I", argv[i], 2) == 0){
            infile = fopen(argv[i] + 2, "r");
            if(infile == NULL){
                fprintf(stderr, "can't open the file %s", argv[i] + 2);
                return 1;
            }
        }
        if(strncmp("-O", argv[i], 2) == 0){
            outfile = fopen(argv[i] + 2, "w");
            if(infile == NULL){
                fprintf(stderr, "can't open the file %s", argv[i] + 2);
                return 1;
            }
        }
    }
    int keyLength = 0;
    int currKey = 0;
    if(encodeMinus || encodePlus){
        while (keyStart[keyLength] != '\0'){
            keyLength = keyLength + 1;
        } 
   }
    while(!feof(infile)){
        char nextChar = fgetc(infile);
        if((encodePlus || encodeMinus) && keyLength > 0){
            if(!(nextChar < '0' || (nextChar > '9' && nextChar < 'A') || nextChar > 'Z')){
                currKey = currKey % keyLength;
                int valueToAdd = keyStart[currKey] - '0';
                if(encodeMinus){
                    valueToAdd = -valueToAdd;
                }
                if(nextChar >= '0' && nextChar <= '9'){
                    nextChar = ((nextChar - '0') + valueToAdd) % 10;
                    if(nextChar < 0){
                        nextChar = nextChar + 10;
                    }
                    nextChar = nextChar + '0';
                }
                else if(nextChar >= 'A' && nextChar <= 'Z'){
                    nextChar = ((nextChar - 'A') + valueToAdd) % 26;
                    if(nextChar < 0){
                        nextChar = nextChar + 26;
                    }
                    nextChar = nextChar + 'A';
                }
            }
        }
        currKey = currKey + 1;
        fputc(nextChar, outfile);
    }
    fclose(infile);
    return 0;
}