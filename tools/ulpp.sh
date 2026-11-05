#!/bin/bash
# ulpp.sh SRC VERSION > out.c : preprocess an ultralib source file (path relative to ultralib/src, e.g. io/pimgr.c)
# for libgultra_rom version VERSION (I, J, K, L ...) with the KMC cccp, ready for ul.py. ULTRALIB= the ultralib checkout.
U=${ULTRALIB:?set ULTRALIB to the ultralib checkout}
CCCP=$(find ~/.local/share/decompnet/toolchains/gcc-2.7.2-kmc -name cccp -type f | head -1)
DBG=-DNDEBUG; [ "$2" = I ] && DBG=   # 2.0I libgultra_rom was built without -DNDEBUG (ultralib makefiles/gcc.mk)
exec $CCCP -P -undef -nostdinc -I$U -I$U/include -I$U/include/compiler/gcc -I$U/include/PR -I$U/src \
  -D_LANGUAGE_C -D_MIPS_SZLONG=32 -D__USE_ISOC99 -DF3DEX_GBI_2 -DBUILD_VERSION=VERSION_$2 \
  -DBUILD_VERSION_STRING=\"2.0$2\" -D_FINALROM $DBG -D_ULTRA64 -D__GNUC__=2 -Dmips -D__mips__ -D_MIPS_ISA=3 \
  -DMIPSEB -D_MIPSEB -D_MIPS_SIM=1 "$U/src/$1"
