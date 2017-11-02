#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <dlfcn.h>
#include "viperfx_so.h"

#define ViPERFX_SO "libviperfx.so"
#define ViPERFX_ENTRYPOINT "viperfx_create_instance"

void* viperfx_load_library (const char * so_path_name)
{
  if (so_path_name == NULL) {
    return dlopen (ViPERFX_SO, RTLD_NOW);
  } else {
    return dlopen (so_path_name, RTLD_NOW);
  }
}

void viperfx_unload_library (void * handle)
{
  if (handle == NULL)
    return;
  dlclose (handle);
}

fn_viperfx_ep query_viperfx_entrypoint (void * handle)
{
  if (handle == NULL)
    return NULL;
  return (fn_viperfx_ep)dlsym (
      handle, ViPERFX_ENTRYPOINT);
}

int viperfx_command_set_px4_vx4x1 (viperfx_interface * intf,
	int32_t param, int32_t value)
{
  int32_t cmd_data[3];
  cmd_data[0] = param;
  cmd_data[1] = sizeof(int32_t) * 1;
  cmd_data[2] = value;

  if (intf->command (intf, COMMAND_CODE_SET,
    sizeof(cmd_data), cmd_data, NULL, NULL) != 0) {
    return FALSE;
  }
  return TRUE;
}

int viperfx_command_set_px4_vx4x2 (viperfx_interface * intf,
	int32_t param, int32_t value_l, int32_t value_h)
{
  int32_t cmd_data[4];
  cmd_data[0] = param;
  cmd_data[1] = sizeof(int32_t) * 2;
  cmd_data[2] = value_l;
  cmd_data[3] = value_h;

  if (intf->command (intf, COMMAND_CODE_SET,
    sizeof(cmd_data), cmd_data, NULL, NULL) != 0) {
    return FALSE;
  }
  return TRUE;
}

int viperfx_command_set_px4_vx4x3 (viperfx_interface * intf,
	int32_t param, int32_t value_l, int32_t value_h, int32_t value_e)
{
  int32_t cmd_data[5];
  cmd_data[0] = param;
  cmd_data[1] = sizeof(int32_t) * 3;
  cmd_data[2] = value_l;
  cmd_data[3] = value_h;
  cmd_data[4] = value_e;

  if (intf->command (intf, COMMAND_CODE_SET,
    sizeof(cmd_data), cmd_data, NULL, NULL) != 0) {
    return FALSE;
  }
  return TRUE;
}

int viperfx_command_set_ir_path (viperfx_interface * intf,
    const char * pathname)
{
  char cmd_data[4 + 256];
  int32_t * cmd_data_int = (int32_t *)cmd_data;

  if (strlen (pathname) >= 256)
    return FALSE;

  memset (cmd_data, 0, sizeof(cmd_data));
  cmd_data_int[0] = PARAM_HPFX_CONV_UPDATEKERNEL;
  cmd_data_int[1] = 256;
  cmd_data_int[2] = (int32_t)strlen (pathname);
  memcpy (&cmd_data_int[3],
      pathname, strlen (pathname));

  if (intf->command (intf, COMMAND_CODE_SET,
    sizeof(cmd_data), cmd_data, NULL, NULL) != 0) {
      return FALSE;
  }
  return TRUE;
}
