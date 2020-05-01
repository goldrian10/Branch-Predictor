#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

 
//void dos_bits(int, int, int, int);
//void gshare(int, int, int, int, int); 



// este metodo recibe  como parametro una varable tipo char, esto es en realidad para devolver el valor de estado prueba por ahí
//la funcion es tipo char y devuelve el pc completo en forma de int
char *indice(char *estado_prueba){
	 
    static char pc_number [50], index[50];
    int contador=0;
       
	
	fscanf(stdin, "%s %s ", pc_number, estado_prueba);
    int stringLen = strlen(pc_number);
   
    for(int i= 0; i<= stringLen; i++){
		index[contador]=pc_number[i];
		contador++;
	}
	
	
	return index;
}


//la funcion indexacion sirve para colocar el valor del pc en la tabla bht, esto con un apuntador llamado apuntador_matriz y lo devuelve en el indice correcto
//ademas recibe una variable de control por si se desea obtener el estado del contador de 2 bits en este indice
//tambien esta funcion recibe y modifica el valor de contador tabla que este se utiliza para actualizar la tabla bht cuando esta se llena
//al llenarse se va al inicio de la tabla y se remplaza este indice por el nuevo pc

void indexacion(int control, int entries,int index,int bht[][2], int *estados,int &contador_tabla, int &apuntador_matriz,int &contador_estado){
	
	//se recorre la bht y al encontrarse el indice se sale del for con el valor de apuntador_matriz donde se requiere
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
		//si se encuentra un 0 quiere decir que no encontró el pc actual y se procede a guardarlo en este valor
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



//algoritmo bimodal es la funcion encargada de realizar la comparacion entre la prediccion y el valor del outcome
//esta recibe 2 variables nuevas por parametros que son test y taken_predict estos se actualizan cuando hay una prediccion correcta y cuando el outcome es un taken respectivamente
//ademas actualiza los valores de estado_prueba y estado_predecido para tener informacion de estos en los metodos de los predictores
//esta funcion actualiza el valor del estado del 2bc en este indice
void algoritmo_bimodal(int bht[][2], char *estado_prueba, char *estado_predecido, int apuntador_matriz, int contador_estado, int *estados, float &test, float &taken_predict){
	
	if(bht[apuntador_matriz][0]>1){
		strcpy(estado_predecido ,"T");
	}
	else{
		strcpy(estado_predecido ,"N");
	}
	
	if(strcmp(estado_predecido, estado_prueba)==0){//if estado predecido == estado prueba
		//la funcion strcmp compara los strings y devuelve un 0 si son iguales
		test++;
		//si contador estado es mayor a 1 significa que la prediccion era taken entoncrs se aumenta contador estado
		if(estados[contador_estado]>1){
		contador_estado++;
		taken_predict++;
			
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
	
	//aqui se evita que el contador sea mayor a 3 (ST) o menos a 0 (SN)
	if(contador_estado > 3){
		contador_estado = 3;
	}
	else if(contador_estado < 0){
		contador_estado = 0;
	}
	bht[apuntador_matriz][0]=estados[contador_estado];
	//return bht[apuntador_matriz][0];
}//



//la funcion simOut es la que va a guardar los valores requeridos en el archivo de texto
//recibe como parametros fp que es el puntero de tipo FILE, y pc, outcome, predition son los valores de pc_bits, estado_prueba y estado_prediccion 
//estado nos dice si la prediccion fue correcta o incorrecta en este indice
void simOut(FILE *fp , char *pc, char *outcome, char *prediction,char *estado){
	
	
	//nos aseguramos de que fp exista
	if (fp==NULL) {fputs ("File error\n",stderr); exit (1);}
	fprintf(fp,"%s      %s              %s        %s\n",pc,outcome,prediction,estado);
	
}


// la funcion dos bits es la que se ejecuta cuando el usuario digita un 0 en la seccion de prediction type
//esta recibe la tabla bht donde va a guardar los indices y estados de los 2bc, n que es el tamaño de bits que se necesitan para indexar
//entries que es el numero de entradas del bht
//estados que es el resultado del enum del estado del 2bc y o que me dice si requiero escribir el archivo de texto
 void dos_bits(FILE *fp,int bht[][2], int entries, int n, int *estados,float &taken, float &prueba, float &taken_predict, float &test, int o){
	char estado_predecido[] = "N";
	char estado_prueba[] = "T";
	
	
	
	static char cadena_indice[50], index_str[50];
	//char *index;
	int apuntador_matriz=0, contador_tabla=0,contador_estado=0,contadorB=0;
	char *pc_bits;
	static char estado[50];
	/////////////////////////////////////////// 	
	//llenar bht
	//inicializamos todas en SN y las de indice en 0
	
	for(apuntador_matriz=0; apuntador_matriz < entries; apuntador_matriz++){
		bht[apuntador_matriz][0]=0;
		bht[apuntador_matriz][1]=0;
		
	}
	////////////// 
	
	//ciclo principal de la funcion, se termina donde se acaba el archivo 
	while(!feof(stdin)){
		//este contador se utiliza para saber si la prediccion fue correcta
		contadorB++;
		apuntador_matriz=0;
		pc_bits = indice(estado_prueba);
		uint pc_bits_int=atoi(pc_bits);

		sprintf(index_str, "%u", pc_bits_int);
		
		//aqui se modifica el tamaño del pc para tomar solo los nbits menos significativos y se guardan en index_int
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
		
		//se compara si mi outcome fue taken para aumentar su respectivo contador
		if(strcmp(estado_prueba,"T")==0){
			taken++;
		}
		//se procede a indexar y ejecutar los algoritmos para saber entrenar el predictor
		indexacion(1,entries,index_int,bht,(int*)estados,contador_tabla, apuntador_matriz, contador_estado);
		
		algoritmo_bimodal(bht, estado_prueba, estado_predecido, apuntador_matriz, contador_estado, (int*)estados, test,taken_predict);
		
		prueba++;
		
		//se compara si o está en 1 para saber si se debe escribir el archivo de texto y ademas que se termine a las 500 lineas
		if(o==1 && prueba<=500){
			if(contadorB==test){strcpy(estado ,"Correcto");}
			else{strcpy(estado ,"Incorrecto");
				contadorB--;}
			simOut(fp,pc_bits, estado_prueba, estado_predecido,estado);
		}
		
		
	}
	
	//se cierra el archivo de texto
	if(o==1){fclose ( fp );}
		
	
}



// la funcion gshare es la que se ejecuta cuando el usuario digita un 1 en la seccion de prediction type
//esta recibe la tabla bht donde va a guardar los indices y estados de los 2bc, n que es el tamaño de bits que se necesitan para indexar
//gbits que es el tamaño del registro de historia
//entries que es el numero de entradas del bht
//estados que es el resultado del enum del estado del 2bc y o que me dice si requiero escribir el archivo de texto

void gshare(FILE *fp,int bht[][2], int gbits, int entries, int n, int *estados, float &taken, float &prueba, float &taken_predict, float &test,int o){
	uint ghist=0;
	static char cadena_indice[50], index_str[50], estado[50];
	int apuntador_matriz=0, contador_tabla=0,contador_estado=0, contadorG=0,contadorB=0;
	uint index=0;
	char *pc_bits;

	char estado_prueba[] = "T";
	char estado_predecido[] = "N";
	
	//se crea una mascara de tamaño 2^gbits -1 para asegurarse que nunca hayan más digitos que gbits
	uint mask= pow(2,gbits)-1;
	
	/////////////////////////////////////////// 	
	//llenar bht
	//inicializamos todas en SN y las de indice en 0
	
	for(apuntador_matriz=0; apuntador_matriz < entries; apuntador_matriz++){
		bht[apuntador_matriz][0]=0;
		bht[apuntador_matriz][1]=0;
	}
	
	
	//ciclo principal de la funcion, se termina donde se acaba el archivo 
	while(!feof(stdin)){
		//estos contadores se utilizan el G para saber si el outcome fue taken y modiificar la historia
		//y el contadorB para saber si la prediccion fue correcta
		contadorG++;
		contadorB++;
		apuntador_matriz=0;
		
		//se transforman los pc bits a un int sin signo y se hace xor con la historia (antes inicializada en  0)
		pc_bits = indice(estado_prueba);
		uint pc_bits_int=atoi(pc_bits);
		
		//compruebo que ghist no sea mayor a gbits
		ghist=ghist&mask;
		index = pc_bits_int ^ ghist;
		
		sprintf(index_str, "%u", index);
		
		//con este algoritmo se obtienen los bit menos significativos requeridos
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
	
	
		//se compara si mi outcome fue taken para aumentar su respectivo contador
		if(strcmp(estado_prueba,"T")==0){
			taken++;
		}
		
		indexacion(1,entries, index_int,bht,(int*)estados,contador_tabla, apuntador_matriz, contador_estado);
		algoritmo_bimodal(bht, estado_prueba, estado_predecido, apuntador_matriz, contador_estado, (int*)estados, test,taken_predict);
		
		//se le hace shift a la historia global para actualizarla
		ghist=ghist<<1;
		//si fue taken se le suma 1 y si no se deja en 0
		if(taken==contadorG){
				//taken
				ghist=ghist+1;
		}
		else{
			//not taken
				contadorG--;		
		}
	
		
		prueba++;
		
		//se compara si o está en 1 para saber si se debe escribir el archivo de texto y ademas que se termine a las 500 lineas
		if(o==1 && prueba<=500){
			if(contadorB==test){strcpy(estado ,"Correcto");}
			else{strcpy(estado ,"Incorrecto");
				contadorB--;}
			simOut(fp,pc_bits, estado_prueba, estado_predecido,estado);
		}
		
		
	}
	
	//se cierra el archivo de texto
	if(o==1){fclose ( fp );}
		
	}//fin gshare









// la funcion Pshare es la que se ejecuta cuando el usuario digita un 1 en la seccion de prediction type
//esta recibe la tabla bht donde va a guardar los indices y estados de los 2bc, n que es el tamaño de bits que se necesitan para indexar
//pbits que es el tamaño del registro de historia privada
//entries que es el numero de entradas del bht
//estados que es el resultado del enum del estado del 2bc y o que me dice si requiero escribir el archivo de texto

void pshare(FILE *fp,int bht[][2],int entries, int pbits, int n,int *estados, float &taken, float &prueba, float &taken_predict, float &test,int o){
	//se crea una matriz 2^s x 2 para usarla de pht
	int pht[entries][2];
	//se inicializan el resto de variables a utilizar
	uint phist=0,index=0;
	char *pc_bits;
	static char cadena_indice[50], index_str[50], estado[50];
	char estado_predecido[] = "N";
	char estado_prueba[] = "T";

	int apuntador_matriz=0, contador_tabla=0,contador_estado=0, contadorP=0, contador=0, indexBits=0, stringLen=0,contadorB=0;
	uint index_int=0;

	//mask es una mascara de tamaño (2^ph)-1 para que el registro de la historia privada no sea mas grande que este
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
		contadorB++;
		apuntador_matriz=0;
		
		pc_bits = indice(estado_prueba);
		contador=0;
		stringLen = strlen(pc_bits);
		indexBits = stringLen-n;
		if(indexBits<0){
			indexBits=0;
		}
		for(int i= indexBits; i<= stringLen; i++){
			cadena_indice[contador]=pc_bits[i];
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
		algoritmo_bimodal(bht, estado_prueba, estado_predecido, apuntador_matriz, contador_estado, (int*)estados, test, taken_predict);
		
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
		
		if(o==1 && prueba<=500){
			if(contadorB==test){strcpy(estado ,"Correcto");}
			else{strcpy(estado ,"Incorrecto");
				contadorB--;}
			simOut(fp,pc_bits, estado_prueba, estado_predecido,estado);
		}
		
		
	}
	if(o==1){fclose ( fp );}

}





int main (int argc, char** argv){
	//enum utilizado para tener mas control sobre los estados del 2bc
	enum bimodal { SN=0, WN, WT, ST};
	enum bimodal estados[] ={SN,WN,WT,ST};
	float taken=0, prueba=0, test=0, taken_predict=0;
	//argv[2]=  S (BHT/PHT size  2^s entries) = = n
	//argv[4]= prediction type
	//argv[6]= G history register size
	//argv[8]= P history register size
	//argv[10b]= simulation out
	enum argumentos {s=2,type=4, gSize=6, pSize=8, simOut=10};
	//se inicializa el puntero tipo FILE que va al archivo 
	FILE *fp=NULL;
	

	static char tipo[50];
	char *p =  NULL, *t=NULL, *r= NULL, *x=NULL,*f=NULL;
    int n = strtoq(argv[s], &p, 10); //convierte el string del argumento a un numero, p es un puntero nulo necesario y 10 es la base
	int gh = strtoq(argv[gSize], &t, 10);
	int ph = strtoq(argv[pSize], &r, 10);
	int bpt = strtoq(argv[type], &x, 10);
	int o = strtoq(argv[simOut], &f, 10);
	//entradas del BHT = 2 ^n
    int entries = pow (2,n);
    
    //creacion del branch history table
    int bht[entries][2];
    
	switch(bpt){
	case 0:
		strcpy(tipo ,"Bimodal");
		//si o esta activo se crea, se pone el nombre del archivo y el encabezado
		if(o==1){
			fp = fopen ( "Bimodal.txt", "wt" );
			fprintf(fp, "PC           Outcome      Prediction   correct/incorrect\n");
		}
		
		dos_bits(fp,bht, entries, n, (int*)estados, taken, prueba, taken_predict, test,o);

		break;
	case 1:
		strcpy(tipo ,"Gshare");
		if(o==1){
			fp = fopen ( "Gshare.txt", "wt" );
			fprintf(fp, "PC           Outcome      Prediction   correct/incorrect\n");
		}
		
		gshare(fp,bht, gh, entries, n, (int*)estados, taken, prueba, taken_predict, test,o);

		break;
	case 2:
		strcpy(tipo ,"Pshare");
		if(o==1){
			fp = fopen ( "Pshare.txt", "wt" );
			fprintf(fp, "PC           Outcome      Prediction   correct/incorrect\n");
		}
		
		pshare(fp,bht,entries, ph, n, (int*)estados, taken, prueba, taken_predict, test,o);
		
		break;
	case 3:
		
		break;
	}
	
	printf("_______________________________________________________________________________\n Prediction parameters:\n_______________________________________________________________________________\n Branch prediction type:                                %s\n BHT size (entries):                                    %d\n Global history register size:                          %d\n Private history register size:                         %d\n",tipo ,n,gh,ph);
	printf("_______________________________________________________________________________\n Simulation results:\n_______________________________________________________________________________\n Number of branch:                                     %f\n Number of correct prediction of taken branches:        %f\n Number of incorrect prediction of taken branches:      %f\n Correct prediction of not taken branches:              %f\n Incorrect prediction of not taken branches:            %f\n Percentage of correct predictions:                   %f%c\n_______________________________________________________________________________\n",prueba,taken_predict,(taken-taken_predict),(test-taken_predict),((prueba-taken)-(test-taken_predict)),((test*100)/prueba),'%');

																																																																																																																					//prueba = cantidad de branches 
																																																																																																																					//test = cantidad de correctos
																																																																																																																					//taken = cantidad de tomados
																																																																																																																					//prueba - test = cantidad de incorrectos
																																																																																																																					//taken_predict = T correctos
																																																																																																																					//test-taken predict = NT correctos
	return 0;
}//fin del main
