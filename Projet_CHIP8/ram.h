#ifndef RAM_RAM_H
#define RAM_RAM_H



#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


/**
 * \brief Emulates a 4KB (4,096 bytes) RAM.
 *
 * Une structure RAM doit etre initialisé et detruite en utilisant
 * les fonctions RAM_Init et RAM_destroy
 *
 */

/////////////////////////////////////////////////         STRUCTURES         ///////////////////////////////////////////////////////////////////////////////


struct RAM  {
        uint8_t* tableau;
};


/////////////////////////////////////////////////        FONCTIONS          ///////////////////////////////////////////////////////////////////////////////


/**
 * \memberof RAM
 * \brief    Initialise une RAM
 * \param    m une RAM
 * \return   1 si il n'y a aucun probleme et 0 sinon
 */
int RAM_Init(struct RAM* m);


/**
 * \memberof RAM
 * \brief    Detruit une RAM
 * \param    m la ram
 */
void RAM_destroy(struct RAM *m);


/**
 * \memberof RAM
 * \brief    Ecrit dans une RAM une valeur donné à une position donnée
 * \param    m la ram
 * \param    value la valeur à écrire
 * \param    pos la position
 * \return   0 si tout s'est bien passé
 */
int RAM_write(struct RAM* m, uint8_t value, unsigned int pos);


/**
 * \memberof RAM
 * \brief    Lit dans une RAM à une position donnée
 * \param    m la ram
 * \param    pos la position
 * \return   la valeur lue
 */
uint8_t RAM_read(struct RAM* m, unsigned int  pos);


/**
 * \memberof RAM
 * \brief    Affiche le continue d'une RAM entre deux positions données
 * \param    m la ram
 * \param    pos la position de départ
 * \param    pos la position finale
 * \return   la valeur lue
 */
void  RAM_print (struct RAM* m,uint8_t pos, uint8_t posfinal);

#endif