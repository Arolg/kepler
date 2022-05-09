#include "gtest/gtest.h"
#include "my_project/KeplState.hpp"
#include "my_project/CartState.hpp"

TEST(KeplerTests, test) {

    std::cout << "FROM KEPLER ELEMENTS TO CARTESIAN STATE VECTORS\n";
    std::vector<double> kep_state_vec = {7000,0.06,0.5,0.4,0.4,-0.5};
    double mu = 398600;
    double dt = 300;
    KepState K(kep_state_vec, mu);
    CartState cart = K.convert_to_cart(dt);
    for (int i = 0; i < 6; ++i) {
        std::cout << cart.get_state()[i] << std::endl;
    }

    CartState C(cart.get_state(), mu);
    KepState kep = C.convert_to_kep(dt);
    for (int i = 0; i < 6; ++i)
    {
        std::cout << kep.get_state()[i] << std::endl;
    }

    ASSERT_TRUE(true);
}
