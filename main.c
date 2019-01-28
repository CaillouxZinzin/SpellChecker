#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#include <string.h>

int main()
{

   /*int c;
    DicoAL dictio, pref;
    Mot mot;

    mot=creerMot();
    char * str="\0";
    dictio=initDico2(dictio, mot);
    afficherDico2(dictio, str, -1);


    mot=creerMot();
    dictio=ajoutMot2(dictio, mot);
    afficherDico2(dictio, str, -1);

    mot=creerMot();
    dictio=ajoutMot2(dictio, mot);
    afficherDico2(dictio, str, -1);

    mot=creerMot();
    dictio=ajoutMot2(dictio, mot);
    afficherDico2(dictio, str, -1);

    mot=creerMot();
    dictio=ajoutMot2(dictio, mot);
    afficherDico2(dictio, str, -1);

    //mot=creerMot();
    //dictio=ajoutMot2(dictio, mot);
    //afficherDico2(dictio, str, -1);

    suggestionMot2(dictio, "bagare", 3);*/



    FILE * dictionnaire;
    FILE * file;
    FILE * temp;
    char c;
    int sucess;
    int choix_action=0, choix_arbre=-1, choix, i=0;
    char string[50];


    dictionnaire=fopen("dictionaire.txt", "r+");
    if (dictionnaire==NULL)
    {
        perror("dictionnaire introuvable \n");
        exit(0);
    }

    while (choix_arbre!=1 && choix_arbre!=2)
    {
        printf ("\n Quel type d'arbre voulez vous utilisez? \n 1- Dico ABR \n 2- Dico AL \n");
        scanf("%d", &choix_arbre);
    }
    if (choix_arbre==1)
    {

        DicoABR * arbre;
        arbre=initDico();
        while (!ferror(dictionnaire) && !feof(dictionnaire))
        {
        i=0;
            do
           {
               c=fgetc(dictionnaire);
               string[i]=c;
               i++;
           }
           while (c!= '\n' && c != EOF);
           string[i-1]='\0';
           i=0;


            if (strcmp(string, "\n")!=0)
                ajoutMot(arbre, string);

        }
        while (choix_action!=4)
            {
                printf("\n Que voulez vous faire? \n 1-Afficher une partie du dictionnaire? \n 2-Verimot \n 3-??? \n 4-Quitter \n");
                scanf("%d", &choix_action);
                switch (choix_action)
                {
                    case 1 :
                        printf("Quelle partie de l'arbre voulez-vous affichez? \n 1-Depuis le début 2-A partir d'un mot \n");
                            scanf ("%d", &choix);
                            if (choix==1)
                            {
                                printf("\n Voici le dictionnaire : \n");
                                affiche_infixe(arbre->racine, " ");
                            }
                            else if (choix==2)
                            {
                                printf("A partir de quel mot? \n");
                                scanf("%s", string);
                                printf("\n Voici le dictionnaire : \n");
                                affiche_infixe(arbre->racine, string);
                            }
                        break;
                    case 2 :
                        file=fopen("file.txt", "r+");
                        if (file==NULL)
                        {
                            perror("Fichier file.txt introuvable");
                            exit(0);
                        }
                        temp=fopen("temp.txt", "w+");
                        if (file==NULL)
                        {
                            perror("Ouverture du fichier temp impossible");
                            exit(0);
                        }
                        fputc('\n', dictionnaire);
                        while(!ferror(file) && !feof(file))
                        {
                            do
                            {
                                c= fgetc(file);
                                string[i++]=c;
                            }
                            while (c!= '\n' && c != EOF);
                            string[i-1]='\0';
                            i=0;
                           printf("On travaille avec le mot: %s \n", string);

                            if (rechercheMot(arbre, string)!=NULL)
                            {
                                fputs(string, temp);
                                fputc('\n', temp);
                                printf("Ce mot existe dans le dictionnaire.\n");
                            }
                            else
                            {
                                printf(" Le mot n'existe pas dans le dictionaire, que voulez vous faire? \n 1- Le remplacer par un mot du dico 2-Le rajouter dans le dictionnaire \n");
                                scanf("%d", &choix);
                                if (choix==1)
                                {
                                     printf("Par quel mot voulez-vous le remplacer? \n");
                                     suggestionMot(arbre, string, 3);
                                     scanf("%s", string);
                                     fputs(string, temp);
                                     fputc('\n',temp);
                                }
                                if (choix==2)
                                {
                                    ajoutMot(arbre, string);
                                    fputs(string, dictionnaire);
                                    fputc('\n', dictionnaire);
                                    fputs(string, temp);
                                    fputc('\n', temp);
                                }

                            }

                        }
                        fclose(temp);
                        fclose(file);
                        remove("file.txt");
                        rename("temp.txt", "file.txt");
                        break;
                    case 3 :
                        break;
                    case 4 :
                        fclose(dictionnaire);
                        break;
                    default: printf("Demande inconnue \n");
                }
            }
    }
    else
    {
        DicoAL * dico;
        Mot mot=lireMot("\0");
        dico=initDico2(dico, mot);
        while (!ferror(dictionnaire) && !feof(dictionnaire))
        {
        i=0;
            do
           {
               c=fgetc(dictionnaire);
               string[i]=c;
               i++;
           }
           while (c!= '\n' && c != EOF);
           string[i-1]='\0';
           i=0;
            mot=lireMot(string);

            if (strcmp(string, "\n")!=0)
                ajoutMot2(dico, mot);

        }
       while (choix_action!=4)
            {
                printf("\n Que voulez vous faire? \n 1-Afficher une partie du dictionnaire? \n 2-??? \n 3-??? \n 4-Quitter \n");
                scanf("%d", &choix_action);
                switch (choix_action)
                {
                    case 1 :  printf("Quelle partie de l'arbre voulez-vous affichez? \n 1-Depuis le début 2-A partir d'un mot \n");
                                scanf ("%d", &choix);
                                if (choix==1)
                                {
                                    printf("\n Voici le dictionnaire : \n");
                                    afficherDico2(dico, "\0", " ", -1);
                                }
                                else if (choix==2)
                                {
                                    printf("A partir de quel mot? \n");
                                    scanf("%s", string);
                                    printf("\n Voici le dictionnaire : \n");
                                    afficherDico2(dico,"\0", string , -1);
                                }
                        break;
                    case 2 :
                        file=fopen("file.txt", "r+");
                        if (file==NULL)
                        {
                            perror("Fichier file.txt introuvable");
                            exit(0);
                        }
                        temp=fopen("temp.txt", "w+");
                        if (file==NULL)
                        {
                            perror("Ouverture du fichier temp impossible");
                            exit(0);
                        }
                        fputc('\n', dictionnaire);
                        while(!ferror(file) && !feof(file))
                        {
                            do
                            {
                                c= fgetc(file);
                                string[i++]=c;
                            }
                            while (c!= '\n' && c != EOF);
                            string[i-1]='\0';
                            i=0;
                            if (string!=" ")
                            {

                               printf("On travaille avec le mot: %s \n", string);
                               Mot mot=lireMot(string);
                                if (rechercheMot2(dico, mot)!=NULL)
                                {
                                    fputs(string, temp);
                                    fputc('\n', temp);
                                    printf("Ce mot existe dans le dictionnaire.\n");
                                }
                                else
                                {
                                    printf(" Le mot n'existe pas dans le dictionaire, que voulez vous faire? \n 1- Le remplacer par un mot du dico 2-Le rajouter dans le dictionnaire \n");
                                    scanf("%d", &choix);
                                    if (choix==1)
                                    {
                                         printf("Par quel mot voulez-vous le remplacer? \n");
                                         suggestionMot2(dico, string, 3);
                                         scanf("%s", string);
                                         fputs(string, temp);
                                         fputc('\n',temp);
                                    }
                                    if (choix==2)
                                    {
                                        ajoutMot(dico, mot);
                                        fputs(string, dictionnaire);
                                        fputc('\n', dictionnaire);
                                        fputs(string, temp);
                                        fputc('\n', temp);
                                    }
                                }
                              }

                            }
                        fclose(temp);
                        fclose(file);
                        remove("file.txt");
                        rename("temp.txt", "file.txt");
                        break;
                    case 3 :
                        break;
                    case 4 :
                        break;
                    default: printf("Demande inconnue \n");
                }
            }
    }
    return 0;
}
