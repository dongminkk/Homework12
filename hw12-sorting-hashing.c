#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */ // 배열 13개
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE //MAX_HASH_TABLE_SIZE도 13개

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a);  //초기화 함수
int freeArray(int *a);  //동적할당 해재하는 함수
void printArray(int *a); // 출력 하는 함수

int selectionSort(int *a); //선택 정렬 함수
int insertionSort(int *a); //삽입 정렬
int bubbleSort(int *a); //버블 정렬
int shellSort(int *a); // 셸 정렬
/* recursive function으로 구현 */
int quickSort(int *a, int n); //퀵 정렬


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht); 

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);


int main()
{
	char command; // 문자형 변수 선언
	int *array = NULL; // 정수형 포인터 array 선언
	int *hashtable = NULL; // 정수형 포인터 hashtable 선언
	int key = -1;
	int index = -1;
	
	srand(time(NULL));

	printf("[----- [kim dongmin] [2017038093] -----]\n");

	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); //기능 선택

		switch(command) {
		case 'z': case 'Z':
			initialize(&array); //초기화
			break;
		case 'q': case 'Q':
			freeArray(array); // 동적할당 해제
			break;
		case 's': case 'S':
			selectionSort(array); //선택 정렬
			break;
		case 'i': case 'I':
			insertionSort(array); //삽입 정렬
			break;
		case 'b': case 'B':
			bubbleSort(array); //버블 정렬
			break;
		case 'l': case 'L':
			shellSort(array); // 셸 정렬
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array); // 출력
			quickSort(array, MAX_ARRAY_SIZE); //퀵 정렬
			printf("----------------------------------------------------------------\n");
			printArray(array); //정렬 후 출력

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array); //출력
			hashing(array, &hashtable); // 해싱
			printArray(hashtable); //해싱 후 정렬
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key); //키값 입력 받음
			printArray(hashtable);// 정렬 후 출력
			index = search(hashtable, key); // 입력 받은 키값 과 같은 인덱스 반환 받음
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]); //출력
			break;

		case 'p': case 'P':
			printArray(array); // 배열 출력
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");//잘못입력에 대한 오류 처리
			break;
		}

	}while(command != 'q' && command != 'Q'); //'q' && 'Q' 이면 반복문 종료

	return 1; //리턴 1
}

int initialize(int** a) // 초기화 함수
{
	int *temp = NULL; //정수형 포인터 temp 선언

	/* array가 NULL인 경우 메모리 할당 */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE); // 동적할당
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else
		temp = *a;

	/* 랜덤값을 배열의 값으로 저장 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}

int freeArray(int *a) //동적할당 해제
{
	if(a != NULL) // a이 널이 될때 까지 
		free(a); //동적할당 해제
	return 0;
}

void printArray(int *a) //출력하는 함수
{
	if (a == NULL) { // a ==NULL 일때 오류 출력 비어 있을때
		printf("nothing to print.\n"); //nothing to print.
		return; // 리턴
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++) // 0부터 MAX_ARRAY_SIZE까지 반복
		printf("a[%02d] ", i); // a출력
	printf("\n"); 
	for(int i = 0; i < MAX_ARRAY_SIZE; i++) // 0부터 MAX_ARRAY_SIZE까지 반복
		printf("%5d ", a[i]); // a출력
	printf("\n");
}


int selectionSort(int *a) //선택 정렬 함수
{
	int min; //정수형 min 선언
	int minindex; //정수형 minindex 선언
	int i, j; //정수형 i, j 선언

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); // 정렬 하기 전 배열 출력

	for (i = 0; i < MAX_ARRAY_SIZE; i++) // MAX_ARRAY_SIZE 만큼 반복
	{
		minindex = i;  //minindex 에 i값 대입
		min = a[i]; // min에 i 번째 a배열 값 대입
		for(j = i+1; j < MAX_ARRAY_SIZE; j++) //MAX_ARRAY_SIZE+1 만큼 반복
		{
			if (min > a[j]) //min > a[j] 일때
			{
				min = a[j]; //min에 a[j] 대입
				minindex = j; //minindex에 j 대입
			}
		}
		a[minindex] = a[i]; //a[minindex]에 a[i] 대입
		a[i] = min; //a[i] 에 min 대입
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); // 정렬 후 배열 출력
	return 0;
}

int insertionSort(int *a) //삽입 정렬
{
	int i, j, t; //정수형 i, j, t 선언

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); // 정렬 하기 전 배열 출력

	for(i = 1; i < MAX_ARRAY_SIZE; i++) // 반복문
	{
		t = a[i]; //t에 a[i]
		j = i; //j 에 i
		while (a[j-1] > t && j > 0) // while문 a[j-1] > t 이고 j > 0 일때
		{
			a[j] = a[j-1];
			j--; //j -1
		}
		a[j] = t; //a[j] 에 t
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); // 정렬 후 배열 출력

	return 0;
}

int bubbleSort(int *a) //버블 정렬
{
	int i, j, t; //정수형 i, j, t 선언

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); // 정렬 하기 전 배열 출력

	for(i = 0; i < MAX_ARRAY_SIZE; i++) // 반복문
	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++) // 반복문
		{
			if (a[j-1] > a[j]) // 조건문 a[j-1] > a[j] 일때
			{
				t = a[j-1]; //t = a[j-1]
				a[j-1] = a[j]; //a[j-1] = a[j]
				a[j] = t; //a[j] = t
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); // 정렬 후 배열 출력

	return 0;
}

int shellSort(int *a) // 셸 정렬
{
	int i, j, k, h, v; //정수형 i, j, k, h, v 선언

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); // 정렬 하기 전 배열 출력

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2) // 반복문
	{
		for (i = 0; i < h; i++) // 반복문
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h) // 반복문
			{
				v = a[j]; //v = a[j]
				k = j; // k = j
				while (k > h-1 && a[k-h] > v) // 반복문 k > h-1 && a[k-h] > v 일때
				{
					a[k] = a[k-h]; // a[k] = a[k-h]
					k -= h; //  k -= h
				}
				a[k] = v; // a[k] = v
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a); // 정렬 후 배열 출력

	return 0;
}

int quickSort(int *a, int n) //퀵 정렬
{
	int v, t; //정수형 v, t 선언
	int i, j; //정수형 i, j 선언

	if (n > 1) // 조건문 n > 1 일때
	{
		v = a[n-1];
		i = -1;
		j = n - 1;

		while(1) // 반복문
		{
			while(a[++i] < v);
			while(a[--j] > v);

			if (i >= j) break;
			t = a[i];
			a[i] = a[j];
			a[j] = t;
		}
		t = a[i];
		a[i] = a[n-1];
		a[n-1] = t;

		quickSort(a, i);
		quickSort(a+i+1, n-i-1);
	}


	return 0;
}

int hashCode(int key) { 
   return key % MAX_HASH_TABLE_SIZE; /* hash code generator, key % MAX_HASH_TABLE_SIZE */
}

int hashing(int *a, int **ht) //해싱
{
	int *hashtable = NULL; //정수형 포인터 hashtable 선언

	/* hash table이 NULL인 경우 메모리 할당 */
	if(*ht == NULL) { //조건문 *ht == NULL 일때
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE); // 동적할당
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else {
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1;

	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		printf("hashtable[%d] = %d\n", i, hashtable[i]);
	*/

	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i];
		hashcode = hashCode(key);
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		if (hashtable[hashcode] == -1)
		{
			hashtable[hashcode] = key;
		} else 	{

			index = hashcode;

			while(hashtable[index] != -1)
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key;
		}
	}

	return 0;
}

int search(int *ht, int key) /* hash table에서 key를 찾아 hash table의 index return */
{
	int index = hashCode(key); // 정수 형 index 선언후 hashCode(key) 대입

	if(ht[index] == key) // 조건문 ht[index] == key 일때
		return index; // 해당 인덱스 리턴

	while(ht[++index] != key) // 반복문 ht[++index] != key 일때 맞을 때 까지 반복하여 찾음
	{
		index = index % MAX_HASH_TABLE_SIZE;
	}
	return index; // 리턴 index
}



