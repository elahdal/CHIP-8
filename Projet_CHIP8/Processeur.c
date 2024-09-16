#include "Processeur.h"

int Init_Vide_Processeur(struct Processeur* proc, struct RAM* ram, struct Display* display, struct Speaker* speaker, struct Keyboard* keyboard){
        proc->V = calloc(16,sizeof(uint8_t));
        proc->Pile = malloc(16*sizeof(uint16_t));
        proc ->display = display;
	proc ->speaker = speaker;
	proc ->keyboard = keyboard;
	proc->ram = ram;
	proc->ST=0;
	proc->DT=0;
	proc->SP=1;
	proc->I=0;
	proc->PC=0x200;
	
        if(proc->V && proc->Pile){
                        return 0;
        }
	printf("Erreur lors de l'allocation du tableau des registres");
	return 1;
}


void destroy(struct Processeur *proc){
        free(proc->V);
        free(proc->Pile);
}


int Processeur_00E0(struct Processeur *proc){
        return Display_CLS (proc->display);
}


int Processeur_00EE(struct Processeur *proc){
                if(proc->SP == 1){
                        return 1;
                }
                proc->PC=proc->Pile[proc->SP];
                proc->SP -=1;
                return 0;
}


int Processeur_1nnn(struct Processeur *proc, uint16_t nnn){
        if (nnn>4096){
                return 1;
        }
        proc->PC = nnn;
        return 0;
}


int Processeur_2nnn(struct Processeur *proc, uint16_t nnn){
        if (nnn>4096){
                return 1;
        }
        proc->SP += 1;
	proc->Pile[proc->SP] = proc->PC;
        proc->PC = nnn;
        return 0;
}


int Processeur_3xkk( struct Processeur *proc, uint8_t x, uint8_t kk){
        if (proc->V[x] == kk){
                proc->PC +=2;
        }
        return 0;                
}


int Processeur_4xkk( struct Processeur *proc, uint8_t x, uint8_t kk){
        if (proc->V[x] != kk){
                proc->PC +=2;
        }
        return 0;
}


int Processeur_5xy0( struct Processeur *proc, uint8_t x, uint8_t y){
        if (proc->V[x] == proc->V[y]){
                proc->PC +=2;
        }
        return 0;
}


int Processeur_6xkk( struct Processeur *proc, uint8_t x, uint8_t kk){
        proc->V[x] = kk;
        
        return 0;
}


int Processeur_7xkk( struct Processeur *proc, uint8_t x, uint8_t kk){
        proc->V[x] += kk;
        
        return 0;
}



int Processeur_8xy0(struct Processeur *proc, uint8_t x, uint8_t y){
        proc->V[x] = proc->V[y];
        return 0;
}


int Processeur_8xy1(struct Processeur *proc, uint8_t x, uint8_t y){
        proc->V[x] = proc->V[x] | proc->V[y];
	proc->V[15]=0;
        return 0;
}


int Processeur_8xy2(struct Processeur *proc, uint8_t x, uint8_t y){
	proc->V[x] = proc->V[x] & proc->V[y];
	proc->V[15] = 0;
	return 0;
}

int Processeur_8xy3(struct Processeur* proc,uint8_t x,uint8_t y){
        proc->V[x]=proc->V[x] ^ proc->V[y];
	proc->V[15] = 0;
        return 0;
}

int Processeur_8xy4(struct Processeur *proc, uint8_t x, uint8_t y){
        if( proc->V[x]+proc->V[y] > 255){
		proc->V[x] += proc->V[y];
                proc->V[15] = 1;
        }
        else {
		proc->V[x] += proc->V[y];
                proc->V[15] = 0;
        }
        return 0;
}

int Processeur_8xy5(struct Processeur *proc,uint8_t x,uint8_t y){
	if (proc->V[x] >= proc->V[y]){
		proc->V[x]-=proc->V[y];
		proc->V[15]=1;
	}else{
		proc->V[x]-=proc->V[y];
		proc->V[15]=0;
	}
	return 0;

}

int Processeur_8xy6(struct Processeur *proc,uint8_t x,uint8_t y){
	uint8_t temp;
	
	proc->V[x]=proc->V[y];
	temp=proc->V[x];
	proc->V[x]=proc->V[x]>>1;
	proc->V[15]=temp & 1;
        return 0;

}

int Processeur_8xy7(struct Processeur *proc,uint8_t x,uint8_t y){ // SUBN
	if (proc->V[y] >= proc->V[x]){
			proc->V[x]=proc->V[y] - proc->V[x];
			proc->V[15]=1;
		}else{
			proc->V[x]=proc->V[y] - proc->V[x];
			proc->V[15]=0;
		}
	return 0;
}

int Processeur_8xyE(struct Processeur *proc,uint8_t x,uint8_t y ){
	proc->V[x]=proc->V[y];
        if ((proc->V[x] & 1<<7) != 0){
		proc->V[x]=proc->V[x]<<1;
		proc->V[15]=1;
        }else {
		proc->V[x]=proc->V[x]<<1;
		proc->V[15]=0;
        }
       
        return 0;

}

int Processeur_9xy0( struct Processeur *proc, uint8_t x, uint8_t y){
        if (proc->V[x] != proc->V[y]){
                proc->PC +=2;
        }
        return 0;
}
        
int Processeur_Annn(struct Processeur *proc, uint16_t nnn){
        if (nnn>4096){
                return 1;
        }
        proc->I = nnn;
        return 0;
}

int Processeur_Bnnn(struct Processeur *proc, uint16_t nnn){
        if (proc->V[0] + nnn>4096){
                return 1;
        }
        proc->PC = proc->V[0] + nnn;
        return 0;
}

int Processeur_Cxkk(struct Processeur *proc, uint8_t x, uint16_t kk){
        srand(time(NULL));
        int r = rand();
        r = r & kk;
        proc->V[x] = r;
        return 0;
}


void Processeur_Dxyn(struct Processeur *proc, uint8_t x, uint8_t y, uint8_t nibble){
        struct Sprite sprite;
        Sprite_init (&sprite, nibble);
        for (unsigned int i = 0; i < nibble;i++){
                Sprite_add(&sprite,RAM_read(proc->ram, proc->I+i));
        }
        Display_DRW(proc->display,&sprite,proc->V[x],proc->V[y],&proc->V[15]);
        Sprite_destroy(&sprite);
}


int Processeur_Ex9E(struct Processeur* proc, uint8_t x){
        if (Keyboard_get (proc->keyboard,proc->V[x])==KEY_DOWN){
                proc->PC+=2;
        }
        return 0;
}


int Processeur_ExA1(struct Processeur* proc, uint8_t x){
        if (Keyboard_get (proc->keyboard,proc->V[x])==KEY_UP){
                proc->PC+=2;
        }
	return 0;
}



/**
 * \memberof Processeur
 * \brief    La valeur de DT est placé dans Vx 
 * \param    proc Le processeur.
 * \param    X l'indice du registre ou la valeur sera placé
 * \return   1 en cas d'echec 0 sinon
 */
int Processeur_Fx07(struct Processeur* proc,uint8_t x){
        proc->V[x]=proc->DT;
        return 0;
}  

void Processeur_Fx0A(struct Processeur *proc, uint8_t x){
        Keyboard_wait (proc->keyboard, &proc->V[x]);
}

    

int Processeur_Fx15(struct Processeur *proc, uint8_t x){
        proc->DT= proc->V[x];
	return 0;
}

int Processeur_Fx18(struct Processeur *proc,uint8_t x){
	proc->ST=proc->V[x];
        return 0;
}

int Processeur_Fx1E(struct Processeur *proc,uint8_t x){
        proc->I+=proc->V[x];
        return 0;
}

int Processeur_Fx29(struct Processeur *proc, uint8_t x){
	struct Sprite sprite;
	Sprite_init (&sprite, 20);
	return Sprite_get (&sprite, proc->I, &proc->V[x]);
}


int Processeur_Fx33(struct Processeur *proc,uint8_t x){
        int centaines;
	int dizaines;
	int unites; 
	
	unites = proc->V[x] % 10;
	dizaines = (proc->V[x] % 100 - unites) /10;
	centaines = (proc->V[x] % 1000 - dizaines*10 -unites) /100;
	
	RAM_write(proc->ram,centaines,proc->I);
	RAM_write(proc->ram,dizaines,proc->I+1);
	RAM_write(proc->ram,unites,proc->I+2);
	
        return 0;
}

int Processeur_Fx55(struct Processeur *proc,uint8_t x){
        for(unsigned int uiboucle =0; uiboucle<=x ;uiboucle++){
                RAM_write(proc->ram,proc->V[uiboucle],proc->I+uiboucle);
        }
	proc->I+=x+1; 
        return 0;
}

int Processeur_Fx65(struct Processeur *proc,uint8_t x){
        for(unsigned int uiboucle=0; uiboucle<=x ;uiboucle++){
                proc->V[uiboucle]=RAM_read(proc->ram,proc->I+uiboucle);
        }
	proc->I+=x+1; 
        return 0;
}

uint16_t fetch(struct Processeur *proc){
        uint8_t part1 = RAM_read(proc->ram,proc->PC);
        uint8_t part2 = RAM_read(proc->ram,proc->PC+1);
        uint16_t instruction;
        instruction = ((uint16_t) part1 << 8) + part2;
        return instruction;
}

void decode_execute(struct Processeur *proc,uint16_t instruction){
        if((instruction & 0xFFFF) == 0x00E0){
		Processeur_00E0(proc);
	}
	else if ((instruction & 0xFFFF) == 0x00EE){
		Processeur_00EE(proc);
	}      
	else if((instruction & 0xF000) == 0x1000) {
                Processeur_1nnn(proc, instruction & 0x0FFF);
        }
        else if((instruction & 0xF000) == 0x2000) {
                Processeur_2nnn(proc, instruction & 0x0FFF);
        }
        else if ((instruction & 0xF000) == 0x3000) {
                uint16_t x = (instruction & 0x0F00)>>8;
                Processeur_3xkk(proc,(uint8_t) x ,instruction & 0x00FF);
        }
        else if ((instruction & 0xF000) == 0x4000){
                uint16_t x = (instruction & 0x0F00)>>8;
                Processeur_4xkk(proc,(uint8_t) x, (uint8_t) (instruction & 0x00FF));
        }
        else if((instruction & 0xF00F) == 0x5000){
                uint16_t x = (instruction & 0x0F00)>>8;
                Processeur_5xy0(proc,(uint8_t) x,(uint8_t) ((instruction & 0x00F0) >> 4));
        }
        else if((instruction & 0xF000) == 0x6000){
                uint16_t x =(instruction & 0x0F00)>>8;
                Processeur_6xkk(proc,(uint8_t) x, (uint8_t)(instruction & 0x00FF));
        }
        else if((instruction & 0xF000) == 0x7000){
                uint16_t x =(instruction & 0x0F00)>>8;
                Processeur_7xkk(proc, (uint8_t) x, (uint8_t)(instruction & 0x00FF));
        }
        else if((instruction & 0xF00F) == 0x8000){
                uint16_t x = (instruction & 0x0F00) >> 8;
                uint16_t y = (instruction & 0x00F0) >> 4;
                Processeur_8xy0(proc,(uint8_t) x,(uint8_t)y);
        }
        else if((instruction & 0xF00F) == 0x8001){
                uint16_t x = (instruction & 0x0F00) >> 8;
                Processeur_8xy1(proc, (uint8_t) x, (uint8_t) ((instruction & 0x00F0) >> 4));
        }
        else if((instruction & 0xF00F) == 0x8002){
                uint16_t x = (instruction & 0x0F00) >> 8;
                Processeur_8xy2(proc, (uint8_t) x, (uint8_t) ((instruction & 0x00F0 )>> 4));
        }
        else if((instruction & 0xF00F) == 0x8003){
                uint16_t x = (instruction & 0x0F00) >> 8;
                Processeur_8xy3(proc, (uint8_t) x, (uint8_t) ((instruction & 0x00F0 )>> 4));
        }
        else if((instruction & 0xF00F) == 0x8004){
                uint16_t x = (instruction & 0x0F00) >> 8;
                Processeur_8xy4(proc, (uint8_t) x, (uint8_t) ((instruction & 0x00F0 )>> 4));
        }
        else if((instruction & 0xF00F) == 0x8005){
                uint16_t x = (instruction & 0x0F00) >> 8;
                Processeur_8xy5(proc, (uint8_t) x, (uint8_t) ((instruction & 0x00F0) >> 4));
        }
        else if((instruction & 0xF00F) == 0x8006){
                uint16_t x = (instruction & 0x0F00) >> 8;
                Processeur_8xy6(proc, (uint8_t) x,(uint8_t) ((instruction & 0x00F0) >> 4));
        }
        else if((instruction & 0xF00F) == 0x8007){
                uint16_t x = (instruction & 0x0F00) >> 8;
                Processeur_8xy7(proc, (uint8_t) x, (uint8_t) ((instruction & 0x00F0) >> 4));
        }
        else if((instruction & 0xF00F) == 0x800E){
                uint16_t x = (instruction & 0x0F00) >> 8;
                Processeur_8xyE(proc, (uint8_t) x,(uint8_t) ((instruction & 0x00F0) >> 4));
        }
        else if((instruction & 0xF00F) == 0x9000){
                uint16_t x = (instruction & 0x0F00) >> 8;
                Processeur_9xy0(proc, (uint8_t) x, (uint8_t) ((instruction & 0x00F0) >> 4));
        }
        else if((instruction & 0xF000) == 0xA000){
                Processeur_Annn(proc,instruction & 0x0FFF);
        }
        else if((instruction & 0xF000) == 0xB000){
                Processeur_Bnnn(proc,instruction & 0x0FFF);
        }
        else if((instruction & 0xF000) == 0xC000){
                uint16_t x = (instruction & 0x0F00) >> 8;
                uint8_t kk = instruction;
                Processeur_Cxkk(proc, (uint8_t) x, kk);
        }
	else if((instruction & 0xF000) ==  0xD000){
		Processeur_Dxyn(proc, (uint8_t)((instruction & 0x0F00) >> 8), (uint8_t)((instruction & 0x00F0) >> 4), (uint8_t)(instruction & 0x000F));
	}
	else if((instruction & 0xF0FF) ==  0xE09E){
		uint16_t x = (instruction & 0x0F00) >> 8;
		Processeur_Ex9E(proc, (uint8_t) x);
	}
                
	else if((instruction & 0xF0FF) ==  0xE0A1){
		uint16_t x = (instruction & 0x0F00) >> 8;
		Processeur_ExA1(proc, (uint8_t) x);
	}
                        
                
        else if ((instruction & 0xF0FF ) == 0xF007){
		uint16_t x = ( instruction & 0x0F00) >> 8;
		Processeur_Fx07(proc, (uint8_t) x);
        }
                
	else if ((instruction & 0xF0FF ) == 0xF00A){
		uint16_t x = ( instruction & 0x0F00) >> 8;
		Processeur_Fx0A(proc, (uint8_t) x);
	}
                
        else if ((instruction & 0xF0FF ) == 0xF015){
		uint16_t x = ( instruction & 0x0F00) >> 8;
		Processeur_Fx15(proc, (uint8_t) x);
        }
        else if ((instruction & 0xF0FF ) == 0xF018){
		uint16_t x = ( instruction & 0x0F00) >> 8;
		Processeur_Fx18(proc, (uint8_t) x);
        }
        
	else if((instruction & 0xF0FF ) == 0xF01E){
		uint16_t x = ( instruction & 0x0F00) >> 8;
		Processeur_Fx1E(proc, (uint8_t) x);
        }
	else if((instruction & 0xF0FF ) == 0xF029){
		uint16_t x = ( instruction & 0x0F00) >> 8;
		Processeur_Fx29(proc, (uint8_t) x);
        }
                
        else if ((instruction & 0xF0FF ) == 0xF033){
		uint16_t x = ( instruction & 0x0F00) >> 8;
		Processeur_Fx33(proc, (uint8_t) x);
        }
        else if ((instruction & 0xF0FF ) == 0xF055){
		uint16_t x = ( instruction & 0x0F00) >> 8;
		Processeur_Fx55(proc, (uint8_t) x);
        }
        else if ((instruction & 0xF0FF ) == 0xF065){
		uint16_t x = (instruction & 0x0F00) >> 8;
		Processeur_Fx65(proc, (uint8_t) x);
        }
        else if ((instruction & 0xF0FF ) == 0xF01E){
		uint16_t x = ( instruction & 0x0F00) >> 8;
		Processeur_Fx1E(proc, (uint8_t) x);
        }else {
		printf("Echec du decodage");
	}
}



void fetch_decode_execute(struct Processeur *proc) {
        uint16_t instruction = fetch(proc);
        proc->PC += 2;
        decode_execute(proc,instruction);
}
