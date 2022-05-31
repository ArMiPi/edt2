#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"strings.h"

String newEmptyString(int size) {
    String str = (String) malloc((size + 1) * sizeof(char));
    if(str == NULL) {
        printf("ERROR: Could not allocate memory for string\n");
        exit(EXIT_FAILURE);
    }

    return str;
}

String copyString(String str) {
    if(str == NULL) return NULL;

    String strf = newEmptyString(strlen(str));
    sprintf(strf, "%s", str);

    return strf;
}

String concat(String str1, String str2) {
    String str = newEmptyString(strlen(str1) + strlen(str2));
    sprintf(str, "%s%s", str1, str2);
    
    return str;
}

String slice(String str, int start, int end) {
    if(str == NULL) return NULL;

    int size = end - (start - 1) + 1;
    String sliced_str = newEmptyString(size);

    int j = 0;
    for(int i = start; i <= end; i++, j++) {
        sliced_str[j] = str[i];
    }
    sliced_str[j] = '\0';

    return sliced_str;
}

bool startsWith(String str1, String str2) {
    if(str1 == NULL || str2 == NULL) return false;

    int size1 = strlen(str1);
    int size2 = strlen(str2);

    if(size1 < size2) return false;

    for(int i = 0; i < size2; i++) {
        if(str1[i] != str2[i]) return false;
    }

    return true;
}

bool endsWith(String str1, String str2) {
    if(str1 == NULL || str2 == NULL) return false;

    int size1 = strlen(str1);
    int size2 = strlen(str2);

    if(size1 < size2) return false;

    for(int i = size1 - size2, j = 0; i < size1; i++, j++) {
        if(str1[i] != str2[j]) return false;
    }

    return true;
}

int contains(String str1, String str2) {
    if(str1 == NULL || str2 == NULL) return -1;

    if(strlen(str2) == 0) return 0;

    int size1 = strlen(str1);
    int size2 = strlen(str2);

    if(size1 < size2) return -1;

    for(int i = 0, j = 0; i < size1; i++) {
        if(j != 0 && (str1[i] != str2[j])) j = 0;

        if(str1[i] == str2[j]) j++;

        if(j == size2) return i - j + 1;
    }

    return -1;
}

/*
    # Entradas:
        - origin: String base
        - target: String procurada
    
    # Saída:
        - int
    
    # Descrição:
        - Retorna o número de vezes que target é encontrado em origin

        - origin != NULL && target != NULL && target != ""
*/
int ocurrenciesNumber(String origin, String target) {
    if(origin == NULL || target == NULL || strcmp(target, "") == 0) return 0;

    // Numero de ocorrências
    int ocurrencies = 0;
    
    // Tamanho de origin
    int originSize = strlen(origin);

    // Tamanho de target
    int targetSize = strlen(target);
    
    // Percorrer origin em busca de target
    for(int i = 0, j = 0; i < originSize; i++) {
        if(origin[i] != target[j]) {
            if(j != 0) j = 0;
            continue;
        }
        if(i + (targetSize - j) > originSize) break;

        j++;
        if(j == targetSize) {
            ocurrencies++;
            j = 0;
        }
    }

    return ocurrencies;
}

String *split(String origin, String separator) {
    // Verificar as entradas
    if(origin == NULL) return NULL;
    int flag = 0;
    if(separator == NULL) {
        separator = copyString(" ");
        flag = 1;
    }
    if(strcmp(separator, "") == 0) return NULL;

    // Definir tamanho do vetor a ser retornado
    int size = ocurrenciesNumber(origin, separator) + 2;
    
    // Alocar vetor de retorno
    String *splited = (String *) malloc(size * sizeof(String));
    if(splited == NULL) {
        printf("ERROR: Could not allocate memory for split() return\n");
        exit(EXIT_FAILURE);
    }

    String helper = origin;
    // Armazenar as substrings no vetor de saída
    for(int i = 0, increment = 0; i < size - 1; i++) {
        splited[i] = copyUntil(helper, separator);
        increment = contains(helper, separator);
        helper += increment + strlen(separator);
    }
    splited[size - 1] = NULL;

    // Retorno
    if(flag) free(separator);
    return splited;
}

String join(int num_strings, String *strings, String joiner) {
    if(strings == NULL || joiner == NULL) return NULL;

    int size = 0;

    for(int i = 0; i < num_strings; i++)
        size += strlen(strings[i]) + strlen(joiner);
    
    String final_string = newEmptyString(size);
    final_string[0] = '\0';

    for(int i = 0; i < num_strings - 1; i++)
    {
        strcat(final_string, strings[i]);
        strcat(final_string, joiner);
    }
    strcat(final_string, strings[num_strings-1]);

    return final_string;
}

String copyUntil(String origin, String limit) {
    if(origin == NULL || limit == NULL) return NULL;
    if(strlen(limit) == 0) return NULL;

    String copy;

    int copySize = contains(origin, limit);

    if(copySize == -1) return copyString(origin);

    copy = newEmptyString(copySize);
    for(int i = 0; i < copySize; i++) copy[i] = origin[i];
    copy[copySize] = '\0';

    return copy;
}
