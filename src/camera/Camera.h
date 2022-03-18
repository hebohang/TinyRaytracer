#include <Eigen/Dense>
#include <numbers>

// 光追的摄像机
// 需要 FOV 和 摄像机朝向（相当于屏幕的法线了）
class Camera
{
public:
    Camera() = default;
    [[nodiscard]] const auto  GetFov() const { return fov; }
    [[nodiscard]] const auto& GetPos() const { return pos; }
    [[nodiscard]] const auto& GetOrientation() const { return normal; }

private:
    Eigen::Vector3f pos{ 0.0f, 0.0f, 0.0f };
    Eigen::Vector3f normal{ 0.0f, 0.0f, -1.0f };
    double fov = std::numbers::pi / 2.;
};