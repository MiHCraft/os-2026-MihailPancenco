#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fs.h"
#include "kernel/param.h"
#include "kernel/fcntl.h"
#include "user/user.h"

static char path[MAXPATH];
static char *wanted;
static int show_inode;
static int failed;

/* Read one entry and close before recursion: depth never consumes FDs.
 * Reopening and skipping costs O(n^2) reads per directory, acceptable here.
 * The directory must not be modified during the walk. */
static int
entry_at(int index, struct dirent *entry)
{
  int fd = open(path, O_RDONLY);
  if(fd < 0){
    fprintf(2, "find: cannot open %s\n", path);
    failed = 1;
    return -1;
  }
  int n = 0;
  for(int i = 0; i <= index; i++){
    n = read(fd, entry, sizeof(*entry));
    if(n != sizeof(*entry))
      break;
  }
  close(fd);
  if(n == 0)
    return 0;
  if(n != sizeof(*entry)){
    fprintf(2, "find: directory read failed: %s\n", path);
    failed = 1;
    return -1;
  }
  return 1;
}

static void
walk(void)
{
  struct stat st;
  struct dirent entry;
  char name[DIRSIZ + 1];
  if(stat(path, &st) < 0){
    fprintf(2, "find: cannot stat %s\n", path);
    failed = 1;
    return;
  }
  char *base = path;
  for(char *p = path; *p; p++)
    if(*p == '/' && p[1])
      base = p + 1;
  if(strcmp(base, wanted) == 0){
    if(show_inode)
      printf("%s inode %d\n", path, st.ino);
    else
      printf("%s\n", path);
  }
  if(st.type != T_DIR)
    return;
  int len = strlen(path);
  for(int index = 0; entry_at(index, &entry) > 0; index++){
    if(entry.inum == 0)
      continue;
    memmove(name, entry.name, DIRSIZ);
    name[DIRSIZ] = 0;
    if(strcmp(name, ".") == 0 || strcmp(name, "..") == 0)
      continue;
    int slash = len > 0 && path[len - 1] != '/';
    if(len + slash + strlen(name) + 1 > sizeof(path)){
      fprintf(2, "find: path too long below %s\n", path);
      failed = 1;
      continue;
    }
    if(slash)
      path[len] = '/';
    strcpy(path + len + slash, name);
    walk();
    path[len] = 0;
  }
}

int
main(int argc, char *argv[])
{
  if((argc != 3 && argc != 4) ||
     (argc == 4 && strcmp(argv[3], "-n") != 0)){
    fprintf(2, "usage: find <dir> <name> [-n]\n");
    exit(1);
  }
  if(strlen(argv[1]) == 0 || strlen(argv[1]) >= sizeof(path)){
    fprintf(2, "find: invalid starting path\n");
    exit(1);
  }
  strcpy(path, argv[1]);
  int len = strlen(path);
  while(len > 1 && path[len - 1] == '/')
    path[--len] = 0;
  wanted = argv[2];
  show_inode = argc == 4;
  walk();
  exit(failed);
}
