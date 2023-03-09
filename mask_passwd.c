#include "mask.h"

void mask_passwd(){

		fprintf(stdout, "%s", "1 for saving\n"
						"2 for retriving\n");
		int n;
		scanf("%d", &n);
		if (n == 1){
				save();
		}else if(n == 2){
				show();
		}
};

void printPasswd(char *storeFile, char *email)
{
		char *retriveFileContent = strstr(storeFile, email);

		char *fullUsername;
		char *fullPassword;

		fullUsername = malloc(sizeof(char) * 256);
		fullPassword = malloc(sizeof(char) * 256);

		int emailLoop = 0;
		int passwordLoop = 0;


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
		}

}

void save()
{
		char ch;
		FILE *fp;
		fp = fopen("storage", "a+");
		char email[256], password[256];
		printf("\n\n\n\n\n\n\n\n\n");
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
}

void show()
{    
		FILE *fp;
		char ch;
		fp = fopen("storage", "r");

		if(!fp)
		{    printf("\n\n\n\n\n\n\n\n\n\n\n\n");
				printf("\t\t\t\t\t\tYou have not stored any passwords yet. \n");
				save();
		}
		char *storeFile;
		storeFile = malloc(sizeof(char) * 1024);

		fread(storeFile, 1024, 1, fp);

		char email[256];
		printf("\n\n\n\n\t\t\t\t\t\t\t\tInput User ID or its initials:");
		scanf("%s", email);
		printf("\n\n\n\t\t\t\t---------------------------------------------------------------------------------------------\n");
		printPasswd(storeFile, email);
		printf("\n\t\t\t\t---------------------------------------------------------------------------------------------\n");
		fclose(fp);
}
