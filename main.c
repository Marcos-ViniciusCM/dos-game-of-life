#include <stdio.h>
#include <dos.h>
#include <i86.h> 
#include <conio.h>
#include <stdlib.h>
#include <math.h> 
#include <string.h>
#include <time.h>


#define SCREEN_WIDTH  320
#define SET_MODE            0x00 
#define VIDEO_INT           0x10
#define SCREEN_HEIGTH 200
#define VGA_256_COLOR_MODE  0x13 
#define TEXT_MODE     0x03

 typedef unsigned char bytePerson;

unsigned char __far *VGA = (unsigned char __far *)0xA0000000L;


//cada grid vai ter 4 pixel entao fica 80x50
unsigned int tabuleiro[4000] = {0};

//proximo e oque vai ser printado na tela;
unsigned int proximo[4000] = {0};

void defineMode(bytePerson mode){
union REGS regs;
    regs.h.ah = SET_MODE;
    regs.h.al = mode;
    int86(VIDEO_INT,&regs,&regs);
}

void voltaTexto(){
    union REGS regs;
    //voltar modo texto
regs.h.ah = 0x00;
regs.h.al = 0x3;
int86(0x10,&regs,&regs);
}


void desenhaPixel(int x,int y,bytePerson color){
    //multiplica o y por 320 e soma o x e coloca a cor no offset
    //y + 2
    VGA[((y<<6) + (y<<8) )+x] = color;
}


//index pega a posicao atual no array que deve se comportar igual grid
int getNeighbors(int x, int y) {
    int index = (y*80) + x;
    if (x <= 0 || x >= 79 || y <= 0 || y >= 49)
        return 0;
   
    
	
   return tabuleiro[index - 80] + 
           tabuleiro[index + 80] + 
           tabuleiro[index - 1] + 
           tabuleiro[index - 1 - 80] + 
           tabuleiro[index - 1 + 80] + 
           tabuleiro[index + 1] + 
           tabuleiro[index + 1 + 80] + 
           tabuleiro[index + 1 - 80];
}

void verificaVizinhos(int x, int y) {
    int vizinhos = getNeighbors(x, y);
    int index = (y*80) + x;
//solidao
    if (tabuleiro[index] == 1 && vizinhos < 2) {
        proximo[index] = 0;
    } 
    
    //sobrevivencia
    if(tabuleiro[index] == 1 && (vizinhos == 2 || vizinhos == 3)){
    	proximo[index] = 1;
	}
	
	//superpolucao
	if(tabuleiro[index] == 1 && vizinhos > 3){
		proximo[index] = 0;
	}
	
	//reproducao
	if(tabuleiro[index] == 0 && vizinhos == 3){
		proximo[index] = 1;
	}

    if(tabuleiro[index] == 0 && vizinhos != 3){
        proximo[index] = 0;
    }
    
}


void reiniciaArray(unsigned int *array){
    memset(array, 0, 4000 * sizeof(unsigned int));
}

void atualizaTabuleiro(){
    memcpy(tabuleiro, proximo, 4000 * sizeof(unsigned int));
}
void inicializaRando(){
    int i;
     srand(time(NULL));
    for(i=0;i< 4000;i++){
        tabuleiro[i] = rand() % 2;
    }
}

 void copiaArrayParaTela(){
    int index = 0 ;
    int x,y = 0;
    int i = 0;
    int x1,y1=0;
    int tela_x, tela_y;
    int atual_y = 0;
    int atual_x = 0;
     for( ; i < 4000;i++){
          if(i % 80 == 0 && i !=0){
             y++;
             x=0;
          }

          tela_x = x * 4;
          tela_y = y * 4;
       
          for(x1 = 0 ; x1 < 4;x1++){
            for(y1 = 0 ; y1 < 4 ; y1++){
               int atual_y = tela_y + y1;
                int atual_x = tela_x + x1;
                VGA[(( (atual_y) <<6) + ( (atual_y)<<8) )+ atual_x  ] = proximo[i]; //PROXIMO
            }
          }

          //VGA[((y<<6) + (y<<8) )+ x  ] = proximo[i]; 
         x++;
           
     }
 }



int main() {

int x = 0;
int y = 0;
tabuleiro[82] = 1;
tabuleiro[163] = 1;
tabuleiro[241] = 1;
tabuleiro[242] = 1;
tabuleiro[243] = 1;

   
defineMode(VGA_256_COLOR_MODE);
inicializaRando();
 
   while(!kbhit()){
    int i;
    y = 0;
    x=0;   
    for(i = 0; i < 4000;i++){
         x++;
         if(i % 80 == 0 && i !=0){
            y++;
            x=0;
         }
       
        verificaVizinhos(x,y);   
    }
    
    copiaArrayParaTela();
    atualizaTabuleiro();
    reiniciaArray(proximo);
   }

getch();



    defineMode(TEXT_MODE);
    printf("Hello, World!\n");
    return 0;
}