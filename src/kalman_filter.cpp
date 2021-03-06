#include "kalman_filter.h"

using Eigen::MatrixXd;
using Eigen::VectorXd;

/* 
 * Please note that the Eigen library does not initialize 
 *   VectorXd or MatrixXd objects with zeros upon creation.
 */

KalmanFilter::KalmanFilter() {}

KalmanFilter::~KalmanFilter() {}

void KalmanFilter::Init(VectorXd &x_in, MatrixXd &P_in, MatrixXd &F_in,
                        MatrixXd &H_in, MatrixXd &R_in, MatrixXd &Q_in) {
  x_ = x_in;
  P_ = P_in;
  F_ = F_in;
  H_ = H_in;
  R_ = R_in;
  Q_ = Q_in;
}

void KalmanFilter::Predict() {
  /**
   * TODO: predict the state
   */
  x_ = F_ * x_;
  MatrixXd Ft_ = F_.transpose();
  P_ = F_ * P_ * Ft_ + Q_;
}

void KalmanFilter::Update(const VectorXd &z) {
  /**
   * TODO: update the state by using Kalman Filter equations
   */
  VectorXd z_pred = H_ * x_;
  VectorXd y  = z - z_pred;
  UpdateCommon(y);

}

void KalmanFilter::UpdateEKF(const VectorXd &z) {
  /**
   * TODO: update the state by using Extended Kalman Filter equations
   */
  VectorXd z_pred(3);
  double rho = sqrt(x_(0)*x_(0) + x_(1)*x_(1));
  if(rho>0.00001){
    z_pred << rho, 
            atan2(x_(1), x_(0)),
            (x_(0)*x_(2)+x_(1)*x_(3))/(rho);
  } else{
    z_pred << rho, atan2(x_(1), x_(0)), 0.;
  }
  VectorXd y = z - z_pred;
  while(y(1)>M_PI){
    y(1) -= 2*M_PI;
  }
  while(y(1)<-M_PI){
    y(1) += 2*M_PI;
  }
  UpdateCommon(y);
}

void KalmanFilter::UpdateCommon(const VectorXd y){
  MatrixXd Ht = H_.transpose();
  MatrixXd S  = H_ * P_ * Ht + R_;
  MatrixXd Si = S.inverse();
  MatrixXd PHt = P_ * Ht;
  MatrixXd K = PHt * Si;

  x_ = x_ + (K*y);
  P_ = P_ - K*H_*P_;
}
