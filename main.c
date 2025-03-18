#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    uint32_t* tmp = (uint32_t *)malloc(sizeof(uint32_t) * argc);
    FILE *fp;
    uint32_t sum = 0;

    for(int i = 1; i < argc; i++) {
        fp = fopen(argv[i], "rb");
        if(fp == NULL) {
            perror("fopen");
            free(tmp);
            return 1;
        }

        fseek(fp, 0, SEEK_END);
        if(ftell(fp) != sizeof(uint32_t)) {
            fprintf(stderr, "file size is not %ld\n", sizeof(uint32_t));
            free(tmp);
            fclose(fp);
            return 1;
        }
        fseek(fp, 0, SEEK_SET);
        
        uint32_t num;
        if(fread(&num, sizeof(uint32_t), 1, fp) == 1) {
            num = ntohl(num);
            tmp[i-1] = num;
            sum += num;
        } else {
            perror("fread");
            free(tmp);
            fclose(fp);
            return 1;
        }
        fclose(fp);
    }

    for(int i = 0; i < argc-1; i++) {
        printf("%d(0x%x)", tmp[i], tmp[i]);
        if(i != argc - 2) {
            printf(" + ");
        }
        else {
            printf(" = %d(0x%x)", sum, sum);
        }
    }

    free(tmp);
    return 0;
}
