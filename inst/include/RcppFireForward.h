// -*- mode: C++ -*-
//
// RcppFireForward.h: Rcpp/ArrayFire glue
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

#ifndef RcppFire__RcppFireForward__h
#define RcppFire__RcppFireForward__h

#include <RcppCommon.h>
#include <Rconfig.h>
//#include <RcppFireConfig.h>

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
    }  
}

#endif
