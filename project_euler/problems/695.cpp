#include "common/calculus/ext_polynomial/division.h"
#include "common/calculus/ext_polynomial/factorized.h"
#include "common/calculus/ext_polynomial/io.h"
#include "common/calculus/ext_polynomial/multiplication.h"
#include "common/calculus/ext_polynomial/mv_function.h"
#include "common/calculus/ext_polynomial/mv_integration_ext.h"
#include "common/calculus/ext_polynomial/mv_make.h"
#include "common/calculus/ext_polynomial/mv_substitution_function.h"
#include "common/stl/base.h"
#include <cmath>

using namespace calculus::ext_polynomial;

using DF4 = DMVFunction<4>;

int main_695() {
  double phi = (sqrt(5.) - 1.) / 2;
  auto zero = DF4(), one = DF4(1.), x0 = DMakeXi<4>(0), y0 = DMakeXi<4>(1),
       x1 = DMakeXi<4>(2), y1 = DMakeXi<4>(3);
  auto fc = one;
  // auto fc = 24. * one;
  // auto fc = x0 * y0;
  // auto fc = 24. * x0 * y0;
  // auto fc = 8. * x0 * y0 * (1. - x0) * (1. - y0);

  // 0 <= x0 <= 1, 0 <= y0 <= 1
  // Region 1: 0 <= x1 <= x0, y0 <= y1 <= 1
  auto f1_4 = fc * (one - x0) * (one - y1);
  //   xc_1 = (1 - phi) * x0, yc_1 = (2 + phi) * y0
  //   Region 1.1:
  //   0 <= x1 <= xc_1
  //   x1 * y1 <= x0 * y0
  //   (x1 - x0) * (y1 - y0) <= -x0 * y0
  //     2 * y0 <= y1 <= 1
  //     Region 1.1.1: y1 <= yc_1
  //       (x1 - x0) * (y1 - y0) <= -x0 * y0
  //       Substitute1: y1 = y0 + y1s
  //         y1s = y1 - y0
  //         y0 <= y1s <= 1 - y0
  //         (x1 - x0) * y1s <= -x0 * y0
  auto f111_4 = SubstitutionFunction(f1_4, 3, y0 + y1);
  cout << "\tf111_4 = " << f111_4 << endl;
  auto f111_3 = IntegrationAB(f111_4, 2, 0., x0 - x0 * y0 / y1);
  cout << "\tf111_3 = " << f111_3 << endl;
  //       Region 1.1.1.1: 1 <= yc_1
  //         1 <= (2 + phi) * y0
  //         1 - phi <= y0
  auto f1111_2 = IntegrationAB(f111_3, 3, y0, DMakeFXi(1, 1., -1.));
  cout << "\tf1111_2 = " << f1111_2 << endl;
  auto f1111_1 = IntegrationAB(f1111_2, 1, 1 - phi, 0.5);
  cout << "\tf1111_1 = " << f1111_1 << endl;
  //       Region 1.1.1.2: yc_1 < 1
  //         y0 < 1 - phi
  auto f1112_2 = IntegrationAB(f111_3, 3, y0, DMakeFXi(1, 0., 1 + phi));
  cout << "\tf1112_2 = " << f1112_2 << endl;
  auto f1112_1 = IntegrationAB(f1112_2, 1, 0., 1 - phi);
  cout << "\tf1112_1 = " << f1112_1 << endl;
  auto f111_1 = f1111_1 + f1112_1;
  cout << "\tf111_1 = " << f111_1 << endl;
  //     Region 1.1.2: yc_1 < y1
  //       x1 * y1 <= x0 * y0
  //       (2 + phi) * y0 < y1 <= 1
  //       y0 < 1 - phi
  auto f112_3 = IntegrationAB(f1_4, 2, 0., x0 * y0 / y1);
  cout << "\tf112_3 = " << f112_3 << endl;
  auto f112_2 = IntegrationAB(f112_3, 3, DMakeFXi(1, 0, 2 + phi), 1.);
  cout << "\tf112_2 = " << f112_2 << endl;
  auto f112_1 = IntegrationAB(f112_2, 1, 0., 1 - phi);
  cout << "\tf112_1 = " << f112_1 << endl;
  auto f11_1 = f111_1 + f112_1;
  cout << "\tf11_1 = " << f11_1 << endl;
  //   Region 1.2:
  //   xc_1 <= x1 <= x0
  //   x0 * y0 <= x1 * y1
  //   -x0 * y0 <= (x1 - x0) * (y1 - y0)
  //     Region 1.2.1: y1 <= yc_1
  //       x0 * y0 <= x1 * y1
  //       x1 <= 1
  auto f121_3 = IntegrationAB(f1_4, 2, x0 * y0 / y1, x0);
  cout << "\tf121_3 = " << f121_3 << endl;
  //       Region 1.2.1.1: 1 <= yc_1
  //         1 <= (2 + phi) * y0
  //         1 - phi <= y0
  auto f1211_2 = IntegrationAB(f121_3, 3, y0, 1.);
  cout << "\tf1211_2 = " << f1211_2 << endl;
  auto f1211_1 = IntegrationAB(f1211_2, 1, 1 - phi, 1.0);
  cout << "\tf1211_1 = " << f1211_1 << endl;
  //       Region 1.2.1.2: yc_1 < 1
  //         y0 < 1 - phi
  auto f1212_2 = IntegrationAB(f121_3, 3, y0, DMakeFXi(1, 0., 2 + phi));
  cout << "\tf1212_2 = " << f1212_2 << endl;
  auto f1212_1 = IntegrationAB(f1212_2, 1, 0., 1 - phi);
  cout << "\tf1212_1 = " << f1212_1 << endl;
  auto f121_1 = f1211_1 + f1212_1;
  cout << "\tf121_1 = " << f121_1 << endl;
  //     Region 1.2.2: yc_1 < y1
  //       -x0 * y0 <= (x1 - x0) * (y1 - y0)
  //       (2 + phi) * y0 < y1 <= 1
  //       y0 < 1 - phi
  //       Substitute1: y1 = y0 + y1s
  //         y1s = y1 - y0
  //         (1 + phi) * y0 <= y1s <= 1 - y0
  //         -x0 * y0 <= (x1 - x0) * y1s
  auto f122_4 = SubstitutionFunction(f1_4, 3, y0 + y1);
  cout << "\tf122_4 = " << f122_4 << endl;
  auto f122_3 = IntegrationAB(f122_4, 2, x0 - x0 * y0 / y1, x0);
  cout << "\tf122_3 = " << f122_3 << endl;
  auto f122_2 =
      IntegrationAB(f122_3, 3, DMakeFXi(1, 0, 1 + phi), DMakeFXi(1, 1., -1));
  cout << "\tf122_2 = " << f122_2 << endl;
  auto f122_1 = IntegrationAB(f122_2, 1, 0., 1 - phi);
  cout << "\tf122_1 = " << f122_1 << endl;
  auto f12_1 = f121_1 + f122_1;
  cout << "\tf12_1 = " << f12_1 << endl;
  auto f1_1 = f11_1 + f12_1;
  cout << "\tf1_1 = " << f1_1 << endl;
  auto f1_0 = IntegrationAB(f1_1, 0, 0., 1.);
  cout << "\tf1_0 = " << f1_0 << endl;

  // Segment 2: x0 <= x1 <= 1, y0 <= y1 <= 1
  auto s2p = fc * (one - x1) * (one - y1);
  //   Substitute1: x1 = x0 + x1s, y1 = y0 + y1s
  //   After S1: 0 <= x1s <= 1 - x0, 0 <= y1s <= 1 - y0
  auto s2ps1 =
      SubstitutionFunction(SubstitutionFunction(s2p, 2, x0 + x1), 3, y0 + y1);
  //   Substitute2: x0 = 1 - x0s, y0 = 1 - y0s
  //   After S2: 0 <= x1s <= x0s, 0 <= y1s <= y0s
  auto s2ps2 = SubstitutionFunction(SubstitutionFunction(s2ps1, 0, one - x0), 1,
                                    one - y0);
  //   Region 2.1: (x1 - x0) * (y1 - y0) <= x0 * y0
  //     After S1: x1s * y1s <= x0 * y0
  //     After S2: x1s * y1s <= (1 - x0s) * (1 - y0s)
  //     Region 2.1.1: 1 <= x0 + y0
  //       After S2: x0s + y0s <= 1
  auto f4_211 = s2ps2;
  auto f3_211 = IntegrationAB(f4_211, 3, zero, y0);
  auto f2_211 = IntegrationAB(f3_211, 2, zero, x0);
  auto f1_211 = IntegrationAB(f2_211, 1, zero, one - x0);
  //     Region 2.1.2: x0 + y0 <= 1
  //       After S2: 1 <= x0s + y0s
  auto f4_212 = s2ps2;
  auto f3_212c = IntegrationAB(f4_212, 3, (one - x0) * (one - y0) / x1, y0);
  auto f3_212c_ii = Integration(f3_212c, 2);
  auto f2_212c_b = SubstitutionIndex(f3_212c_ii, 2, 0);
  auto a_212c_f3 = DMakeFXi(0, 1.) * DMakeFXi(1, 1.) / DMakeFXi(1);
  auto f2_212c_a = SubstitutionFactorized(f3_212c_ii, 2, a_212c_f3);
  auto f2_212c = f2_212c_b - f2_212c_a;
  auto f2_212 = f2_211 - f2_212c;
  auto f2_212_ii = Integration(f2_212, 1);
  auto f1_212_b = SubstitutionValue(f2_212_ii, 1, 1., true);
  auto a_212_f2 = -DMakeFXi(0, 1);
  auto f1_212_a = SubstitutionFactorized(f2_212_ii, 1, a_212_f2);
  auto f1_212 = f1_212_b - f1_212_a;
  auto f1_2 = f1_211 + f1_212;
  auto f0_2 = Integration(f1_2, 0, 0., 1., true);
  cout << "\tf0_2 = " << f0_2 << endl;

  // Segment 3: x0 <= x1 <= 1, 0 <= y1 <= y0
  //   Similar to Segment 1 under (x0 <-> y0) and (x1 <-> y1) swap
  auto f3_0 = f1_0;
  cout << "\tf3_0 = " << f3_0 << endl;

  // Segment 4: x0 <= x1 <= 1, y0 - 1 <= y1 <= 0
  auto s4p = fc * (1. - x1) * (1. + y1 - y0);
  //   xc_4 = (1 + phi) * x0, yc_4 = -phi * y0
  //   Region 4.1:
  //   xc_4 <= x1 <= 1
  //   -x0 * y0 <= x1 * y1
  //   (x1 - x0) * (y1 - y0) <= -x0 * y0
  //     Region 4.1.1 (c): (x1 - x0) * (y1 - y0) <= -x0 * y0
  //       Region 4.1.1.1: x1 < 1 <= 2*x0
  //         0.5 <= x0 < phi
  //       Region 4.1.1.2: 2*x0 < 1
  //         x0 <= 0.5
  auto f0_411 = zero;  // TODO.
  //     Region 4.1.2: x1 * y1 <= -x0 * y0
  //       yc_412 = -x0 * y0
  //       Region 4.1.2.1 (y0 - 1) <= yc_4
  //         (1+phi) y0 <= 1
  //         y0 <= phi
  auto f4_4121 = s4p;
  cout << "\tf4_4121 = " << f4_4121 << endl;
  auto f3_4121 = IntegrationAB(s4p, 3, -x0 * y0 / x1, zero);
  cout << "\tf3_4121 = " << f3_4121 << endl;
  auto f3_4121_ii = Integration(f3_4121, 2);
  cout << "\tf3_4121_ii = " << f3_4121_ii << endl;
  auto f2_4121_b = SubstitutionValue(f3_4121_ii, 2, 1., true);
  auto a_4121_f3 = DMakeFXi(0) * (1 + phi);
  auto f2_4121_a = SubstitutionFactorized(f3_4121_ii, 2, a_4121_f3);
  auto f2_4121 = f2_4121_b - f2_4121_a;
  cout << "\tf2_4121 = " << f2_4121 << endl;
  auto f1_4121 = Integration(f2_4121, 1, 0., phi, true);
  cout << "\tf1_4121 = " << f1_4121 << endl;
  auto f0_4121 = Integration(f1_4121, 0, 0., phi, true);
  cout << "\tf0_4121 = " << f0_4121 << endl;
  //       Region 4.1.2.2 yc4 < (y0 - 1) <= yc_412
  //         1 < (1+phi) y0
  //           phi < y0
  //         y0 * (1 + x0) <= 1
  //           y0 <= 1 / (1 + x0)
  //         Region 4.1.2.2.1
  //           xc_4 <= x1 <= 1
  //           -x0 * y0 / x1 <= y1 <= 0
  auto f2_41221 = f2_4121;
  cout << "\tf2_41221 = " << f2_41221 << endl;
  // auto f1_41221 = Integration(f2_41221, 0, (one - y0) / y0, phi * one);
  //   auto f2_41221_ii = Integration(f2_41221, 0);
  //   cout << "\tf2_41221_ii = " << f2_41221_ii << endl;
  //   auto f1_41221_b = SubstitutionValue(f2_41221_ii, 0, phi, true);
  //   auto a_41221_f2 = -DMakeFXi(1, 1) / DMakeFXi(1);
  //   auto f1_41221_a = SubstitutionFactorized(f2_41221_ii, 0, a_41221_f2);
  //   auto f1_41221 = f1_41221_b - f1_41221_a;
  //   cout << "\tf1_41221 = " << f1_41221 << endl;
  //   // auto f0_41221 = Integration(f1_41221, 1, phi, 1., true);
  //   auto f0_41221 = zero;  // TODO: Support integration
  //   cout << "\tf0_41221 = " << f0_41221 << endl;
  //         Region 4.1.2.2.2 (c)
  //           xc_4 <= x1 <= x0 * y0 / (1 - y0)
  //           -x0 * y0 / x1 <= y1 <= y0 - 1
  auto f4_41222 = s4p;
  cout << "\tf4_41222 = " << f4_41222 << endl;
  auto f3_41222 = IntegrationAB(f4_41222, 2, (1.0 + phi) * x0, -x0 * y0 / y1);
  cout << "\tf3_41222 = " << f3_41222 << endl;
  auto f3_41222_ii = Integration(f3_41222, 3);
  cout << "\tf3_41222_ii = " << f3_41222_ii << endl;
  auto b_f3_41222 = -DMakeFXi(1, 1);
  auto f2_41222_b = SubstitutionFactorized(f3_41222_ii, 3, b_f3_41222);
  auto a_f3_41222 = -DMakeFXi(1, 0) * phi;
  auto f2_41222_a = SubstitutionFactorized(f3_41222_ii, 3, a_f3_41222);
  auto f2_41222 = f2_41222_b - f2_41222_a;
  cout << "\tf2_41222 = " << f2_41222 << endl;
  auto f2_4122 = f2_41221 - f2_41222;
  cout << "\tf2_4122 = " << f2_4122 << endl;
  auto f2_4122_ii = Integration(f2_4122, 0);
  cout << "\tf2_4122_ii = " << f2_4122_ii << endl;
  auto f1_4122_b = SubstitutionValue(f2_4122_ii, 0, phi, true);
  auto a_4122_f2 = -DMakeFXi(1, 1) / DMakeFXi(1);
  auto f1_4122_a = SubstitutionFactorized(f2_4122_ii, 0, a_4122_f2);
  auto f1_4122 = f1_4122_b - f1_4122_a;
  cout << "\tf1_4122 = " << f1_4122 << endl;
  auto f0_4122 = Integration(f1_4122, 1, phi, 1., true);
  cout << "\tf0_4122 = " << f0_4122 << endl;
  //       Region 4.1.2.3 yc412 < (y0 - 1)
  //         1 < y0 * (1 + x0)
  //           1 / (1 + x0) < y0
  auto f4_4123 = s4p;
  cout << "\tf4_4123 = " << f4_4123 << endl;
  auto f3_4123 = IntegrationAB(f4_4123, 3, y0 - one, zero);
  cout << "\tf3_4123 = " << f3_4123 << endl;
  auto f2_4123 = IntegrationAB(f3_4123, 2, (1 + phi) * x0, one);
  cout << "\tf2_4123 = " << f2_4123 << endl;
  auto f1_4123 = IntegrationAB(f2_4123, 0, (one - y0) / y0, phi * one);
  cout << "\tf1_4123 = " << f1_4123 << endl;
  auto f0_4123 = Integration(f1_4123, 1, phi, 1., true);
  cout << "\tf0_4123 = " << f0_4123 << endl;
  auto f0_412 = f0_4121 + f0_4122 + f0_4123;
  cout << "\tf0_412 = " << f0_412 << endl;
  auto f0_41 = f0_412 - f0_411;
  cout << "\tf0_41 = " << f0_41 << endl;
  //   Region 4.2:
  //   x0 <= x1 <= xc_4
  //   x1 * y1 <= -x0 * y0
  //   -x0 * y0 <= (x1 - x0) * (y1 - y0)
  //     Similar to Region 4.1 under (x0 <-> y0) and (x1 <-> y1) swap
  auto f0_42 = f0_41;
  auto f0_4 = f0_41 + f0_42;
  cout << "\tf0_4 = " << f0_4 << endl;

  auto f0 = f1_0 + f0_2 + f3_0 + f0_4;
  cout << "\tf0 = " << f0 << endl;
  return 0;
}
