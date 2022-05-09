//
// Created by ismat on 01.05.2022.
//
//Cartesian coordinates (x,y,z,x_dot,y_dot,z_dot)
//Keplerian elements (a,e,i,Omega,omega,M0) where M0 is the mean anomaly
#include "State.hpp"

State::State(std::vector<double> state,double mu){
    this -> state = state;
    this -> mu = mu;

}


std::vector<double> State::get_state() const{
    return this -> state;
}


void State::set_state( std::vector<double> state) {
    this -> state = state;
}


double State::get_mu() const{
    return this -> mu;
}

void State::set_mu(double mu){
    this -> mu = mu;
}

double State::get_parameter() const{
    return this -> get_a() * (1 - std::pow(this -> get_eccentricity(),2));
}

double State::v_from_ecc(const double & ecc, const double & e){

    double f = 2 * std::atan(std::sqrt((1 + e)/ (1 - e)) * std::tan(ecc/2));
    return f;
}


double State::ecc_from_f(const double & f,const double & e){

    double ecc = 2 * std::atan(std::sqrt((1 - e)/ (1 + e)) * std::tan(f/2));
    return ecc;
}



double State::get_n() const{
    return std::sqrt(this -> mu / std::pow(std::abs(this -> get_a()),3));
}


double State::H_from_f(const double & f,const double & e){

    return 2 * std::atanh(std::sqrt( (e - 1) / (1 + e) ) * std::tan( f / 2 ));
}

double State::v_from_H(const  double & H, const  double & e){

    double f = 2 * std::atan(std::sqrt( (1 + e) / (e - 1) ) * std::tanh( H / 2 ));

    return f;
}


double State::v_from_M(const double & M, const double & e){
    if (e < 1){
        return State::v_from_ecc(State::ecc_from_M(M, e), e);
    }
    else{
        return State::v_from_H(State::H_from_M(M, e), e) ;
    }
}

double State::ecc_from_M(const double & M,const double & e){

    double ecc = M;


    for (unsigned int i = 0; i < 1000; ++i){

        double max_decc = 0.1;

        double decc = (State::M_from_ecc(ecc,e) - M)/(1 - e * std::cos(ecc));

        int sign;
        if (decc >= 0){
            sign = 1;
        }
        else{
            sign = -1;
        }

        decc =  sign * std::min(max_decc,std::abs(decc));

        ecc = ecc - decc;

    }

    return ecc;

}


double State::H_from_M(const  double & M,const  double & e){

    double H = std::atan(M);

    double damp = 1;

    for (unsigned int i = 0; i < 1000; ++i){

        double max_dH = 0.1;

        double dH = (State::M_from_H(H,e) - M)/(e * std::cosh(H) - 1);

        int sign;
        if (dH >= 0){
            sign = 1;
        }
        else{
            sign = -1;
        }

        dH = damp * sign * std::min(max_dH,std::abs(dH));

        H = H - dH;

    }
    return H;

}


double State::M_from_ecc(const double & ecc,const double & e){

    return ecc - e * std::sin(ecc);
}


double State::M_from_H(const double & H,const double & e){

    return e * std::sinh(H) - H;
}


double State::M_from_f(const double & f,const double & e){

    if (e < 1){
        return State::M_from_ecc(State::ecc_from_f(f,e),e);
    }
    else{
        return State::M_from_H(State::H_from_f(f,e),e);
    }
}

