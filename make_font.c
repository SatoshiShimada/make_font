
#include <stdio.h>

int main(int argc, char *argv[])
{
	FILE *fin, *fout;
	char buf[1024];
	unsigned short font;
	int i, number = 0;

	if(argc != 3) return -2;

	fin = fopen(argv[1], "r");
	if(!fin) return -1;
	fout = fopen(argv[2], "w");
	if(!fout) return -1;

	fprintf(fout, "unsigned short fontdata[] = {\n\t");

	do {
		fgets(buf, sizeof(buf), fin);
		if(buf[0] == '!') break;
		if(buf[0] == '\n') {
			fprintf(fout, "\n\t/* %d */\n\t", number);
			number++;
			continue;
		}

		for(i = 0; i < 16; i++) {
			if(buf[i] == '@') {
				font &= ~(0x01 << (15 - i));
			} else if(buf[i] == '.') {
				font |= (0x01 << (15 - i));
			} else {
				fprintf(stderr, "unknown charactor\n");
			}
		}
		fprintf(fout, "0x%04x, ", font);
	} while(!feof(fin));

	fprintf(fout, "\n};\n");

	fclose(fin);
	fclose(fout);

	return 0;
}
