
#include <stdlib.h>
#include "save.h"

int main(){
    Data data ;
    charge_file(&data);

    display_data(data);

    save_data(&data);

    display_data(data);

    free_data(&data);
    exit(EXIT_SUCCESS);
}