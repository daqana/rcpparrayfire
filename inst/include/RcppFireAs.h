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
		typed_array(const af::array &src_data) : af::array(src_data) {};
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
			std::vector<cpp_type> buff( Rf_length( object ) );

			::Rcpp::internal::export_indexing<
				std::vector<cpp_type>,
				cpp_type
				>( object, buff ) ;

			Shield<SEXP> dims( ::Rf_getAttrib( object, R_DimSymbol ) ) ;
			af::array result;
			if( Rf_isNull(dims) ){
				result = af::array( ::Rf_length(object), buff.data() ) ; 
			}
			else{
				int* idims = INTEGER(dims) ;
				unsigned int udims[4] ;
				std::copy( idims, idims + ::Rf_length(dims), std::begin(udims) ) ;
				af::dim4 dims_( ::Rf_length(dims), udims ) ; 
				result = af::array( dims_, buff.data() ) ; 
			}

			return ::RcppFire::typed_array<AF_DTYPE>( result );
		}
    }; 

}
}

#endif

