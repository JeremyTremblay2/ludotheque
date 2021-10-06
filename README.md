# Ludotheque
Un projet de ludothèque réalisé en C.

## Description détaillée

Cette ludothèque sans interface graphique gère le prêt de jeux de plusieurs types (jeux de construction, jeux de cartes, jeux de logique, jeux de plateau ...). Chaque jeu est disponible en plusieurs exemplaires. Pour pouvoir emprunter des jeux il faut être adhérent à la ludothèque (15€ par personne pour une année). À la date anniversaire de son adhésion, l’adhérent doit payer de nouveau une adhésion, sinon il ne peut plus emprunter. Chaque adhérent peut emprunter jusqu'à trois jeux en même temps pour une durée maximale de 1 mois. 

## Fonctionnalités implantées

- [x] Affichage de la liste des jeux disponibles triée par type de Jeux, puis par ordre alphabétique de leur nom
- [x] Affichage de la liste des emprunts en cours en mentionnant : le nom du jeu, l’identité de l’emprunteur ainsi que la date de l’emprunt
- [x] Affichage de la liste des réservations pour un jeu donné
- [x] Saisie et enregistrement d’un nouvel emprunt ou d’une réservation
- [x] Création de compte pour les nouveaux adhérents et renouvellement de leur abonnement
- [x] Enregistrement de réservation si le jeu est indisponible à l'emprunt
- [x] Retour d'un jeu et distribution à l'éventuel adhérent l'ayant réservé
- [x] Annulation de réservations
- [x] Saisies controlées
- [x] Persistance des données dans des fichiers textuels et binaires

## Eléments importants du code

- [x] Structures de données variées (listes chainées et tableaux de pointeurs)
- [x] Tri rapide (Quicksort), tri à bulle
- [x] Recherche itérative, recherche dichotomique
- [x] Manipulations de fichiers binaires et textuels
- [x] Découpage du code

## Comment lancer le projet

Placer les fichiers dans un répertoire puis exécuter la commande à l'aide de GCC, qui va venir compiler les fichiers :  
* gcc *.c -o Ludotheque

Puis pour l'éxécution :
* ./Ludotheque

## Informations complémentaires

Ce projet fut réalisé durant le premier semestre de DUT informatique, dans le cadre du cours de __Structures de données__.
Lors de ce projet, j'étais en trinôme avec WISSOCQ Maxime et COUDOUR Adrien.
