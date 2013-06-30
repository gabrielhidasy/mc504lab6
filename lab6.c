#include <stdio.h>
#include <stdlib.h>
#include <ext2fs/ext2_fs.h>
#include <ext2fs/ext2fs.h>

int main (int argc, char *argv[]) {

  ext2_filsys * gagatinho = NULL;
  int error, bit1, bit2, n_seg, tam;
  ext2fs_block_bitmap* map;
  blk_t block_start, block_end;
  io_manager unix_io;
 
  error = ext2fs_open(argv[1], EXT2_FLAG_RW, 0, 4096, unix_io_manager, gagatinho); //EXT2_FLAG_RW flag que determina apenas leitura e escrita | superbloco 0 determina que o superbloco primário 1024 será usado
  if(error != 0){
    printf("Erro na abertura do sistema de arquivos.\n");
    return 0;
  }

  if(argc == 2){
   
    error = ext2fs_allocate_block_bitmap (*gagatinho, BLOCK_FLAG_DATA_ONLY, map);
    if(error != 0){
      printf("Erro na alocação do bitmap.\n");
      return 0;
    }
   
    block_start = ext2fs_get_block_bitmap_start (*map);
    block_end = ext2fs_get_block_bitmap_end (*map);
   
    for(bit2=0, n_seg=0; block_start <= block_end;  block_start++){
      bit1=bit2;
      bit2 = ext2fs_test_block_bitmap (*map, block_start);
      if(bit1==0&&bit2==0){
	n_seg++;
      } else {
	if(n_seg!=0){
	  printf("%dKB / %dsegm\n", n_seg*4, n_seg);
	  n_seg = 0;
	}
      }
    }
   
    /*error = ext2fs_read_block_bitmap(argv[0]);
      if(error != 0){
      printf("Erro na leitura do bitmap.\n");
      return 0;
      }*/
  } else if (argc == 3){
    //TODO
  } else {
    printf("Entrada inválida.\n");
  }
  error = ext2fs_close(*gagatinho);
  if(error != 0){
    printf("Erro no fechamento do sistema de arquivos.\n");
  }
  return 0;
}
