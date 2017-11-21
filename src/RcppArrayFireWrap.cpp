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
    SEXP af_wrap( const af::array& object ){
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
        }
        //NOTE:there is no af::sparse() in the current open source version of arrayfire
        //if(object.issparse() == true){
        //    const int  RTYPE = Rcpp::traits::r_sexptype_traits<T>::rtype;

        //    IntegerVector dim = IntegerVector::create( object.dims(0), object.dims(1) );

        //    // copy the data into R objects
        //    Vector<RTYPE> x(object.device<T>(), object.device<T>() + object.nonzeros() ) ;
        //    IntegerVector i(/*begin of the row indices of object*/, /*end*/);
        //    IntegerVector p(/*begin of the col indices of object*/, /*end*/);

        //    std::string klass ;
        //    switch( RTYPE ){
        //        case REALSXP: klass = "dgCMatrix" ; break ;
        //        // case INTSXP : klass = "igCMatrix" ; break ; class not exported
        //        case LGLSXP : klass = "lgCMatrix" ; break ;
        //        default:
        //            throw std::invalid_argument( "RTYPE not matched in conversion to sparse matrix" ) ;
        //    }
        //    S4 s(klass);
        //    s.slot("i")   = i;
        //    s.slot("p")   = p;
        //    s.slot("x")   = x;
        //    s.slot("Dim") = dim;
        //    return s;
        //}
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
        ::Rcpp::RObject x = ::RcppArrayFire::af_wrap( data );
        if (data.numdims() > 1)
            x.attr("dim") = wrap(data.dims());
        return x;
    }
}
