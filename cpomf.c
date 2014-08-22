/**
 * cpomf is a command line utility to upload files to pomf.se, written in C.
 *
 * License: Modified BSD License
 * Authors: Patrick "Tyil" Spek <p.spek@tyil.nl>
 *          dakidaki
 *          jewsdidwtc
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "cpomf.h"

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

	// Make booleans for all the special outputs
	int pVersion = 0;
	int pLicense = 0;
	int pCredits = 0;

	while ((c = getopt(argc, argv, "clf:v")) != -1) {
		switch (c) {
			case 'c':
				pCredits = 1;
				break;
			case 'l':
				pLicense = 1;
				break;
			case 'f':
				file = optarg;
				break;
			case 'v':
				pVersion = 1;
				break;
		}
	}

	// Show the license if requested
	if (pLicense == 1) {
		printf("%s", readfile("LICENSE"));
		return 0;
	}

	// Show the version if requested
	if (pVersion == 1) {
		printf("%s\n", version());
		return 0;
	}

	// Show the credits if requested
	if (pCredits == 1) {
		printf("%s\n", readfile("CREDITS"));
		return 0;
	}

	// Upload a file if given
	if (file == NULL) {
		printf("No file given for upload.\n");
		return 1;
	}

	return 0;
}

const char *readfile(const char *file)
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

const char *version()
{
	return "cpomf, version 0.0.1";
}
