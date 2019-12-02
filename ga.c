#define TAMPOP 1000
#define TAMCROMOSOME 10
#define GERATIONS 100
#define MINRANDOM 0
#define MAXRANDOM 5
#define NUMCOMPETITOR 3
#define ELITSM 0.05
#define MUTATIONRATE 50


#include <time.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct _cromosome_{
	int body[TAMCROMOSOME];
	float fitnes;

}cromosome;


typedef struct _population_ {
	cromosome individuals[TAMPOP];
	cromosome betterIndividual;
}population;



void quicksort(cromosome[], int,int);
void orderCromosomes(cromosome[]);
void printCromosomes(cromosome[],int);
void printCromosome(cromosome);
cromosome crossOver(cromosome,cromosome);



population* tournament(population p){
	population* newPop = (population*)malloc(sizeof(population));
	int k,i,indexs[NUMCOMPETITOR];
	cromosome c[NUMCOMPETITOR]; 

	cromosome p1,p2,auxCromosome,son;
	int aux;

	for( k = 0 ; k < TAMPOP; k++ ){
	//	printf("BEGIN TOURNAMENT\n");
		p1 = p.individuals[rand()%(int)(TAMPOP*ELITSM)];
		p2 = p.individuals[rand()%(int)(TAMPOP*ELITSM)];
		//printCromosome(p1);
		//printCromosome(p2);
		for(i = 0 ; i < NUMCOMPETITOR-2 ; i ++){
			auxCromosome = p.individuals[rand()%(int)(TAMPOP*ELITSM)];
			if(p1.fitnes < auxCromosome.fitnes){
				p2 = p1;
				p1 = auxCromosome;
			}else if(p2.fitnes<auxCromosome.fitnes){
				p2 = auxCromosome;
			}
			//c[i] = p.individuals[rand()%(int)(TAMPOP*ELITSM)];

		}
	//	printf("Selecteds\n");
		//printCromosome(p1);
		//printCromosome(p2);
		son = crossOver(p1,p2);
		//printf("son\n");
		//printCromosome(son);
		newPop->individuals[k] = son;
	
	
	}
	return newPop;
}

cromosome crossOver(cromosome c1, cromosome c2){
	cromosome result;
	int half = TAMCROMOSOME/2;
	int mutationRate;

	for (int i = 0; i < half; i++)
	{
		result.body[i] = c1.body[i];
		result.body[half+i] = c2.body[half+i];
	}
	if(TAMCROMOSOME%2 == 0){
		result.body[TAMCROMOSOME] = c2.body[TAMCROMOSOME];

	}
	mutationRate = rand()%100;
	
		// if(mutationRate <= MUTATIONRATE){
		// 	result.body[rand()%TAMCROMOSOME] = (rand()+MINRANDOM)%MAXRANDOM;

		// }

	result.fitnes = 0;
	return result;
}

cromosome generateRandomCromosome(){
	cromosome c;
	//c = (cromosome*)malloc(sizeof(cromosome));
	
	int i = 0 ;
	for(i = 0 ; i < TAMCROMOSOME;i++){
		c.body[i] = (rand()+MINRANDOM) % MAXRANDOM;
	}
	return c;
}
population* initPopulation()
{	
	population* p = (population*)malloc(sizeof(population));
	int i;
	for (i = 0 ; i<TAMPOP; i++){
		p->individuals[i] = generateRandomCromosome();
	}
	return p;
}
void printPop(population p)  {
	int i,j;
	srand(time(NULL));
	for(i = 0 ; i <TAMPOP; i++){
		for(j = 0 ; j< TAMCROMOSOME;j++){
			printf("%d",p.individuals[i].body[j]);
		}
		printf("\n");
	}

}

void printPopFitnes(population p)  {
	int i,j;
	srand(time(NULL));
	for(i = 0 ; i <TAMPOP; i++){
		for(j = 0 ; j< TAMCROMOSOME;j++){
			printf("%d",p.individuals[i].body[j]);
		}
		printf(" %f",p.individuals[i].fitnes);
		printf("\n");
	}

}

void printCromosomes(cromosome p[],int length)  {
	int i,j;
	printf("begin Print cromosome");
	for(i = 0 ; i <length; i++){
		for(j = 0 ; j< TAMCROMOSOME;j++){
			printf("%d",p[i].body[j]);
		}
		printf(" %f",p[i].fitnes);
		printf("\n");
	}

}
void printCromosome(cromosome p)  {
	int i,j;
	for(j = 0 ; j< TAMCROMOSOME;j++){
		printf("%d",p.body[j]);
	}
	printf(" %f",p.fitnes);
	printf("\n");
}

void orderPopulation(population* p){
	int i = 0,k = 0;
	cromosome c;
	for(i = 0 ; i < TAMPOP; i ++){
		for(k = 0 ; k <TAMPOP ; k ++){
			if(p->individuals[i].fitnes >p->individuals[k].fitnes){
				c = p->individuals[i];
				p->individuals[i] = p->individuals[k];
				p->individuals[k] = c;

			}
		}
	}
}

void orderCromosomes(cromosome* p){
	int i = 0,k = 0;
	cromosome c;
	for(i = 0 ; i < TAMPOP; i ++){
		for(k = 0 ; k <TAMPOP ; k ++){
			if(p[i].fitnes >p[k].fitnes){
				c = p[i];
				p[i] = p[k];
				p[k] = c;

			}
		}
	}

	printf("%f , %f",p[0].fitnes,p[1].fitnes);
}




void fitnes(population* p,int m, int profit[],int price[]){

	int i,j,sumValue,sumProfit;
	for( i = 0;i < TAMPOP; i ++){
		p->individuals[i].fitnes = 0;
		sumValue = 0 ;
		sumProfit = 0;
		for(j = 0 ; j <TAMCROMOSOME; j ++){
			sumValue+=p->individuals[i].body[j]*price[j];
			sumProfit = sumProfit+(p->individuals[i].body[j]*profit[j]);
		}

		if(sumValue > m){
			p->individuals[i].fitnes = -(sumValue-m);
		}else{
			p->individuals[i].fitnes = (sumValue) + (sumProfit);
		}
		
		//printf("%f\n",p->individuals[i].fitnes);
	}



}
void mutate(population* p){

	int i,j,sumValue,sumProfit,mutationRate;
	for( i = 0;i < TAMPOP; i ++){
		mutationRate = rand()%100;
		if(mutationRate <= MUTATIONRATE){
			if(p->individuals[i].fitnes > 0){
				p->individuals[i].body[rand()%TAMCROMOSOME] += (rand()+MINRANDOM+1)%3;
			}else{
				int aux = (rand()+MINRANDOM)%3;
				int auxIndex = rand()%TAMCROMOSOME;

				while(p->individuals[i].body[auxIndex] - aux < 0){
					printf("while");
					aux = (rand()+MINRANDOM)%MAXRANDOM;
					auxIndex = rand()%TAMCROMOSOME;
				}
				printf("nowhile\n");
				p->individuals[i].body[auxIndex] -= aux;
			}

			
		}
		
		//printf("%f\n",p->individuals[i].fitnes);
	}



}


int main(){
	srand(time(NULL));
	printf("Start\n");
	int profit[10] = {92,57,49,68,60,43,67,84,87,72};
	int price[10] =  {23,31,29,44,53,38,63,85,89,82};
	int money = 165;

	int i;
	int countGen = 0;
	population* p = initPopulation();
	population* auxPop;
	population* auxPop2;
	//printPopFitnes(*p);
	fitnes(p,money,profit,price);
	orderPopulation(p);
	printPopFitnes(*p);

	while(countGen < GERATIONS){
		printf("next Gen\n");
		auxPop =  tournament(*p);
		printf("end tourn\n");
		//printPopFitnes(*auxPop);
		fitnes(auxPop,money,profit,price);
		printf("endFitnes\n");
		mutate(auxPop);
		printf("endMutate\n");
		fitnes(auxPop,money,profit,price);
		printf("endFitnes\n");
		orderPopulation(auxPop);
		printf("endOrder\n");
		printPopFitnes(*auxPop);	
		countGen++;
		p  = auxPop;
	}

	


	

	return 0;
}
