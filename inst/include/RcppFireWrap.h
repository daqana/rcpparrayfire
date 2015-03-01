#ifndef RcppFire__RcppFireWrap__h
#define RcppFire__RcppFireWrap__h

#include <Rcpp.h>
#include <arrayfire.h>

namespace RcppFire{
	template<typename T> SEXP wrap_array( const af::array& object ){
		T* host_ptr = object.host<T>() ;
		::Rcpp::RObject x  = ::Rcpp::wrap( host_ptr, host_ptr + object.elements() ) ;
		delete[] host_ptr;
		
		return x ;
	}

	SEXP af_wrap( const af::array& object ) ;
} /* namespace RcppFire */

namespace Rcpp{
    /* wrap */
    SEXP wrap ( const af::array& data ) ; 
}

#endif

