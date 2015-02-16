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

#include <arrayfire.h>

/* forward declarations */
namespace RcppFire{
	template<af::dtype AF_DTYPE> class typed_array;
}

namespace Rcpp {
    /* support for wrap */
    SEXP wrap ( const af::array& ) ;
    
    namespace traits {
	/* support for as */
	template<af::dtype AF_DTYPE> class Exporter<RcppFire::typed_array<AF_DTYPE>>;
    } // namespace traits 
}

#endif
