/*
 * obstacle.cpp
 *
 *  Created on: Dec 22, 2016
 *      Author: ingerbha
 */


#include "obstacle.h"

obstacle::obstacle(const Eigen::Matrix<double,9,1>& state, double T, double dt)
: n_samp_(T/dt)
{
	T_ = T;
	dt_ = dt;

	x_.resize(n_samp_);
	y_.resize(n_samp_);
	u_.resize(n_samp_);
	v_.resize(n_samp_);

	x_(0) = state(0);
	y_(0) = state(1);
	psi_ = state(2);
	u_(0) = state(3);
	v_(0) = state(4);
	A_ = state(5);
	B_ = state(6);
	C_ = state(7);
	D_ = state(8);

	r11_ = cos(psi_);
	r12_ = -sin(psi_);
	r21_ = sin(psi_);
	r22_ = cos(psi_);

	calculateTrajectory();
};

obstacle::~obstacle(){
};

Eigen::VectorXd obstacle::getX(){
	return x_;
}

Eigen::VectorXd obstacle::getY(){
	return y_;
}

Eigen::VectorXd obstacle::getU(){
	return u_;
}

Eigen::VectorXd obstacle::getV(){
	return v_;
}

double obstacle::getPsi(){
	return psi_;
}

double obstacle::getA(){
	return A_;
}

double obstacle::getB(){
	return B_;
}

double obstacle::getC(){
	return C_;
}

double obstacle::getD(){
	return D_;
}

void obstacle::calculateTrajectory()
{
	for (int i = 1; i < n_samp_;  i++)
	{
		x_(i) = (x_(i-1) + (r11_*u_(i-1) + r12_*v_(i-1))*dt_);
		y_(i) = (y_(i-1) + (r21_*u_(i-1) + r22_*v_(i-1))*dt_);
		u_(i) = (u_(i-1));
		v_(i) = (v_(i-1));
	}

};



