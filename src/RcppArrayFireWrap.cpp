// -*- mode: C++ -*-
//
// RcppArrayFireWrap.cpp: Rcpp/ArrayFire glue, support for wrap
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

#include <RcppArrayFireWrap.h>

namespace RcppArrayFire{
    SEXP wrap_af_impl( const af::array& object ){
        ::Rcpp::RObject x;

        switch(object.type()){
            case f64:
                x = wrap_array<double>( object ) ;
                break;
            case c64:
                x = wrap_array<std::complex<double>>( object ) ;
                break;
            case f32:
                x = wrap_array<float>( object ) ;
                break;
            case c32:
                x = wrap_array<std::complex<float>>( object ) ;
                break;
            case s32:
                x = wrap_array<int>( object ) ;
                break;
            case u32:
                x = wrap_array<unsigned int>( object ) ;
                break;
            default:
                Rcpp::stop("Unsopprted data type");
                break;
        }

        return x;
    }
} /* namespace RcppArrayFire */

namespace Rcpp{
    /* wrap */
    template <> SEXP wrap (const af::dim4& dims) {
        std::vector<dim_t> res(dims.ndims());
        for(int i = 0; i < dims.ndims(); ++i)
            res[i] = dims[i];
        return wrap(res);
    }

    template <> SEXP wrap (const af::array& data ){
        ::Rcpp::RObject x = ::RcppArrayFire::wrap_af_impl( data );
        if (data.issparse() == false && data.numdims() > 1)
            x.attr("dim") = wrap(data.dims());
        return x;
    }
}
