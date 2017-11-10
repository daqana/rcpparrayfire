// -*- mode: C++ -*-
//
// RcppFire.h: Rcpp/ArrayFire glue
//
// Copyright (C) 2015 Kazuki Fukui
//
// This file is part of RcppFire.
//
// RcppFire is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// RcppFire is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with RcppFire.  If not, see <http://www.gnu.org/licenses/>.

#ifndef RcppFire__RcppFire__h
#define RcppFire__RcppFire__h

#if defined(Rcpp_hpp) && !defined(COMPILING_RCPPFIRE)
    #error "The file 'Rcpp.h' should not be included. Please correct to include only 'RcppFire.h'."
#endif

#include <RcppFireForward.h>
#include <Rcpp.h>
#include <RcppFireWrap.h>
#include <RcppFireAs.h>

#endif

