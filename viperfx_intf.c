#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "viperfx_intf.h"

int viperfx_command_set_px4_vx4x1 (viperfx_interface * intf,
	int32_t param, int32_t value)
{
  int32_t cmd_data[3];
  cmd_data[0] = param;
  cmd_data[1] = sizeof(int32_t);
  cmd_data[2] = value;

  return (!intf->command (intf, COMMAND_CODE_SET,
    sizeof(cmd_data), cmd_data, NULL, NULL));
}

int viperfx_command_set_px4_vx4x2 (viperfx_interface * intf,
	int32_t param, int32_t value_l, int32_t value_h)
{
  int32_t cmd_data[4];
  cmd_data[0] = param;
  cmd_data[1] = sizeof(int32_t) << 1;
  cmd_data[2] = value_l;
  cmd_data[3] = value_h;

  return (!intf->command (intf, COMMAND_CODE_SET,
    sizeof(cmd_data), cmd_data, NULL, NULL));
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

  return (!intf->command (intf, COMMAND_CODE_SET,
    sizeof(cmd_data), cmd_data, NULL, NULL));
}

int viperfx_command_set_ir_path (viperfx_interface * intf,
    const char * pathname)
{
  char cmd_data[4 + 256];
  int32_t * cmd_data_int = (int32_t *)cmd_data;
  int32_t pathlen = (int32_t) strlen(pathname);
	
  if (pathlen >= 256)
    return FALSE;

  memset (cmd_data, 0, sizeof(cmd_data));
  cmd_data_int[0] = PARAM_HPFX_CONV_UPDATEKERNEL;
  cmd_data_int[1] = 256;
  cmd_data_int[2] = pathlen;
  memcpy (&cmd_data_int[3],
      pathname, pathlen);

  return (!intf->command (intf, COMMAND_CODE_SET,
    sizeof(cmd_data), cmd_data, NULL, NULL));
}
