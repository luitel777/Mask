#include "mask.h"

int main(int argc, char *argv[])
{
		const struct option mask_options[] = {
				{"help", 0, NULL, 'h'},
				{"image", 0, NULL, 'i'},
				{"passwd", 0, NULL, 'p'},
				{NULL, 0, NULL, 0}
		};
		if(argc < 2){
				fprintf(stderr, "%s", "error: specify options. Try --help\n");
		}
		int next_option = getopt_long(argc, argv, "hip", mask_options, NULL);
		switch(next_option){
				case 'h':
						fprintf(stdout, "%s", "-h or --help for this information\n"
												"-i or --image for image parsing\n"
												"-p or --passwd for password hiding/retriving\n");
						break;
				case 'i':
						mask_image();
						break;
				case 'p':
						mask_passwd();
						break;
				default:
						fprintf(stderr, "%s", "argument is not found\n");
						break;
		}

}
