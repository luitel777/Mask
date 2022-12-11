#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>

#define ENCRYPTION 5
#define BUFFER 8
#define MESSAGE 1024

void options(int n);

void show();

void green()
{
  printf("\033[0;32m");
}

void blue()
{
	printf("\033[0;34m");
}

void white()
{
	printf("\033[0;37m");
}

void red () 
{
  printf("\033[1;31m");
}

void yellow()
{
  printf("\033[1;33m");
}

void cyan()
{
printf("\033[0;36m");
}

void printPasswd(char *storeFile, char *email)
{
	char *retriveFileContent = strstr(storeFile, email);

	char *fullUsername;
	char *fullPassword;

	fullUsername = malloc(sizeof(char) * 256);
	fullPassword = malloc(sizeof(char) * 256);

	int emailLoop = 0;
	int passwordLoop = 0;

	if(retriveFileContent == 0)
	{  
		printf(" \t\t\t\t\t\t\t  User Id not found. Please enter correct details \n");
	
	    printf("\n\t\t\t\t---------------------------------------------------------------------------------------------\n");
		printf("\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t  Press 'Enter' to continue and 'Esc' to go back");
			char a;
			a=getch();
			while(1)
			{
			switch(a)
			 {
				case '\r':
				show();
				break;
				case 27:
				options(2);
				break;
		   	 }
    		}

	}

	int countProof = 0;
	int i,loop = 0;
	for(i = 0; i < strlen(retriveFileContent); i++)
	{
		if(retriveFileContent[i] == '\n' || retriveFileContent[- 1] == ' ')
		{
			break;
		}
		countProof++;


		if(retriveFileContent[i] == ' ')
		{
			loop = 73;
			int j = i;
			while(retriveFileContent[j] != '\n')
			{
				if(retriveFileContent[j] == ' ')
				{
					printf(" ");
				}else{
					fullPassword[passwordLoop] = retriveFileContent[j] + ENCRYPTION;
					passwordLoop++;
				}
				j++;
			}
		}

		if(loop == 0){
			fullUsername[emailLoop] = retriveFileContent[i];
			emailLoop++;
		}

	}

	printf("\n\t\t\t\t\t\t\t\tEmail: %s\n", fullUsername);
	printf("\t\t\t\t\t\t\t\tPassword: %s\n", fullPassword);

	if(countProof == 0)
	{
		printf("\t\t\t\t\t\t\t Name not found fraud detected. going back to menu");
		options(2);
	}

}

unsigned char* readBytes(unsigned char *bytesRead, FILE *fp, size_t length)
{
	size_t fr = fread(bytesRead, 1, length, fp);
	if(fr == 0)
	{
		fprintf(stderr, "\n\t\t\t\t\t\tError: %s\n", strerror(errno));
	}
	return bytesRead;
}

//for PNG
void header(FILE *fp){
	printf("\n\t\t\t\t\t\t__TESTING IMAGE PROPERTY__\n");

	fseek(fp, 0, SEEK_SET);
	unsigned char *head;
	head = malloc(BUFFER);
	readBytes(head,fp,BUFFER);

	int checkHeader[8] = { 137, 80, 78, 71, 13, 10, 26, 10};
	int i, j = 0;
	
	for(i = 0; i <  8 ;i++){
		if(head[j] != checkHeader[i]){
			fprintf(stderr, "\n\t\t\t\t\t\tInvalid header: File is not a valid PNG\n");
			break;
		}
		j++;
	}
}


int image(int decodeencode, char *strHide, char *fileName){
	if (decodeencode == 1){
		FILE *fn = fopen(fileName, "a+");
		
		if(fn != 0){
			red();
			printf("\n\t\t\t\t\t\t\t\t\tFile cannot be opened\n");
			white();
			return 0;
		}

		printf("\n\t\t\t\t\t\t\t\t%s", strHide);
		fwrite(strHide, sizeof(strHide) * 4 , 1, fn);

		printf("\n\t\t\t\t\t\t\t\tMessage has been hidden\n");
		fclose(fn);
	} else if(decodeencode == 2)
	{
		FILE *fb = fopen(fileName, "r+b");
		header(fb);
		fseek(fb, -MESSAGE, SEEK_END);
		unsigned char *hiddenText;
		
		hiddenText = malloc(MESSAGE);
		
		readBytes(hiddenText, fb, MESSAGE);
    	int i,k;


		for(i = 0; i < MESSAGE ;i++)
		{
			if(hiddenText[i] == 'I' && hiddenText[i+1] == 'E' && hiddenText[i+2] == 'N' && hiddenText[i+3] == 'D')
			{
				printf("\n\t\t\t\t\t\tMessage has been decoded\n");
				for(k = i+4+3+1; k < MESSAGE;k++)
				{
					printf("%c", hiddenText[k]);
				}
			}
		}
		fclose(fb);
	}else if(decodeencode == 3){
		FILE *fb = fopen(fileName, "r+b");
		fseek(fb, -MESSAGE, SEEK_END);
		unsigned char *hiddenText;
		
		hiddenText = malloc(MESSAGE);
		
		readBytes(hiddenText, fb, MESSAGE);
    	int i,k;
		for(i = 0; i < MESSAGE ;i++)
		{
			if(hiddenText[i] == 0XFF && hiddenText[i+1] == 0xD9)
			{
				printf("\n\t\t\t\t\t\tMessage has been decoded\n");
				for(k = i+2; k < MESSAGE;k++)
				{
					printf("%c", hiddenText[k]);
				}
			}
		}
		fclose(fb);
	}
	return 0;
}

void save()
{   char ch;
    system("cls");
    FILE *fp;
	fp = fopen("storage", "a+");
    char email[256], password[256];
	printf("\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("\n\t\t\t\t\t\t\t\t\tUser ID: ");
	scanf("%s", email);
	printf("\t\t\t\t\t\t\t\t\tPassword: ");
	scanf("%s", password);
	int i;
	for(i = 0; i < strlen(email); i++)
	{
     	fwrite(&email[i], 1, 1, fp);
	}
	int space = ' ';
	fwrite(&space, 1, 1, fp);
	for(i = 0; i < strlen(password); i++)
	{
	    int j = password[i];
    	j = j - ENCRYPTION;
    	fwrite(&j, 1, 1, fp);
	}
	int newline = '\n';
	fwrite(&newline, 1, 1, fp);
	fclose(fp);
	printf("\n\n\t\t\t\t\t\t\t\t press 'Enter' to continue and 'Esc' to go back");
	char a;
	a=getch();
	while(1)
	{
		switch(a)
		{
			case '\r':
				save();
				break;
			case 27:
				options(1);
				break;
		}
    }
}

void show()
{    
	FILE *fp;
	char ch;
	system ("cls");
		int loop = 0;
		while(loop == 0)
		{
			fp = fopen("storage", "r");

			if(!fp)
			{    printf("\n\n\n\n\n\n\n\n\n\n\n\n");
				printf("\t\t\t\t\t\tYou have not stored any passwords yet. \n");
				Sleep(3);
				save();
			}
			char *storeFile;
			storeFile = malloc(sizeof(char) * 1024);

			fread(storeFile, 1024, 1, fp);

			char email[256];
			printf("\n\n\n\n\n\n\n\t\t\t\t\t\t\t\tInput User ID or its initials:");
			scanf("%s", email);
			  printf("\n\n\n\t\t\t\t---------------------------------------------------------------------------------------------\n");
			printPasswd(storeFile, email);
			  printf("\n\t\t\t\t---------------------------------------------------------------------------------------------\n");
			fclose(fp);
			
		 	printf("\n\n\n\n\n\n\t\t\t\t\t\t\t press 'Enter' to continue and 'Esc' to go back");
			char a;
			a=getch();
			while(1)
			{
			switch(a)
			 {
				case '\r':
				show();
				break;
				case 27:
				options(2);
				break;
		   	 }
    		}
		}
	ch=getch();
	if(ch==27)
	{
	  options(2);	
	}	
}

void png(n)
{
	char in;
	system("cls");
	if(n==1)
	{
		printf("\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t=> 1. Encode");
	}
	else 
	{
		printf("\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t   1. Encode");
	}
	if(n==2)
	{
		printf("\n\t\t\t\t\t\t\t\t\t\t=> 2. Decode PNG");
	}
	else 
	{
		printf("\n\t\t\t\t\t\t\t\t\t\t   2. Decode PNG");
	}
	if(n==3)
	{
		printf("\n\t\t\t\t\t\t\t\t\t\t=> 3. Decode JPG");
	}
	else 
	{
		printf("\n\t\t\t\t\t\t\t\t\t\t   3. Decode JPG");
	}
	if(n!=1&&n!=2&&n!=3)
	{
		printf("");
	}
	printf("\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\tpress 'Enter' to continue and 'Esc' to go back to menu");
	while(1)
	{
	in=getch();
	switch(in)
	{
		case 49:
			png(1);
			break;
		case 50:
			png(2);
			break;
		case 51:
			png(3);
			break;
		case 27:
			options(3);
			break;
		case'\r':
			if(n==1)
			{   system("cls");
				printf("\n\n\n\n\n\n\t\t\t\t\t\t\t\tSpecify png/jpg filename: ");
	  			char filename[256];
				scanf("%s", filename);
				char strHide[20];
				printf("\n\t\t\t\t\t\t\t\tText to hide: ");
				int c;
				do
				{
					c = getchar();
				}
				while (c != EOF && c != '\n');
					// https://stackoverflow.com/a/5918223
				fgets(strHide, 1024, stdin);
				image(n, strHide, filename);
			}
			if(n==2)
			{   system("cls");
				printf("\n\t\t\t\t\t\t\t\tSpecify png filename\n");
	  			char filename[256];
	  			printf("\t\t\t\t\t\t\t");
				scanf("%s", filename);
				char strHide[20];
				image(n, strHide, filename);	
			}
			if(n == 3){
			system("cls");
				printf("\n\t\t\t\t\t\tSpecify jpg filename\n");
	  			char filename[256];
		  		printf("\t\t\t\t\t");
				scanf("%s", filename);
				char strHide[20];
				image(n, strHide, filename);	
			}
	}
    }
}

void generate()
{
	char ch;
	system("cls");
	int length;
	printf("\n\n\n\t\t\t\t\t\t\t\t\t\tlength: ");
	scanf("%d",&length);
	if (length<= 0){
		printf("Password must be >=1");
		return 1;
	}
	char*password=malloc(length+1);
	char*digits = "0123456789";
	int digits_length = strlen(digits);
	char*lowers = "abcdefghijklmnopqrstuvwxyz";
	int lowers_length = strlen(lowers);
	char*uppers = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int uppers_length = strlen(uppers);
	char*symbols = "!@#$%^&*()";
	int symbols_length = strlen(symbols);
	
	
	srand(time(NULL)*getpid());
	
	
	int i = 0;
	for(i=0;i<length;i++){
		int char_type=rand()%4;
	if(char_type==0){
			password[i]=digits[rand()%digits_length];
			
		}
	else if(char_type==1){
		password[i] = lowers[rand()%lowers_length];
	    }
	else if(char_type==2){
		password[i]=uppers[rand()%uppers_length];
		}
	else{
		password[i]=symbols[rand()%symbols_length];
		}
		
    }
    password[length]='\0';
    printf("\n\t\t\t\t\t\t\t\t\t\t%s\n",password);

	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\tpress 'esc' to go back to menu");
	while(1)
	{
	ch=getch();
	if(ch==27)
	{
	  options(4);	
	}
    }
}

void menu()
{    yellow();
	printf("\n\n\n\n\n\n\n"
	       "\t\t\t\t\t\t\t\t ****    **** ******* ***      ** **     **\n"
           "\t\t\t\t\t\t\t\t ** ** **  ** ******* ****     ** **     **\n"
           "\t\t\t\t\t\t\t\t **  ***   ** **      ** **    ** **     **\n"
           "\t\t\t\t\t\t\t\t **   *    ** ******* **  **   ** **     **\n"
           "\t\t\t\t\t\t\t\t **        ** ******* **   **  ** **     **\n"
           "\t\t\t\t\t\t\t\t **        ** **      **    ** ** **     **\n"
           "\t\t\t\t\t\t\t\t **        ** ******* **     **** *********\n"
           "\t\t\t\t\t\t\t\t **        ** ******* **      *** *********\n\n\n");
           white();
}

void options(int n)
{   char ch;
    system("cls");
    menu();
	if(n==1)
	{   green();
		printf("\t\t\t\t\t\t\t\t\t=> 1. Save user id and password\n");
		white();
	}
	else
	{
    	printf("\t\t\t\t\t\t\t\t\t1. Save user id and password\n");
    }
	if(n==2)
	{   green();
		printf("\t\t\t\t\t\t\t\t\t=> 2. View saved user id and password\n");
		white();
	}
	else
	{
	    printf("\t\t\t\t\t\t\t\t\t2. View saved user id and password\n");
    }
	if(n==3)
	{   green();
		printf("\t\t\t\t\t\t\t\t\t=> 3. Hide message in PNG/JPG image\n");
		white();
	}
	else
	{
    	printf("\t\t\t\t\t\t\t\t\t3. Hide message in PNG/JPG image\n");
    }
    if(n==4)
    {   green();
    	printf("\t\t\t\t\t\t\t\t\t=> 4. Generate password\n");
    	white();
	}
	else
	{
		printf("\t\t\t\t\t\t\t\t\t4. Generate password\n");
	}
	if(n==5)
    {   green();
    	printf("\t\t\t\t\t\t\t\t\t=> 5. Exit Program\n");
    	white();
	}
	else
	{
		printf("\t\t\t\t\t\t\t\t\t5. Exit Program\n");
	}
	while(1)
	{
	ch=getch();
	switch(ch)
	{
		case 49:
			printf("\t\t\t");
			options(1);
			break;
		case 50:
			options(2);
			break;
		case 51:
			options(3);
			break;
		case 52:
			options(4);
			break;
		case 53:
			options(5);
			break;
		case '\r':
			if(n==1)
			{
				save();
			}
			if(n==2)
			{
				show();
			}
			if(n==3)
			{
				png(1);
			}
			if(n==4)
			{
				generate();
			}
			if(n==5)
			{
			  exit(0);
			}
	}
    }
}

void mask()
{   
    printf("\n\n\n\n\n\n\n\n\n\n"
"\t\t\t\t\t\t\t ******   ******           ****           ***********   ***      ***\n"
"\t\t\t\t\t\t\t *** *** *** ***          ******          ***********   ***     ***\n"
"\t\t\t\t\t\t\t ***  ** **  ***         ***  ***         ***           ***    ***\n"
"\t\t\t\t\t\t\t ***   ***   ***        ***    ***        ***           ***   ***\n"
"\t\t\t\t\t\t\t ***    *    ***       ************       ***********   *** ***\n"
"\t\t\t\t\t\t\t ***         ***      **************      ***********   *** ***\n"
"\t\t\t\t\t\t\t ***         ***     ***          ***             ***   ***   ***\n"
"\t\t\t\t\t\t\t ***         ***    ***            ***            ***   ***    ***\n"
"\t\t\t\t\t\t\t ***         ***   ***              ***   ***********   ***     ***\n"
"\t\t\t\t\t\t\t ***         ***  ***                ***  ***********   ***      ***\n");
	printf("\n\n");
		printf("\t\t\t\t\t\t\t\t..............PRESS 'ENTER' TO CONTINUE..............");
		printf("\n");
		char ch;
	while(1)
		{
		if(kbhit)
		{
			ch=getch();
			if(ch==13)
			{
				options(1);
			}
		}
	}
};

int main()
{
	mask();
}
