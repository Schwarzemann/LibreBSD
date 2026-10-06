#	libcrypto from LibreSSL 4.3.3 (C-only). Built to the object directory only.

LIB=	crypto
USE_FORT?= yes	# cryptographic software
USE_SHLIBDIR=	yes

.include <bsd.own.mk>
.include <bsd.shlib.mk>

.include "../Makefile.inc"
CPPFLAGS+=	-DLIBRESSL_INTERNAL -DLIBRESSL_CRYPTO_INTERNAL
CPPFLAGS+=	-I${LIBRESSLDIST}/crypto
CPPFLAGS+=	-I${LIBRESSLDIST}/crypto/aes
CPPFLAGS+=	-I${LIBRESSLDIST}/crypto/asn1
CPPFLAGS+=	-I${LIBRESSLDIST}/crypto/bio
CPPFLAGS+=	-I${LIBRESSLDIST}/crypto/bn
CPPFLAGS+=	-I${LIBRESSLDIST}/crypto/bytestring
CPPFLAGS+=	-I${LIBRESSLDIST}/crypto/conf
CPPFLAGS+=	-I${LIBRESSLDIST}/crypto/dh
CPPFLAGS+=	-I${LIBRESSLDIST}/crypto/dsa
CPPFLAGS+=	-I${LIBRESSLDIST}/crypto/curve25519
CPPFLAGS+=	-I${LIBRESSLDIST}/crypto/ec
CPPFLAGS+=	-I${LIBRESSLDIST}/crypto/ecdh
CPPFLAGS+=	-I${LIBRESSLDIST}/crypto/ecdsa
CPPFLAGS+=	-I${LIBRESSLDIST}/crypto/err
CPPFLAGS+=	-I${LIBRESSLDIST}/crypto/evp
CPPFLAGS+=	-I${LIBRESSLDIST}/crypto/hidden
CPPFLAGS+=	-I${LIBRESSLDIST}/crypto/hmac
CPPFLAGS+=	-I${LIBRESSLDIST}/crypto/lhash
CPPFLAGS+=	-I${LIBRESSLDIST}/crypto/mlkem
CPPFLAGS+=	-I${LIBRESSLDIST}/crypto/modes
CPPFLAGS+=	-I${LIBRESSLDIST}/crypto/ocsp
CPPFLAGS+=	-I${LIBRESSLDIST}/crypto/pkcs12
CPPFLAGS+=	-I${LIBRESSLDIST}/crypto/rsa
CPPFLAGS+=	-I${LIBRESSLDIST}/crypto/sha
CPPFLAGS+=	-I${LIBRESSLDIST}/crypto/stack
CPPFLAGS+=	-I${LIBRESSLDIST}/crypto/x509
CPPFLAGS+=	-I${LIBRESSLDIST}/include/compat
CPPFLAGS+=	-I${LIBRESSLDIST}/include
CPPFLAGS+=	-I${LIBRESSLDIST}/crypto/arch/amd64
CPPFLAGS+=	-I${LIBRESSLDIST}/crypto/bn/arch/amd64

.include "srcs.inc"

.include <bsd.lib.mk>
