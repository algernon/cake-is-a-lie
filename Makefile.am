bin_PROGRAMS			= src/cake-is-a-lie

pkgdata_DATA			= data/cake.png data/debian-logo.png

src_cake_is_a_lie_CFLAGS	= ${caca_CFLAGS} ${imlib2_CFLAGS} \
				-DDATADIR="\"${pkgdatadir}\""
src_cake_is_a_lie_LDFLAGS	= ${caca_LIBS} ${imlib2_LIBS}

EXTRA_DIST			= COPYING
