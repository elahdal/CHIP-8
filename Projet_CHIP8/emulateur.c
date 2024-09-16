



#include "emulateur.h"



struct EMULATEUR*  emulateur_init(){
        struct EMULATEUR* emu=malloc(sizeof(struct EMULATEUR));
        emu->ram=malloc(sizeof(struct RAM));
        RAM_Init(emu->ram);
                
	emu->speaker = malloc(sizeof(struct Speaker));
	Speaker_init(emu->speaker);
                
	emu->display = malloc(sizeof(struct Display));
	Display_init(emu->display, 10);
                
	emu->keyboard =malloc(sizeof(struct Keyboard));
	Keyboard_init(emu->keyboard);
                
	emu->proc= malloc(sizeof(struct Processeur));
	Init_Vide_Processeur(emu->proc, emu->ram,emu->display, emu->speaker, emu-> keyboard);
	
	if( emu->display && emu->proc && emu->ram && emu->speaker && emu->keyboard){
		return emu;
	}
	printf("Erreur lors de la creation de l'emulateur");
        return NULL;
}

int emulateur_destroy(struct EMULATEUR* emu){
	if (emu){
		if (emu->ram && emu->speaker && emu->display  && emu->keyboard){
			RAM_destroy(emu->ram);
			Speaker_destroy (emu->speaker);
			Keyboard_destroy(emu->keyboard);
			Display_destroy(emu->display);
		}
		free(emu);
		return 0;
	}
	return 1;
}




int emulateur_load(struct EMULATEUR* emu, char* filename){
	FILE* ROM = fopen(filename,"rb");
	if (ROM != NULL){
		emu->proc->PC=0x200;
		uint8_t code;
		unsigned int  pos=0x200;
		while ( fread(&code, sizeof(uint8_t) ,1, ROM)){
			RAM_write(emu->ram, code, pos);
			pos++;
			}
		fclose(ROM); 
	}else{
		printf("Impossible d'ouvrir le fichier.\n");
		return 1;
	}

	return 0;
}

void emulateur_loop(struct EMULATEUR* emu){

	uint32_t ancien_temps = 0;
	const uint32_t FPS = 1000/60; // 60Hz
	Uint32 temps_ecoule;
	Uint32 temps_boucle;
	unsigned int uicpt=0;
	while (1)
	{	
		SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT); 
		
		if (uicpt==1){
			SDL_Delay(1); // delay de 1 ou 2 millisecondes alterné
			uicpt = 0;
		}else {
			SDL_Delay(2); // delay de 1 ou 2 millisecondes alterné
			uicpt = 1;
		}
		fetch_decode_execute(emu->proc); // instruction
		
		
		temps_boucle = SDL_GetTicks();
		temps_ecoule = temps_boucle - ancien_temps; // temps ecoule depuis la derniere decrementation
		if (temps_ecoule > FPS)
		{

			if(emu->proc->DT >= temps_ecoule/FPS){
				emu->proc->DT -= temps_ecoule/FPS; // decremente le delay timer en respectant le temps reel ecoulé
				}			
			else emu->proc->DT = 0;
			
			if(emu->proc->ST >= temps_ecoule/FPS){
				emu->proc->ST -= temps_ecoule/FPS; // decremente le sound timer en respectant le temps reel ecoulé
			}
			else emu->proc->ST = 0;
			
			 if (emu->proc->ST > 0) Speaker_on(emu->proc->speaker); // le buzzer sonne s'il n'est pas a zero
			else if (emu->proc->ST ==0) Speaker_off(emu->proc->speaker);

			ancien_temps = temps_boucle - temps_ecoule / FPS; // fixe ce temps
			Display_update(emu->display); 
		}
	}
}



int main () {
        if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER|SDL_INIT_AUDIO)) {
                errcode = SDL;
        }
        else {
                printf("The SDL library has been initialized successfully.\n");
		struct EMULATEUR* emu =emulateur_init();

		if (emulateur_load(emu,"/home/yass/Documents/projet_chip8/Projet_CHIP8/Projet_CHIP8/Rom_test/Tetris [Fran Dachille, 1991].ch8")==0) { //6-keypad.ch8q
			printf("The ROM 2-ibm-logo.ch8 has been loaded.\n");
			printf("Run...\n");
		}
		//  1-chip8-logo.ch8  2-ibm-logo.ch8  3-corax+.ch8 4-flags.ch8  5-quirks.ch8  6-keypad.ch8  7-beep.ch8  Tetris [Fran Dachille, 1991].ch8
		emulateur_loop(emu);
		emulateur_destroy(emu);
                SDL_Quit();
	}
        if (errcode != QUIT) {
                fprintf(stderr,"The program has terminated abnormally (errcode=%s)\n",errorstr());
                return 1;
        }
        return 0;
}
