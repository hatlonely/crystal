#include <iostream>
#include <string>

#define 整型 int
#define 常量 const
#define 字符 char
#define 返回 return
#define 私有 private
#define 共有 public
#define 保护 protected
#define 类 class
#define 空 void
#define 我 this
#define 虚 virtual
#define 调用 .
#define 指针 *
#define 输出 <<
#define 的 ->
#define 是 =
#define 继承 :
#define 主函数 main
#define 字符串 std::string
#define 屏幕 std::cout
#define 换行 std::endl

类 动物 {
共有:
    动物(字符串 名字) {
        我 的 名字 是 名字;
    }
    虚 空 自我介绍() {
        屏幕 输出 "我的名字叫" 输出 名字 输出 换行;
    }
保护:
    字符串 种类;
    字符串 名字;
};

类 狗 继承 动物 {
共有:
    狗(字符串 名字) : 动物(名字) {
        我 的 种类 是 "狗";
    }
    空 自我介绍() {
        屏幕 输出 "我是一只" 输出 种类 输出 "，我的名字叫" 输出 名字 输出 换行;
    }
};

整型 主函数(整型 参数个数, 常量 字符 指针 参数列表[]) {
    狗 麻吉 是 狗("麻吉");
    麻吉 调用 自我介绍();
    返回 0;
}

