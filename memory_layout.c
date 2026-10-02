#include <stdio.h>
#include <stdlib.h>

/* 1. DATA SEGMENT: Initialized global / static variables (non-zero value) */
int g_data_var = 100;
static int s_data_var = 200;

/* 2. BSS SEGMENT: Uninitialized global / static variables or initialized to 0 */
int g_bss_var;              /* Uninitialized -> defaults to 0 */
static int s_bss_zero = 0;  /* Initialized to 0 -> stored in BSS */

/* Dummy function to get address in TEXT SEGMENT */
void sample_function(void) {
    /* Do nothing, only used to obtain function address */
}

void demo_memory_layout(void) {
    /* 1. TEXT / RODATA: String literal constant (Read-Only Data) */
    const char *str_literal = "Hello Memory Layout";

    /* 4. HEAP SEGMENT: Dynamic memory allocation */
    int *heap_var1 = (int *)malloc(sizeof(int));
    int *heap_var2 = (int *)malloc(sizeof(int));

    /* 5. STACK SEGMENT: Local variables inside function */
    int stack_var1 = 10;
    int stack_var2 = 20;

    printf("\n====================================================================\n");
    printf("                  C MEMORY LAYOUT PRACTICAL DEMO                    \n");
    printf("====================================================================\n");
    printf("%-20s | %-22s | %-18s\n", "MEMORY SEGMENT", "VARIABLE / OBJECT", "MEMORY ADDRESS (%p)");
    printf("--------------------------------------------------------------------\n");

    /* Print STACK segment addresses */
    printf("%-20s | %-22s | %p\n", "STACK", "stack_var1 (local)", (void *)&stack_var1);
    printf("%-20s | %-22s | %p\n", "STACK", "stack_var2 (local)", (void *)&stack_var2);
    printf("%-20s | %-22s | %p\n", "STACK", "heap_var1 pointer", (void *)&heap_var1);

    printf("--------------------------------------------------------------------\n");
    /* Print HEAP segment addresses */
    printf("%-20s | %-22s | %p\n", "HEAP", "*heap_var2 (malloc)", (void *)heap_var2);
    printf("%-20s | %-22s | %p\n", "HEAP", "*heap_var1 (malloc)", (void *)heap_var1);

    printf("--------------------------------------------------------------------\n");
    /* Print BSS segment addresses */
    printf("%-20s | %-22s | %p\n", "BSS", "s_bss_zero (static=0)", (void *)&s_bss_zero);
    printf("%-20s | %-22s | %p\n", "BSS", "g_bss_var (uninit)", (void *)&g_bss_var);

    printf("--------------------------------------------------------------------\n");
    /* Print DATA segment addresses */
    printf("%-20s | %-22s | %p\n", "DATA", "s_data_var (static!=0)", (void *)&s_data_var);
    printf("%-20s | %-22s | %p\n", "DATA", "g_data_var (global!=0)", (void *)&g_data_var);

    printf("--------------------------------------------------------------------\n");
    /* Print TEXT / RODATA segment addresses */
    printf("%-20s | %-22s | %p\n", "TEXT (ROData)", "str_literal string", (void *)str_literal);
    printf("%-20s | %-22s | %p\n", "TEXT (Code)", "sample_function()", (void *)&sample_function);
    printf("%-20s | %-22s | %p\n", "TEXT (Code)", "main() function", (void *)&demo_memory_layout);
    printf("====================================================================\n\n");

    /* Free Heap memory */
    free(heap_var1);
    free(heap_var2);
}

int main(void) {
    demo_memory_layout();
    return 0;
}