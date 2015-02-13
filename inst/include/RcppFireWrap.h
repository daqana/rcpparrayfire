#ifndef RcppFire__RcppFireWrap__h
#define RcppFire__RcppFireWrap__h

namespace Rcpp{

    namespace RcppFire{
	SEXP af_wrap( const af::array& object, const ::Rcpp::Dimension& dim){
		::Rcpp::RObject x;

		switch(object.type()){
			case af::f64:
				x = ::Rcpp::wrap( object.device<double>() , object.device<double>() + object.elements() ) ;
				break;
			case af::c64:
				x = ::Rcpp::wrap( 
						reinterpret_cast<std::complex<double>>(object.device<af::cdouble>()),
						reinterpret_cast<std::complex<double>>(object.device<af::cdouble>()) + object.elements() ) ;
				break;
			case af::f32:
				x = ::Rcpp::wrap( object.device<float>() , object.device<float>() + object.elements() ) ;
				break;
			case af::c32:
				x = ::Rcpp::wrap( 
						reinterpret_cast<std::complex<float>>(object.device<af::cfloat>()),
						reinterpret_cast<std::complex<float>>(object.device<af::cfloat>()) + object.elements() ) ;
				break;
			case af::s32:
				x = ::Rcpp::wrap( object.device<int>() , object.device<int>() + object.elements() ) ;
				break;
			case af::f32:
				x = ::Rcpp::wrap( object.device<unsigned int>() , object.device<unsigned int>() + object.elements() ) ;
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
		object.unlock(); //TODO : check wrap() implementation and see if the datas are hard copied
	    return x; 
	}
    } /* namespace RcppFire */
	
    /* wrap */

    SEXP wrap ( const af::array& data ){
		::Rcpp::RObject x;

		switch(data.dims().numdims())
		{
			case 3:
				x = RcppFire::af_wrap( data ) ;
				x.attr( "dim" ) = Dimension( data.dims(0), data.dims(1), data.dims(2) );
				break;
			case 2:
				x = RcppFire::af_wrap( data ) ;
				x.attr( "dim" ) = Dimension( data.dims(0), data.dims(1) );
				break;
			case 1:
				x = RcppFire::af_wrap( data ) ;
				x.attr( "dim" ) = Dimension( data.dims(0) );
				break;
		}

		return x;

    }
}

#endif

