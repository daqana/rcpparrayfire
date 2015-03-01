#include <RcppFireWrap.h>

namespace RcppFire{
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
		}
		//NOTE:there is no af::sparse() in the current open source version of arrayfire
		//if(object.issparse() == true){
		//	const int  RTYPE = Rcpp::traits::r_sexptype_traits<T>::rtype;

		//	IntegerVector dim = IntegerVector::create( object.dims(0), object.dims(1) );

		//	// copy the data into R objects
		//	Vector<RTYPE> x(object.device<T>(), object.device<T>() + object.nonzeros() ) ;
		//	IntegerVector i(/*begin of the row indices of object*/, /*end*/);
		//	IntegerVector p(/*begin of the col indices of object*/, /*end*/);

		//	std::string klass ;
		//	switch( RTYPE ){
		//		case REALSXP: klass = "dgCMatrix" ; break ;
		//		// case INTSXP : klass = "igCMatrix" ; break ; class not exported
		//		case LGLSXP : klass = "lgCMatrix" ; break ;
		//		default:
		//			throw std::invalid_argument( "RTYPE not matched in conversion to sparse matrix" ) ;
		//	}
		//	S4 s(klass);
		//	s.slot("i")   = i;
		//	s.slot("p")   = p;
		//	s.slot("x")   = x;
		//	s.slot("Dim") = dim;
		//	return s;
		//}
		return x; 
	}
} /* namespace RcppFire */

namespace Rcpp{
    /* wrap */

    SEXP wrap ( const af::array& data ){
		::Rcpp::RObject x = ::RcppFire::af_wrap( data ) ;
		switch(data.numdims())
		{
		case 3:
			x.attr( "dim" ) = Dimension( data.dims(0), data.dims(1), data.dims(2) );
			break;
		case 2:
			x.attr( "dim" ) = Dimension( data.dims(0), data.dims(1) );
			break;
		case 1:
			//x.attr( "dim" ) = Dimension( data.dims(0) );
			break;
		}

		return x;
    }
}

