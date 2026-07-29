#include <unistd.h>
#include <stdio.h>
#include <strings.h>
#include <stdlib.h>

#ifdef GUI_GTK
#include <gui/gtk/gtk.h>
#endif

enum GUI_TOOLKIT {
	GTK,
	NUM_OF_GUITOOLKITS
};

enum OUTPUT_FORMAT {
	JSON,
	NUM_OF_OUTPUT_FORMATS
};

enum RENDERER {
	DEFAULT,
	NUM_OF_RENDERERS
};

enum GUI_TOOLKIT gui_toolkit;
enum OUTPUT_FORMAT output_format;
enum RENDERER renderer;

const char* GUI_TOOLKIT_NAMES[NUM_OF_GUITOOLKITS] = {
	"GTK"
};

const char* OUTPUT_FORMAT_NAMES[NUM_OF_OUTPUT_FORMATS] = {
	"JSON"
};

const char* RENDERER_NAMES[NUM_OF_RENDERERS] = {
	"default"
};

FILE* fin;
FILE* fout;
int json_state;

static void usage() {
	printf("Usage: xocl [-h] [-i <input>] [-o <output>] [-g <gui>]\n");
	printf("            [-r <renderer>] [-f <format>]\n");
	printf("\n");
	printf("Example:\n");
	printf("xsltproc gtk.xsl app.html | xocl > data.json\n");
	printf("\n");
	printf("Default input: stdin\n");
	printf("Default output: stdout\n");
	printf("\n");
	printf("Currently available GUI options:\n");
	printf("- gtk (default)\n");
	printf("\n");
	printf("Currently available renderer options:\n");
	printf("- default (default)\n");
	printf("\n");
	printf("Currently available format options:\n");
	printf("- json (default)\n");
}

static int parse_option_output_format(char* optstr) {
	int selected = -1;
	for(int i = 0; i < NUM_OF_OUTPUT_FORMATS; i++) {
		if ( strcasecmp(OUTPUT_FORMAT_NAMES[i], optstr) == 0 ) {
			selected = i;
		}
	}
	return selected;
}

static int parse_option_gui_toolkit(char* optstr) {
	int selected = -1;
	for(int i = 0; i < NUM_OF_GUITOOLKITS; i++) {
		if ( strcasecmp(GUI_TOOLKIT_NAMES[i], optstr) == 0 ) {
			selected = i;
		}
	}
	return selected;
}

static int parse_option_renderer(char* optstr) {
	int selected = -1;
	for(int i = 0; i < NUM_OF_RENDERERS; i++) {
		if ( strcasecmp(RENDERER_NAMES[i], optstr) == 0 ) {
			selected = i;
		}
	}
	return selected;
}

void json_start(void) {
	json_state = 0;
	fputc('{', fout);
}

void json_string(const char *s) {
	FILE* fp = fout;
	fputc('"', fp);
	for (; *s; s++) {
		switch (*s) {
		case '"':  fputs("\\\"", fp); break;
		case '\\': fputs("\\\\", fp); break;
		case '\n': fputs("\\n", fp); break;
		case '\r': fputs("\\r", fp); break;
		case '\t': fputs("\\t", fp); break;
		default:   fputc(*s, fp);
		}
	}
	fputc('"', fp);
}

void json_key(const char* s) {
	if (json_state) {
		fputc(',', fout);
	}
	fprintf(fout, "\"%s\":", s);
	json_state = 1;
}

void json_close(void) {
	json_state = 0;
	fputc('}', fout);
}

int readxml(char** xmlbuffer) {
	size_t cap;
	int chunk = 10;
	int bytes = 0;
	size_t pos = 0;
	cap = chunk + 1;
	char* xmlui = malloc(cap);
	while( ( bytes = fread(xmlui + pos, 1, chunk, fin) ) ) {
		pos += bytes;
		cap = cap + chunk - (chunk - bytes);
		xmlui = realloc(xmlui, cap);
		if (xmlui == NULL) {
			return 1;
		}
	}
	*(xmlui + pos) = 0;
	*xmlbuffer = xmlui;
	return 0;
}

int main(int argc, char **argv) {
	int ch;
	fin = stdin;
	fout = stdout;
	output_format = JSON;
	gui_toolkit = GTK;
	renderer = DEFAULT;
	while ((ch = getopt(argc, argv, ":i:o:f:g:r:h")) != -1) {
		switch (ch) {
		case ':':
			fprintf(stderr, "option -%c requires an argument", optopt);
			return 1;
		case 'h':
			usage();
			return 0;
		case 'i':
			fin = fopen(optarg, "r");
			if (!fin) {
				fprintf(stderr, "Unable to open input file.\n");
				return 1;
			}
			break;
		case 'o':
			fout = fopen(optarg, "w");
			if (!fout) {
				fprintf(stderr, "Unable to open output file.\n");
				return 1;
			}
			break;
		case 'f':
			if ((output_format = parse_option_output_format(optarg)) == -1) {
				fprintf(stderr, "Unknown output format.\n");
				return 1;
			}
			break;
		case 'g':
			if ((gui_toolkit = parse_option_gui_toolkit(optarg)) == -1) {
				fprintf(stderr, "Unknown GUI toolkit identifier.\n");
				return 1;
			}
			break;
		case 'r':
			if ((renderer = parse_option_renderer(optarg)) == -1) {
				fprintf(stderr, "Unknown renderer backend identifier.\n");
				return 1;
			}
			break;
		}
	}
	int status = 1;
	if (gui_toolkit == GTK) {
		#ifdef GUI_GTK
		status = gui_gtk_start();
		#else
		fprintf(stderr, "GUI toolkit GTK not available.\n");
		#endif
	}
	return status;
}
