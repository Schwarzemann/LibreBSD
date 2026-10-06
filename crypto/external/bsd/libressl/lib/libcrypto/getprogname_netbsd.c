/*	$NetBSD$	*/

/*
 * NetBSD-local, not part of the LibreSSL import.
 *
 * LibreSSL's include/compat/stdlib.h renames getprogname() to
 * libressl_getprogname() unconditionally, and the portable tree only
 * supplies that name for systems without getprogname(). NetBSD has
 * getprogname() in libc, so forward the renamed symbol to it.
 */

#include <stdlib.h>

#undef getprogname
extern const char *getprogname(void);

const char *
libressl_getprogname(void)
{
	return getprogname();
}
