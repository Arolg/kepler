//
// Created by ismat on 02.05.2022.
//

#ifndef MY_PROJECT_KEPLSTATE_HPP
#define MY_PROJECT_KEPLSTATE_HPP

#include "State.hpp"
class CartState;
class KepState : public State{

public:

    /**
    Constructor
    @param state 6x1 vector of orbital elements ordered like so :
    - sma : semi-major axis [L]
    - e : eccentricity [-]
    - i : inclination in [0,pi] [rad]
    - Omega : right-ascension of ascending node in [0,2 pi] [rad]
    - omega : longitude of perigee [0,2 pi] [rad]
    - M0 : mean anomaly at epoch [rad]
    @param mu standard gravitational parameter of central body
    */
    KepState(std::vector<double> state,double mu);
    KepState();


    virtual double get_energy() const;
    virtual double get_a() const;
    virtual double get_eccentricity() const;
    virtual double get_momentum() const;

    double get_inclination() const;
    double get_Omega() const;
    double get_omega() const;
    double get_M0() const;


    double get_speed(double f) const;
    double get_radius(double f) const;

    /**
    Returns the cartesian state corresponding to the
    keplerian state
    @param delta_T time since epoch
    @return cartesian state vector (x, y, z, x_dot, y_dot, z_dot)
    */

    CartState convert_to_cart(double delta_T) const;


protected:

};


#endif //MY_PROJECT_KEPLSTATE_HPP
