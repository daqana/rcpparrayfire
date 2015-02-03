// -*- mode: C++; c-indent-level: 4; c-basic-offset: 4; indent-tabs-mode: nil; -*-
/* :tabSize=4:indentSize=4:noTabs=false:folding=explicit:collapseFolds=1: */
//
// RcppArmadilloWrap.h: Rcpp/Armadillo glue
//
// Copyright (C)  2010 - 2013  Dirk Eddelbuettel, Romain Francois and Douglas Bates
//
// This file is part of RcppArmadillo.
//
// RcppArmadillo is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// RcppArmadillo is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with RcppArmadillo.  If not, see <http://www.gnu.org/licenses/>.

#ifndef RcppFire__RcppFireWrap__h
#define RcppFire__RcppFireWrap__h

namespace Rcpp{

    namespace RcppFire{

	template <typename T>
	SEXP af_wrap( const T& object, const ::Rcpp::Dimension& dim){
	    //TODO : dlete this line. ::Rcpp::RObject x = ::Rcpp::wrap( object.memptr() , object.memptr() + object.n_elem ) ;
		//FIXME : Need to indicate type parameter for the following line
	    ::Rcpp::RObject x = ::Rcpp::wrap( object.device<>() , object.deviece<>() + object.elements() ) ; 
	    x.attr( "dim" ) = dim ;
	    return x; 
	}

	// DE 03-Aug-2013
	// here is an alternate form which would not set dimension which we could do
	// for row and column vectors -- but the current form of return row and col
        // as matrix types with one col (or row, respectively) is now entrenched
	template <typename T>
	SEXP arma_wrap(const T& object) {
	    //TODO : delete this line. return ::Rcpp::wrap(object.memptr() , object.memptr() + object.n_elem);
		//FIXME : Need to indicate type parameter for the following line
	    return ::Rcpp::wrap(object.device<>() , object.device<>() + object.elements());
	}

	//TODO : delete the following code block. we might not need this for af::array
	//template <typename T>
	//SEXP arma_subview_wrap( const arma::subview<T>& data, int nrows, int ncols ){
    //        const int RTYPE = Rcpp::traits::r_sexptype_traits<T>::rtype ;
    //        Rcpp::Matrix<RTYPE> mat( nrows, ncols ) ;
    //        for( int j=0, k=0; j<ncols; j++)
    //            for( int i=0; i<nrows; i++, k++) 
    //                mat[k] = data(i,j) ;
    //        return mat ;
	//}
	
    } /* namespace RcppArmadillo */
	
    /* wrap */

    template <typename T> SEXP wrap ( const af::array& data ){
		if(data.dims().numdims() == 3){
			return RcppFire::af_wrap( data, Dimension( data.dims(0), data.dims(1), data.dims(2) ) ) ;
		}
		else if(data.dims().numdims == 2){
			return RcppFire::af_wrap( data, Dimension( data.dims(0), data.dims(1) ) ) ;
		}
		else if(data.dims().numdims == 1){ //TODO : need to check documentation. how col(), row() works
			return RcppFire::af_wrap( data, Dimension( data.dims(0), data.dims(1) ) ) ;
		}
    }

    //TODO : issparse method to check if the array is sparse
	//template <typename T> SEXP wrap ( const arma::SpMat<T>& sm ){
    //    const int  RTYPE = Rcpp::traits::r_sexptype_traits<T>::rtype;
    //        
    //    IntegerVector dim = IntegerVector::create( sm.n_rows, sm.n_cols );
	//	
    //    // copy the data into R objects
    //    Vector<RTYPE> x(sm.values, sm.values + sm.n_nonzero ) ;
    //    IntegerVector i(sm.row_indices, sm.row_indices + sm.n_nonzero);
    //    IntegerVector p(sm.col_ptrs, sm.col_ptrs + sm.n_cols+1 ) ;

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

}

#endif

