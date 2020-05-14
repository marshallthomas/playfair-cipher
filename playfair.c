#include "cipherHelper.c"
int main(int argc, char *argv[])
{
	if(argc<=4)
	{
		printf("Proper usage involves three inputs\n");
		printf("./a.out inputfile outputfile cipher key\n");
		printf("Where inputfile is the file to be decoded/encoded.\n");
		printf("Where output file is the file to be created by encoding/decoding the inputfile\n");
		printf("cipher is 1 or 2.  1 for encoding the input file, 2 for decoding the input file\n");
		printf("key is the five letter code that is to be the key for the playfair cipher.\n");
		exit(0);
	}
	char inputFile[30], outputFile[30];
	char key[20];
	int cipher;
	strcpy(inputFile, argv[1]);
	strcpy(outputFile, argv[2]);
	cipher=argv[3][0]-48;
	char cipherTable[5][5];
	strcpy(key, argv[4]);
	FILE *inputPointer, *outputPointer;
	inputPointer=fopen(inputFile, "r");
	outputPointer=fopen(outputFile, "w");
	systemCheck(inputPointer, key);
	createTable(cipherTable, key);
	encryptOrDecrypt(inputPointer, outputPointer, cipherTable, cipher);

	printCipherTable(cipherTable);
	return(0);	
}
