// -*- mode: C++ -*-
//
// RcppFire.cpp: Rcpp/ArrayFire glue
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

#include <RcppFire.h>


//' Report the information about current device and platform
//' @details Return a list contains the informations about current device and platform.
//' The list object include device name, palatform information, toolkit information, 
//' and compute capability.
//' @return List contains the information about device and platform.
//' @export
//' @references \url{http://www.arrayfire.com/docs/group__device__mat.htm#gafae79277ec9ce681976c48392985baf0}  
// [[Rcpp::export]]
Rcpp::List arrayfire_device_prop() {
	char name[64],
		 platform[64],
		 toolkit[64],
		 compute[64];

	af::deviceprop( name, platform, toolkit, compute ) ;

	return Rcpp::List::create(
			Rcpp::Named("name") = std::string(name),
			Rcpp::Named("platform") = std::string(platform),
			Rcpp::Named("toolkit") = std::string(toolkit),
			Rcpp::Named("compute") = std::string(compute) ) ;
}

//' Switch to specified device 
//' @param index the index of a device switched to.
//' @details Available indices
//' can be obtained by calling \code{\link{arrayfire_count_device}}.
//' @export 
//' @references \url{http://www.arrayfire.com/docs/group__device__mat.htm#ga6473f398cab654fc0bef97833a5bea5f}  
// [[Rcpp::export]]
void arrayfire_set_device( const int index ) {
	try{
		af::deviceset( index - 1 );
	}
	catch( af::exception &ex ){
		Rcpp::Rcerr << "arrayfire exception" << std::endl;
		Rcpp::Rcerr << ex << std::endl;
	}
	catch( std::exception &ex ){
		forward_exception_to_r( ex ) ;
	}
	catch( ... ){
		::Rf_error("c++ exception (unknown reason)");
	}
}

//' Return the index of current device 
//' @details Get the index of current device which is lower or
//' equal to a value returned by \code{\link{arrayfire_count_device}}.
//' @return the index of current device.
//' @export 
//' @references \url{http://www.arrayfire.com/docs/group__device__mat.htm#ga6d1964af8b32ca9c2f9525bf5ef8112a}
// [[Rcpp::export]]
int arrayfire_get_device() {
	// increment by 1 since the index of device start from 0
	return af::deviceget() + 1 ;
}

//' Return the number of available devices
//' @details Return the number of available devices.
//' @return the number of available devices. 
//' @export 
//' @references \url{http://www.arrayfire.com/docs/group__device__mat.htm#ga6d1964af8b32ca9c2f9525bf5ef8112a}
// [[Rcpp::export]]
int arrayfire_count_device() {
	return af::devicecount() ;
}

// af_rand_setseed is unavailable in the current version of arrayfire
//void arrayfire_set_setseed_random( const unsigned int seed ) {
//	af_rand_setseed( seed ) ;
//}
