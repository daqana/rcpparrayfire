// -*- mode: C++ -*-
//
// RcppArrayFireForward.h: Rcpp/ArrayFire glue
//
// Copyright (C) 2015 Kazuki Fukui
// Copyright (C) 2017 Ralf Stubner (R Institute GmbH)
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

#ifndef RcppArrayFire__RcppArrayFireForward__h
#define RcppArrayFire__RcppArrayFireForward__h

#include <RcppCommon.h>
#include <Rconfig.h>

#include <arrayfire.h>

/* forward declarations */
namespace RcppArrayFire{
    template<
        af::dtype AF_DTYPE,
        af::storage AF_STORAGETYPE> class typed_array;
}

namespace Rcpp {
    /* support for wrap */
    template <> SEXP wrap (const af::array&);
    template <> SEXP wrap (const af::dim4&);

    /* support for as */
    template <> af::dim4 as (SEXP);

    namespace traits {
    /* support for as */
    template<
        af::dtype AF_DTYPE,
        af::storage AF_STORAGETYPE> class Exporter<RcppArrayFire::typed_array<AF_DTYPE, AF_STORAGETYPE>>;
    }
}

#endif
