#include <stdio.h>
#include "header/struct/Record.h"
#include "header/struct/AssociativeArray.h"

void ajout_client(AARAY* tableau){

char tab[7][];
RECORD* tmp;

fgets(tab,7,stdin);

aapush(tableau,tab[0], tab[1],*record);

}



int main() {
    printf("Hello World\n");
    return 0;
}
