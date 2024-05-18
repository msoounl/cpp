#include <iostream>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd = open("myfile", O_RDONLY);
    off_t ret = lseek(fd, 0, SEEK_END);
    std::cout << ret << std::endl;

    off_t ret2 = lseek(fd, 0, SEEK_CUR);
    std::cout << ret2 << std::endl;

    return 0;
}
