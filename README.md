# windows_terminal_tools C++ 头文件

一些Windows控制台的函数

## 函数列表

### 设置光标位置

```cpp
WINBOOL set_cursor_position(SHORT x, SHORT y);
```

- **描述**: 设置光标位置。
- **参数**:
  - `x`: 第几列。
  - `y`: 第几行。
- **返回值**: 是否设置成功。

### 获取光标位置

```cpp
WINBOOL get_cursor_position(SHORT &x, SHORT &y);
```

- **描述**: 获取光标位置。
- **参数**:
  - `x`: 存储第几列的变量。
  - `y`: 存储第几行的变量。
- **返回值**: 是否获取成功。

### 获取控制台大小

```cpp
WINBOOL get_console_size(SHORT &width, SHORT &height);
```

- **描述**: 获取控制台大小。
- **参数**:
  - `width`: 存储宽度的变量。
  - `height`: 存储高度的变量。
- **返回值**: 是否获取成功。

### 清空控制台

```cpp
WINBOOL clear_console();
```

- **描述**: 清空控制台，并将光标移动到左上角。
- **返回值**: 是否清空成功。

### 输出字符串

```cpp
WINBOOL output_string(const char *str);
```

- **描述**: 输出字符串。
- **参数**:
  - `str`: 要输出的字符串。
- **返回值**: 是否输出成功。

### 设置颜色

```cpp
WINBOOL set_color(color_codes froncolor = white, color_codes backcolor = black);
```

- **描述**: 设置颜色。
- **参数**:
  - `froncolor`: 前景色，默认为白色。
  - `backcolor`: 背景色，默认为黑色。
- **返回值**: 是否设置成功。

### 隐藏光标

```cpp
WINBOOL hide_cursor();
```

- **描述**: 隐藏光标。
- **返回值**: 是否隐藏成功。

### 显示光标

```cpp
WINBOOL show_cursor();
```

- **描述**: 显示光标。
- **返回值**: 是否显示成功。

### 关闭快速编辑模式

```cpp
WINBOOL disable_quick_edit_mode();
```

- **描述**: 关闭快速编辑模式。
- **返回值**: 是否关闭成功。

### 开启快速编辑模式

```cpp
WINBOOL enable_quick_edit_mode();
```

- **描述**: 开启快速编辑模式。
- **返回值**: 是否开启成功。

### 关闭插入模式

```cpp
WINBOOL disable_insert_mode();
```

- **描述**: 关闭插入模式。
- **返回值**: 是否关闭成功。

### 开启插入模式

```cpp
WINBOOL enable_insert_mode();
```

- **描述**: 开启插入模式。
- **返回值**: 是否开启成功。

### 添加鼠标输入模式

```cpp
WINBOOL add_mouse_input_mode();
```

- **描述**: 添加鼠标输入模式。
- **返回值**: 是否添加成功。

### 移除鼠标输入模式

```cpp
WINBOOL remove_mouse_input_mode();
```

- **描述**: 移除鼠标输入模式。
- **返回值**: 是否移除成功。
