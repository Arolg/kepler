//
// Created by ismat on 02.05.2022.
//

#include "CartState.hpp"
#include "KeplState.hpp"
CartState::CartState(std::vector<double> state,double mu) : State(state,mu){

}

CartState::CartState() : State(std::vector<double>(6),1){}


std::vector<double> CartState::get_position_vector() const{
    std::vector<double> state(this->state.begin(), this->state.begin() + 3);
    return state;
}


std::vector<double> CartState::get_velocity_vector() const{
    std::vector<double> state(this->state.begin() + 3, this->state.begin() + 6);
    return state;
}

double CartState::get_speed() const{
    return norm(this -> get_velocity_vector());
}

double CartState::get_radius() const{
    return norm(this -> get_position_vector());
}

double CartState::get_momentum() const{
    return norm(this -> get_momentum_vector());
}

double CartState::get_energy() const{
    return std::pow(this -> get_speed(), 2) / 2 - this -> mu /(this -> get_radius());
}


double CartState::get_a() const{
    double energy = this -> get_energy();
    return  - this -> mu/(2 * energy);
}

std::vector<double> CartState::get_momentum_vector() const {
    std::vector<double> h_vector = cross(this -> get_position_vector(), this -> get_velocity_vector());
    return h_vector;
}

std::vector<double> CartState::get_eccentricity_vector() const {
    std::vector<double> ecc_vector = (cross(this -> get_velocity_vector(),this -> get_momentum_vector()) / (this -> mu)
                                      - this -> get_position_vector() / norm(this -> get_position_vector()));
    return ecc_vector;
}

double CartState::get_eccentricity() const{
    return norm(this -> get_eccentricity_vector());
}

KepState CartState::convert_to_kep(double delta_T) const{

    double a = this -> get_a();


    std::vector<double> h_vector = this -> get_momentum_vector();
    double h = this -> get_momentum();


    std::vector<double> ecc_vector = this -> get_eccentricity_vector();
    double e = this -> get_eccentricity();


    double p = this -> get_parameter();


    std::vector<double> Z_axis = {0,0,1};
    std::vector<double> nodal_line = cross(Z_axis,h_vector);
    double Omega;
    if (nodal_line[1] >= 0) {
        if (norm(nodal_line) > 0)
            Omega = acos(nodal_line[0] / norm(nodal_line));
        else
            Omega = 0.0;
    } else
        Omega = 2 * M_PI - acos(nodal_line[0] / norm(nodal_line));

    double i = std::acos((h_vector / h)[2]);
    double omega;
    if (ecc_vector[2] >= 0) {
        if (norm(nodal_line) > 0 && norm(ecc_vector) > 0)
            omega = acos(ecc_vector * nodal_line / norm(ecc_vector) / norm(nodal_line));
        else
            omega = 0.0;
    } else
        omega = 2 * M_PI - acos(ecc_vector * nodal_line / norm(ecc_vector) / norm(nodal_line));



    double cos_e = 1./e * (p / this -> get_radius() - 1);
    double f;
    if (std::abs(cos_e - 1) < 1e-10){
        f = 0;
    }
    else if (std::abs(cos_e + 1) < 1e-10){
        f = M_PI;
    }
    else{
        f = std::acos(cos_e);
    }



    if ((this -> get_position_vector() * this -> get_velocity_vector()) < 0){
        f = 2 * M_PI - f;
    }

    double ecc,M,H;
    if (e < 1){
        ecc = State::ecc_from_f(f,e);
        M = ecc - e * std::sin(ecc);
    }

    else {
        H = State::H_from_f(f,e);
        M = e * std::sinh(H) - H;
    }

    double n = std::sqrt(this -> mu / std::pow(std::abs(a) , 3));

    double M0 = M - n * delta_T;

    std::vector<double> kep_state = {a,e,i,Omega,omega,M0};

    return KepState(kep_state,this -> mu);
}