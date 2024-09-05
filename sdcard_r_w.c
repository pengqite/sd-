/*
 * @Descripttion:
 * @version:
 * @Author: zhangfan
 * @email: 2207044692@qq.com
 * @Date: 2024-09-05 10:42:42
 * @LastEditors: zhangfan
 * @LastEditTime: 2024-09-05 13:15:16
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
void write_to_sd(const char *sd_file_path, const char *file_path)
{
    // 打开文件以写模式（"w"），会覆盖文件内容
    FILE *file1 = fopen(sd_file_path, "ab");
    if (file1 == NULL)
    {
        printf("无法打开文件 %s 进行写入\n", sd_file_path);
        return;
    }

    FILE *file2 = fopen(file_path, "rb");
    if (file2 == NULL)
    {
        printf("无法打开文件 %s 进行写入\n", file_path);
        return;
    }

    // 获取文件大小
    fseek(file2, 0, SEEK_END);
    long file_size = ftell(file2);
    rewind(file2);

    // 分配内存读取文件内容
    unsigned char *buffer = (unsigned char *)malloc(file_size);
    fread(buffer, sizeof(unsigned char), file_size, file2);

    // 写入数据到文件
    // fprintf(file, "%s", data);
    // printf("成功写入到文件: %s\n", file_path);
    fwrite(buffer, sizeof(unsigned char), file_size, file1);

    free(buffer);
    fclose(file1);
    // 关闭文件
    fclose(file2);
}

void read_video_file(const char *file_path)
{
    FILE *file = fopen(file_path, "rb");
    if (file == NULL)
    {
        printf("无法打开文件 %s\n", file_path);
        return;
    }

    // 获取文件大小
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    // 分配内存读取文件内容
    unsigned char *buffer = (unsigned char *)malloc(file_size);
    fread(buffer, sizeof(unsigned char), file_size, file);

    printf("成功读取视频文件，大小: %ld 字节\n", file_size);

    free(buffer);
    fclose(file);
}

void read_from_sd(const char *file_path)
{
    // 打开文件以读模式（"r"）
    FILE *file = fopen(file_path, "r");
    if (file == NULL)
    {
        printf("无法打开文件 %s 进行读取\n", file_path);
        return;
    }

    // 读取文件内容并打印
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        printf("读取到的数据: %s\n", buffer);
    }

    // 关闭文件
    fclose(file);
}

int main()
{
    // 假设SD卡已经挂载到 /mnt/sdcard
    const char *sd_mount_point = "/mnt/sdcard";
    const char *file_name = "test.mp4";
    const char *video_path = "/home/root/test.mp4";
    char sd_file_path[256];

    // 构造文件路径
    snprintf(sd_file_path, sizeof(sd_file_path), "%s/%s", sd_mount_point, file_name);

    // 写入数据到SD卡上的文件
    //  read_video_file(video_path);
    write_to_sd(sd_file_path, video_path);

    // 从SD卡上的文件读取数据
    // read_from_sd(file_path);

    return 0;
}
