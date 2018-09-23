// -*- mode: C++ -*-
//
// RcppArrayFireAs.h: Rcpp/ArrayFire glue, support for as
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

#ifndef RcppArrayFire__RcppArrayFireAs__h
#define RcppArrayFire__RcppArrayFireAs__h

#include <algorithm>
#include <iterator>
#include <type_traits>
#include <arrayfire.h>

namespace RcppArrayFire{
    template<af::dtype AF_DTYPE> struct dtype2cpp{};
    template<> struct dtype2cpp<f32>{ typedef float type ; };
    template<> struct dtype2cpp<c32>{ typedef af::cfloat type ; };
    template<> struct dtype2cpp<f64>{ typedef double type ; };
    template<> struct dtype2cpp<c64>{ typedef af::cdouble type ; };
    template<> struct dtype2cpp<b8>{ typedef bool type ; };
    template<> struct dtype2cpp<s32>{ typedef int type ; };
    template<> struct dtype2cpp<u32>{ typedef unsigned int type ; };


    template<af::dtype AF_DTYPE>
    class typed_array : public af::array{
    public:
        typed_array() : af::array() {}
        ~typed_array(){}
        typed_array(const af::array &src_data) : af::array(src_data) {};
    };

    template<
        af::dtype AF_DTYPE,
        af::storage AF_STORAGETYPE = AF_STORAGE_CSR>
    class typed_sparray : public af::array{
    public:
        typed_sparray() : af::array() {}
        ~typed_sparray(){}
        typed_sparray(const af::array &src_data) : af::array(src_data) {};
    };

    template<typename value_type>
    class SEXP2CxxPtr : private ::Rcpp::Shield<SEXP> {
    private:
        static const int RTYPE = ::Rcpp::traits::r_sexptype_traits<value_type>::rtype;
        typedef typename ::Rcpp::traits::storage_type<RTYPE>::type STORAGE ;

        STORAGE* start;
        std::vector<value_type> buff;

        void initialize_buff(SEXP , std::vector<value_type>&, ::Rcpp::traits::false_type){
            // do nothing
        }
        void initialize_buff(SEXP object, std::vector<value_type> &buff, ::Rcpp::traits::true_type){
             buff.resize( Rf_length( object ) );
            ::Rcpp::internal::export_indexing<
                std::vector<value_type>,
                value_type
                >( object, buff ) ;
        }

        const STORAGE* data_dispatch(::Rcpp::traits::false_type) const {
            return start;
        }
        const value_type* data_dispatch(::Rcpp::traits::true_type) const {
            return buff.data();
        }
        size_t size_dispatch(::Rcpp::traits::false_type) const {
            return ::Rf_length(this->t);
        }
        size_t size_dispatch(::Rcpp::traits::true_type) const {
            return buff.size();
        }

        // disable copy
        SEXP2CxxPtr(const SEXP2CxxPtr&);
        SEXP2CxxPtr operator=(const SEXP2CxxPtr&);

    public:
        SEXP2CxxPtr( SEXP x )
            : ::Rcpp::Shield<SEXP>(::Rcpp::r_cast<RTYPE>(x))
        {
            start = ::Rcpp::internal::r_vector_start<RTYPE>(this->t) ;

            initialize_buff(
                x,
                buff,
                typename ::Rcpp::traits::r_sexptype_needscast<value_type>()
            );
        }
        ~SEXP2CxxPtr(){}

        const value_type* data() const {
            return data_dispatch(
                typename ::Rcpp::traits::r_sexptype_needscast<value_type>()
            );
        };

        size_t size() const {
            return size_dispatch(
                typename ::Rcpp::traits::r_sexptype_needscast<value_type>()
            );
        }
    };

}

namespace Rcpp{
namespace internal{
    template<typename T>
    T af_complex_caster( Rcomplex from ){
        T af_complex;
        af_complex.x = from.r;
        af_complex.y = from.i;
        return af_complex;
    }

    //template <>
    //inline af::cdouble caster<Rcomplex, af::cdouble>( Rcomplex from ){
    //    return af_complex_caster<af::cdouble>( from ) ;
    //}

    //template<>
    //inline af::cfloat  caster<Rcomplex, af::cfloat>( Rcomplex from ){
    //    return af_complex_caster<af::cfloat>( from ) ;
    //}
}

namespace traits {

    template<af::dtype AF_DTYPE>
    class Exporter< ::RcppArrayFire::typed_array<AF_DTYPE> >{
    private:
        SEXP object ;

    public:
        Exporter( SEXP x ) : object(x){}
        ~Exporter(){}

        ::RcppArrayFire::typed_array<AF_DTYPE> get() {
            typedef typename ::RcppArrayFire::dtype2cpp<AF_DTYPE>::type cpp_type ;
            //std::vector<cpp_type> buff( Rf_length( object ) );

            // copying to buff is not efficient
            //::Rcpp::internal::export_indexing<
            //    std::vector<cpp_type>,
            //    cpp_type
            //    >( object, buff ) ;
            ::RcppArrayFire::SEXP2CxxPtr<cpp_type> buff( object ) ;

            Shield<SEXP> dims( ::Rf_getAttrib( object, R_DimSymbol ) ) ;
            af::array result;
            if( Rf_isNull(dims) ){
                result = af::array( buff.size(), buff.data() ) ;
            }
            else{
                result = af::array(::Rcpp::as<af::dim4>(dims), buff.data());
            }

            return ::RcppArrayFire::typed_array<AF_DTYPE>( result );
        }
    };


    // Exporter for CSR matrix (dgRMatrix)
    template<af::dtype AF_DTYPE>
    class Exporter< ::RcppArrayFire::typed_sparray<AF_DTYPE, AF_STORAGE_CSR> >{
    private:
        S4 d_x;
        IntegerVector d_dims, d_j, d_p;

    public:
        Exporter(SEXP x) : d_x(x), d_dims(d_x.slot("Dim")), d_j(d_x.slot("j")), d_p(d_x.slot("p")) {
            if (!d_x.is("dgRMatrix") && !d_x.is("lgRMatrix"))
                throw std::invalid_argument("Need S4 class dgRMatrix/lgRMatrix for a teyped_sparray<af::dtype, AF_STORAGE_CSR>");
        }
        ~Exporter(){}

        ::RcppArrayFire::typed_sparray<AF_DTYPE, AF_STORAGE_CSR> get() {
            typedef typename ::RcppArrayFire::dtype2cpp<AF_DTYPE>::type cpp_type ;
            ::RcppArrayFire::SEXP2CxxPtr<cpp_type> buff(
                static_cast<SEXP>(d_x.slot("x")) ) ;

            af::array result;
            result = af::sparse(
                    d_dims[0], d_dims[1], buff.size(),
                    buff.data(), d_p.begin(), d_j.begin(),
                    AF_DTYPE, AF_STORAGE_CSR);

            return ::RcppArrayFire::typed_sparray<AF_DTYPE, AF_STORAGE_CSR>( result );
        }
    };

    // Exporter for CSC matrix (dgCMatrix)
    // NOTE: af::sparseConvertTo does not support CSC
    template<af::dtype AF_DTYPE>
    class Exporter< ::RcppArrayFire::typed_sparray<AF_DTYPE, AF_STORAGE_CSC> >{
    private:
        typedef typename ::RcppArrayFire::dtype2cpp<AF_DTYPE>::type cpp_type ;
        S4 d_x;
        IntegerVector d_dims, d_i, d_p;

    public:
        Exporter(SEXP x) : d_x(x), d_dims(d_x.slot("Dim")), d_i(d_x.slot("i")), d_p(d_x.slot("p")) {
            if (!d_x.is("dgCMatrix") && !d_x.is("lgCMatrix"))
                throw std::invalid_argument("Need S4 class dgCMatrix/lgCMatrix for a teyped_sparray<af::dtype, AF_STORAGE_CSC>");
        }
        ~Exporter(){}

        ::RcppArrayFire::typed_sparray<AF_DTYPE, AF_STORAGE_CSC> get() {
            typedef typename ::RcppArrayFire::dtype2cpp<AF_DTYPE>::type cpp_type ;
            ::RcppArrayFire::SEXP2CxxPtr<cpp_type> buff(
                static_cast<SEXP>(d_x.slot("x")) ) ;

            af::array result;
            result = af::sparse(
                    d_dims[0], d_dims[1], buff.size(),
                    buff.data(), d_i.begin(), d_p.begin(),
                    AF_DTYPE, AF_STORAGE_CSC);

            return ::RcppArrayFire::typed_sparray<AF_DTYPE, AF_STORAGE_CSC>( result );
        }
    };
}
}

#endif
