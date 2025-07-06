#ifndef IO_H
#define IO_H

typedef enum 
{
  IO_10, IO_11, IO_12, IO_13, IO_14, IO_15, IO_16, IO_17, 
  IO_20, IO_21, IO_22, IO_23, IO_24, IO_25, IO_26, IO_27, 
} io_e;

typedef enum 
{
  IO_SELECT_GPIO, 
  IO_SELECT_ALT1,
  IO_SELECT_ALT2,
  IO_SELECT_ALT3,
} io_select_e;

typedef enum 
{
  IO_DIR_INPUT, 
  IO_DIR_OUTPUT
} io_dir_e;

typedef enum
{
    IO_RESISTOR_DISABLED,
    IO_RESISTOR_ENABLED,
} io_resistor_e;

typedef enum
{
    IO_OUT_LOW, // (pull-down)
    IO_OUT_HIGH, // (pull-up)
} io_out_e;

typedef enum
{
    IO_TRIGGER_RISING,
    IO_TRIGGER_FALLING
} io_trigger_e;

typedef struct
{
    io_select_e select;
    io_resistor_e resistor;
    io_dir_e dir;
    io_out_e out;
} io_config;

typedef enum 
{
  IO_IN_LOW, 
  IO_IN_HIGH,
} io_in_e;

void io_configure(io_e io, io_config config);
void io_set_select(io_e io, io_select_e io_select);
void io_set_dir(io_e io, io_dir_e io_dir);
void io_set_resistor(io_e io, io_resistor_e io_res);
void io_set_out(io_e io, io_out_e io_out);
void io_set_trigger(io_e io, io_trigger_e io_trigger);
io_in_e io_get_dir(io_e io);



#endif 
