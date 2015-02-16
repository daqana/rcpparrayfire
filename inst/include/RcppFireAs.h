#ifndef RcppFire__RcppFireAs__h
#define RcppFire__RcppFireAs__h

#include <type_traits>

namespace RcppFire{
	template<af::dtype AF_DTYPE> struct af_dtype2cpp{};
	template<> struct af_dtype2cpp<af::f32>{ typedef float type ; };
	template<> struct af_dtype2cpp<af::c32>{ typedef af::cfloat type ; };
	template<> struct af_dtype2cpp<af::f64>{ typedef double type ; };
	template<> struct af_dtype2cpp<af::c64>{ typedef af::cdouble type ; };
	template<> struct af_dtype2cpp<af::b8>{ typedef bool type ; };
	template<> struct af_dtype2cpp<af::s32>{ typedef int type ; };
	template<> struct af_dtype2cpp<af::u32>{ typedef unsigned int type ; };


	template<af::dtype AF_DTYPE> 
	class array_decorator{ //FIXME : wired to call this decorator?
	public:
		array_decorator(){}
		array_decorator(af::array &src_data) : data(src_data) ;
		operator af::array(){
			return data;
		}

		begin();
		end();

	private:
		af::array data;
	};
}

namespace Rcpp{
namespace traits {
	template<typename T> 
	typename T af_complex_caster( Rcomplex from ){
		T af_complex;
		af_complex.x = from.r;
		af_complex.y = from.i;
		return af_complex;
	}

	template <>
	inline af::cdouble caster<Rcomplex, af::cdouble>( Rcomplex from ){
		return af_complex_caster<af::cdouble>( from ) ;
	}

	template<>
	inline af::cfloat  caster<Rcomplex, af::cfloat>( Rcomplex from ){
		return af_complex_caster<af::cfloat>( from ) ;
	}


	template<af::dtype AF_DTYPE> 
	class Exporter<RcppFire::array_decorator<AF_DTYPE>>{
	private:
		SEXP object ;

	public:
		Exporter( SEXP x ) : object(x){}
		~Exporter(){}

		RcppFire::array_decorator<AF_DTYPE> get() {
			Shield<SEXP> dims( ::Rf_getAttrib( object, R_DimSymbol ) ) ;
			af::array result;
			if( Rf_isNull(dims) ){
				result = af::array( ::Rf_length(object), AF_DTYPE ) ; 
			}
			else{
				af::dim4 dims_( ::Rf_length(dims), INTEGER(dims) ) ; //FIXME : the second argument should be unsigned int*
				result = af::array( dims_, AF_DTYPE ) ; 
			}
			::Rcpp::internal::export_indexing<
				std::add_pointer<RcppFire::af_dtype2cpp<AF_DTYPE>::type>::type,
				af_dtype2cpp<AF_DTYPE>::type
				>( object, result.device<RcppFire::af_dtype2cpp<AF_DTYPE>::type>() ) ;
			result.unlock() ;

			return RcppFire::array_decorator<AF_DTYPE>(result);
		}
    }; 
}

#endif

