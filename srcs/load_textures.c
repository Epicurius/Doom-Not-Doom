/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 13:01:23 by nneronin          #+#    #+#             */
/*   Updated: 2020/10/15 13:04:47 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static int LoadTexture(void)
{
    int initialized = 0;
    int fd = open("portrend_textures.bin", O_RDWR | O_CREAT, 0644);

        #define UnloadTexture(name) free(name)

        Texture dummylightmap;
        memset(&dummylightmap, 0, sizeof(dummylightmap));

        LoadTexture("wall2.ppm", WallTexture);   LoadTexture("wall2_norm.ppm", WallNormal);
        LoadTexture("wall3.ppm", WallTexture2);  LoadTexture("wall3_norm.ppm", WallNormal2);
        LoadTexture("floor2.ppm", FloorTexture); LoadTexture("floor2_norm.ppm", FloorNormal);
        LoadTexture("ceil2.ppm", CeilTexture);   LoadTexture("ceil2_norm.ppm", CeilNormal);

        printf("Initializing textures... ");
        lseek(fd, 0, SEEK_SET);
        for(unsigned n=0; n<NumSectors; ++n)
        {
            for(int s=printf("%d/%d", n+1,NumSectors); s--; ) putchar('\b');
            fflush(stdout);

            PutTextureSet(FloorTexture, FloorNormal);
            PutTextureSet(CeilTexture,  CeilNormal);
            for(unsigned w=0; w<sectors[n].npoints; ++w) PutTextureSet(WallTexture, WallNormal);
            for(unsigned w=0; w<sectors[n].npoints; ++w) PutTextureSet(WallTexture2, WallNormal2);
        }
        ftruncate(fd, lseek(fd, 0, SEEK_CUR));
        printf("\n"); fflush(stdout);

        UnloadTexture(WallTexture);  UnloadTexture(WallNormal);
        UnloadTexture(WallTexture2); UnloadTexture(WallNormal2);
        UnloadTexture(FloorTexture); UnloadTexture(FloorNormal);
        UnloadTexture(CeilTexture);  UnloadTexture(CeilNormal);

        #undef UnloadTexture
        #undef LoadTexture
        initialized = 1;
    }
    off_t filesize = lseek(fd, 0, SEEK_END);
    char* texturedata = mmap(NULL, filesize, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if(!texturedata) perror("mmap");

    printf("Loading textures\n");
    off_t pos = 0;
    for(unsigned n=0; n<NumSectors; ++n)
    {
        sectors[n].floortexture = (void*) (texturedata + pos); pos += sizeof(struct TextureSet);
        sectors[n].ceiltexture  = (void*) (texturedata + pos); pos += sizeof(struct TextureSet);
        unsigned w = sectors[n].npoints;
        sectors[n].uppertextures = (void*) (texturedata + pos); pos += sizeof(struct TextureSet) * w;
        sectors[n].lowertextures = (void*) (texturedata + pos); pos += sizeof(struct TextureSet) * w;
    }
    printf("done, %llu bytes mmapped out of %llu\n", (unsigned long long)pos, (unsigned long long) filesize);
    if(pos != filesize)
    {
        printf(" -- Wrong filesize! Let's try that again.\n");
        munmap(texturedata, filesize);
        goto InitializeTextures;
    }
    return initialized;
}
