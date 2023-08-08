//导入pangolin的库
#include <pangolin/pangolin.h>
//导入Eigen的相关库
#include <Eigen/Core>
#include <Eigen/Geometry>
//导入Linux系统中使用的一些系统调用函数。比如usleep函数
#include <unistd.h>

// 本例演示了如何画出一个预先存储的轨迹
using namespace std;
using namespace Eigen;

//轨迹文件的路径
string trajectory_file = "/home/psj/Desktop/slam_study/ch3_4/src/trajectory.txt";

//函数声明
void DrawTrajectory(vector<Isometry3d, Eigen::aligned_allocator<Isometry3d>>);

//定义主函数
int main(int argc, char **argv) 
{
  /*    使用Eigen库中的Isometry3d类型作为元素的向量。Isometry3d是一个3D变换矩阵类型。

        Eigen::aligned_allocator<Isometry3d> 是一个用于分配 Isometry3d 对象的自定义分配器。它是在使用
        Eigen 库时为了保证内存对齐而提供的。在 C++ 中，内存对齐是指在分配内存时，确保某些类型的对象的地址
        是对齐的，以提高访问效率。对于 Eigen 库中的一些特殊类型，如 Isometry3d，它们需要按照特定的对齐要
        求进行存储，以避免性能损失。

        poses是定义的变量
  */  
  vector<Isometry3d, Eigen::aligned_allocator<Isometry3d>> poses;
  /*
        ifstream fin(trajectory_file) 是在 C++ 中使用输入文件流对象 ifstream 打开一个文件。在这个代码
        中，它用于打开存储轨迹信息的文件 trajectory_file。

        ifstream是C++标准库中用于从文件中读取数据的类。它提供一组用于读取文件内容的成员函数和操作符重载。
        此处, trajectory_file 是一个表示文件路径的字符串，用于指定要打开的轨迹文件的位置。ifstream 对象
        fin 被创建并与该文件关联。

        一旦文件被成功打开，您就可以使用 fin 对象来读取文件中的数据。通常，您可以使用 >> 操作符重载来逐个
        读取文件中的数据项。

        请注意，打开文件之后，应该检查文件是否成功打开。可以通过检查 fin 对象的状态来确定文件是否成功打开。
        例如，可以使用 fin.is_open() 来检查文件是否打开成功。
  */
  ifstream fin(trajectory_file);
  if (!fin) 
  {
    cout << "cannot find trajectory file at " << trajectory_file << endl;
    return 1;
  }
  /*
        !fin.eof() 是对输入文件流对象 fin 的 eof() 成员函数的逻辑非操作。在C++中，eof() 函数用于检查文件
        流的结束标志。
        
        eof() 返回一个布尔值，表示文件流是否已达到文件末尾。当文件流到达文件末尾时，eof() 返回 true，否则
        返回 false。

        此处，!fin.eof() 用于检查文件流 fin 是否还未到达文件末尾。如果文件流还未到达文件末尾，!fin.eof() 
        的结果为真，表示文件流尚未结束。
  */
  while (!fin.eof()) 
  {
    /*
        time：时间
        tx：平移向量的 x 分量
        ty：平移向量的 y 分量
        tz：平移向量的 z 分量
        qx：四元数的 x 分量
        qy：四元数的 y 分量
        qz：四元数的 z 分量
        qw：四元数的 w 分量
    */
    double time, tx, ty, tz, qx, qy, qz, qw;
    //赋值
    fin >> time >> tx >> ty >> tz >> qx >> qy >> qz >> qw;
    //定义欧氏变换矩阵Twr并用四元数初始化他的旋转矩阵
    Isometry3d Twr(Quaterniond(qw, qx, qy, qz));
    //初始化他的平移矩阵
    Twr.pretranslate(Vector3d(tx, ty, tz));
    //调用 push_back(Twr)，将 Twr 添加到 poses 容器的末尾，扩展容器的大小，并将 Twr 插入到新的位置。
    poses.push_back(Twr);
  }
  //size() 是容器的成员函数之一，用于返回容器中元素的数量。
  cout << "read total " << poses.size() << " pose entries" << endl;

  //画出轨迹
  DrawTrajectory(poses);
  return 0;
}

//画出轨迹的函数
void DrawTrajectory(vector<Isometry3d, Eigen::aligned_allocator<Isometry3d>> poses) 
{
  // create pangolin window and plot the trajectory
  //创建显示窗口
  pangolin::CreateWindowAndBind("Trajectory Viewer", 1024, 768);
  /*
        glEnable(GL_DEPTH_TEST); 是OpenGL函数调用，用于启用深度测试。
        在OpenGL中，深度测试是一种用于确定像素是否应该被绘制的技术。它通过比较每个像素的深度值（即离相机的距离）
        与当前已绘制像素的深度值进行判断。只有当像素的深度值小于当前已绘制像素的深度值时，才会将该像素绘制到屏幕
        上，从而实现正确的遮挡关系。
        通过调用 glEnable(GL_DEPTH_TEST)，我们启用了深度测试功能。这意味着在绘制场景时，OpenGL会自动处理深度值，
        确保正确的遮挡关系，并按照深度值绘制像素。  
  */
  glEnable(GL_DEPTH_TEST);
  /*
        glEnable(GL_BLEND); 是OpenGL函数调用，用于启用混合功能。
        在OpenGL中，混合（Blending）是一种将新像素颜色与已存在的像素颜色进行混合的技术。通过启用混合功能，可以实
        现透明效果、颜色混合以及其他特殊效果。
        调用 glEnable(GL_BLEND) 启用了混合功能。这意味着在绘制过程中，OpenGL将根据特定的混合方程式，将新的像素颜
        色与已存在的像素颜色进行混合，并将混合后的结果绘制到屏幕上。
  */
  glEnable(GL_BLEND);
  /*
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 是 OpenGL 函数调用，用于设置混合函数。
        在 OpenGL 中，混合函数用于指定混合因子，控制混合操作中源颜色和目标颜色的权重。glBlendFunc() 函数接受两个参
        数，分别是源混合因子和目标混合因子。
        在这个特定的调用中，GL_SRC_ALPHA 指定源混合因子，表示使用源颜色的alpha值作为权重。GL_ONE_MINUS_SRC_ALPHA
        指定目标混合因子，表示使用目标颜色的 alpha 值的补数作为权重。
        因此，这个混合函数设置将根据源颜色的 alpha 值和目标颜色的 alpha 值的补数来进行混合操作。这通常用于实现透明效
        果，其中源颜色的透明度决定了最终像素的透明度，并与背景进行混合。
        需要注意的是，在调用 glBlendFunc() 之前，应该先启用混合功能（通过调用 glEnable(GL_BLEND)）
  */
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  /*
        pangolin::OpenGlRenderState 是 Pangolin 库中的一个类，它用于管理 OpenGL 渲染状态，包括投影矩阵、模型视图
        矩阵和其他与渲染相关的状态。
        通过调用 pangolin::OpenGlRenderState() 的无参数构造函数，创建了一个名为 s_cam 的 OpenGlRenderState 对象。
        这个对象将用于在 Pangolin 窗口中设置和管理 OpenGL 渲染状态，以便进行后续的渲染操作。
  */
  pangolin::OpenGlRenderState s_cam
  (
  /*
        pangolin::ProjectionMatrix(1024, 768, 500, 500, 512, 389, 0.1, 1000) 是一个函数调用，用于创建 Pangolin 
        中的投影矩阵。
        pangolin::ProjectionMatrix() 是 Pangolin 库中的一个函数，它用于创建一个投影矩阵，用于定义场景的投影变换。
        在这个特定的调用中，传递了一系列参数 (1024, 768, 500, 500, 512, 389, 0.1, 1000)，用于定义投影矩阵的属性。
        具体参数的含义如下：
            1024 和 768 是视口的宽度和高度（以像素为单位）。
            -500 和 500 是投影平面的左右边界。
            -512 和 389 是投影平面的上下边界。
            0.1 和 1000 是近裁剪面和远裁剪面的位置。
        通过调用 pangolin::ProjectionMatrix(1024, 768, 500, 500, 512, 389, 0.1, 1000)，会创建一个投影矩阵，定义了
        场景的投影变换，用于后续的渲染操作和绘制。
  */
    pangolin::ProjectionMatrix(1024, 768, 500, 500, 512, 389, 0.1, 1000),
  /*
        pangolin::ModelViewLookAt(0, -0.1, -1.8, 0, 0, 0, 0.0, -1.0, 0.0) 是一个函数调用，用于创建 Pangolin中的模
        型视图矩阵。
        pangolin::ModelViewLookAt() 是 Pangolin 库中的一个函数，它用于创建一个 LookAt 视图矩阵，用于定义场景的观察变换。
        在这个特定的调用中，传递了一系列参数 (0, -0.1, -1.8, 0, 0, 0, 0.0, -1.0, 0.0)，用于定义模型视图矩阵的属性。
        具体参数的含义如下：
            0, -0.1, -1.8 是相机位置的 x、y、z 坐标。
            0, 0, 0 是观察目标的 x、y、z 坐标。
            0.0, -1.0, 0.0 是相机的上向量的 x、y、z 分量。
        通过调用 pangolin::ModelViewLookAt(0, -0.1, -1.8, 0, 0, 0, 0.0, -1.0, 0.0)，会创建一个模型视图矩阵，定义了场景
        的观察变换，用于后续的渲染操作和绘制。这个观察变换将相机位置设置为 (0, -0.1, -1.8)，观察目标设置为原点 (0, 0, 0)，
        并指定了相机的上向量。
  */
    pangolin::ModelViewLookAt(0, -0.1, -1.8, 0, 0, 0, 0.0, -1.0, 0.0)
  );
  /*
        在这个语句中，首先通过调用 pangolin::CreateDisplay()创建一个显示窗口，并将返回的pangolin::View对象赋值给d_cam引用。
        接下来，通过调用 SetBounds() 方法设置了窗口的边界。具体的参数 (0.0, 1.0, 0.0, 1.0, -1024.0f / 768.0f) 定义了窗口边
        界的范围。前两个参数 0.0 和 1.0 表示窗口的水平边界范围，从左边界到右边界。后两个参数 0.0 和 1.0 表示窗口的垂直边界范围
        ，从下边界到上边界。最后一个参数 -1024.0f / 768.0f 是窗口的纵横比（aspect ratio），用于保持窗口显示的宽高比。
        最后，通过调用 SetHandler() 方法设置了一个 pangolin::Handler3D 对象作为窗口的事件处理器。该处理器使用之前创建的s_cam
        对象作为参数，用于处理与三维交互相关的事件和操作。
        通过这个语句，创建了一个窗口对象 d_cam，并设置了窗口的边界和事件处理器，以便进行后续的窗口渲染和交互操作。
  */
  pangolin::View &d_cam = pangolin::CreateDisplay()
    .SetBounds(0.0, 1.0, 0.0, 1.0, -1024.0f / 768.0f)
    .SetHandler(new pangolin::Handler3D(s_cam));


  while (pangolin::ShouldQuit() == false) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    d_cam.Activate(s_cam);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glLineWidth(2);
    for (size_t i = 0; i < poses.size(); i++) {
      // 画每个位姿的三个坐标轴
      Vector3d Ow = poses[i].translation();
      Vector3d Xw = poses[i] * (0.1 * Vector3d(1, 0, 0));
      Vector3d Yw = poses[i] * (0.1 * Vector3d(0, 1, 0));
      Vector3d Zw = poses[i] * (0.1 * Vector3d(0, 0, 1));
      glBegin(GL_LINES);
      glColor3f(1.0, 0.0, 0.0);
      glVertex3d(Ow[0], Ow[1], Ow[2]);
      glVertex3d(Xw[0], Xw[1], Xw[2]);
      glColor3f(0.0, 1.0, 0.0);
      glVertex3d(Ow[0], Ow[1], Ow[2]);
      glVertex3d(Yw[0], Yw[1], Yw[2]);
      glColor3f(0.0, 0.0, 1.0);
      glVertex3d(Ow[0], Ow[1], Ow[2]);
      glVertex3d(Zw[0], Zw[1], Zw[2]);
      glEnd();
    }
    // 画出连线
    for (size_t i = 0; i < poses.size(); i++) {
      glColor3f(0.0, 0.0, 0.0);
      glBegin(GL_LINES);
      auto p1 = poses[i], p2 = poses[i + 1];
      glVertex3d(p1.translation()[0], p1.translation()[1], p1.translation()[2]);
      glVertex3d(p2.translation()[0], p2.translation()[1], p2.translation()[2]);
      glEnd();
    }
    pangolin::FinishFrame();
    usleep(5000);   // sleep 5 ms
  }
}