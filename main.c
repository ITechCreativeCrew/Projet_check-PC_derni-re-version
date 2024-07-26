#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include "file.h"

int main(int argc ,char * argv[] )
{
        Student *std;
        std=(Student *)malloc(NB_MAX*sizeof(Student));
        creatFile();
        getname(std);
        getfname(std);
        FILE *file_liste;
        file_liste=openw("presence.html");
        inserer_imageHTML("presence.html");
        fclose(file_liste);
        menu();
        interface(std);


        free(std);
        return 0;
}
