// -*- mode: C++; c-indent-level: 4; c-basic-offset: 4; indent-tabs-mode: nil; -*-
/* :tabSize=4:indentSize=4:noTabs=false:folding=explicit:collapseFolds=1: */
//
// RcppArmadilloForward.h: Rcpp/Armadillo glue
//
// Copyright (C)  2010 - 2014  Dirk Eddelbuettel, Romain Francois and Douglas Bates
//
// This file is part of RcppArmadillo.
//
// RcppArmadillo is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// RcppArmadillo is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with RcppArmadillo.  If not, see <http://www.gnu.org/licenses/>.

#ifndef RcppFire__RcppFireForward__h
#define RcppFire__RcppFireForward__h

#include <RcppCommon.h>
#include <Rconfig.h>
#include <RcppFireConfig.h>

#define AF_EXTRA_MAT_PROTO RcppFire/Mat_proto.h
#define AF_EXTRA_MAT_MEAT  RcppFire/Mat_meat.h
#define AF_EXTRA_COL_PROTO RcppFire/Col_proto.h
#define AF_EXTRA_COL_MEAT  RcppFire/Col_meat.h
#define AF_EXTRA_ROW_PROTO RcppFire/Row_proto.h
#define AF_EXTRA_ROW_MEAT  RcppFire/Row_meat.h

// using this define makes the R RNG have precedent over both the
// C++11-based RNG provided by Armadillo, as well as the C++98-based
// fallback.
//
// One can use the C++11-based on by commenting out the following
// #define and also selecting C++11 (eg via src/Makevars* or the
// DESCRIPTION file) and/or defining #define-ing ARMA_USE_CXX11_RNG
#define AF_RNG_ALT         RcppFire/Alt_R_RNG.h

#include <arrayfire.h>

/* forward declarations */
namespace Rcpp {
    /* support for wrap */
    SEXP wrap ( const af::array& ) ;
    
    namespace traits {
	/* support for as */
	class Exporter< af::array > ;
    } // namespace traits 

    class ConstReferenceInputParameter;
    class ReferenceInputParameter;
    class ConstInputParameter;

}

#endif
