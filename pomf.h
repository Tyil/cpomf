/**
 * License: Modified BSD License
 * Authors: Patrick "Tyil" Spek <p.spek@tyil.nl>
 *          inuoppai
 */

#ifndef _POMF_H
#define _POMF_H

struct string {
	char *ptr;
	size_t len;
};

void pomf_upload_file(const char*, char*);
void init_string(struct string *s);
size_t writefunc(void *ptr, size_t size, size_t nmemb, struct string *s);

#endif
