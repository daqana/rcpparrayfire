#include <RcppFire.h>


//' Report the information about current device and platform
//' @export
//' @details 
//' @return  
//' @note 
//' @seealso   
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
//' @export 
//' @details 
//' @return  
//' @note 
//' @seealso   
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
//' @export 
//' @details 
//' @return  
//' @note 
//' @seealso   
// [[Rcpp::export]]
int arrayfire_get_device() {
	// increment by 1 since the index of device start from 0
	return af::deviceget() + 1 ;
}

//' Return the number of available device 
//' @export 
//' @details 
//' @return  
//' @note 
//' @seealso   
// [[Rcpp::export]]
int arrayfire_count_device() {
	return af::devicecount() ;
}

// af_rand_setseed is unavailable in the current version of arrayfire
//void arrayfire_set_setseed_random( const unsigned int seed ) {
//	af_rand_setseed( seed ) ;
//}
