




#ifndef EMULATEUR_EMULATEUR_H
#define EMULATEUR_EMULATEUR_H


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> 
#include <unistd.h>
#include <time.h>
#include "ram.h"
#include "Processeur.h"
#include <display/display.h>
#include <display/sprite.h>
#include <keyboard/keyboard.h>
#include <misc/error.h>
#include <speaker/speaker.h>


/**
 * \brief Simule une machine.
 *
 * Une structure EMULATEUR doit etre initialisé et detruite en utilisant
 * les fonctions emulateur_init et emulateur_destroy
 *
 */


/////////////////////////////////////////////////         STRUCTURES         ///////////////////////////////////////////////////////////////////////////////


struct EMULATEUR {
	struct RAM* ram;
	struct Processeur* proc;
	struct Display* display;
	struct Speaker* speaker;
	struct Keyboard* keyboard;
};
/**
 * \memberof EMULATEUR
 * \brief    Initialise un emulateur
 * \return   un emulateur initialisé si il n'y a aucun probleme et NULL sinon
 */
struct EMULATEUR*  emulateur_init();


/**
 * \memberof EMULATEUR
 * \brief    Detruit un emulateur
 * \param    emu l'emulateur
 * \return   1 en cas d'echec 0 sinon
 */
int emulateur_destroy(struct EMULATEUR* emu);

/**
 * \memberof EMULATEUR
 * \brief    Charge une ROM depuis un fichier et la stock dans la memoire a l'adresse 0x200
 * \param    emu l'emulateur
 * \param    filename le nom du fichier à charger
 * \return   1 en cas d'echec 0 sinon
 */
int emulateur_load(struct EMULATEUR* emu, char* filename);


#endif