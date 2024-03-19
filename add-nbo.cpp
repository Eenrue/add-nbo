#include <stdio.h>
#include <stdint.h>

uint32_t my_ntohl(uint32_t n){
    return ((n&0xFF)<<24)|((n&0xFF00)<<8)|((n&0xFF0000)>>8)|((n>>24)&0xFF);
}

int main(int argc, char *argv[]){
    FILE *file1=fopen(argv[1],"rb");
    FILE *file2=fopen(argv[2],"rb");
    if(file1==NULL||file2==NULL){
	printf("Can't open files!\n");
        return 1;
    }
    uint32_t num1, num2;

    if (fread(&num1, sizeof(uint32_t), 1, file1) != 1) {
        printf("Error reading from file: %s\n", argv[1]);
        fclose(file1);
        fclose(file2);
        return 1;
    }
    num1 = my_ntohl(num1);

    if(fread(&num2, sizeof(uint32_t), 1, file2) != 1) {
        printf("Error reading from file: %s\n", argv[2]);
        fclose(file1);
        fclose(file2);
        return 1;
    }
    num2 = my_ntohl(num2);

    fclose(file1);
    fclose(file2);

    // Print sum
    printf("%u(0x%x) + %u(0x%x) = %u(0x%x)\n", num1, num1, num2, num2, num1 + num2, num1 + num2);

    return 0;


}
