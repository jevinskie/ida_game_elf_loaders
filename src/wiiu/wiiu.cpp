#include "elf_reader.h"
#include "cafe_loader.h"

#include <idaldr.h>

static int idaapi
 accept_file(linput_t *li, char fileformatname[MAX_FILE_FORMAT_NAME], int n) 
{
  if ( n > 0 )
    return 0;
    
  elf_reader<elf32> elf(li);
  
  if (elf.verifyHeader()) {
    if (elf.type() == ELF_FILETYPE_CAFE_RPL) {
      set_processor_type("ppc", SETPROC_ALL);

      qsnprintf(fileformatname, MAX_FILE_FORMAT_NAME, "WII U RPX/RPL");
      return ACCEPT_FIRST | 1;
    }
  }
  
  return 0;
}

static void idaapi
 load_file(linput_t *li, ushort neflags, const char *fileformatname)
{
  elf_reader<elf32> elf(li); elf.read();
  
  ea_t relocAddr = 0;
  if (neflags & NEF_MAN) {
    askaddr(&relocAddr, "Please specify a relocation address base.");
  }
  
  cafe_loader ldr(&elf); ldr.apply();
}

#ifdef _WIN32
__declspec(dllexport)
#endif
loader_t LDSC =
{
  IDP_INTERFACE_VERSION,
  0,
  accept_file,
  load_file,
  NULL,
  NULL,
  NULL
};