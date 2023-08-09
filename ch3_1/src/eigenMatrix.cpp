#include <iostream>
//用于定时的库
#include <ctime>
//Eigen的核心部分
#include <Eigen/Core>
//Eigen用于矩阵运算的部分
#include <Eigen/Dense>
//使用命名空间
using namespace std;
using namespace Eigen;
//矩阵最大长度，后面用到的
#define MATRIX_SIZE 100

int main(int argc,char **argv){
	//如果不在前面使用命名空间的话这里应该谢写为Eigen::Matrix..，float是声明了你创建了的矩阵的数据类型，后面依次是行数和列数。
    Matrix<float,2,3> matrix_23;
    //这个比较特殊，这个库里面有一些给你写好的矩阵类型，例如Vector3d就是double类型的三维向量，本质上他也是Eigen::Matrix..，只不过封装的更好了。
    Vector3d v_3d;
    Matrix<float,3,1> vd_3d;
    //这个代表3X3的double型矩阵，Matrix3d::Zero()是Eigen中的一个函数，意思是将矩阵所有元素的置都赋值为0.
    Matrix3d matrix_33 = Matrix3d::Zero();
    //Dynamic是动态的意思，也可以用-1代替，Matrix<double,Dynamic,Dynamic>就是未知行列数的double型矩阵（动态的矩阵）。在我们定义矩阵的时候，如果矩阵的类型我们是已知的，那么我们就尽量在定义的时候写清楚，这样的话程序在运行的时候效率会高很多。
    Matrix<double,Dynamic,Dynamic> matrix_dynamic;
    //MatrixXd就是未知行列数的double型方阵。
    MatrixXd matrix_x;
    //这是给矩阵赋值。
    matrix_23 << 1,2,3,4,5,6 ;
    cout << "matrix 2x3 from 1 to 6: \n" << matrix_23 << "\n\n" <<endl;

	//这里是通过遍历打印出矩阵里的所有元素，访问矩阵的时候用（）去访问
    cout << "print matrix 2x3:" << endl;
    for (int i =0 ;i<2 ;i++ ){
        for (int j=0 ;j<3;j++){
            cout << matrix_23(i,j) << "\t";
        }
        cout <<endl;
    }

    v_3d << 3,2,1;
    vd_3d << 4,5,6;
	
	//Eigen库定义的矩阵在运算时必须严格数据类型，不同的数据类型之间不能进行计算，当我们想让不同数据类型的矩阵进行运算的时候需要用.cast<type>()对矩阵进行类型转换。
    Matrix<double,2,1> result = matrix_23.cast<double>() * v_3d;
    cout << "[1,2,3;4,5,6] * [3;2;1] = \n" << result <<"\n\n" <<endl;

	//这里的赋值是给矩阵里的所有元素都赋值一个随机数。
    matrix_33 = Matrix3d::Random();
    //打印矩阵
    cout << "Random matrix :\n" << matrix_33 <<"\n\n" <<endl;
    //打印矩阵的转置
    cout << "Transpose : \n" << matrix_33.transpose() << "\n\n" <<endl;
    //打印矩阵的所有元素的和
    cout << "sum: \n" << matrix_33.sum() <<"\n\n" <<endl;
    //打印矩阵的迹（也就是主对角线所有元素的和）
    cout << "trace: \n" << matrix_33.trace() << "\n\n" <<endl;
    //打印矩阵的逆
    cout << "inverse: \n" << matrix_33.inverse() << "\n\n" <<endl;
    //打印矩阵的行列式的值
    cout << "det: \n" << matrix_33.determinant() << "\n\n" <<endl;


	//这里是求解矩阵的特征值和特征向量，eigen_solve(matrix_33.transpose() * matrix_33是为了保证对角化成功。
    SelfAdjointEigenSolver<Matrix3d> eigen_solve(matrix_33.transpose() * matrix_33);
    //打印矩阵的特征值
    cout << "Eigen value: \n" << eigen_solve.eigenvalues() <<"\n\n" << endl;
    //打印矩阵的特征向量
    cout << "Eigen vector: \n" << eigen_solve.eigenvectors() << "\n\n" <<endl;


	//这里是一个求解方程的例子，求解的方程为matrix_NN * X = v_Nd
	//我们通过三种方法来求解，并计算一下求解时间
    Matrix<double,MATRIX_SIZE,MATRIX_SIZE> matrix_NN = MatrixXd::Random(MATRIX_SIZE,MATRIX_SIZE);
    matrix_NN = matrix_NN * matrix_NN.transpose();
    Matrix<double, MATRIX_SIZE,1> v_Nd = MatrixXd::Random(MATRIX_SIZE,1);
	
	//记录当前的时间，储存在time_stt 里
    clock_t time_stt = clock();
    //利用直接求逆的方法求X
    Matrix<double,MATRIX_SIZE,1> x = matrix_NN.inverse() * v_Nd;
    //进行计时    ps：这里的CLOCKS_PER_SEC的意思是你计算机一秒计时的周期数，我刚开始也不知带这个是什么东东，如果不知道我在说啥那就去搜一下，下面我也会给出链接
    cout << "time of normal inverse is :"
         << 1000 * (clock()-time_stt) / (double) CLOCKS_PER_SEC
         << "ms"
         << endl;
    cout << "x = " << x.transpose() << "\n\n" <<endl;

    time_stt = clock();
    //利用QR分解法求X         （鬼知道这是什么东西，没有去深入了解，感觉应该也不用深入了解是怎么分解的，如果我学到后面发现真需要搞懂，我会回来补坑的）
    x = matrix_NN.colPivHouseholderQr().solve(v_Nd);
    cout << "time of Qr decomposition is :"
         << 1000 * (clock()-time_stt) / (double) CLOCKS_PER_SEC
         << "ms"
         << endl;
    cout << "x = " << x.transpose() << "\n\n" <<endl;

    time_stt = clock();
    //利用cholesky分解法求X   （鬼知道这是什么东西，没有去深入了解，感觉应该也不用深入了解是怎么分解的，如果我学到后面发现真需要搞懂，我会回来补坑的）
    x = matrix_NN.ldlt().solve(v_Nd);
    cout << "time of ldlt decomposition is :"
         << 1000 * (clock()-time_stt) / (double) CLOCKS_PER_SEC
         << "ms"
         << endl;
    cout << "x = " << x.transpose() << "\n\n" <<endl;

	//书里说在QR分解法是最快的，试了一下确实如此
    return 0;

}