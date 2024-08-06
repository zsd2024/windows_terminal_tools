#include <windows.h>
#include <conio.h>
namespace things
{
    namespace windows_terminal_tools
    {
        enum color_codes
        {
            unknown = -1,
            black = 0,
            blue = 1,
            green = 2,
            cyan = 3,
            red = 4,
            magenta = 5,
            yellow = 6,
            white = 7,
            bright_black = 8,
            bright_blue = 9,
            bright_green = 10,
            bright_cyan = 11,
            bright_red = 12,
            bright_magenta = 13,
            bright_yellow = 14,
            bright_white = 15
        };
        struct console_color
        {
            color_codes froncolor = unknown;
            color_codes backcolor = unknown;
            console_color(color_codes f = unknown, color_codes b = unknown)
            {
                froncolor = f;
                backcolor = b;
            }
        };
        /// @brief 设置光标位置
        /// @param x 第几列
        /// @param y 第几行
        /// @return 是否设置成功
        WINBOOL set_cursor_position(SHORT x, SHORT y)
        {
            COORD coord = {x, y};                                                    // 定义坐标
            return SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); // 设置光标位置，失败则返回
        }
        /// @brief 获取光标位置
        /// @param x 存储第几列的变量
        /// @param y 存储第几行的变量
        /// @return 是否获取成功
        WINBOOL get_cursor_position(SHORT &x, SHORT &y)
        {
            CONSOLE_SCREEN_BUFFER_INFO info;                                         // 定义结构体
            if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info)) // 获取屏幕信息，失败则返回
                return false;                                                        // 失败则返回
            x = info.dwCursorPosition.X;                                             // 获取光标列位置
            y = info.dwCursorPosition.Y;                                             // 获取光标行位置
            return true;                                                             // 成功则返回
        }
        /// @brief 获取控制台大小
        /// @param width 存储宽度的变量
        /// @param height 存储高度的变量
        /// @return 是否获取成功
        WINBOOL get_console_size(SHORT &width, SHORT &height)
        {
            CONSOLE_SCREEN_BUFFER_INFO info;                                         // 定义结构体
            if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info)) // 获取屏幕信息，失败则返回
                return false;                                                        // 失败则返回
            width = info.srWindow.Right - info.srWindow.Left + 1;                    // 获取宽度
            height = info.srWindow.Bottom - info.srWindow.Top + 1;                   // 获取高度
            return true;                                                             // 成功则返回
        }
        /// @brief 清空控制台
        /// @note 该函数会清空控制台，并将光标移动到左上角
        /// @return 是否清空成功
        WINBOOL clear_console()
        {
            set_cursor_position(0, 0);                                                                                 // 移动光标到左上角
            SHORT width, height;                                                                                       // 存储控制台大小
            if (!get_console_size(width, height))                                                                      // 获取控制台大小，失败则返回
                return false;                                                                                          // 失败则返回
            char *buffer = new char[width * height];                                                                   // 申请一块内存
            memset(buffer, ' ', width * height);                                                                       // 用空格填充内存
            COORD coord = {0, 0};                                                                                      // 定义坐标
            DWORD count;                                                                                               // 定义计数器
            if (!WriteConsoleOutputCharacterA(GetStdHandle(STD_OUTPUT_HANDLE), buffer, width * height, coord, &count)) // 输出到控制台，失败则返回
                return false;                                                                                          // 失败则返回
            delete[] buffer;                                                                                           // 释放内存
            return true;                                                                                               // 成功则返回
        }
        /// @brief 输出字符串
        /// @param str 要输出的字符串
        /// @return 是否输出成功
        WINBOOL output_string(const char *str)
        {
            DWORD count;                                                                           // 定义计数器
            return WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), str, strlen(str), &count, NULL); // 输出到控制台
        }
        /// @brief 获取颜色
        /// @param froncolor 存储前景色的变量
        /// @param backcolor 存储背景色的变量
        /// @return 是否获取成功
        WINBOOL get_color(color_codes &froncolor, color_codes &backcolor)
        {
            CONSOLE_SCREEN_BUFFER_INFO info;                                         // 定义结构体
            if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info)) // 获取屏幕信息，失败则返回
                return false;                                                        // 失败则返回
            froncolor = (color_codes)(info.wAttributes & 0x000F);                    // 获取前景色
            backcolor = (color_codes)((info.wAttributes & 0x00F0) >> 4);             // 获取背景色
            return true;                                                             // 成功则返回
        }
        /// @brief 获取颜色
        /// @param color 存储颜色的变量
        /// @return 是否获取成功
        WINBOOL get_color(console_color &color)
        {
            color_codes froncolor, backcolor;
            if (!get_color(froncolor, backcolor))
                return false;
            color.froncolor = froncolor;
            color.backcolor = backcolor;
            return true;
        }
        /// @brief 设置颜色
        /// @param froncolor 前景色
        /// @param backcolor 背景色
        /// @return 是否设置成功
        WINBOOL set_color(color_codes froncolor = unknown, color_codes backcolor = unknown)
        {
            if (froncolor == unknown || backcolor == unknown)
            {
                console_color color;
                set_color(froncolor == unknown ? color.froncolor : froncolor, backcolor == unknown ? color.backcolor : backcolor);
            }
            return SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)((int)backcolor << 4 | (int)froncolor)); // 设置颜色
        }
        /// @brief 设置颜色
        /// @param color 颜色
        /// @return 是否设置成功
        WINBOOL set_color(console_color color)
        {
            return set_color(color.froncolor, color.backcolor);
        }
        /// @brief 隐藏光标
        /// @return 是否隐藏成功
        WINBOOL hide_cursor()
        {
            CONSOLE_CURSOR_INFO info = {1, 0};                                   // 定义光标信息
            return SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info); // 隐藏光标
        }
        /// @brief 显示光标
        /// @return 是否显示成功
        WINBOOL show_cursor()
        {
            CONSOLE_CURSOR_INFO info = {1, 1};                                   // 定义光标信息
            return SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info); // 显示光标
        }
        /// @brief 关闭快速编辑模式
        /// @return 是否关闭成功
        WINBOOL disable_quick_edit_mode()
        {
            DWORD mode;
            if (!GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), &mode))  // 获取输入模式，失败则返回
                return false;                                            // 失败则返回
            mode &= ~ENABLE_QUICK_EDIT_MODE;                             // 关闭快速编辑模式
            return SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), mode); // 设置输入模式，失败则返回
        }
        /// @brief 开启快速编辑模式
        /// @return 是否开启成功
        WINBOOL enable_quick_edit_mode()
        {
            DWORD mode;
            if (!GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), &mode))  // 获取输入模式，失败则返回
                return false;                                            // 失败则返回
            mode |= ENABLE_QUICK_EDIT_MODE;                              // 开启快速编辑模式
            return SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), mode); // 设置输入模式，失败则返回
        }
        /// @brief 关闭插入模式
        /// @return 是否关闭成功
        WINBOOL disable_insert_mode()
        {
            DWORD mode;
            if (!GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), &mode))  // 获取输入模式，失败则返回
                return false;                                            // 失败则返回
            mode &= ~ENABLE_INSERT_MODE;                                 // 关闭插入模式
            return SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), mode); // 设置输入模式，失败则返回
        }
        /// @brief 开启插入模式
        /// @return 是否开启成功
        WINBOOL enable_insert_mode()
        {
            DWORD mode;
            if (!GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), &mode))  // 获取输入模式，失败则返回
                return false;                                            // 失败则返回
            mode |= ENABLE_INSERT_MODE;                                  // 开启插入模式
            return SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), mode); // 设置输入模式，失败则返回
        }
        /// @brief 添加鼠标输入模式
        /// @return 是否添加成功
        WINBOOL add_mouse_input_mode()
        {
            DWORD mode;
            if (!GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), &mode))  // 获取输入模式，失败则返回
                return false;                                            // 失败则返回
            mode |= ENABLE_MOUSE_INPUT;                                  // 添加鼠标输入模式
            return SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), mode); // 设置输入模式，失败则返回
        }
        /// @brief 移除鼠标输入模式
        /// @return 是否移除成功
        WINBOOL remove_mouse_input_mode()
        {
            DWORD mode;
            if (!GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), &mode))  // 获取输入模式，失败则返回
                return false;                                            // 失败则返回
            mode &= ~ENABLE_MOUSE_INPUT;                                 // 移除鼠标输入模式
            return SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), mode); // 设置输入模式，失败则返回
        }
    }
}