/**
* \file save.c
* \brief Ensemble de fonction qui s'occupe de la sauvegarde d'une partie.
* \details c'est dans ces fonctions que l'on met en place la sauvegarde mais aussi le chargement d'une partie.
* \author Vallet Guillaume
*/

#include "commun.h"
#include "save.h"

/**
* \brief fonction qui sauvegarde la progression du joueur.
*
* \details Dans cette fonction on sauvegarde plusieurs information dans un fichier texte. On sauvegarde l'argent du joueur, le n° du jour qu'il vient de finir,
* le nombre d'action achetées et des actions qui sont achetées et ensuite on sauvegarde leur emplacement dans la barre des actions.
*  
*/
void sauvegarde(int money, int jour, action_t * liste_action[], action_t * action_equipe[])
{
    
    FILE * save;
    int i = 0;

    int nb_action = 0;
    while(liste_action[i]){
        if(liste_action[i]->statut)
            nb_action++;
        i++;
    }
    i = 0;
    //Sauvegarde de la money et du jour
    save = fopen("save.txt","w"); 
    fprintf(save,"%i\n%i\n",money,jour);
    //Sauvegarde du nombre d'action achetées
    fprintf(save,"%i ",nb_action);
    //Sauvegarde de toute les actions achetées
    while(i < nb_action)
    {
        if(liste_action[i]->statut == true)
            fprintf(save,"%i ",liste_action[i]->id);
        i++;

    }
    fprintf(save,"\n");

    //Sauvegarde des 4 actions équipées (Si vide, écris -1)
    i = 0;
    while(i < 4)
    {

        fprintf(save,"%i ",action_equipe[i]->id);
        i++; 

    }
    fprintf(save,"\n");
    fclose(save);
}

/**
* \brief fonction qui charge une anciènne sauvegarde.
*
* \details Dans cette fonction on charge plusieurs information à partir d'un fichier texte. On charge l'argent du joueur, le n° du jour qu'il vient de finir,
* le nombre d'action achetées et des actions qui sont achetées et ensuite on charge leur emplacement dans la barre des actions.
*  
*/
int charger(int * money, int * jour,  action_t * liste_action[], action_t * action_equipe[])
{

    FILE * save;
    int i = 0;
    //Billy le dieu :OOOOO
    int billy;
    int nb_action;
    //Ouvre le fichier en lecture, si il n'existe pas renvoie une erreur
    if(save = fopen("save.txt","r"))
    {

        //Recupere la money, le jour, et le nombre d'action achetées
        fscanf(save,"%i",money);
        if((*money) != -1){ 

            fscanf(save,"%i",jour);
            fscanf(save,"%i",&nb_action);

            //Recupere les id des actions achetées
            while(i < nb_action){

                fscanf(save,"%i",&billy); //On prend l'adresse de billy pour mettre un truc dedans
                liste_action[billy]->statut = true; 
                i++;
            }
            i = 0;

            //Recupere les id des actions équipées
            while(i < 4){

                fscanf(save,"%i",&billy);
                action_equipe[i]= liste_action[billy];
                i++;
            }

            return 1;
        }
        else{

            *money = 0;
            return 0;

        }

    }
    else return 0;
    fclose(save);
}
//Test
/*int main(){

    int jour;
    int money;
    int nb_action;
    int test_a[6] = {1,2,3,5,7,9};
    int test_e[4] = {0,1,2,8};
    int action_a[50];
    int action_e[4];
    printf("Coucou");
    sauvegarde(5,1,6,test_a,test_e);
    charger(&money, &jour, &nb_action, action_a, action_e);

    printf("%i\n%i\n",money, jour);
    for(int i = 0; i < nb_action; i++){ //Billy > ALL

        printf("%i ", action_a[i]);

    }
    printf("\n");
    for(int i = 0; i < 4; i++){

        printf("%i ",action_e[i]);

    }
    printf("\n");
    return 0;
}*/