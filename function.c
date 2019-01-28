#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"


//PARTIE 1//

//QUESTION 2//
DicoABR * initDico()
{
    DicoABR *new=malloc(sizeof(DicoABR));
    new->racine=NULL;
    new->n=0;
    //printf("Votre dictionnaire a bien était crée\n");
    return new;
}

int ajoutMot(DicoABR * A, char *s)
{
    if (s=="")
    {
        return -1;
    }
    if (A==NULL)
    {
        printf("arbre null");
        return -1;
    }
    Node * new=malloc(sizeof(Node));
    strcpy(new->key, s);

    Node * y=NULL;
    Node * temp=A->racine;

    while (temp!=NULL)
    {
        y=temp;
        if (strcmp(temp->key, s)<0)
        {
            temp=temp->droit;
        }
        else if (strcmp(temp->key, s)>0)
        {
            temp=temp->gauche;
        }
        else if (strcmp(temp->key, s)==0)
        {
            free(new);
            printf("\n L'élement existe déjà le dictionnaire \n");
            return -1;
        }

    }
    if (y==NULL)
    {

        A->racine=new;
        new->gauche=NULL;
        new->droit=NULL;
        new->pere=NULL;
        A->n++;
        return 0;
    }
    else
    {
        if (strcmp(y->key, s)<0)
        {

            y->droit=new;
            new->gauche=NULL;
            new->droit=NULL;
            new->pere=y;
            A->n++;
            return 0;
        }
        else if (strcmp(y->key, s)>0)
        {

            y->gauche=new;
            new->gauche=NULL;
            new->droit=NULL;
            new->pere=y;
            A->n++;
            return 0;
        }
        else if (strcmp(y->key, s)==0)
        {
            free(new);
            printf("\n L'élement existe dans le dictionnaire \n");
            return -1;
        }
    }

}

void affiche_infixe(Node *r, char * s)
{
    if (r==NULL)
        return;
    else
    {
    affiche_infixe(r->gauche, s);
    if (strcmp(r->key, s)>=0)
        printf("%s \n", r->key);
    affiche_infixe(r->droit, s);
    }
}

Node * rechercheMot(DicoABR *A, char *s)
{
 Node * temp=A->racine;

    while (temp!=NULL && (strcmp(temp->key, s)!=0))
    {

        if (strcmp(temp->key, s)<0)
        {
            temp=temp->droit;
        }
        else if (strcmp(temp->key, s)>0)
        {
            temp=temp->gauche;
        }

    }
    if (temp==NULL)
    {

        return NULL;
    }
    else
    {
        return temp;
    }

}

int supprimeMot(DicoABR* A, char * s)
{
    Node * noeud=rechercheMot(A, s);
    if (noeud==NULL)
    {
        return -1;
    }
    else
    {
        Node * droit=noeud->droit;
        Node * gauche=noeud->gauche;
        if (gauche==NULL && droit==NULL)
        {
            if (strcmp(noeud->pere->key, noeud->key)<0)
            {
                noeud->pere->droit=NULL;
            }
            else
            {
                noeud->pere->gauche=NULL;
            }
            free(noeud);
            return 0;
        }

        else if (gauche!=NULL && droit!=NULL)
        {
            Node * temp=droit ;
            while (temp->gauche!=NULL)
            {
                temp=temp->gauche;
            }

            if (temp->droit!=NULL)
            {
                temp->pere->gauche=temp->droit;
            }
            else
                temp->pere->gauche=NULL;
            if (strcmp(noeud->pere->key, noeud->key)<0)
            {
                noeud->pere->droit=temp;

            }
            else
            {
                noeud->pere->gauche=temp;
            }
            temp->pere=noeud->pere;
            temp->droit=droit;
            temp->gauche=gauche;


            if (droit!=temp)
                droit->pere=temp;
            else
                temp->droit=NULL;

            gauche->pere=temp;

            free(noeud);

            return 0;
        }
        else if (gauche!=NULL || droit!=NULL)
        {
            if(droit==NULL)
            {
                gauche->pere=noeud->pere;
                if (strcmp(noeud->pere->key, noeud->key)<0)
                {
                    noeud->pere->droit=gauche;
                }
                else
                {
                    noeud->pere->gauche=gauche;
                }
                free(noeud);
                return 0;
            }
            else
            {
               droit->pere=noeud->pere;
                if (strcmp(noeud->pere->key, noeud->key)<0)
                {
                    noeud->pere->droit=droit;
                }
                else
                {
                    noeud->pere->gauche=droit;
                }
                free(noeud);
                return 0;
            }
        }
    }
}

//QUESTION 3//

void suggestionMot (DicoABR * A,char * string, int k)
{
    liste_sug * l=malloc(sizeof(liste_sug));
    l->tete=NULL;
    l->taille=0;
    l=suggestionMotRec (A, A->racine, string, k, l);
    afficher_liste (l);
    cellulel * temp=l->tete;
    cellulel * temp2=l->tete->suivant;
    while (temp!=NULL)
    {
        temp2=temp->suivant;
        free(temp);
        temp=temp2;
    }
    free(l);
}

liste_sug* suggestionMotRec (DicoABR * A, Node * n,char * string, int k, liste_sug * l)
{
    if (n==NULL)
    {
        return l;

    }
    else
    {


            l=suggestionMotRec(A, n->gauche, string, k, l);
            int i=0, nb=0;
            while (n->key[i]==string[i] && nb<strlen(string))
            {
                i++;
                nb++;
            }

            l=insererliste(n, k, nb, l);

            l=suggestionMotRec(A, n->droit, string, k, l);
            return l;
    }

}

liste_sug * insererliste(Node * n, int k, int nb, liste_sug * l)
{

if (n->key=="")
{
    return l;
}
    if (l->taille>=k)
    {
        l=insererlistepleine( n, k, nb, l);
        return l;
    }

    else
    {

        cellulel * temp=l->tete;
        cellulel * temp2=NULL;

        if (temp==NULL)
        {
            cellulel * new=malloc(sizeof(cellulel));
            new->noeud=n;
            new->suivant=NULL;
            new->nbcom=nb;
            l->tete=new;
            l->taille=1;
           // printf("\nListe actuelle: \n");
           // afficher_liste(l);
            return l;
        }

        while(temp->suivant!=NULL && temp->nbcom<=nb)
        {
            //printf("\nParcours de la liste pour inse\n");
            temp2=temp;
            temp=temp->suivant;
        }
        if (temp==l->tete)
        {
            //printf("\n Insertion au niveau de la  tete \n");
            cellulel * new=malloc(sizeof(cellulel));
            new->noeud=n;
            if(temp->nbcom<=nb)
            {
                if (temp->nbcom==nb)
                {
                    if (strcmp(temp->noeud->key, n->key)>0)
                    {
                        new->suivant=NULL;
                        new->nbcom=nb;
                        temp->suivant=new;
                        //printf ("Element %s, inserer car plus proche que %s\n", n->key, temp->noeud->key);
                    }

                    else
                    {
                        l->tete=new;
                        new->suivant=temp;
                        new->nbcom=nb;
                        //printf ("Element %s avant %s, inserer car moins proche que %s\n", n->key, temp->noeud->key,temp->noeud->key);
                    }
                }
                else
                {
                    new->suivant=temp->suivant;
                    temp->suivant=new;
                    new->nbcom=nb;
                    //new->suivant=NULL;
                }

            }
            else
            {
                l->tete=new;
                new->suivant=temp;
                new->nbcom=nb;
            }
        l->taille+= 1;
        //printf("liste actuelle: \n");
        //afficher_liste(l);
        return l;
        }
        if (temp->suivant==NULL && temp->nbcom<=nb)
        {

            if (temp->nbcom<nb)
            {
                cellulel * new=malloc(sizeof(cellulel));
                new->noeud=n;
                new->suivant=NULL;
                new->nbcom=nb;
                temp->suivant=new;
                //printf ("Element %s, inserer car plus proche que %s \n", n->key, temp->noeud->key);
                //printf("taille maintenant %d\n", l->taille);
            }
            else if (temp->nbcom==nb)
            {

                if (strcmp(temp->noeud->key, n->key)>0)
                {
                    cellulel * new=malloc(sizeof(cellulel));
                    new->noeud=n;
                    new->suivant=NULL;
                    new->nbcom=nb;
                    temp->suivant=new;
                    //printf ("Element %s, inserer car plus proche que %s\n", n->key, temp->noeud->key);
                }

                else
                {
                    cellulel * newWR=malloc(sizeof(cellulel));
                    newWR->noeud=n;
                    newWR->nbcom=nb;
                    newWR->suivant=temp;
                    temp2->suivant=newWR;
                    //printf ("Element %s avant %s, inserer car moins proche que %s\n", n->key, temp->noeud->key,temp->noeud->key);
                }
                //;
            }
            //printf("\nlongueur +1 avec %s de %d\n", n->key, l->taille);
            l->taille+= 1;
            //printf("liste actuelle: \n");
            //afficher_liste(l);
            return l;
        }
        else if (temp->nbcom>nb)
        {
            cellulel * new=malloc(sizeof(cellulel));
            new->noeud=n;
            new->suivant=temp;
            new->nbcom=nb;
            temp2->suivant=new;
            l->taille=l->taille+1;
            //printf ("Element %s avant %s, inserer car moins proche que %s\n", n->key, temp->noeud->key,temp->noeud->key);
            //afficher_liste(l);
        return l;
        }
        return l;

    }
}

liste_sug * insererlistepleine(Node * n, int k, int nb, liste_sug * l)
{
   cellulel * temp=l->tete;
    if (nb<l->tete->nbcom)
    {

        //printf("\n NB COMMUN AVEC LA TETE: %d \n", l->tete->nbcom);
        //printf("\n Pas d'insertion car %s est plus petit que la tête", n->key);
        //printf("\nListe actuelle: \n");
        //afficher_liste(l);
        return l;
    }
    else if (nb>l->tete->nbcom)
    {

        l->tete=temp->suivant;
        l->taille=l->taille-1;
        free(temp);
        l=insererliste(n,k,nb,l);
        return l;
    }
    else if (nb==l->tete->nbcom)
    {
        if (strcmp(n->key, temp->noeud->key)<0)
        {
        l->tete=temp->suivant;
        l->taille=l->taille-1;
        //printf("%d", l->taille);
        free(temp);
        l=insererliste(n,k,nb,l);
        return l;
        }
        //printf("\n Pas d'insertion car %s est plus petit que la tête", n->key);
        //printf("\nListe actuelle: \n");
       // afficher_liste(l);
        return l;
    }

}

void afficher_liste (liste_sug * l)
{
    cellulel * temp=l->tete;
    printf("taille: %d", l->taille);
    while (temp!=NULL)
    {
        printf("\n%s \n", temp->noeud->key);
        temp=temp->suivant;
    }
}

/*FONCTIONS PARTIE 2*/


DicoAL initDico2(DicoAL dico, Mot mot)
{
        Mot temp=mot;
        char c;

        c=mot->cara;
        Cellule * nouvo=malloc(sizeof(Cellule));
        nouvo->cara=c;
        nouvo->succ=NULL;
        nouvo->alt=NULL;
        dico=nouvo;
        while (nouvo->cara!='$')
        {
            temp=temp->suivant;
            c=temp->cara;
            Cellule * nouvoS=malloc(sizeof(Cellule));
            nouvoS->succ=NULL;
            nouvoS->alt=NULL;
            nouvoS->cara=c;
            nouvo->succ=nouvoS;
            nouvo=nouvoS;

        }
    return dico;

}

Mot creerMot()
{
    Mot mot=malloc(sizeof(Mot));
    Car * temp;
    temp=mot;
    char c, d;
    scanf("%c", &c);
    scanf("%c", &d);
    temp->cara=c;
    temp->suivant=NULL;
    while (c!='$')
    {
        Car * temp2=malloc(sizeof(Car));
        scanf("%c", &c);
        scanf("%c", &d);
        temp2->cara=c;
        temp2->suivant=NULL;
        temp->suivant=temp2;
        temp=temp2;

    }
    return mot;
}

DicoAL prefixeMot(DicoAL dico, Mot mot)
{

        Mot temp=mot;

        Cellule * tempdico=dico;
        Cellule * tempdico2=NULL;
        while (tempdico!=NULL && temp!=NULL)
        {
            if (temp->cara!=tempdico->cara)
            {

                tempdico=tempdico->alt;
            }
            else if (temp->cara==tempdico->cara)
            {

                    tempdico2=tempdico;
                    tempdico=tempdico->succ;
                    temp=temp->suivant;

            }

        }

    return tempdico2;
}

int rechercheMot2(DicoAL dico, Mot mot)
{
    Cellule * currentcell= dico;
    Car * currentcar=mot;
    while (currentcar->cara!='$' && currentcell!=NULL )
    {
        if (currentcar->cara==currentcell->cara)
        {
            currentcar=currentcar->suivant;
            currentcell=currentcell->succ;
        }
        if (currentcar->cara!=currentcell->cara)
        {

            currentcell=currentcell->alt;
        }

    }
    if (currentcell==NULL)
    {
        return 0;
    }
    else if (currentcell->cara==currentcar->cara && currentcar->cara=='$')
    {
        return 1;
    }
    else
        return 0;
}


DicoAL ajoutMot2(DicoAL dico, Mot mot)
{
    if (rechercheMot2(dico, mot)==1)
    {
        printf("\n Ce mot est déjà dans le dictionaire \n");
        return dico;
    }
    else
    {
        Cellule * cellinse=prefixeMot(dico, mot);

        if (cellinse==NULL)
        {
            Cellule * tempcell=dico;
            Car * tempcar=mot;
            if (tempcar->cara<tempcell->cara)
            {
                Cellule * nouvo=malloc(sizeof(Cellule));
                nouvo->cara=tempcar->cara;
                nouvo->succ=NULL;
                nouvo->alt=tempcell;
                tempcell=nouvo;
                while (tempcar->cara!='$')
                {
                    tempcar=tempcar->suivant;
                    Cellule * nouvo2=malloc(sizeof(Cellule));
                    nouvo2->succ=NULL;
                    nouvo2->alt=NULL;
                    nouvo2->cara=tempcar->cara;
                    nouvo->succ=nouvo2;
                    nouvo=nouvo2;
                }
            return tempcell;
            }

            while (tempcell->alt!=NULL && tempcar->cara>tempcell->alt->cara)
            {
                tempcell=tempcell->alt;
            }
            Cellule * inse=malloc(sizeof(Cellule));
            inse->alt=tempcell->alt;
            tempcell->alt=inse;
            inse->cara=tempcar->cara;
            inse->succ=NULL;
            while (tempcar->cara!='$')
            {

                Cellule * inse2=malloc(sizeof(Cellule));
                tempcar=tempcar->suivant;
                inse2->cara=tempcar->cara;
                inse2->alt=NULL;
                inse2->succ=NULL;
                inse->succ=inse2;
                inse=inse2;
            }
        return dico;
        }
        /*FIN CELLINSE==NULL*/
        else
        {
            Car * tempcar=mot;
            Cellule * tempCell=cellinse->succ;
            Cellule * inse=malloc(sizeof(Cellule));

            while (tempcar->cara!=cellinse->cara)
            {
                tempcar=tempcar->suivant;
            }
            tempcar=tempcar->suivant;
            /*if (tempCell==NULL)
            {

                cellinse->succ=inse;
                inse->cara=tempcar->cara;
                inse->succ=NULL;
                inse->alt=NULL;
                while (tempcar->cara!='$')
                {
                    Cellule * inse2=malloc(sizeof(Cellule));

                    tempcar=tempcar->suivant;

                    inse2->cara=tempcar->cara;
                    inse2->alt=NULL;
                    inse2->succ=NULL;
                    inse->succ=inse2;
                    inse=inse2;
                }

            }*/


            if (tempCell->cara<tempcar->cara)
            {

                while (tempCell->alt!=NULL && tempcar->cara>tempCell->cara)
                {
                    tempCell=tempCell->alt;
                }
                inse->alt=tempCell->alt;
                inse->succ=NULL;
                inse->cara=tempcar->cara;
                tempCell->alt=inse;
                while (tempcar->cara!='$')
                {
                    Cellule * inse2=malloc(sizeof(Cellule));

                    tempcar=tempcar->suivant;

                    inse2->cara=tempcar->cara;
                    inse2->alt=NULL;
                    inse2->succ=NULL;
                    inse->succ=inse2;
                    inse=inse2;
                }

            }
            else
            {
                cellinse->succ=inse;
                inse->alt=tempCell;
                inse->succ=NULL;
                inse->cara=tempcar->cara;
                while (tempcar->cara!='$')
                {
                    Cellule * inse2=malloc(sizeof(Cellule));

                    tempcar=tempcar->suivant;

                    inse2->cara=tempcar->cara;
                    inse2->alt=NULL;
                    inse2->succ=NULL;
                    inse->succ=inse2;
                    inse=inse2;
                }
            }
        return dico;
        }

    }
return dico;
}


void afficherDico2 (DicoAL currentCell,char *mot, char * cond, int i)
{
    if(currentCell!=NULL)
    {
	    if(currentCell->cara == '$')
	    {
	        if(i!=0)
	        {
	            if (strcmp(mot,cond)>=0 && strcmp(mot, " ")>0)
	           {
                printf("%s\n",mot);
                i--;
	           }
	        }


	        if(currentCell->alt==NULL)
	            return;
	    }
	    if(currentCell->succ !=NULL)
	    {
	        char c = currentCell->cara;
	        size_t len = strlen(mot);

	        char *cat = malloc(len+1+1);
	        strcpy(cat,mot);
	        cat[len]=c;
	        cat[len+1]='\0';
	        afficherDico2(currentCell->succ,cat, cond , i);
	        free(cat);


    }

	    if(currentCell->alt!=NULL)
	    {
	        afficherDico2(currentCell->alt, mot, cond, i);
	    }
    }
    else
        printf("dictionnaire vide.\n");

}


Cellule * CellASupp (DicoAL dico, Mot mot)
{
    Cellule * teteCell= dico;
    Car * tempCar=mot;
    while (teteCell!=NULL && tempCar->cara>teteCell->cara)
    {
        teteCell=teteCell->alt;
    }
    Cellule * tempCell=teteCell;
    Cellule * CellSupp=teteCell;

    while (tempCar!=NULL)
    {
        if (tempCell->alt!=NULL)
        {
            CellSupp=tempCell;
        }
        if (tempCar->cara==tempCell->cara)
        {
            tempCar=tempCar->suivant;
            tempCell=tempCell->succ;
        }
        else
        {
            tempCell=tempCell->alt;
            CellSupp=tempCell;
        }

    }
return CellSupp;
}

Cellule * PereCell (DicoAL dico, Cellule * temp, Mot mot)
{

    Cellule * teteCell= dico;
    Car * tempCar=mot;
    while (teteCell!=NULL && tempCar->cara>teteCell->cara && teteCell->alt!=temp)
    {

        teteCell=teteCell->alt;
    }


    if (teteCell->alt==temp)
    {
        return teteCell;
    }

    Cellule * tempCell=teteCell;
    while (tempCell->succ!=temp && tempCell->alt!=temp)
    {
        if (tempCell->cara!=tempCar->cara)
        {
            tempCell=tempCell->alt;
        }
        else
        {
            tempCell=tempCell->succ;
            tempCar=tempCar->suivant;
        }
    }
    return tempCell;
}

DicoAL supprimeMot2 (DicoAL dico, Mot mot)
{
    if (rechercheMot2(dico, mot)==0)
    {
        printf("\n Ce mot n'existe pas \n");
        return dico;
    }
    else
    {
        DicoAL suppCell=CellASupp(dico, mot);

        Cellule * tempCell=suppCell;
        if (tempCell==dico)
            {
                DicoAL tempDico=dico->alt;
                while (tempCell!=NULL)
                {
                    suppCell=tempCell->succ;
                    free(tempCell);
                    tempCell=suppCell;
                }
                return tempDico;
            }
        Cellule * pere=PereCell(dico, tempCell, mot);

        if (pere->alt==tempCell)
        {
            pere->alt=tempCell->alt;
        }
        else if (tempCell->alt!=NULL)
            {
               pere->succ=tempCell->alt;
            }



        while (tempCell!=NULL)
        {
            suppCell=tempCell->succ;
            free(tempCell);
            tempCell=suppCell;
        }
    return dico;
    }
}


void suggestionMot2(DicoAL dico, char * string, int k)
{
    liste_sug * l=malloc(sizeof(liste_sug));
    l->tete=NULL;
    l->taille=0;
    char * pred="\0";
    l=suggestionMot2Rec (dico, string, k, l, pred);
    afficher_liste (l);
    cellulel * temp=l->tete;
    cellulel * temp2=NULL;
    while (temp!=NULL)
    {
        temp2=temp->suivant;
        free(temp);
        temp=temp2;
    }
    free(l);
}


liste_sug * suggestionMot2Rec (DicoAL dico, char * string, int k, liste_sug * liste, char * pred)
{
    if (dico==NULL)
    {
        return liste;

    }
    else
    {
        if (dico->cara=='$' && strcmp(pred, "")!= 0)
        {

            liste=traitementMot(pred, string, k, liste);
        }

        if (dico->succ!=NULL)
        {
            int l=strlen(pred);
            char * newpred=malloc(sizeof(char)*l+1);
            strcpy(newpred, pred);
            newpred[l]=dico->cara;
            newpred[l+1]='\0';
            liste=suggestionMot2Rec (dico->succ, string, k, liste, newpred);
        }
        if (dico->alt!=NULL)
        {
            liste=suggestionMot2Rec(dico->alt, string, k , liste, pred);
        }


    }
return liste;
}


liste_sug * traitementMot (char * string, char * mot, int k, liste_sug * liste)
{
    int i=0, nb=0;
    while (string[i]==mot[i])
    {
        i++;
        nb++;
    }
    Node * noeud=malloc(sizeof(Node));
    strcpy(noeud->key,string);
    noeud->pere=NULL;
    noeud->droit=NULL;
    noeud->gauche=NULL;
    liste=insererliste(noeud, k, nb, liste);
    return liste;
}

Mot lireMot (char * m)
{
    int i=0;
    Mot mot=malloc(sizeof(Mot));
    mot->cara=m[i];
    mot->suivant=NULL;
    Car * tempCar=mot;
    i++;
    while (m[i]!='\0')
    {

       Car * tempCar2=malloc(sizeof(Car));
       tempCar2->cara=m[i];
       tempCar2->suivant=NULL;
       tempCar->suivant=tempCar2;
       tempCar=tempCar2;
       i++;
    }
    if (tempCar->cara!='$')
    {
      Car * finmot=malloc(sizeof(Car));
      finmot->cara='$';
      finmot->suivant=NULL;
      tempCar->suivant=finmot;
    }

    return mot;
}

/*PARTIE 3 */

DicoABR veriDicoABR(DicoABR *arbre, Node *node, File *dictionnaire)
{
    File *dico=NULL;
    DicoABR *tree;
    int choix,r;
    char *s;
    dico=fopen("dico.txt","w");
    printf("%s \n", node->key);
    printf("Pour corriger ce mot, tapez 1. Pour supprimer ce mot, tapez 2. Pour validez ce mot, tapez 3.");
    switch(choix)
    {
    case 1:
        printf("Entrez une proposition de mot : ");
        scanf("%s", s);
        r=ajoutMot(tree,s);
        if(r==-1)
            printf("Echec dan la modifiaction du mot.");
        else
            fprintf(dico,"%s",s);
        break
    case 2 :
        break;
    case 3 :
        r=ajoutMot(tree, node->key);
        if(r==-1)
            printf("Echec dans la validation du mot");
        else
            fprintf(dico,"%s", node->key);
        break;
    }
    if(node->left!=NULL)
        tree=veriDicoABR(arbre,node->left,dictionnaire);
    if(node->right!=NULL)
        tree=veriDicoABR(arbre,node->right,dictionnaire);
    return tree;
}
