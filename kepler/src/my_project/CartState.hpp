//
// Created by ismat on 02.05.2022.
//

#ifndef MY_PROJECT_CARTSTATE_HPP
#define MY_PROJECT_CARTSTATE_HPP

#include "State.hpp"
class KepState;

class CartState : public State{

public:
    /**
    Constructor
    @param state 6x1 vector of cartesian state :
    - x
    - y
    - z
    - x_dot
    - y_dot
    - z_dot
    @param mu standard gravitational parameter of central body [L^3/T^2]
    */
    CartState( std::vector<double> state,double mu);
    CartState();

    virtual double get_momentum() const;
    virtual double get_energy() const;
    virtual double get_a() const;
    virtual double get_eccentricity() const;

    double get_speed() const;
    double get_radius() const;

    std::vector<double> get_position_vector() const;
    std::vector<double> get_velocity_vector() const;
    std::vector<double> get_momentum_vector() const ;
    std::vector<double> get_eccentricity_vector() const ;

    /**
    Returns the keplerian orbital elements state corresponding to the
    cartesian state
    @param delta_T time since epoch
    @return keplerian state vector of orbital_elements (a, e, i, Omega, omega, M0)
    */

    KepState convert_to_kep(double delta_T) const;

protected:

};
#endif //MY_PROJECT_CARTSTATE_HPP
