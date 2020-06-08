FloatingFlag
================

Projet consiste à faire sur la basse des systémes masse-ressort un modéle du drapeau flottant dans le vent. Ce projet est programmé en C++ à l'aide de la librairie GLEW et GLUT (freeGlut) d'OpenGL.

Installation
============

## Dependence
	* Nécessite la prise en charge d'OpenGL et les bibliothèques GLEW et GLUT (paquets libglew-dev et freeglut3-dev dans Debian).
	* 'GLUT' https://www.opengl.org/resources/libraries/glut/
    * 'GLEW' http://glew.sourceforge.net/

## Compilation tester
    * g++ Version : 6.3.0
    * OpenGL Version : 3.0 Mesa 13.0.6
	* GLEW Version : 2.0.0
	* freeglut3 Version : 2.8.1-3


Utilisation
===========

## Exécutable
    * Créer un dossier "bin" dans le même répertoire que les dossiers "src" et "include" si necéssaire.
    * make au niveau des dossiers "src" et "include".
    * ./Flag pour lancer l'exécutable.
    
## Interface du jeu
	* Au lancement du programme un menu aparait sur le terminal :
		1. France ,
		2. Canada,
		3. Tunisie,
		4. Nouvelle Zélande,
		5. Etat-Unis.
	* Faire un choix en indiquant le chiffre parmi ce qui est proposé ci-dessus pour le voir apparaitre.

## Commandes du jeu
	* Mouvement de la balle :
		* clique "s" vers le bas,
		* clique "z" vers le haut,
		* clique "d" vers la droite,
		* clique "q" vers la gauche,
		* clique "f" en profondeur vers le bas,
		* clique "r" en profondeur vers le haut.
	* Mouvement de la caméra :
		* clique "↑" vers le haut,
		* clique "↓" vers le bas,
		* clique "→" vers la droite,
		* clique "←" vers la gauche.

Notes
=====

## Authors
    * BEN HAMOUDA Amel (Université Paris-Est Marne-la-Vallee, France)

