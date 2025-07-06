#include "io.h"
#include "common/defines.h"

  

void io_set_select(io_e io, io_select_e io_select)
{
  UNUSED(io);
  UNUSED(io_select);
}

void io_set_dir(io_e io, io_dir_e io_dir)
{
  UNUSED(io);
  UNUSED(io_dir);
}

void io_set_resistor(io_e io, io_resistor_e io_res)
{
  UNUSED(io);
  UNUSED(io_res);
}

void io_set_out(io_e io, io_out_e io_out)
{
  UNUSED(io);   
  UNUSED(io_out);
}

void io_set_trigger(io_e io, io_trigger_e io_trigger)
{
  UNUSED(io);
  UNUSED(io_trigger);
}

void io_configure(io_e io, io_config config)
{
  UNUSED(io);
  UNUSED(config);
}

io_in_e io_get_dir(io_e io)
{
  UNUSED(io);
  return IO_IN_LOW; 
}
