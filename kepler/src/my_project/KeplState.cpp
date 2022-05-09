//
// Created by ismat on 02.05.2022.
//
#include "KeplState.hpp"
#include "CartState.hpp"
KepState::KepState(std::vector<double> state,double mu) : State(state,mu){
}

KepState::KepState() : State(std::vector<double>(6),1){
}


double KepState::get_energy() const{
    return - this -> mu / (2 * this -> get_a());
}

double KepState::get_momentum() const{
    return std::sqrt(this -> mu * this -> get_parameter());
}

double KepState::get_speed(double f) const{
    return std::sqrt(this -> mu * (2./(this -> get_radius(f)) - 1./(this -> get_a())));
}

double KepState::get_radius(double f) const{
    return this -> get_parameter() / (1 + this -> get_eccentricity() * std::cos(f));
}

double KepState::get_a() const{
    return this -> state[0];
}

double KepState::get_eccentricity() const{
    return this -> state[1];
}

double KepState::get_inclination() const{
    return this -> state[2];
}

double KepState::get_Omega() const{
    return this -> state[3];
}

double KepState::get_omega() const{
    return this -> state[4];
}

double KepState::get_M0() const{
    return this -> state[5];
}


CartState KepState::convert_to_cart(double dt) const{

    double M = this -> get_M0() + this -> get_n() * dt;
    double v = State::v_from_M(M, this->get_eccentricity());


    double r = this -> get_radius(v);
    double r_dot = this -> get_momentum() / this -> get_parameter() * this -> get_eccentricity() * std::sin(v);

    std::vector<double> cartesian_state(6);
    cartesian_state[0] = r * ( std::cos(this -> get_Omega()) * std::cos(this -> get_omega()+ v) - std::sin(this -> get_Omega()) * std::sin(this -> get_omega()+ v) * std::cos(this -> get_inclination()) );
    cartesian_state[1] = r * ( std::sin(this -> get_Omega()) * std::cos(this -> get_omega()+ v) + std::cos(this -> get_Omega()) * std::sin(this -> get_omega()+ v) * std::cos(this -> get_inclination()) );
    cartesian_state[2] = r * ( sin(this -> get_omega()+ v) * sin(this -> get_inclination()) );

    cartesian_state[3] = cartesian_state[0] / r * r_dot - this -> get_momentum() / r * (std::cos(this->get_Omega()) * std::sin(this->get_omega() + v) + std::sin(this->get_Omega()) * std::cos(this->get_omega() + v) * std::cos(this->get_inclination()));
    cartesian_state[4] = cartesian_state[1] / r * r_dot - this -> get_momentum() / r * (std::sin(this->get_Omega()) * std::sin(this->get_omega() + v) - std::cos(this->get_Omega()) * std::cos(this->get_omega() + v) * std::cos(this->get_inclination()));
    cartesian_state[5] = cartesian_state[2] / r * r_dot + this -> get_momentum() / r * std::sin(this->get_inclination()) * std::cos(this->get_omega() + v);

    return CartState(cartesian_state,this -> mu);
}