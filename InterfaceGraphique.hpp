// DIRECTIVES
#ifndef INTERFACEGRAPHIQUE_HPP
#define INTERFACEGRAPHIQUE_HPP

// LIBRAIRIES
#include <QApplication> // QApplication est l'include de base de tout programme Qt
#include <QObject> // QObject est la classe de base de tous les objets sous Qt. La méthode connect() nous sera particulièrement utile pour les signaux et les slots
#include <QtWidgets> // QtWidgets est un module qui nous permettera d'afficher nos fenêtres
#include <QPushButton> // QPushButton nous permet de créer des objets QPushButton étant tout simplement des boutons
#include <QRadioButton>
/* QRadioButton nous permettera de créer des boutons radio. Les boutons radio nous seront utile dans la création du menu car ils permetteront de présenter sous la
forme d'un QCM, des choix à l'utilisateur de sélectionner ce qu'il désire faire.
*/
#include <QLabel> // QLabel est utilisé pour afficher du texte ou une image. Cette classe nous sera utile pour l'affichage de l'échéancier
#include "Moteur.hpp" // Pour utiliser la classe Moteur
#include "GestionnaireDeFichiers.hpp" // Pour utiliser la classe GestionnaireDeFichiers

// CLASSE
class InterfaceGraphique
{
    private:
    // VARIABLES

    public:
    // CONSTRUCTEURS
    InterfaceGraphique()
    {}

    // DESTRUCTEUR
    ~InterfaceGraphique()
    {}

    // METHODES
    // Cette fonction aura pour but de créer un menu à l'aide des QRadioButton.
    affichage_menu()
    {}

    /*
    Cette fonction servira à l'affichage de l'échéancier sous forme de texte.
    Nous avons comme argument un Moteur, qui nous est envoyé par l'Echéancier, comportant toutes les infos nécéssaires à l'affichage de ce dernier.
    */
    affichage_echeancier(Moteur M)
    {}

    /*
    Cette fonction évaluera si un bouton a été cliqué.
    */
    bouton_clic(QPushButton Bouton);

    /*
    Cette fonction a pour but de créer un bouton retour afin que l'utilisateur puisse revenir au menus principal.
    */
    creation_retour();
}

#endif