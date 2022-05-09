//
// Created by ismat on 01.05.2022.
//

#ifndef MY_PROJECT_STATE_HPP
#define MY_PROJECT_STATE_HPP
#include <iostream>
#include <cmath>
#include <vector>
#include "overloads.hpp"

class State{

public:
    State(std::vector<double> state,double mu);


    /**
    Computes true anomaly from eccentric anomaly
    @param ecc eccentric anomaly
    @param e eccentricity (0 =< e < 1)
    @return true anomaly
    */
    static double v_from_ecc(const double & ecc, const double & e);

    template <typename T>
    static std::vector<T> cross(std::vector<T> const &a, std::vector<T> const &b)
    {
        std::vector<T> r (a.size());
        r[0] = a[1] * b[2]-b[1] * a[2];
        r[1] = - a[0] * b[2] + b[0] * a[2];
        r[2] = a[0] * b[1] - b[0] * a[1];
        return r;
    }

    template <typename T>
    static T norm(const std::vector<T>& vector)
    {
        T norm = static_cast<T>(0);
        for (const auto& elm: vector)
        {
            norm += elm * elm;
        }
        norm = std::sqrt(norm);

        return norm;
    }
    /**
    Computes eccentric anomaly eccentric from true anomaly
    @param f true anomaly
    @param e eccentricity (0 =< e < 1)
    @return eccentric anomaly
    */
    static double ecc_from_f(const double & f,const double & e);

    /**
    Computes hyperbolic anomaly from true anomaly
    @param f true anomaly
    @param e eccentricity (1 < e)
    @return hyperbolic anomaly
    */
    static double H_from_f(const double & f,const double & e);

    /**
    Computes true anomaly from hyperbolic anomaly
    @param H hyperbolic anomaly
    @param e eccentricity (1 < e)
    @return true anomaly
    */
    static double v_from_H(const  double & H, const  double & e);

    /**
    Computes true anomaly from mean anomaly
    @param M mean anomaly
    @param e eccentricity (0 =< e < 1)
    @return true anomaly
    */
    static double v_from_M(const double & M, const double & e);

    /**
    Computes eccentric anomaly eccentric from mean anomaly
    @param M mean anomaly
    @param e eccentricity (0 =< e < 1)
    @param pedantic if true, will print out convergence details
    @return eccentric anomaly
    */
    static double ecc_from_M(const double & M,const double & e);


    /**
    Computes hyperbolic anomaly eccentric from mean anomaly
    @param M mean anomaly
    @param e eccentricity (1 < e)
    @param pedantic if true, will print out convergence details
    @return hyperbolic anomaly
    */
    static double H_from_M(const  double & M,const  double & e);


    /**
    Computes mean anomaly from eccentric anomaly
    @param ecc eccentric anomaly
    @param e eccentricity (0 =< e < 1)
    @return mean anomaly
    */
    static double M_from_ecc(const double & ecc,const double & e);

    /**
    Computes mean anomaly from hyperbolic anomaly
    @param H hyperbolic anomaly
    @param e eccentricity (1 < e)
    @return mean anomaly
    */
    static double M_from_H(const double & H,const double & e);

    /**
    Computes mean anomaly from true anomaly
    @param f true anomaly
    @param e eccentricity (0 =< e < 1)
    @return mean anomaly
    */
    static double M_from_f(const double & f,const double & e);

    virtual double get_momentum() const = 0;
    virtual double get_energy() const = 0;
    virtual double get_a() const = 0;
    virtual double get_eccentricity() const = 0;


    std::vector<double> get_state() const;
    double get_n() const;
    double get_parameter() const;
    double get_mu() const;
    void set_mu(double mu);
    void set_state(std::vector<double> state) ;

protected:
    double mu;
    std::vector<double> state;
};

#endif //MY_PROJECT_STATE_HPP
