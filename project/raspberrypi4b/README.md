### 1. Board

#### 1.1 Board Info

Board Name: Raspberry Pi 4B.

IIC Pin: SCL/SDA GPIO3/GPIO2.

### 2. Install

#### 2.1 Dependencies

Install the necessary dependencies.

```shell
sudo apt-get install libgpiod-dev pkg-config cmake -y
```

#### 2.2 Makefile

Build the project.

```shell
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

#### 2.3 CMake

Build the project.

```shell
mkdir build && cd build 
cmake .. 
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

Test the project and this is optional.

```shell
make test
```

Find the compiled library in CMake. 

```cmake
find_package(mag3110 REQUIRED)
```

### 3. MAG3110

#### 3.1 Command Instruction

1. Show mag3110 chip and driver information.

   ```shell
   mag3110 (-i | --information)
   ```

2. Show mag3110 help.

   ```shell
   mag3110 (-h | --help)
   ```

3. Show mag3110 pin connections of the current board.

   ```shell
   mag3110 (-p | --port)
   ```

4. Run mag3110 register test.

   ```shell
   mag3110 (-t reg | --test=reg)
   ```

5. Run mag3110 read test, num means test times.

   ```shell
   mag3110 (-t read | --test=read) [--times=<num>]
   ```

6. Run mag3110 read function, num means read times.

   ```shell
   mag3110 (-e read | --example=read) [--times=<num>]
   ```

#### 3.2 Command Example

```shell
./mag3110 -i

mag3110: chip is NXP MAG3110.
mag3110: manufacturer is NXP.
mag3110: interface is IIC.
mag3110: driver version is 1.0.
mag3110: min supply voltage is 2.0V.
mag3110: max supply voltage is 3.6V.
mag3110: max current is 0.90mA.
mag3110: max temperature is 85.0C.
mag3110: min temperature is -40.0C.
```

```shell
./mag3110 -p

mag3110: SCL connected to GPIO3(BCM).
mag3110: SDA connected to GPIO2(BCM).
```

```shell
./mag3110 -t reg

mag3110: chip is NXP MAG3110.
mag3110: manufacturer is NXP.
mag3110: interface is IIC.
mag3110: driver version is 1.0.
mag3110: min supply voltage is 2.0V.
mag3110: max supply voltage is 3.6V.
mag3110: max current is 0.90mA.
mag3110: max temperature is 85.0C.
mag3110: min temperature is -40.0C.
mag3110: start register test.
mag3110: mag3110_get_data_ready_status test.
mag3110: data status is 0x00.
mag3110: mag3110_get_mode_status test.
mag3110: mode status is 0x00.
mag3110: mag3110_set_offset_x/mag3110_get_offset_x test.
mag3110: set offset x 0x1C7F.
mag3110: check offset x ok.
mag3110: mag3110_set_offset_y/mag3110_get_offset_y test.
mag3110: set offset y 0x08BD.
mag3110: check offset y ok.
mag3110: mag3110_set_offset_z/mag3110_get_offset_z test.
mag3110: set offset z 0x60E3.
mag3110: check offset z ok.
mag3110: mag3110_set_rate_over_sample/mag3110_get_rate_over_sample test.
mag3110: set rate 80hz, 16 over sample.
mag3110: check rate over sample z ok.
mag3110: set rate 40hz, 32 over sample.
mag3110: check rate over sample z ok.
mag3110: set rate 20hz, 64 over sample.
mag3110: check rate over sample z ok.
mag3110: set rate 10hz, 128 over sample.
mag3110: check rate over sample z ok.
mag3110: set rate 40hz, 16 over sample.
mag3110: check rate over sample z ok.
mag3110: set rate 20hz, 32 over sample.
mag3110: check rate over sample z ok.
mag3110: set rate 10hz, 64 over sample.
mag3110: check rate over sample z ok.
mag3110: set rate 5hz, 128 over sample.
mag3110: check rate over sample z ok.
mag3110: set rate 20hz, 16 over sample.
mag3110: check rate over sample z ok.
mag3110: set rate 10hz, 32 over sample.
mag3110: check rate over sample z ok.
mag3110: set rate 5hz, 64 over sample.
mag3110: check rate over sample z ok.
mag3110: set rate 2.5hz, 128 over sample.
mag3110: check rate over sample z ok.
mag3110: set rate 10hz, 16 over sample.
mag3110: check rate over sample z ok.
mag3110: set rate 5hz, 32 over sample.
mag3110: check rate over sample z ok.
mag3110: set rate 2.5hz, 64 over sample.
mag3110: check rate over sample z ok.
mag3110: set rate 1.25hz, 128 over sample.
mag3110: check rate over sample z ok.
mag3110: set rate 5hz, 16 over sample.
mag3110: check rate over sample z ok.
mag3110: set rate 2.5hz, 32 over sample.
mag3110: check rate over sample z ok.
mag3110: set rate 1.25hz, 64 over sample.
mag3110: check rate over sample z ok.
mag3110: set rate 0.63hz, 128 over sample.
mag3110: check rate over sample z ok.
mag3110: set rate 2.5hz, 16 over sample.
mag3110: check rate over sample z ok.
mag3110: set rate 1.25hz, 32 over sample.
mag3110: check rate over sample z ok.
mag3110: set rate 0.63hz, 64 over sample.
mag3110: check rate over sample z ok.
mag3110: set rate 0.31hz, 128 over sample.
mag3110: check rate over sample z ok.
mag3110: set rate 1.25hz, 16 over sample.
mag3110: check rate over sample z ok.
mag3110: set rate 0.63hz, 32 over sample.
mag3110: check rate over sample z ok.
mag3110: set rate 0.31hz, 64 over sample.
mag3110: check rate over sample z ok.
mag3110: set rate 0.16hz, 128 over sample.
mag3110: check rate over sample z ok.
mag3110: set rate 0.63hz, 16 over sample.
mag3110: check rate over sample z ok.
mag3110: set rate 0.31hz, 32 over sample.
mag3110: check rate over sample z ok.
mag3110: set rate 0.16hz, 64 over sample.
mag3110: check rate over sample z ok.
mag3110: set rate 0.08hz, 128 over sample.
mag3110: check rate over sample z ok.
mag3110: mag3110_set_fast_read_mode/mag3110_get_fast_read_mode test.
mag3110: enable fast read mode.
mag3110: check mode ok.
mag3110: disable fast read mode.
mag3110: check mode ok.
mag3110: mag3110_set_trigger_mode/mag3110_get_trigger_mode test.
mag3110: enable trigger mode.
mag3110: check trigger mode ok.
mag3110: disable trigger mode.
mag3110: check trigger mode ok.
mag3110: mag3110_set_mode/mag3110_get_mode test.
mag3110: set active mode.
mag3110: check mode ok.
mag3110: set standby mode.
mag3110: check mode ok.
mag3110: mag3110_set_automatic_magnetic_sensor_reset test.
mag3110: enable automatic magnetic sensor reset.
mag3110: check reset ok.
mag3110: disable automatic magnetic sensor reset.
mag3110: check reset ok.
mag3110: mag3110_set_disable_offset_correction/mag3110_get_disable_offset_correction test.
mag3110: disable offset correction.
mag3110: check disable offset correction ok.
mag3110: enable offset correction.
mag3110: check disable offset correction ok.
mag3110: mag3110_offset_convert_to_register/mag3110_offset_convert_to_data test.
mag3110: set ut 915.0.
mag3110: check ut 915.0.
mag3110: set ut -793.0.
mag3110: check ut -793.0.
mag3110: mag3110_reset test.
mag3110: check reset ok.
mag3110: finish register test.
```

```shell
./mag3110 -t read --times=3

mag3110: chip is NXP MAG3110.
mag3110: manufacturer is NXP.
mag3110: interface is IIC.
mag3110: driver version is 1.0.
mag3110: min supply voltage is 2.0V.
mag3110: max supply voltage is 3.6V.
mag3110: max current is 0.90mA.
mag3110: max temperature is 85.0C.
mag3110: min temperature is -40.0C.
mag3110: start read test.
mag3110: normal read mode test.
mag3110: x is 35.7uT.
mag3110: y is 7.6uT.
mag3110: z is -59.9uT.
mag3110: x is 35.6uT.
mag3110: y is 7.4uT.
mag3110: z is -60.2uT.
mag3110: x is 35.5uT.
mag3110: y is 6.9uT.
mag3110: z is -60.4uT.
mag3110: fast read mode test.
mag3110: x is 35.6uT.
mag3110: y is 7.0uT.
mag3110: z is -60.6uT.
mag3110: x is 35.6uT.
mag3110: y is 7.4uT.
mag3110: z is -59.9uT.
mag3110: x is 35.7uT.
mag3110: y is 7.6uT.
mag3110: z is -60.2uT.
mag3110: trigger mode test.
mag3110: x is 35.7uT.
mag3110: y is 7.3uT.
mag3110: z is -59.6uT.
mag3110: x is 35.6uT.
mag3110: y is 7.2uT.
mag3110: z is -60.0uT.
mag3110: x is 35.5uT.
mag3110: y is 7.3uT.
mag3110: z is -59.5uT.
mag3110: read die temperature test.
mag3110: die temperature is 30.0C.
mag3110: die temperature is 30.0C.
mag3110: die temperature is 30.0C.
mag3110: finish read test.
```

```shell
./mag3110 -e read --times=3

1/3
x is 35.200uT.
y is 6.900uT.
z is -59.600uT.
2/3
x is 35.500uT.
y is 7.300uT.
z is -60.000uT.
3/3
x is 35.500uT.
y is 6.900uT.
z is -59.600uT.
```

```shell
./mag3110 -h

Usage:
  mag3110 (-i | --information)
  mag3110 (-h | --help)
  mag3110 (-p | --port)
  mag3110 (-t reg | --test=reg)
  mag3110 (-t read | --test=read) [--times=<num>]
  mag3110 (-e read | --example=read) [--times=<num>]

Options:
  -e <read>, --example=<read>
                                 Run the driver example.
  -h, --help                     Show the help.
  -i, --information              Show the chip information.
  -p, --port                     Display the pin connections of the current board.
  -t <reg | read>, --test=<reg | read>
                                 Run the driver test.
      --times=<num>              Set the running times.([default: 3])
```

