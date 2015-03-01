inlineCxxPlugin <- function(...){
	plugin <- Rcpp::Rcpp.plugin.maker(
		include.before = "#include <RcppFire.h>",
		libs = sprintf("%s $(LAPACK_LIBS) $(BLAS_LIBS) $(FLIBS)", RcppFireLdFlags()),
		LinkingTo = c("Rcpp"),
		package = "RcppFire"
	)
	settings <- plugin()
	settings
}
