# VoiceFan_HAL 🎤🌀

基于 STM32F103C8T6 的语音控制智能风扇，支持 OLED 表情显示、舵机摇头、呼吸灯和电量检测。

## 📸 功能特性

| 功能 | 说明 |
|------|------|
| 🎤 **语音/串口控制** | 通过 USART1 接收指令，实现风扇调速、灯光控制、摇头开关 |
| 🔢 **三档风速** | 一档 (30%)、二档 (60%)、最大档 (100%)，支持正反转 |
| 🌀 **风扇摇头** | 舵机驱动左右扫风，角度范围 0°~120° |
| 😀 **OLED 表情** | 128×64 OLED 屏，7 种表情随状态变化（睡眠、瞪眼、开心、狂热等） |
| 💡 **呼吸灯** | 独立 LED 呼吸效果，可开关 |
| 🔋 **电量检测** | ADC 实时采集电池电压，支持 OLED 显示与充电状态判断 |

## 🛠 硬件平台

| 项目 | 规格 |
|------|------|
| **主控芯片** | STM32F103C8T6 (LQFP48) |
| **主频** | 72 MHz (HSE 8MHz + PLL ×9) |
| **开发环境** | Keil MDK-ARM V5.32 |
| **HAL 库** | STM32Cube FW_F1 V1.8.7 |
| **CubeMX** | 6.17.0 |

### 引脚分配

| 引脚 | 外设 | 功能 |
|------|------|------|
| PA0 | TIM2_CH1 | 电机 PWM 输出 |
| PA1 | GPIO | 电机方向控制 IN1 |
| PA2 | GPIO | 电机方向控制 IN2 |
| PA3 | ADC1_IN3 | 电池电压采集 |
| PA9 | USART1_TX | 语音模块串口发送 |
| PA10 | USART1_RX | 语音模块串口接收 |
| PB0 | TIM3_CH3 | LED 呼吸灯 PWM |
| PB1 | TIM3_CH4 | 舵机 PWM |
| PB8 | GPIO (模拟 I2C) | OLED SCL |
| PB9 | GPIO (模拟 I2C) | OLED SDA |
| PD0 | RCC_OSC_IN | 外部 8MHz 晶振 |
| PD1 | RCC_OSC_OUT | 外部 8MHz 晶振 |

## 📁 项目结构

```
VoiceFan_HAL/
├── Core/                   # 核心 HAL 配置层
│   ├── Inc/                # 头文件 (main, gpio, adc, tim, usart)
│   └── Src/                # CubeMX 自动生成的初始化代码
├── BSP/                    # 板级支持包
│   ├── Inc/                # BSP 模块头文件
│   │   ├── BSP.h           #   统一头文件
│   │   ├── Control.h       #   串口指令解析
│   │   ├── Motor.h         #   直流电机驱动
│   │   ├── Servo.h         #   舵机驱动
│   │   ├── PWM.h           #   PWM 输出管理
│   │   ├── OLED.h          #   OLED 显示驱动
│   │   ├── OLED_Data.h     #   字库与表情图片数据
│   │   ├── Face_Config.h   #   表情状态机
│   │   ├── OperatingMode.h #   运行模式切换
│   │   ├── LED_Breathing.h #   呼吸灯控制
│   │   ├── PowerDetection.h#   电量检测
│   │   ├── Delay.h         #   微秒/毫秒延时
│   │   ├── AD.h            #   ADC 采集
│   │   ├── Usart.h         #   串口收发
│   │   ├── BSP_Usart.h     #   BSP 层串口封装
│   │   └── Variable.h      #   全局变量定义
│   └── Src/                # BSP 模块实现
├── Drivers/                # STM32 Cube 驱动库
│   ├── CMSIS/              #   ARM Cortex-M 核心支持
│   └── STM32F1xx_HAL_Driver/# STM32F1 HAL 库
├── MDK-ARM/                # Keil uVision5 工程文件
│   ├── VoiceFan_HAL.uvprojx#   工程文件
│   ├── keilkill.bat        #   编译产物清理脚本
│   └── startup_stm32f103xb.s# 启动文件
└── VoiceFan_HAL.ioc        # STM32CubeMX 配置文件
```

## 📡 串口指令协议

通过 USART1 发送单字节指令，波特率由 CubeMX 配置：

| 指令 | 功能 | 表情 |
|:----:|------|:----:|
| `0x01` | 风扇一档 (30%) | 打招呼 |
| `0x02` | 风扇二档 (60%) | 瞪大眼 |
| `0x03` | 风扇最大档 (100%) | 快乐 |
| `0x04` | 关闭风扇 | 睡觉 |
| `0x05` | 开始摇头 | 狂热 |
| `0x06` | 停止摇头 | 非常快乐 |
| `0x07` | 开启灯光 | — |
| `0x08` | 关闭灯光 | — |
| `0x09` | 开启呼吸灯 | — |
| `0x10` | 关闭呼吸灯 | — |
| `0x11` | 切换电量显示 | — |

> 指令由外部语音识别模块（如 SU-03T、LD3320）通过串口发送，模块识别到语音关键词后输出对应 HEX 指令。

## 🚀 快速开始

### 前置条件

- **Keil MDK-ARM** V5.32 或更高版本
- STM32F1xx 设备支持包
- ST-Link / J-Link 调试器

### 编译与烧录

1. 克隆仓库
```bash
git clone https://github.com/ZZZ-pinking/VoiceFan_Hal.git
```

2. 使用 Keil MDK 打开工程
```
MDK-ARM/VoiceFan_HAL.uvprojx
```

3. 编译 (F7)，烧录 (F8)

4. 如需重新生成代码，用 STM32CubeMX 打开 `VoiceFan_HAL.ioc`，配置后生成代码

### 清理编译产物

```bash
cd MDK-ARM && keilkill.bat
```

## 🎛 控制逻辑

```
main()
  ├── BSP_Init()          # 初始化 OLED / 电机 / 舵机 / PWM / ADC / 串口
  ├── Face_Config()       # 根据 Face_Mode 显示对应表情 (主循环)
  └── OperatingMode()     # 根据 Fan_Speed / Fan_Swing 更新风速与摇头 (主循环)

TIM3 中断 (20ms)：
  ├── GetCur_Power()      # 采集电池电压
  ├── Servo_Update()      # 舵机角度更新
  └── LED_Breathing()     # 呼吸灯 PWM 更新

USART1 中断：
  └── HAL_UART_RxCpltCallback()  # 指令解析 → 更新 Fan_Speed / Face_Mode 等
```

## 📄 许可证

本项目使用 STMicroelectronics HAL 库，详见 [LICENSE](LICENSE) 文件。

---

*⚡ 基于江协科技 OLED 驱动库 & STM32CubeMX 生成代码构建*
