#include "ArmorDetect.h"

//无参构造函数
ArmorNumclassifier::ArmorNumclassifier()
{
    svm = ml::SVM::create();	// 构造SVM参数模型
    armorImageSize = Size(40, 40);	// SVM模型识别图像大小（通过透视变换实现）
    p = Mat();		// 模型识别矩阵

    warpPerspective_mat = Mat(3, 3, CV_32FC1);		// 3 * 3 透视变换的变换矩阵
    // 透视变换后的目标点
    dstPoints[0] = Point2f(0, 0);
    dstPoints[1] = Point2f(armorImageSize.width, 0);
    dstPoints[2] = Point2f(armorImageSize.width, armorImageSize.height);
    dstPoints[3] = Point2f(0, armorImageSize.height);
}

//析构函数
ArmorNumclassifier::~ArmorNumclassifier(){}

//载入SVM模型（识别装甲板数字）
void ArmorNumclassifier::loadSvmModel(const char* model_path,Size armorImageSize)
{
    // 载入模型
    svm = StatModel::load<SVM>(model_path);
    if (svm.empty())
    {
        cout << "Svm load error! Please check the path!" << endl;
        exit(0);
    }
    this->armorImageSize = armorImageSize;

    // 设置dstPoints
    dstPoints[0] = Point2f(0, 0);
    dstPoints[1] = Point2f(armorImageSize.width, 0);
    dstPoints[2] = Point2f(armorImageSize.width, armorImageSize.height);
    dstPoints[3] = Point2f(0, armorImageSize.height);
}

//对图像进行处理:将图像二值化，将数字凸显出来
void ArmorNumclassifier::LoadImage(Mat & src)
{
    // 复制图像副本
    (src).copyTo(warpPerspective_src);

    // 预处理图像
    cvtColor(warpPerspective_src, warpPerspective_src, COLOR_BGR2GRAY);
    threshold(warpPerspective_src, warpPerspective_src, armorParam.bright_threshold, 255, THRESH_BINARY);

}

//利用投射变换得到装甲板图片
void ArmorNumclassifier::getArmorImage(ArmorBox & armor)
{
    // 获取原始装甲板图片上的四个顶点（透视变换初始图片的目标点）
    for (int i = 0; i < 4; i++)
        srcPoints[i] = armor.armorVertices[i];

    // 使用透视变换获取装甲板图片
    /*
        * GetPerspectiveTransform()由四对点计算透视变换矩阵
        * Param: src 输入图像的四边形顶点坐标  dst 输出图像的相应四边形顶点坐标
    */
    warpPerspective_mat = getPerspectiveTransform(srcPoints, dstPoints);  // 定义 3 * 3 透射变换矩阵
    /*
        * warpPerspective()对图像进行透视变换
        * Param: src 输入图像  dst 输出图像  M 3*3的透视变换矩阵  dsize 图像尺寸大小
        *		 flags 输出图像的插值方法  borderMode 图像边界的处理方法  Scalar& borderValue 图像边界颜色设置，一般设置为0
    */
    warpPerspective(warpPerspective_src, warpPerspective_dst, warpPerspective_mat, armorImageSize, INTER_NEAREST, BORDER_CONSTANT, Scalar(0));
    warpPerspective_dst.copyTo(armor.armorImg); // 复制到透射变换后的装甲板图片


    //DeBug用
    //imshow("armorImg",armor.armorImg);
}

//利用SVM实现装甲板数字识别
void ArmorNumclassifier::setArmorNum(ArmorBox & armor)
{
    // 处理armorImg，使armorImg适应SVM模型样本大小的要求
    // p为模型识别矩阵
    /*
        * reshape()既可以改变矩阵的通道数，又可以对矩阵元素进行序列化
        * Param: cn 表示图像通道数（channels），如果设置为0，表示通道数不变
        *		 rows 表示矩阵行数，如果设置为0，表示矩阵行数不变
    */
    p = armor.armorImg.reshape(1, 1);	// 将图像转变为单通道，单行的矩阵
    /*
        * convertTo()缩放并转换到另外一种数据类型
        * Param: dst 目标矩阵  type 需要的输出矩阵类型
    */
    p.convertTo(p, CV_32FC1);	// 将图像类型转变为CV_32FC1

    // 将SVM模型识别到的数字记录到armorNum参数中
    armor.armorNum = (int)svm->predict(p);

    //DeBug用
    //cout<<armor.armorNum<<endl;
}