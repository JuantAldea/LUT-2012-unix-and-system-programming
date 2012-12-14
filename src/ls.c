/*******************************************************************\
 *                                                                 *
 *             CT50A3000 - Unix and System Programming             *
 *                                                                 *
 *    Shell Project                                                *
 *                                                                 *
 *    Authors:                                                     *
 *        Juan Antonio Aldea Armenteros - 0404450                  *
 *        Pablo Caro Martin - 0404489                              *
 *                                                                 *
\*******************************************************************/

#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <grp.h>
#include <pwd.h>
#include <time.h>
void print_text_permissions(mode_t protection)
{
    printf((S_ISDIR(protection))  ? "d" : "-");
    printf((protection & S_IRUSR) ? "r" : "-");
    printf((protection & S_IWUSR) ? "w" : "-");
    printf((protection & S_IXUSR) ? "x" : "-");
    printf((protection & S_IRGRP) ? "r" : "-");
    printf((protection & S_IWGRP) ? "w" : "-");
    printf((protection & S_IXGRP) ? "x" : "-");
    printf((protection & S_IROTH) ? "r" : "-");
    printf((protection & S_IWOTH) ? "w" : "-");
    printf((protection & S_IXOTH) ? "x" : "-");
}

void print_file_dir_entry(char *name, struct stat *filestat)
{
    print_text_permissions(filestat->st_mode);
    printf(" %d ", filestat->st_nlink);
    printf("%s ", getpwuid(filestat->st_uid)->pw_name);
    printf("%s ", getgrgid(filestat->st_gid)->gr_name);
    printf("%d ", filestat->st_size);
    char *date = ctime(&(filestat->st_mtime));
    date[strlen(date) - 1] = '\0';
    printf("%s ", date);
    printf("%s", name);
    printf("\n");
}

int main (int argc, char *argv[])
{
    int list_all = 0;
    int verbose = 0;
    int optc = -1;
    while ((optc = getopt(argc, argv, "la")) != -1) {
        switch (optc) {
            case 'a':
                list_all = 1;
            break;
            case 'l':
                verbose = 1;
            break;
        }
    }

    char *path = NULL;
    if (optind == argc){
        path = malloc(sizeof(sizeof(char) * 2));
        path[0] = '.';
        path[1] = '\0';
    }else{
        path = argv[optind];
    }

    DIR *dir = opendir(path);
    if (dir == NULL){
        struct stat stat_info;
        if (stat(path, &stat_info) == 0){
            print_file_dir_entry(path, &stat_info);
        }else{
            fprintf(stderr, "Unable to open %s: %s\n", path,  strerror(errno));
        }
        return;
    }

    struct dirent *dir_contents = NULL;
    while((dir_contents = readdir(dir)) != NULL){
        struct stat stat_info;
        if (list_all || dir_contents->d_name[0] != '.'){
            if (!verbose){
                printf("%s ", dir_contents->d_name);
            }else{
                char *full_path = malloc(strlen(dir_contents->d_name) + strlen(path) + 2);
                sprintf(full_path, "%s/%s", path, dir_contents->d_name);
                if (stat(full_path, &stat_info) == 0){
                    print_file_dir_entry(dir_contents->d_name, &stat_info);
                }else{
                    printf("ERROR\n");
                }
                free(full_path);
            }
        }
    }
    if (!verbose){
        printf("\n");
    }

    if (optind == argc){
        free(path);
    }
    if (dir != NULL){
        closedir(dir);
    }
    return 0;
}
