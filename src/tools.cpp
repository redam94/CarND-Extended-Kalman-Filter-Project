#include "tools.h"
#include <iostream>

using Eigen::VectorXd;
using Eigen::MatrixXd;
using std::vector;

Tools::Tools() {}

Tools::~Tools() {}

VectorXd Tools::CalculateRMSE(const vector<VectorXd> &estimations,
                              const vector<VectorXd> &ground_truth) {
  /**
   * TODO: Calculate the RMSE here.
   */
  VectorXd rmse(4);
  rmse << 0, 0, 0, 0;
  if((estimations.size() != ground_truth.size()) || ground_truth.size() == 0){
     std::cout << "Invalid length for estimations or ground_truth is empty" << std::endl;
     return rmse;
  }
  for(int i=0; i<estimations.size(); i++){
     VectorXd diff(4);
     diff = estimations[i].array() - ground_truth[i].array();
     rmse = rmse.array() + diff.array()*diff.array();
  }
  return rmse;
}

MatrixXd Tools::CalculateJacobian(const VectorXd& x_state) {
  /**
   * TODO:
   * Calculate a Jacobian here.
   */
  
}
