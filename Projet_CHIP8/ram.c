#include "ram.h"


//return 1 en cas d'erreur 0 si l'init a reussit
int RAM_Init(struct RAM* m){
        m->tableau=malloc(4096*sizeof(uint8_t));
        if(!m->tableau){
                printf("Erreur lors de l'allocation du tableau");
                return 1;
        }
        return 0;
        
}


void RAM_destroy (struct RAM* m){
        free(m->tableau);
}


int RAM_write (struct RAM* m, uint8_t value, unsigned int  pos){
        m->tableau[pos] = value;
        return 0;
}

uint8_t RAM_read(struct RAM* m, unsigned int  pos){
	return m->tableau[pos];
}

void RAM_print (struct RAM* m,uint8_t pos, uint8_t posfinal){
        for(unsigned int i=pos;i<posfinal;i+=1){//pas550 mais test ici
                printf("La position de %d  :%d\n",i,m->tableau[i]);
        }
}



