// -*- mode: C++ -*-
//
// RcppFireAs.h: Rcpp/ArrayFire glue, support for as
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

#ifndef RcppFire__RcppFireAs__h
#define RcppFire__RcppFireAs__h

#include <algorithm>
#include <iterator>
#include <type_traits>

namespace RcppFire{
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
	//	return af_complex_caster<af::cdouble>( from ) ;
	//}

	//template<>
	//inline af::cfloat  caster<Rcomplex, af::cfloat>( Rcomplex from ){
	//	return af_complex_caster<af::cfloat>( from ) ;
	//}
}

namespace traits {

	template<af::dtype AF_DTYPE> 
	class Exporter<::RcppFire::typed_array<AF_DTYPE>>{
	private:
		SEXP object ;

	public:
		Exporter( SEXP x ) : object(x){}
		~Exporter(){}

		::RcppFire::typed_array<AF_DTYPE> get() {
			typedef typename ::RcppFire::dtype2cpp<AF_DTYPE>::type cpp_type ;
			//std::vector<cpp_type> buff( Rf_length( object ) );

			// copying to buff is not efficient
			//::Rcpp::internal::export_indexing<
			//	std::vector<cpp_type>,
			//	cpp_type
			//	>( object, buff ) ;
			::RcppFire::SEXP2CxxPtr<cpp_type> buff( object ) ;

			Shield<SEXP> dims( ::Rf_getAttrib( object, R_DimSymbol ) ) ;
			af::array result;
			if( Rf_isNull(dims) ){
				result = af::array( buff.size(), buff.data() ) ; 
			}
			else{
				int* idims = INTEGER(dims) ;
				af::dim4 dims_( ::Rf_length(dims), idims ) ; 
				result = af::array( dims_, buff.data() ) ; 
			}

			return ::RcppFire::typed_array<AF_DTYPE>( result );
		}
    }; 

}
}

#endif

