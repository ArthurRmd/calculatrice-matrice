#include <stdio.h>
#include <stdlib.h>
#define max 20

void saisie ( int nb_col, int nb_lig,float mat[][max] );
void affichage (int nb_col, int nb_lig, float mat[max][max]);
void remise_0 (float mat[][max]);
void produit_2matrices ();
void somme_matrices (float matA[][max],float matB[][max],float matR[][max],int nb_col,int nb_lig);
void multiplication_scalaire (float matA[][max],float matR[][max],int nb_col,int nb_lig);
void creation_tab (float I[][max], int nb_ligA, float A[][max]);
void transposee (float R[][max]);
void inverse_matrice (float matA[][max],float matR[][max],int nb_col) ;
void lireFichier(float mat[max][max]);






int main()
{
    int nb_colA, nb_ligA,menu;
    float R[max][max];
    float A[max][max];
    float B[max][max];




    while ( menu != 0)
    {
        printf("\n");
        printf("\n");
        printf("       #####################################################\n");
        printf("       #               Que voulez vous faire ?             #\n");
        printf("       #                                                   #\n");
        printf("       #       1: Calculer somme                           #\n");
        printf("       #       2: Calculer produit ( scalaire )            #\n");
        printf("       #       3: Calculer produit ( 2 matrices )          #\n");
        printf("       #       4: Transposee                               #\n");
        printf("       #       5: Calculer inverse                         #\n");
        printf("       #       0: Quitter                                  #\n");
        printf("       #                                                   #\n");
        printf("       #####################################################\n");

        printf("\n");
        printf("-> ");
        scanf("%d", &menu);
        printf("\n");

        switch (menu)
        {

        case 1:
            printf("\n");
            printf("Rentrez le nombre de lignes de la matrice : ");
            scanf("%d", &nb_ligA);
            printf("Rentrez le nombre de colonnes de la matrice : ");
            scanf("%d", &nb_colA);

            printf("\nVeuillez remplir la matrice A\n");
            saisie(nb_colA,nb_ligA, A);

            printf("\nVeuillez remplir la matrice B\n");
            saisie(nb_colA,nb_ligA, B);

            somme_matrices (A,B,R,nb_colA, nb_ligA);
            break;

        case 2:
            printf("\n");
            printf("Rentrez le nombre de lignes de la matrice A : ");
            scanf("%d", &nb_ligA);
            printf("Rentrez le nombre de colonnes de la matrice A : ");
            scanf("%d", &nb_colA);
            printf("\n");
            saisie(nb_colA,nb_ligA, A);
            multiplication_scalaire (A,R,nb_colA,nb_ligA);
            break;

        case 3:
            printf("\n");
            produit_2matrices();
            break;



        case 4:
            transposee(R);
            break;

        case 5:
            printf("Entrez le nombre de lignes de la matrice A : ");
            scanf("%d",&nb_ligA);
            printf("Entrez le nombre de colonnes de la matrice A : ");
            scanf("%d",&nb_colA);
            printf("\n");

            saisie( nb_colA, nb_ligA, A);
            inverse_matrice(A,R,nb_colA) ;
            break;




        case 0 :

            break;



        }

    }
    return 0;
}

void saisie( int nb_col, int nb_lig,float mat[][max])
{

    int i, j,i2, j2;
    float element ;

    i2 = 1;
    j2 = 1;

    /* Permet de rentrer chaque case de la matrice   */
    for (i=0; i<nb_lig; i++)
    {
        for (j=0; j<nb_col; j++)
        {
            printf("Entrez l'element (%d, %d ) : ", i2, j2);
            scanf("%f",&element);
            mat [i][j]=element;
            j2+= 1;
        }
        j2=1;
        printf("\n");
        i2+=1;
    }
}




void affichage(int nb_col, int nb_lig, float mat[max][max])
{


    int i, j ;
    float resultat;
    int lettre;
    char nom_fichier[30];

    /* Affiche en fonction du nombre de ligne et de colonne   */

    for (i=0; i<nb_lig; i++)
    {
        for (j=0; j<nb_col; j++)
        {

            if ( j == 0)
            {
                printf("  | ");
            }

            resultat = mat[i][j];
            printf("%7.2f |", resultat );
        }
        printf("\n");
    }

    /*  Permet d'enregistrer dans un fichier texte   */

    printf("\nSouhaitez vous sauvegarder la matrice dans un fichier texte ? \n(oui: 1/ non: 2) : ");
    scanf("%d", &lettre);

    if (lettre == 1)
    {

        /*   Demande le nom du fichier */

        printf("\nQuelle nom voulez vous donner au fichier : ");
        scanf("%s", nom_fichier);

        FILE *f;
        f = fopen(nom_fichier, "w");

        if ( f == NULL)
        {
            printf("Erreur \n");
        }

        else
        {

            /*  Permet d'écrire dans le fichier  */

            for (i=0; i<nb_lig; i++)
            {
                for (j=0; j<nb_col; j++)
                {

                    if ( j == 0)
                    {
                        fprintf(f,"  | ");
                    }

                    resultat = mat[i][j];
                    fprintf(f,"%7.2f |", resultat );
                }
                fprintf(f,"\n");
            }

            fclose(f);



        }
    }
}

void remise_0( float mat[][max])
{

    int i, j;

    /*  Permet de renitialiser la matrice  */
    for (i=0 ; i<max ; i++)
    {

        for (j=0 ; j < max ; j++)
        {

            mat[i][j]= 0;
        }

    }
}

void produit_2matrices ()
{
    int i,j,k;
    int nb_colA, nb_ligA, nb_colB, nb_ligB;

    float R[max][max];
    float A[max][max];
    float B[max][max];

    printf("Rentrez le nombre de lignes de la matrice A : ");
    scanf("%d", &nb_ligA);
    printf("Rentrez le nombre de colonnes de la matrice A : ");
    scanf("%d", &nb_colA);
    printf("\n");
    saisie(nb_colA,nb_ligA, A);

    printf("Rentrez le nombre de colonnes de la matrice B : ");
    scanf("%d", &nb_colB);
    nb_ligB = nb_colA;
    printf("\n");
    saisie(nb_colB,nb_ligB,B);

    /* Affectation du résultat de la multiplication à R */
    for (i=0; i<nb_ligA; i++)
    {
        for (j=0; j<nb_colB; j++)
        {
            R[i][j]=0;
            for (k=0; k<nb_ligB; k++)
                R[i][j] += A[i][k]*B[k][j];
        }
    }

    affichage(nb_colB, nb_ligA, R);
    printf("\n");
}

void somme_matrices (float matA[][max],float matB[][max],float matR[][max],int nb_col,int nb_lig)
{
    int i,j;

    float resultat;
    remise_0(matR);

    /* Boucle pour calculer la somme   */

    for(i=0; i<nb_lig; i++)
    {
        for(j=0; j<nb_col; j++)
        {
            resultat=matA[i][j]+matB[i][j];
            matR[i][j]=resultat;
        }
    }

    affichage(nb_col, nb_lig, matR);
    printf("\n");
}

void multiplication_scalaire (float matA[][max],float matR[][max],int nb_col,int nb_lig)
{
    int i,j;
    float scalaire;
    float resultat;

    /* Demande du scalaire    */

    printf("Entrez le scalaire : ");
    scanf("%f",&scalaire);

    /*  Boucle pour multiplier   */

    for(i=0; i<nb_lig; i++)
    {
        for(j=0; j<nb_col; j++)
        {
            resultat=matA[i][j]*scalaire;
            matR[i][j]=resultat;
        }
    }
    printf("\n");
    affichage(nb_col, nb_lig, matR);
    printf("\n");
}

void creation_tab (float I[][max],  int nb_ligA, float A[][max])
{


    int i, j;
    int temp1;


    /*  Création matrice de transition  */

    for (i=0; i<max ; i++)
    {

        for (j=0; j<max ; j++)
        {

            I[i][j] = 0;
        }
    }

    for (i=0; i<nb_ligA ; i++)
    {

        for (j=0; j<nb_ligA ; j++)
        {

            I[i][j] = A[i][j];
        }
    }


    for (i=0; i<nb_ligA ; i++)
    {
        temp1 = (i+(nb_ligA));
        I[i][temp1]=1;
    }



}


void transposee(float R[][max])
{

    int nb_colA, nb_ligA,i, j;
    float temp [max][max];

    printf("\n");
    printf("Rentrez le nombre de lignes de la matrice : ");
    scanf("%d", &nb_ligA);
    printf("Rentrez le nombre de colonnes de la matrice : ");
    scanf("%d", &nb_colA);

    saisie(nb_colA, nb_ligA, temp);

    /* Calcul de la transposée */

    for (i=0; i<nb_ligA ; i++)
    {

        for (j=0; j<nb_colA ; j++)
        {
            R[j][i] = temp[i][j];
        }
    }

    affichage(nb_ligA, nb_colA, temp);
    printf("\nLa transposee est :\n\n");
    affichage(nb_ligA, nb_colA, R);
}



void inverse_matrice (float matA[][max],float matR[][max],int nb_col)
{
    int i,j,k;
    float matI[max][max];
    float resultat;
    int lettre;
    char nom_fichier[30];


    /*  Utilise la procédure création_tab -> matrice de transition  */
    creation_tab(matI,nb_col,matA) ;


    for(i=0; i<nb_col-1; i++)
    {
        for(j=i+1; j<nb_col; j++)
        {
            int l1=matI[i][i];

            int l2=matI[j][i];

            for(k=0; k<nb_col*2; k++)
            {
                matI[i][k]=matI[i][k]*l2;

                matI[j][k]=matI[j][k]*l1;

                matI[j][k]=matI[j][k]-matI[i][k];

            }


        }
    }





    for(i=nb_col-1; i>=0; i--)
    {

        for(j=i-1; j>=0; j--)
        {
            int l1=matI[i][i];

            int l2=matI[j][i];

            for(k=0; k<nb_col*2; k++)
            {
                matI[i][k]=matI[i][k]*l2;

                matI[j][k]=matI[j][k]*l1;

                matI[j][k]=matI[j][k]-matI[i][k];

            }


        }
    }

    for (i=0; i<nb_col; i++ )
    {

        float var=matI[i][i];


        for (j=0; j<nb_col*2; j++)
        {
            matI[i][j]= matI[i][j]/var;
        }
    }

    /*  Affichage*/

    for(i=0; i<nb_col; i++)
    {
        for(j=0; j<nb_col; j++)
        {
            resultat = matI[i][j+nb_col];
            printf("%7.4f |", resultat );
        }
        printf("\n");

    }



    printf("\nSouhaitez vous sauvegarder la matrice dans un fichier texte ? \n(oui: 1/ non: 2) : ");
    scanf("%d", &lettre);

    if (lettre == 1)
    {


        printf("\nQuelle nom voulez vous donner au fichier : ");
        scanf("%s", nom_fichier);


    }

    FILE *f;
    f = fopen(nom_fichier, "w");

    if ( f == NULL)
    {
        printf("Erreur \n");
    }

    else
    {


        for (i=0; i<nb_col; i++)
        {
            for (j=0; j<nb_col; j++)
            {

                if ( j == 0)
                {
                    fprintf(f,"  | ");
                }

                resultat = matI[i][j+nb_col];
                fprintf(f,"%7.4f |", resultat );
            }
            fprintf(f,"\n");
        }

        fclose(f);



    }
}










