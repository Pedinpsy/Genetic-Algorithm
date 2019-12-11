#define TAMPOP 1000
#define TAMCROMOSOME 15
#define GERATIONS 5555
#define MINRANDOM 0
#define MAXRANDOM 5
#define MINMUTATE 1
#define MAXMUTATE 10
#define NUMCOMPETITOR 3
#define ELITSM 1
#define MUTATIONRATE 80
#define CROSSTYPE "Rand"
#define MAXGENRAND 7
#define MINGENRAND 9
#define GENPRINT 100


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
int* generateRandomValuesToCross(int);



population* tournament(population p){
	population* newPop = (population*)malloc(sizeof(population));
	int k,i,indexs[NUMCOMPETITOR];
	cromosome c[NUMCOMPETITOR]; 

	cromosome p1,p2,auxCromosome,son;
	int aux;

	for( k = 0 ; k < TAMPOP; k++ ){
		//printf("BEGIN TOURNAMENT\n");
		p1 = p.individuals[rand()%(int)(TAMPOP*ELITSM)];
		p2 = p.individuals[rand()%(int)(TAMPOP*ELITSM)];
		//printCromosome(p1);
		//printCromosome(p2);
		for(i = 0 ; i < NUMCOMPETITOR-2 ; i ++){
			//printf("BEGIN TOURNAMENT2\n");
			auxCromosome = p.individuals[rand()%(int)(TAMPOP*ELITSM)];
			if(p1.fitnes < auxCromosome.fitnes){
				p2 = p1;
				p1 = auxCromosome;
			}else if(p2.fitnes<auxCromosome.fitnes){
				p2 = auxCromosome;
			}
			//c[i] = p.individuals[rand()%(int)(TAMPOP*ELITSM)];
			//printf("end TOURNAMENT\n");
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
int* generateRandomValuesToCross(int numGen){
	int aux;
 	int* numbers = (int*)malloc(sizeof(int)*numGen);
	int flag = 1;
		for(int i = 0 ; i < numGen; i ++){
			flag = 1;
			while(flag == 1){
				//printf("while");
				flag = 0;
				aux = rand()%TAMCROMOSOME;
				for(int k = 0; k <=i; k ++ ){
					if(aux == numbers[k]){
						flag = 1;
						break;
					}
				}
			}
			numbers[i] = aux;

		}
		return numbers;

}


cromosome crossOver(cromosome c1, cromosome c2){
	//printf("bbeg cross\n");
	cromosome result;
	int half = TAMCROMOSOME/2;

	if(CROSSTYPE == "Half"){
		for (int i = 0; i < half; i++)

		{
			result.body[i] = c1.body[i];
			result.body[half+i] = c2.body[half+i];
		}
			if(TAMCROMOSOME%2 == 0){
			result.body[TAMCROMOSOME] = c2.body[TAMCROMOSOME];

			}
		}else if(CROSSTYPE == "Rand"){

			for(int i = 0 ; i < TAMCROMOSOME; i ++){
				result.body[i] = c1.body[i];

			}
			int numGen = (rand()+MINGENRAND)%MAXGENRAND;
			//printf("randvall");
			//printf("%d\n",numGen );
			int* numbers = generateRandomValuesToCross(numGen);
		//	printf("end randvall");
			for(int i = 0 ; i < numGen; i ++){
				result.body[numbers[i]] = c1.body[numbers[i]];

			}

		}
		// if(mutationRate <= MUTATIONRATE){
		// 	result.body[rand()%TAMCROMOSOME] = (rand()+MINRANDOM)%MAXRANDOM;

		// }

	result.fitnes = 0;
	//printf("end cross\n");
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
			printf("%d-",p[i].body[j]);
		}
		printf(" %f",p[i].fitnes);
		printf("\n");
	}

}
void printCromosome(cromosome p)  {
	int i,j;
	for(j = 0 ; j< TAMCROMOSOME;j++){
		printf("%d|",p.body[j]);
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
			p->individuals[i].fitnes = ((sumValue)*0.2 + (sumProfit)*0.8);
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
				p->individuals[i].body[rand()%TAMCROMOSOME] += (rand()+MINMUTATE+1)%3;
			}else{
				int aux = (rand()+MINMUTATE)%3;
				int auxIndex = rand()%TAMCROMOSOME;

				while(p->individuals[i].body[auxIndex] - aux < 0){
					aux = (rand()+MINMUTATE)%MAXMUTATE;
					auxIndex = rand()%TAMCROMOSOME;
				}
				p->individuals[i].body[auxIndex] -= aux;
			}

			
		}
		
		//printf("%f\n",p->individuals[i].fitnes);
	}



}


int main(){
	srand(time(NULL));
	printf("Start\n");
	//int profit[10] = {92,57,49,68,60,43,67,84,87,72};
	//int price[10] =  {23,31,29,44,53,38,63,85,89,82};

	//int profit[100] = {94,506,416,992,649,237,457,815,446,422,791,359,667,598,7,544,334,766,994,893,633,131,428,700,617,874,720,419,794,196,997,116,908,539,707,569,537,931,726,487,772,513,81,943,58,303,764,536,724,789,479,142,339,641,196,494,66,824,208,711,800,314,289,401,466,689,833,225,244,849,113,379,361,65,486,686,286,889,24,491,891,90,181,214,17,472,418,419,356,682,306,201,385,952,500,194,737,324,992,224};
	//int price[100] =  {485,326,248,421,322,795,43,845,955,252,9,901,122,94,738,574,715,882,367,984,299,433,682,72,874,138,856,145,995,529,199,277,97,719,242,107,122,70,98,600,645,267,972,895,213,748,487,923,29,674,540,554,467,46,710,553,191,724,730,988,90,340,549,196,865,678,570,936,722,651,123,431,508,585,853,642,992,725,286,812,859,663,88,179,187,619,261,846,192,261,514,886,530,849,294,799,391,330,298,790};
	//int money = 995;


	int profit[15]={825594,1677009,1676628,1523970,943972,97426,69666,1296457,1679693,1902996,1844992,1049289,1252836,1319836,953277};
	int price[15]={382745,799601,909247,729069,467902,44328,34610,698150,823460,903959,853665,551830,610856,670702,488960};
	int money = 7500000;



	cromosome bestguy;

	int i;
	long countGen = 0;
	population* p = initPopulation();
	population* auxPop;
	population* auxPop2;
	//printPopFitnes(*p);
	fitnes(p,money,profit,price);
	orderPopulation(p);
	//printPopFitnes(*p);
	bestguy = p->individuals[0];
	printf("beg Gen\n");
	while(countGen < GERATIONS){
		//printf("next Gen\n");
		auxPop =  tournament(*p);
		//printf("end tourn\n");
		//printPopFitnes(*auxPop);
		fitnes(auxPop,money,profit,price);
		//printf("endFitnes\n");
		mutate(auxPop);
		//printf("endMutate\n");
		fitnes(auxPop,money,profit,price);
	//	printf("endFitnes\n");
		orderPopulation(auxPop);
	//	printf("endOrder\n");
		//printPopFitnes(*auxPop);	
		
		countGen++;
		p  = auxPop;

		if(p->individuals[0].fitnes > bestguy.fitnes){
			bestguy = p->individuals[0];

		}
		if(countGen%GENPRINT == 0){
			printf("gen %d\n", countGen);
			printCromosome(auxPop->individuals[0]);

		}
	}
printf("gen %d\n", countGen);
	printf("o melhor gene foi: \n ");
	printCromosome(bestguy);
	printf("\nfitness: %f",bestguy.fitnes);



	

	return 0;
}
