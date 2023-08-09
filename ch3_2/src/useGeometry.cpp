#include <iostream>
#include <cmath>
#include <Eigen/Core>
#include <Eigen/Geometry>

using namespace std;
using namespace Eigen;

int main(int argc ,char **argv){
	//Eigen/Geometry模块提供了各种旋转和平移的表示
	//3d旋转矩阵直接使用Matrix3d或Matrix3f，这里的Identity()函数将矩阵初始化为单位矩阵
    Matrix3d rotation_matrix = Matrix3d::Identity();
    //AngleAxisd（旋转向量），此句创建了一个绕着z轴旋转45度的旋转向量。其中，M_PI/4表示旋转角度，即π/4，Vector3d(0,0,1)表示旋转轴，即z轴的单位向量。
    AngleAxisd rotation_vector(M_PI / 4 , Vector3d(0,0,1));
    //将输出流中浮点数的小数部分保留3位，其余部分按默认方式处理。不懂的我后面给个链接嘻嘻
    cout.precision(3);
    //打印出这个旋转向量
    cout << "rotation_matrix = \n" << rotation_vector.matrix() << endl;
     
    //一条语句，将旋转向量直接转换为旋转矩阵，是不是很方便哈哈哈 
    rotation_matrix = rotation_vector.toRotationMatrix();
    //再打印出来
    cout << "rotation_matrix = \n" << rotation_matrix << endl;
	
	//这条语句定义了旋转前点v的坐标v（1，0，0）
    Vector3d v(1,0,0);
    //看不懂这一句的回去前面讲旋转向量那里再看看，旋转向量乘以原坐标得出旋转后的坐标（这是因为重载了运算符）
    Vector3d v_rotated = rotation_vector * v;
    cout << "(1,0,0) after rotation (by rotation_vector) = " << v_rotated.transpose() << endl;
	
	//旋转矩阵乘以原坐标得出旋转后的坐标（这是因为重载了运算符）
    v_rotated = rotation_matrix * v;
    cout << "(1,0,0) after rotation (by rotation_matrix) = " << v_rotated.transpose() << endl;

	//欧拉角：可以直接将旋转矩阵转换成欧拉角
	/*
	在Eigen库中，Matrix3d类和Quaterniond类都提供了eulerAngles()方法，用于将
	旋转矩阵或四元数转换为欧拉角（Euler angles）。其中，eulerAngles()方法接受
	三个参数，分别表示旋转顺序。在这个三个参数中，每个参数都是一个整数，用于表示绕
	哪个坐标轴旋转的角度。数值从0到2，分别代表x轴、y轴、z轴。例如，(2,1,0)表示先
	绕z轴旋转，再绕y轴旋转，最后绕x轴旋转。这个旋转顺序通常被称为“ZYX”旋转顺序。
	使用不同的旋转顺序，会得到不同的欧拉角表示。在机器人控制和导航中，常常需要根据
	具体的应用场景，选择合适的旋转顺序来描述物体的旋转姿态。
	*/
    Vector3d euler_angles = rotation_matrix.eulerAngles(2,1,0);
    //打印出欧拉角（“偏航-俯仰-滚转”（yaw-pitch-roll)）
    cout << "yaw pitch roll = " << euler_angles.transpose() <<endl; 

	//欧氏变换矩阵用Eigen::Isomestry   
	//忘了什么是欧氏变换矩阵的回去看3.1.3
    Isometry3d T = Isometry3d::Identity();  //三维欧氏变换矩阵是一个4X4的矩阵。这里虽然为3d，但是实质上T是4X4的矩阵
    //还记得欧氏变换矩阵有旋转矩阵和平移向量吧
    T.rotate(rotation_vector);//这一句是赋值了旋转矩阵（按照rotation_vector进行旋转）
    T.pretranslate(Vector3d(1,3,4));//这一句是赋值了平移矩阵（把平移向量设置为1，3，4）
    //打印出来赋完值的旋转矩阵
    cout << "Transform Matrix = \n" << T.matrix() << endl;

	//用变换矩阵进行坐标变换
    Vector3d v_transformed = T * v;//相当于R*v+t
    //打印出变换好的
    cout << "v_transformed = " << v_transformed.matrix() << endl;

	//四元数

	//可以将旋转向量直接转换成相对应的四元数，反之亦然
    Quaterniond q = Quaterniond(rotation_vector);
    //打印出来，这里有一个要注意的地方，就是coeffs（）这个函数将这个四元数转换成了矩阵，并且顺序是（x，y，z，w）其中w为实部，前三者为虚部。
    cout << "quaternion from rotation vector = " << q.coeffs().transpose() << endl;
	
	//也可以将旋转矩阵赋值给他
    q = Quaterniond(rotation_matrix);
    cout << "quaternion from rotation matrix = " << q.coeffs().transpose() << endl;
	
	//使用四元数旋转一个向量，使用重载了打乘法
    v_rotated = q * v;//这里的乘法是重载了的，数学上是 q * v * q的逆
    cout << "(1,0,0) after rotation (by quaternion) = " << v_rotated.transpose() << endl;
	
	//这里也给出了不使用重载的函数，用常规的数学运算来求出坐标，但是不建议，看起来就复杂的头皮发麻QAQ
    cout << "should be equal to " << (q * Quaterniond(0,1,0,0) * q.inverse()).coeffs().transpose() << endl;

    return 0;
}