#include "mask.h"

unsigned char* readBytes(unsigned char *bytesRead, FILE *fp, size_t length)
{
		size_t fr = fread(bytesRead, 1, length, fp);
		if(fr == 0)
		{
				fprintf(stderr, "\n\t\t\t\t\t\tError: %s\n", strerror(errno));
		}
		return bytesRead;
}

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
				if(fn == NULL){
						fprintf(stderr, "%s\n", strerror(errno));
						return -1;
				}

				printf("\n\t\t\t\t\t\t\t\t%s", strHide);
				fwrite(strHide, sizeof(strHide) * 4 , 1, fn);

				printf("\n\t\t\t\t\t\t\t\tMessage has been hidden\n");
				fclose(fn);

		} else if(decodeencode == 2) {
				FILE *fb = fopen(fileName, "r+b");
				if(fb == NULL){
						fprintf(stderr, "%s\n", strerror(errno));
						return -1;
				}

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
				if(fb == NULL){
						fprintf(stderr, "%s\n", strerror(errno));
						return -1;
				}

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

void mask_image()
{
		fprintf(stdout, "%s", "1 for encoding\n"
						"2 for decoding png\n"
						"3 for decoding jpg\n");
		int n;
		scanf("%d", &n);
		if (n == 1){

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
				fgets(strHide, 20, stdin);
				image(n, strHide, filename);
		}
		if(n==2)
		{   
				printf("\n\t\t\t\t\t\t\t\tSpecify png filename\n");
				char filename[256];
				printf("\t\t\t\t\t\t\t");
				scanf("%s", filename);
				char strHide[20];
				image(n, strHide, filename);	
		}
		if(n == 3){
				printf("\n\t\t\t\t\t\tSpecify jpg filename\n");
				char filename[256];
				printf("\t\t\t\t\t");
				scanf("%s", filename);
				char strHide[20];
				image(n, strHide, filename);	
		}

}

