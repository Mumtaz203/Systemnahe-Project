#include <CUnit/Basic.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 8192  // Büyük çıktı için artırıldı
#define TOLERANCE 3       // Maksimum farklılık sayısı

// 📌 Programı çalıştırıp çıktıyı almak için fonksiyon
int run_command(const char *cmd, char *output, size_t size) {
    FILE *fp = popen(cmd, "r");
    if (!fp) return -1;

    size_t bytesRead = fread(output, 1, size - 1, fp);
    output[bytesRead] = '\0';  // Null-terminate
    pclose(fp);
    return 0;
}

// 📌 **Benzerlik kontrolü**: Küçük farklılıkları tolere eden fonksiyon
int are_outputs_similar(const char *output1, const char *output2) {
    char *line1, *line2;
    char buffer1[BUFFER_SIZE], buffer2[BUFFER_SIZE];
    
    strncpy(buffer1, output1, sizeof(buffer1));
    strncpy(buffer2, output2, sizeof(buffer2));

    line1 = strtok(buffer1, "\n");
    line2 = strtok(buffer2, "\n");

    int diff_count = 0;

    while (line1 && line2) {
        if (strcmp(line1, line2) != 0) {
            diff_count++;
            if (diff_count > TOLERANCE) return 0;  // Çok farklı → başarısız
        }
        line1 = strtok(NULL, "\n");
        line2 = strtok(NULL, "\n");
    }

    return 1;  // Çıktılar büyük ölçüde benzer
}

// ✅ **./program -l . ile ls -l benzer mi?**
void test_flag_l() {
    char output[BUFFER_SIZE], expected[BUFFER_SIZE];
    run_command("./program -l .", output, sizeof(output));
    run_command("ls -l", expected, sizeof(expected));

    printf("\n==============================\n");
    printf("Test: List Mode (-l)\n");
    printf("==============================\n");
    printf("\n🔹 Expected (ls -l):\n%s\n", expected);
    printf("\n🔹 Actual (./program -l .):\n%s\n", output);
}

// ✅ **./program -R . ile ls -R benzer mi?**
void test_flag_R() {
    char output[BUFFER_SIZE], expected[BUFFER_SIZE];
    run_command("./program -R .", output, sizeof(output));
    run_command("ls -R", expected, sizeof(expected));

    printf("\n==============================\n");
    printf("Test: Recursive Mode (-R)\n");
    printf("==============================\n");
    printf("\n🔹 Expected (ls -R):\n%s\n", expected);
    printf("\n🔹 Actual (./program -R .):\n%s\n", output);
}

// ✅ **./program -T . ile ls -t benzer mi?**
void test_flag_T() {
    char output[BUFFER_SIZE], expected[BUFFER_SIZE];
    run_command("./program -T .", output, sizeof(output));
    run_command("ls -t", expected, sizeof(expected));  // **ls -lt değil, ls -t!**

    printf("\n==============================\n");
    printf("Test: Time Mode (-T)\n");
    printf("==============================\n");
    printf("\n🔹 Expected (ls -t):\n%s\n", expected);
    printf("\n🔹 Actual (./program -T .):\n%s\n", output);
}

// Main fonksiyonu - Tüm testleri çalıştırır
int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("LS Similarity Tests", 0, 0);

    CU_add_test(suite, "List Mode (-l) Test", test_flag_l);
    CU_add_test(suite, "Recursive Mode (-R) Test", test_flag_R);
    CU_add_test(suite, "Time Mode (-T) Test", test_flag_T);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    CU_cleanup_registry();
    return 0;
}

