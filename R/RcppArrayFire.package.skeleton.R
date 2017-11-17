## Copyright (C) 2015 Kazuki Fukui
##
## This file is part of RcppArrayFire.
##
## RcppArrayFire is free software: you can redistribute it and/or modify it
## under the terms of the GNU General Public License as published by
## the Free Software Foundation, either version 2 of the License, or
## (at your option) any later version.
##
## RcppArrayFire is distributed in the hope that it will be useful, but
## WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with RcppArrayFire.  If not, see <http://www.gnu.org/licenses/>.

##' Create a skeleton for a new package that intends to use RcppArrayFire
##'
##' \code{RcppArrayFire.package.skeleton} creates a skeleton for a new package that intends to use
##' RcppArrayFire. It is based on the \code{\link{package.skeleton}} function that it executes first.
##' @details In addition to \code{\link{package.skeleton}}, the \code{DESCRIPTION} and \code{NAMESPACE}
##' files are updated. In addition, minimal \code{configure} and \code{src/Makevars.in} files for finding
##' the necessary compiler flags are created.
##' @param name         See \code{\link{package.skeleton}}
##' @param list         See \code{\link{package.skeleton}}
##' @param environment  See \code{\link{package.skeleton}}
##' @param path         See \code{\link{package.skeleton}}
##' @param force        See \code{\link{package.skeleton}}
##' @param code_files   See \code{\link{package.skeleton}}
##' @param example_code If \code{TRUE}, example C++ code using RcppArrayFire is added to the package
##' @export
##' @importFrom utils packageDescription
RcppArrayFire.package.skeleton <- function(name="anRpackage",
                                           list=character(),
                                           environment=.GlobalEnv,
                                           path=".",
                                           force=FALSE,
                                           code_files=character(),
                                           example_code=TRUE) {

    env <- parent.frame(1)

    if (! length(list)) {
        fake <- TRUE
        assign("Rcpp.fake.fun", function(){}, envir = env)
    } else {
        fake <- FALSE
    }

    haveKitten <- requireNamespace("pkgKitten", quietly=TRUE, character.only=TRUE)
    skelFunUsed <- ifelse(haveKitten, "kitten", "package.skeleton")
    message("\nCalling ", skelFunUsed, " to create basic package.")

    ## first let the traditional version (or the kitten alternate) do its business
    call <- match.call()
    call[[1]] <- if (haveKitten) as.name("kitten") else as.name("package.skeleton")
    if (! haveKitten) {                 # in the package.skeleton() case
        if ("example_code" %in% names(call)){
            call[["example_code"]] <- NULL    # remove the example_code argument
        }
        if (fake) {
            call[["list"]] <- "Rcpp.fake.fun"
        }
    }

    tryCatch(eval(call, envir=env),
             error = function(e) {
                 stop(paste("error while calling `", skelFunUsed, "`", sep=""))
             })

    message("\nAdding RcppArrayFire settings")

    ## now pick things up
    root <- file.path(path, name)

    ## Add Rcpp to the DESCRIPTION
    DESCRIPTION <- file.path(root, "DESCRIPTION")
    if (file.exists(DESCRIPTION)) {
        x <- cbind(read.dcf(DESCRIPTION),
                   "Imports" = sprintf("Rcpp (>= %s)", packageDescription("Rcpp")[["Version"]]),
                   "LinkingTo" = "Rcpp, RcppArrayFire",
                   "SystemRequirements" = "C++11")
        write.dcf(x, file=DESCRIPTION)
        message(" >> added Imports: Rcpp")
        message(" >> added LinkingTo: Rcpp, RcppArrayFire")
        message(" >> added SystemRequirements: C++11")
    }

    ## add a useDynLib to NAMESPACE,
    NAMESPACE <- file.path( root, "NAMESPACE")
    lines <- readLines( NAMESPACE )
    if (! grepl("useDynLib", lines)) {
        lines <- c(sprintf("useDynLib(%s)", name),
                   "importFrom(Rcpp, evalCpp)",        ## ensures Rcpp instantiation
                   lines)
        writeLines(lines, con = NAMESPACE)
        message( " >> added useDynLib and importFrom directives to NAMESPACE")
    }

    ## lay things out in the src directory
    src <- file.path(root, "src")
    if (!file.exists(src)) {
        dir.create(src)
    }
    man <- file.path(root, "man")
    if (!file.exists(man)) {
        dir.create(man)
    }
    skeleton <- system.file("skeleton", package="RcppArrayFire")
    Makevars.in <- file.path(src, "Makevars.in")
    if (!file.exists(Makevars.in)) {
        file.copy(file.path(skeleton, "Makevars.in"), Makevars.in)
        message(" >> added Makevars.in file with Rcpp settings")
    }

    configure <- file.path(root, "configure")
    if (! file.exists(configure)) {
        file.copy(file.path(skeleton, "configure"), configure)
        message(" >> added configure file with RcppArrayFire settings")
    }

    if (example_code) {
        file.copy(file.path(skeleton, "rcpparrayfire_hello_world.cpp"), src)
        message(" >> added example src file using arrayfire classes")
        file.copy(file.path(skeleton, "rcpparrayfire_hello_world.Rd"), man)
        message(" >> added example Rd file for using arrayfire classes")

    Rcpp::compileAttributes(root)
        message(" >> invoked Rcpp::compileAttributes to create wrappers")
    }

    if (fake) {
        rm("Rcpp.fake.fun", envir=env)
        unlink(file.path(root, "R"  , "Rcpp.fake.fun.R"))
        unlink(file.path(root, "man", "Rcpp.fake.fun.Rd"))
    }

    invisible(NULL)
}
