
/*===========================================================*

 Devoir : Devoir 1
 Par    : Eya Cherni
 Date   : 2024/09/2


 /*
Ce module contient plusieurs fonctions qui saisissent
et valider des dates,sous certaines conditions. 

Le main() (programme principal)  affiche une date valide  donnée par
l'utilisateur.
Valide l'année, le jours,le mois et trouve le jour litteral
avec les autres fonctions.


*/


/*=========================================================*/
/*=========================================================*/


//Permet de désactiver certains warnings du compilateur 
#define _CRT_SECURE_NO_WARNINGS 

// Librairies usuelles à inclure 
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h> 
#include<assert.h>
#include<conio.h> // Necessaire pour _kbhit() et _getch()

/*=========================================================*/
#include "WinConsole.h"   //Librairie non usuelle 

/*=========================================================*/
/*                  LES CONSTANTES                         */
/*=========================================================*/

  /*
	MODE_TESTS :
	Cette constante détermine si le programme est exécuté en mode test ou en mode
	normal.
	- Valeur 0 : Le programme est exécuté en mode normal.
	- Valeur 1 : Le programme est exécuté en mode test.
  */
#define MODE_TESTS 0


  /* constante pour attribuer un chiffre aux mois (1 a 12) */
enum mois { JAN = 1, FEV, MAR, AVR, MAI, JUN, JUI, AOU, SEP, OCT, NOV, DEC };

/*constantes pour attribiuer un chiffre aux jours de semaine  (0 a 6) */
enum jours { DIM, LUN, MARD, MER, JEU, VEN, SAM };

/*  Année minimale valide. */
#define ANN_MIN 1900

/*  Année maximale valide. */
#define ANN_MAX 2024

/*Année de référence pour les calculs. */
#define ANNEE_0  2024


/* Mois de référence pour les calculs (9 = septembre). */
#define MOIS_0 9

/*Jour de reference 0 pour le dimanche */
#define JOUR_0 0

/*Nombres de jours dans une annee non bissextile*/
#define NB_JRS_AN 365

/*Nombre de jours dans une annee  bissextile*/
#define NB_JOURS_ANN_BI 366

/*Maximum de jours dans un mois*/
#define NB_JRS_MOIS 31

/*Jours dans une semaine*/
#define NB_JRS_SEM 7

/*Jours en février*/
#define NB_JRS_FEV 28 

/*code ASCII de la fleche gauche*/
#define FLECHE_G 75

/*code ASCII de la fleche droite*/
#define FLECHE_D 77

/*code ASCII de l`espace*/
#define ESPACE 32

/*Nombre d`espacement dans les case de jours*/
#define NB_ESP 10 

/*Nombre de jours dans un mois de 30 jours*/
#define NB_J_MOIS 30

/*Nombre de jours dans un mois de 31 jours*/
#define NB_J_MOIS_UN 31

/*Nombre de jours dans un mois de fevrier jours*/
#define NB_J_FEV_BI 29 


/*FFLUSH() : Cette constante empêche le programme de
	planter si l'utilisateur rentre du texte.*/

#define FFLUSH()   while (getchar() != '\n') {}


	/*=========================================================*/
	/*=========================================================*/

//Declaration des prototypes des fonctions utilisees dans le vrai main()


int valider_entier(const char* message, int borne_min, int borne_max);



int est_bissextile(int annee);



int nb_jours_mois(int mois, int annee);



int nb_jours_diff(int annee, int mois, int jours);



int quel_jour(int nb_jours);



const char* affiche_mois(int mois);


const char* affiche_jour(int jours);

void affichage_en_tete(int mois, int annee);



void calendrier_mois(int annee, int mois, int jours);


void passage_temps(int annee, int mois);



#if (MODE_TESTS) 

//Prototype des fonctions du main() test 

/*Permettent de valider le comportement des fonctions
 avec assertations.*/

void test_est_bissextile(void);

void test_nb_jours_mois(void);

void test_nb_jours_diff(void);

void test_queljours(void);


// Le main() test qui est execute quand MODE_tests==1
int main(void)
{
	//Appel des fonctions tests.

	test_est_bissextile();

	test_nb_jours_mois();

	test_nb_jours_diff();

	test_queljours();
}
#else


// Le  vrai main() qui est execute quand MODE_tests==0

int main(void)
{

	int annee = 0 ;       // stocke l'année saisie par l'utilisateur

	int mois = 0 ;       // stocke le mois  saisie par l'utilisateur

	int jours = 0 ;      //stocke le jour saisie par l'utilisateur

	int nb_jours;         //stocke le nombre de jours du mois saisie

	int jours_diff_valide;  // stocke le nombre de jours entre jour saisie et 1er sept. 

	int jours_semaine;  // stocke le chiffre du jours de semaine du jour saisie (0 a 6)


	// Validation de l'année saisie par l'utilisateur

	do
	{
		clrscr();  //Efface l`ecran 
	
		annee = valider_entier("Entrer une annee entre 1900 et 2024 (0 pour annuler) :",
			ANN_MIN, ANN_MAX);

		if (!(annee == 0))
		{


			// Validation du mois selon l'année saisie
			if (annee == ANN_MAX)
			{
				mois = valider_entier("Entrez un mois de 1 a 8 (0 pour annuler) : "
					, JAN, AOU);

			}
			else
				mois = valider_entier("Entrez un mois de 1 a 12 (0 pour annuler) : "
					, JAN, DEC);


			if (!(mois == 0))
			{
				// Récupération du nombre de jours dans le mois valide
				nb_jours = nb_jours_mois(mois, annee);

				// Validation du jour selon le mois et l'année
				jours = valider_entier("Entrez un jour de votre mois (0 pour annuler):",
					1, nb_jours);

				if (!(jours == 0))
				{


					affichage_en_tete(mois, annee);

					calendrier_mois(annee, mois, jours);



					jours_diff_valide = nb_jours_diff(annee, mois, jours);

					jours_semaine = quel_jour(jours_diff_valide);


					gotoxy(0, 19);

					printf("\n\nLe %d/%s/%d etait un %s.\n\n", jours, affiche_mois(mois),
						annee, affiche_jour(jours_semaine));

					passage_temps(annee, mois);


				}
			}

		}
	} 
	while ((annee != 0) && (mois != 0) && (jours != 0));  

	printf("Merci d`avoir utilise le programme\n"); 

	
	return EXIT_SUCCESS;

}
#endif



/*=========================================================*/

/*

-int valider_entier(const char* message, int borne_min, int borne_max) :
Cette fonction demande et saisie un nombre entier compris
entre une bornes (min et max). Elle vérifie que l'entrée
est valide et renvoie l'entier

*/

int valider_entier(const char* message, int borne_min, int borne_max)
{
	int va;  //Variable pour stocker l'année,le mois et le jours saisie par l'utilisateur

	do
	{
		printf("%s", message);

		scanf("%d", &va);

		FFLUSH();

		// Vérifie si l'utilisateur veut annuler
		if (va == 0) return 0;

		if ((va < borne_min) || (va > borne_max))

			printf("Votre valeur est incorrecte \n");

	} while ((va < borne_min) || (va > borne_max));

	// Retourne l'entier valide
	return va;

}



/*=========================================================*/

/*

- int est_bissextile(int annee) :
Elle vérifie si une année est bissextile.
renvois 1 si cest le cas ,sinon 0.

*/

int est_bissextile(int annee)
{

	return ((annee % 4 == 0 && !(annee % 100 == 0)) || ((annee % 400 == 0)));


}



/*=========================================================*/

/*-

- int nb_jours_mois(int mois, int annee) :
Cette fonction renvoie le nombre de jours dans un mois donné pour une année
spécifique avec switch case, en prenant en compte si l'année est bissextile
pour le mois de février.

*/

int nb_jours_mois(int mois, int annee)

{
	int nbj;  // Variable pour stocker le nombre de jours dans le mois spécifié

	switch (mois)
	{
	case JAN: case MAR: case MAI: case JUI:
	case AOU: case OCT: case DEC:
		nbj = NB_J_MOIS_UN; 
		break;
	case AVR: case JUN:  case SEP: case NOV:
		nbj = NB_J_MOIS;
		break; 
	case FEV:
		if (est_bissextile(annee))
			nbj = NB_J_FEV_BI;
		else
			nbj = NB_JRS_FEV;
		break;
	}
	return nbj;

}





/*=========================================================*/


/* nb_jours_diff : Elle va calculer le nombre de jours de difference entre la date de
reference et la date recue en parametre. */


int nb_jours_diff(int annee, int mois, int jours)
{
	int annee_0 = ANNEE_0;       // Annee de reference 2024.

	int mois_0 = MOIS_0;         // Mois de reference septembre (9).

	int jour_0 = 1;       // Jour de reference (1er ).

	int diff_jours = 0;  //Difference de jours entre la date saisie et la date reference.

	while (annee_0 > annee)
	{
		// On ajoute une annee complete de difference.

		if ((annee_0 > (annee + 1)) || (mois < SEP)) {

			if (est_bissextile(annee_0)) {     // Si l`annee est bissextile.

				diff_jours += NB_JOURS_ANN_BI;  // Oui ,+366 jours.
			}
			else {
				diff_jours += NB_JRS_AN;       // Non ,+ 365 jours.
			}
		}
		annee_0--;

	}
	if (mois >= SEP) {
		annee_0++;

	}
	do
	{
		mois_0--;

		// Si mois_0 est Janvier on retourne a decembre et on decremente

		if (mois_0 == 0) {

			mois_0 = DEC;

			annee_0--;
		}
		if (!(mois_0 == mois))

			diff_jours += nb_jours_mois(mois_0, annee_0);
	}

	while (!(mois_0 == mois));

	diff_jours += (nb_jours_mois(mois_0, annee_0) - jours + 1);


	return diff_jours;

}




/*=========================================================*/


/* quel_jour: Donne le jours de la semaine (0 a 6) du jour saise,
Recule de (nb_jours %7) a partir de la date de reference */

int quel_jour(int nb_jours)
{

	return (JOUR_0 - (nb_jours % NB_JRS_SEM) + NB_JRS_SEM) % NB_JRS_SEM;

}



/*=========================================================*/


/* affiche_mois: Elle va lier au mois litteral au mois saisie */

const char* affiche_mois(int mois)
{

	switch (mois)
	{
	case JAN:
		return "Janvier";
	case FEV:
		return "Fevrier";
	case MAR:
		return "Mars";
	case AVR:
		return "Avril";
	case MAI:
		return "Mai";
	case JUN:
		return "Juin";
	case JUI:
		return "Juillet";
	case AOU:
		return "Aout";
	case SEP:
		return "Septembre";
	case OCT:
		return "Octobre";
	case NOV:
		return "Novembre";
	case DEC:
		return "Decembre";

	}

}



/*=========================================================*/

/*affiche_jour : Elle va lier un jour litteral au jour  saisie */

const char* affiche_jour(int jours)
{

	switch (jours)
	{
	case DIM:
		return "Dimanche";
	case LUN:
		return "Lundi";
	case MARD:
		return "Mardi";
	case MER:
		return "Mercredi";
	case JEU:
		return "Jeudi";
	case VEN:
		return "Vendredi";
	case SAM:
		return "Samedi";
	}

}



/*=========================================================*/

/*affichage_en_tete: Cette fonction affiche l'en-tête du calendrier, comprenant le
nom du mois et l'année centrés, ainsi que les noms des jours de la semaine.
Elle facilite la lecture du calendrier.*/

void affichage_en_tete(int mois, int annee)
{
	clrscr();	  // Effacer l`ecran


	printf("============================================================================\n");

	printf("                               <=  %s,%d  =>\n", affiche_mois(mois), annee);

	printf("============================================================================\n");


	printf("|   Dimanche  |  Lundi  | Mardi  | Mercredi |  Jeudi  | Vendredi | Samedi  |\n");

	printf("============================================================================\n");

	
}




/*=========================================================*/


/*
  calendrier_mois : Cette fonction génère et affiche le calendrier d'un mois
  spécifique d'une année donnée. Elle calcule les jours de la semaine pour chaque jour
  du mois et les affiche en alignant correctement les jours dans un format de calendrier.
  Elle met également en surbrillance un jour particulier fourni par l'utilisateur,
  facilitant ainsi la visualisation de la date choisie.*/

void calendrier_mois(int annee, int mois, int jours)
{

	int jours_ecart;      // nb jours d`ecart entre date de ref, et chaque jours affiche.

	int jours_affiche = 1;  // la date du jours affiche dans le calendirer  

	int jours_sem = 0;   // le jours de semaine (0 a 6) des jours affiche 

	int posy = 5;      // la coordonne "y" pour la fonction gotoxy




	// on commence par le 1er du mois ( jours_affiche =1)

	while (jours_affiche <= nb_jours_mois(mois, annee))

	{
		jours_ecart = nb_jours_diff(annee, mois, jours_affiche);

		jours_sem = quel_jour(jours_ecart); // nous donne jour de semiane (0 a 6)  

		if (jours_affiche == jours)
		{
			textcolor(RED); 
		}
		else
		{
			textcolor(WHITE);
		}
		 
		//ici + 10 cest le nombre car dimanche cest jours 0
		gotoxy(((jours_sem * NB_ESP) + NB_ESP), posy);   

		printf("%d", jours_affiche);

		jours_affiche++;

		jours_sem++;

		//si le jour_sem est un multiple de 7: saute de ligne , revenir a 0
		if (jours_sem % NB_JRS_SEM == 0)
		{
			posy += 2;

			jours_sem = DIM;

		}

	}

}




/*=========================================================*/

/* Cette fonction gère l'interaction utilisateur pour naviguer dans le calendrier,
 permettant de voir les mois précédents et suivants, ainsi que de retourner à
 l'entrée d'une nouvelle date.Elle limite la date au aout 2024
 et janvier 1900.*/

void passage_temps(int annee, int mois)
{
	unsigned char touche;


	printf("\nAppuyez les fleches gauche/droite pour voir les mois precedents/suivants.\n\n");

	printf("\nAppuyer sur l`espace pour saisir une autre date.\n\n");

	do
	{
		touche = 0;

		if (_kbhit())      // on verifie si on appuie sur une touche etendu
		{
			touche = _getch();   // premiere lecture de la touche  

			if (touche == 0 || touche == 224)

				touche = _getch();    //2e lecture de la touche

			switch (touche)
			{
			case FLECHE_G:

				mois--;
				if (mois < JAN)   //passage de janvier a decembre
				{
					mois = DEC;

					annee--;
				}

				if (annee < ANN_MIN)   //limite l`affichage au janvier 1900
				{
					mois = JAN;
					annee = ANN_MIN;
				}

				break;

			case FLECHE_D:

				mois++;

				if (mois > DEC)   //passage de decembre a janvier
				{

					mois = JAN;

					annee++;

				}
				if ((mois > AOU) && (annee == ANN_MAX))  //limite affichge aout 2024
				{
					mois = AOU;
					annee = ANN_MAX;
				}

				break;
			}

			clrscr();	  // Effacer l`ecran 

			affichage_en_tete(mois, annee);

			calendrier_mois(annee, mois, -1);

			gotoxy(0, 19); 

			printf
			("Appuyez les fleches gauche/droite pour voir les mois precedents/suivants.\n");  

			printf("\nAppuyer sur l`espace pour saisir une autre date.\n"); 
		}
	}

	while (touche != ESPACE); 
}




/*=========================================================*/

// Tests utilitaires  :

/*

	test_est_bissextile : Vérifie le fonctionnement de la fonction
	`est_bissextile`.

	Stratégie :
	- Utilise des assertions pour comparer les résultats de `est_bissextile`
	aux attentes.
	- Teste des années bissextiles (comme 2024 et 2004) et non bissextiles
	(comme 1900).

	Valeur de retour :
	- Cette fonction ne retourne rien. Elle s'arrête en cas d'échec
	d'une assertion.
*/


void test_est_bissextile(void)
{
	//Annee bissextiles
	assert(est_bissextile(2024) == 1);
	assert(est_bissextile(2020) == 1);
	assert(est_bissextile(1932) == 1);
	assert(est_bissextile(1928) == 1);
	//Annee non-bissextiles
	assert(est_bissextile(1900) == 0);
	assert(est_bissextile(1901) == 0);
	assert(est_bissextile(1951) == 0);
	assert(est_bissextile(2017) == 0);

}



/*=========================================================*/

/*
	test_nb_jours_mois : Vérifie  fonctionnement de la fonction `nb_jours_mois`.

	Stratégie :
	- Utilise des assertions pour comparer les résultats de `nb_jours_mois` aux
	valeurs attendues.
	- Teste les mois de 31 et 30 jours et février en année bissextile (2012) et
	non bissextile (2011).

	Valeur de retour :
	- Ne retourne rien ; l'arrêt se produit en cas d'échec d'une assertion.
*/

void test_nb_jours_mois(void)
{
	//Mois avec 31 jours 
	assert(nb_jours_mois(8, 2024) == 31);
	assert(nb_jours_mois(1, 2020) == 31);
	//Mois avec 28 jours 
	assert(nb_jours_mois(2, 2011) == 28);
	assert(nb_jours_mois(2, 2023) == 28);
	//Mois avec 29 jours 
	assert(nb_jours_mois(2, 2012) == 29);
	assert(nb_jours_mois(2, 2008) == 29);
	//Mois avec 30 jours 
	assert(nb_jours_mois(6, 2024) == 30);
	assert(nb_jours_mois(4, 2021) == 30);
}



/*=========================================================*/

/*
	test_nb_jours_diff : Vérifie  fonctionnement de la fonction `nb_jours_diff`.

	- Utilise des assertions pour comparer les résultats aux
	valeurs attendues,du nb de jours entre une date et le
	1er septembre 2024

	- Ne retourne rien ; l'arrêt se produit en cas d'échec d'une assertion.
*/

void test_nb_jours_diff(void)
{
	assert(nb_jours_diff(2024, 8, 1) == 31);
	assert(nb_jours_diff(2023, 9, 1) == 366);
	assert(nb_jours_diff(2022, 9, 1) == 731);
	assert(nb_jours_diff(2000, 1, 1) == 9010);
	assert(nb_jours_diff(1900, 1, 1) == 45534);
	//test avec un autre jours que 1er du mois
	assert(nb_jours_diff(2023, 2, 4) == 575);  

}



/*=========================================================*/

/*
	test_queljours : Vérifie le fonctionnement de la fonction `queljours`.

	Stratégie :
	- Utilise des assertions pour comparer les résultats aux
	valeurs attendues du jour donné au jours de semaine correspondant.
	- Ne retourne rien ; l'arrêt se produit en cas d'échec d'une assertion.
*/

void test_queljours(void)
{
	assert(quel_jour(1) == 6);
	assert(quel_jour(244) == 1);
	assert(quel_jour(1633) == 5);
	assert(quel_jour(8391) == 2);
	//test avec un multiple de 7 
	assert(quel_jour(21) == 0); 
}