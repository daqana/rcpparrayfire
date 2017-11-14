# RcppArrayFire

R and ArrayFire via Rcpp

## Prerequisites

- R
- Rcpp
- ArrayFire
- g++ (>= 4.8)

## Installation
```R
install.packages('devtools')
library(devtools)
install_github(repo = 'RInstitute/RcppArrayFire')
```
If you want to try RcppArrayFire with keeping your
local enviornment clean, then
```R
dev_mode(on = T)
install_github(repo = 'RInstitute/RcppArrayFire')
# do something with RcppArrayFire
dev_mode(on = F)
```
RcppArrayFire uses the unified backend of ArrayFire. If you have
installed ArrayFire in a non-standard directory, you can use the
`--with-arrayfire` option:
```R
install_github(repo = 'RInstitute/RcppArrayFire',
               args = c("--configure-args='--with-arrayfire=/opt/arrayfire-3'"))
```

## Trademark notice

RcppArrayFire is not affiliated with or endorsed by ArrayFire. The
ArrayFire literal mark is used under a limited license granted by
ArrayFire the trademark holder in the United States and other countries.

## Status

Under development

## Authors

Kazuki Fukui

Ralf Stubner

## License

GPL (>= 2)
