% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/RcppArrayFire.package.skeleton.R
\name{RcppArrayFire.package.skeleton}
\alias{RcppArrayFire.package.skeleton}
\title{Create a skeleton for a new package that intends to use RcppArrayFire}
\usage{
RcppArrayFire.package.skeleton(
  name = "anRpackage",
  list = character(),
  environment = .GlobalEnv,
  path = ".",
  force = FALSE,
  code_files = character(),
  example_code = TRUE
)
}
\arguments{
\item{name}{See \code{\link{package.skeleton}}}

\item{list}{See \code{\link{package.skeleton}}}

\item{environment}{See \code{\link{package.skeleton}}}

\item{path}{See \code{\link{package.skeleton}}}

\item{force}{See \code{\link{package.skeleton}}}

\item{code_files}{See \code{\link{package.skeleton}}}

\item{example_code}{If \code{TRUE}, example C++ code using RcppArrayFire is added to the package}
}
\description{
\code{RcppArrayFire.package.skeleton} creates a skeleton for a new package that intends to use
RcppArrayFire. It is based on the \code{\link{package.skeleton}} function that it executes first.
}
\details{
In addition to \code{\link{package.skeleton}}, the \code{DESCRIPTION} and \code{NAMESPACE}
files are updated. In addition, minimal \code{configure} and \code{src/Makevars.in} files for finding
the necessary compiler flags are created.
}
