// -*- mode: C++ -*-
//
// RcppArrayFire.cpp: Rcpp/ArrayFire glue
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

#include <RcppArrayFire.h>


//' Report the information about current device and platform
//' @details Return a list containing the information about current device and platform.
//' The list object includes device name, palatform information, toolkit information,
//' and compute capability.
//' @return List containing the information about device and platform.
//' @export
//' @references \url{http://arrayfire.org/docs/group__device__func__prop.htm#gaa9eab56ddac21650581682912ea78293}
// [[Rcpp::export]]
Rcpp::List arrayfire_device_info() {
	char name[64],
		 platform[64],
		 toolkit[64],
		 compute[64];

	af::deviceInfo( name, platform, toolkit, compute ) ;

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
//' @references \url{http://arrayfire.org/docs/group__device__func__set.htm#gafbb906ca5b89ec43fdb0e3a14d1df1e7}
// [[Rcpp::export]]
void arrayfire_set_device( const int index ) {
	try{
		af::setDevice( index - 1 );
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
//' @references \url{http://arrayfire.org/docs/group__device__func__get.htm#ga4dfe3f90475b735384f8b28cf2b19a11}
// [[Rcpp::export]]
int arrayfire_get_device() {
	// increment by 1 since the index of device start from 0
	return af::getDevice() + 1 ;
}

//' Return the number of available devices
//' @details Return the number of available devices.
//' @return the number of available devices.
//' @export
//' @references \url{http://arrayfire.org/docs/group__device__func__count.htm#gac3c8750da69ee883fd14c0a8290e45f1}
// [[Rcpp::export]]
int arrayfire_count_device() {
	return af::getDeviceCount() ;
}

//' Display ArrayFire and device info
//' @param verbose  Flag to return verbose info
//' @details Display ArrayFire and device info.
//' @export
//' @references \url{http://arrayfire.org/docs/group__device__func__info.htm#ga1360e706b046b1c5b299bd6e689a0276} and \url{http://arrayfire.org/docs/group__device__func__info__string.htm#ga73ee21947f018445ea720036c1edfb69}
// [[Rcpp::export]]
void arrayfire_info(const bool verbose = false) {
    Rcpp::Rcout << af::infoString(verbose) << std::endl;
}

// af_rand_setseed is unavailable in the current version of arrayfire
//void arrayfire_set_setseed_random( const unsigned int seed ) {
//	af_rand_setseed( seed ) ;
//}
