#	libssl from LibreSSL 4.3.3 (C-only). Built to the object directory only.

LIB=	ssl
USE_FORT?= yes	# cryptographic software
USE_SHLIBDIR=	yes

.include <bsd.own.mk>
.include <bsd.shlib.mk>

.include "../Makefile.inc"
CPPFLAGS+=	-DLIBRESSL_INTERNAL
CPPFLAGS+=	-I${LIBRESSLDIST}/ssl
CPPFLAGS+=	-I${LIBRESSLDIST}/ssl/hidden
CPPFLAGS+=	-I${LIBRESSLDIST}/crypto
CPPFLAGS+=	-I${LIBRESSLDIST}/crypto/bio
CPPFLAGS+=	-I${LIBRESSLDIST}/include/compat
CPPFLAGS+=	-I${LIBRESSLDIST}/include
CPPFLAGS+=	-I${LIBRESSLDIST}/crypto/arch/amd64

.include "srcs.inc"
LIBDPLIBS+=	crypto	${.CURDIR}/../libcrypto

.include <bsd.lib.mk>
