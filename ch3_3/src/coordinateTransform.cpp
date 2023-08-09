//include各种库
#include <iostream>
#include <cmath>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <algorithm>

using namespace std;
using namespace Eigen;

int main(int argc ,char **argv){
	
	//定义两个小萝卜的四元数并赋值
    Quaterniond q1(0.35,0.2,0.3,0.1),q2(-0.5,0.4,-0.1,0.2);
    //四元数归一化（！！！！！四元数使用前需要归一化）
    q1.normalize();
    q2.normalize();

	//定义两个小萝卜的平移向量
    Vector3d t1(0.3,0.1,0.1),t2(-0.1,0.5,0.3);

	//小萝卜一号看到的
    Vector3d p1(0.5,0,0.2);
	/*
		不要忘记了欧氏变换矩阵的形式
		| R, T |
		| 0, 1 |
	*/
	//定义两个欧氏变换矩阵并把四元数赋值给他们（也就是相当于初始化变换矩阵的旋转矩阵）【四元数表示旋转】
    Isometry3d T1w(q1),T2w(q2);

	/*
		当然，你也可以这么写
		//将四元数转换为旋转矩阵
		Matrix3d R1 = q1.toRotationMatrix();
		Matrix3d R2 = q2.toRotationMatrix();
		//将旋转矩阵赋值给欧氏变换矩阵
		Isometry3d T1w.rotate(R1);
		Isometry3d T2w.rotate(R2);
	*/

    //将平移向量给到变换矩阵
    T1w.pretranslate(t1);
    T2w.pretranslate(t2);
    //根据刚才推出来的公式进行计算
    //这里为什么要对T1w取逆再运算呢，如果理解不了这一个地方的建议回到3.1去复习一下
    Vector3d p2 = T2w*T1w.inverse() *p1;
    cout << endl << p2.transpose() << endl;
    return 0;
}