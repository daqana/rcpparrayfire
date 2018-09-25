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

//' Set the seed for random number generation in ArrayFire.
//' @details Sets the seed for the current default random engine in ArrayFire. Note that a (64bit) double is used as input, since R does not support 64bit integers.
//' @param seed a (64bit) double whose bit representation is reinterpreted as a 64bit integer
//' @export
//' @references \url{http://arrayfire.org/docs/group__random__func__set__seed.htm}
// [[Rcpp::export]]
void arrayfire_set_seed( const double seed ) {
    uint64_t _seed;
    static_assert(sizeof seed == sizeof _seed, "Size does not match!");
    std::memcpy(&_seed, &seed, sizeof seed);
	af::setSeed( _seed ) ;
}

//' Get the seed for random number generation in ArrayFire.
//' @details Gets the seed for the current default random engine in ArrayFire. Note that a (64bit) double is used as output, since R does not support 64bit integers.
//' @return a (64bit) double whose bit representation is reinterpreted from the 64bit integer seed
//' @export
//' @references \url{http://arrayfire.org/docs/group__random__func__get__seed.htm}
// [[Rcpp::export]]
double arrayfire_get_seed() {
    uint64_t seed = af::getSeed();
    double result;
    static_assert(sizeof seed == sizeof result, "Size does not match!");
    std::memcpy(&result, &seed, sizeof seed);
    return result;
}

//' Get string description for the active backend
//' @details Get string description for the active backend.
//' @return string description for the active backend
//' @export
//' @references \url{http://arrayfire.org/docs/group__unified__func__getactivebackend.htm#gac6a8e976a151d007e0cf5cf4f11da2a9}
// [[Rcpp::export]]
std::string arrayfire_get_active_backend() {
    switch(af::getActiveBackend()) {
    case AF_BACKEND_CPU:
        return "CPU";
    case AF_BACKEND_CUDA:
        return "CUDA";
    case AF_BACKEND_DEFAULT:
        return "DEFAULT";
    case AF_BACKEND_OPENCL:
        return "OpenCL";
    default:
        Rcpp::stop("Unknown active backend!");
    }
}

//' Get a vector of string descriptions for the available backends
//' @details Get a vector of string descriptions for the available backends.
//' @return vector of string descriptions for the available backends
//' @export
//' @references \url{http://arrayfire.org/docs/group__unified__func__getavailbackends.htm#ga32fc807a8d4680987a915362573c1a2c}
// [[Rcpp::export]]
Rcpp::CharacterVector arrayfire_get_available_backends() {
    int backends = af::getAvailableBackends();
    Rcpp::CharacterVector result;
    if(backends & AF_BACKEND_CPU)
        result.push_back("CPU");
    if(backends & AF_BACKEND_CUDA)
        result.push_back("CUDA");
    if(backends & AF_BACKEND_OPENCL)
        result.push_back("OpenCL");
    return result;
}

//' Set the current backend
//' @details Set the current backend.
//' @param backend string description of backend (DEFAULT, CPU, OPENCL, CUDA)
//' @export
//' @references \url{http://arrayfire.org/docs/group__unified__func__setbackend.htm#ga7e0fad1f134b0421811ee3a4ce47e987}
// [[Rcpp::export]]
void arrayfire_set_backend(std::string backend = "DEFAULT") {
    for (auto & c: backend)
        c = std::toupper(c);
    if (backend == "CPU")
        return af::setBackend(AF_BACKEND_CPU);
    if (backend == "CUDA")
        return af::setBackend(AF_BACKEND_CUDA);
    if (backend == "DEFAULT")
        return af::setBackend(AF_BACKEND_DEFAULT);
    if (backend == "OPENCL")
        return af::setBackend(AF_BACKEND_OPENCL);
}
