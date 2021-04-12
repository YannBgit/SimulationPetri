// DIRECTIVES
#ifndef INTERFACEGRAPHIQUE_HPP
#define INTERFACEGRAPHIQUE_HPP

// LIBRAIRIES

#include <QApplication>
//QApplication est l'include de base de tout programme Qt.

#include <QObject>
//QObject est la classe de base de tous les objets sous Qt.
//La méthode connect() nous sera particulièrement utilse pour les signaux et les slots.

#include <QtWidgets>
//QtWidgets est un module qui nous permettera d'afficher nos fenêtres.

#include <QPushButton>
//QPushButton nous permet de créer des objets QPushButton étant tout simplement des boutons.

#include <QRadioButton>
//QRadioButton nous permettera de créer des boutons radio.
//Les boutons radio nous seront utile dans la création du menu car ils permetteront de 
//présenter sous la forme d'un QCM, des choix à l'utilisateur de sélectionner ce qu'il 
//désire faire.

#include <QLabel>
//QLabel est utilisé pour afficher du texte ou une image. Cette classe nous sera utile pour l'affichage 
//de l'échéancier.

#include "Echeancier.hpp"
//Nous avons besoin de cet include pour obtenir le moteur que l'on devra afficher affichage_echancier.


//LISTE DES FONCTIONS

    affichage_menu();
    //Cette fonction aura pour but de créer un menu à l'aide des QRadioButton.
    affichage_echeancier(Moteur m);
    //Cette fonction servira d'affichage de l'échéancier sous forme de texte.
    //Nous avons comme argument un Moteur, qui nous est envoyé par l'Echéancier, comportant toutes 
    //les infos nécéssaires à l'affichage de ce dernier.
    bouton_clic(QPushButton bouton);
    //Cette fonction évaluera si un bouton a été cliqué.
    creation_retour();
    //Cette fonction a pour but de créer un bouton retour afin que l'utilisateur puisse revenir 
    //au menus principal.
    

#endif
