#include <stdio.h>
#include <pthread.h> 
#include <unistd.h> 
#include <stdlib.h>
#include <ctype.h>

int MAX=799;											//максимальная матрица [799][799], на моем компьютере больше - ошибка

void *mult(void* arg) 
{ 
    int *data = (int *)arg; 
    int k = 0, i = 0; 
      
    int x = data[0]; 
    for (i = 1; i <= x; i++) 
           k += data[i]*data[i+x]; 
      
    int *p = (int*)malloc(sizeof(int)*1000000); 
         *p = k; 
      
												//закрыть поток и вернуть переменную
    pthread_exit(p); 
} ;

void Threadmultification(int matA[MAX][MAX],int matB[MAX][MAX],int matC[MAX][MAX],int m1, int n1, int m2, int n2)
{      
    	int r1=m1,c1=n1,r2=m2,c2=n2,i,j,k;      
	int max = m1*n2; 									//размер
    	pthread_t *threads; 									//массив потоков
    	threads = (pthread_t*)malloc(sizeof(pthread_t)*max); 
      
    	int count = 0; 
    	int* data = NULL; 
   	for (i = 0; i < m1; i++){ 
        	for (j = 0; j < n2; j++){  
												//загружаем строки и столбики
            		data = (int *)malloc(sizeof(int)*10000000); 
            		data[0] = n1; 
            		for (k = 0; k < n1; k++) 
                		data[k+1] = matA[i][k]; 
            		for (k = 0; k < m2; k++) 
                		data[k+c1+1] = matB[k][j]; 

                	pthread_create(&threads[count++], NULL,  mult, (void*)(data)); 		//создаем потоки
		} 
	}

	FILE *outPutFile;
	char output[]="output.txt";								//проверять результат в этом файле
	outPutFile=fopen(output, "w");

    	for (i = 0; i < max; i++){ 
		void *k; 
      		pthread_join(threads[i], &k);				//присоединяем потоки             
          	int *p = (int *)k; 
     		fprintf(outPutFile, "%d ",*p); 				//печатаем в файл
      		if ((i + 1) % n2 == 0) 
          		fprintf(outPutFile, "\n"); 
    	}
	fclose(outPutFile);
}

int main(int argc, char *argv[]){
	int c,d,q,w;
	int num[1500], arr[1500];
	int prov, hope;
	unsigned long h;
	int row1, row2, column1, column2;
	q=0;
	w=0;
	row1=0;
	row2=0;
	column1=0;
	column2=0;

	char temp;

	int matA[MAX][MAX];
	int matB[MAX][MAX];
	int matC[MAX][MAX];

	FILE *proba1 = fopen(argv[1],"r");				//работаем с первым файлом-матрицей
	if(proba1 == NULL){
		printf("File is not valid\n");
		exit(1);
	}
	else{
	temp = getc(proba1);						//далее будет проверяться каждый символ
        while(temp != EOF){
		prov=(int)temp;						//проверяем, чтобы первым считалась цифра
		if(prov<48 || prov>57){
			printf("(1) Wrong matrix!");
			exit(1);
		}
		if(prov==48){
			temp=getc(proba1);
			hope=(int)temp;
			if(hope>47 && hope<58){
				printf("Error, 01, 02...");
				exit(1);
			}
		}
                while(temp != '\n'){
			if(temp == ' '){
                                column1++;
				temp = getc(proba1);
				prov=(int)temp;
				if (prov<48 || prov>57){
					printf("(2)Wrong matrix!");
					exit(1);
				}
					
				temp = getc(proba1);
				hope=(int)temp;
				if((prov<48 || prov>57)&&(hope<48 || hope>57)){
					printf("(2)Wrong matrix!");
					exit(1);
				}
				if(prov==48){
					if(hope>47 && hope<58){
						printf("Error, 01, 02...");
						exit(1);
					}
				}
			}
			else{
				prov=(int)temp;
				if(prov==48){
					if((prov<48 || prov>57) && prov!='\n' && prov!=EOF){
						printf("Error, 01, 02...");
						exit(1);
					}
				}
				temp=getc(proba1);
			}
		}
                if(temp == '\n'){										//подсчет строк и столбиков
                        row1++;
			num[q]=column1+1;
			if(q!=0 && num[q-1]!=num[q]){
				printf("Error, wrong matrix!");
				exit(1);
			}
			column1=0;
			q++;
                }
		temp = getc(proba1);
		if(temp==EOF)
			column1=num[0];
        }
       	fclose(proba1);
	}
	FILE *proba2 = fopen(argv[1],"r");									//работаем со вторым файлом-матрицей
	if(proba2 == NULL){
                printf("File is not valid\n");									//проверка каждого символа здесь аналогична тому, что написано выше
                exit(1);
	}
	else{
	temp = getc(proba2);
	while(temp != EOF){
		prov=(int)temp;
		if(prov<48 || prov>57){
			printf("(1) Wrong matrix!");
			exit(1);
		}
		if(prov==48){
			temp=getc(proba2);
			hope=(int)temp;
			if(hope>47 && hope<58){
				printf("Error, 01, 02...");
				exit(1);
			}
		}
		while(temp != '\n'){
			if(temp == ' '){
				column2++;
				temp=getc(proba2);
				prov=(int)temp;
				if (prov<48 || prov>57){
					printf("(2)Wrong matrix!");
					exit(1);
				}
				temp=getc(proba2);
				hope=(int)temp;
				if((prov<48 || prov>57)&& prov!='\n' && prov!=EOF){
					printf("(2) Wrong matrix!");
					exit(1);
				}
				if(prov==48){
					if(hope>47 && hope<58){
						printf("Error, 01, 02...");
						exit(1);
					}
				}
			}
			else{	
				prov=(int)temp;
				if((prov<48 || prov>57)&&prov!='\n' && prov!=EOF){
					printf("(2) Wrong matrix!");
					exit(1);
				}
				temp=getc(proba2);
			}
		}
		if(temp == '\n'){									//число строк и столбцов второй матрицы
			row2++;
			arr[w]=column2+1;
			if(w!=0 && arr[w-1]!=arr[w]){
				printf("Error, wrong matrix!");
				exit(1);
			}
			column2=0;
			w++;
		}
		temp= getc(proba2);
		if(temp==EOF)
			column2=arr[0];
	}
	fclose(proba2);	
	}	
	FILE *file1 = fopen(argv[1],"r");
	FILE *file2 = fopen(argv[1],"r");
	printf("Row:\t%d\n",row1);	
	printf("Col:\t%d\n",column1);	
	for (c = 0; c < row1; c++){									//заполняем первую матрицу и вторую
		for (d = 0; d < column1; d++){
			fscanf(proba1,"%ld",&h);
			matA[c][d] = h;
            	}
	}
        fclose(file1);

	for (c = 0; c < row2; c++){
            	for (d = 0; d < column2; d++){
              		fscanf(file2,"%ld",&h);
			matB[c][d] = h;	
            	}
       	}
       	fclose(file2);

	if (column1==row2){										//важно проверить, чтобы число столбиков первой матрицы было равно числу строк второй матрицы
		printf("\nThread multiplication done. Open output.txt\n"); 
		Threadmultification(matA,matB,matC,row1,column1,row2,column2);
	}
	else
		printf( "\n No multiplication because of rows and columns\n");
	return 0;
}
