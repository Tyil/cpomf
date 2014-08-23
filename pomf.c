/**
 * License: Modified BSD License
 * Authors: Patrick "Tyil" Spek <p.spek@tyil.nl>
 */

#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <jansson.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>

#include "pomf.h"

int pomf_upload_file(const char *file, char *url)
{
	// cURL declarations
	CURL *curl;
	CURLcode curlResponse;
	struct curl_httppost *post = NULL;
	struct curl_httppost *last = NULL;

	// fileinfo declarations
	struct stat fileInfo;
	FILE *fd;
	struct pomf_cb_struct s;

	// jansson JSON parser declarations
	json_t *jsonRoot, *jsonFiles, *jsonArray, *jsonUrl;
	json_error_t error;

	// Attempt to open the file
	fd = fopen(file, "rb");

	// File couldn't be opened
	if (!fd) {
		fprintf(stderr, "fopen(%s) failed", file);
		return 1;
	}

	// Attempt to read filesize
	if (fstat(fileno(fd), &fileInfo) != 0) {
		fprintf(stderr, "fstat(fileno(%s)) failed\n", file);
		return 2;
	}

	// Initialize the cURL session
	curl = curl_easy_init();

	// Check if the cURL session created succesfully
	if (curl == NULL) {
		fprintf(stderr, "curl_easy_init() failed\n");
		return 3;
	}

	// Set cURL options
	curl_formadd(&post, &last,
		CURLFORM_COPYNAME, "files[]",
		CURLFORM_FILE, file,
		CURLFORM_CONTENTTYPE, "application/octet-stream",
		CURLFORM_END);
	curl_easy_setopt(curl, CURLOPT_URL, "http://pomf.se/upload.php");
	curl_easy_setopt(curl, CURLOPT_READDATA, fd);
	curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE, (curl_off_t)fileInfo.st_size);
	curl_easy_setopt(curl, CURLOPT_HTTPPOST, post);
	curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
	curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, pomf_cb_func);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);

	// Init the HTTP response string
	pomf_cb_init(&s);

	// Send the cURL request
	curlResponse = curl_easy_perform(curl);

	// Check if we got a positive response
	if (curlResponse != CURLE_OK) {
		free(s.ptr);
		fprintf(stderr, "curl_easy_perform() failed\n");
		return 4;
	}

	// Parse the JSON response
	jsonRoot  = json_loads(s.ptr, 0, &error);
	jsonFiles = json_object_get(jsonRoot, "files");
	jsonArray = json_array_get(jsonFiles, 0);
	jsonUrl   = json_object_get(jsonArray, "url");

	// Cleanup the cURL data
	free(s.ptr);
	curl_easy_cleanup(curl);

	// Create the url
	strcpy(url, "http://a.pomf.se/");
	strcat(url, json_string_value(jsonUrl));

	return 0;
}

void pomf_cb_init(struct pomf_cb_struct *s) {
	s->len = 0;
	s->ptr = malloc(s->len+1);

	if (s->ptr == NULL) {
		fprintf(stderr, "malloc() failed\n");
		exit(EXIT_FAILURE);
	}

	s->ptr[0] = '\0';
}

size_t pomf_cb_func(void *ptr, size_t size, size_t nmemb, struct pomf_cb_struct *s)
{
	size_t new_len = s->len + size*nmemb;
	s->ptr = realloc(s->ptr, new_len+1);

	if (s->ptr == NULL) {
		fprintf(stderr, "realloc() failed\n");
		exit(EXIT_FAILURE);
	}

	memcpy(s->ptr+s->len, ptr, size*nmemb);
	s->ptr[new_len] = '\0';
	s->len = new_len;

	return size*nmemb;
}
