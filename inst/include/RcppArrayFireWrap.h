// -*- mode: C++ -*-
//
// RcppArrayFireWrap.h: Rcpp/ArrayFire glue, support for wrap
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

#ifndef RcppArrayFire__RcppArrayFireWrap__h
#define RcppArrayFire__RcppArrayFireWrap__h

#include <iostream>
#include <memory>
#include <Rcpp.h>
#include <arrayfire.h>

namespace RcppArrayFire{
    // see Rcpp/inst/include/internal/wrap.h for details
    template<typename T> SEXP wrap_array_dispatch(const af::array& object, ::Rcpp::traits::true_type){
        // NOTE: object.host<T>() might cause memory leak, when af_get_data_ptr throws an exception.
        // T* host_ptr = object.host<T>() ; // we do not use this;

        // see arrayfire/src/api/cpp/array.cpp for the details of the following code
        if (object.type() != (af::dtype)af::dtype_traits<T>::af_type) {
            ::Rcpp::stop("Requested type does'nt match with array");
        }
        std::unique_ptr<T[]> host_ptr(new T[object.elements()]);

        try{
            af_err __err = af_get_data_ptr((void *)host_ptr.get(), object.get());
            if(__err != AF_SUCCESS){
                throw af::exception(__FILE__, __LINE__, __err);
            }
        }
        catch (af::exception &e){
            ::Rcpp::Rcerr << e << std::endl;
            ::Rcpp::stop("error in Arrayfire");
        }

        return ::Rcpp::wrap(host_ptr.get(), host_ptr.get() + object.elements()) ;
    }

    template<typename T> SEXP wrap_array_dispatch(const af::array& object, ::Rcpp::traits::false_type){
        // when casting is not needed for wrap, copy directly to R object.
        if (object.type() != (af::dtype)af::dtype_traits<T>::af_type) {
            ::Rcpp::stop("Requested type does'nt match with array");
        }
        const size_t size = static_cast<size_t>(object.elements());
        const int RTYPE = ::Rcpp::traits::r_sexptype_traits<T>::rtype ;
        ::Rcpp::Shield<SEXP> x( Rf_allocVector( RTYPE, size ) );
        try{
            object.host(
                static_cast<void *>(::Rcpp::internal::r_vector_start<RTYPE>(x))
            );
        }
        catch (af::exception &e){
            ::Rcpp::Rcerr << e << std::endl;
            ::Rcpp::stop("error in Arrayfire");
        }

        return ::Rcpp::wrap_extra_steps<T>(x) ;
    }


    template<typename T> SEXP wrap_dense_array( const af::array& object ){
        return wrap_array_dispatch<T>(object, typename ::Rcpp::traits::r_sexptype_needscast<T>());
    }

    template<typename T> SEXP wrap_sparse_array( const af::array& object, const af::storage storage_type ){
        const int RTYPE = Rcpp::traits::r_sexptype_traits<T>::rtype;

        const std::string major = (storage_type == AF_STORAGE_CSR)? "R" : "C";
        std::string klass ;
        switch( RTYPE ){
            case REALSXP:
                klass = std::string("dg") + major + "Matrix";
                break;

            case LGLSXP:
                klass = std::string("lg") + major + "Matrix";
                break;

            default:
                throw std::invalid_argument( "RTYPE not matched in conversion to sparse matrix" );
                break;
        }

        ::Rcpp::S4 s(klass);
        switch ( storage_type ) {
            case AF_STORAGE_CSR:
                s.slot("p") = wrap_dense_array<int>( af::sparseGetRowIdx( object ) );
                s.slot("j") = wrap_dense_array<int>( af::sparseGetColIdx( object ) );
                break;

            case AF_STORAGE_CSC:
                s.slot("i") = wrap_dense_array<int>( af::sparseGetRowIdx( object ) );
                s.slot("p") = wrap_dense_array<int>( af::sparseGetColIdx( object ) );
                break;
        }
        s.slot("x") = wrap_dense_array<T>( af::sparseGetValues( object ) );
        s.slot("Dim") = ::Rcpp::IntegerVector::create( object.dims(0), object.dims(1) );

        return s;
    }

    template<typename T> SEXP wrap_array( const af::array& object ){
        if ( object.issparse() ) {
            return wrap_sparse_array<T>( object, af::sparseGetStorage( object ) );
        }
        else { // if dense array
            return wrap_dense_array<T>( object );
        }
    }

    SEXP wrap_af_impl( const af::array& object ) ;
} /* namespace RcppArrayFire */

#endif
