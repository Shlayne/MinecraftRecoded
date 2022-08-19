/*################################################################################
  ##
  ##   Copyright (C) 2016-2022 Keith O'Hara
  ##
  ##   This file is part of the GCE-Math C++ library.
  ##
  ##   Licensed under the Apache License, Version 2.0 (the "License");
  ##   you may not use this file except in compliance with the License.
  ##   You may obtain a copy of the License at
  ##
  ##       http://www.apache.org/licenses/LICENSE-2.0
  ##
  ##   Unless required by applicable law or agreed to in writing, software
  ##   distributed under the License is distributed on an "AS IS" BASIS,
  ##   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  ##   See the License for the specific language governing permissions and
  ##   limitations under the License.
  ##
  ################################################################################*/

#ifndef _gcem_HPP
#define _gcem_HPP

// NOTICE: I have changed all instances of "gcem_incl" to "gcem" because I prefer it.

#include "gcem/gcem_options.hpp"

namespace gcem
{
    #include "gcem/quadrature/gauss_legendre_50.hpp"

    #include "gcem/is_inf.hpp"
    #include "gcem/is_nan.hpp"
    #include "gcem/is_finite.hpp"
    
    #include "gcem/signbit.hpp"
    #include "gcem/copysign.hpp"
    #include "gcem/neg_zero.hpp"
    #include "gcem/sgn.hpp"

    #include "gcem/abs.hpp"
    #include "gcem/ceil.hpp"
    #include "gcem/floor.hpp"
    #include "gcem/trunc.hpp"
    #include "gcem/is_odd.hpp"
    #include "gcem/is_even.hpp"
    #include "gcem/max.hpp"
    #include "gcem/min.hpp"
    #include "gcem/sqrt.hpp"
    #include "gcem/inv_sqrt.hpp"

    #include "gcem/find_exponent.hpp"
    #include "gcem/find_fraction.hpp"
    #include "gcem/find_whole.hpp"
    #include "gcem/mantissa.hpp"
    #include "gcem/round.hpp"
    #include "gcem/fmod.hpp"

    #include "gcem/pow_integral.hpp"
    #include "gcem/exp.hpp"
    #include "gcem/expm1.hpp"
    #include "gcem/log.hpp"
    #include "gcem/log1p.hpp"
    #include "gcem/log2.hpp"
    #include "gcem/log10.hpp"
    #include "gcem/pow.hpp"

    #include "gcem/gcd.hpp"
    #include "gcem/lcm.hpp"

    #include "gcem/tan.hpp"
    #include "gcem/cos.hpp"
    #include "gcem/sin.hpp"

    #include "gcem/atan.hpp"
    #include "gcem/atan2.hpp"
    #include "gcem/acos.hpp"
    #include "gcem/asin.hpp"

    #include "gcem/tanh.hpp"
    #include "gcem/cosh.hpp"
    #include "gcem/sinh.hpp"

    #include "gcem/atanh.hpp"
    #include "gcem/acosh.hpp"
    #include "gcem/asinh.hpp"

    #include "gcem/binomial_coef.hpp"
    #include "gcem/lgamma.hpp"
    #include "gcem/tgamma.hpp"
    #include "gcem/factorial.hpp"
    #include "gcem/lbeta.hpp"
    #include "gcem/beta.hpp"
    #include "gcem/lmgamma.hpp"
    #include "gcem/log_binomial_coef.hpp"

    #include "gcem/erf.hpp"
    #include "gcem/erf_inv.hpp"
    #include "gcem/incomplete_beta.hpp"
    #include "gcem/incomplete_beta_inv.hpp"
    #include "gcem/incomplete_gamma.hpp"
    #include "gcem/incomplete_gamma_inv.hpp"
}

#endif
