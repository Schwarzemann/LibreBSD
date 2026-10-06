#	LibreSSL 4.3.3 shared settings for NetBSD (C-only, no assembly).
#	See dist/ for the vendor tree; these flags mirror its CMake config,
#	with HAVE_* set to what NetBSD libc and headers provide.

LIBRESSLDIST=	${.CURDIR}/../../dist

# Left unset: EXPLICIT_BZERO, STRTONUM (NetBSD hides it behind _OPENBSD_SOURCE; the
# compat/ copy is renamed libressl_strtonum and so cannot clash with libc), GETAUXVAL,
# GNU_STACK. compat/ supplies explicit_bzero and strtonum;
# OPENSSL_NO_ASM selects the portable C code paths (no .S, no arch bn_arch.c).
# GETAUXVAL and GNU_STACK are Linux-only.
CPPFLAGS+=	-DHAVE_ARC4RANDOM_BUF -DHAVE_ARC4RANDOM_UNIFORM -DHAVE_ARPA_NAMESER_H -DHAVE_ASPRINTF -DHAVE_CLOCK_GETTIME -DHAVE_ENDIAN_H -DHAVE_ERR_H -DHAVE_FTRUNCATE -DHAVE_GETDELIM -DHAVE_GETENTROPY -DHAVE_GETLINE -DHAVE_GETOPT -DHAVE_GETPAGESIZE -DHAVE_MEMMEM -DHAVE_NETINET_IP_H -DHAVE_REALLOCARRAY -DHAVE_RESOLV_H -DHAVE_STRCASECMP -DHAVE_STRLCAT -DHAVE_STRLCPY -DHAVE_STRNDUP -DHAVE_STRNLEN -DHAVE_STRSEP -DHAVE_SYSLOG -DHAVE_SYSLOG_R
CPPFLAGS+=	-DOPENSSL_NO_ASM -DOPENSSL_NO_HW_PADLOCK -D__BEGIN_HIDDEN_DECLS= -D__END_HIDDEN_DECLS=
CPPFLAGS+=	-DOPENSSLDIR=\"/etc/openssl\"
