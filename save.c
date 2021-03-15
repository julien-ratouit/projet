#include <stdio.h>
#include <stdlib.h>

//Sauvegarde la partie a la fin de la journée
void sauvegarde(int money, int jour,int nb_action, int action_achete[], int action_equipe[]){
    
    FILE * save;
    int i = 0;

    //Sauvegarde de la money et du jour
    save = fopen("save.txt","w"); 
    fprintf(save,"%i\n%i\n",money,jour);

    //Sauvegarde du nombre d'action achetées
    fprintf(save,"%i ",nb_action);

    //Sauvegarde de toute les actions achetées
    while(i < nb_action){

        fprintf(save,"%i ",action_achete[i]);
        i++;

    }
    fprintf(save,"\n");

    //Sauvegarde des 4 actions équipées (Si vide, écris -1)
    i = 0;
    while(i < 4){

        if(action_equipe[i]) fprintf(save,"%i ",action_equipe[i]);
        else fprintf(save,"-1 ");

    }
    fprintf(save,"\n");
    fclose(save);
}

//Charge les données de la partie précédente
int charger(int * money, int * jour, int * nb_action, int action_achete[], int action_equipe[]){

    FILE * save;
    int i = 0;

    //Ouvre le fichier en lecture, si il n'existe pas renvoie une erreur
    if(save = fopen("save.txt","r")){

        //Recupere la money, le jour, et le nombre d'action achetées
        fscanf(save,"%i",money);
        fscanf(save,"%i",jour);
        fscanf(save,"%i",nb_action);

        //Recupere les id des actions achetées
        while(i < (*nb_action)){

            fscanf(save,"%i", action_achete + i);

        }
        i = 0;

        //Recupere les id des actions équipées
        while(i < 4){

            fscanf(save,"%i", action_achete + i);

        }

        return 1;

    }
    else return 0;
    fclose(save);
}

int main(){

    int jour;
    int money;
    int nb_action;
    int test_a[6] = {1,2,3,5,7,9};
    int test_e[4] = {0,1,2,8};
    int action_a[50];
    int action_e[4];

    sauvegarde(5,1,6,test_a,test_e);
    charger(&money, &jour, &nb_action, action_a, action_e);

    printf("%i\n%i\n",money, jour);
    for(int i = 0; action_a[i]; i++){

        printf("%i ", action_a[i]);

    }
    printf("\n");
    for(int i = 0; i < 4; i++){

        printf("%i ",action_e[i]);

    }
    printf("\n");
    return 0;
}