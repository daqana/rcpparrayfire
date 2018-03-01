// -*- mode: C++ -*-
//
// RcppArrayFire.h: Rcpp/ArrayFire glue
//
// Copyright (C) 2015 Kazuki Fukui
//
// This file is part of RcppArrayFire.
//
// RcppArrayFire is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// RcppArrayFire is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with RcppArrayFire.  If not, see <http://www.gnu.org/licenses/>.

#ifndef RcppArrayFire__RcppArrayFire__h
#define RcppArrayFire__RcppArrayFire__h

#if defined(Rcpp_hpp) && !defined(COMPILING_RCPPARRAYFIRE)
    #error "The file 'Rcpp.h' should not be included. Please correct to include only 'RcppArrayFire.h'."
#endif

#include <RcppArrayFireForward.h>
#include <Rcpp.h>
#include <RcppArrayFireWrap.h>
#include <RcppArrayFireAs.h>

#endif

