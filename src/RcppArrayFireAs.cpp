#include <RcppArrayFire.h>
namespace Rcpp{
template <> af::dim4 as (SEXP dims) {
    IntegerVector tmp = as<IntegerVector>(dims);
    switch(tmp.size()) {
    case 4:
        return af::dim4(tmp[0], tmp[1], tmp[2], tmp[3]);
    case 3:
        return af::dim4(tmp[0], tmp[1], tmp[2]);
    case 2:
        return af::dim4(tmp[0], tmp[1]);
    case 1:
        return af::dim4(tmp[0]);
    default:
        stop("Inadmissible dimension");
    }
}
}
