#                                               -*- Autoconf -*-
# Copyright (C) 2015 Kazuki Fukui
# Copyright (C) 2017, 2018 Ralf Stubner (R Institute GmbH)
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

# use deprecated CXX1X* to support R versions 3.1.0 to 3.3.3
CXX11=`"${R_HOME}/bin/R" CMD config CXX1X`
CXX11STD=`"${R_HOME}/bin/R" CMD config CXX1XSTD`
CXX="${CXX11} ${CXX11STD}"
CXXFLAGS=`"${R_HOME}/bin/R" CMD config CXX1XFLAGS`
CPPFLAGS=`"${R_HOME}/bin/R" CMD config CPPFLAGS`
AC_LANG(C++)
AC_REQUIRE_CPP
AC_PROG_CXX

AS_IF([test $(uname) == "Darwin"],
            [
             AF_BACKEND="opencl"
             AF_RPATH="-Wl,-rpath,/usr/local/lib"
            ],
            [
             AF_BACKEND=""
             AF_RPATH=""
            ])

# set backend
AC_ARG_WITH([backend],
            AC_HELP_STRING([--with-backend=TYPE],
                           [set one of cpu, cuda or opencl (default=blank for unified backend)]),
            [AF_BACKEND="${with_backend}"],
            [])

AC_SUBST([AF_INCLUDE], "")
AC_SUBST([AF_LIBS], "-laf${AF_BACKEND}")

# set path to root of arrayfire
AC_ARG_WITH([arrayfire],
            AC_HELP_STRING([--with-arrayfire=PREFIX],
                           [path to where arrayfire is installed]),
            [
             AF_INCLUDE="-I${with_arrayfire}/include ${AF_INCLUDE}"
             AF_LIBS="-L${with_arrayfire}/lib ${AF_LIBS}"
             AF_RPATH="-Wl,-rpath,${with_arrayfire}/lib"
            ],
            [])

CPPFLAGS="${CPPFLAGS} ${AF_INCLUDE}"
AF_LIBS="${AF_LIBS} ${AF_RPATH}"
LDFLAGS="${LDFLAGS} ${AF_LIBS}"

# check for arrayfire header
AC_CHECK_HEADER([arrayfire.h],
    [],
    [AC_MSG_ERROR([unable to find arrayfire.h])])

AC_MSG_CHECKING([for libaf${AF_BACKEND}.so])
        AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[
#include <arrayfire.h>
#include <string>
const std::string info = af::infoString();]])],
                [AC_MSG_RESULT(yes)],
                [
                 AC_MSG_RESULT(no)
                 AC_MSG_ERROR([unable to find libaf${AF_BACKEND}.so])
                ])


AC_CONFIG_FILES([src/Makevars R/flags.R])
AC_OUTPUT

echo
echo "Final src/Makevars"
cat src/Makevars
