﻿#pragma once

#include <glm/glm.hpp>
#include "Ray.h"
#include "DirectionalLight.h"

#define M_PHI 1.618033988749895

class Atmosphere
{
public:
    explicit Atmosphere(DirectionalLight* _sun_light,
                        double _earth_radius      = 6360e3f,
                        double _atmosphere_radius = 6420e3f,
                        double _h_rayleigh        = 7994.0f,
                        double _h_mie             = 1200.0f)
                        : sun_light        (_sun_light),
                          planet_radius    (_earth_radius),
                          atmosphere_radius(_atmosphere_radius),
                          h_rayleigh       (_h_rayleigh),
                          h_mie            (_h_mie)
    {
        m_center = glm::highp_dvec3(0.0f, 
                                    planet_radius + 1000.0f, 
                                    0.0f);
        sun_light->m_direction = glm::normalize(sun_light->m_direction);
    }

    ~Atmosphere() {}

    static double f(double x)
    {
//        if(x > 0.0f || x < -1.0f)
//        printf("x = %.2f\n",x);
        return exp(x); //15.0232s
//        return 1.0 - x + (x * x * 0.5) - (x*x*x / 6.0) + (x*x*x*x / 24.0);
//        return glm::pow(M_PHI, x); //18.6742s
    }

    glm::highp_dvec3 computeIncidentLight(const Ray & ray, double t_min, double t_max, glm::highp_dvec3& transmittance);
    glm::highp_dvec3 computeLightColor(const Ray & ray, double t_min, double t_max, double NdotL, glm::highp_dvec3& ambient);
    bool intersect(const Ray & ray, double & t0, double & t1, bool is_planet = false);
    glm::highp_dvec3 computeColor(const Ray & ray, glm::highp_dvec3& transmittance, double& t_max);

    DirectionalLight* sun_light;
    glm::highp_dvec3 m_center;
    double planet_radius;
    double atmosphere_radius;
    double h_rayleigh;
    double h_mie;

    static const glm::highp_dvec3 BETA_RAYLEIGH;
    static const glm::highp_dvec3 BETA_MIE;
};
