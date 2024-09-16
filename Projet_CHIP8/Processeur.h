#ifndef PROCESSEUR_PROCESSEUR_H
#define PROCESSEUR_PROCESSEUR_H


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include "ram.h"
#include <display/display.h>
#include <display/sprite.h>
#include <keyboard/keyboard.h>
#include <misc/error.h>
#include <speaker/speaker.h>

/**
 * \brief Emulates a chip8 Processeur.
 *
 * Une structure Processeur doit etre initialisé et detruite en utilisant
 * les fonctions Init_Vide_Processeur et destroy_Processeur
 *
 */



/////////////////////////////////////////////////         STRUCTURES         ///////////////////////////////////////////////////////////////////////////////

struct Processeur {
                uint8_t* V;  //16 registres generaux
                uint16_t I;  // registre I pour les adresses
		uint16_t* Pile; // Pile first in first out
                unsigned int SP; //stack pointeur
		unsigned int DT;
		unsigned int ST;
                unsigned int PC; //compteur de programme
		struct RAM* ram;
		struct Display* display;
		struct Keyboard* keyboard;
		struct Speaker* speaker;
                
};

/**
 * \memberof Processeur
 * \brief    Initialise un processeur
 * \param    proc Le processeur.
 * \param    ram La ram de la machine
 * \param    display l'ecran 
 * \param    speaker le buzzer de son
 * \param    keyboard le clavier
 * \return   1 en cas d'echec 0 sinon
 */
int Init_Vide_Processeur(struct Processeur* proc,struct RAM* ram, struct Display* display,struct Speaker* speaker,struct Keyboard* keyboard);

/**
 * \memberof Processeur
 * \brief    detruit/desalloue le contenu d'un processeur
 * \param    proc Le processeur.
 */
void destroy_Processeur(struct Processeur* proc);

/**
 * \memberof Processeur
 * \brief    Clear the display
 * \param    proc Le processeur.
 * \return    1 en cas d'echec 0 sinon
 */
int Processeur_00E0(struct Processeur *proc); 

/**
 * \memberof Processeur
 * \brief    Retour d'un sous programme
 * \param    proc Le processeur.
 * \return    1 en cas d'echec 0 sinon
 */
int Processeur_00EE(struct Processeur *proc);

/**
 * \memberof Processeur
 * \brief    L'interpreteur donne la valeur nnn au PC (un jump)
 * \param    proc Le processeur.
 * \param    nnn l'adresse du jump
 * \return    1 en cas d'echec 0 sinon
 */
int Processeur_1nnn(struct Processeur *proc, uint16_t nnn);

/**
 * \memberof Processeur
 * \brief    L'interpreteur incremente SP, et ajoute la valeur de PC au sommet de SP ensuite l'interpreteur donne la valeur nnn au PC (appel d'une fonction dans une fonction)
 * \param    proc Le processeur.
 * \param    nnn l'adresse du jump
 * \return    1 en cas d'echec 0 sinon
 */
int Processeur_2nnn(struct Processeur *proc, uint16_t nnn);

/**
 * \memberof Processeur
 * \brief    Compare Vx et kk. SI ils sont egaux on increment PC de 2 (skip la prochaine instruction)
 * \param    proc Le processeur.
 *  \param    x indice d'un registre
 * \param    kk 
 * \return    1 en cas d'echec 0 sinon
 */
 int Processeur_3xkk( struct Processeur *proc, uint8_t x, uint8_t kk);

/**
 * \memberof Processeur
 * \brief    Compare Vx et kk. SI ils sont different on increment PC de 2 (skip la prochaine instruction)
 * \param    proc Le processeur.
 * \param    x indice d'un registre
 * \param    kk 
 * \return    1 en cas d'echec 0 sinon
 */
int Processeur_4xkk( struct Processeur *proc, uint8_t x, uint8_t kk);

/**
 * \memberof Processeur
 * \brief    Compare Vx et Vy. SI ils sont different on increment PC de 2 (skip la prochaine instruction)
 * \param    proc Le processeur.
 * \param    x indice d'un registre
 *  \param    y indice d'un registre
 * \return    1 en cas d'echec 0 sinon
 */
 int Processeur_5xy0( struct Processeur *proc, uint8_t x, uint8_t y);

/**
 * \memberof Processeur
 * \brief    Mets kk dans Vx
 * \param    proc Le processeur.
 * \param    x indice d'un registre
 *  \param    kk
 * \return    1 en cas d'echec 0 sinon
 */
int Processeur_6xkk( struct Processeur *proc, uint8_t x, uint8_t kk);

/**
 * \memberof Processeur
 * \brief    Ajoute kk a Vx
 * \param    proc Le processeur.
 * \param    x indice d'un registre
 *  \param    kk
 * \return    1 en cas d'echec 0 sinon
 */
int Processeur_7xkk( struct Processeur *proc, uint8_t x, uint8_t kk);

/**
 * \memberof Processeur
 * \brief    Mets Vy dans Vx
 * \param    proc Le processeur.
 * \param    x indice d'un registre
 *  \param    y indice d'un registre
 * \return    1 en cas d'echec 0 sinon
 */
int Processeur_8xy0(struct Processeur *proc, uint8_t x, uint8_t y);

/**
 * \memberof Processeur
 * \brief    stock dans Vx la valeur du ou bit a bit entre Vx et Vy
 * \param    proc Le processeur.
 * \param    x indice d'un registre
 *  \param    y indice d'un registre
 * \return    1 en cas d'echec 0 sinon
 */
int Processeur_8xy1(struct Processeur *proc, uint8_t x, uint8_t y);


/**
 * \memberof Processeur
 * \brief    stock dans Vx la valeur du et bit bit entre Vx et Vy
 * \param    proc Le processeur.
 * \param    x indice d'un registre
 *  \param    y indice d'un registre
 * \return    1 en cas d'echec 0 sinon
 */
 
int Processeur_8xy2(struct Processeur *proc, uint8_t x, uint8_t y);

/**
 * \memberof Processeur
 * \brief    stock dans Vx la valeur  du ou exclusif bit à bit entre Vx et Vy
 * \param    proc Le processeur.
 * \param    x indice d'un registre
 * \param    y indice d'un registre
 * \return   0 si tout s'est bien passé
 */
int Processeur_8xy3(struct Processeur *proc, uint8_t x, uint8_t y);

/**
 * \memberof Processeur
 * \brief    stock dans Vx la valeur de l'addition entre Vx et Vy et dans Vf si il y a un dépassement
 * \param    proc Le processeur.
 * \param    x indice d'un registre
 * \param    y indice d'un registre
 * \return   0 si tout s'est bien passé
 */
int Processeur_8xy4(struct Processeur *proc, uint8_t x, uint8_t y);

/**
 * \memberof Processeur
 * \brief    stock dans Vx la valeur de la soustraction entre Vx et Vy et dans Vf si il y a un dépassement
 * \param    proc Le processeur.
 * \param    x indice d'un registre
 * \param    y indice d'un registre
 * \return   0 si tout s'est bien passé
 */
int Processeur_8xy5(struct Processeur *proc, uint8_t x, uint8_t y);

/**
 * \memberof Processeur
 * \brief    stock la valeur du bit de poids fort de Vx dans Vf ensuite Vx est divisé par 2
 * \param    x indice d'un registre
 * \return   0 si tout s'est bien passé
 */
int Processeur_8xy6(struct Processeur *proc, uint8_t x,uint8_t y);


/**
 * \memberof Processeur
 * \brief    stock la valeur la valeur de soustraction de Vy-Vx dans Vx et met 1 dans Vf si Vy > Vx et 0 sinon ( si Vx = 15 alors on ne garde que la retenu et pas la soustraction)
 * \param    x indice d'un registre
 * \param    y indice d'un registre
 * \return   0 si tout s'est bien passé
 */
int Processeur_8xy7(struct Processeur *proc, uint8_t x, uint8_t y);


/**
 * \memberof Processeur
 * \brief    stock la valeur du bit de poids fort de Vx dans Vf ensuite Vx est multiplié par 2
 * \param    x indice d'un registre
 * \return   0 si tout s'est bien passé
 */
int Processeur_8xyE(struct Processeur *proc, uint8_t x,uint8_t y);

/**
 * \memberof Processeur
 * \brief    Skip la prochaine instruction si Vx est différent de Vy
 * \param    x indice d'un registre
 * \param    y indice d'un registre
 * \return   0 si tout s'est bien passé
 */
int Processeur_9xy0(struct Processeur *proc, uint8_t x, uint8_t y);

/**
 * \memberof Processeur
 * \brief    Met I à la position nnn en mémoire
 * \param    nnn entier
 * \return   0 si tout s'est bien passé
 */
int Processeur_Annn(struct Processeur *proc, uint16_t nnn);

/**
 * \memberof Processeur
 * \brief    Jump en mémoire à la position nnn + V0
 * \param    nnn entier
 * \return   0 si tout s'est bien passé
 */
int Processeur_Bnnn(struct Processeur *proc, uint16_t nnn);

/**
 * \memberof Processeur
 * \brief    Stock dans Vx le et logique entre kk et un entier random
 * \param    x indice d'un registre
 * \param    kk entier
 * \return   0 si tout s'est bien passé
 */
int Processeur_Cxkk(struct Processeur *proc, uint8_t x, uint16_t kk);

/**
 * \memberof Processeur
 * \brief    Sprite le display à l'addresse i en mémoire
 * \param    x indice d'un registre
 * \param    y indice d'un registre
 */
void Processeur_Dxyn(struct Processeur *proc, uint8_t x, uint8_t y, uint8_t nibble);

/**
 * \memberof Processeur
 * \brief    Skip la prochaine instruction si la touche de la valeur de Vx n'est pas pressé
 * \param    x indice d'un registre
 * \param    y indice d'un registre
 * \return   0 si tout s'est bien passé
 */
int Processeur_Ex9E(struct Processeur *proc, uint8_t x);

/**
 * \memberof Processeur
 * \brief    Skip la prochaine instruction si la touche de la valeur de Vx est pressé
 * \param    x indice d'un registre
 * \param    y indice d'un registre
 */
int Processeur_ExA1(struct Processeur* proc, uint8_t x);

/**
 * \memberof Processeur
 * \brief    La valeur de DT est placé dans Vx
 * \param    proc Le processeur.
 * \param    X l'indice du registre ou la valeur sera placé
 * \return   1 en cas d'echec 0 sinon
 */
int Processeur_Fx07(struct Processeur *proc, uint8_t x);

/**
 * \memberof Processeur
 * \brief    Attente de l'appuie d'une touche sur le clavier, sauvegarde cette touche dans Vx
 * \param    proc Le processeur.
 * \param    X l'indice du registre ou la valeur sera placé
 */
void Processeur_Fx0A(struct Processeur *proc, uint8_t x);

/**
 * \memberof Processeur
 * \brief    Remplace le delay timer par l'entier stocké Vx
 * \param    proc Le processeur.
 * \param    X l'indice du registre ou la valeur sera placé
 * \return   1 en cas d'echec 0 sinon
 */
int Processeur_Fx15(struct Processeur *proc, uint8_t x);

/**
 * \memberof Processeur
 * \brief    Remplace le sound timer par l'entier stocké Vx
 * \param    proc Le processeur.
 * \param    X l'indice du registre ou la valeur sera placé
 * \return   0 si tout s'est bien passé
 */
int Processeur_Fx18(struct Processeur *proc, uint8_t x);

/**
 * \memberof Processeur
 * \brief    Remplace I par I + l'entier stocké dand Vx
 * \param    proc Le processeur.
 * \param    X l'indice du registre ou la valeur sera placé
 * \return   0 si tout s'est bien passé et 1 sinon
 */
int Processeur_Fx1E(struct Processeur *proc, uint8_t x);


/**
 * \memberof Processeur
 * \brief    donne au registre I la position du sprite de V[x]
 * \param    proc Le processeur.
 * \param    X l'indice du registre 
 * \return   0 si tout s'est bien passé et 1 sinon
 */
int Processeur_Fx29(struct Processeur *proc, uint8_t x);
/**
 * \memberof Processeur
 * \brief    Ecrit en mémoire à l'adresse I+2, I+1, I la representation en base 10 de l'entier stocké dans Vx
 * \param    proc Le processeur.
 * \param    X l'indice du registre ou la valeur sera placé
 * \return   0 si tout s'est bien passé et 1 sinon
 */
int Processeur_Fx33(struct Processeur *proc, uint8_t x);

/**
 * \memberof Processeur
 * \brief    Ecrit en mémoire à partir de l'adresse I les registres V0 jusqu'à Vx
 * \param    proc Le processeur.
 * \param    X l'indice du registre ou la valeur sera placé
 * \return   0 si tout s'est bien passé et 1 sinon
 */
int Processeur_Fx55(struct Processeur *proc, uint8_t x);

/**
 * \memberof Processeur
 * \brief    Stock dans les registres V0 jusqu'à Vx ce qui est écrit en mémoire à partir de l'adresse I
 * \param    proc Le processeur.
 * \param    X l'indice du registre ou la valeur sera placé
 * \return   0 si tout s'est bien passé et 1 sinon
 */
int Processeur_Fx65(struct Processeur *proc, uint8_t x);

/**
 * \memberof Processeur
 * \brief    recupere en memoire l'instruction pointé par PC
 * \param    proc Le processeur.
 * \return   l'instruction décodé sur 16 bits
 */
uint16_t fetch(struct Processeur *proc);

/**
 * \memberof Processeur
 * \brief    Decode l'instruction en parametre et appele la bonne fonction
 * \param    proc Le processeur.
 * \param instruction un entier en 16 bit qui represente une instruction
 */
void decode_execute(struct Processeur *proc,uint16_t instruction);

/**
 * \memberof Processeur
 * \brief    appele les fonction fetch et decode_execute et incremente PC
 * \param    proc Le processeur.
 */
void fetch_decode_execute(struct Processeur *proc);


#endif