/**
    \file       example_1.c
    \author     Eremin Dmitry (http://github.com/NeonMercury)
    \date       October, 2015
    \brief      Loading *.json file into the application and tokenizing it.
*/

#include "jfes.h"
#include "examples.h"
/* For malloc and free functions. You can use your own memory functions. */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

/** Example 1 entry point. */
int example_1_entry(int argc, char **argv) {
    unsigned long buffer_size = 2048;
    char *json_data = malloc(buffer_size * sizeof(char));

    if (!get_file_content("example_1.json", json_data, &buffer_size)) {
        
        return -1;
    }

    for(uint32_t i = 0; i < buffer_size; i++)
    {
        if(!strncmp(json_data + i, "\"temp_min\"", strlen("\"temp_min\"")))
        {   
            char *tmp_min;
            strtok(json_data + i, ":");
            tmp_min = strtok(NULL, ",");
            printf("%s\r\n", tmp_min);
        }
        if(!strncmp(json_data + i, "\"temp_max\"", strlen("\"temp_max\"")))
        {   
            char *tmp_max;
            strtok(json_data + i, ":");
            tmp_max = strtok(NULL, ",");
            printf("%s\r\n", tmp_max);
            // printf("start parsing\r\n");
            // for(uint32_t j = i + strlen("\"company\": "); j < buffer_size; j++)
            // {
            //     if(json_data[j] == ',')
            //     {
            //         printf("\r\n");
            //         break;
            //     }
            //     printf("%c", json_data[j]);
            // }
        }
    }

    jfes_parser_t parser;
    jfes_token_t tokens[1024];
    jfes_size_t tokens_count = 1024;

    jfes_config_t config;
    config.jfes_malloc = (jfes_malloc_t)malloc;
    config.jfes_free = free;

    jfes_init_parser(&parser, &config);
    jfes_status_t status = jfes_parse_tokens(&parser, json_data, buffer_size, tokens, &tokens_count);

    free(json_data);
    return 0;
}