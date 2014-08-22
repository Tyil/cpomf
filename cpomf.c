/**
 * cpomf is a command line utility to upload files to pomf.se, written in C.
 *
 * License: Modified BSD License
 * Authors: Patrick "Tyil" Spek <p.spek@tyil.nl>
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "cpomf.h"
#include "pomf.c"

/**
 * main
 *
 * @returns int
 */
int main(int argc, char **argv)
{
	// Create variables for getopts
	int c;
	char *file = NULL;

	while ((c = getopt(argc, argv, "clf:v")) != -1) {
		switch (c) {
			case 'c':
				printf("%s\n", read_file("CREDITS"));
				return 0;
				break;
			case 'l':
				printf("%s", read_file("LICENSE"));
				return 0;
				break;
			case 'f':
				upload_file(optarg);
				break;
			case 'v':
				printf("%s\n", version());
				return 0;
				break;
		}
	}
}

const char *read_file(const char *file)
{
	char *buffer = 0;
	long length;
	FILE *f = fopen(file, "r");

	if (f == NULL) {
		sprintf("The %s file does not exist.\n", file, buffer);
		return buffer;
	}

	fseek(f, 0, SEEK_END);
	length = ftell(f);
	fseek(f, 0, SEEK_SET);
	buffer = malloc(length);

	if (buffer) {
		fread(buffer, 1, length, f);
	}

	fclose(f);

	return buffer;
}

void upload_file(const char *file)
{
	const char *url;

	// Attempt to upload the file and get an URL back
	url = pomf_upload_file(file);

	// If NULL was returned, the upload failed
	if (url == NULL) {
		printf("Upload of file %s failed!\n", file);
	} else {
		printf("File '%s' uploaded to %s\n", file, url);
	}
}

const char *version()
{
	return "cpomf, version 0.0.1";
}
