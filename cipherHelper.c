#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void systemCheck(FILE* , char[5]);
void createTable(char[5][5], char[5]);
int keycheck(char[5], int);
char toCapitalize(char);
void printCipherTable(char[5][5]);
void convertBuffer(char[2], char[5][5], int, int[2]);
int findPosition(int[2], char, char[5][5]);
//debug print statement, shows completed cipher table. 
void printCipherTable(char cipherTable[5][5])
{
	printf("The cipher table is now below\n");
	for(int i=0; i<5; i++)
	{
		for(int j=0; j<5; j++)
		{
			printf("[%c]", cipherTable[i][j]);
		}
		printf("\n");
	}
	
}
//checks that the key provided is indeed five letters
int keycheck(char key[], int number)
{
	for(int i=0; i<5; i++)
	{
		if(number==key[i])
		{
			return(-1);
		}
	}
	return(1);
}
//capitalizes lower case letters
char toCapitalize(char input)
{
	input=input-32;
	return(input);
}
//creates the cipher table based on the five letter key that was provided
void createTable(char Table[5][5], char key[5])
{
	int charCounter=65;
	for(int i=0; i<5; i++)
	{
		Table[0][i]=key[i];
	}
	for(int j=1; j<5; j++)
	{
		for(int i=0; i<5; i++)
		{
			while(keycheck(key, charCounter)==-1 || charCounter==74)
			{
				charCounter++;
			}

			Table[j][i]=charCounter++;
		}
	}
}
//Dummy Checking at beginning of program, makes sure that user is using it correctly
void systemCheck(FILE *inputPointer, char key[])
{
	if(inputPointer==NULL)
	{
		printf("input file did not open\n");
		exit(0);
	}
	if(strlen(key)!=5)
	{
		printf("a playfair cipher is supposed to have a key size of 5.\n");
		printf("Try again\n");
		exit(0);
	}
}
//returns position of character in cipher table
//returns -1, -1 if invalid character
int findPosition(int position[2], char buffer, char cipherTable[5][5])
{
	for(int i=0; i<5; i++)
	{
		for(int j=0; j<5; j++)
		{
			if(buffer==cipherTable[i][j] || (buffer==74 && cipherTable[i][j]==73))
			{
				position[0]=i;
				position[1]=j;
				return(0);
			}
		}
	}	
	position[0]=-1;
	position[1]=-1;	
	printf("positions are %i and %i\n", position[0], position[1]);
	return(-1);
}
/* This function converts each letter in the input file to their corresponding output decryption or encryption.  
If the character is not alphabetical, then it passes on through.  This will retain the input file's normal format, while still doing a playfair cipher.  However, this means that the letter pairs may not necessarily be directly next to each other.  The intent was that, upon decryption, the file will appear as it originally was.  */
void encryptOrDecrypt(FILE *inputPointer, FILE *outputPointer, char cipherTable[5][5], int cipher)
{
	char buffer=0;
	unsigned char keyBuffer[20];
	keyBuffer[19]='\0';
	int counter=0;
	int garbageCounter=0;
	int letterLocation[2];
	while(buffer!=EOF)
	{
		buffer=getc(inputPointer);
		if(buffer>=65 && buffer<=(65+25))
		{
			keyBuffer[garbageCounter+counter]=buffer;
			letterLocation[counter]=garbageCounter+counter;
			counter++;
		}
		else if(buffer>=97 && buffer<=(97+25))
		{
			keyBuffer[garbageCounter+counter]=toCapitalize(buffer);
			letterLocation[counter]=garbageCounter+counter;
			counter++;
		}
		else if(buffer!=EOF)
		{
			keyBuffer[garbageCounter+counter]=buffer;
			garbageCounter++;
		}
		if(counter==2)
		{
			keyBuffer[garbageCounter+counter]='\0';
			printf("input is %c %c\n", keyBuffer[letterLocation[0]], keyBuffer[letterLocation[1]]);
			convertBuffer(keyBuffer, cipherTable, cipher, letterLocation);
			printf("output is %c %c\n", keyBuffer[letterLocation[0]], keyBuffer[letterLocation[1]]);
			fprintf(outputPointer, "%s", keyBuffer);
			printf("%s\n", keyBuffer);
			counter=0;
			garbageCounter=0;
		}
	}
	if(counter==1)
	{
		keyBuffer[garbageCounter+counter]='X';
		letterLocation[counter]=garbageCounter+counter;
		counter++;
		convertBuffer(keyBuffer, cipherTable, cipher, letterLocation);
		fprintf(outputPointer, "%s", keyBuffer);
	}
} 
// converts the characters in the buffer to their respective encrypted/decrypted positions. 
void convertBuffer(char buffer[2], char cipherTable[5][5], int cipher, int letterLocation[2])
{
	int positionOne[2];
	int positionTwo[2];
	findPosition(positionOne, buffer[letterLocation[0]], cipherTable);
	findPosition(positionTwo, buffer[letterLocation[1]], cipherTable);
	if(positionOne[0]==-1 || positionTwo[0]==-1)
	{
		printf("position finder is wrong\n");
		printf("characters are %c and %c\n", buffer[letterLocation[0]], buffer[letterLocation[1]]);
		printCipherTable(cipherTable);
		exit(0);
	}
	//If the setup is a line that is horizontal
	if(positionOne[0]==positionTwo[0])
	{
		if(cipher==1)
		{
			positionOne[1]++;
			positionTwo[1]++;
		}
		else
		{
			positionOne[1]--;
			positionTwo[1]--;
		}
		if(positionOne[1]>=5)
		{
			positionOne[1]=0;
		}
		else if(positionTwo[1]>=5)
		{
			positionTwo[1]=0;
		}
		if(positionOne[1]<0)
		{
			positionOne[1]=4;
		}
		else if(positionTwo[1]<0)
		{
			positionTwo[1]=4;
		}
	}
	else if(positionOne[1]==positionTwo[1])
	{
		if(cipher==1)
		{
			positionOne[0]++;
			positionTwo[0]++;
		}
		else
		{
			positionOne[0]--;
			positionTwo[0]--;
		}
		if(positionOne[0]>=5)
		{
			positionOne[0]=0;
		}
		else if(positionTwo[0]>=5)
		{
			positionTwo[0]=0;
		}
		if(positionOne[0]<0)
		{
			positionOne[0]=4;
		}
		else if(positionTwo[0]<0)
		{
			positionTwo[0]=4;
		}
	}
	else
	{	
		int temp;
		temp=positionOne[1];
		positionOne[1]=positionTwo[1];
		positionTwo[1]=temp;	
	}
	buffer[letterLocation[0]]=cipherTable[positionOne[0]][positionOne[1]];
	buffer[letterLocation[1]]=cipherTable[positionTwo[0]][positionTwo[1]];
	
}
