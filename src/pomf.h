/**
 * License: Modified BSD License
 * Authors: Patrick "Tyil" Spek <p.spek@tyil.nl>
 *          inuoppai
 */

#ifndef _POMF_H
#define _POMF_H

struct pomf_cb_struct {
	char *ptr;
	size_t len;
};

int pomf_upload_file(const char*, char*);
void pomf_cb_init(struct pomf_cb_struct *s);
size_t pomf_cb_func(void *ptr, size_t size, size_t nmemb, struct pomf_cb_struct *s);

#endif
