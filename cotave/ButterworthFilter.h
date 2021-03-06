/**
 * $Id$
 * Copyright (c) 2017 Cota Nabeshima <cota@upard.org>
 * This file is subject to the MIT license available at,
 * http://opensource.org/licenses/mit-license.php
 */

#ifndef _COTAVE_BUTTERWORTHFILTER_H_
#define _COTAVE_BUTTERWORTHFILTER_H_

namespace cotave {

class ButterworthFilter {
 private:
  unsigned int order;
  double *x_coeff;
  double *y_coeff;
  double *x;
  double *y;

  ButterworthFilter(const ButterworthFilter &opp);
  ButterworthFilter &operator=(const ButterworthFilter &opp);

 public:
  ButterworthFilter(unsigned int order, double sampling_frequency,
                    double cutoff_frequency);
  ~ButterworthFilter();

  void initialize(double input);
  void update(double input);
  double getOutput() const;

  unsigned int getOrder() const;
  double getXCoeff(unsigned int i) const;
  double getYCoeff(unsigned int i) const;

  static void zeroPhaseFilter(double *outputs, const double *inputs,
                              unsigned int size, unsigned int order,
                              double sampling_frequency,
                              double cutoff_frequency);
};

}  // namespace cotave

#include "ButterworthFilter.ipp"

#endif /* _COTAVE_BUTTERWORTHFILTER_H_ */
