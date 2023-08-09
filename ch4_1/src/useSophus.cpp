#include <iostream>
#include <cmath>
#include <Eigen/Core>
#include <Eigen/Geometry>
//导入sophus相关的库
#include <sophus/se3.hpp>

using namespace std;
using namespace Eigen;

int main(int argc ,char **argv)
{
    //设置一个旋转矩阵 = 旋转向量（绕Z轴旋转90度）.转换为旋转矩阵（）；
    Matrix3d R = AngleAxisd(M_PI / 2 , Vector3d(0,0,1)).toRotationMatrix();
    //将旋转矩阵赋值给四元数q
    Quaterniond q(R);
    //可以由旋转矩阵直接得出特殊正交群
    Sophus::SO3d SO3_R(R);
    //也可以由四元数直接得出特殊正交群
    Sophus::SO3d SO3_Q(q);
    //打印出来
    cout << "SO(3) from rotation vector is \n" << SO3_R.matrix() << endl;
    cout << "SO(3) from quaternion is \n" << SO3_R.matrix() << endl;
    cout << "they are equal \n " << endl;
    
    //.log()函数直接提取特殊正交群的李代数（使用对数映射）
    Vector3d so3 = SO3_R.log();
    //打印出李代数（向量）
    cout << "so3 =    \n" << so3.transpose() << endl;
    //打印出李代数（向量转换为反对称矩阵）hat
    cout << "so3 hat =  \n  " << Sophus::SO3d::hat(so3) << endl;
    //打印出李代数（反对称矩阵转换为向量）vee
    cout << "so3 hat vee =\n    " << Sophus::SO3d::vee(Sophus::SO3d::hat(so3)).transpose() << endl;

    //增量扰动模型的更新

    //设置更新量为这么多
    Vector3d update_so3(1e-4,0,0);
    //求出更新后的
    Sophus::SO3d SO3_updated = Sophus::SO3d::exp(update_so3) * SO3_R;
    cout << "SO3 updated is  \n " << SO3_updated.matrix() << endl;


    cout << "*********************************" <<endl;


    //se3也是大同小异，so3懂了se3自然就看懂了，只不过是多了平移而已。
    Vector3d t(1,0,0);
    Sophus::SE3d SE3_Rt(R,t);
    Sophus::SE3d SE3_Qt(q,t);
    cout << "SE(3) from R,t is \n" << SE3_Rt.matrix() << endl;
    cout << "SE(3) from Q,t is \n" << SE3_Qt.matrix() << endl;

    typedef Eigen::Matrix<double,6,1> Vector6d;
    Vector6d se3 = SE3_Rt.log();
    cout << "se3 =    \n" << se3.transpose() << endl;
    cout << "se3 hat =  \n  " << Sophus::SE3d::hat(se3) << endl;
    cout << "se3 hat vee =\n    " << Sophus::SE3d::vee(Sophus::SE3d::hat(se3)).transpose() << endl;

    Vector6d update_se3;
    update_se3.setZero();
    update_se3(0,0) = 1e-4d;
    Sophus::SE3d SE3_updated = Sophus::SE3d::exp(update_se3) * SE3_Rt;
    cout << "SE3 updated is  \n " << SE3_updated.matrix() << endl;

    return 0;
}