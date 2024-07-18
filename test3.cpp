#include <iostream>
#include <memory>

// 定义 Logger 接口
class Logger
{
public:
  virtual ~Logger() = default;
  virtual void log(const std::string& message) = 0;
};

// 实现 ConsoleLogger 类
class ConsoleLogger : public Logger
{
public:
  void log(const std::string& message) override
  {
    std::cout << message << std::endl;
  }
};

// 服务类依赖于 Logger 接口
class UserService
{
private:
  std::shared_ptr<Logger> logger;

public:
  UserService(std::shared_ptr<Logger> logger) : logger(logger) {}

  void performTask() { logger->log("Performing a task"); }
};

// 使用依赖注入创建 UserService 实例
int main()
{
  auto logger = std::make_shared<ConsoleLogger>();
  UserService userService(std::move(logger));

  userService.performTask();  // 控制台输出：Performing a task

  return 0;
}
