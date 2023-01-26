#include "ordenacao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getNome(char nome[]){
	//substitua por seu nome
	strncpy(nome, "Janaina Saldiva Kshesek", MAX_CHAR_NOME);
	nome[MAX_CHAR_NOME-1] = '\0';//adicionada terminação manual para caso de overflow
}

//a função a seguir deve retornar o seu número de GRR
unsigned int getGRR(){
	return 20224892;
}

int buscaSequencial_aux(int vetor[], int valor, int inicio, int fim, int* numComp){
	if (inicio > fim)
		return -1;
	if (valor == vetor[fim]){
		(*numComp)++;
		return fim;
	}
	(*numComp)++;
	return buscaSequencial_aux(vetor, valor, inicio, fim-1, numComp);
}

int buscaSequencial(int vetor[], int tam, int valor, int* numComparacoes){
	*numComparacoes = 0;
	return buscaSequencial_aux(vetor, valor, 0, tam-1, numComparacoes);
}

int buscaBinaria_aux(int vetor[], int valor, int inicio, int fim, int* numComp){
	
	int m = (inicio+fim)/2;

	if (inicio > fim)
		return -1;

	if (valor == vetor[m]){
		(*numComp)++;
		return m;
	}
	if (valor < vetor[m]){
		(*numComp)++;
		return buscaBinaria_aux(vetor, valor, inicio, m-1, numComp);
	}
	(*numComp)++;
	return buscaBinaria_aux(vetor, valor, m+1, fim, numComp);
}


int buscaBinaria(int vetor[], int tam, int valor, int* numComparacoes){
	*numComparacoes = 0;
	return buscaBinaria_aux(vetor, valor, 0, tam-1, numComparacoes);
}

void troca(int vetor[], int a, int b){
	int x = vetor[a];
	vetor[a] = vetor[b];
	vetor[b] = x;
}


int insertionSort_aux(int vetor[], int inicio, int fim, int* numComp){
	int i = fim;

	if (inicio >= fim)
		return *vetor;

	insertionSort_aux(vetor, inicio, fim-1, numComp);
	
	while (i >inicio && vetor[i-1] > vetor[i])
	{
		troca(vetor, i-1, i);
		(*numComp)++;
		i--;
	}
	return *vetor;
}

int insertionSort(int vetor[], int tam){	
	int numComparacoes = 0;
	insertionSort_aux(vetor, 0, tam-1, &numComparacoes);
	return numComparacoes;
}

int minimo(int vetor[], int inicio, int fim, int* numComp){
	if (inicio == fim)
		return inicio;
	int menor = minimo(vetor, inicio, fim-1, numComp);
	(*numComp)++;
	if (vetor[fim] < vetor[menor]){
		menor = fim;
	}
	return menor;
}

int selectionSort_aux(int vetor[], int inicio, int fim, int* numComp){
	if (inicio >= fim)
		return *vetor;
	troca(vetor, inicio, minimo(vetor, inicio, fim, numComp));
	return selectionSort_aux(vetor, inicio+1, fim, numComp);
}

int selectionSort(int vetor[], int tam){
	int numComp = 0;
	selectionSort_aux(vetor, 0, tam-1, &numComp);
	return numComp;
}

void intercala(int* vetor, int inicio, int fim, int m, int* numComp){
	int i, j, k, l, n;
	int tamanho = fim-inicio+1;
	int* aux = (int *) malloc(tamanho*sizeof(int));

	i = inicio;
	j = m+1;

	for(k=0; k<tamanho; k++){
		(*numComp)++;
		if ((j>fim) || (i<=m && vetor[i] <= vetor[j])){
			aux[k] = vetor[i];
			i++;
		}
		else{
			aux[k] = vetor[j];
			j++;
		}
	}
	for (l=0, n=inicio; l<tamanho; l++, n++){
		vetor[n] = aux[l];
	}

	free(aux);
}

void mergeSort_aux(int vetor[], int inicio, int fim, int* numComp){
	if (inicio >= fim)
		return;
	int m = (inicio+fim)/2;
	mergeSort_aux(vetor, inicio, m, numComp);
	mergeSort_aux(vetor, m+1, fim, numComp);
	intercala(vetor, inicio, fim, m, numComp);
}

int mergeSort(int vetor[], int tam){
	int numComp = 0;
	mergeSort_aux(vetor, 0, tam-1, &numComp);
	return numComp;
}

int particiona(int vetor[], int inicio, int fim, int x, int* numComp){
	int m = inicio-1;
	int i;
	for (i=inicio; i<=fim; i++){
		if (vetor[i] <= x){
			(*numComp)++;
			m++;
			troca(vetor, m, i);
		}
	}
	return m;
}

void quickSort_aux(int vetor[], int inicio, int fim, int* numComp){
	if (inicio >= fim)
		return;
	int m = particiona(vetor, inicio, fim, vetor[fim], numComp);
	quickSort_aux(vetor, inicio, m-1, numComp);
	quickSort_aux(vetor, m+1, fim, numComp);
}

int quickSort(int vetor[], int tam){
	int numComp = 0;
	quickSort_aux(vetor, 0, tam-1, &numComp);
	return numComp;
}

void max_heapify(int vetor[], int i, int tam){
	int esq, dir, maior;
	
	maior = i;
	esq = 2*i + 1;
	dir = 2*i + 2;

	if (esq <= tam && vetor[esq] > vetor[maior])
		maior = esq;
	
	if (dir <= tam && vetor[dir] > vetor [maior])
		maior = dir;

	if (maior != i){
		troca(vetor, i, maior);
		max_heapify(vetor, maior, tam);
	}
}

int constroi_heap_max(int vetor[], int tam){
	int i;
	for(i = tam/2 - 1; i >= 0; i--){
		max_heapify(vetor, i, tam);
	}
	return *vetor;
}

int heapSort_aux(int vetor[], int tam){
	int i;

	constroi_heap_max(vetor, tam);

	for(i = tam - 1; i >= 0; i--){
		troca(vetor, 0, i);
		max_heapify(vetor, 0, i);
	}

	return *vetor;
}

int heapSort(int vetor[], int tam){
	heapSort_aux(vetor, tam-1);
	return 1;
}
