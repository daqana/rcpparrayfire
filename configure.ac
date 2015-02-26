#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.
AC_PREREQ([2.63])
AC_INIT([rcppfire], [0.0.1])

: ${R_HOME=`R RHOME`}
if test -z "${R_HOME}" ; then
	echo "could not determin R_HOME"
	exit 1
fi

AC_LANG([C++])

CXX=`${R_HOME}/bin/R CMD config CXX`
CXXFLAGS=`${R_HOME}/bin/R CMD config CXXFLAGS`
LDFLAGS=`${R_HOME}/bin/R CMD config LDFLAGS`


dnl  TODO : windows support
dnl AC_CANONICAL_HOST


# check complier version
AC_CHECK_PROG(CXX_CHECK, [${CXX}], found, missing)
if test "${CXX_CHECK}" = "missing" ; then
	AC_MSG_ERROR([unable to find ${CXX}])
	exit 1
fi

case "${CXX}" in
	g++)
		GCC_VERSION=`g++ -dumpversion \
			| sed -e 's/\.\(@<:@0-9@:>@@<:@0-9@:>@\)/\1/g' -e 's/\.\(@<:@0-9@:>@\)/0\1/g' -e 's/^@<:@0-9@:>@\{3,4\}$/&00/'`
		AC_MSG_CHECKING([for GCC version >= 4.8])
		if test ${GCC_VERSION} -gt 40800 ; then
			AC_MSG_RESULT(yes)
		else
			AC_MSG_RESULT(no)
			AC_MSG_ERROR([GCC is too old])
		fi
		;;
	clang++) 
		dnl FIXME : `clang++ --verion` is bit different on OSX, clang++ & LLVM
		CLANG_VERSION=`clang++ --version | grep version \
			| awk '{print $3}' \
			| sed -e 's/\.\(@<:@0-9@:>@@<:@0-9@:>@\)/\1/g' -e 's/\.\(@<:@0-9@:>@\)/0\1/g' -e 's/^@<:@0-9@:>@\{3,4\}$/&00/'`
		AC_MSG_CHECKING([for CLANG version >= 3.3])
		if test ${CLANG_VERSION} -gt 30300 ; then
			AC_MSG_RESULT(yes)
		else
			AC_MSG_RESULT(no)
			AC_MSG_ERROR([CLANG is too old])
		fi
		;;
	icpc)
		ICPC_VERSION=`icpc -v 2>&1 | awk '{print $3}' \
			| sed -e 's/\.\(@<:@0-9@:>@@<:@0-9@:>@\)/\1/g' -e 's/\.\(@<:@0-9@:>@\)/0\1/g' -e 's/^@<:@0-9@:>@\{3,4\}$/&00/' `
		AC_MSG_CHECKING([for Intel C++ Complier version >= 15.0])
		if test ${ICPC_VERSION} -gt 150000 ; then
			AC_MSG_RESULT(yes)
		else
			AC_MSG_RESULT(no)
			AC_MSG_ERROR([Intel C++ compiler is too old])
		fi
		;;
	*)
		AC_MSG_ERROR([unsupported C++ complier])
		exit 1
		;;
esac

# set path to root of arrayfire
AC_ARG_WITH([arrayfire], 
			AC_HELP_STRING([--with-arrayfire=PREFIX], 
						   [path to where arrayfire is installed (default=/usr/local)]),
			[],
			[with_arrayfire="/usr/local"])

# set build type
AC_ARG_WITH([build-type], 
			AC_HELP_STRING([--with-build-type], 
						   [set one of cpu, cuda, or opencl (default=cuda)]),
			[],
			[with_build_type=cuda])

if test -e ${with_arrayfire} ; then
	CXXFLAGS="${CXXFLAGS} -I${with_arrayfire}/include"
	LDFLAGS="${LDFLAGS} -L${with_arrayfire}/lib"
else
	AC_MSG_ERROR([Unable to find ${with_arrayfire}])
	exit 1
fi

# check for arrayfire header
AC_CHECK_HEADER([arrayfire.h],
				[],
				[
				 AC_MSG_ERROR([unable to find arrayfire.h])
				 exit 1
				])

# check for arrayfire lib
AC_MSG_CHECKING([for libafxxx.so])
case "${with_build_type}" in
	cpu|cuda|opencl)
		dnl AC_SEARCH_LIBS([af::info], [af${with_build_type}],
		dnl 			  [],
		dnl 			  [
		dnl 			   AC_MSG_ERROR([unable to find libaf${with_build_type}.so])
		dnl 			   exit 1
		dnl 			  ])
		LDFLAGS="${LDFLAGS} -laf${with_build_type}"
		AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[
#include <arrayfire.h>
const int ndev = af::devicecount();]])],
						   [AC_MSG_RESULT(yes)],
						   [
							AC_MSG_RESULT(no)
						    AC_MSG_ERROR([unable to find libaf${with_build_type}.so])
						    exit 1
						   ])
		;;
	*)
		AC_MSG_ERROR([build type must be one of cpu, cuda, or opencl])
		exit 1
		;;
esac


AC_SUBST([AF_INCLUDE], ["-I${with_arrayfire}/include"])
AC_SUBST([AF_LIBS], ["-L${with_arrayfire}/lib -laf${with_build_type}"])

AC_CONFIG_FILES([src/Makevars R/flags.R])
AC_OUTPUT
