#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// RecordType
struct RecordType
{
	int	id;
	char name;
	int	order; 
	struct RecordType* next;
};

// Fill out this structure
struct HashType
{
	struct RecordType* down;
};

// Compute the hash function
int hash(int x, int tableSize)
{
	int num;
	num = (x % tableSize);
	return num;
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

void insertRecord(struct HashType *hashTable, struct RecordType *record, int tableSize)
{
	int index = hash(record->id, tableSize);

	if (hashTable[index].down == NULL)
	{
		hashTable[index].down = record; // record is a pointer that points to RecordType struct, which has the address
		hashTable[index].down->next = NULL;
	}
	
	else
	{
		struct RecordType *temp = hashTable[index].down;
		
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		
		temp->next = record;
		temp->next->next = NULL;
	}
    // call the hash function to get the index
    // if the RecordType at that index is NULL
        // set 'record' equal to the HashType pointer in the table at index
    // else
        // traverse to the end of the linkedlist and add 'record' to the end of it
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
	int i;

	for (i=0;i<hashSz;++i)
	{
		struct RecordType* temp = pHashArray[i].down;

		printf("Index %d -> ", i);

		while (temp != NULL)
		{
			printf("%d, %c, %d -> ", temp->id, temp->name, temp->order);
			temp = temp->next;
		}

		printf("NULL\n");
		// if index is occupied with any records, print all
	}
}

int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0;

	recordSz = parseData("input.txt", &pRecords);
	printRecords(pRecords, recordSz);
	
	int tableSize = 11;

	struct HashType* info = calloc(tableSize, sizeof(struct HashType));

	for (int x = 0; x < recordSz; ++x)
	{
		insertRecord(info, &pRecords[x], tableSize);
	}

	displayRecordsInHash(info, tableSize);
	
	free(info);
	free(pRecords);

	return 0;
	// Your hash implementation
}