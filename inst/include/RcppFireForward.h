#ifndef RcppFire__RcppFireForward__h
#define RcppFire__RcppFireForward__h

#include <RcppCommon.h>
#include <Rconfig.h>
//#include <RcppFireConfig.h>

#include <arrayfire.h>

/* forward declarations */
namespace RcppFire{
	template<af::dtype AF_DTYPE> class typed_array;
}

namespace Rcpp {
    /* support for wrap */
    SEXP wrap ( const af::array& ) ;
    
    namespace traits {
	/* support for as */
	template<af::dtype AF_DTYPE> class Exporter<RcppFire::typed_array<AF_DTYPE>>;
    }  
}

#endif
