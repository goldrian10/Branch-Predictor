#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

 
void dos_bits(int, int, int, int);
void gshare(int, int, int, int, int); 

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



int algoritmo_bimodal(int bht[][2], char *estado_prueba, char *estado_predecido, int apuntador_matriz, int contador_estado, int *estados, int &test){
	if(bht[apuntador_matriz][0]>1){
		strcpy(estado_predecido ,"T");
	}
	else{
		strcpy(estado_predecido ,"N");
	}
	//printf("Estado prueba %s\n",estado_prueba);
	//printf("Estado predecido %s\n",estado_predecido);

	if(strcmp(estado_predecido, estado_prueba)==0){//if estado predecido == estado prueba
		//la funcion strcmp compara los strings y devuelve un 0 si son iguales
		test++;
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



///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

void indexacion(int control, int entries,int index,int bht[][2], int *estados,int &contador_tabla, int &apuntador_matriz,int &contador_estado){
	
	
	for(apuntador_matriz=0; apuntador_matriz <= entries; apuntador_matriz++){
		
		
		if(apuntador_matriz==entries){
			//printf("se llleno bht:%d\n",bht[apuntador_matriz][0]);
			bht[contador_tabla][1]=index;
			contador_estado=0;
			contador_tabla++;
			
			if (contador_tabla> entries){
				contador_tabla=0;
			}
			break;
		}
		
		if(bht[apuntador_matriz][1] == index){
		//	printf("se encontro el indice\n contador bht:%d\n",bht[apuntador_matriz][0]);
			
			if(control==1){
				for(contador_estado=0; contador_estado<4;contador_estado++){
					if(estados[contador_estado] == bht[apuntador_matriz][0]){
						break;
					}
					
				}
			}
			else if(control==2){
				break;
			}
			else{
				printf("variable de control no ingresada");
			}
			break;
		}
		
		else if(bht[apuntador_matriz][1]==0){
		//	printf("se encontro un 0 en la tabla\n contador bht:%d\n",bht[apuntador_matriz][0]);
			bht[apuntador_matriz][1]=index;
			if(control==1){
				contador_estado=0;																
			}
			else if(control==2){
				break;
			}
			else{
				printf("variable de control no ingresada");
			}
			break;	
		}
		
		
	}//fin for
}//fin de indexacion


void gshare(int bht[][2], int gbits, int entries, int n, int *estados){
	uint ghist=0;
	static char cadena_indice[50], index_str[50];
	int apuntador_matriz=0, test=0, contador_tabla=0,contador_estado=0, contadorG=0,taken=0;
	uint index=0;
	char *pc_bits;
	char estado_prueba[] = "T";
	char estado_predecido[] = "N";
	uint mask= pow(2,gbits)-1;
	
	/////////////////////////////////////////// 	
	//llenar bht
	//inicializamos todas en SN y las de indice en 0
	
	for(apuntador_matriz=0; apuntador_matriz < entries; apuntador_matriz++){
		bht[apuntador_matriz][0]=0;
		bht[apuntador_matriz][1]=0;
		//printf("%d\n",bht[apuntador_matriz][1]);
	}
	
	while(!feof(stdin)){
		contadorG++;
		apuntador_matriz=0;
		
		pc_bits = indice(2, n, estado_prueba);
		uint pc_bits_int=atoi(pc_bits);
		//printf("pcbits: %u \n",pc_bits_int);
		ghist=ghist&mask;
		index = pc_bits_int ^ ghist;
		
		sprintf(index_str, "%u", index);
		
		
		int contador=0, indexBits;
		int stringLen = strlen(index_str);
		indexBits = stringLen-n;
		if(indexBits<0){
			indexBits=0;
		}
		for(int i= indexBits; i<= stringLen; i++){
			cadena_indice[contador]=index_str[i];
			contador++;
		}
		uint index_int=atoi(cadena_indice);
		//printf("index: %u\n",index_int);
		if(strcmp(estado_prueba,"T")==0){
			taken++;
		}
		
		indexacion(1,entries, index_int,bht,(int*)estados,contador_tabla, apuntador_matriz, contador_estado);
		algoritmo_bimodal(bht, estado_prueba, estado_predecido, apuntador_matriz, contador_estado, (int*)estados, test);
		ghist=ghist<<1;
		if(taken==contadorG){
				//taken
				//printf("correct\n");
				ghist=ghist+1;
		}
		else{
			//not taken
				//printf("incorrect\n");	
				contadorG--;		
		}
		//printf("test: %d\ncontad: %d \n", test, contadorG);
		
		
	}//fin while
	printf("test: %d\n", test);
}//fin gshare







 void dos_bits(int bht[][2], int entries, int n, int *estados){
	char estado_predecido[] = "N";
	char estado_prueba[] = "T";
	char *index;
	int apuntador_matriz=0, test=0, prueba=0, contador_tabla=0,contador_estado=0;
	/////////////////////////////////////////// 	
	//llenar bht
	//inicializamos todas en SN y las de indice en 0
	
	for(apuntador_matriz=0; apuntador_matriz < entries; apuntador_matriz++){
		bht[apuntador_matriz][0]=0;
		bht[apuntador_matriz][1]=0;
		
	}
	////////////// 
	
	
	while(!feof(stdin)){
		apuntador_matriz=0;
		index = indice(1 ,n,estado_prueba);
		uint index_int=atoi(index);
		
		indexacion(1,entries,index_int,bht,(int*)estados,contador_tabla, apuntador_matriz, contador_estado);
		
		algoritmo_bimodal(bht, estado_prueba, estado_predecido, apuntador_matriz, contador_estado, (int*)estados, test);
		
		prueba++;
		
	}//fin while
	
		printf("pruebas: %d\nCorrectos: %d\n",prueba, test);
	
}//fin dos bits



void pshare(int bht[][2],int entries, int pbits, int n,int *estados){
	//se crea una matriz 2^s x 2 para usarla de pht
	int pht[entries][2];
	//se inicializan el resto de variables a utilizar
	uint phist=0,index=0;
	char *pc_bits;
	static char cadena_indice[50], index_str[50];
	char estado_predecido[] = "N";
	char estado_prueba[] = "T";
	int apuntador_matriz=0, test=0, prueba=0, contador_tabla=0,contador_estado=0, contadorP=0, contador=0, indexBits=0, stringLen=0, taken=0;
	uint index_int=0;

	//mask es una mascara de tamaño 2^gh-1 para que el registro de la historia privada no sea mas grande que este
	uint mask= pow(2,pbits)-1;
	
	//llenar pht
	//inicializamos todas en 0
	
	for(apuntador_matriz=0; apuntador_matriz < entries; apuntador_matriz++){
		pht[apuntador_matriz][0]=0;
		pht[apuntador_matriz][1]=0;
		
	}
	//llenar bht
	//inicializamos todas en SN y las de indice en 0
	
	for(apuntador_matriz=0; apuntador_matriz < entries; apuntador_matriz++){
		bht[apuntador_matriz][0]=0;
		bht[apuntador_matriz][1]=0;
		
	}
	//////////////
	//while que se termina al final del archivo 
	while(!feof(stdin)){
		//contador p se utiliza para compararlo con test y así se sabe de forma local si se tuvo un taken o un not taken
		contadorP++;
		apuntador_matriz=0;
		
		pc_bits = indice(2, n, estado_prueba);
		contador=0;
		stringLen = strlen(pc_bits);
		indexBits = stringLen-n;
		if(indexBits<0){
			indexBits=0;
		}
		for(int i= indexBits; i<= stringLen; i++){
			cadena_indice[contador]=index_str[i];
			contador++;
		}
		uint pc_bits_int=atoi(pc_bits);
	
		uint index_pht_int=atoi(cadena_indice);
		
		
		//se envía la pht a la funcion indexacion para que me guarde el valor obtenido del pc, se pasa un 2 para que solo devuelva el valor de apuntador_matriz
		//con este valor se sabrá la pocision donde se almacenó este branch
		indexacion(2,entries,index_pht_int,pht,(int*)estados,contador_tabla, apuntador_matriz, contador_estado);
		//se obtiene la historia privada de ese branch 
		phist=pht[apuntador_matriz][0];
		
		//se obtienen los bits completos del pc para aplicarles el xor con el phist
		
		phist=phist&mask;
		index = pc_bits_int ^ phist;
		
		//se convierte el valor de index a string para obtener los bits menos significativos
		sprintf(index_str, "%u", index);
		
		contador=0;
		stringLen = strlen(index_str);
		indexBits = stringLen-n;
		if(indexBits<0){
			indexBits=0;
		}
		for(int i= indexBits; i<= stringLen; i++){
			cadena_indice[contador]=index_str[i];
			contador++;
		}
		
		index_int=atoi(cadena_indice);
		//printf("index: %u\n",index_int);
		
		//comprueba si el valor fue taken o not taken y aumenta el contador, esto para modificar la historia privada de este branch
		if(strcmp(estado_prueba,"T")==0){
			taken++;
		}

		//index_int tiene los bits menos significativos y ahora con este dato se indexa el bht 
		indexacion(1,entries, index_int,bht,(int*)estados,contador_tabla, apuntador_matriz, contador_estado);
		algoritmo_bimodal(bht, estado_prueba, estado_predecido, apuntador_matriz, contador_estado, (int*)estados, test);
		
		//se hace el shift para almacenar el nuevo valor de phist que será 1 si fue taken o 0 si fue not taken
		phist=phist<<1;
		if(taken==contadorP){
				//taken
				//printf("correct\n");
				phist=phist+1;
		}
		else{
			//not taken
				//printf("incorrect\n");	
				contadorP--;		
		}
		//se guarda el nuevo valor de phist en la pht
		pht[apuntador_matriz][0]=phist;
		
		prueba++;
		
	}//fin while
	
		printf("pruebas: %d\nCorrectos: %d\n",prueba, test);
	
	
	
}



//main
int main (int argc, char** argv){
	enum bimodal { SN=0, WN, WT, ST};
	enum bimodal estados[] ={SN,WN,WT,ST};
	//argv[2]=  S (BHT/PHT size  2^s entries) = = n
	//argv[4]= prediction type
	//argv[6]= G history register size
	//argv[8]= P history register size
	//argv[10b]= simulation out#include<math.h>

	enum argumentos {s=2,type=4, gSize=6, pSize=8, simOut=10};
	
	/*brainstorm
	usar enum para las variables de los argumentos para ser 
	* mas ordenado
	* 
	*/

	char *p =  NULL, *t=NULL, *r= NULL;
    int n = strtoq(argv[s], &p, 10); //convierte el string del argumento a un numero, p es un puntero nulo necesario y 10 es la base
	int gh = strtoq(argv[gSize], &t, 10);
	int ph = strtoq(argv[pSize], &r, 10);
    int entries = pow (2,n);
    
    //creacion del branch history table
    int bht[entries][2];
    

	
	//dos_bits(bht, entries, n, (int*)estados);
	//gshare(bht, gh, entries, n, (int*)estados);
	pshare(bht,entries, ph, n, (int*)estados);
	
	return 0;
}//fin del main
