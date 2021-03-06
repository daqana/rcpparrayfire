#                                               -*- Autoconf -*-
# Copyright (C) 2015 Kazuki Fukui
# Copyright (C) 2017 Ralf Stubner (R Institute GmbH)
# Copyright (C) 2019 Ralf Stubner
#
# This file is part of RcppArrayFire.
#
# RcppArrayFire is free software: you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# (at your option) any later version.
#
# RcppArrayFire is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with RcppArrayFire.  If not, see <http://www.gnu.org/licenses/>.
#
# Process this file with autoconf to produce a configure script.
AC_PREREQ([2.69])
AC_INIT([rcpparrayfire], [0.0.0])

: ${R_HOME=`R RHOME`}
if test -z "${R_HOME}" ; then
    echo "could not determin R_HOME"
    exit 1
fi

AC_MSG_CHECKING(for R < 3.4.0 for CXX1X flag use)
R_GE_34=`"${R_HOME}/bin/R" --vanilla --slave -e 'cat(if (getRversion() >= numeric_version("3.4.0")) "yes" else "no")'`
if test "x$R_GE_34" == "xyes"; then
   AC_MSG_RESULT([no])
   CXX11=`"${R_HOME}/bin/R" CMD config CXX11`
   CXX11STD=`"${R_HOME}/bin/R" CMD config CXX11STD`
   CXXFLAGS=`"${R_HOME}/bin/R" CMD config CXX11FLAGS`
else
   AC_MSG_RESULT([yes])
   CXX11=`"${R_HOME}/bin/R" CMD config CXX1X`
   CXX11STD=`"${R_HOME}/bin/R" CMD config CXX1XSTD`
   CXXFLAGS=`"${R_HOME}/bin/R" CMD config CXX1XFLAGS`
fi
CXX="${CXX11} ${CXX11STD}"
CPPFLAGS=`"${R_HOME}/bin/R" CMD config CPPFLAGS`
AC_LANG(C++)
AC_REQUIRE_CPP
AC_PROG_CXX

AC_SUBST([AF_INCLUDE])
AC_SUBST([AF_LIBS])

# set path to root of arrayfire
AC_ARG_WITH([arrayfire],
            AC_HELP_STRING([--with-arrayfire=PREFIX],
                           [path to where arrayfire is installed]),
            [AF_PATH = ${with_arrayfire}],
            [])

if test -n "${AF_PATH}"
then
    AF_INCLUDE="-I${AF_PATH}/include"
    AF_LIBS="-L${AF_PATH}/lib -laf -Wl,-rpath,${AF_PATH}/lib"
else
    # let's look around -- code inspiered by RPostgreSQL
    AC_MSG_NOTICE([checking for ArrayFire header])
	for dir in \
	/usr/include \
	/usr/local/include \
	/opt/arrayfire/include
	do
      AC_MSG_NOTICE([Checking directory ${dir}.])
	   if test -f ${dir}/arrayfire.h
	   then
	   	AF_INCLUDE="-I${dir}"
		break
	   fi
	done
   AC_MSG_NOTICE([checking for ArrayFire library])
	for dir in \
	/usr/lib \
	/usr/lib64 \
	/usr/local/lib \
	/usr/local/lib64 \
	/opt/arrayfire/lib \
	/opt/arrayfire/lib64
	do
      AC_MSG_NOTICE([Checking directory ${dir}.])
	   if test -r ${dir}/libaf.so -o -r ${dir}/libaf.dylib
	   then
         AF_LIBS="-L${dir} -laf -Wl,-rpath,${dir}"
		break
	   fi
	done
fi

AS_IF([test -z "${AF_INCLUDE}" -o -z "${AF_LIBS}"], [AC_MSG_ERROR([Cannot find ArrayFire installation.])])

CPPFLAGS="${CPPFLAGS} ${AF_INCLUDE}"
LDFLAGS="${LDFLAGS} ${AF_LIBS}"

# check for arrayfire header
AC_CHECK_HEADER([arrayfire.h],
    [],
    [AC_MSG_ERROR([unable to find arrayfire.h])])

AC_MSG_CHECKING([for libaf.so])
        AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[
#include <arrayfire.h>
#include <string>
const std::string info = af::infoString();]])],
                [AC_MSG_RESULT(yes)],
                [
                 AC_MSG_RESULT(no)
                 AC_MSG_ERROR([unable to find libaf.so])
                ])


AC_CONFIG_FILES([src/Makevars R/flags.R])
AC_OUTPUT
