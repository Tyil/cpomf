/**
 * cpomf is a command line utility to upload files to pomf.se, written in C.
 *
 * License: Modified BSD License
 * Authors: Patrick "Tyil" Spek <p.spek@tyil.nl>
 *          inuoppai
 */

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

#include "pomf.h"
#include "main.h"

#define MAX_LINE 1024

#ifndef INSTALL_PATH
	#define INSTALL_PATH "."
#endif

/**
 * main
 *
 * @returns int
 */
int main(int argc, char **argv)
{
	// Create variables for getopts
	int c;

	while ((c = getopt(argc, argv, "cf:hlv")) != -1) {
		switch (c) {
			case 'c':
				printf("%s\n", read_file("CREDITS"));
				return 0;
				break;
			case 'f':
				upload_file(optarg);
				break;
			case 'h':
				printf("%s\n", read_file("README.md"));
				return 0;
				break;
			case 'l':
				printf("%s", read_file("LICENSE"));
				return 0;
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
	char fp[MAX_LINE];
	long length;
	FILE *f;

	// Set the filepath
	strcpy(fp, INSTALL_PATH);
	strcat(fp, "/share/cpomf/");
	strcat(fp, file);

	// Attempt to open the file
	f = fopen(fp, "r");

	// Check if opening succeeded
	if (f == NULL) {
		fprintf(stderr, "The file '%s' doesn't exist.\n", fp);
		return "";
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
	char url[MAX_LINE] = {0};

	// Attempt to upload the file and get an URL back
	if(pomf_upload_file(file, url) == 0) {
		printf("%s\t%s\n", file, url);
	} else {
		printf("%s\tFAILED\n\n", file);
	}
}

const char *version()
{
	return "cpomf, version 1.0.2";
}
