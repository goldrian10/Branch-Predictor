#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
 
 
void dos_bits(int, int, int);
void gshare(int, int, int, int); 
char *indice(int seleccion , int n, char *estado_prueba){
	 
    static char pc_number [50], index[50];
    int contador=0, indexBits;
       
	
	fscanf(stdin, "%s %s ", pc_number, estado_prueba);
    int stringLen = strlen(pc_number);
    
    if (seleccion == 1){
		indexBits = stringLen-n;

		if(indexBits<0){
			indexBits=0;
		}
	}
	
	else if(seleccion == 2){
		indexBits=0;
	}
    for(int i= indexBits; i<= stringLen; i++){
		index[contador]=pc_number[i];
		contador++;
	}
	
	//printf("index: %s", index);
	return index;
}



int algoritmo_bimodal(int bht[][2], char *estado_prueba, char *estado_predecido, int apuntador_matriz, int contador_estado, int *estados){
	if(bht[apuntador_matriz][0]>1){
		strcpy(estado_predecido ,"T");
	}
	else{
		strcpy(estado_predecido ,"N");
	}
	printf("Estado prueba %s\n",estado_prueba);
	printf("Estado predecido %s\n",estado_predecido);

	if(strcmp(estado_predecido, estado_prueba)==0){//if estado predecido == estado prueba
		//la funcion strcmp compara los strings y devuelve un 0 si son iguales
		if(estados[contador_estado]>1){
		contador_estado++;
			
		}
		else{
		 contador_estado--;
		}
	}
	else{//estado predecido != estado_prueba
		if(estados[contador_estado]>1){
			contador_estado--;
		}
		else{
			contador_estado++;
		}
	 
	}
	if(contador_estado > 3){
		contador_estado = 3;
	}
	else if(contador_estado < 0){
		contador_estado = 0;
	}
	bht[apuntador_matriz][0]=estados[contador_estado];
	return bht[apuntador_matriz][0];
}//

void indexacion(int entries,int index, /*quitar prueba*/int prueba ,int bht[][2], int *estados, char *estado_prueba){
	
	int contador_estado=0, apuntador_matriz=0, contador_tabla=0;
	char estado_predecido[] = "N";
	
	for(apuntador_matriz=0; apuntador_matriz <= entries; apuntador_matriz++){
		
		
		if(apuntador_matriz==entries){
			prueba++;
			bht[contador_tabla][1]=index;
			contador_estado=0;
			
			algoritmo_bimodal(bht, estado_prueba, estado_predecido, apuntador_matriz, contador_estado, (int*)estados);
			contador_tabla++;
			if (contador_tabla> entries){
				contador_tabla=0;
			}
			break;
		}
		
		if(bht[apuntador_matriz][1] == index){
			prueba++;
			//printf("se encontro\n contador bht:%d\n",bht[apuntador_matriz][0]);
			
			for(contador_estado=0; contador_estado<4;contador_estado++){
				if(estados[contador_estado] == bht[apuntador_matriz][0]){
					break;
				}
				
			}
			
			algoritmo_bimodal(bht, estado_prueba, estado_predecido, apuntador_matriz, contador_estado, (int*)estados);
			
			break;
		}//fin del if
		
		else if(bht[apuntador_matriz][1]==0){
			prueba++;
			bht[apuntador_matriz][1]=index;
			contador_estado=0;																
			algoritmo_bimodal(bht, estado_prueba, estado_predecido, apuntador_matriz, contador_estado, (int*)estados);

			break;	
		}
		
		
	}//fin for
}//fin de indexacion



 void dos_bits(int bht[][2], int entries, int n, int *estados){


	 char estado_prueba[] = "T";
	 
	 char *index;
	 int prueba =0;
	/////////////////////////////////////////// 	
	//llenar bht
	//inicializamos todas en SN y las de indice en 0
	int apuntador_matriz=0;
	for(apuntador_matriz=0; apuntador_matriz < entries; apuntador_matriz++){
		bht[apuntador_matriz][0]=0;
		bht[apuntador_matriz][1]=0;
		//printf("%d\n",bht[apuntador_matriz][1]);
	}
	////////////// 
	
	
	while(!feof(stdin)){
		
		
		apuntador_matriz=0;
		index = indice(1 ,n,estado_prueba);
		uint index_int=atoi(index);
		//printf("pc_bits; %u", index_int);
		
		
		indexacion(entries, index_int,/*quitar prueba*/ prueba,bht,(int*)estados, estado_prueba);
		/*for(apuntador_matriz=0; apuntador_matriz <= entries; apuntador_matriz++){
			
			
			if(apuntador_matriz==entries){
				prueba++;
				bht[contador_tabla][1]=index_int;
				contador_estado=0;
				
				algoritmo_bimodal(bht, estado_prueba, estado_predecido, apuntador_matriz, contador_estado, (int*)estados);
				contador_tabla++;
				if (contador_tabla> entries){
					contador_tabla=0;
				}
				break;
			}
			
			if(bht[apuntador_matriz][1] == index_int){
				prueba++;
				//printf("se encontro\n contador bht:%d\n",bht[apuntador_matriz][0]);
				
				for(contador_estado=0; contador_estado<4;contador_estado++){
					if(estados[contador_estado] == bht[apuntador_matriz][0]){
						break;
					}
					
				}
				
				algoritmo_bimodal(bht, estado_prueba, estado_predecido, apuntador_matriz, contador_estado, (int*)estados);
				
				break;
			}//fin del if
			
			else if(bht[apuntador_matriz][1]==0){
				prueba++;
				bht[apuntador_matriz][1]=index_int;
				contador_estado=0;																
				algoritmo_bimodal(bht, estado_prueba, estado_predecido, apuntador_matriz, contador_estado, (int*)estados);

				break;	
			}
			
			
		}//fin for  */
			
		
	}//fin while
	
		
	 printf("\n%d\n",prueba);
	
}//fin dos bits


void gshare(int bht[][2], int gbits, int entries, int n, int *estados){
	int ghist=0;
	int apuntador_matriz=0;
	char *index, *pc_bits;
	char estado_predecido[] = "N";
	char estado_prueba[] = "T";
	
	/////////////////////////////////////////// 	
	//llenar bht
	//inicializamos todas en SN y las de indice en 0
	
	for(apuntador_matriz=0; apuntador_matriz < entries; apuntador_matriz++){
		bht[apuntador_matriz][0]=0;
		bht[apuntador_matriz][1]=0;
		//printf("%d\n",bht[apuntador_matriz][1]);
	}
	
	while(!feof(stdin)){
		apuntador_matriz=0;
		pc_bits = indice(2, n, estado_prueba);
		uint pc_bits_uint=atoi(pc_bits);
		int pc_bits_int = (int) pc_bits_uint;
		printf("pcbits: %u  %d\n",pc_bits_uint, pc_bits_int);
		index = pc_bits_int ^ ghist;
		printf("index: %d\n",index);
		
		
		
	}
	
}//fin gshare





//main
int main (int argc, char** argv){
	enum bimodal { SN=0, WN, WT, ST};
	enum bimodal estados[] ={SN,WN,WT,ST};
	//argv[2]=  S (BHT size  2^s entries) = = n
	//argv[4]= prediction type
	//argv[6]= G prediction register size
	//argv[8]= P history register size
	//argv[10b]= simulation out#include<math.h>

	enum argumentos {s=2,type=4, gSize=6, pSize=8, simOut=10};
	
	/*brainstorm
	usar enum para las variables de los argumentos para ser 
	* mas ordenado
	* 
	*/
	
	//dos_bits();//mal hecho
	char *p =  NULL, *t=NULL;
    int n = strtoq(argv[s], &p, 10); //convierte el string del argumento a un numero, p es un puntero nulo necesario y 10 es la base
	int gl = strtoq(argv[gSize], &t, 10);
    int entries = pow (2,n);
    
    //creacion del branch history table
    int bht[entries][2];
    

	
	//dos_bits(bht, entries, n, (int*)estados);
	gshare(bht, gl, entries, n, (int*)estados);
	
	return 0;
}//fin del main
