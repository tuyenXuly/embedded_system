#include "print_cli.h"
#include "main.h"
#include "stdarg.h"
#include "stdio.h"
extern UART_HandleTypeDef huart1;

//void print_cli(const char* str, ...)
//{
//  char stringArray[128];
//
//	va_list args;
//	va_start(args,str);
//	uint8_t len_str = vsprintf(stringArray,str,args);
//	va_end(args);
//
//	HAL_UART_Transmit(&huart1,(uint8_t *)stringArray,len_str,200);
//}

void print_cli(const char* format, ...)
{
    // Tăng kích thước bộ đệm nếu cần xử lý chuỗi lớn hơn
    char buffer[256];

    va_list args;
    va_start(args, format);

    // Sử dụng vsnprintf để đảm bảo an toàn bộ đệm
    int len = vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    if (len > 0) {
        // Nếu chuỗi dài hơn bộ đệm, chỉ gửi phần vừa bộ đệm
        if (len >= sizeof(buffer)) {
            len = sizeof(buffer) - 1;
        }
        HAL_UART_Transmit(&huart1, (uint8_t*)buffer, len, HAL_MAX_DELAY);
    }
}
