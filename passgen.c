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
    // initalize pseudorandom seed based on current time with added variance (clock)
    srand(time(0) + clock());
    argHandler(argc, argv, type);

    return 0;
}

int argHandler(int argc, char *argv[], Passtype type){
    if(argc > 4){
        printf("Too many arguments, try using h for help\n");
        return 1;
    
    // this handles flags passed into exec
    } else if(argc == 2) {
        switch(*argv[1]){
            case 'h':
            printf("Usage:\tpassgen [type (u, l, n, m, s)] [password count integer] [character count integer]\n\t type flags are: upper, lower, number, mixed, special\n");
            break;

            default:
            printf("Error: did not use type flags and integers to specify char and pass counts use [passgen h] for help\n");
            return 1;
        }
    }
    else if(argc == 4){
        // Must convert character array (strings to integers)
        int passcount = atoi(argv[2]);
        int charcount = atoi(argv[3]);
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

            case 's':
                printf("Special selected\n");
                type = SPECIAL;
                break;

            default:
                printf("Error: not a flag, try [passgen h] for help\n");
                return 1;
            }
        genPass(passcount, charcount, type);
    } else {
        printf("Error: did not use type flags and integers to specify char and pass counts use [passgen h] for help\n");
        return 1;
    }
    return 0;
}


int genPass(int passcount, int charcount, Passtype type){
    // constant for ascii table vals
    const int RANDMAX = 128;
    while(passcount > 0){
        char pass[charcount+1];
        for(int i = 0; i < charcount; i++){
            int r = rand();
            // match types with respective logic
            if(type == MIXED){
                // checks if rand is out of ascii scope and randomizes until it isnt
                while(128 == (r % RANDMAX) || (r % RANDMAX) < 33){
                    r = rand();
                }
                // passes value when rand is within scope
                if(127 > (r % RANDMAX) && (r % RANDMAX) >= 33){
                    pass[i] = r % RANDMAX;
                    r = rand();
                }
            } else if(type == UPPER){
                // checks if rand is out of ascii upper char scope
                while(90 < (r % RANDMAX) || (r % RANDMAX) < 65){
                    r = rand();
                }
                // pass value
                if(90 >= (r % RANDMAX) && (r % RANDMAX) >= 65){
                    pass[i] = r % RANDMAX;
                }
            } else if(type == LOWER){
                while(122 < (r % RANDMAX) || (r % RANDMAX) < 97){
                    r = rand();
                } 
                if(122 >= (r % RANDMAX) && (r % RANDMAX) >= 97){
                    pass[i] = r % RANDMAX;
                }
            } else if(type == NUMBER){
                while(57 < (r % RANDMAX) || (r % RANDMAX) < 48){
                    r = rand();
                }
                if(57 >= (r % RANDMAX) && (r % RANDMAX) >= 48){
                    pass[i] = r % RANDMAX;
                }
            } else if(type == SPECIAL){
                char specialChars[] = "!@#$%^&*()-_=+[{]};:'\",<.>/?";
                int specialCharCount = strlen(specialChars);

                r = rand() % specialCharCount;
                pass[i] = specialChars[r];
                } else {
                printf("Aborted due to error\n");
                return 1;
            }
            printf("%c", pass[i]); 
        }
         // seperate passwords
        printf("\n");
        passcount--;   
    }
    return 0;
}
