#include <CUnit/Basic.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 8192  // Büyük çıktı için artırıldı

// 📌 Programı çalıştırıp çıktıyı almak için fonksiyon
int run_command(const char *cmd, char *output, size_t size) {
    FILE *fp = popen(cmd, "r");
    if (!fp) return -1;

    size_t bytesRead = fread(output, 1, size - 1, fp);
    output[bytesRead] = '\0';  // Null-terminate
    pclose(fp);
    return 0;
}

// ✅ **./program -t . ile ls -t benzer mi?**
void test_flag_t() {
    char output[BUFFER_SIZE], expected[BUFFER_SIZE];
     run_command("ls -t --format=horizontal", expected, sizeof(expected));
    run_command("./program -t .", output, sizeof(output));  

    printf("\n==============================\n");
    printf("Test: Time Mode (-t)\n");
    printf("==============================\n");
    printf("\n\U0001F539 Expected (ls -t):\n%s\n", expected);
    printf("\n\U0001F539 Actual (./program -t .):\n%s\n", output);
}

// ✅ **./program -l . ile ls -l benzer mi?**
void test_flag_l() {
    char output[BUFFER_SIZE], expected[BUFFER_SIZE];
    run_command("ls -l", expected, sizeof(expected));
    run_command("./program -l .", output, sizeof(output));

    printf("\n==============================\n");
    printf("Test: List Mode (-l)\n");
    printf("==============================\n");
    printf("\n\U0001F539 Expected (ls -l):\n%s\n", expected);
    printf("\n\U0001F539 Actual (./program -l .):\n%s\n", output);
}

// ✅ **./program -R . ile ls -R benzer mi?**
void test_flag_R() {
    char output[BUFFER_SIZE], expected[BUFFER_SIZE];

    // 📌 `ls -R` çıktısını tam olarak sistemde nasıl görünüyorsa o şekilde alıyoruz.
    run_command("ls -R --format=horizontal", expected, sizeof(expected));
    run_command("./program -R .", output, sizeof(output));

    printf("\n==============================\n");
    printf("Test: Recursive Mode (-R)\n");
    printf("==============================\n");
    printf("\n\U0001F539 Expected (ls -R):\n%s\n", expected);
    printf("\n\U0001F539 Actual (./program -R .):\n%s\n", output);
}

// 📌 **Main fonksiyonu - Tüm testleri çalıştırır**
int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("LS Similarity Tests", 0, 0);

    CU_add_test(suite, "List Mode (-l) Test", test_flag_l);
    CU_add_test(suite, "Recursive Mode (-R) Test", test_flag_R);
    CU_add_test(suite, "Time Mode (-t) Test", test_flag_t);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    CU_cleanup_registry();
    return 0;
}

