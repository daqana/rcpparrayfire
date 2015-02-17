#include <RcppFire.h>


//' Report the information about current device and platform
//' 
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
//' 
//' @details 
//' @return  
//' @note 
//' @seealso   
// [[Rcpp::export]]
void arrayfire_set_device( const int index ) {
	af::deviceset( index );
}

//' Return the index of current device 
//' 
//' @details 
//' @return  
//' @note 
//' @seealso   
// [[Rcpp::export]]
int arrayfire_get_device() {
	return af::deviceget() ;
}

//' Return the number of available device 
//' 
//' @details 
//' @return  
//' @note 
//' @seealso   
// [[Rcpp::export]]
int arrayfire_count_device() {
	return af::devicecount() ;
}

// [[Rcpp::export]]
void arrayfire_set_setseed_random( const unsigned int seed ) {
	af::af_rand_setseed( seed ) ;
}
