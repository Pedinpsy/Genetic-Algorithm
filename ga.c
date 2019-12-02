#define TAMPOP 10
#define TAMCROMOSOME 10
#define GERATIONS 1000
#define MINRANDOM 0
#define MAXRANDOM 5
#define NUMCOMPETITOR 5
#define ELITSM 0.2


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
void printCromosomes(cromosome[]);



void tournament(population p){
	int k,i,indexs[NUMCOMPETITOR];
	cromosome c[NUMCOMPETITOR]; 

	for( k = 0 ; k < TAMPOP; k++ ){
		for(i = 0 ; i < NUMCOMPETITOR ; i ++){
			c[i] = p.individuals[rand()%(int)(TAMPOP*ELITSM)];

		}
		//printCromosomes(c);
		//scanf("%d");
		//orderCromosomes(c);
	}
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

void printCromosomes(cromosome p[])  {
	int i,j;
	srand(time(NULL));
	for(i = 0 ; i <TAMPOP; i++){
		for(j = 0 ; j< TAMCROMOSOME;j++){
			printf("%d",p[i].body[j]);
		}
		printf(" %f",p[i].fitnes);
		printf("\n");
	}

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


int main(){
	printf("Begin\n");
	int profit[10] = {92,57,49,68,60,43,67,84,87,72};
	int price[10] =  {23,31,29,44,53,38,63,85,89,82};
	int money = 165;

	int i;
	population* p = initPopulation();
	//printPopFitnes(*p);
	printf("Begin\n");
	fitnes(p,money,profit,price);
	orderPopulation(p);
	printPopFitnes(*p);
	tournament(*p);
	


	

	return 0;
}
