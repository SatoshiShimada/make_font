
#include <stdio.h>

int main(int argc, char *argv[])
{
	FILE *fin, *fout;
	char buf[1024];
	unsigned short font;
	int i, number = 0;

	if(argc != 3) {
		fprintf(stderr, "Usage: %s [font source file name] [font output file name]\n", argv[0]);
		return -2;
	}

	fin = fopen(argv[1], "r");
	if(!fin) {
		fprintf(stderr, "Error: file open [%s]\n", argv[1]);
		return -1;
	}
	fout = fopen(argv[2], "w");
	if(!fout) {
		fprintf(stderr, "Error: file open [%s]\n", argv[2]);
		return -1;
	}

	//fprintf(fout, "unsigned short fontdata[] = {\n\t");
	fprintf(fout, "unsigned short font_bitmap_data[] = {\n\t");
	fprintf(fout, "/* %d */\n\t", number++);

	do {
		fgets(buf, sizeof(buf), fin);
		if(buf[0] == '!') break;
		if(buf[0] == '#') continue;
		if(buf[0] == '\n') {
			fprintf(fout, "\n\t/* %d */\n\t", number++);
			continue;
		}

		for(i = 0; i < 16; i++) {
			if(buf[i] == '@') {
				font &= ~(0x0001 << (15 - i));
			} else if(buf[i] == '.') {
				font |= (0x0001 << (15 - i));
			} else {
				fprintf(stderr, "unknown charactor [%c]\n", buf[i]);
			}
		}
		fprintf(fout, "0x%04x, ", font);
	} while(!feof(fin));

	fprintf(fout, "\n};\n");

	fclose(fin);
	fclose(fout);

	return 0;
}
