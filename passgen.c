#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stdlib.h>

typedef enum{
    UPPER,
    LOWER,
    NUMBER,
    MIXED,
    SPECIAL,
} Passtype;

/* Password Gen in C */
int argHandler(int, char**, Passtype);
int genPass(int, int, Passtype);

int main(int argc, char *argv[]){
    Passtype type;
    // initalize pseudorandom seed based on current time
    srand(time(0));

    return 0;
}

int argHandler(int argc, char *argv[], Passtype type){
    if(argc > 4){
        printf("Too many arguments");
        return 1;
    
    // this handles flags passed into exec
    } else if(argc == 3){
        // Must convert character array (strings to integers)
        /*int charcount = argv[2];
        int passcount = argv[3];*/
        switch(*argv[1]){
            case 'u':
                printf("Uppercase selected\n");
                type = UPPER;
                break;

            case 'l':
                printf("Lowercase selected\n");
                type = LOWER;
                break;

            case 'n':
                printf("Number selected\n");
                type = NUMBER;
                break;

            case 'm':
                printf("Mixed selected\n");
                type = MIXED;
                break;
                genPass(passcount, charcount, type);

            case 's':
                printf("Special selected\n");
                type = SPECIAL;
                break;

            default:
                printf("Error: not a flag, try [passgen h] for help\n");
            }
    } else {
        printf("Error: did not use integers to specify char and pass counts\n");
        return 0;
    }  
}


int genPass(int passcount, int charcount, Passtype type){
    // constant for ascii table vals
    const int RANDMAX = 128;
    int r = rand();
    while(passcount > 0){
        char pass[(charcount*sizeof(int))+1];
        for(int i = 0; i < charcount; i++){
            // match types with respective logic
            if(type == MIXED){
                // checks if rand is out of ascii scope and randomizes until it isnt
                while(128 == (r % RANDMAX) && (r % RANDMAX) < 33){
                    r = rand();
                }
                // passes value when rand is within scope
                if(127 > (r % RANDMAX) && (r % RANDMAX) >= 33){
                    pass[i] = r;
                }
            } else if(type == UPPER){
                // checks if rand is out of ascii upper char scope
                while(90 < (r % RANDMAX) && (r % RANDMAX) < 65){
                    r = rand();
                }
                // pass value
                if(90 >= (r % RANDMAX) && (r % RANDMAX) >= 65){
                    pass[i] = r;
                }
            } else if(type == LOWER){
                //Fill logic here, 2 more to go!
            }
            printf("%c", pass[i]); 
        }
        // seperate passwords
        printf("\n");
        passcount--;
    }
    return 0;
}