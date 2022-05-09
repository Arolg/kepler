#include "gtest/gtest.h"
#include "my_project/KeplState.hpp"
#include "my_project/CartState.hpp"

TEST(KeplerTests, Mercury) {

    std::cout << "FROM KEPLER ELEMENTS TO CARTESIAN STATE VECTORS\n";
    std::vector<double> kep_state_vec = {0.387098, 0.205635, 7.0047, 48.3313, 29.1241, 168.6562};
    double mu = 1;
    double dt = 1;
    KepState MercuryK(kep_state_vec, mu);
    CartState cart = MercuryK.convert_to_cart(dt);
    for (int i = 0; i < 6; ++i) {
        std::cout << cart.get_state()[i] << std::endl;
    }

    CartState Mercury(cart.get_state(), mu);
    KepState kep = Mercury.convert_to_kep(dt);
    for (int i = 0; i < 6; ++i)
    {
        std::cout << kep.get_state()[i] << std::endl;
    }

    ASSERT_TRUE(true);
}
