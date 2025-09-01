#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
// #include <math.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <stdbool.h>
#include <pthread.h>

pthread_mutex_t record_mutex = PTHREAD_MUTEX_INITIALIZER;

void *image_maker(void *arg)
{
    void **args = (void **)arg;
    int (*record)[4] = (int (*)[4])args[0];
    int num = (intptr_t)args[1];
    const int rect = (rand() % 500) + 1;
    pthread_mutex_lock(&record_mutex);
    record[num][3] = 0;
    int const width = record[num][0];
    int const height = record[num][1];
    record[num][2] = (rect + (width * height));
    pthread_mutex_unlock(&record_mutex);
    free(args);

    uint8_t *image = malloc(width * height * 3);
    if (!image)
    {
        fprintf(stderr, "Failed to allocate memory\n");
        free(image);
        return NULL;
    }

    int r = rand() % 256, g = rand() % 256, b = rand() % 256;
    bool ra = true, ga = true, ba = true;

    for (int x = 0; x < width; ++x)
    {

        uint8_t red = r;
        uint8_t green = g;
        uint8_t blue = b;

        if (ra)
        {
            r += rand() % 2;
        }
        else
        {
            r -= rand() % 2;
        }

        if (ga)
        {
            g += rand() % 2;
        }
        else
        {
            g -= rand() % 2;
        }

        if (ba)
        {
            b += rand() % 2;
        }
        else
        {
            b -= rand() % 2;
        }

        if (r > 255)
        {
            r = 255;
            ra = false;
        }

        if (g > 255)
        {
            g = 255;
            ga = false;
        }

        if (b > 255)
        {
            b = 255;
            ba = false;
        }

        if (r < 0)
        {
            r = 0;
            ra = true;
        }

        if (b < 0)
        {
            b = 0;
            ba = true;
        }

        if (g < 0)
        {
            g = 0;
            ga = true;
        }

        for (int y = 0; y < height; ++y)
        {
            size_t idx = (size_t)y * width * 3 + (size_t)x * 3;
            image[idx + 0] = red;
            image[idx + 1] = green;
            image[idx + 2] = blue;
            pthread_mutex_lock(&record_mutex);
            record[num][3] += 1;
            pthread_mutex_unlock(&record_mutex);
        }
    }

    for (int recta = 0; recta < rect; recta++)
    {
        int x = rand() % width;
        int y = rand() % height;
        int xs = rand() % width;
        int ys = rand() % height;
        r = rand() % 256;
        g = rand() % 256;
        b = rand() % 256;
        uint8_t red = r;
        uint8_t green = g;
        uint8_t blue = b;
        for (int i = xs; i < x; i++)
        {
            for (int j = ys; j < y; j++)
            {
                if (i >= 0 && i < width && j >= 0 && j < height)
                {
                    size_t idx = (size_t)j * width * 3 + (size_t)i * 3;
                    image[idx + 0] = red;
                    image[idx + 1] = green;
                    image[idx + 2] = blue;
                }
            }
        }
        pthread_mutex_lock(&record_mutex);
        record[num][3] += 1;
        pthread_mutex_unlock(&record_mutex);
    }

    char filename[64];
    sprintf(filename, "output%d.png", num);

    if (!stbi_write_png(filename, width, height, 3, image, width * 3))
    {
        fprintf(stderr, "Failed to write image\n");
        free(image);
        return NULL;
    }
    free(image);
    return NULL;
}

int main()
{

    printf("Welcome to image Downloader\n");
    int total;
    printf("\nHow many images do you want to downlaod? ");
    scanf("%d", &total);

    int record[total][4];
    pthread_t threads[total];
    int res;
    printf("Do you want to set individual resolution or all the same\nPress 0 for Individual\nPress 1 All the same\n");
    scanf("%d", &res);
    if (res == 0)
    {
        for (int i = 0; i < total; i++)
        {
            printf("For image %2d what resolution do you want\n", i + 1);
            printf("Press 0 for 1280 X 720 (HD)\n");
            printf("Press 1 for 1920 X 1080 (FHD)\n");
            printf("Press 2 for 3840 X 2160 (4K)\n");
            printf("Press 3 for 7680 X 4320 (8K)\n");
            scanf("%d", &res);
            if (res == 0)
            {
                record[i][0] = 1280;
                record[i][1] = 720;
                record[i][2] = 0;
                record[i][3] = 0;
            }
            else if (res == 1)
            {
                record[i][0] = 1920;
                record[i][1] = 1080;
                record[i][2] = 0;
                record[i][3] = 0;
            }
            else if (res == 2)
            {
                record[i][0] = 3840;
                record[i][1] = 2160;
                record[i][2] = 0;
                record[i][3] = 0;
            }
            else
            {
                record[i][0] = 7680;
                record[i][1] = 4320;
                record[i][2] = 0;
                record[i][3] = 0;
            }
        }
    }
    else
    {
        printf("What resolution do you want for the images\n");
        printf("Press 0 for 1280 X 720 (HD)\n");
        printf("Press 1 for 1920 X 1080 (FHD)\n");
        printf("Press 2 for 3840 X 2160 (4K)\n");
        printf("Press 3 for 7680 X 4320 (8K)\n");
        scanf("%d", &res);
        printf("Setting things up ...\n");
        for (int i = 0; i < total; i++)
        {
            if (res == 0)
            {
                record[i][0] = 1280;
                record[i][1] = 720;
                record[i][2] = 0;
                record[i][3] = 0;
            }
            else if (res == 1)
            {
                record[i][0] = 1920;
                record[i][1] = 1080;
                record[i][2] = 0;
                record[i][3] = 0;
            }
            else if (res == 2)
            {
                record[i][0] = 3840;
                record[i][1] = 2160;
                record[i][2] = 0;
                record[i][3] = 0;
            }
            else
            {
                record[i][0] = 7680;
                record[i][1] = 4320;
                record[i][2] = 0;
                record[i][3] = 0;
            }
        }
    }

    printf("Starting to make thread\n");

    for (int i = 0; i < total; i++)
    {
        void **args = malloc(2 * sizeof(void *));
        args[0] = record;
        args[1] = (void *)(intptr_t)i;
        if (pthread_create(&threads[i], NULL, image_maker, (void *)args))
        {
            printf("Error creating thread\n");
            exit(1);
        }
    }

    printf("All threads are made Downloading image...\n");

    sleep(1);

    while (true)
    {
        pthread_mutex_lock(&record_mutex);
        for (int i = 0; i < 23; i++)
        {
            printf("_");
        }
        printf("\n");
        printf("|Thread | percent Done|\n");
        int compelted = 0;
        for (int i = 0; i < total; i++)
        {
            int per = 0;
            if (record[i][3] > 0 && record[i][2] > 0)
            {
                per = (int)(((int64_t)record[i][3] * 100) / record[i][2]);
                if (per == 100)
                {
                    compelted += 1;
                }
            }
            printf("|%4d   | %3d         |\n", i + 1, per);
        }
        pthread_mutex_unlock(&record_mutex);
        for (int i = 0; i < 23; i++)
        {
            printf("-");
        }
        printf("\n\n");
        if (compelted == total)
        {
            break;
        }
        sleep(1);
    }
    printf("Almost there, just wraping things up\n");
    for (int i = 0; i < total; i++)
    {
        pthread_join(threads[i], NULL);
    }
    printf("We are all done thanks for downloading images from us:) \n");
    return 0;
}
