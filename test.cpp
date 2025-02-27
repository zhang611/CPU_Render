#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // 测试 OpenCV 版本
    std::cout << "OpenCV version: " << CV_VERSION << std::endl;

    // 读取图片
    cv::Mat image = cv::imread("E:/Job/project/CPU_Render/test.png"); // 确保 test.jpg 文件存在
    if (image.empty()) {
        std::cerr << "Error: Could not open or find the image!" << std::endl;
        return -1;
    }

    // 显示图片
    cv::imshow("Original Image", image);

    // 转换为灰度图
    cv::Mat grayImage;
    cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY);

    // 显示灰度图
    cv::imshow("Gray Image", grayImage);

    // 保存灰度图
    cv::imwrite("gray_test.jpg", grayImage);

    // 等待按键后关闭窗口
    cv::waitKey(0);
    cv::destroyAllWindows();

    std::cout << "Test completed successfully!" << std::endl;

    return 0;
}