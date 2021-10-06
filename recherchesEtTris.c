/* programme : recherchesEtTris.c
   auteurs : Jérémy TREMBLAY, Adrien COUDOUR, Maxime WISSOCQ
   date début: 17/12/2020
   date dernière modifiction : 15/01/2021
   Finalité : fonctions de recherches, de tri, de modification, d'ajout, de suppression des données de la ludothèque.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include"ludotheque.h"

#define TAILLEMAX 10000

/* FONCTIONS DE TRIS */

/*
Nom:triJeuxParNom
  Description: Fonction qui trie les jeux en fonctions du nom
  La fonction recherche la valeur minimum et i et tri le tableau de pointeur grâce a la fonction permutation 
  Paramètre en entrée:
	-*tJeux[] tableau de pointeur de la structure jeux
	-nbJeux Taille logique du fichier jeux
	
  Paramètre en sortie:
  -Aucun paramètre en sortie
Variables locales:
  -k entier compteur utiliser dans le for.
  -rmin entier qui récupère la valeur minimum de la fonction de recherche de Rmin
*/

void triJeuxParNom(Jeu *tJeux[], int nbJeux)
{
	int k, rmin;
	for (k = 0; k < nbJeux - 1; k++)
	{
		rmin = rechercheRMin(tJeux, k, nbJeux);
		permutation(tJeux, k, rmin);
	}
}

/*
Nom:rechercheRMin
  Description:Fonction qui recherche la valeur minimum
  la fonction compare le nom du jeu en fonction du tableau de pointeur tJeux par rapport a la valeur de j et la valeur récupère en rmin
  Paramètre en entrée:
	-*tJeux[] tableau de pointeur de la fonction jeux
	-n valeur de rmin trouvé en fonction précédente
	-i valeur de l'étape du for de la fonction précédente
	
  Paramètre en sortie:
  -entier renvoyant la valeur minimum
Variables locales:
  -j compteur prenant la place de i est utiliser dans la fonction pour comparer
  -rmin correspond a la valeur de i
*/

int rechercheRMin(Jeu *tJeux[], int i, int n)
{
	int rmin = i, j;
	for (j = i + 1; j < n; j++)
	{
		if (strcmp(tJeux[j]->nomJeu, tJeux[rmin]->nomJeu) < 0)
			rmin = j;
	}
	return rmin;
}

/*
Nom:permutation
  Description:Fonction de permutation qui permute le nom de 2 jeu
  Paramètre en entrée:
	-*tJeux[] tableau de pointeur de la structure tJeux
	-i numéro du première élément a permuter
	-j numéro  du second élément a permuter
	
  Paramètre en sortie:
  -Aucun paramètre en sortie
Variables locales:
  -jeu permutation élément de la structure jeu
*/

void permutation(Jeu *tJeux[], int i, int j)
{
	Jeu permutation;
	permutation = *tJeux[i];
	*tJeux[i] = *tJeux[j];
	*tJeux[j] = permutation;
}

/*
Nom:triRapideEmpruntsparId
  Description: Fonction de tri rapide de la fonction Emprunt permet de trier la fonction Emprunt en fonction de l'idEmprunt,cette fonction
  à l'aide de mur et pivot tri le fichier en regardant tant que  le courant est inférieur au nombre d'emprunt alors l'idEmprunt devient le 
  pivot et si la constante mur est différent de la constante courant alors le tri s'effectue

  Paramètre en entrée:
  -**tEmp tableau de pointeur contenant les informations de la fonction emprunt
  -nbEmp taille logique du fichier emprunt
  Paramètre en sortie:
  -Aucun paramètre en sortie
Variables locales:
  -mur entier définit a 0 permet le tri est comparé au courant
  -courant entier définit a 0 permet le tri est comparé au mur
  -pivot entier, valeur de l'idEmprunt du tableau Emprunt correspondant au nombre d'emprunt -1
  -emp1 élément de la structure Emprunt.
*/

void triRapideEmpruntsParId(Emprunt **tEmp, int nbEmp)
{
	int mur, courant, pivot;
	Emprunt emp1, emp2;

	if (nbEmp <= 1)
		return;

	mur = courant = 0;
	pivot = tEmp[nbEmp - 1]->idEmprunt;
	while (courant < nbEmp)
	{
		if (tEmp[courant]->idEmprunt <= pivot)
		{
			if (mur != courant)
			{
				emp1 = *tEmp[courant];
				*tEmp[courant] = *tEmp[mur];
				*tEmp[mur] = emp1;
			}
			mur++;
		}
		courant++;
	}

	triRapideEmpruntsParId(tEmp, mur - 1);
	triRapideEmpruntsParId(tEmp + mur - 1, nbEmp - mur + 1);

	return;
}

/* 
Nom triBullesEmpParDates

Decription générale : trie le contenu du tableau des emprunts par dates d'emprunt croissantes en utilisant la fonction de comparaison de dates

Variables locales :
	-i, k compteurs de boucles
	-temp variables de stockage temporaire
*/

void triBullesEmpParDates(Emprunt **tEmp, int nbEmp) 
{
    int i, k;
    Emprunt temp;

    for (k = 0; k < nbEmp - 1; k++)
    	for (i = nbEmp - 1; i > k; i--)
    		if (comparaisonDates(tEmp[i]->dateEmprunt, tEmp[i - 1]->dateEmprunt) >= 1)
    		{
    			temp = *tEmp[i];
    			*tEmp[i] = *tEmp[i - 1];
    			*tEmp[i - 1] = temp;
    		}
}
 


/* FONCTIONS DE RECHERCHES */

/*
Nom : rechercheIdentiteAdherent

Finalité : Fonction parcourant un tableau jusqu'à ce que l'id adhérent passé en paramètre soit trouvé. 
Elle copie alors les données de l'adhérent dans une structure passée en paramètre.

Description générale :
	-Cette fonction parcours un tableau d'adhérents à l'aide d'une boucle for.
	-Si l'id adhérent passé en paramètre est trouvé dans le tableau, les données de l'adhérent sont copiés dans une variable adh de type
	Adhérent et la position de l'id recherché dans le tableau est retournée.
	-Si l'id recherché est supérieur à l'id actuel du tableau, la fonction retourne -1 (on l'a dépassé).
	-La fonction retourne aussi -1 si l'id n'est pas trouvé.

Paramètres en entrée : 
	-**tAdh : Un tableau de pointeurs d'adhérent
	-nbAdh : le nombre d'adhérents (ou taille logique)
	-idAdherent : l'id recherchée (entier)
	-*adh : un pointeur vers une variable de type Adherent, où seront stockés les données de l'adhérent trouvé.  

Valeur retournée : La position de l'id recherchée ou -1 si l'id n'a pas été trouvée dans le tableau.

Variables locales: 
	-i, entier, la position de l'id une fois trouvée (=compteur de la boucle de parcour du tableau).
*/

int rechercheIdentiteAdherent(Adherent **tAdh, int nbAdh, int idAdherent, Adherent *adh)
{
	int i;

	for (i = 0; i < nbAdh; i++)
	{
		if (tAdh[i]->idAdherent == idAdherent)
		{
			//On copie le tout dans la structure passée par pointeur.
			strcpy(adh->nom, tAdh[i]->nom);
			strcpy(adh->prenom, tAdh[i]->prenom);
			strcpy(adh->civilite, tAdh[i]->civilite);
			adh->dateInscription.jour = tAdh[i]->dateInscription.jour;
			adh->dateInscription.mois = tAdh[i]->dateInscription.mois;
			adh->dateInscription.annee = tAdh[i]->dateInscription.annee;
			adh->idAdherent = tAdh[i]->idAdherent;
			return i;
		}

		//Comme les adhérents sont triés par ID, cela signifie qu'on l'a dépassé.
		if (tAdh[i]->idAdherent > idAdherent)
			return -1;
	}
	return -1;
}

/*
Nom : rechercheInfosJeux

Finalité : Fonction parcourant un tableau jusqu'à ce que le nom de jeu passé en paramètre soit trouvé. 
	Permet d'obtenir les informations du jeu correspondant.

Description générale :
	-Cette fonction parcours un tableau de jeux à l'aide d'une boucle for.
	-Si le nom de jeu passé en paramètre est trouvé dans le tableau, les données du jeu sont copiées dans une variable jouet de type
	Jeu et la position du jeu dans le tableau est retournée.
	-Si le nom du jeu recherché est supérieur au nom actuel du tableau, la fonction retourne -1 (on l'a dépassé).
	-La fonction retourne aussi -1 si le jeu n'est pas trouvé.

Paramètres en entrée : 
	-**tJeux : Un tableau de pointeurs de jeux
	-nbJeux le nombre de jeux (ou taille logique)
	-nomJeu[], chaîne de caractères. Le nom recherché.
	-*jouet : un pointeur vers une variable de type Jeu, où seront stockés les donnés du jeu recherché.  

Valeur retournée : La position du jeu recherché ou -1 si le nom n'a pas été trouvé dans le tableau.

Variables locales: 
	-i, la position du jeu une fois trouvé (compteur de boucle).
*/

int rechercheInfosJeux(Jeu **tJeux, int nbJeux, char nomJeu[], Jeu *jouet)
{
	int i;

	for (i = 0; i < nbJeux; i++)
	{
		if (strcmp(tJeux[i]->nomJeu, nomJeu) == 0)
		{
			//On copie le tout dans la structure passée par pointeur.
			jouet->idJeu = tJeux[i]->idJeu;
			jouet->nbExemplaire = tJeux[i]->nbExemplaire;
			strcpy(jouet->nomJeu, tJeux[i]->nomJeu);
			strcpy(jouet->typeJeu, tJeux[i]->typeJeu);
			return i;
		}

		//Comme les jeux sont triés par nom, cela veut dire qu'on l'a dépassé.
		if (strcmp(tJeux[i]->nomJeu, nomJeu) > 0)
			return -1;
	}

	return -1;
}

/*
Nom : rechercheInfosJeu2

Finalité : Fonction de recherche pour connaître les informations d'un jeu en fonction de son id.

Description générale : 
	-On parcour le tableau des jeux.
	-Si on trouve un jeu dont l'id est égal à l'id de jeu fournit en paramètre, alors on retourne sa position
	dans le tableau, et l'on assigne les informations dans la structure Jeu(pointeur), en paramètre.
	-Sinon on retourne -1.

Paramètres en entrée:
	-**tJeux tableau de pointeurs de la structure Jeu, contenant les informations des Jeux.
	-nbJeux, entier. Taille logique du tableau de pointeurs précédent.
	-idJeux, entier. Identifiant d'un jeux, utilisé pour la comparaison avec les id qui se trouvent dans le tableau. 
	-Jeu *jouet : pointeur sur une variable de type Jeu. Lorsque l'on a trouvée la valeur recherchée, on copie les informations dedans.

Valeur retournée : entier qui permet de savoir si la fonction s'est bien ou mal déroulée (-1 dans le cas où l'on ne trouve pas le jeu, 
son emplacement dans le tableau sinon).

Variables locales :
	int i, variable compteur qui va servir au parcour du tableau dans une boucle.
*/

int rechercheInfosJeu2(Jeu **tJeux, int nbJeux, int idJeux, Jeu *jouet)
{
	int i;

	for (i = 0; i < nbJeux; i++)
	{
		if (tJeux[i]->idJeu == idJeux)
		{
			//On copie le tout dans la structure passée par pointeur.
			jouet->idJeu = tJeux[i]->idJeu;
			jouet->nbExemplaire = tJeux[i]->nbExemplaire;
			strcpy(jouet->nomJeu, tJeux[i]->nomJeu);
			strcpy(jouet->typeJeu, tJeux[i]->typeJeu);
			return i;
		}
	}
	return -1;
}

/*
Nom:rechercheIdResa
  Description:Fonction récursive permettant de rechercher si l'id de réservation est différent de l'id rentrée a la place d'indice la fonction 
  ce stop uniquement lorsqur la liste est terminé ou que l'on a retrouvé l'indice
  Paramètre en entrée:
  -lr liste chaîné résarvation
  -indice entier retourné
	
  Paramètre en sortie:
  -int entier qui correspond a l'indice
  Constantes:Pas de constante dans le programme.
*/

int rechercheIdResa(ListeReservation lr, int indice)
{
	if (lr == NULL)
		return indice;

	if (lr->r.idResa != indice)
		return indice;

	rechercheIdResa(lr->suivant, indice + 1);
}

/*
Nom:rechercheInfoResa
  Description:Fonction de recherche récursive qui recherche toutes les informations de la structure, le copie dans le pointeur reserv si l'id Reservation
  envoyé en paramètre en fonction de l'id correspondant a la list. Si la liste est vide nous renvoyé 0 pour pouvoir réalisé un message dans la fonction l'appelant
  est renvoyé 1 si la fonction c'est bien déroulé et que touts les éléments soit bien copié. Nous rapellons enfin la fonction si la condition de recherche
  n'est pas validé en passant au maillon suivant  
  Paramètre en entrée:
  	-ListeReservation lr une liste de réservation lr ou des données cont être insérées.
  	-idResa correspond a l'id Reservation que l'on veut supprimer. 
  	-Reservation *reserv pointeur sur la structure Reservation qui pointe sur l'ensemble de la structure
  Paramètre en sortie:
  	-int est retourné si la fonction a bien tout copié ou alors si la liste est vide.
  Constantes:
  Aucune constante.
*/

int rechercheInfoResa(ListeReservation lr, int idResa, Reservation *reserv)
{
	if (lr == NULL)
		return 0;

	if (lr->r.idResa == idResa)
	{
		reserv->idJeux = lr->r.idJeux;
		reserv->idAdherent = lr->r.idAdherent;
		reserv->dateReservation.jour = lr->r.dateReservation.jour;
		reserv->dateReservation.mois = lr->r.dateReservation.mois;
		reserv->dateReservation.annee = lr->r.dateReservation.annee;
		return 1;
	}

	return rechercheInfoResa(lr->suivant, idResa, reserv);
}

/*
Nom:rechercherReservationPlusAncienne
  Description: Fonction récursive permettant de rechercher dans le fichier réservation l'id ayant la date la plus ancienne, si la liste
  est vide aucune reservation est disponible,il y a donc aucune recherche effectué cependant si la liste n'est pas vide il faut comparer
  2 date, pour pouvoir savoir qu'elle jeu choisir.
  Paramètre en entrée:
  -lr strucutre liste chaînée reservation
  -*dateResa pointeur sur la structure Date
  -*reserv pointeur sur la structure reservation
  -idJeux taille logique du fichier jeu
  Paramètre en sortie:
  -Aucun paramètre en sortie
  Constantes:Pas de constante dans le programme.
*/

void rechercherReservationPlusAncienne(ListeReservation lr, Emprunt **tEmp, int nbEmp, Date *dateResa, Reservation *reserv, int idJeux, Date dateActu)
{
	if (lr == NULL)
		return;

	if (lr->r.idJeux == idJeux && comparaisonDates(*dateResa, lr->r.dateReservation) == 0)
		if (compteNbEmp(tEmp, nbEmp, lr->r.idAdherent) < 3 && rechercheDateEmpruntDepasse(tEmp, nbEmp, lr->r.idAdherent, dateActu) != 1)
		{
			*reserv = lr->r;
			*dateResa = lr->r.dateReservation;
		}

	rechercherReservationPlusAncienne(lr->suivant, tEmp, nbEmp, dateResa, reserv, idJeux, dateActu);
}

/*
Nom:rechercheIdEmprunt
  Description:Fonction de recherche de l'id Emprunt la fonction est réalisé tant que le compteur est différent d'une valeur d'emprunt déjà existant.
  Lorsque la condition est réalisé renvoie la valeur de l'indice i ou alors lorsque la condition n'est jamais réalisé renvoie la fonction ou i c'est arrêté
  Paramètre en entrée:
	-**tEmp tableau de pointeur contenant les informations du fichier Emprunt 
	-nbEmp taille logique du fichier Emprunt
  Paramètre en sortie:
  -int entier renvoyé permettant de connaître la position dans le tableau tEmp de la valeur recherché.
  Variable local:
  -int i; compteur renvoyé, est la position ou la condition est réalisé, renvoie la taille logique si la condition n'est jamais respecté
*/

int rechercheIdEmprunt(Emprunt **tEmp, int nbEmp)
{
	int i;

	for (i = 0; i < nbEmp; i++)
	{
		if (i != tEmp[i]->idEmprunt)
			return i;
	}
	return i;
}

/*
Nom:rechercheEmprunt
  Description:Fonction de recherche de l'id Emprunt dans le tableau tEmp permet de renvoyé dans le pointeur emp toutes les données nécaissaire permettant de faire un récapitulatif des informations pour vérifier qu'il n'y ai aucune erreur, que la suppression ne soit pas fait par une erreur de saisie du client.
  Paramètre en entrée:
  	-idEmp correspond a l'id de l'emprunt du client
  	-*emp pointeur sur la structure Emprunt
	-nbEmp taille logique du fichier Emprunt
	-**tEmp tableau de pointeur de la structure Emprunt
  Paramètre en sortie:
  	-int est retourné la valeur de i qui correspond à la valeur ou l'id de l'emprunt correspond à celui du client	
Variables locales:
  -int i, variable qui servira de compteur permet de récupéré la ligne de l'id avec toutes ces informations.
*/

int rechercheEmprunt(Emprunt **tEmp, int nbEmp, int idEmp, Emprunt *emp)
{
	int debut = 0, milieu, fin = nbEmp - 1; 

	while (debut <= fin)
	{
		milieu = (debut + fin) / 2;

		if (tEmp[milieu]->idEmprunt == idEmp)
		{
			*emp = *tEmp[milieu];
			return milieu;
		}

		if (tEmp[milieu]->idEmprunt < idEmp)
			debut = milieu + 1;
		else
			fin = milieu - 1;
	}
	return -1;
}

/*
Nom:rechercheDateEmpruntDepasse
  Description:Fonction qui recherche si la date de l'emprunt est supérieur a 1 mois si c'est le cas alors le client ne pourra pas emprunter un nouveau jeu.
  Paramètre en entrée:
  	-idAdherent correspond a l'id de l'adhérent du client
	-nbEmp taille logique du fichier Emprunt
	-**tEmp tableau de pointeur de la structure Emprunt
	-dateActu élément de la structure date correspond a la date du jour (s'actualise automatique)
  Paramètre en sortie:
  	-int est retourné si le programme a eu une erreur lors de l'éxecution	
  Variables locales:
  -int i, variable qui servira de compteur permet de récupéré la ligne de l'id avec toutes ces informations.
*/


int rechercheDateEmpruntDepasse(Emprunt **tEmp, int nbEmp, int idAdherent, Date dateActu)
{
	int i;

	for (i = 0; i < nbEmp; i++)
	{
		if (tEmp[i]->idAdherent == idAdherent && validiteDateEmp(dateActu, tEmp[i]->dateEmprunt) == 1)
			return 1;
	}

	return 0;
}

/*
Nom:compteNbEmp
  Description:Fonction qui compte le nombre d'emprunt renvoie la variable compteur Paramètre en entrée:
  	-idAdherent correspond a l'id de l'adhérent du client
	-nbEmp taille logique du fichier Emprunt
	-**tEmp tableau de pointeur de la structure Emprunt
  Paramètre en sortie:
  	-int est retourné la valeur de i qui correspond à la valeur ou l'id de l'emprunt correspond à celui du client	
  Variables locales:
  -int i, variable qui servira de compteur permet de récupéré la ligne de l'id avec toutes ces informations.
  int compteur variable compteur
*/

int compteNbEmp(Emprunt **tEmp, int nbEmp, int idAdherent)
{
	int i, compteur = 0;

	for (i = 0; i < nbEmp; i++)
		if (tEmp[i]->idAdherent == idAdherent)
			compteur++;

	return compteur;
}
